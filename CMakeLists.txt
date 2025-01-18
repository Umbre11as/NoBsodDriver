cmake_minimum_required(VERSION 3.26)
project(NoBsodDriver)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include("${CMAKE_CURRENT_LIST_DIR}/cmake/global-flags.cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Od /Oi /GS- /GL- /W0 /guard:cf- /Qspectre-") # Обожаю CMake (нет)
add_link_options("/ENTRY:DriverEntry")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(WDK REQUIRED)

include(FetchContent)
FetchContent_Declare(kCaveHook
        GIT_REPOSITORY https://github.com/Umbre11as/kCaveHook.git
        GIT_TAG        master
)
FetchContent_MakeAvailable(kCaveHook)

file(GLOB_RECURSE SOURCES "src/*.cpp")

wdk_add_driver(NoBsodDriver ${SOURCES})

target_link_libraries(NoBsodDriver kCaveHook)
