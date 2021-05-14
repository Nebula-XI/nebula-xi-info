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

#include "info_base.h"

namespace nebulaxi {

class info_axi_i2c final : public info_axi_base {
    inline static constexpr auto k_unit { "axi-i2c" };

public:
    using list_type = info_list<info_axi_i2c>;
    info_axi_i2c()
        : info_axi_base { k_unit }
    {
    }
    info_axi_i2c(const std::string_view& name, const std::string_view& label, uint64_t axi_offset)
        : info_axi_base { name, label, axi_offset, k_unit }
    {
    }
};

class info_i2c_dev_base : public info_base {
    uint32_t m_address {};
    double m_frequency {};

public:
    info_i2c_dev_base(const std::string_view& unit)
        : info_base { unit }
        , m_address {}
        , m_frequency {}
    {
    }
    info_i2c_dev_base(const std::string_view& name, const std::string_view& label,
        uint32_t address, double frequency, info_uid parent_uid,
        const std::string_view& unit)
        : info_base { name, label, parent_uid, unit }
        , m_address { address }
        , m_frequency { frequency }
    {
    }
    auto address() const noexcept { return m_address; }
    auto frequency() const noexcept { return m_frequency; }
};

class info_i2c_dev final : public info_i2c_dev_base {
    inline static constexpr auto k_unit { "i2c-dev" };

public:
    using list_type = info_list<info_i2c_dev>;
    info_i2c_dev()
        : info_i2c_dev_base { k_unit }
    {
    }
    info_i2c_dev(const std::string_view& name, const std::string_view& label,
        uint32_t address, double frequency, info_uid parent_uid)
        : info_i2c_dev_base { name, label, address, frequency, parent_uid, k_unit }
    {
    }
};

class info_i2c_mux final : public info_i2c_dev_base {
    inline static constexpr auto k_unit { "i2c-mux" };

public:
    using list_type = info_list<info_i2c_mux>;
    using segments_map = std::map<info_uid, uint32_t, std::less<uint32_t>>;
    info_i2c_mux()
        : info_i2c_dev_base { k_unit }
        , m_segments {}
    {
    }
    info_i2c_mux(const std::string_view& name, const std::string_view& label,
        uint32_t address, double frequency, uint32_t ports,
        info_uid parent_uid)
        : info_i2c_dev_base { name, label, address, frequency, parent_uid, k_unit }
    {
        for (decltype(ports) port {}; port < ports; ++port) {
            m_segments.emplace(make_info_uid {}(name, label, std::to_string(port)),
                port);
        }
    }
    auto& segments() const noexcept { return m_segments; }

private:
    segments_map m_segments {};
};

}
