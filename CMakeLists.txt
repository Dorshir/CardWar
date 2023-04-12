cmake_minimum_required(VERSION 3.24)
project(CardWar)

set(CMAKE_CXX_STANDARD 14)

add_executable(CardWar Demo.cpp doctest.h StudentTest1.cpp TestRunner.cpp sources/card.cpp sources/game.cpp sources/player.cpp)
