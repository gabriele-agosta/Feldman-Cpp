cmake_minimum_required(VERSION 3.27)
project(Feldman_C__)

set(CMAKE_CXX_STANDARD 17)

add_executable(Feldman_C__ main.cpp
        player.cpp
        player.h
        polynomial.cpp
        polynomial.h
        dealer.cpp
        dealer.h
        mod_pow.cpp
        mod_pow.h)
