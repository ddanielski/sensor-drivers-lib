#include "esp_internal_temp_sensor_interface.hpp"

#include <cstring>
#include <esp_err.h>
#include <esp_log.h>
#include <vector>

#include "driver_interface.hpp"
#include "esp_internal_temp_sensor_config.hpp"
#include "esp_internal_temp_sensor_driver.hpp"
#include "sensors_characteristics.hpp"

const constexpr char* TAG = "esp_internal_temp_sensor_interface";

drivers::esp_internal_temp_sensor_interface::esp_internal_temp_sensor_interface(
    drivers_abstraction::hardware_driver* driver)
    : drivers_abstraction::driver_interface(driver)
    , characteristic_id_count(1)
{
    characteristic_id[0] = sensors_characteristics::kInternalTemperatureCharacteristicId;
}

drivers::esp_internal_temp_sensor_interface::~esp_internal_temp_sensor_interface()
{
    driver()->close();
}

uint32_t
drivers::esp_internal_temp_sensor_interface::get_data(drivers_abstraction::sensor_data* data)
{
    static bool driver_opened = false;
    esp_err_t   err           = ESP_OK;

    if (!driver_opened)
    {
        err = driver()->open();
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to open driver: %s", esp_err_to_name(err));
            return 0;
        }
        driver_opened = true;
    }

    std::vector<char> buffer(esp_internal_temp_sensor_data_size);

    auto* sensor_driver = static_cast<esp_internal_temp_sensor_driver*>(driver());
    err                 = sensor_driver->read(buffer, drivers_abstraction::kNoAddress, sizeof(float));
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to read data from driver");
        return 0;
    }

    data[0].characteristic_id = characteristic_id[0];

    if (buffer.size() >= sizeof(uint32_t))
    {
        uint32_t value = 0;
        std::memcpy(&value, buffer.data(), sizeof(value)); // Copy from vector
        data[0].data = value;
    }
    else
    {
        ESP_LOGE(TAG, "Insufficient data in read buffer"); // Handle error case
    }

    return characteristic_id_count;
}
