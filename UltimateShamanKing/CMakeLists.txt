cmake_minimum_required(VERSION 3.6)
project(Ultimate_Shaman_King)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp stdafx.cpp stdafx.h constant.cpp constant.h TmxLevel.cpp TmxLevel.h GameView.cpp GameView.h GameScene.cpp GameScene.h Units/Player.cpp Units/Player.h lib/tinyxml2/tinyxml2.cpp lib/tinyxml2/tinyxml2.h Units/Unit.cpp Units/Unit.h Units/Enemy.cpp Units/Enemy.h Snowball.cpp Snowball.h Screens/GameOverView.cpp Screens/GameOverView.h Screens/MenuView.cpp Screens/MenuView.h Random.h Screens/MenuBackground.cpp Screens/MenuBackground.h Screens/Menu.cpp Screens/Menu.h Units/Beloved.cpp Units/Beloved.h Units/Villain.cpp Units/Villain.h Units/VillainSpirit.cpp Units/VillainSpirit.h Fire.cpp Fire.h Dialog.cpp Dialog.h Replica.cpp Replica.h Line.cpp Line.h SkillPanel.cpp SkillPanel.h Skill.cpp Skill.h Shield.cpp Shield.h)
add_executable(Ultimate_Shaman_King ${SOURCE_FILES})

# enable warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set_target_properties(Ultimate_Shaman_King PROPERTIES COMPILE_FLAGS "-Weverything")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set_target_properties(Ultimate_Shaman_King PROPERTIES COMPILE_FLAGS "-Wall -Wextra")
endif()

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

include(cotire)
set_target_properties(Ultimate_Shaman_King PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.h")
cotire(Ultimate_Shaman_King)