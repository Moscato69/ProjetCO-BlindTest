cmake_minimum_required(VERSION 3.12)
project(PorjetCO)

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
        Window.cpp
        Window.h
        FrameGrid.cpp
        FrameGrid.hpp
        InputDeviceUDP.cpp
        InputDeviceUDP.hpp
        EndFrame.cpp
        EndFrame.hpp
        KeyboardWatcher.cpp
        KeyboardWatcher.hpp)

add_executable(ProjetCO_OUT ${SOURCE_FILES})

target_compile_options(ProjetCO_OUT PRIVATE ${WX_CXX_FLAGS})
target_link_libraries(ProjetCO_OUT ${wxWidgets_LIBRARIES} ${WX_LIBS} X11)