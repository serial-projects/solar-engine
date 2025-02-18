#!/bin/sh
copy_file(){
    cp -v ./App/App ../Engine-v1
}

# NOTE: check if CHOST has been defined.
if [[ -z "${CHOST}" ]]; then
    CHOST=$(which gcc)
fi

build_things(){
    
    # NOTE: This is a too aggresive solution ;-) 
    rm -v -r ./build/
    mkdir ./build
    
    # Run cmake from there.
    cd ./build
    cmake .. -G Ninja                                   \
        -DCMAKE_C_COMPILER=${CHOST}                     \
        -DCMAKE_BUILD_TYPE="Debug"                      \
        -DPROJECT_FORCE_COLORS=1                        \
        -DPROJECT_USE_ASAN=1
    ninja -v clean
    ninja -v -j$(nproc) && copy_file
}

# Entry point:
build_things