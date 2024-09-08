#include "common.h"
#include "hardware_defs.h"
#include "network.h"

#include <linux/module.h>       // MODULE_PARM_DESC
#include <linux/moduleparam.h>  // module_param
#include <linux/interrupt.h>    // IRQF_SHARED, irqreturn_t, request_irq, free_irq

// Store the function pointers for network device operations
static struct net_device_ops r8139dn_netdev_ops = {
    .ndo_open = r8139dn_net_open,
    .ndo_start_xmit = r8139dn_net_start_xmit,
    .ndo_stop = r8139dn_net_close,
    .ndo_set_mac_address = r8139dn_net_set_mac_addr,
    .ndo_change_mtu = r8139dn_net_set_mtu,
};

// Helper function for net_device allocation and initialization
static int r8139dn_net_device_init(struct pci_dev *pdev, struct net_device **ndev_out) {
    struct net_device *ndev;
    struct r8139dn_priv *priv;

    // Allocate Ethernet device
    ndev = alloc_etherdev(sizeof(*priv));
    if (!ndev) {
        return -ENOMEM;
    }

    priv = netdev_priv(ndev);
    priv->pdev = pdev;
    priv->mmio = NULL; // This will be set in the main initialization function
    priv->msg_enable = netif_msg_init(debug, R8139DN_MSG_ENABLE); // Initialize message enable flags

    ndev->netdev_ops = &r8139dn_netdev_ops;
    SET_NETDEV_DEV(ndev, &pdev->dev);

    *ndev_out = ndev;
    return 0;
}

// Helper function to handle device registration and configuration
static int r8139dn_register_device(struct net_device *ndev, struct pci_dev *pdev) {
    int err;
    
    // Register network device
    err = register_netdev(ndev);
    if (err) {
        return err;
    }

    // Set PCI driver data
    pci_set_drvdata(pdev, ndev);

    return 0;
}

// Cleanup function to handle net_device cleanup on errors
static void r8139dn_net_device_cleanup(struct net_device *ndev) {
    free_netdev(ndev);
}

// Main initialization function
int r8139dn_net_init(struct pci_dev *pdev, void __iomem *mmio) {
    struct net_device *ndev;
    struct r8139dn_priv *priv;
    int err;

    // Initialize net_device and private data
    err = r8139dn_net_device_init(pdev, &ndev);
    if (err) {
        return err;
    }

    priv = netdev_priv(ndev);
    priv->mmio = mmio;  // Set the memory-mapped I/O base address

    // Hardware reset
    err = r8139dn_hw_reset(priv);
    if (err) {
        goto err_hw_reset;
    }

    // Retrieve MAC address
    r8139dn_hw_eeprom_mac_to_kernel(ndev);

    // Configure LEDs
    r8139dn_hw_configure_leds(priv, CFG1_LEDS_TXRX_LNK_FDX);

    // Register the network device
    err = r8139dn_register_device(ndev, pdev);
    if (err) {
        goto err_register_netdev;
    }

    // Check if TX/RX are active
    if (!(txrx & (TX | RX))) {
        netdev_warn(ndev, "Neither TX nor RX is activated. Is this really what you want?\n");
    }

    // Probe message if enabled
    if (netif_msg_probe(priv)) {
        netdev_info(ndev, "Ready!\n");
    }

    return 0;

// Error handling and cleanup
err_hw_reset:
    netdev_err(ndev, "Hardware reset failed\n");

err_register_netdev:
    r8139dn_net_device_cleanup(ndev);

    return err;
}

static int r8139dn_net_open(struct net_device *ndev) {
    struct r8139dn_priv *priv = netdev_priv(ndev);
    int irq = priv->pdev->irq;
    int err;

    if (netif_msg_ifup(priv)) {
        netdev_info(ndev, "Bringing interface up...\n");
    }

    err = request_irq(irq, r8139dn_net_interrupt, IRQF_SHARED, ndev->name, ndev);
    if (err) {
        return err;
    }

    priv->interrupts = INT_LNKCHG_PUN | INT_TIMEOUT;
    priv->tcr = TCR_IFG_DEFAULT | TCR_MXDMA_1024;

    err = r8139dn_hw_reset(priv);
    if (err) {
        goto err_open_hw_reset;
    }

    r8139dn_hw_kernel_mac_to_regs(ndev);
    netif_carrier_off(ndev);
    _r8139dn_net_check_link(ndev);

    if (txrx & TX) {
        err = _r8139dn_net_init_tx_ring(priv);
        if (err) {
            goto err_open_init_ring;
        }

        r8139dn_hw_setup_tx(priv);
        netif_start_queue(ndev);
        priv->interrupts |= INT_TX;
    } else {
        netif_stop_queue(ndev);
    }

    if (txrx & RX) {
        err = _r8139dn_net_init_rx_ring(priv);
        if (err) {
            goto err_open_init_ring;
        }

        r8139dn_hw_setup_rx(priv);
        priv->interrupts |= INT_RX;
    }

    r8139dn_hw_enable_irq(priv);
    return 0;

err_open_hw_reset:
err_open_init_ring:
    _r8139dn_net_release_rings(priv);
    free_irq(irq, ndev);
    return err;
}
