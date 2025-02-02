cmake_minimum_required(VERSION 3.12)
project(cielmalloc_benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose build type: Debug/Release/RelWithDebInfo/MinSizeRel." FORCE)
endif (NOT CMAKE_BUILD_TYPE)

set(FETCHCONTENT_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

include(FetchContent)

FetchContent_Declare(
    cielmalloc
    GIT_REPOSITORY https://github.com/namespaceciel/cielmalloc.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(cielmalloc)

FetchContent_Declare(
    ctz
    GIT_REPOSITORY https://github.com/namespaceciel/ctz.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(ctz)

add_executable(cielmalloc_benchmark
    src/main.cpp
)

target_link_libraries(cielmalloc_benchmark PUBLIC cielmalloc ctz)
