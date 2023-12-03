cmake_minimum_required(VERSION 3.27)
project(aoc_cpp_2023)

set(CMAKE_CXX_STANDARD 23)

# Third party
add_subdirectory(libs/fmt-10.1.1) # FMT

# Add solutions manually here
set(SOLUTION_LIST
        day_01
        # day_02
)

add_library(COMMON_LIB INTERFACE src/common/SolutionBase.h)

foreach (solution ${SOLUTION_LIST})
    file(GLOB_RECURSE SOLUTION_FILES CONFIGURE_DEPENDS src/solutions/${solution}/*.cpp)
    add_executable(${solution} ${SOLUTION_FILES})
    target_include_directories(${solution} PRIVATE src/solutions/${solution})
    target_include_directories(${solution} INTERFACE libs/fmt-10.1.1/include)
    target_include_directories(${solution} PRIVATE src/common)
    target_link_libraries(${solution} PRIVATE fmt::fmt-header-only)
endforeach ()
