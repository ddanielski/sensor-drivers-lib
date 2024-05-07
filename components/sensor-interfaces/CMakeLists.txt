list(APPEND srcs "src/esp_internal_temp_sensor_interface.cpp")

idf_component_register(SRCS "${srcs}" INCLUDE_DIRS "include" REQUIRES sensor-abstraction PRIV_REQUIRES sensor-drivers)