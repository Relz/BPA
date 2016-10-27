cmake_minimum_required(VERSION 3.6)
project(SfmlAnimation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp constant.cpp constant.h stdafx.cpp stdafx.h)
add_executable(SfmlAnimation ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SfmlAnimation ${SFML_LIBRARIES})
endif()