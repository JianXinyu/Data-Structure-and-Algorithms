cmake_minimum_required(VERSION 2.8)
project(LeetCode CXX)

add_subdirectory(dp)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic -Werror)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        dp)

target_link_libraries(${PROJECT_NAME}
        dp)
