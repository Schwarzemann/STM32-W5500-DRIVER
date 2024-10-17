#pragma once

#include "SPI/SerialConfiguration.h"
#include <cstdint>

namespace eth {
namespace spi {

    // Forward declaration of SPI_HandleTypeDef to avoid direct dependency
    struct SPI_HandleTypeDef;

    /**
     * @class SPIController
     * @brief Manages SPI communication operations.
     */
    class SPIController
    {
    public:
        using SPIHandle = SPI_HandleTypeDef;

        /**
         * @brief Constructs an SPIController with the given configuration.
         * @param config The SPI configuration settings.
         */
        explicit SPIController(const SpiConfiguration& config);

        // Disable copy constructor
        SPIController(const SPIController&) = delete;

        /**
         * @brief Sends data to a specific SPI address.
         * @param address The target address for the data.
         * @param data The data byte to send.
         */
        void sendData(uint16_t address, uint8_t data);

        /**
         * @brief Retrieves data from a specific SPI address.
         * @param address The target address to read from.
         * @return The received data byte.
         */
        uint8_t receiveData(uint16_t address);

        /**
         * @brief Provides access to the underlying SPI handle.
         * @return Reference to the SPI handle.
         */
        SPIHandle& getHandle() noexcept;

        // Disable copy assignment
        SPIController& operator=(const SPIController&) = delete;

    private:
        /**
         * @enum GPIOState
         * @brief Represents the state of the GPIO pin for Slave Select.
         */
        enum class GPIOState : uint8_t
        {
            High,
            Low
        };

        /**
         * @brief Controls the Slave Select pin state.
         * @param state The desired state of the pin.
         */
        void controlSlaveSelect(GPIOState state);

        // RAII class for managing Slave Select pin
        class SlaveSelectGuard;

        SPIHandle spiHandle_{};
        SpiConfiguration spiConfig_;
    };

} // namespace spi
} // namespace eth
