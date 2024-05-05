#ifndef SENSOR_DRIVER_HARDWARE_DRIVER_H
#define SENSOR_DRIVER_HARDWARE_DRIVER_H

#include <cstdint>
#include <vector>

#include <esp_err.h>

namespace drivers_abstraction {

const constexpr uint32_t kNoAddress = 0;

class hardware_driver
{
public:
    hardware_driver()          = default;
    virtual ~hardware_driver() = default;

    hardware_driver(const hardware_driver&)            = delete;
    hardware_driver& operator=(const hardware_driver&) = delete;
    hardware_driver(hardware_driver&&)                 = delete;
    hardware_driver& operator=(hardware_driver&&)      = delete;

    virtual esp_err_t open()                                                                   = 0;
    virtual void      close()                                                                  = 0;
    virtual esp_err_t read(std::vector<char>& buffer, uint32_t address, uint32_t bytes)        = 0;
    virtual esp_err_t write(const std::vector<char>& buffer, uint32_t address, uint32_t bytes) = 0;
    virtual esp_err_t ioctl(int flag, void* value)                                             = 0;
};

} // namespace drivers_abstraction

#endif // SENSOR_DRIVER_HARDWARE_DRIVER_H
