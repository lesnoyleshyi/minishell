cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 11)

add_executable(minishell srcs/execute/old_main.c srcs/builtins/exit.c)
