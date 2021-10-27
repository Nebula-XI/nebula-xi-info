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

#include "nebulaxi/info/info_sdram.h"
#include "nebulaxi/units_tree/info_sdram_units_tree.h"

namespace nebulaxi {

class info_axi_sdram_parser : public info_base_parser<info_list, info_axi_sdram> {
protected:
    void parser(const info_units_tree& units_tree) override
    {
        // TODO: add configuration parser
    }
    void parser(const std::string_view& config) override { parser(info_sdram_units_tree { config }.get_units()); }

public:
    info_axi_sdram_parser() = default;
    info_axi_sdram_parser(const std::string_view& config) { parser(config); }
};

class info_sdram_parser final : public info_axi_sdram_parser {
public:
    using axi_parser = info_axi_sdram_parser;
    info_sdram_parser(const std::string_view& config) { parser(config); }
    template <typename parser>
    typename parser::list_type get_info() const { return parser::get_info(); }
    template <typename parser>
    typename parser::list_type find_by_name(const std::string_view& name) const { return parser::find_by_name(name); }
    template <typename parser>
    std::optional<typename parser::value_type> get_by_label(const std::string_view& label) const { return parser::get_by_label(label); }
    template <typename parser>
    std::optional<typename parser::value_type> get_by_uid(info_uid uid) const { return parser::get_by_uid(uid); }

private:
    void parser(const std::string_view& config) final
    {
        auto units_tree = info_sdram_units_tree { config }.get_units();
        axi_parser::parser(units_tree);
        // TODO: add configuration parser
    }
};
}
