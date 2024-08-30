// Hardware Registers

#define BIT(n) (1U << (n))

// ID Registers (Unicast filter)
enum UNICAST_FILTER_REG {
    UNICAST_REG_0 = 0x00, // Unicast filter ID Register 0
    UNICAST_REG_1,        // Unicast filter ID Register 1
    UNICAST_REG_2,        // Unicast filter ID Register 2
    UNICAST_REG_3,        // Unicast filter ID Register 3
    UNICAST_REG_4,        // Unicast filter ID Register 4
    UNICAST_REG_5         // Unicast filter ID Register 5
};

// Multicast Registers
enum MULTICAST_FILTER_REG {
    MULTICAST_REG_0 = 0x08, // Multicast filter Register 0
    MULTICAST_REG_1,        // Multicast filter Register 1
    MULTICAST_REG_2,        // Multicast filter Register 2
    MULTICAST_REG_3,        // Multicast filter Register 3
    MULTICAST_REG_4,        // Multicast filter Register 4
    MULTICAST_REG_5,        // Multicast filter Register 5
    MULTICAST_REG_6,        // Multicast filter Register 6
    MULTICAST_REG_7         // Multicast filter Register 7
};

// Transmit Status and Address Descriptor Registers
enum TX_STATUS_ADDR_REG {
    TX_STATUS_DESC_0 = 0x10, // Transmit status of descriptor 0
    TX_STATUS_DESC_1 = 0x14, // Transmit status of descriptor 1
    TX_STATUS_DESC_2 = 0x18, // Transmit status of descriptor 2
    TX_STATUS_DESC_3 = 0x1c, // Transmit status of descriptor 3
    TX_START_ADDR_0  = 0x20, // Transmit start address of descriptor 0
    TX_START_ADDR_1  = 0x24, // Transmit start address of descriptor 1
    TX_START_ADDR_2  = 0x28, // Transmit start address of descriptor 2
    TX_START_ADDR_3  = 0x2c  // Transmit start address of descriptor 3
};

// General Registers
enum GENERAL_REG {
    RX_BUFFER_START_ADDR = 0x30, // Start address of the RX buffer
    EARLY_RX_BYTE_CNT    = 0x34, // Early RX byte count
    EARLY_RX_STATUS      = 0x36, // Early RX status
    COMMAND_REG          = 0x37, // Command register
    PACKET_READ_ADDR     = 0x38, // Current address of packet read
    BUFFER_ADDR          = 0x3a, // Current buffer address
    INTERRUPT_MASK_REG   = 0x3c, // Interrupt mask register
    INTERRUPT_STATUS_REG = 0x3e, // Interrupt status register
    TX_CONFIG_REG        = 0x40, // TX configuration register
    RX_CONFIG_REG        = 0x44, // RX configuration register
    TIMER_COUNT_REG      = 0x48, // Timer count register
    MISSED_PKT_COUNTER   = 0x4c, // Missed packet counter
    EEPROM_CONTROL_REG   = 0x50, // EEPROM control register
    CONFIG_REG_0         = 0x51, // Configuration register 0
    CONFIG_REG_1         = 0x52, // Configuration register 1
    TIMER_INTERRUPT_REG  = 0x54, // Timer interrupt register
    MEDIA_STATUS_REG     = 0x58, // Media status register
    CONFIG_REG_3         = 0x59, // Configuration register 3
    CONFIG_REG_4         = 0x5a, // Configuration register 4
    MULTI_INT_SELECT     = 0x5c, // Multiple interrupt select
    PCI_REVISION_ID      = 0x5e, // PCI revision ID
    TX_STATUS_ALL_DESC   = 0x60  // Transmit status of all descriptors
};

// PHY Registers
enum PHY_REG {
    BASIC_MODE_CTRL_REG   = 0x62, // Basic mode control register
    BASIC_MODE_STATUS_REG = 0x64, // Basic mode status register
    AUTO_NEG_ADVERT_REG   = 0x66, // Auto-negotiation advertisement register
    AUTO_NEG_LINK_PARTNER = 0x68, // Auto-negotiation link partner register
    AUTO_NEG_EXPANSION    = 0x6a, // Auto-negotiation expansion register
    DISCONNECT_COUNTER    = 0x6c, // Disconnect counter
    FALSE_CARRIER_COUNTER = 0x6e, // False carrier sense counter
    NWAY_TEST_REG         = 0x70, // N-Way test register
    RX_ERROR_COUNTER      = 0x72, // RX error counter
    CARRIER_SENSE_CONFIG  = 0x74, // Carrier sense configuration register
    PHY_PARAM_1           = 0x78, // PHY parameter 1
    TWISTER_PARAM         = 0x7c, // Twister parameter
    PHY_PARAM_2           = 0x80  // PHY parameter 2
};

// Power Management Registers
enum POWER_MGMT_REG {
    PM_CRC_0            = 0x84, // Power management CRC register 0
    PM_CRC_1,                   // Power management CRC register 1
    PM_CRC_2,                   // Power management CRC register 2
    PM_CRC_3,                   // Power management CRC register 3
    PM_CRC_4,                   // Power management CRC register 4
    PM_CRC_5,                   // Power management CRC register 5
    PM_CRC_6,                   // Power management CRC register 6
    PM_CRC_7,                   // Power management CRC register 7
    WAKEUP_FRAME_0       = 0x8c, // Power management wakeup frame 0
    WAKEUP_FRAME_1       = 0x94, // Power management wakeup frame 1
    WAKEUP_FRAME_2       = 0x9c, // Power management wakeup frame 2
    WAKEUP_FRAME_3       = 0xa4, // Power management wakeup frame 3
    WAKEUP_FRAME_4       = 0xac, // Power management wakeup frame 4
    WAKEUP_FRAME_5       = 0xb4, // Power management wakeup frame 5
    WAKEUP_FRAME_6       = 0xbc, // Power management wakeup frame 6
    WAKEUP_FRAME_7       = 0xc4, // Power management wakeup frame 7
    PM_LSB_CRC_0         = 0xcc, // LSB of the mask byte of wakeup frame 0
    PM_LSB_CRC_1,                // LSB of the mask byte of wakeup frame 1
    PM_LSB_CRC_2,                // LSB of the mask byte of wakeup frame 2
    PM_LSB_CRC_3,                // LSB of the mask byte of wakeup frame 3
    PM_LSB_CRC_4,                // LSB of the mask byte of wakeup frame 4
    PM_LSB_CRC_5,                // LSB of the mask byte of wakeup frame 5
    PM_LSB_CRC_6,                // LSB of the mask byte of wakeup frame 6
    PM_LSB_CRC_7,                // LSB of the mask byte of wakeup frame 7
    CONFIG_REG_5         = 0xd8  // Configuration register 5
};

// Transmit Status of Descriptor x Register
enum TX_STATUS_FLAGS {
    TX_GAP               = 0x04,  // Gap between transmit status descriptors
    TX_CARRIER_SENSE_LOST = (1 << 31), // Carrier sense lost during TX
    TX_ABORT             = (1 << 30), // TX aborted due to reaching retry limit
    TX_OUT_OF_WINDOW     = (1 << 29), // Out of window collision during TX
    TX_CDH_FAILED        = (1 << 28), // CD heart beat failure
    TX_COLLISION_COUNT   = (0xff << 24), // Collision count during TX
    TX_EARLY_THRESHOLD_SHIFT = 16, // Shift for early TX threshold
    TX_EARLY_THRESHOLD   = (0x3f << TX_EARLY_THRESHOLD_SHIFT), // Early TX threshold
    TX_OK                = (1 << 15), // TX completed successfully
    TX_UNDERRUN          = (1 << 14), // TX underrun occurred
    TX_DMA_OWNED         = (1 << 13), // DMA transfer completed
    TX_SIZE              = 0x1fff  // Size of Ethernet frame to send
};

// RX Status Register (in RX packet header)
enum RX_STATUS_FLAGS {
    RX_MULTICAST_ADDR    = (1 << 15), // Multicast address received
    RX_PHYS_ADDR_MATCH   = (1 << 14), // Physical address matched
    RX_BROADCAST_ADDR    = (1 << 13), // Broadcast address received
    RX_INVALID_SYMBOL    = (1 << 5),  // Invalid symbol error (100BASE-TX 5B/4B)
    RX_RUNT_PKT          = (1 << 4),  // Runt packet received (size < 64 bytes)
    RX_LONG_PKT          = (1 << 3),  // Long packet received (size > 4096 bytes)
    RX_CRC_ERR           = (1 << 2),  // CRC error detected
    RX_FRAME_ALIGN_ERR   = (1 << 1),  // Frame alignment error detected
    RX_OK                = (1 << 0)   // Receive completed successfully
};

// Early RX Status Register
enum EARLY_RX_STATUS_FLAGS {
    EARLY_RX_GOOD_PKT    = (1 << 3),  // Early RX good packet received
    EARLY_RX_BAD_PKT     = (1 << 2),  // Early RX bad packet received
    EARLY_RX_OVERWRITE   = (1 << 1),  // Early RX buffer overwrite occurred
    EARLY_RX_OK          = (1 << 0)   // Early RX completed successfully
};

// Command Register
enum COMMAND_FLAGS {
    CMD_RESET            = (1 << 4),  // Reset command
    CMD_RX_ENABLE        = (1 << 3),  // RX enable command
    CMD_TX_ENABLE        = (1 << 2),  // TX enable command
    CMD_BUFFER_EMPTY     = (1 << 0)   // Buffer empty flag
};

// Interrupt Register (Mask/Status)
enum INTERRUPT_FLAGS {
    INT_SYSTEM_ERROR     = (1 << 15), // System error on PCI bus
    INT_TIMEOUT          = (1 << 14), // Timeout interrupt
    INT_CABLE_LENGTH_CHANGE = (1 << 13), // Cable length changed after RX enabled
    INT_RX_FIFO_OVERFLOW = (1 << 6),  // RX FIFO overflow occurred
    INT_LINK_CHANGE_OR_RX_UNDERRUN = (1 << 5), // Link change or RX underrun detected
    INT_RX_BUFFER_OVERFLOW = (1 << 4), // RX buffer overflow occurred
    INT_TX_ERROR         = (1 << 3),  // TX error (TX underrun or TX abort)
    INT_TX_OK            = (1 << 2),  // TX completed successfully
    INT_RX_ERROR         = (1 << 1),  // RX error (CRC or frame alignment error)
    INT_RX_OK            = (1 << 0),  // RX completed successfully
    INT_TX_EVENTS        = INT_TX_OK | INT_TX_ERROR, // TX related interrupts
    INT_RX_EVENTS        = INT_RX_OK | INT_RX_ERROR | INT_RX_BUFFER_OVERFLOW | INT_RX_FIFO_OVERFLOW, // RX related interrupts
    INT_CLEAR_ALL        = 0xffff     // Clear all interrupt flags
};

// TX Configuration Register
enum TX_CONFIG_FLAGS {
    TX_HW_VERSION_MASK   = 0x7cc00000, // Mask to fetch hardware version ID
    TX_IFG_SHIFT         = 24,         // Interframe Gap Time shift
    TX_IFG_84            = (0 << TX_IFG_SHIFT), // 8.4 us interframe gap time
    TX_IFG_88            = (1 << TX_IFG_SHIFT), // 8.8 us interframe gap time
    TX_IFG_92            = (2 << TX_IFG_SHIFT), // 9.2 us interframe gap time
    TX_IFG_96            = (3 << TX_IFG_SHIFT), // 9.6 us interframe gap time (default)
    TX_LOOPBACK_SHIFT    = 17,         // Loopback mode shift
    TX_LOOPBACK_DISABLE  = (0 << TX_LOOPBACK_SHIFT), // Disable loopback mode
    TX_LOOPBACK_ENABLE   = (3 << TX_LOOPBACK_SHIFT), // Enable loopback mode (packets not transmitted)
    TX_APPEND_CRC        = (1 << 16),  // Append CRC to end of frame
    TX_DMA_BURST_SHIFT   = 8,          // Max DMA burst size shift
    TX_DMA_BURST_16      = (0 << TX_DMA_BURST_SHIFT), // 16-byte burst size
    TX_DMA_BURST_32      = (1 << TX_DMA_BURST_SHIFT), // 32-byte burst size
    TX_DMA_BURST_64      = (2 << TX_DMA_BURST_SHIFT), // 64-byte burst size
    TX_DMA_BURST_128     = (3 << TX_DMA_BURST_SHIFT), // 128-byte burst size
    TX_DMA_BURST_256     = (4 << TX_DMA_BURST_SHIFT), // 256-byte burst size
    TX_DMA_BURST_512     = (5 << TX_DMA_BURST_SHIFT), // 512-byte burst size
    TX_DMA_BURST_1024    = (6 << TX_DMA_BURST_SHIFT), // 1024-byte burst size
    TX_DMA_BURST_2048    = (7 << TX_DMA_BURST_SHIFT)  // 2048-byte burst size
};

// RX Configuration Register
enum RX_CONFIG_FLAGS {
    RX_ERTH_SHIFT        = 24,         // Early RX Threshold shift
    RX_ERTH              = (0xf << RX_ERTH_SHIFT), // Early RX threshold multiplier
    RX_MULTIPLE_EARLY_INT = (1 << 17), // Enable multiple early interrupts
    RX_ERROR_PACKETS_8   = (1 << 16),  // Receive error packets (8 <= size < 64 bytes)
    RX_FIFO_THRESHOLD_SHIFT = 13,      // RX FIFO threshold shift
    RX_FIFO_THRESHOLD    = (7 << RX_FIFO_THRESHOLD_SHIFT), // RX FIFO threshold (transfer when whole packet is in FIFO)
    RX_BUFFER_LEN_SHIFT  = 11,         // RX buffer length shift
    RX_BUFFER_LEN_8K     = (0 << RX_BUFFER_LEN_SHIFT), // RX buffer length 8K
    RX_BUFFER_LEN_16K    = (1 << RX_BUFFER_LEN_SHIFT), // RX buffer length 16K
    RX_BUFFER_LEN_32K    = (2 << RX_BUFFER_LEN_SHIFT), // RX buffer length 32K
    RX_BUFFER_LEN_64K    = (3 << RX_BUFFER_LEN_SHIFT), // RX buffer length 64K
    RX_DMA_BURST_SHIFT   = 8,          // RX DMA burst size shift
    RX_DMA_BURST_16      = (0 << RX_DMA_BURST_SHIFT), // RX DMA burst size 16 bytes
    RX_DMA_BURST_32      = (1 << RX_DMA_BURST_SHIFT), // RX DMA burst size 32 bytes
    RX_DMA_BURST_64      = (2 << RX_DMA_BURST_SHIFT), // RX DMA burst size 64 bytes
    RX_DMA_BURST_128     = (3 << RX_DMA_BURST_SHIFT), // RX DMA burst size 128 bytes
    RX_DMA_BURST_256     = (4 << RX_DMA_BURST_SHIFT), // RX DMA burst size 256 bytes
    RX_DMA_BURST_512     = (5 << RX_DMA_BURST_SHIFT), // RX DMA burst size 512 bytes
    RX_DMA_BURST_1024    = (6 << RX_DMA_BURST_SHIFT), // RX DMA burst size 1024 bytes
    RX_DMA_BURST_NO_LIMIT = (7 << RX_DMA_BURST_SHIFT), // Unlimited RX DMA burst size
    RX_WRAP_MODE         = (1 << 7),  // Enable RX wrap mode
    RX_ACCEPT_ERROR_PKT  = (1 << 5),  // Accept error packets (CRC, align, collided)
    RX_ACCEPT_RUNT_PKT   = (1 << 4),  // Accept runt packets (size < 64 bytes but >= 8 bytes)
    RX_ACCEPT_BROADCAST  = (1 << 3),  // Accept broadcast packets
    RX_ACCEPT_MULTICAST  = (1 << 2),  // Accept multicast packets
    RX_ACCEPT_PHYS_MATCH = (1 << 1),  // Accept physical match packets
    RX_ACCEPT_ALL_PKT    = (1 << 0)   // Accept all packets (promiscuous mode)
};

// Hardware Version ID in TCR (chipset versions)
enum HW_VERSION_ID {
    HW_VER_RTL8139       = BIT(30) | BIT(29), // RTL8139 chipset version
    HW_VER_RTL8139A      = BIT(30) | BIT(29) | BIT(28), // RTL8139A chipset version
    HW_VER_RTL8139AG_C   = BIT(30) | BIT(29) | BIT(28) | BIT(26), // RTL8139AG_C chipset version
    HW_VER_RTL8139B_8130 = BIT(30) | BIT(29) | BIT(28) | BIT(27), // RTL8139B_8130 chipset version
    HW_VER_RTL8100       = BIT(30) | BIT(29) | BIT(28) | BIT(27) | BIT(23), // RTL8100 chipset version
    HW_VER_RTL8100B_8139D = BIT(30) | BIT(29) | BIT(28) | BIT(26) | BIT(22), // RTL8100B_8139D chipset version
    HW_VER_RTL8139CP     = BIT(30) | BIT(29) | BIT(28) | BIT(26) | BIT(23), // RTL8139CP chipset version
    HW_VER_RTL8101       = BIT(30) | BIT(29) | BIT(28) | BIT(26) | BIT(23) | BIT(22) // RTL8101 chipset version
};

// EEPROM Control Register
enum EEPROM_CTRL_FLAGS {
    EEPROM_CTRL_NORMAL    = 0x00, // EEPROM in normal mode (network/host communication)
    EEPROM_CTRL_AUTO_LOAD = 0x40, // Auto-load 93C46 EEPROM contents (returns to normal mode after 2ms)
    EEPROM_CTRL_PROGRAM   = 0x80, // EEPROM programming mode (EECS, EESK, EEDI, EEDO reflect EEPROM pins)
    EEPROM_CTRL_EECS      = 0x08, // EEPROM chip select
    EEPROM_CTRL_EESK      = 0x04, // EEPROM serial data clock
    EEPROM_CTRL_EEDI      = 0x02, // EEPROM serial data input
    EEPROM_CTRL_EEDO      = 0x01, // EEPROM serial data output
    EEPROM_CMD_READ       = 0x06, // Read data from EEPROM
    EEPROM_CMD_EWEN       = 0x04, // Enable write mode (must precede all programming modes)
    EEPROM_CMD_ERASE      = 0x07, // Erase EEPROM memory location
    EEPROM_CMD_WRITE      = 0x05, // Write to EEPROM memory location (after address: 16 bits of data)
    EEPROM_CMD_ERAL       = 0x04, // Erase all EEPROM memory locations
    EEPROM_CMD_WRAL       = 0x04, // Write to all EEPROM memory locations
    EEPROM_CMD_EWDS       = 0x04, // Disable all EEPROM programming instructions
    EEPROM_CMD_EWEN_ADDR  = 0x30, // EEPROM enable write address
    EEPROM_CMD_ERAL_ADDR  = 0x20, // EEPROM erase all address
    EEPROM_CMD_WRAL_ADDR  = 0x10, // EEPROM write all address
    EEPROM_CMD_EWDS_ADDR  = 0x00, // EEPROM disable write address
    EEPROM_ADDR_LEN       = 0x06, // EEPROM address length (after start bit and opcode)
    EEPROM_OPCODE_LEN     = 0x03, // EEPROM opcode length (with start bit included)
    EEPROM_CMD_READ_LEN   = EEPROM_OPCODE_LEN + EEPROM_ADDR_LEN, // EEPROM read command length
    EEPROM_DATA_MAC       = 0x07, // EEPROM data MAC address location
    EEPROM_CFG_WRITE_ENABLE = 0xc0 // Unlock write access to specific EEPROM registers
};

// Configuration Register 1
enum CONFIG_REG1_FLAGS {
    CONFIG1_LEDS_SHIFT = 6, // LEDs configuration shift
    CONFIG1_LEDS_TXRX_LNK100_LNK10 = (0 << CONFIG1_LEDS_SHIFT), // LEDs configuration: TX/RX, Link 100, Link 10
    CONFIG1_LEDS_TXRX_LNK_FDX      = (1 << CONFIG1_LEDS_SHIFT), // LEDs configuration: TX/RX, Link, Full-duplex
    CONFIG1_LEDS_TX_LNK_RX         = (2 << CONFIG1_LEDS_SHIFT), // LEDs configuration: TX, Link, RX
    CONFIG1_LEDS_TX_LNK100_LNK10   = (3 << CONFIG1_LEDS_SHIFT), // LEDs configuration: TX, Link 100, Link 10
    CONFIG1_LEDS_MASK              = CONFIG1_LEDS_TX_LNK100_LNK10 // LEDs mask configuration
};

// Media Status Register
enum MEDIA_STATUS_FLAGS {
    MEDIA_STATUS_TX_FLOW_CTRL_ENABLE = (1 << 7), // TX flow control enable
    MEDIA_STATUS_RX_FLOW_CTRL_ENABLE = (1 << 6), // RX flow control enable
    MEDIA_STATUS_AUX_POWER_PRESENT   = (1 << 4), // Auxiliary power present status
    MEDIA_STATUS_SPEED_10MBPS        = (1 << 3), // Speed status: 0 = 100Mbps, 1 = 10Mbps
    MEDIA_STATUS_LINK_BAD            = (1 << 2), // Link status: 0 = OK, 1 = fail
    MEDIA_STATUS_TX_PAUSE_FRAME      = (1 << 1), // TX pause frame status
    MEDIA_STATUS_RX_PAUSE_FRAME      = (1 << 0)  // RX pause frame status
};
