# Cmake version
cmake_minimum_required (VERSION 3.8)

# Name
project(Enigma)

# At least c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add sources to this project's executable.
file(GLOB_RECURSE sources src/*.cpp header/*.h)
add_executable (Enigma ${sources})

# static linking
target_link_libraries(Enigma PRIVATE -lm)

# library include
target_include_directories (Enigma PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/header/)

# Debug preprocessor definition
target_compile_definitions(Enigma PUBLIC "$<$<CONFIG:Debug>:_DEBUG>")
