cmake_minimum_required(VERSION 3.16)
project(tsl_ref LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(tsl_ref INTERFACE)
target_include_directories(tsl_ref INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_testing()

add_executable(test_trit_compile tests/test_trit_compile.cpp)
target_link_libraries(test_trit_compile PRIVATE tsl_ref)
add_test(NAME test_trit_compile COMMAND test_trit_compile)

add_executable(test_policy_compile tests/test_policy_compile.cpp)
target_link_libraries(test_policy_compile PRIVATE tsl_ref)
add_test(NAME test_policy_compile COMMAND test_policy_compile)

add_executable(test_ops_tables tests/test_ops_tables.cpp)
target_link_libraries(test_ops_tables PRIVATE tsl_ref)
add_test(NAME test_ops_tables COMMAND test_ops_tables)

add_executable(test_add_sat_table tests/test_add_sat_table.cpp)
target_link_libraries(test_add_sat_table PRIVATE tsl_ref)
add_test(NAME test_add_sat_table COMMAND test_add_sat_table)

add_executable(test_serialize tests/test_serialize.cpp)
target_link_libraries(test_serialize PRIVATE tsl_ref)
add_test(NAME test_serialize COMMAND test_serialize)

add_executable(test_reduce tests/test_reduce.cpp)
target_link_libraries(test_reduce PRIVATE tsl_ref)
add_test(NAME test_reduce COMMAND test_reduce)

add_executable(test_cmp_policy tests/test_cmp_policy.cpp)
target_link_libraries(test_cmp_policy PRIVATE tsl_ref)
add_test(NAME test_cmp_policy COMMAND test_cmp_policy)

add_executable(test_toy_pipeline tests/test_toy_pipeline.cpp)
target_link_libraries(test_toy_pipeline PRIVATE tsl_ref)
add_test(NAME test_toy_pipeline COMMAND test_toy_pipeline)

add_executable(test_reduce_policy tests/test_reduce_policy.cpp)
target_link_libraries(test_reduce_policy PRIVATE tsl_ref)
add_test(NAME test_reduce_policy COMMAND test_reduce_policy)

add_executable(test_toy_masked_pipeline tests/test_toy_masked_pipeline.cpp)
target_link_libraries(test_toy_masked_pipeline PRIVATE tsl_ref)
add_test(NAME test_toy_masked_pipeline COMMAND test_toy_masked_pipeline)

add_executable(bench_reduce bench/bench_reduce.cpp)
target_link_libraries(bench_reduce PRIVATE tsl_ref)

add_executable(bench_reduce_baseline bench/bench_reduce_baseline.cpp)
