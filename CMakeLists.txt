# Configuring a project that uses google test/mock
# Gene De Lisa
# http://rockhoppertech.com/

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

project(boostTest1 VERSION 0.0.1 LANGUAGES C CXX)

message( STATUS "PROJECT_NAME: " ${PROJECT_NAME} )

# add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall -Wextra -pedantic")

###############################################################################
# Boost Test
#
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories (${TEST_SOURCE_DIR}/src
                    ${Boost_INCLUDE_DIRS}
)

# https://www.boost.org/doc/libs/1_46_1/libs/test/doc/html/utf/user-guide/usage-variants/dynamic-lib-variant.html
add_definitions(-DBOOST_TEST_DYN_LINK)



#####################
# your source and test sources

###############################################################################
## file globbing ##############################################################
###############################################################################

# These instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables
# `sources`, `sources_app` for app specific (e.g. main),  and `data`.
file(GLOB_RECURSE sources       src/main/*.cpp src/main/*.hpp src/main/*.h)
file(GLOB_RECURSE sources_app   src/app/*.cpp src/app/*.hpp src/app/*.h)
file(GLOB_RECURSE sources_test  src/test/*.cpp src/main/*.hpp src/main/*.h)
file(GLOB_RECURSE data          resources/*)

include_directories(src/include)

###############################################################################
## target definitions #########################################################
###############################################################################

# I've added src/include so it appears in the generated Xcode project.
add_executable(exampleapp ${sources} ${sources_app} ${data} src/include)

add_executable(unit_tests ${sources_test} ${sources})

set_target_properties(exampleapp PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
set_target_properties(unit_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(exampleapp
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
)
target_link_libraries(unit_tests
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
