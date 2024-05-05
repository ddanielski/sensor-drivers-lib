#ifndef SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_INTERFACE_H
#define SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_INTERFACE_H

#include <array>

#include "driver_interface.hpp"
#include "hardware_driver.hpp"

namespace drivers {
class esp_internal_temp_sensor_interface : public drivers_abstraction::driver_interface
{
public:
    explicit esp_internal_temp_sensor_interface(drivers_abstraction::hardware_driver* driver);
    ~esp_internal_temp_sensor_interface() override;

    esp_internal_temp_sensor_interface(const esp_internal_temp_sensor_interface&)            = delete;
    esp_internal_temp_sensor_interface& operator=(const esp_internal_temp_sensor_interface&) = delete;
    esp_internal_temp_sensor_interface(esp_internal_temp_sensor_interface&&)                 = delete;
    esp_internal_temp_sensor_interface& operator=(esp_internal_temp_sensor_interface&&)      = delete;

    uint32_t                      get_data(drivers_abstraction::sensor_data* data) override;
    [[nodiscard]] const uint32_t* get_characteristic() const override
    {
        return characteristic_id.data();
    }
    [[nodiscard]] uint32_t get_num_characteristics() const override
    {
        return characteristic_id_count;
    }

private:
    uint32_t                characteristic_id_count;
    std::array<uint32_t, 1> characteristic_id {};
};
} // namespace drivers

#endif // SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_INTERFACE_H
