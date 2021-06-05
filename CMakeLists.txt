cmake_minimum_required(VERSION 2.8)
project(proxy)

add_definitions(-ggdb3 -Werror -Wno-builtin-macro-redefined -Wno-deprecated)
add_definitions(-DIM_RUN_MODE)

if (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION} VERSION_LESS 2.8.12)
    add_definitions(-std=c++0x)
else()
    add_compile_options(-std=c++0x)
endif()

set(PROJECT_ROOT_PATH           "${CMAKE_SOURCE_DIR}")
set(LIBRARY_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}/lib")
set(RUNTIME_OUTPUT_DIRECTORY    "${CMAKE_SOURCE_DIR}/bin")

include_directories(
	"${PROJECT_ROOT_PATH}/googletest/googletest/include/"
	"${PROJECT_ROOT_PATH}/googletest/googlemock/include/"
	"${PROJECT_ROOT_PATH}/"
)          

link_directories(
	"${PROJECT_ROOT_PATH}/googletest/googletest/build-aux/"
	"${PROJECT_ROOT_PATH}/googletest/googlemock/build-aux/"
	"${LIBRARY_OUTPUT_DIRECTORY}/"
)

add_subdirectory( googletest )
enable_testing()

add_executable(test_hashmap test_hashmap.cpp)
add_executable(test_skiplist test_skiplist.cpp)

target_link_libraries(test_hashmap gtest gmock pthread deps)
target_link_libraries(test_skiplist gtest gmock pthread deps)


add_test(NAME test_hashmap COMMAND test_hashmap)
add_test(NAME test_skiplist COMMAND test_skiplist)
