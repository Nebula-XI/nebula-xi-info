cmake_minimum_required(VERSION 3.19)

project(nebula_xi_info_tests
	DESCRIPTION "Nebula-XI Info Tests"
)

enable_testing()

add_subdirectory(test_info_gpio)
add_subdirectory(test_info_i2c)
add_subdirectory(test_info_sdram)
add_subdirectory(test_info_spi)
