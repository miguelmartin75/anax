#!/bin/bash
pushd build

# Debug Builds
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON
sudo make install

cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF
sudo make install

# Release Builds
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON
sudo make install

cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF
sudo make install

popd
