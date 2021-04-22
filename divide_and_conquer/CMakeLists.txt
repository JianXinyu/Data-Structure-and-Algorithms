 cmake_minimum_required(VERSION 2.8)
 set(TARGET_NAME divide_and_conquer)

 add_library(${TARGET_NAME}
         STATIC
         169MajorityElement.cpp
         )

 target_include_directories(${TARGET_NAME}
         PUBLIC
         ${CMAKE_SOURCE_DIR})