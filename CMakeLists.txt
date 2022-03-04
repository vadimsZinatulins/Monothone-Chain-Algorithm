cmake_minimum_required(VERSION 3.10)

project(MonothoneChain VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

find_package(SDL2 REQUIRED)

configure_file(${PROJECT_SOURCE_DIR}/config/config.h.in ${PROJECT_SOURCE_DIR}/include/config.h)

add_executable(
	${PROJECT_NAME}
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/Game.cpp
	${PROJECT_SOURCE_DIR}/src/KeyManager.cpp
	${PROJECT_SOURCE_DIR}/src/Time.cpp
	${PROJECT_SOURCE_DIR}/src/Cronometer.cpp
	${PROJECT_SOURCE_DIR}/src/Random.cpp
	${PROJECT_SOURCE_DIR}/src/MonothoneChain.cpp
)
target_include_directories(
	${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PUBLIC ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC ${SDL2_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
