#include "common.h"
#include "hardware_defs.h"

#include <linux/module.h>       // MODULE_PARM_DESC
#include <linux/moduleparam.h>  // module_param
#include <linux/interrupt.h>    // IRQF_SHARED, irqreturn_t, request_irq, free_irq

irqreturn_t r8139dn_net_interrupt(int irq, void *dev) {
    struct net_device *ndev = (struct net_device *)dev;
    struct r8139dn_priv *priv = netdev_priv(ndev);
    u16 isr = r8139dn_r16(ISR);

    if (!isr) {
        return IRQ_NONE;
    }

    r8139dn_w16(ISR, isr);
    isr &= priv->interrupts;

    if (isr & INT_LNKCHG_PUN) {
        _r8139dn_net_check_link(ndev);
    }

    if (isr & INT_RX) {
        _r8139dn_net_interrupt_rx(ndev);
    }

    if (isr & INT_TX) {
        _r8139dn_net_interrupt_tx(ndev);
    }

    return IRQ_HANDLED;
}

void _r8139dn_net_interrupt_tx(struct net_device *ndev) {
    struct r8139dn_priv *priv = netdev_priv(ndev);
    struct r8139dn_tx_ring *tx_ring = &priv->tx_ring;
    int cpu, hw;
    u32 tsd;

    hw = smp_load_acquire(&tx_ring->hw);
    cpu = smp_load_acquire(&tx_ring->cpu);

    while (hw != cpu) {
        tsd = r8139dn_r32(TSD0 + hw * TSD_GAP);

        if (!(tsd & (TSD_TOK | TSD_TUN | TSD_TABT))) {
            break;
        }

        if (tsd & TSD_TOK) {
            ndev->stats.tx_packets++;
            ndev->stats.tx_bytes += (tsd & TSD_SIZE);
        } else {
            r8139dn_w16(ISR, INT_TER);
            ndev->stats.tx_errors++;

            if (tsd & TSD_TABT) {
                ndev->stats.tx_aborted_errors++;
            }

            if (tsd & TSD_TUN) {
                ndev->stats.tx_fifo_errors++;
            }
        }

        smp_store_release(&tx_ring->hw, (hw + 1) & (R8139DN_TX_DESC_NB - 1));
    }

    if (netif_queue_stopped(ndev)) {
        netif_wake_queue(ndev);
    }
}

void _r8139dn_net_interrupt_rx(struct net_device *ndev) {
    struct r8139dn_priv *priv = netdev_priv(ndev);
    struct r8139dn_rx_ring *rx_ring = &priv->rx_ring;
    struct r8139dn_rx_header *rxh;
    struct sk_buff *skb;
    u16 rx_offset;

    while (!(r8139dn_r8(CR) & CR_BUFE)) {
        rx_offset = (rx_ring->cpu) & (R8139DN_RX_BUFLEN - 1);
        // RX processing logic...
    }
}
