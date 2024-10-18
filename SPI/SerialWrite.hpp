#pragma once

#include "SerialConfiguration.hpp"
#include <cstdint>
#include <vector>  // Add the vector include to match the batchWrite declaration

namespace eth {
namespace spi {

    // Define SPI_HandleTypeDef here to avoid incomplete type
    struct SPI_HandleTypeDef {
        uint32_t Instance;  // Mock instance field
    };

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
        explicit SPIController(const SPIConfiguration& config);

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

        /**
         * @brief Writes multiple data values over SPI (batch write).
         * @param dataList A list of address-data pairs.
         */
        void batchWrite(const std::vector<std::pair<uint16_t, uint8_t>>& dataList);

        /**
         * @brief Checks if the SPI is ready for transmission.
         * @return True if ready, false otherwise.
         */
        bool isSPIReady() const;

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
        class SelectRAII {
        public:
            explicit SelectRAII(SPIController& controllerInstance);
            ~SelectRAII();
        private:
            SPIController& controller;
        };

        SPIHandle spiHandle_;
        SPIConfiguration spiConfig_;
    };

} // namespace spi
} // namespace eth
