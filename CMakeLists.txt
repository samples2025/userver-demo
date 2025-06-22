cmake_minimum_required(VERSION 3.14)

project(userver-http-client CXX)

find_package(userver COMPONENTS core REQUIRED)

add_executable(${PROJECT_NAME} "http-client.cpp")
target_link_libraries(${PROJECT_NAME} userver::core)
