cmake_minimum_required(VERSION 3.15)
project(flightgear)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(flightgear main.cpp Lexer.cpp Lexer.h Command.h OpenServerCommand.cpp OpenServerCommand.h ConnectCommand.cpp ConnectCommand.h PrintCommand.cpp PrintCommand.h ConditionParser.cpp ConditionParser.h DefineVarCommand.cpp DefineVarCommand.h SleepCommand.cpp SleepCommand.h Parser.cpp Parser.h IfCommand.cpp IfCommand.h LoopCommand.cpp LoopCommand.h parseBufferToSymbleTable.cpp parseBufferToSymbleTable.h Maps.h Maps.cpp SetCommand.cpp SetCommand.h Expression.h ExpressionCalculate.cpp ExpressionCalculate.h)