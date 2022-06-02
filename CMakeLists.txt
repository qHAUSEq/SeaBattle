cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME SeaBattle)
project(${PROJECT_NAME})

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/external/lib/cmake/SFML")

file(GLOB ALL_REQUIRED_DLL "external/bin/*.dll")
file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} ${SCRF} src/Source.cpp src/TextField.cpp src/Func.cpp src/Header.h)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system sfml-network)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/Texture/exit.png 
${CMAKE_CURRENT_SOURCE_DIR}/res/Texture/GreenCross.png 
${CMAKE_CURRENT_SOURCE_DIR}/res/Texture/menu.png 
${CMAKE_CURRENT_SOURCE_DIR}/res/Texture/RedCross.png 
${CMAKE_CURRENT_SOURCE_DIR}/res/Texture/settings.png 
${CMAKE_CURRENT_SOURCE_DIR}/res/Texture/ship.png 
${CMAKE_CURRENT_SOURCE_DIR}/res/Texture/ship_left.png 
${CMAKE_CURRENT_SOURCE_DIR}/res/Texture/start.png
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Texture/)
  
  
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res/Music/music.ogg DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Music/)

file(COPY 	${CMAKE_CURRENT_SOURCE_DIR}/res/Font/Cavorting.otf
			${CMAKE_CURRENT_SOURCE_DIR}/res/Font/MoonlessSC-Regular.otf
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Font/)