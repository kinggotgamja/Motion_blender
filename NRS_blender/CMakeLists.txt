cmake_minimum_required(VERSION 3.10)
project(NRS_blender)

# C++17 표준 사용
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 소스 파일 및 헤더 파일 설정
set(SOURCE_FILES src/main.cpp src/Profiler.cpp)
set(HEADER_FILES src/Profiler.h)

# 실행 파일 생성
add_executable(NRSProfiler ${SOURCE_FILES} ${HEADER_FILES})

# include 디렉토리 추가
target_include_directories(NRSProfiler PRIVATE ${CMAKE_SOURCE_DIR})

# 컴파일 옵션 (필요에 따라 추가 가능)
target_compile_options(NRSProfiler PRIVATE -Wall -Wextra -O2)
