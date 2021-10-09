#!/bin/bash

mkdir -p lib
cd lib

echo "compiling shared"
#cd angelscript/sdk/angelscript/projects/gnuc
cd angelscript/sdk/angelscript/projects/cmake/build_vita
CXX=arm-vita-eabi-g++ make -j8
cd ../../../../../../ffmpeg
./build_ffmpeg
#CXX=arm-vita-eabi-g++ make -j8
