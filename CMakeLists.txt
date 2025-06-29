cmake_minimum_required(VERSION 3.15)
project(Metronome)

set(CMAKE_CXX_STANDARD 17)

# Add vcpkg toolchain file (adjust path if needed)
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
endif()

# Find SFML
find_package(SFML CONFIG REQUIRED COMPONENTS audio)

# Add your source files
add_executable(metronome metronome.cpp)

# Link SFML
target_link_libraries(metronome PRIVATE sfml-audio)
