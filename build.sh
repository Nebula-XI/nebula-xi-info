#!/bin/bash

build_presets=(linux-x64-release linux-x64-debug windows-x64-release windows-x64-debug)
test_presets=(linux-x64-release linux-x64-debug)

for arg in "$*"; do
    if [[ "$arg" == "config" ]]; then
        for i in ${build_presets[@]}; do
            echo "-- Configure $i"
            cmake --preset $i
        done
    elif [[ "$arg" == "build" ]]; then
        for i in ${build_presets[@]}; do
            echo "-- Build $i"
            cmake --build --preset $i
        done
    elif [[ "$arg" == "rebuild" ]]; then
        for i in ${build_presets[@]}; do
            echo "-- Rebuild $i"
            cmake --build --preset $i-rebuild
        done
    elif [[ "$arg" == "test" ]]; then
        for i in ${test_presets[@]}; do
            echo "-- Test $i"
            ctest --preset $i
        done
    else
        echo "Usage:"
        echo -e '\t' "config - Configure presets."
        echo -e '\t' "build - Build presets."
        echo -e '\t' "rebuild - Rebuild presets."
        echo -e '\t' "test - Test presets."
    fi
done
