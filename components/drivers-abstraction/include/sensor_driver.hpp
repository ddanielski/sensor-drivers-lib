#ifndef SENSOR_DRIVER_SENSOR_DRIVER_H
#define SENSOR_DRIVER_SENSOR_DRIVER_H

#include <cstdint>

#include <esp_err.h>

namespace sensor_abstraction {

using SensorAddress = uint32_t;

const constexpr SensorAddress kNoAddress = 0;

class sensor_driver
{
public:
    sensor_driver()          = default;
    virtual ~sensor_driver() = default;

    sensor_driver(const sensor_driver&)            = delete;
    sensor_driver& operator=(const sensor_driver&) = delete;
    sensor_driver(sensor_driver&&)                 = delete;
    sensor_driver& operator=(sensor_driver&&)      = delete;

    virtual esp_err_t open()                                                           = 0;
    virtual void      close()                                                          = 0;
    virtual esp_err_t read(char* buffer, SensorAddress address, uint32_t bytes)        = 0;
    virtual esp_err_t write(const char* buffer, SensorAddress address, uint32_t bytes) = 0;
    virtual esp_err_t ioctl(int flag, void* value)                                     = 0;
};

} // namespace sensor_abstraction

#endif // SENSOR_DRIVER_SENSOR_DRIVER_H
