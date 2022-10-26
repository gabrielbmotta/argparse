cmake_minimum_required(VERSION 3.0)
project(argparse)

set(CXX_STANDARD 11)

set(LIB_SOURCES
        argparse.h
        argparse.cpp
)

add_library(${PROJECT_NAME} ${LIB_SOURCES})

add_executable(${PROJECT_NAME}_testcpp test.cpp)
target_link_libraries(${PROJECT_NAME}_testcpp PUBLIC ${PROJECT_NAME})

add_executable(${PROJECT_NAME}_testc test.c)
target_link_libraries(${PROJECT_NAME}_testc PUBLIC ${PROJECT_NAME})