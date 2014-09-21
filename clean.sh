#!/bin/bash

if [ $# -ge 2 ]; then
    CMAKE_PATH=$1
else
    CMAKE_PATH=build
fi

rm -rf $CMAKE_PATH
mkdir -p $CMAKE_PATH
