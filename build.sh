#!/bin/bash

mkdir build
cmake -S./ -B./build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang-14 -DCMAKE_CXX_COMPILER=clang++-14
cmake --build ./build
