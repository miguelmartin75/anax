#!/bin/bash
pushd build

# Debug Builds
# note: 
# only need to install headers once, and may as well do it whilst
# compiling/installing one binary
cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=ON -DINSTALL_HEADERS=ON
sudo make install

cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=OFF -DINSTALL_HEADERS=OFF
sudo make install

# Release Builds
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DINSTALL_HEADERS=OFF
sudo make install

cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DINSTALL_HEADERS=OFF
sudo make install

popd
