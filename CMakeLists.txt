cmake_minimum_required(VERSION 3.9)
MESSAGE(STATUS $ENV{TRAVIS_BUILD_NUMBER})
project(Allocator)

set(CMAKE_CXX_STANDARD 14)
include (CTest)
add_library(my_alloc Memory_Pool.cpp Memory_Pool.h Check.h My_Allocator.h)
add_library(list Linked_List.h Linked_List.cpp Node.h)

add_executable(allocator main.cpp)
add_executable(TEST tests.cpp)
add_test(memtest allocator)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
set(CMAKE_CXX_STANDARD 14)

set_target_properties(allocator PROPERTIES
        CXX_STANDART 14
        CXX_STANDART_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )

set_target_properties(TEST PROPERTIES
        COMPILE_DEFENITONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

target_link_libraries(TEST my_alloc list
        ${Boost_LIBRARIES}
        )

target_link_libraries(allocator list
        my_alloc
        )

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set( CPACK_PACKAGE_FILE_NAME allocator)
set(CPACK_PACKAGE_CONTACT nikita1993chizh@gmail.com)
include(CPack)
enable_testing()
