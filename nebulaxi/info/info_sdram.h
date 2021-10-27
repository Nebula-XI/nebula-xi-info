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

#pragma once

#include "nebulaxi/info/info_base.h"

namespace nebulaxi {
class info_axi_sdram final : public info_axi_base {
public:
    using list_type = info_list<info_axi_sdram>;
    info_axi_sdram() = default;
    info_axi_sdram(const std::string_view& name, const std::string_view& driver, uint64_t axi_offset)
        : info_axi_base { name, driver, axi_offset }
    {
    }
};
class info_sdram_dev_base : public info_base {
    info_sdram_dev_base() = default;
    info_sdram_dev_base(const std::string_view& name, const std::string_view& driver, info_uid parent_uid)
        : info_base { name, driver, parent_uid }
    {
    }
};

}
