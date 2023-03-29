#!/bin/bash

CXX="clang++"
CXXFLAGS="-g -fcolor-diagnostics -fansi-escape-codes -Isrc/headers -F/Library/Frameworks -Wno-c++11-extensions -Wno-gnu-static-float-init"
LDFLAGS="-framework SDL2 -framework SDL2_image -framework SDL2_ttf"
SRC_DIR="src/source"
BIN_DIR="bin"
TARGET="${BIN_DIR}/rubyrun"

mkdir -p "${BIN_DIR}"
${CXX} ${CXXFLAGS} ${LDFLAGS} "${SRC_DIR}"/*.cpp -o "${TARGET}"
