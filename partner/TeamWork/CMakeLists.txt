cmake_minimum_required(VERSION 2.8)
project(TeamWork)

set(CMAKE_CXX_STANDARD 11)

add_executable(TeamWork main.cpp Examination.cpp Calculator.cpp)

#添加头文件搜索路径
#include_directories(/usr/include/muduo)

##添加库文件搜索路径
#link_directories(/usr/local/lib)



#
##添加头文件搜索路径
#include_directories(/usr/include/boost)
#
##添加库文件搜索路径
#link_directories(/usr/local/boost)
set(CMAKE_EXE_LINKER_FLAGS "-static")
#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

