cmake_minimum_required(VERSION 3.19)

project(nebula_xi_info_gpio_test
	DESCRIPTION "Nebula-XI Info GPIO Test"
)

add_executable(${PROJECT_NAME} test_info_gpio.cpp)
add_test("test_info_gpio" ${PROJECT_NAME})
