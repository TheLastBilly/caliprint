cmake_minimum_required(VERSION 3.0)
project ("caliprint" VERSION 0.1)

add_compile_options(-std=c11 -Wall)

include(CPack)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

file(GLOB SOURCES
    src/include/*.h
    src/*.c
)

add_executable( caliprint ${SOURCES} )

TARGET_LINK_LIBRARIES( caliprint ${GTK3_LIBRARIES})