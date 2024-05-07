#include "esp_internal_temp_sensor_driver.hpp"

#include <cstring>
#include <vector>

const constexpr int INT_TEMP_SENSOR_TEMP_MIN = -10;
const constexpr int INT_TEMP_SENSOR_TEMP_MAX = 80;

drivers::esp_internal_temp_sensor_driver::esp_internal_temp_sensor_driver()
{
    temperature_sensor_config_t temp_sensor
        = TEMPERATURE_SENSOR_CONFIG_DEFAULT(INT_TEMP_SENSOR_TEMP_MIN, INT_TEMP_SENSOR_TEMP_MAX);
    ESP_ERROR_CHECK(temperature_sensor_install(&temp_sensor, &esp_internal_temp_handle));
}

esp_err_t
drivers::esp_internal_temp_sensor_driver::open()
{
    return temperature_sensor_enable(esp_internal_temp_handle);
}

void
drivers::esp_internal_temp_sensor_driver::close()
{
    temperature_sensor_disable(esp_internal_temp_handle);
}

esp_err_t
drivers::esp_internal_temp_sensor_driver::read(char* buffer,
                                               sensor_abstraction::SensorAddress /*address*/,
                                               uint32_t bytes)
{
    // Ensure the buffer has enough space to store a float
    if (bytes < sizeof(float))
    {
        return ESP_ERR_INVALID_SIZE;
    }

    float tsens_out = 0.0F;
    ESP_ERROR_CHECK(temperature_sensor_get_celsius(esp_internal_temp_handle, &tsens_out));
    memcpy(buffer, &tsens_out, sizeof(float));

    return ESP_OK;
}

esp_err_t
drivers::esp_internal_temp_sensor_driver::write(const char* /*buffer*/,
                                                sensor_abstraction::SensorAddress /*address*/,
                                                uint32_t /*bytes*/)
{
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t
drivers::esp_internal_temp_sensor_driver::ioctl(int /*flag*/, void* /*value*/)
{
    return ESP_ERR_NOT_SUPPORTED;
}
