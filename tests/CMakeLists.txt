cmake_minimum_required(VERSION 3.19)

project(nebula-xi-info-tests)

set(PROJECT_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/ctest/)

add_subdirectory(test_info_gpio)
add_subdirectory(test_info_i2c)
add_subdirectory(test_info_sdram)
add_subdirectory(test_info_spi)
