cmake_minimum_required(VERSION 2.6)
project(wgen)

add_executable(wgen main.cpp)

install(TARGETS wgen RUNTIME DESTINATION bin)
