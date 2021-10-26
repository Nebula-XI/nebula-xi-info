# nebula-xi-info

Units Tree Configuration (UTC) and Units Information Structures (UIS) for AXI Library

.. image:: https://img.shields.io/badge/License-LGPL%20v3-blue.svg
  :target: https://www.gnu.org/licenses/lgpl-3.0]

[![CMake](https://github.com/Nebula-XI/nebula-xi-info/actions/workflows/cmake.yml/badge.svg)](https://github.com/Nebula-XI/nebula-xi-info/actions/workflows/cmake.yml)

## Requirements

CMake 3.21, Ninja 1.10.2, Boost 1.75, GCC 10.3 (Linux Native Build) or MinGW Cross-Compiler 10.3 (Build for Windows on Linux)

## Configuring

### Linux Native x86_64

`cmake --preset linux-x64-release`

`cmake --preset linux-x64-debug`

### Windows on Linux x86_64

`cmake --preset windows-x64-release`

`cmake --preset windows-x64-debug`

## Building

### Linux Native x86_64

`cmake --build --preset linux-x64-release`

`cmake --build --preset linux-x64-release-rebuild`

`cmake --build --preset linux-x64-release-verbose`

`cmake --build --preset linux-x64-debug`

`cmake --build --preset linux-x64-debug-rebuild`

`cmake --build --preset linux-x64-debug-verbose`

### Windows on Linux x86_64

`cmake --build --preset windows-x64-release`

`cmake --build --preset windows-x64-release-rebuild`

`cmake --build --preset windows-x64-release-verbose`

`cmake --build --preset windows-x64-debug`

`cmake --build --preset windows-x64-debug-rebuild`

`cmake --build --preset windows-x64-debug-verbose`

## Testing

### Linux Native x86_64

`ctest --preset linux-x64-release`

`ctest --preset linux-x64-debug`

### Windows on Linux x86_64

`ctest --preset windows-x64-release`

`ctest --preset windows-x64-debug`

## All

### Linux

`./make sh config build test`

## JSON Configuration File

```json

{
    "id": "Nebula-XI",
    "name": "FMC126P",
    "version": "3.1",
    "units": [
        {
            "name": "RX DMA Switch",
            "driver": "AXI4-Stream Switch",
            "offset": "0x00010000"
        },
        {
            "name": "ATG",
            "driver": "AXI Traffic Generator",
            "offset": "0x00030000"
        },
        {
            "name": "I2C",
            "driver": "AXI IIC",
            "offset": "0x00020000",
            "units": [
                {
                    "name": "TCA9548A",
                    "driver": "TCA9548A",
                    "label": "D23",
                    "addr": "0x70",
                    "freq": "400000",
                    "channels": "8",
                    "units": [
                        {
                            "name": "FMC",
                            "channel": "0"
                        },
                        {
                            "name": "POWER",
                            "channel": "1",
                            "units": [
                                {
                                    "name": "INA219",
                                    "driver": "INA219",
                                    "label": "D33",
                                    "addr": "0x40",
                                    "freq": "400000",
                                    "additional": {}
                                },
                                {
                                    "name": "LTC2991",
                                    "driver": "LTC2991",
                                    "label": "D31",
                                    "addr": "0x90",
                                    "freq": "400000",
                                    "additional": {}
                                }
                            ]
                        },
                        {
                            "name": "EXAR",
                            "channel": "5",
                            "units": [
                                {
                                    "name": "XR77128",
                                    "driver": "XR77128",
                                    "label": "D32",
                                    "addr": "0x28",
                                    "freq": "400000"
                                }
                            ]
                        },
                        {
                            "name": "DDR4",
                            "channel": "6",
                            "units": [
                                {
                                    "name": "DDR4 SODIMM",
                                    "driver": "DDR4 SODIMM",
                                    "label": "XS1.1",
                                    "addr": "0x50",
                                    "freq": "400000"
                                }
                            ]
                        },
                        {
                            "name": "SWITCH CLOCK",
                            "channel": "7",
                            "units": [
                                {
                                    "name": "ADN4600",
                                    "driver": "ADN4600",
                                    "label": "D13",
                                    "addr": "0x48",
                                    "freq": "400000"
                                }
                            ]
                        }
                    ]
                }
            ]
        }
    ]
}


```

## Parsing Example

### Parsing I2C Configuration
```c
    std::ifstream units_config_file(NEBULAXI_CONFIG_FILE_PATH);
    std::stringstream units_config {};
    units_config << units_config_file.rdbuf();
    info_i2c_parser i2c_parser{ units_config.str() };
    auto i2c_axi_info = i2c_parser.get_info<info_i2c_parser::axi_parser>();
    auto i2c_mux_info = i2c_parser.get_info<info_i2c_parser::mux_parser>();
    auto i2c_dev_info = i2c_parser.get_info<info_i2c_parser::dev_parser>();
    ...
```

### Result of Parsing I2C Configuration
```bash
Configuration file: ./config/units_tree_config.json

------------------------------------
name: I2C
driver: AXI IIC
uid: 0x58875f695bf8ea28
parent uid: 0x0
offset: 0x20000

------------------------------------
name: TCA9548A
driver: TCA9548A
uid: 0x14c14faa34bf6cd7
parent uid: 0x58875f695bf8ea28
label: D23
channel uid[0]: 0xe7910cc3fda6b096
channel uid[1]: 0x488221bc24ee1e0c
channel uid[2]: 0x5c65022f03333b3d
channel uid[3]: 0x8c55022f6824b52f
channel uid[4]: 0xf37946dd0bc48ce3
channel uid[5]: 0x49ceaf6b9cd0de06
channel uid[6]: 0xa3783dd9104a6e54
channel uid[7]: 0xf6717f718861e01d

------------------------------------
name: INA219
driver: INA219
uid: 0x2391a47e188a84e5
parent uid: 0x488221bc24ee1e0c
label: D33
channel name: POWER
channel num: 1
address: 0x40
frequency: 400000

------------------------------------
name: LTC2991
driver: LTC2991
uid: 0x20ac9d698f6fc36e
parent uid: 0x488221bc24ee1e0c
label: D31
channel name: POWER
channel num: 1
address: 0x90
frequency: 400000

------------------------------------
name: XR77128
driver: XR77128
uid: 0xe5d3408984af77d4
parent uid: 0x49ceaf6b9cd0de06
label: D32
channel name: EXAR
channel num: 5
address: 0x28
frequency: 400000

------------------------------------
name: DDR4 SODIMM
driver: DDR4 SODIMM
uid: 0x611210280a1c4dfd
parent uid: 0xa3783dd9104a6e54
label: XS1.1
channel name: DDR4
channel num: 6
address: 0x50
frequency: 400000

------------------------------------
name: ADN4600
driver: ADN4600
uid: 0x4b0789abdde24d29
parent uid: 0xf6717f718861e01d
label: D13
channel name: SWITCH CLOCK
channel num: 7
address: 0x48
frequency: 400000

```
