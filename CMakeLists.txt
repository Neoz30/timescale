cmake_minimum_required(VERSION 3.28)

project(
	Timescale
	VERSION 1.0
	LANGUAGES CXX
	)

add_executable(Timescale timescale/main.cpp)
add_library(Vec2 timescale/libmath/vec2.cpp)
# add_library(Graphics "./timescale/graphics/graphics.cpp")

if (NOT PNG AND WIN32 AND NOT MSVC)
	set(PNG_LIBRARY "C:/Program Files (x86)/libpng")
	set(PNG_PNG_INCLUDE_DIR "C:/Program Files (x86)/libpng/include")
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(Timescale
	PUBLIC "timescale"
	PUBLIC ${SDL2_INCLUDE_DIR}
	PUBLIC ${SDL2IMAGE_INCLUDE_DIRS}
	)

if(WIN32 AND NOT MSVC)
	target_link_libraries(Timescale	PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image mingw32)
else()
	target_link_libraries(Timescale	PUBLIC ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
endif()

target_link_libraries(Timescale PUBLIC Vec2)