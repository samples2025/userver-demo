project(sample CXX)

cmake_minimum_required(VERSION 3.20)

find_package(userver REQUIRED COMPONENTS core)

set(APP_DIR ${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${APP_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${APP_DIR}/include)
target_link_libraries(${PROJECT_NAME} userver::core)
