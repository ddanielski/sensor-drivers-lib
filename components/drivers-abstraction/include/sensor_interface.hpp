#ifndef SENSOR_DRIVER_SENSOR_INTERFACE_H
#define SENSOR_DRIVER_SENSOR_INTERFACE_H

#include <cstdint>

#include "sensor_driver.hpp"

namespace sensor_abstraction {

using CharacteristicId   = uint32_t;
using NumCharacteristics = uint32_t;
using SensorData         = uint32_t;

struct sensor_data
{
    CharacteristicId characteristic_id;
    SensorData       data;
};

class sensor_interface
{
public:
    explicit sensor_interface(sensor_driver* driver)
        : driver_(driver)
    {
    }

    virtual ~sensor_interface() = default;

    sensor_interface(const sensor_interface&)            = delete;
    sensor_interface& operator=(const sensor_interface&) = delete;
    sensor_interface(sensor_interface&&)                 = delete;
    sensor_interface& operator=(sensor_interface&&)      = delete;

    virtual uint32_t                      get_data(sensor_data* data)     = 0;
    [[nodiscard]] virtual const uint32_t* get_characteristic() const      = 0;
    [[nodiscard]] virtual uint32_t        get_num_characteristics() const = 0;

protected:
    sensor_driver* driver()
    {
        return driver_;
    }

private:
    sensor_driver* driver_;
};

} // namespace sensor_abstraction

#endif // SENSOR_DRIVER_SENSOR_INTERFACE_H
