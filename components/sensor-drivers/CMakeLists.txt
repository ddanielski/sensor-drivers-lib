list(APPEND srcs "src/esp_internal_temp_sensor_driver.cpp")

idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "include" REQUIRES driver sensor-abstraction PRIV_REQUIRES)