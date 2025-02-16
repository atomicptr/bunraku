cmake_minimum_required(VERSION 3.30)

project(bunraku)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("src")

### setup dependencies
include(FetchContent)

###### raylib
set(RAYLIB_VERSION 5.5)
FetchContent_Declare(
  raylib
  URL "https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz"
  SYSTEM
  FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)


add_executable(anim8_1945 examples/anim8_1945/src/main.cpp)
target_link_libraries(anim8_1945 PRIVATE raylib)

add_executable(cat_fighter_fsm examples/cat_fighter_fsm/src/main.cpp)
target_link_libraries(cat_fighter_fsm PRIVATE raylib)
