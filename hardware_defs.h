#ifndef _RTL8139_HW_H
#define _RTL8139_HW_H

#include <linux/netdevice.h>
#include <linux/io.h>

#include "hardware_registers.h"  // Includes the updated and renamed hardware register definitions

struct rtl8139_priv;

// Hardware Interface Functions

/**
 * Resets the RTL8139 hardware to its default state.
 * 
 * @param priv Pointer to the private data structure of the network device.
 * @return 0 on success, or a negative error code on failure.
 */
int rtl8139_hw_reset(struct rtl8139_priv *priv);

/**
 * Reads the MAC address from the EEPROM and writes it to the kernel.
 * 
 * @param ndev Pointer to the network device structure.
 */
void rtl8139_hw_eeprom_mac_to_kernel(struct net_device *ndev);

/**
 * Configures the MAC address in the device registers based on the kernel MAC.
 * 
 * @param ndev Pointer to the network device structure.
 */
void rtl8139_hw_kernel_mac_to_regs(struct net_device *ndev);

/**
 * Sets up the transmit (TX) ring buffer and descriptors.
 * 
 * @param priv Pointer to the private data structure of the network device.
 */
void rtl8139_hw_setup_tx(struct rtl8139_priv *priv);

/**
 * Sets up the receive (RX) ring buffer and descriptors.
 * 
 * @param priv Pointer to the private data structure of the network device.
 */
void rtl8139_hw_setup_rx(struct rtl8139_priv *priv);

/**
 * Disables the transceiver to save power.
 * 
 * @param priv Pointer to the private data structure of the network device.
 */
void rtl8139_hw_disable_transceiver(struct rtl8139_priv *priv);

/**
 * Enables interrupts for the RTL8139 device.
 * 
 * @param priv Pointer to the private data structure of the network device.
 */
void rtl8139_hw_enable_irq(struct rtl8139_priv *priv);

/**
 * Acknowledges and clears the interrupt status register.
 * 
 * @param priv Pointer to the private data structure of the network device.
 */
void rtl8139_hw_ack_irq(struct rtl8139_priv *priv);

/**
 * Disables interrupts for the RTL8139 device.
 * 
 * @param priv Pointer to the private data structure of the network device.
 */
void rtl8139_hw_disable_irq(struct rtl8139_priv *priv);

/**
 * Configures the LED settings on the RTL8139 device.
 * 
 * @param priv Pointer to the private data structure of the network device.
 * @param led_cfg LED configuration value to be set.
 */
void rtl8139_hw_configure_leds(struct rtl8139_priv *priv, u8 led_cfg);

/**
 * Returns a string representation of the hardware version.
 * 
 * @param version Hardware version ID.
 * @return Pointer to a string containing the hardware version.
 */
const char *rtl8139_hw_version_str(u32 version);


// Base Address Registers (BAR) in the PCI Configuration Space

enum
{
    RTL8139_IOAR,   // BAR0: I/O Ports, Programmed I/O (PMIO)
    RTL8139_MEMAR   // BAR1: Memory-Mapped I/O (MMIO)
                    // BAR2 -> BAR5 are unused (all 0)
};

// I/O and Memory regions require at least 256 bytes
#define RTL8139_IO_SIZE 256

// Maximum Ethernet frame size supported by the device
#define RTL8139_MAX_ETH_SIZE 1792
#define RTL8139_MAX_MTU (RTL8139_MAX_ETH_SIZE - ETH_HLEN - ETH_FCS_LEN)

// Transmit (TX) Descriptor Configuration
#define RTL8139_TX_DESC_NB 4  // Must be a power of 2 due to hardware constraints
#define RTL8139_TX_DESC_SIZE RTL8139_MAX_ETH_SIZE
#define RTL8139_TX_DMA_SIZE (RTL8139_TX_DESC_SIZE * RTL8139_TX_DESC_NB)

// Receive (RX) DMA Configuration
#define RTL8139_RX_PAD 16
#define RTL8139_RX_BUFLEN 16384
#define RTL8139_RX_DMA_SIZE (RTL8139_RX_BUFLEN + RTL8139_RX_PAD)
#define RTL8139_RX_HEADER_SIZE 4
#define RTL8139_RX_ALIGN_ADD 3
#define RTL8139_RX_ALIGN_MASK (~RTL8139_RX_ALIGN_ADD)
#define RTL8139_RX_ALIGN(val) (((val) + RTL8139_RX_ALIGN_ADD) & RTL8139_RX_ALIGN_MASK)

// RX Packet Header Structure
struct rtl8139_rx_header
{
    u16 status;  // Status of the received packet
    u16 size;    // Size of the received packet
};


// Macros for Register Access

/**
 * Reads an 8-bit value from a specified register.
 * 
 * @param reg Register offset.
 * @return Value read from the register.
 */
#define rtl8139_r8(reg)  ioread8(priv->mmio + (reg))

/**
 * Reads a 16-bit value from a specified register.
 * 
 * @param reg Register offset.
 * @return Value read from the register.
 */
#define rtl8139_r16(reg) ioread16(priv->mmio + (reg))

/**
 * Reads a 32-bit value from a specified register.
 * 
 * @param reg Register offset.
 * @return Value read from the register.
 */
#define rtl8139_r32(reg) ioread32(priv->mmio + (reg))

/**
 * Writes an 8-bit value to a specified register.
 * 
 * @param reg Register offset.
 * @param val Value to write.
 */
#define rtl8139_w8(reg, val)  iowrite8((val), priv->mmio + (reg))

/**
 * Writes a 16-bit value to a specified register.
 * 
 * @param reg Register offset.
 * @param val Value to write.
 */
#define rtl8139_w16(reg, val) iowrite16((val), priv->mmio + (reg))

/**
 * Writes a 32-bit value to a specified register.
 * 
 * @param reg Register offset.
 * @param val Value to write.
 */
#define rtl8139_w32(reg, val) iowrite32((val), priv->mmio + (reg))

// Raw Write Operations (No Endian Swapping)
/**
 * Writes a 16-bit value to a specified register without endian swapping.
 * 
 * @param reg Register offset.
 * @param val Value to write.
 */
#define rtl8139_w16_raw(reg, val) __raw_writew((val), priv->mmio + (reg))

/**
 * Writes a 32-bit value to a specified register without endian swapping.
 * 
 * @param reg Register offset.
 * @param val Value to write.
 */
#define rtl8139_w32_raw(reg, val) __raw_writel((val), priv->mmio + (reg))

#endif
