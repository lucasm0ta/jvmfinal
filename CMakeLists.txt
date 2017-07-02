cmake_minimum_required(VERSION 3.1)
project(jvmfinal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/array.c
        src/classList.c
        src/classLoader.c
        src/classViewer.c
        src/frame.c
        src/instructionMapper.c
        src/instructions.c
        src/lookupswitchViewer.c
        src/main.c
        src/methodArea.c
        src/objectManager.c
        src/switchViewer.c
        src/tableswitchViewer.c)

add_executable(jvmfinal ${SOURCE_FILES})
target_link_libraries(jvmfinal m)

set_property(TARGET jvmfinal PROPERTY C_STANDARD 99)
