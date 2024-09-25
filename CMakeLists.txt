CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

PROJECT(step-motor-test LANGUAGES CXX)

IF (WIN32)
	option(CMAKE_USE_WIN32_THREADS_INIT "using WIN32 threads" ON)
ENDIF ()

#################################
# GDB 设置
#################################
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

SET(SRC_LIST ${PROJECT_SOURCE_DIR}/src/main.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x")

IF (WIN32)
    MESSAGE(STATUS "Running on Windows")
ELSE()
    MESSAGE(STATUS "Not running on Windows")
    include_directories(${PROJECT_SOURCE_DIR}/src/include)
    link_directories(/usr/lib)
ENDIF()

message("PROJECT_NAME: ${PROJECT_NAME}")
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}/src")
message("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")
#################################
# 生成可执行文件
#################################
add_executable(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} 
					pthread)
