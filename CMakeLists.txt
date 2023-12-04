cmake_minimum_required(VERSION 3.27)
project(aoc_cpp_2023)

set(CMAKE_CXX_STANDARD 23)

# Third party
add_subdirectory(libs/fmt-10.1.1) # FMT
include_directories(INTERFACE libs/fmt-10.1.1/include)
link_libraries(fmt::fmt-header-only)

# Helper library
add_library(COMMON_LIB STATIC src/common/SolutionBase.cpp)
include_directories(INTERFACE src/common)
link_libraries(COMMON_LIB)

# Add solutions manually here
set(SOLUTION_LIST
        day_01
        day_02
        day_03
        day_04
        day_05
)

foreach (solution ${SOLUTION_LIST})
    file(GLOB_RECURSE SOLUTION_FILES CONFIGURE_DEPENDS src/solutions/${solution}/*.cpp)
    add_executable(${solution} ${SOLUTION_FILES})
    target_include_directories(${solution} PRIVATE src/solutions/${solution})
endforeach ()
