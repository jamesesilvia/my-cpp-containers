project(building_skills)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{GMOCK_HOME}/include $ENV{GTEST_HOME}/include)
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GTEST_HOME}/mybuild)
add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

set(sources 
   main.cpp
   StackTest.cpp
   ListTest.cpp
   )
add_executable(test ${sources})
target_link_libraries(test pthread)
target_link_libraries(test gmock)
target_link_libraries(test gtest)
