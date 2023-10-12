cmake_minimum_required(VERSION 3.26)
project(LSTM_inf_in_C)

set(CMAKE_CXX_STANDARD 17)

add_executable(LSTM_inf_in_C main.c
        initialization.c
        operators.c
        )

#ADD_LIBRARY(TEST initialization.c
#        test.cpp)
