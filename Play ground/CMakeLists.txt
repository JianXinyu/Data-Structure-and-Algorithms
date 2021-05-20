cmake_minimum_required(VERSION 2.8)
project(dsa CXX)

#add_subdirectory(dp)
add_subdirectory(divide_and_conquer)
add_subdirectory(sorting)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic -Werror)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        divide_and_conquer
        sorting)

target_link_libraries(${PROJECT_NAME}
        divide_and_conquer
        sorting)
