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

namespace nebulaxi
{
    class info_axi_spi final : public info_axi_base
    {
    public:
        using list_type = info_list<info_axi_spi>;
        info_axi_spi() = default;
        info_axi_spi(const std::string_view &name, const std::string_view &label, uint64_t axi_offset)
            : info_axi_base{name, label, axi_offset} {}
    };
    class info_spi_dev_base : public info_base
    {
        uint32_t m_chip_select{};
        double m_frequency{};

    public:
        info_spi_dev_base() = default;
        info_spi_dev_base(const std::string_view &name, const std::string_view &label, uint32_t chip_select, double frequency, info_uid parent_uid)
            : info_base{name, label, parent_uid}, m_chip_select{chip_select}, m_frequency{frequency} {}
        auto chip_select() const noexcept { return m_chip_select; }
        auto frequency() const noexcept { return m_frequency; }
    };
    class info_spi_dev final : public info_spi_dev_base
    {
    public:
        using list_type = info_list<info_spi_dev>;
        info_spi_dev() = default;
        info_spi_dev(const std::string_view &name, const std::string_view &label, uint32_t chip_select, double frequency, info_uid parent_uid)
            : info_spi_dev_base{name, label, chip_select, frequency, parent_uid} {}
    };

}
