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
class info_axi_i2c final : public info_axi_base {
public:
    using list_type = info_list<info_axi_i2c>;
    info_axi_i2c() = default;
    info_axi_i2c(const std::string_view& name, const std::string_view& driver, uint64_t axi_offset)
        : info_axi_base { name, driver, axi_offset }
    {
    }
};
class info_i2c_dev_base : public info_base {
    std::string m_label {};
    uint32_t m_address {};
    double m_frequency {};

public:
    info_i2c_dev_base() = default;
    info_i2c_dev_base(const std::string_view& name, const std::string_view& driver,
        const std::string_view& label, uint32_t address, double frequency, info_uid parent_uid)
        : info_base { name, driver, parent_uid }
        , m_label { label }
        , m_address { address }
        , m_frequency { frequency }
    {
    }
    auto& label() const noexcept { return m_label; }
    auto address() const noexcept { return m_address; }
    auto frequency() const noexcept { return m_frequency; }
};
class info_i2c_dev final : public info_i2c_dev_base {
    std::optional<uint32_t> m_channel {};
    std::optional<std::string> m_channel_name {};

public:
    using list_type = info_list<info_i2c_dev>;
    info_i2c_dev() = default;
    info_i2c_dev(const std::string_view& channel_name, uint32_t channel, const std::string_view& name, const std::string_view& driver,
        const std::string_view& label, uint32_t address, double frequency, info_uid parent_uid)
        : info_i2c_dev_base { name, driver, label, address, frequency, parent_uid }
        , m_channel { channel }
        , m_channel_name { channel_name }
    {
    }
    info_i2c_dev(const std::string_view& name, const std::string_view& driver,
        const std::string_view& label, uint32_t address, double frequency, info_uid parent_uid)
        : info_i2c_dev_base { name, driver, label, address, frequency, parent_uid }
    {
    }
    auto channel() const noexcept { return m_channel; }
    auto channel_name() const noexcept { return m_channel_name; }
};
class info_i2c_mux final : public info_i2c_dev_base {
public:
    using list_type = info_list<info_i2c_mux>;
    using channels_map = std::map<info_uid, uint32_t, std::less<uint32_t>>;
    info_i2c_mux() = default;
    info_i2c_mux(const std::string_view& name, const std::string_view& driver,
        const std::string_view& label, uint32_t address, double frequency, uint32_t channels, info_uid parent_uid)
        : info_i2c_dev_base { name, driver, label, address, frequency, parent_uid }
    {
        for (decltype(channels) channel {}; channel < channels; ++channel) {
            m_channels.emplace(make_info_uid {}(name, driver, std::to_string(channel)), channel);
        }
    }
    auto& channels() const noexcept { return m_channels; }

private:
    channels_map m_channels {};
};

}
