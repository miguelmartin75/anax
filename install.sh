#!/bin/bash

if [ $# -ge 2 ]; then
    CMAKE_PATH=$1
else
    CMAKE_PATH=build
fi

echo "using $CMAKE_PATH for cmake config"

if [ ! -d $CMAKE_PATH ]; then
    echo "${CMAKE_PATH} does not exist!"
    if [ $ARGC >= 1 ]; then
        echo "please ensure you did not mis-spell your directory path"
    else
        echo "you may provide one argument to the this script;"
        echo "the directory where the cmake files are generated"
    fi
fi


OLD_PATH=$PWD

pushd $CMAKE_PATH

BUILD_TYPES=(Debug Release)
ON_OFF=(ON OFF)

i=0
for buildType in $BUILD_TYPES
do
    for sharedLibs in $ON_OFF
    do
        INSTALL_HEADERS=OFF
        if [ i != 0 ]; then
            INSTALL_HEADERS=ON
        fi

        cmake $OLD_PATH -DCMAKE_BUILD_TYPE=$buildType -DBUILD_SHARED_LIBS=$sharedLibs -DINSTALL_HEADERS=OFF
        make install

        i=i+1
    done
done

popd
