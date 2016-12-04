cmake_minimum_required(VERSION 3.6)
project(Ultimate_Shaman_King)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp stdafx.cpp stdafx.h constant.cpp constant.h handleEvents.cpp handleEvents.h Yoh.cpp Yoh.h Drawable.cpp Drawable.h)
add_executable(Ultimate_Shaman_King ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Ultimate_Shaman_King ${SFML_LIBRARIES})
endif()