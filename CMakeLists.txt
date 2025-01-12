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
add_subdirectory(02_EvaluateReelLines)
add_subdirectory(03_PickGameSimulation)
add_subdirectory(04_MysteryJackpots)
add_subdirectory(05_ProgressiveJackpot)
add_subdirectory(06_PokerEvaluator)