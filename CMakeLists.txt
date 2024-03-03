cmake_minimum_required(VERSION 3.24)
project(Lab3dsa)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3dsa
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ListIterator.cpp
        ListIterator.h
        ShortTest.cpp
        ShortTest.h
        SortedIteratedList.cpp
        SortedIteratedList.h)
