#checking the version for targeting inklude directories
cmake_minimum_required(VERSION 3.22)

#project name
project(UnrolledLinkedList)

#setting source and headers folders
set(SOURCE_DIR ./source)
set(INCLUDE_DIRECTORIES ./include)

#setting headers
set(HEADER_FILES ${INCLUDE_DIRECTORIES}/UnrolledLinkedList.h ${INCLUDE_DIRECTORIES}/UnrolledLinkedListNode.h)

#setting source files
set(SOURCE_OUT ${SOURCE_DIR}/main.cpp)
set(SOURCE_LIB ${SOURCE_DIR}/UnrolledLinkedList.cpp ${SOURCE_DIR}/UnrolledLinkedListNode.cpp ${HEADER_FILES})

#changing executable directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

#compilating included source files as static library
add_library(UnrolledLL STATIC ${SOURCE_LIB})

#retargeting headers directories
target_include_directories(UnrolledLL PRIVATE ${INCLUDE_DIRECTORIES})

#compilating main executable file
add_executable(main ${SOURCE_OUT})

#retargeting headers directories
target_include_directories(main PRIVATE ${INCLUDE_DIRECTORIES})

#linking
target_link_libraries(main UnrolledLL)