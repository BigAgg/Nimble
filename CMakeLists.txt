cmake_minimum_required(VERSION 3.12) # FetchContent is available in 3.11+
project(Nimble)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API aa1f7df0-828a-4fcd-9afc-2dc80491aca7)
set(CMAKE_CXX_STANDARD 20)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Our Project
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib )

include_directories(
	"include/GameObject"
	"include/Main"
	"include/Utility"
)

file(GLOB SRC CONFIGURE_DEPENDS
	"include/*/*.hpp"
	"src/*/*.cpp"
)
add_executable(${PROJECT_NAME} main.cpp ${SRC})
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
