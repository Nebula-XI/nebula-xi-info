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

#include "info_i2c.h"

namespace nebulaxi {

class info_i2c_units_tree : public info_units_tree {
    static constexpr auto k_i2c { "i2c" };
    static constexpr auto k_segments_num { "segsnum" };
    static constexpr auto k_segment { "seg" };
    static constexpr auto k_address { "addr" };
    static constexpr auto k_frequency { "freq" };

public:
    using info_units_tree::info_units_tree;
    constexpr auto unit_name() const { return k_i2c; }
    auto get_segments_num_optional() const { return m_units_tree.get_optional<uint32_t>(k_segments_num); }
    auto get_segments_num() const { return m_units_tree.get<uint32_t>(k_segments_num); }
    auto get_segment() const { return m_units_tree.get<uint32_t>(k_segment); }
    auto get_address() const { return std::strtol(m_units_tree.get<std::string>(k_address).c_str(), nullptr, 16); }
    auto get_frequency() const { return m_units_tree.get<double>(k_frequency); }
};

}
