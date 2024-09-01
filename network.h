#ifndef _RTL8139_NET_H
#define _RTL8139_NET_H

#include "hardware_defs.h"

#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/pci.h>

// Struct to hold the private data of the RTL8139 network device
struct rtl8139_priv {
    int msg_enable;                  // Message enable flags
    struct pci_dev *pdev;            // Pointer to the PCI device structure
    void __iomem *mmio;              // Memory-mapped I/O base address

    u16 irq_flags;                   // Interrupts to be handled

    // TX Ring buffer structure
    struct rtl8139_tx_ring {
        void *buffers[RTL8139_TX_DESC_NB]; // Pointers to TX buffer data
        dma_addr_t dma_addr;                // DMA address for hardware access
        int cpu_idx, hw_idx;                // Indices for CPU and hardware buffer positions
    } tx_ring;

    // RX Ring buffer structure
    struct rtl8139_rx_ring {
        unsigned char *buffer;        // Pointer to RX buffer data
        dma_addr_t dma_addr;          // DMA address for hardware access
        u16 cpu_idx;                  // Index for CPU buffer position
    } rx_ring;

    u32 trans_ctrl_reg;               // Transmission control register
    u32 tx_flags;                     // Flags for transmission operations
};

/**
 * Initializes the RTL8139 network device.
 * 
 * @param pdev Pointer to the PCI device structure.
 * @param mmio Base address of the memory-mapped I/O.
 * @return 0 on success, or a negative error code on failure.
 */
int rtl8139_net_init(struct pci_dev *pdev, void __iomem *mmio);

/**
 * Default message enable flags for the network device.
 */
#define RTL8139_MSG_ENABLE \
    (NETIF_MSG_DRV       | \
     NETIF_MSG_PROBE     | \
     NETIF_MSG_LINK      | \
     NETIF_MSG_TIMER     | \
     NETIF_MSG_IFDOWN    | \
     NETIF_MSG_IFUP      | \
     NETIF_MSG_RX_ERR    | \
     NETIF_MSG_TX_ERR)

#endif
