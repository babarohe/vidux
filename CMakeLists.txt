set(SOURCE_CODE vidux CACHE NAME "main")

cmake_minimum_required(VERSION 3.0.0)
project( ${SOURCE_CODE} )

# project(vidux VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(vidux main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ${SOURCE_CODE} main.cpp )
target_link_libraries( ${SOURCE_CODE} ${OpenCV_LIBS} )
