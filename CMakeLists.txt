cmake_minimum_required(VERSION 3.23)
project(new_labwork)

set(CMAKE_CXX_STANDARD 14)

add_executable(new_labwork main.cpp bmp/bmp.cpp bmp/bmp.h sandpile/sandpile.cpp parser/parser.cpp parser/parser.h
        make_picture/make_picture.cpp make_picture/make_picture.h)
