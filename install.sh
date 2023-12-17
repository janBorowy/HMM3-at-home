#!/bin/bash

git clone -b SDL2 https://github.com/libsdl-org/SDL_image.git
git clone -b SDL2 https://github.com/libsdl-org/SDL_ttf.git
mkdir SDL_image/build
cd SDL_image/build
cmake -DCMAKE_INSTALL_PREFIX=../.. ..
make
make install
cd ../../SDL_ttf
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=../.. ..
make
make install
cd ../..