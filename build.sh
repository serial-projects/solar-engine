#!/bin/bash
exec_cc(){
    echo "[::] - $1"
    $1
}

exec_cc "/usr/bin/g++ $(find -name *.cpp | grep src) -o ./bin/Solar -g -O2 -pipe -lSDL2 -lGLEW -lglm -lGL -lm -I./include/"