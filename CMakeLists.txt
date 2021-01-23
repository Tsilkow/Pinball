cmake_minimum_required(VERSION 3.10)

project(Pinball VERSION 1.0)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

include_directories("inc")
set(SOURCES
	src/kulka.cpp
	src/odbijacz.cpp
	src/plansza.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_library(Modules SHARED ${SOURCES})

add_executable(Pinball main.cpp)
target_compile_options(Pinball PRIVATE -Wall)
target_link_libraries(Pinball sfml-graphics sfml-audio Modules)
