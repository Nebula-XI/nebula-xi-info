cmake_minimum_required(VERSION 3.19)

project(nebula_xi_info_i2c_test
	DESCRIPTION "Nebula-XI Info I2C Test"
)

add_executable(${PROJECT_NAME} test_info_i2c.cpp)
add_test("test_info_i2c" ${PROJECT_NAME})
