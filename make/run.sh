#!/bin/bash

cd "$(dirname "$0")"

LD_PRELOAD=./shared/libavcodec.so:\
./shared/libswresample.so:\
./shared/libavformat.so:\
./shared/libswscale.so:\
./shared/libavutil.so \
./powerslave_ex
