cmake_minimum_required(VERSION 3.16.3)

project(MC-RCON)

file(GLOB_RECURSE SRC "*.cpp")

add_library(mcrcon SHARED ${SRC})
