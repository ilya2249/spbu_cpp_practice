add_executable(hw1_main main.cpp)

add_executable(hw1_tests tests/test_sort.cpp)

add_executable(hw1_bench bench/benchmark.cpp)

target_include_directories(hw1_main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(hw1_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(hw1_bench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

