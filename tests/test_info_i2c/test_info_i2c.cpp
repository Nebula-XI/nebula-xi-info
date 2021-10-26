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

#ifndef CONFIG_FILE_PATH
#define CONFIG_FILE_PATH "units_tree_config.json"
#endif

using namespace nebulaxi;

CTEST_DATA(nebula_xi_info)
{
    info_i2c_parser* i2c_parser {};
};

CTEST_SETUP(nebula_xi_info)
{
    std::ifstream units_config_file(CONFIG_FILE_PATH);
    std::stringstream units_config {};
    units_config << units_config_file.rdbuf();
    data->i2c_parser = new info_i2c_parser { units_config.str() };
};

CTEST_TEARDOWN(nebula_xi_info)
{
    if (data->i2c_parser) {
        delete data->i2c_parser;
        data->i2c_parser = nullptr;
    }
}

CTEST2(nebula_xi_info, i2c_axi)
{
    auto i2c_parser = *static_cast<info_i2c_parser*>(data->i2c_parser);
    for (const auto& info : i2c_parser.get_info<info_i2c_parser::axi_parser>()) {
        print_info(info);
        // TODO: add test
    }
}

CTEST2(nebula_xi_info, i2c_mux)
{
    auto i2c_parser = *static_cast<info_i2c_parser*>(data->i2c_parser);
    for (const auto& info : i2c_parser.get_info<info_i2c_parser::mux_parser>()) {
        print_info(info);
        // TODO: add test
    }
}

CTEST2(nebula_xi_info, i2c_dev)
{
    auto i2c_parser = *static_cast<info_i2c_parser*>(data->i2c_parser);
    for (const auto& info : i2c_parser.get_info<info_i2c_parser::dev_parser>()) {
        print_info(info);
        // TODO: add test
    }
}

int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}
