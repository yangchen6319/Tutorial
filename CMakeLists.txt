cmake_minimum_required(VERSION 3.15)

# set the project name
project(Tutorial)


# add the MathFunctions library
add_subdirectory(MathFunctions)

# add the executable
add_executable(myprog Tutorial.cpp)

target_link_libraries(myprog PUBLIC MathFunctions)
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(myprog PUBLIC
                           ${PROJECT_BINARY_DIR}
                           ${PROJECT_SOURCE_DIR}/MathFunctions
                           )

add_executable(copy Chapter4/4-1Copy.c++)
target_link_libraries(copy PUBLIC MathFunctions)
target_include_directories(copy PUBLIC
                           ${PROJECT_SOURCE_DIR}/MathFunctions)   