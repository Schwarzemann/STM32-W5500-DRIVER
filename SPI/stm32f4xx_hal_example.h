#pragma once

#include <cstdint>

// Mock structure for GPIO initialization settings
struct GPIO_InitTypeDef {
    uint32_t Pin;      /**< Specifies the GPIO pins to be configured */
    uint32_t Mode;     /**< Specifies the operating mode for the selected pins */
    uint32_t Pull;     /**< Specifies the Pull-up or Pull-down activation for the selected pins */
    uint32_t Speed;    /**< Specifies the speed for the selected pins */
    uint32_t Alternate;/**< Specifies the alternate function for the selected pins */
};

// Mock structure for SPI handle
struct SPI_HandleTypeDef {
    uint32_t Instance; /**< SPI Instance (e.g., SPI1, SPI2, etc.) */
    struct {
        uint32_t Mode;
        uint32_t Direction;
        uint32_t DataSize;
        uint32_t ClockPolarity;
        uint32_t ClockPhase;
        uint32_t NSS;
        uint32_t BaudRatePrescaler;
        uint32_t FirstBit;
        uint32_t TIMode;
        uint32_t CRCCalculation;
    } Init;
    uint32_t State; /**< SPI state (e.g., ready, busy, etc.) */
};

// SPI state definitions
#define HAL_SPI_STATE_READY 0

// Mock definitions for GPIO pins and modes
#define GPIO_PIN_13  (1U << 13)
#define GPIO_PIN_14  (1U << 14)
#define GPIO_PIN_15  (1U << 15)
#define GPIO_PIN_12  (1U << 12)

#define GPIO_MODE_AF_PP         0x01
#define GPIO_NOPULL             0x00
#define GPIO_PULLUP             0x01
#define GPIO_MODE_OUTPUT_PP     0x02
#define GPIO_SPEED_HIGH         0x03
#define GPIO_SPEED_LOW          0x00
#define GPIO_AF5_SPI2           0x05

// SPI mode definitions
#define SPI_MODE_MASTER         0x01
#define SPI_DIRECTION_2LINES    0x00
#define SPI_DATASIZE_8BIT       0x07
#define SPI_POLARITY_LOW        0x00
#define SPI_PHASE_1EDGE         0x01
#define SPI_NSS_SOFT            0x01
#define SPI_BAUDRATEPRESCALER_4 0x02
#define SPI_FIRSTBIT_MSB        0x00
#define SPI_TIMODE_DISABLED     0x00
#define SPI_CRCCALCULATION_DISABLED 0x00

// GPIO pin states
#define GPIO_PIN_RESET          0
#define GPIO_PIN_SET            1

// HAL_OK is used as a return value for successful operations
#define HAL_OK 0

// Mock SPI and GPIO Instances
struct SPI_TypeDef {};  // Define SPI_TypeDef as an empty struct
struct GPIO_TypeDef {}; // Define GPIO_TypeDef as an empty struct

#define SPI1 new SPI_TypeDef
#define SPI2 new SPI_TypeDef
#define SPI3 new SPI_TypeDef
#define GPIOA new GPIO_TypeDef
#define GPIOB new GPIO_TypeDef
#define GPIOC new GPIO_TypeDef

// Mock HAL delay function
inline void HAL_Delay(uint32_t milliseconds) {
    // Simulate delay in milliseconds
}

// Mock function to initialize GPIO pins
inline void HAL_GPIO_Init(GPIO_TypeDef* gpio_port, GPIO_InitTypeDef* gpio_init) {
    // Simulate GPIO initialization
}

// Mock function to set GPIO pin states
inline void HAL_GPIO_WritePin(GPIO_TypeDef* gpio_port, uint16_t pin, uint32_t pin_state) {
    // Simulate writing to GPIO pin
}

// Mock SPI Transmit function
inline int HAL_SPI_Transmit(SPI_HandleTypeDef* hspi, const uint8_t* data, uint16_t size, uint32_t timeout) {
    // Simulate SPI transmission
    return HAL_OK;
}

// Mock SPI Receive function
inline int HAL_SPI_Receive(SPI_HandleTypeDef* hspi, uint8_t* data, uint16_t size, uint32_t timeout) {
    // Simulate SPI reception
    return HAL_OK;
}

// Mock SPI Init function
inline int HAL_SPI_Init(SPI_HandleTypeDef* hspi) {
    // Simulate SPI initialization
    return HAL_OK;
}
