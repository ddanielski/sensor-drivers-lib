#ifndef SENSOR_DRIVER_DRIVER_INTERFACE_H
#define SENSOR_DRIVER_DRIVER_INTERFACE_H

#include <cstdint>

#include "hardware_driver.hpp"

namespace drivers_abstraction {

struct sensor_data
{
    uint32_t characteristic_id;
    uint32_t data;
};

class driver_interface
{
public:
    explicit driver_interface(hardware_driver* driver)
        : driver_(driver)
    {
    }

    virtual ~driver_interface() = default;

    driver_interface(const driver_interface&)            = delete;
    driver_interface& operator=(const driver_interface&) = delete;
    driver_interface(driver_interface&&)                 = delete;
    driver_interface& operator=(driver_interface&&)      = delete;

    virtual uint32_t                      get_data(sensor_data* data)     = 0;
    [[nodiscard]] virtual const uint32_t* get_characteristic() const      = 0;
    [[nodiscard]] virtual uint32_t        get_num_characteristics() const = 0;

protected:
    hardware_driver* driver()
    {
        return driver_;
    }

private:
    hardware_driver* driver_;
};

} // namespace drivers_abstraction

#endif // SENSOR_DRIVER_DRIVER_INTERFACE_H
