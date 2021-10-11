#!/bin/bash

mkdir -p lib
cd lib

echo "compiling shared"
if [[ -z "$1" ]]; then
        cd angelscript/projects/gnuc
        make clean
	CXX=g++ make -j$(nproc)
	cd ../../../ffmpeg/FFmpeg-n2.7.2
        ./build_ffmpeg
	make -f Makefile clean
        #CXX=g++ make -f Makefile -j$(nproc)
else
	if [[ "$1" == "VITA" ]]; then
		cd angelscript/projects/cmake
		cmake .
	        make clean
		CXX=arm-vita-eabi-g++ make -j$(nproc)
		cd ../../../ffmpeg/FFmpeg-n2.7.2
                make clean
		cd ..
		./build_ffmpeg VITA
	fi
fi
#./build_ffmpeg
#CXX=arm-vita-eabi-g++ make -j8
