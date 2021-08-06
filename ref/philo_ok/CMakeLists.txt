cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 11)

#include_directories(philo_one)
#include_directories(philo_two)
include_directories(philo_three)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

file(GLOB
        PHILO_ONE "philo_one/*.c")

file(GLOB
        PHILO_TWO "philo_two/*.c")

file(GLOB
        PHILO_THREE "philo_three/*.c")

add_executable(philo
#        ${PHILO_ONE}
#        ${PHILO_TWO}
        ${PHILO_THREE}
        )
