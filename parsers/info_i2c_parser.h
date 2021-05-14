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
#include "info_i2c_units_tree.h"

namespace nebulaxi {

class info_axi_i2c_parser : public info_base_parser<info_list, info_axi_i2c> {
protected:
    void parser(const info_units_tree& units_tree) override
    {
        for (auto& units : units_tree) {
            auto units_tree = info_i2c_units_tree { std::move(units.second) };
            auto name = units_tree.get_name();
            auto label = units_tree.get_label();
            auto offset = units_tree.get_offset();
            if (name == units_tree.unit_name()) {
                m_info_list.emplace_back(name, label, offset);
            }
        }
    }
    void parser(const std::string_view& config) override { parser(info_i2c_units_tree { config }.get_units()); }

public:
    info_axi_i2c_parser() = default;
    info_axi_i2c_parser(const std::string_view& config) { parser(config); }
};

class info_i2c_mux_parser : public info_base_parser<info_list, info_i2c_mux> {
protected:
    void parser(const info_units_tree& units_tree) override
    {
        for (auto& units : units_tree) {
            auto units_tree = info_i2c_units_tree { std::move(units.second) };
            auto parent_name = units_tree.get_name();
            auto parent_label = units_tree.get_label();
            auto paren_offset = units_tree.get_offset();
            if (parent_name == units_tree.unit_name()) {
                auto i2c_tree = units_tree.get_units();
                for (auto& i2c : i2c_tree) {
                    auto i2c_tree = info_i2c_units_tree { std::move(i2c.second) };
                    auto segments_num = i2c_tree.get_segments_num_optional();
                    if (!segments_num.has_value()) {
                        continue;
                    }
                    auto name = i2c_tree.get_name();
                    auto label = i2c_tree.get_label();
                    auto addr = i2c_tree.get_address();
                    auto freq = i2c_tree.get_frequency();
                    m_info_list.emplace_back(name, label, addr, freq, segments_num.value(), make_info_uid {}(parent_name, parent_label));
                }
            }
        }
    }
    void parser(const std::string_view& config) override { parser(info_i2c_units_tree { config }.get_units()); }

public:
    info_i2c_mux_parser() = default;
    info_i2c_mux_parser(const std::string_view& config) { parser(config); }
};

class info_i2c_dev_parser : public info_base_parser<info_list, info_i2c_dev> {
protected:
    void parser(const info_units_tree& units_tree) override
    {
        for (auto& units : units_tree) {
            auto units_tree = info_i2c_units_tree { std::move(units.second) };
            auto parent_name = units_tree.get_name();
            auto parent_label = units_tree.get_label();
            auto paren_offset = units_tree.get_offset();
            if (parent_name == units_tree.unit_name()) {
                auto i2c_tree = units_tree.get_units();
                for (auto& i2c : i2c_tree) {
                    auto i2c_tree = info_i2c_units_tree { std::move(i2c.second) };
                    auto name = i2c_tree.get_name();
                    auto label = i2c_tree.get_label();
                    auto addr = i2c_tree.get_address();
                    auto freq = i2c_tree.get_frequency();
                    auto segments_num = i2c_tree.get_segments_num_optional();
                    if (segments_num.has_value()) {
                        auto i2c_subtree = i2c_tree.get_units();
                        for (auto& i2c_sub : i2c_subtree) {
                            auto i2c_sub_tree = info_i2c_units_tree { std::move(i2c_sub.second) };
                            // FIXME: нужна рекурсивность
                            auto child_name = i2c_sub_tree.get_name();
                            auto child_label = i2c_sub_tree.get_label();
                            auto child_addr = i2c_sub_tree.get_address();
                            auto child_freq = i2c_sub_tree.get_frequency();
                            auto segment = i2c_sub_tree.get_segment();
                            m_info_list.emplace_back(child_name, child_label, child_addr, child_freq, make_info_uid {}(name, label, std::to_string(segment)));
                        }
                    } else {
                        m_info_list.emplace_back(name, label, addr, freq, make_info_uid {}(parent_name, parent_label));
                    }
                }
            }
        }
    }
    void parser(const std::string_view& config) override { parser(info_i2c_units_tree { config }.get_units()); }

public:
    info_i2c_dev_parser() = default;
    info_i2c_dev_parser(const std::string_view& config) { parser(config); }
};

class info_i2c_parser final : public info_axi_i2c_parser, public info_i2c_dev_parser, public info_i2c_mux_parser {
public:
    using axi_parser = info_axi_i2c_parser;
    using dev_parser = info_i2c_dev_parser;
    using mux_parser = info_i2c_mux_parser;
    info_i2c_parser(const std::string_view& config) { parser(config); }
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
        auto units_tree = info_i2c_units_tree { config }.get_units();
        axi_parser::parser(units_tree);
        mux_parser::parser(units_tree);
        dev_parser::parser(units_tree);
    }
};

}
