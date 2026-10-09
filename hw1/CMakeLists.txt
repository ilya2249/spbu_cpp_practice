add_executable(hw1_main main.cpp)

add_executable(hw1_tests tests/test_sort.cpp)
add_test(NAME hw1_tests COMMAND hw1_tests)

add_executable(hw1_bench bench/benchmark.cpp)

target_include_directories(hw1_main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(hw1_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(hw1_bench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Avoid loading incompatible MinGW runtime DLLs from other programs in PATH.
if(MINGW)
    foreach(target IN ITEMS hw1_main hw1_tests hw1_bench)
        target_link_options(${target} PRIVATE -static)
    endforeach()
endif()
