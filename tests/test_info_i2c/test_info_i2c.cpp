/*

MIT License

Copyright (c) 2021 Nebula-XI

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifdef __linux__
#define CTEST_SEGFAULT
#endif
#define CTEST_MAIN
#define CTEST_COLOR_OK
#include <ctest.h>

#include "info_i2c_parser.h"
#include "print_info_i2c.h"

#ifndef NEBULAXI_CONFIG_FILE_PATH
#define NEBULAXI_CONFIG_FILE_PATH "units_tree_config.json"
#endif

#ifndef NEBULAXI_INFO_TEST_VERBOSE
#define NEBULAXI_INFO_TEST_VERBOSE false
#endif

using namespace nebulaxi;
using namespace std::string_view_literals;

static constexpr bool g_verbose { NEBULAXI_INFO_TEST_VERBOSE };

CTEST_DATA(nebulaxi_info)
{
    info_i2c_parser* i2c_parser {};
};

CTEST_SETUP(nebulaxi_info)
{
    std::ifstream units_config_file(NEBULAXI_CONFIG_FILE_PATH);
    std::stringstream units_config {};
    units_config << units_config_file.rdbuf();
    data->i2c_parser = new info_i2c_parser { units_config.str() };
};

CTEST_TEARDOWN(nebulaxi_info)
{
    if (data->i2c_parser) {
        delete data->i2c_parser;
        data->i2c_parser = nullptr;
    }
}

CTEST2(nebulaxi_info, get_info)
{
    if (g_verbose) {
        std::cout << "\nConfig file: " << NEBULAXI_CONFIG_FILE_PATH << '\n';
    }
    auto i2c_parser = *static_cast<info_i2c_parser*>(data->i2c_parser);
    for (const auto& info : i2c_parser.get_info<info_i2c_parser::axi_parser>()) {
        if (g_verbose) {
            print_info(info);
        }
    }
    for (const auto& info : i2c_parser.get_info<info_i2c_parser::mux_parser>()) {
        if (g_verbose) {
            print_info(info);
        }
    }
    for (const auto& info : i2c_parser.get_info<info_i2c_parser::dev_parser>()) {
        if (g_verbose) {
            print_info(info);
        }
    }
}

CTEST2(nebulaxi_info, i2c_axi)
{
    auto i2c_parser = *static_cast<info_i2c_parser*>(data->i2c_parser);
    // TODO: add test
    auto i2c_axi_list = i2c_parser.find_by_driver<info_i2c_parser::axi_parser>("AXI IIC"sv);
    if (i2c_axi_list.empty()) {
        ASSERT_FAIL();
    }
    auto i2c_axi = i2c_axi_list.at(0);
    ASSERT_STR(i2c_axi.name().c_str(), "I2C");
    ASSERT_EQUAL(i2c_axi.axi_offset(), 0x00020000);
}

CTEST2(nebulaxi_info, i2c_mux)
{
    auto i2c_parser = *static_cast<info_i2c_parser*>(data->i2c_parser);
    // TODO: add test
    auto i2c_mux_list = i2c_parser.find_by_driver<info_i2c_parser::mux_parser>("TCA9548A"sv);
    if (i2c_mux_list.empty()) {
        ASSERT_FAIL();
    }
    auto i2c_mux = i2c_mux_list.at(0);
    ASSERT_STR(i2c_mux.name().c_str(), "TCA9548A");
    ASSERT_EQUAL(i2c_mux.channels().size(), 8);
    ASSERT_EQUAL(i2c_mux.uid(), 0x14c14faa34bf6cd7);
}

CTEST2(nebulaxi_info, i2c_dev)
{
    auto i2c_parser = *static_cast<info_i2c_parser*>(data->i2c_parser);
    // TODO: add test
    auto i2c_dev = i2c_parser.get_by_label<info_i2c_parser::dev_parser>("D33"sv);
    if (!i2c_dev.has_value()) {
        ASSERT_FAIL();
    }
    ASSERT_STR(i2c_dev->name().c_str(), "INA219");
}

int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}
