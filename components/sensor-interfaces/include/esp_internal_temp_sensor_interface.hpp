#ifndef SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_INTERFACE_H
#define SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_INTERFACE_H

#include <array>

#include "sensor_driver.hpp"
#include "sensor_interface.hpp"

namespace drivers {
class esp_internal_temp_sensor_interface : public sensor_abstraction::sensor_interface
{
public:
    explicit esp_internal_temp_sensor_interface(sensor_abstraction::sensor_driver* driver);
    ~esp_internal_temp_sensor_interface() override;

    esp_internal_temp_sensor_interface(const esp_internal_temp_sensor_interface&)            = delete;
    esp_internal_temp_sensor_interface& operator=(const esp_internal_temp_sensor_interface&) = delete;
    esp_internal_temp_sensor_interface(esp_internal_temp_sensor_interface&&)                 = delete;
    esp_internal_temp_sensor_interface& operator=(esp_internal_temp_sensor_interface&&)      = delete;

    uint32_t                      get_data(sensor_abstraction::sensor_data* data) override;
    [[nodiscard]] const uint32_t* get_characteristic() const override
    {
        return characteristic_id.data();
    }
    [[nodiscard]] uint32_t get_num_characteristics() const override
    {
        return characteristic_id_count;
    }

private:
    uint32_t                                            characteristic_id_count;
    std::array<sensor_abstraction::CharacteristicId, 1> characteristic_id {};
};
} // namespace drivers

#endif // SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_INTERFACE_H
