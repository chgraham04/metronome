cmake_minimum_required(VERSION 3.10)
project(metronome_engine)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

add_executable(metronome_engine main.cpp metronome.cpp)

target_link_libraries(metronome_engine ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
