cmake_minimum_required(VERSION 3.30)
project(ProjetCO_IN)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")

set(wxWidgets_ROOT_DIR /usr/include/wx)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

execute_process(
        COMMAND wx-config --cxxflags
        OUTPUT_VARIABLE WX_CXX_FLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
        COMMAND wx-config --libs
        OUTPUT_VARIABLE WX_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(SOURCE_FILES main.cpp
        TeamsData.cpp
        TeamsData.hpp
        Frame.cpp
        Frame.hpp
        Window.cpp
        Window.h)

add_executable(ProjetCO_IN ${SOURCE_FILES})

target_compile_options(ProjetCO_IN PRIVATE ${WX_CXX_FLAGS})
target_link_libraries(ProjetCO_IN ${wxWidgets_LIBRARIES} ${WX_LIBS})