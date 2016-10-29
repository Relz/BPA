cmake_minimum_required(VERSION 3.6)
project(Lines)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp gameField.cpp gameField.h randomTool.cpp randomTool.h handleEvents.cpp handleEvents.h initialize.cpp initialize.h)
add_executable(Lines ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Lines ${SFML_LIBRARIES})
endif()