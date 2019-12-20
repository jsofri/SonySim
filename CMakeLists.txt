cmake_minimum_required(VERSION 3.15)
project(SonySim)

set(CMAKE_CXX_STANDARD 14)

add_executable(ACProject main.cpp Command.h VarCommand.cpp VarCommand.h GeneralData.h Expressions/Interpreter.cpp SymbolTable.cpp
        Expressions/Variable.cpp Expressions/Mul.cpp Expressions/UMinus.cpp Expressions/UPlus.cpp Expressions/Plus.cpp Expressions/Minus.cpp Expressions/Div.cpp Expressions/Value.cpp)