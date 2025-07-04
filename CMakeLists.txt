cmake_minimum_required(VERSION 3.10)
project(metronome_engine)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:/libraries/SDL2")
set(SDL2_MIXER_PATH "C:/libraries/SDL2_mixer")

include_directories(${SDL2_PATH}/include)
include_directories(${SDL2_MIXER_PATH}/include)

link_directories(${SDL2_PATH}/lib)
link_directories(${SDL2_MIXER_PATH}/lib)

add_executable(metronome_engine main.cpp metronome.cpp)

target_link_libraries(metronome_engine SDL2 SDL2main SDL2_mixer)
