# RTL8139
A simple driver for Realtek RTL8139 Chipset that is designed for Linux.
Nothing too fancy for sure. It cannot be a replacement for the real driver.


## Hardware Registers

### Unicast Filter Registers
- **UNICAST_REG_0 to UNICAST_REG_5 (0x00 - 0x05)**:  
  These registers are used to store the unicast MAC addresses for the network card. The card uses these addresses to filter incoming packets, ensuring that only packets addressed to these specific MAC addresses are accepted.

### Multicast Filter Registers
- **MULTICAST_REG_0 to MULTICAST_REG_7 (0x08 - 0x0F)**:  
  These registers store the multicast MAC addresses. The network card uses these addresses to filter and accept packets intended for specific multicast groups.

### Transmit Status and Address Descriptor Registers
- **TX_STATUS_DESC_0 to TX_STATUS_DESC_3 (0x10 - 0x1C)**:  
  These registers provide the status of transmissions for each descriptor. They contain information on whether the transmission was successful or if errors occurred.

- **TX_START_ADDR_0 to TX_START_ADDR_3 (0x20 - 0x2C)**:  
  These registers hold the start addresses of the transmit descriptors. They point to the memory locations where the data to be transmitted is stored.

### General Registers
- **RX_BUFFER_START_ADDR (0x30)**:  
  Holds the start address of the receive buffer where incoming packets are stored.

- **EARLY_RX_BYTE_CNT (0x34)**:  
  Tracks the number of bytes that have been received early in the RX buffer.

- **EARLY_RX_STATUS (0x36)**:  
  Provides status information about early packet reception, indicating whether the packet was received successfully, if there were errors, or if the buffer was overwritten.

- **COMMAND_REG (0x37)**:  
  A command register used to control the basic operations of the network card, such as starting or stopping the receiver and transmitter.

- **PACKET_READ_ADDR (0x38)**:  
  Tracks the current read address of the packet being processed by the driver.

- **BUFFER_ADDR (0x3A)**:  
  Holds the current buffer address used by the hardware to track the total number of bytes received.

- **INTERRUPT_MASK_REG (0x3C)**:  
  Enables or disables specific interrupts on the network card.

- **INTERRUPT_STATUS_REG (0x3E)**:  
  Displays the status of interrupts, helping the driver identify which events have occurred.

- **TX_CONFIG_REG (0x40)**:  
  Configures various transmission parameters, including interframe gap time and loopback mode.

- **RX_CONFIG_REG (0x44)**:  
  Configures reception parameters, such as buffer size and early receive threshold.

- **TIMER_COUNT_REG (0x48)**:  
  A general-purpose timer used for various timing operations on the network card.

- **MISSED_PKT_COUNTER (0x4C)**:  
  Counts the number of packets missed due to RX FIFO overflow.

- **EEPROM_CONTROL_REG (0x50)**:  
  Controls EEPROM operations, including reading, writing, and programming.

- **CONFIG_REG_0 (0x51)**:  
  Used for configuration settings related to network card operations.

- **CONFIG_REG_1 (0x52)**:  
  Another configuration register, often used for power management and advanced settings.

- **TIMER_INTERRUPT_REG (0x54)**:  
  Sets the interval for timer-based interrupts.

- **MEDIA_STATUS_REG (0x58)**:  
  Provides information about the media status, including link status and speed.

- **CONFIG_REG_3 (0x59)**:  
  Used for additional configuration settings, often related to power management and wake-on-LAN.

- **CONFIG_REG_4 (0x5A)**:  
  Similar to CONFIG_REG_3, this register is used for various configuration tasks, including advanced features.

- **MULTI_INT_SELECT (0x5C)**:  
  Allows selection of which interrupts are active when multiple interrupt conditions are met.

- **PCI_REVISION_ID (0x5E)**:  
  Stores the PCI revision ID, identifying the specific version of the network card.

- **TX_STATUS_ALL_DESC (0x60)**:  
  Provides the status for all transmit descriptors.

### PHY Registers
- **BASIC_MODE_CTRL_REG (0x62)**:  
  Controls the basic operation mode of the PHY, such as setting speed and duplex.

- **BASIC_MODE_STATUS_REG (0x64)**:  
  Displays the status of the PHY’s basic operation, including link status and speed.

- **AUTO_NEG_ADVERT_REG (0x66)**:  
  Contains the capabilities of the network card advertised during auto-negotiation.

- **AUTO_NEG_LINK_PARTNER (0x68)**:  
  Shows the capabilities of the link partner during auto-negotiation.

- **AUTO_NEG_EXPANSION (0x6A)**:  
  Provides additional information about the auto-negotiation process.

- **DISCONNECT_COUNTER (0x6C)**:  
  Counts the number of times the link has been disconnected.

- **FALSE_CARRIER_COUNTER (0x6E)**:  
  Tracks false carrier events, indicating potential physical layer issues.

- **NWAY_TEST_REG (0x70)**:  
  Used for testing the N-Way auto-negotiation process.

- **RX_ERROR_COUNTER (0x72)**:  
  Counts the number of errors detected during packet reception.

- **CARRIER_SENSE_CONFIG (0x74)**:  
  Configures the carrier sense functionality, determining how the network card detects network activity before transmitting.

- **PHY_PARAM_1 (0x78)**:  
  Used for configuring specific PHY parameters.

- **TWISTER_PARAM (0x7C)**:  
  Configures twister parameters, which are related to the signal processing in the PHY.

- **PHY_PARAM_2 (0x80)**:  
  Another register for configuring PHY-specific parameters.

### Power Management Registers
- **PM_CRC_0 to PM_CRC_7 (0x84 - 0x8B)**:  
  These registers store CRC values used in power management, particularly for wake-up frames.

- **WAKEUP_FRAME_0 to WAKEUP_FRAME_7 (0x8C - 0xC4)**:  
  These registers store the wake-up frames, which allow the network card to wake up from a low-power state when specific packets are received.

- **PM_LSB_CRC_0 to PM_LSB_CRC_7 (0xCC - 0xD3)**:  
  Store the least significant byte of the CRC for each wake-up frame, used in power management.

- **CONFIG_REG_5 (0xD8)**:  
  A configuration register used for various power management settings, including wake-up conditions and FIFO testing.
