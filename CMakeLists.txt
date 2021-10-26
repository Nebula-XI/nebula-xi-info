#
# This file is part of InSys SDK
#
# Copyright (c) 1989-2021 Instrumental Systems, JSC (devlab@insys.ru)
#

cmake_minimum_required(VERSION 3.19)
project(nebula-xi-info)

set(PROJECT_COMPILE_OPTIONS)
set(PROJECT_COMPILE_DEFINES)
set(PROJECT_LINK_LIBRARIES)

set(PROJECT_INCLUDE_DIRS
    ${PROJECT_SOURCE_DIR}/include/info
    ${PROJECT_SOURCE_DIR}/include/parser
    ${PROJECT_SOURCE_DIR}/include/units_tree
)
set(PROJECT_INCLUDES )

add_library(${PROJECT_NAME} INTERFACE)

set(PROJECT_COMPILE_DEFINES ${PROJECT_COMPILE_DEFINES}
    NEBULAXI_CONFIG_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/config/units_tree_config.json" CACHE STRING ""
)

if(NEBULAXI_INFO_TEST_VERBOSE)
    set(PROJECT_COMPILE_DEFINES ${PROJECT_COMPILE_DEFINES} NEBULAXI_INFO_TEST_VERBOSE)
endif()

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} INTERFACE ${PROJECT_COMPILE_DEFINES})

if(NEBULAXI_INFO_BUILD_TEST)
    enable_testing()
    add_subdirectory(tests)
endif()
