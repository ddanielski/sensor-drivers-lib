#ifndef SENSOR_DRIVERS_SENSOR_READING_H
#define SENSOR_DRIVERS_SENSOR_READING_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

#include <array>
#include <cstdint>
#include <list>

#include "freertos/idf_additions.h"
#include <esp_err.h>
#include <esp_log.h>

#include "portmacro.h"
#include "sensor_interface.hpp"

namespace drivers {

const constexpr char*      TAG     = "sensor_reading";
const constexpr BaseType_t core_id = 1;

template<sensor_abstraction::NumCharacteristics max_num_characteristics>
class sensor_reading
{

public:
    using reading_callback = void (*)(sensor_abstraction::sensor_data*, sensor_abstraction::NumCharacteristics);

    explicit sensor_reading(UBaseType_t task_priority)
        : task_priority_(task_priority)
    {
    }

    ~sensor_reading()
    {
        stop();
    }

    sensor_reading(const sensor_reading& other)            = delete;
    sensor_reading& operator=(const sensor_reading& other) = delete;
    sensor_reading(sensor_reading&& other)                 = delete;
    sensor_reading& operator=(sensor_reading&& other)      = delete;

    bool register_sensor(sensor_abstraction::sensor_interface* sensor_interface)
    {
        if (sensor_interface == nullptr)
        {
            return false;
        }

        if (num_characteristics_ + sensor_interface->get_num_characteristics() > max_num_characteristics)
        {
            return false;
        }

        sensor_registry_.push_back(sensor_interface);
        num_characteristics_ += sensor_interface->get_num_characteristics();
        return true;
    }

    void set_poll_time(uint32_t seconds)
    {
        polling_rate_s = seconds;
    }

    void register_callback(reading_callback callback)
    {
        reading_callback_ = callback;
    }

    void start()
    {
        if (polling_rate_s > 0)
        {
            xTaskCreatePinnedToCore(
                &poll_values_task, "sensor_reading_task", 3'072, this, task_priority_, &task_handle_, core_id);
        }

        if (task_handle_ == nullptr)
        {
            ESP_LOGE(TAG, "Failed to create task");
        }
    }

    void stop()
    {
        if (task_handle_ == nullptr)
        {
            return;
        }

        polling_rate_s = 0;
        vTaskDelete(task_handle_);
        task_handle_ = nullptr;
    }

    void get_data()
    {
        num_data_ = 0;
        for (auto* sensor : sensor_registry_)
        {
            num_data_ += sensor->get_data(&data_buffer_[num_data_]);
        }

        if (reading_callback_)
        {
            reading_callback_(data_buffer_.data(), num_data_);
        }
    }

    void poll_values()
    {
        while (task_handle_ != nullptr)
        {
            vTaskDelay(polling_rate_s * 1'000 / portTICK_PERIOD_MS);
            if (polling_rate_s > 0)
            {
                // new reading
                get_data();
            }
        }
    }

private:
    static void poll_values_task(void* param)
    {
        auto* self = static_cast<sensor_reading*>(param);
        self->poll_values();
    }

    UBaseType_t                                                          task_priority_ {};
    TaskHandle_t                                                         task_handle_ {};
    uint32_t                                                             polling_rate_s {};
    reading_callback                                                     reading_callback_ {};
    sensor_abstraction::NumCharacteristics                               num_characteristics_ {};
    sensor_abstraction::NumCharacteristics                               num_data_ {};
    std::array<sensor_abstraction::sensor_data, max_num_characteristics> data_buffer_ {};
    std::list<sensor_abstraction::sensor_interface*>                     sensor_registry_;
};

} // namespace drivers

#endif // SENSOR_DRIVERS_SENSOR_READING_H
