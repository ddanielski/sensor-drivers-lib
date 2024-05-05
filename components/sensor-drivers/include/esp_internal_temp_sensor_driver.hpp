#ifndef SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_DRIVER_H
#define SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_DRIVER_H

#include <vector>

#include "hardware_driver.hpp"
#include <driver/temperature_sensor.h>

namespace drivers {

class esp_internal_temp_sensor_driver : public drivers_abstraction::hardware_driver
{
public:
    esp_internal_temp_sensor_driver();
    ~esp_internal_temp_sensor_driver() override = default;

    esp_internal_temp_sensor_driver(const esp_internal_temp_sensor_driver&)            = delete;
    esp_internal_temp_sensor_driver& operator=(const esp_internal_temp_sensor_driver&) = delete;
    esp_internal_temp_sensor_driver(esp_internal_temp_sensor_driver&&)                 = delete;
    esp_internal_temp_sensor_driver& operator=(esp_internal_temp_sensor_driver&&)      = delete;

    esp_err_t open() override;
    void      close() override;
    esp_err_t read(std::vector<char>& buffer, uint32_t address, uint32_t bytes) override;
    esp_err_t write(const std::vector<char>& buffer, uint32_t address, uint32_t bytes) override;
    esp_err_t ioctl(int flag, void* value) override;

private:
    temperature_sensor_handle_t esp_internal_temp_handle = nullptr;
};

} // namespace drivers

#endif // SENSOR_DRIVERS_ESP_INTERNAL_TEMP_SENSOR_DRIVER_H
