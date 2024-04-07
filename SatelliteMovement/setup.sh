#!/bin/bash -e

BINDIR=./
CATCH2_REPO=https://github.com/catchorg/Catch2.git

git clone $CATCH2_REPO
cd Catch2
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$BINDIR ..
sudo make -j install
cd ..
sudo rm -rf ./.git
