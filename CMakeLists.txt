cmake_minimum_required(VERSION 3.14)
project(userver-demo CXX)

find_package(userver COMPONENTS core REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} userver::core)
