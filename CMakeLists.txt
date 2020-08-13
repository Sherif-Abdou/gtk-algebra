cmake_minimum_required(VERSION 3.17)
project(gtk_algebra)
project(gtk_algebra_lib)
project(gtk_algebra_test)

set(CMAKE_LIBRARY_PATH "/Users/sherif/.boost/lib" ${CMAKE_LIBRARY_PATH})
set(CMAKE_INCLUDE_PATH "/Users/sherif/.boost/include" ${CMAKE_INCLUDE_PATH})

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
