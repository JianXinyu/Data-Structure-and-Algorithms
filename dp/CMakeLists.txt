 cmake_minimum_required(VERSION 2.8)
 set(TARGET_NAME dp)

 add_library(${TARGET_NAME}
         STATIC
         53Maximum-Subarray.cpp
         121BestTimetoBuyandSellStock.cpp
         62UniquePaths.cpp
         63UniquePaths2.cpp
         64MinPathSum.cpp
         120Triangle.cpp
         174DungeonGame.cpp)

 target_include_directories(${TARGET_NAME}
         PUBLIC
         ${CMAKE_SOURCE_DIR})