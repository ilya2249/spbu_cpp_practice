add_executable(hw2_main main.cpp)

target_include_directories(hw2_main PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(hw2_tests tests/test_matrix.cpp)
target_include_directories(hw2_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME hw2_tests COMMAND hw2_tests)

add_executable(hw2_bench bench/benchmark.cpp)
target_include_directories(hw2_bench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
if(MSVC)
    set(HW2_OPTIMIZATION /O2)
else()
    set(HW2_OPTIMIZATION -O2)
endif()
target_compile_options(hw2_bench PRIVATE $<$<CONFIG:Release>:${HW2_OPTIMIZATION}>)
target_compile_definitions(hw2_bench PRIVATE
    HW2_BUILD_CONFIG="$<CONFIG>"
    HW2_COMPILER="${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}"
    HW2_OPTIMIZATION="${HW2_OPTIMIZATION}"
)
