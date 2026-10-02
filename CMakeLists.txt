cmake_minimum_required(VERSION 3.18)
project(Raytrix LANGUAGES CXX)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

set(CORE_SOURCES ${SOURCES})
list(FILTER CORE_SOURCES EXCLUDE REGEX "main\\.cpp$")

add_executable(Raytrix ${SOURCES})
target_compile_features(Raytrix PRIVATE cxx_std_20)
target_compile_definitions(Raytrix PRIVATE ROOT_DIR="${CMAKE_SOURCE_DIR}")
target_include_directories(Raytrix PRIVATE include)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE TEST CONFIGURE_DEPENDS "tests/*.cpp")

add_executable(RunTests ${TEST} ${CORE_SOURCES})
target_compile_features(RunTests PRIVATE cxx_std_20)
target_include_directories(RunTests PRIVATE include)
target_link_libraries(RunTests PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(RunTests)