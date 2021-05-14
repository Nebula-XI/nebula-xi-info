cmake_minimum_required(VERSION 3.19)

project(nebula_xi_info_sdram_test_
	DESCRIPTION "Nebula-XI Info SDRAM Test"
)

add_executable(${PROJECT_NAME} test_info_sdram.cpp)
add_test("test_info_sdram" ${PROJECT_NAME})
