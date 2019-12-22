cmake_minimum_required(VERSION 3.15)
project(flightgear)

set(CMAKE_CXX_STANDARD 11)

add_executable(flightgear main.cpp lexer.cpp lexer.h Command.cpp Command.h OpenServerCommand.cpp OpenServerCommand.h DefineVarCommand.cpp DefineVarCommand.h SleepCommand.cpp SleepCommand.h)