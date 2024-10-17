#pragma once

#include <cstdint>
#include <chrono>
#include <iterator>
#include <type_traits>
#include <stm32f4xx_hal.h>

namespace platform
{
    // HAL-based delay function using milliseconds
    inline void delay(const std::chrono::milliseconds time) noexcept
    {
        HAL_Delay(static_cast<uint32_t>(time.count()));
    }
}

namespace eth
{
    // Concept definitions to check integral types and size conditions
    template <typename Type>
    concept IsIntegral = std::is_integral<Type>::value;

    template <typename Type, std::size_t MinimumSize>
    concept HasMinSize = (sizeof(Type) >= MinimumSize);

    template <typename Type, std::size_t Index>
    concept IsIndexValid = (Index < sizeof(Type));

    namespace spi
    {
        /**
         * @enum SPIInstance
         * @brief Enumerates available SPI peripherals.
         */
        enum class SPIInstance : uint8_t
        {
            Instance1 = 1,
            Instance2,
            Instance3
        };

        /**
         * @enum GPIOPort
         * @brief Enumerates available GPIO ports.
         */
        enum class GPIOPort : uint8_t
        {
            PortA = 'A',
            PortB = 'B',
            PortC = 'C'
        };

        /**
         * @struct GPIOConfiguration
         * @brief Encapsulates GPIO initialization parameters.
         */
        struct GPIOConfiguration
        {
            uint16_t Pins;          /**< GPIO pins to be initialized */
            uint32_t Mode;          /**< GPIO mode (e.g., GPIO_MODE_AF_PP) */
            uint32_t Pull;          /**< GPIO pull-up/pull-down configuration */
            uint32_t Speed;         /**< GPIO speed (e.g., GPIO_SPEED_HIGH) */
            uint32_t AlternateFunc; /**< GPIO alternate function mapping */
        };

        /**
         * @struct SPIConfiguration
         * @brief Encapsulates SPI initialization parameters.
         */
        struct SPIConfiguration
        {
            uint32_t Mode;                      /**< SPI mode (e.g., SPI_MODE_MASTER) */
            uint32_t Direction;                 /**< SPI direction (e.g., SPI_DIRECTION_2LINES) */
            uint32_t DataSize;                  /**< SPI data size (e.g., SPI_DATASIZE_8BIT) */
            uint32_t ClockPolarity;             /**< SPI clock polarity */
            uint32_t ClockPhase;                /**< SPI clock phase */
            uint32_t NSS;                       /**< SPI NSS management */
            uint32_t BaudRatePrescaler;         /**< SPI baud rate prescaler */
            uint32_t FirstBit;                  /**< SPI first bit (MSB/LSB) */
            uint32_t TIMode;                    /**< SPI TI mode */
            uint32_t CRCCalculation;            /**< SPI CRC calculation */
            uint32_t CRCLength;                 /**< SPI CRC length */
        };

        /**
         * @struct SPISettings
         * @brief Aggregates all configurations required to initialize an SPI peripheral.
         */
        struct SPISettings
        {
            SPIInstance spiPeripheral;          /**< Selected SPI peripheral instance */
            GPIOPort gpioPort;                  /**< GPIO port for SPI pins */
            GPIOConfiguration dataPinsConfig;   /**< GPIO configuration for data pins (MOSI, MISO, SCK) */
            GPIOConfiguration ssPinConfig;      /**< GPIO configuration for Slave Select (SS) pin */
            SPIConfiguration spiConfig;         /**< SPI peripheral configuration parameters */
        };

        /**
         * @namespace Configurations
         * @brief Contains predefined SPI configurations.
         */
        namespace Configurations {

            /**
             * @brief Predefined configuration for SPI2 on GPIO Port B.
             */
            inline constexpr SPISettings SPI2_Settings{
                SPIInstance::Instance2,
                GPIOPort::PortB,
                GPIOConfiguration{
                    GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, /**< Pins 13, 14, 15 */
                    GPIO_MODE_AF_PP,                           /**< Alternate Function Push-Pull */
                    GPIO_NOPULL,                               /**< No Pull-up/Pull-down */
                    GPIO_SPEED_HIGH,                           /**< High Speed */
                    GPIO_AF5_SPI2                              /**< Alternate Function 5 for SPI2 */
                },
                GPIOConfiguration{
                    GPIO_PIN_12,                               /**< Pin 12 for SS */
                    GPIO_MODE_OUTPUT_PP,                       /**< Output Push-Pull */
                    GPIO_PULLUP,                               /**< Pull-Up Enabled */
                    GPIO_SPEED_LOW,                            /**< Low Speed */
                    GPIO_AF5_SPI2                              /**< Alternate Function 5 for SPI2 */
                },
                SPIConfiguration{
                    SPI_MODE_MASTER,                           /**< Master Mode */
                    SPI_DIRECTION_2LINES,                      /**< 2-Line Direction */
                    SPI_DATASIZE_8BIT,                          /**< 8-Bit Data Size */
                    SPI_POLARITY_LOW,                           /**< Low Clock Polarity */
                    SPI_PHASE_1EDGE,                            /**< 1st Clock Phase */
                    SPI_NSS_SOFT,                               /**< Software NSS Management */
                    SPI_BAUDRATEPRESCALER_4,                    /**< Baud Rate Prescaler of 4 */
                    SPI_FIRSTBIT_MSB,                           /**< MSB First */
                    SPI_TIMODE_DISABLED,                        /**< TI Mode Disabled */
                    SPI_CRCCALCULATION_DISABLED,                /**< CRC Calculation Disabled */
                    0                                           /**< CRC Length (Not Used) */
                }
            };

        } // namespace Configurations
    } // namespace spi

    namespace byte
    {
        // Byte-related utility concepts and functions
        template <typename T>
        constexpr bool is_compatible_with_byte = std::is_convertible<std::remove_cv_t<T>, std::uint8_t>::value;

        template <typename Iterator>
        constexpr bool is_iterator_compatible_with_byte = is_compatible_with_byte<typename std::iterator_traits<Iterator>::value_type>;

        template <typename T>
        concept ByteConvertible = is_compatible_with_byte<T>;

        template <typename Iterator>
        concept ByteConvertibleIterator = is_iterator_compatible_with_byte<Iterator>;

        // Extracts a specific byte from an integral type based on position
        template <std::size_t Position, typename T>
        requires eth::IsIntegral<T> && eth::IsIndexValid<T, Position>
        inline constexpr std::uint8_t extract_byte_from(T value) noexcept
        {
            const std::size_t shift_bits = Position * 8;
            const std::uint8_t mask = 0xFF;
            return static_cast<std::uint8_t>((value >> shift_bits) & mask);
        }

        // Converts a single byte-compatible value to an integral type
        template <typename T, typename U>
        requires eth::IsIntegral<T> && ByteConvertible<U> && eth::HasMinSize<T, sizeof(std::uint8_t)>
        inline constexpr T convert_to(U value) noexcept
        {
            return static_cast<T>(value);
        }

        // Variadic template to convert multiple byte-compatible values to an integral type
        template <typename T, typename First, typename... Rest>
        requires eth::IsIntegral<T> && ByteConvertible<First> && eth::HasMinSize<T, (sizeof...(Rest) + sizeof(std::uint8_t))>
        inline constexpr T convert_to(First first_value, Rest... remaining_values) noexcept
        {
            const std::size_t shift_amount = sizeof...(remaining_values) * 8;
            return (static_cast<T>(first_value) << shift_amount) | convert_to<T>(remaining_values...);
        }
    } // namespace byte
} // namespace eth
