cmake_minimum_required(VERSION 3.16)

project(HW2 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g -O0 -Wextra -Wall -Wextra -Wpedantic -lgcov --coverage)
add_link_options( -O0 -lgcov --coverage)

# Статическая библиотека
set(STATIC_LIB_SOURCE_FILES staticVersion/src/kMeans.c)
set(STATIC_LIB_HEADERS_PATH staticVersion/headers)
add_library(static_version STATIC ${STATIC_LIB_SOURCE_FILES})
target_include_directories(static_version PUBLIC ${STATIC_LIB_HEADERS_PATH})

# Динамическая библиотека
set(DYNAMIC_LIB_SOURCE_FILES dynamicVersion/src/kMeans.c)
set(DYNAMIC_LIB_HEADERS_PATH dynamicVersion/headers)
add_library(dynamic_version SHARED ${DYNAMIC_LIB_SOURCE_FILES})
target_include_directories(dynamic_version PUBLIC ${DYNAMIC_LIB_HEADERS_PATH})

set(STATIC_MAIN_FILE staticVersion/src/main.c)
add_executable(hw2_static ${STATIC_MAIN_FILE})
target_link_libraries(hw2_static static_version m)

set(DYNAMIC_MAIN_FILE dynamicVersion/src/main.c)
add_executable(hw2_dynamic ${DYNAMIC_MAIN_FILE})
target_link_libraries(hw2_dynamic dynamic_version m pthread)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(static_test test/static_test.cpp)
target_link_libraries(static_test ${GTEST_LIBRARIES} static_version m pthread)

add_executable(dynamic_test test/dynamic_test.cpp)
target_link_libraries(dynamic_test ${GTEST_LIBRARIES} dynamic_version m pthread)

