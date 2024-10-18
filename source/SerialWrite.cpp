#include "../SPI/SerialWrite.hpp"
#include <cstdint>
#include <array>
#include <limits>
#include <stdexcept>
#include <iostream> // For logging purposes

namespace eth {
namespace spi {

    // Internal Utilities Namespace
    namespace internal {

        // Operation identifiers for SPI communication
        enum class Operation : uint8_t {
            READ_OP  = 0x0F,
            WRITE_OP = 0xF0
        };

        // Function to construct SPI command packets
        template <Operation op, typename... Args>
        constexpr auto buildCommandPacket(uint16_t addr, Args... args) {
            std::array<uint8_t, 3 + sizeof...(Args)> packet = {
                static_cast<uint8_t>(op),
                Byte::get<1>(addr),
                Byte::get<0>(addr),
                static_cast<uint8_t>(args)...
            };
            return packet;
        }

        // Maximum allowable timeout value
        constexpr uint32_t MAX_TIMEOUT_DURATION = std::numeric_limits<uint32_t>::max();

        // SPI and GPIO hardware instances
        const std::array<SPI_TypeDef*, 3> SPI_HARDWARE = { SPI1, SPI2, SPI3 };
        const std::array<GPIO_TypeDef*, 3> GPIO_PORTS   = { GPIOA, GPIOB, GPIOC };
    }

    // RAII Wrapper for Slave Select Management
    class SPIController::SelectRAII {
    public:
        explicit SelectRAII(SPIController& controllerInstance)
            : controller(controllerInstance) {
            controller.controlSlaveSelect(GPIOState::Activate);
        }

        // Disable copy and move operations
        SelectRAII(const SelectRAII&) = delete;
        SelectRAII& operator=(const SelectRAII&) = delete;
        SelectRAII(SelectRAII&&) = delete;
        SelectRAII& operator=(SelectRAII&&) = delete;

        ~SelectRAII() {
            controller.controlSlaveSelect(GPIOState::Deactivate);
        }

    private:
        SPIController& controller;
    };

    // Constructor: Initializes SPI and GPIO configurations
    SPIController::SPIController(const SPISettings& spiSettings)
        : settings(spiSettings) {
        // Destructure the SPISettings structure for easier access
        auto [spiInstance, gpioPort, dataPinsConfig, ssPinConfig, spiConfig] = settings;

        // Validate SPI Instance
        size_t spiIndex = static_cast<size_t>(spiInstance) - 1; // Assuming SPIInstance starts at 1
        if (spiIndex >= internal::SPI_HARDWARE.size()) {
            throw std::out_of_range("Invalid SPI Instance selected.");
        }

        // Initialize GPIO for data pins (MOSI, MISO, SCK)
        GPIO_TypeDef* dataGPIOPort = internal::GPIO_PORTS[static_cast<size_t>(gpioPort)];
        HAL_GPIO_Init(dataGPIOPort, const_cast<GPIO_InitTypeDef*>(&dataPinsConfig));

        // Initialize GPIO for Slave Select (SS) pin
        HAL_GPIO_Init(dataGPIOPort, const_cast<GPIO_InitTypeDef*>(&ssPinConfig));

        // Setup SPI handle
        spiHandle.Instance = internal::SPI_HARDWARE[spiIndex];
        spiHandle.Init     = spiConfig;

        // Initialize SPI peripheral
        if (HAL_SPI_Init(&spiHandle) != HAL_OK) {
            throw std::runtime_error("Failed to initialize SPI peripheral.");
        }

        // Configure Slave Select pin as high initially (inactive state)
        controlSlaveSelect(GPIOState::Deactivate);

        // Optional: Enable SPI interrupt if required
        // HAL_NVIC_SetPriority(SPI1_IRQn, 5, 0);
        // HAL_NVIC_EnableIRQ(SPI1_IRQn);

        // Logging initialization success
        std::cout << "SPIController initialized successfully for SPI Instance "
                  << static_cast<int>(spiInstance) << "." << std::endl;
    }

    // Method to send data over SPI
    void SPIController::sendData(uint16_t address, uint8_t data) {
        auto commandPacket = internal::buildCommandPacket<internal::Operation::WRITE_OP>(address, data);

        // Manage Slave Select using RAII
        SelectRAII ssGuard(*this);

        // Transmit the packet
        if (HAL_SPI_Transmit(&spiHandle, commandPacket.data(),
                             static_cast<uint16_t>(commandPacket.size()),
                             internal::MAX_TIMEOUT_DURATION) != HAL_OK) {
            throw std::runtime_error("SPI Transmit failed during sendData.");
        }

        // Optional: Logging transmission success
        std::cout << "Data 0x" << std::hex << static_cast<int>(data)
                  << " sent to address 0x" << address << "." << std::endl;
    }

    // Method to receive data from SPI
    uint8_t SPIController::receiveData(uint16_t address) {
        auto commandPacket = internal::buildCommandPacket<internal::Operation::READ_OP>(address);

        // Manage Slave Select using RAII
        SelectRAII ssGuard(*this);

        // Transmit the read command
        if (HAL_SPI_Transmit(&spiHandle, commandPacket.data(),
                             static_cast<uint16_t>(commandPacket.size()),
                             internal::MAX_TIMEOUT_DURATION) != HAL_OK) {
            throw std::runtime_error("SPI Transmit failed during receiveData.");
        }

        // Prepare buffer to receive data
        uint8_t receivedByte = 0;
        if (HAL_SPI_Receive(&spiHandle, &receivedByte, sizeof(receivedByte),
                            internal::MAX_TIMEOUT_DURATION) != HAL_OK) {
            throw std::runtime_error("SPI Receive failed during receiveData.");
        }

        // Optional: Logging reception success
        std::cout << "Data 0x" << std::hex << static_cast<int>(receivedByte)
                  << " received from address 0x" << address << "." << std::endl;

        return receivedByte;
    }

    // Private method to control Slave Select pin state
    void SPIController::controlSlaveSelect(GPIOState state) {
        uint16_t pinState = (state == GPIOState::Activate) ? GPIO_PIN_RESET : GPIO_PIN_SET;
        auto [spiInstance, gpioPort, dataPinsConfig, ssPinConfig, spiConfig] = settings;

        GPIO_TypeDef* gpioPortPtr = internal::GPIO_PORTS[static_cast<size_t>(gpioPort)];
        uint16_t ssPin           = ssPinConfig.Pin;

        HAL_GPIO_WritePin(gpioPortPtr, ssPin, pinState);

        // Optional: Logging pin state change
        std::cout << "Slave Select pin set to "
                  << ((state == GPIOState::Activate) ? "LOW (Active)" : "HIGH (Inactive)") << "."
                  << std::endl;
    }

    // Accessor for the native SPI handle
    SPI_HandleTypeDef& SPIController::getSPIHandle() noexcept {
        return spiHandle;
    }

    // Additional Functionality: Batch Write Operation
    void SPIController::batchWrite(const std::vector<std::pair<uint16_t, uint8_t>>& dataList) {
        SelectRAII ssGuard(*this);

        for (const auto& [address, data] : dataList) {
            auto commandPacket = internal::buildCommandPacket<internal::Operation::WRITE_OP>(address, data);

            if (HAL_SPI_Transmit(&spiHandle, commandPacket.data(),
                                 static_cast<uint16_t>(commandPacket.size()),
                                 internal::MAX_TIMEOUT_DURATION) != HAL_OK) {
                throw std::runtime_error("SPI Transmit failed during batchWrite.");
            }

            // Optional: Logging each write operation
            std::cout << "Batch Write: Data 0x" << std::hex << static_cast<int>(data)
                      << " sent to address 0x" << address << "." << std::endl;
        }
    }

    // Additional Functionality: Check SPI Status
    bool SPIController::isSPIReady() const {
        // Example implementation; actual implementation may vary based on HAL specifics
        return (spiHandle.State == HAL_SPI_STATE_READY);
    }

} // namespace spi
} // namespace eth
