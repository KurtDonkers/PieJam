cmake_minimum_required (VERSION 3.5)

set(project_name PieJam)
set(version 0.0.1)
project (${project_name} VERSION ${version})

set(CMAKE_CXX_STANDARD 14) # C++14...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
add_definitions(-Wall)

file (GLOB SOURCES "src/*.cpp")

add_executable(${project_name} ${SOURCES})


SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.58.0 REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
    MESSAGE ("BOOST FOUND LIBS ")
    MESSAGE ("BOOST FOUND INCDIRS ${Boost_INCLUDE_DIRS}")
    MESSAGE ("BOOST FOUND LIBDIRS ${Boost_LIBRARY_DIRS}")
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
    SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})
    MESSAGE ("BOOST FOUND LIBS ${USED_LIBS}")
    TARGET_LINK_LIBRARIES(${project_name} ${USED_LIBS})
ENDIF(Boost_FOUND)