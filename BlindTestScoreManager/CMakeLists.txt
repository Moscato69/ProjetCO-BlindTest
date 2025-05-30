cmake_minimum_required(VERSION 3.12)		# never set less 3.12 min version
project(btScoreManager)

# Build type is debug by default
# call cmake .. -DCMAKE_BUILD_TYPE=Release to change to relase
# call cmake .. -DCMAKE_BUILD_TYPE=Debug to revert to debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 23)  # We're using C++23 standard :)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

include_directories(include)

# Choose wich executable will be build : cmake --build . -t  


# First test app : cmake --build . -t testApp
add_executable(testApp 	src/testApp.cpp
                        src/Score.cpp
                        src/Team.cpp
                        src/ScoreManager.cpp)
                        
# First Manager app (mostly for testing) : cmake --build . -t ManagerApp                        
add_executable(ManagerApp 	  src/ManagerApp.cpp
                              src/Score.cpp
                              src/Team.cpp
                              src/ScoreManager.cpp
                              src/InputDevice.cpp
                              src/outputDevice.cpp)


                        




