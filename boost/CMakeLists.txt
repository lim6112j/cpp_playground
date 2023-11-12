cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tutorial)
set(CMAKE_CXX_STANDARD 17)
# add boost dependency
find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(/opt/homebrew/Cellar/boost/1.82.0_1/lib)
link_libraries(boost_program_options)
# add the executable
add_executable(simple simple.cpp)
