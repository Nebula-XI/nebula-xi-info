cmake_minimum_required(VERSION 3.19)

project(nebula_xi_info_test_i2c
	DESCRIPTION "Nebula-XI Info Test I2C"
)

add_executable(${PROJECT_NAME} test_info_i2c.cpp)
add_test("test_info_i2c" ${PROJECT_NAME})
