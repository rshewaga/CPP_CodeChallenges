cmake_minimum_required(VERSION 3.15)


#######################################################################################
# Configure project

set(PROJ_NAME 06_PokerEvaluator)
project(
    ${PROJ_NAME}
    VERSION 1.0
    DESCRIPTION "Evaluate all possible 5-card poker hands."
    HOMEPAGE_URL https://github.com/rshewaga
    LANGUAGES CXX
)

# Release by default for consumers
set(CMAKE_BUILD_TYPE Release)


#######################################################################################
# Other files added to a target for visibility

add_custom_target(
    ${PROJ_NAME}_other_files
    SOURCES
    README.md
)

include(GNUInstallDirs)


#######################################################################################
# Link the following interface to set the c++ standard / compile-time options requested

add_library(${PROJ_NAME}_project_options INTERFACE)

target_compile_features(
    ${PROJ_NAME}_project_options
    INTERFACE
    cxx_std_20
)

target_compile_definitions(
    ${PROJ_NAME}_project_options
    INTERFACE
    CMAKE_BINARY_DIR="${CMAKE_BINARY_DIR}"
    CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
    CMAKE_INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}"
    PROJ_NAME="${PROJ_NAME}"
)



#######################################################################################
# Link the following interface to use the warnings specified in CompilerWarnings.cmake
add_library(
    ${PROJ_NAME}_project_warnings
    INTERFACE
)

# standard compiler warnings
include(../cmake/CompilerWarnings.cmake)
set_project_warnings(${PROJ_NAME}_project_warnings)


#######################################################################################

set(EXEC_NAME 06_PokerEvaluator)
add_executable(
    ${EXEC_NAME}
    src/6_PokerEvaluator.cpp
)

target_link_libraries( 
    ${EXEC_NAME}
    PRIVATE
    ${PROJ_NAME}_project_warnings
    ${PROJ_NAME}_project_options
)