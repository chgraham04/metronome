cmake_minimum_required(VERSION 3.10)
project(metronome_engine)

set(CMAKE_CXX_STANDARD 17)

set(SDL2_PATH "C:/libraries/SDL2/x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "C:/libraries/SDL2_mixer/x86_64-w64-mingw32")

include_directories(${SDL2_PATH}/include/SDL2)
include_directories(${SDL2_MIXER_PATH}/include/SDL2)

link_directories(${SDL2_PATH}/lib)
link_directories(${SDL2_MIXER_PATH}/lib)

add_executable(metronome_engine main.cpp metronome.cpp)

target_link_libraries(metronome_engine
        ${SDL2_PATH}/lib/libSDL2.a
        ${SDL2_MIXER_PATH}/lib/libSDL2_mixer.a

        # Windows system libs for static SDL2
        setupapi
        imm32
        version
        winmm
        ole32
        oleaut32
        uuid
        cfgmgr32
        ws2_32
        shell32
)
