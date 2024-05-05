#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <esp_log.h>

#include "esp_internal_temp_sensor_driver.hpp"
#include "esp_internal_temp_sensor_interface.hpp"
#include "hardware_driver.hpp"

const constexpr char* TAG = "app_main";

extern "C" void
app_main()
{
    // create the driver and interface objects
    drivers::esp_internal_temp_sensor_driver    temp_sensor_driver;
    drivers::esp_internal_temp_sensor_interface temp_sensor_interface(&temp_sensor_driver);

    // Init the sensor data structure
    drivers_abstraction::sensor_data data = {};

    float temp = 0.0F;

    while (true)
    {
        temp_sensor_interface.get_data(&data);
        std::memcpy(&temp, &data.data, sizeof(temp));
        ESP_LOGI(TAG, "Internal temperature: %.2f°C", temp);
        vTaskDelay(1'000 / portTICK_PERIOD_MS);
    }
    ESP_LOGW(TAG, "Restarting now.");
    fflush(stdout);
    esp_restart();
}
