cmake_minimum_required(VERSION 3.6)
project(Ultimate_Shaman_King)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")

set(SOURCE_FILES main.cpp stdafx.cpp stdafx.h constant.cpp constant.h TmxLevel.cpp TmxLevel.h GameView.cpp GameView.h GameScene.cpp GameScene.h Player.cpp Player.h lib/tinyxml2/tinyxml2.cpp lib/tinyxml2/tinyxml2.h Unit.cpp Unit.h)
add_executable(Ultimate_Shaman_King ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(Boost REQUIRED)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(Ultimate_Shaman_King ${SFML_LIBRARIES})
	target_link_libraries(Ultimate_Shaman_King libtinyxml2.so)
endif()

include(${CMAKE_MODULE_PATH}/PVS-Studio.cmake)
pvs_studio_add_target(TARGET analyze ALL
		OUTPUT FORMAT errorfile
		PREPROCESSOR gcc
		ANALYZE Ultimate_Shaman_King
		CXX_FLAGS ${PREPROCESSOR_ADDITIONAL_FLAGS}
		C_FLAGS ${PREPROCESSOR_ADDITIONAL_FLAGS})