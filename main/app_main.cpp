#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "portmacro.h"
#include "sdkconfig.h"
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <esp_log.h>

#include "esp_internal_temp_sensor_driver.hpp"
#include "esp_internal_temp_sensor_interface.hpp"
#include "sensor_driver.hpp"
#include "sensor_interface.hpp"
#include "sensor_reading.hpp"
#include "sensors_characteristics.hpp"

const constexpr char* TAG = "app_main";

void
sensor_reading_cb(sensor_abstraction::sensor_data* data, sensor_abstraction::NumCharacteristics num_data)
{
    for (int i = 0; i < num_data; i++)
    {
        ESP_LOGI(TAG, "Characteristic ID: 0x%" PRIx32, data[i].characteristic_id);
        if (data[i].characteristic_id == sensors_characteristics::kInternalTemperatureCharacteristicId)
        {
            float temp = 0.0F;
            std::memcpy(&temp, &data[i].data, sizeof(temp));
            ESP_LOGI(TAG, "Reading: %.2f°C", temp);
        }
        else
        {
            ESP_LOGW(TAG, "Reading: %" PRIu32, data[i].data);
        }
    }
}

extern "C" void
app_main()
{
    // create the driver and interface objects
    drivers::esp_internal_temp_sensor_driver    temp_sensor_driver;
    drivers::esp_internal_temp_sensor_interface temp_sensor_interface(&temp_sensor_driver);

    // create the sensor reading object
    drivers::sensor_reading<1> sensor_reading(5);

    sensor_reading.set_poll_time(3);

    // register the sensor interface with the sensor reading object
    sensor_reading.register_sensor(&temp_sensor_interface);

    // Register the callback function
    sensor_reading.register_callback(sensor_reading_cb);

    // Start the sensor reading task
    sensor_reading.start();

    while (true)
    {
        vTaskDelay(portMAX_DELAY);
    }

    ESP_LOGW(TAG, "Restarting now.");
    fflush(stdout);
    esp_restart();
}
