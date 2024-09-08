#ifndef _RTL8139_NET_H
#define _RTL8139_NET_H

#include "hardware_defs.h"

#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/pci.h>

// Struct to hold the private data of the RTL8139 network device
// Transmission ring buffer structure
struct rtl8139_tx_ring {
    void *buffers[RTL8139_TX_DESC_NB];   // Array of TX buffer pointers
    dma_addr_t dma_addr;                 // DMA address for hardware access
    int cpu_idx;                         // Index for CPU buffer position
    int hw_idx;                          // Index for hardware buffer position
};

// Reception ring buffer structure
struct rtl8139_rx_ring {
    unsigned char *buffer;               // Pointer to RX buffer
    dma_addr_t dma_addr;                 // DMA address for hardware access
    u16 cpu_idx;                         // Index for CPU buffer position
};

// Primary device structure
struct rtl8139_priv {
    int msg_enable;                      // Enable/disable various message levels (e.g., errors, debug)
    struct pci_dev *pdev;                // PCI device associated with the network card
    void __iomem *mmio;                  // Memory-mapped I/O base address for device registers

    u16 irq_flags;                       // Flags indicating active interrupt conditions

    struct rtl8139_tx_ring tx_ring;      // Transmit ring buffer
    struct rtl8139_rx_ring rx_ring;      // Receive ring buffer

    u32 trans_ctrl_reg;                  // Transmission control register value
    u32 tx_flags;                        // Flags for transmission control (e.g., queue status)
};

// Initialization of TX Ring buffer
int rtl8139_init_tx_ring(struct rtl8139_tx_ring *tx_ring) {
    // Initialize TX buffer pointers and DMA address
    memset(tx_ring->buffers, 0, sizeof(tx_ring->buffers));
    tx_ring->dma_addr = 0;
    tx_ring->cpu_idx = 0;
    tx_ring->hw_idx = 0;
    return 0; // Add error handling as needed
}

// Initialization of RX Ring buffer
int rtl8139_init_rx_ring(struct rtl8139_rx_ring *rx_ring) {
    // Allocate memory for RX buffer and initialize DMA address
    rx_ring->buffer = NULL; // Allocation logic here
    rx_ring->dma_addr = 0;
    rx_ring->cpu_idx = 0;
    return 0; // Add error handling as needed
}

// Initialization of the main private data structure
int rtl8139_priv_init(struct rtl8139_priv *priv, struct pci_dev *pdev) {
    priv->pdev = pdev;
    priv->mmio = NULL; // Set up MMIO base address
    priv->msg_enable = 0;
    priv->irq_flags = 0;
    priv->trans_ctrl_reg = 0;
    priv->tx_flags = 0;

    // Initialize TX and RX rings
    rtl8139_init_tx_ring(&priv->tx_ring);
    rtl8139_init_rx_ring(&priv->rx_ring);
    
    return 0; // Add error handling as needed
}

// Cleanup TX ring buffer
void rtl8139_cleanup_tx_ring(struct rtl8139_tx_ring *tx_ring) {
    // Free TX buffers and reset indices
    memset(tx_ring->buffers, 0, sizeof(tx_ring->buffers));
    tx_ring->dma_addr = 0;
    tx_ring->cpu_idx = 0;
    tx_ring->hw_idx = 0;
}

// Cleanup RX ring buffer
void rtl8139_cleanup_rx_ring(struct rtl8139_rx_ring *rx_ring) {
    // Free RX buffer and reset indices
    if (rx_ring->buffer) {
        // Free logic here
        rx_ring->buffer = NULL;
    }
    rx_ring->dma_addr = 0;
    rx_ring->cpu_idx = 0;
}

// Cleanup the private structure
void rtl8139_priv_cleanup(struct rtl8139_priv *priv) {
    rtl8139_cleanup_tx_ring(&priv->tx_ring);
    rtl8139_cleanup_rx_ring(&priv->rx_ring);
}


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
