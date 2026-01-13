cmake_minimum_required(VERSION 3.10.0)
project(data-table-editor VERSION 0.1.0 LANGUAGES C CXX)

add_executable(data-table-editor main.cpp InputForm.cpp)

find_package(Curses REQUIRED)
target_link_libraries(data-table-editor ${CURSES_LIBRARIES})

