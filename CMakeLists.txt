cmake_minimum_required(VERSION 3.7)
project(jvmfinal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/array.c
        src/array.h
        src/classList.c
        src/classList.h
        src/classLoader.c
        src/classLoader.h
        src/classViewer.c
        src/classViewer.h
        src/frame.c
        src/frame.h
        src/instructionMapper.c
        src/instructionMapper.h
        src/instructions.c
        src/instructions.h
        src/lookupswitchViewer.c
        src/lookupswitchViewer.h
        src/main.c
        src/methodArea.c
        src/methodArea.h
        src/objectManager.c
        src/objectManager.h
        src/switchViewer.c
        src/switchViewer.h
        src/tableswitchViewer.c
        src/tableswitchViewer.h)

add_executable(jvmfinal ${SOURCE_FILES})