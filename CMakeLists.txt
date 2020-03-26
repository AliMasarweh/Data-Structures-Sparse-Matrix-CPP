cmake_minimum_required(VERSION 3.15)
project(SparseMatrix)

set(CMAKE_CXX_STANDARD 98)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
# find_package(Threads)

file(GLOB sources "./*.cpp")
file(GLOB headers "./*.h")

add_executable(TEST ${headers} ${sources})
target_link_libraries(TEST gtest gtest_main pthread)
# target_link_libraries(TEST ${CMAKE_THREAD_LIBS_INIT})
