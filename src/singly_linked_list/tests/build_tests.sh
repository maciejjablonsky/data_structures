#!/bin/bash

mkdir -p build
cd build
cmake ..
mkdir -p bin
make
mv test* bin