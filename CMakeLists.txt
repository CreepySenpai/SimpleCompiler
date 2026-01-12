cmake_minimum_required(VERSION 4.1.2)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_C_STANDARD 23)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(CreepyCompiler VERSION 0.1.0 LANGUAGES C CXX)

add_executable(CreepyCompiler main.cpp)

file(GLOB CREEPY_SRC ${CMAKE_SOURCE_DIR}/src/Creepy/*.cpp)
target_sources(CreepyCompiler PRIVATE ${CREEPY_SRC})

target_include_directories(CreepyCompiler PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_directories(CreepyCompiler PUBLIC ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(CreepyCompiler PUBLIC stdc++exp)

add_compile_definitions(CREEPY_ENABLE_LOGGER CREEPY_ENABLE_ASSERT)