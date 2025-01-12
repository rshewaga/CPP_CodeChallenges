cmake_minimum_required(VERSION 3.15)

set(PROJ_NAME CodeChallenges)
project(
    ${PROJ_NAME}
    VERSION 1.0
    DESCRIPTION "My solutions to various code challenges."
    HOMEPAGE_URL https://github.com/rshewaga
    LANGUAGES CXX
)

add_subdirectory(01_ConsecutiveSymbols)