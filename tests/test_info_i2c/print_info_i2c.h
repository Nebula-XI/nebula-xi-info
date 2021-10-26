#pragma once

#include <iostream>

#include "info_i2c.h"

void print_info(const nebulaxi::info_base& info)
{
    std::cout << '\n' + std::string(36, '-') + '\n';
    std::cout << "name: " << info.name() << '\n';
    std::cout << "driver: " << info.driver() << '\n';
    std::cout << "uid: 0x" << std::hex << info.uid() << '\n';
    std::cout << "parent uid: 0x" << std::hex << info.parent_uid() << '\n';
}

void print_info(const nebulaxi::info_axi_base& info)
{
    print_info(static_cast<nebulaxi::info_base>(info));
    std::cout << "offset: 0x" << std::hex << info.axi_offset() << '\n';
}

void print_info(const nebulaxi::info_i2c_mux& info)
{
    print_info(static_cast<nebulaxi::info_i2c_dev_base>(info));
    std::cout << "label: " << info.label() << '\n';
    std::map<uint32_t, nebulaxi::info_uid> chahnels_map {};
    for (const auto& [uid, channel] : info.channels()) {
        chahnels_map.emplace(channel, uid);
    }
    for (const auto& [channel, uid] : chahnels_map) {
        std::cout << "channel uid[" << std::dec << channel << "]: 0x" << std::hex << uid << '\n';
    }
}

void print_info(const nebulaxi::info_i2c_dev& info)
{
    print_info(static_cast<nebulaxi::info_base>(info));
    std::cout << "label: " << info.label() << '\n';
    if (info.channel_name().has_value()) {
        std::cout << "channel name: " << info.channel_name().value() << '\n';
    }
    if (info.channel().has_value()) {
        std::cout << "channel num: " << info.channel().value() << '\n';
    }
    std::cout << "address: 0x" << std::hex << info.address() << '\n';
    std::cout << "frequency: " << std::dec << info.frequency() << '\n';
}
