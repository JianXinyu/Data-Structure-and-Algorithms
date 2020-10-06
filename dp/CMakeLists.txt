 cmake_minimum_required(VERSION 2.8)
 set(TARGET_NAME dp)

 add_library(${TARGET_NAME}
         STATIC
#         53Maximum-Subarray.cpp
#         121BestTimetoBuyandSellStock.cpp
#         #Unique path I: O(mn), S = O(mn), T = O(mn)
#         62UniquePaths.cpp
#         63UniquePaths2.cpp
#         64MinPathSum.cpp
#         120Triangle.cpp
#         174DungeonGame.cpp
#         931MinimumFallingPathSum.cpp
#         1210MinimumMoves2ReachTargetwithRotations.cpp
#         #Maximal rectangle I: O(mn), S = O(mn), T = O(mn)
#         221MaximalSquare.cpp
#         85MaximalRectangle.cpp
#         304RangeSumQuery2D-Immutable.cpp
#         1277CountSquareSubmatriceswithAllOnes.cpp
#
#         houseRobber.cpp
#         perfectSquares.cpp
         wordBreak.cpp
         )

 target_include_directories(${TARGET_NAME}
         PUBLIC
         ${CMAKE_SOURCE_DIR})