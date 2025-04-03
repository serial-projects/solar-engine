#!/bin/sh

copy_file(){
    cd ..
    cp ./build/App/App ./Engine-v1 -v
}

# NOTE: check if CHOST has been defined.
if [[ -z "${CHOST}" ]]; then
    CHOST=$(which gcc)
fi

# In case you want to run on ninja?

run_ninja(){
    ninja -v clean
    ninja -v -j$(nproc) && copy_file
}

# Or just make?

run_make(){
    make clean
    make -j$(nproc) && copy_file
}


build_things(){
    
    # NOTE: This is a too aggresive solution ;-) 
    rm -v -r ./build/
    mkdir ./build
    
    # Run cmake from there.
    cd ./build
    cmake ..                                            \
        -DCMAKE_C_COMPILER=${CHOST}                     \
        -DCMAKE_BUILD_TYPE="Debug"                      \
        -DPROJECT_FORCE_COLORS=1                        \
        -DPROJECT_USE_ASAN=1                            \
        -G Ninja                                        \
        && run_ninja
}

# Entry point:
build_things