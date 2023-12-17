#!/bin/bash

mkdir extern/SDL_image/build
cd extern/SDL_image/build
cmake -DCMAKE_INSTALL_PREFIX=../../.. ..
make
make install
cd ../../SDL_ttf
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../../.. ..
make
make install
cd ../..