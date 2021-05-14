cmake_minimum_required(VERSION 3.19)

project(nebula_xi_info_test_spi
	DESCRIPTION "Nebula-XI Test SPI Info"
)

add_executable(${PROJECT_NAME} test_info_spi.cpp)
add_test("test_info_spi" ${PROJECT_NAME})
