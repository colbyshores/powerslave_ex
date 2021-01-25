#!/bin/bash

mkdir -p lib
cd lib

echo "downloading libraries"
curl \
-L "http://www.angelcode.com/angelscript/sdk/files/angelscript_2.29.2.zip" \
-o angelscript.zip
curl \
-L "https://github.com/FFmpeg/FFmpeg/archive/n2.7.2.zip" \
-o ffmpeg.zip

echo "extracting sources"
unzip angelscript.zip -d angelscript
unzip ffmpeg.zip -d ffmpeg

echo "compiling shared"
cd angelscript/sdk/angelscript/projects/gnuc
CXX=clang make -j8
cd ../../../../../ffmpeg/FFmpeg-n2.7.2
./configure --disable-static --enable-shared
CXX=clang make -j8
