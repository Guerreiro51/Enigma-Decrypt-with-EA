# Cmake version
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

# Name
project(Enigma LANGUAGES CXX)

# At least c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# MatPlotLib cpp
add_library(matplotlib_cpp INTERFACE)
target_compile_features(matplotlib_cpp INTERFACE cxx_std_17)
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
target_link_libraries(matplotlib_cpp INTERFACE Python3::Python Python3::Module)
find_package(Python3 COMPONENTS NumPy)
if(Python3_NumPy_FOUND)
    target_link_libraries(matplotlib_cpp INTERFACE Python3::NumPy)
else()
    target_compile_definitions(matplotlib_cpp INTERFACE WITHOUT_NUMPY)
endif()
install(TARGETS matplotlib_cpp EXPORT install_targets)

# Add sources to this project's executable.
file(GLOB_RECURSE sources src/*.cpp header/*.h)
add_executable (Enigma ${sources})

# static linking
target_link_libraries(Enigma PRIVATE matplotlib_cpp -lm)

# library include
target_include_directories (Enigma PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/header/)

# Debug preprocessor definition
target_compile_definitions(Enigma PUBLIC "$<$<CONFIG:Debug>:_DEBUG>")

# Create necessary directories
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/!data)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/!plots)