cmake_minimum_required(VERSION 3.2)
project(Effectrino)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    AudioMatrix/AudioMatrix.ino
    Core/Core.ino
    MatrixTester/MatrixTester.ino
    Module/module-config.json
    Module/Module.ino)

include_directories(.)
include_directories(./../libraries)
include_directories(./../hardware)
include_directories(AudioMatrix)
include_directories(Core)
include_directories(MatrixTester)
include_directories(Module)

add_executable(Effectrino ${SOURCE_FILES})