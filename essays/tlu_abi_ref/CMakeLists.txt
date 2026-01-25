cmake_minimum_required(VERSION 3.16)
project(tlu_abi_ref C)

add_library(tlu_abi_ref STATIC
  src/tlu_abi_ref.c
)

target_include_directories(tlu_abi_ref PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(test_tlu_abi_ref
  tests/test_tlu_abi_ref.c
)

target_link_libraries(test_tlu_abi_ref PRIVATE tlu_abi_ref)

enable_testing()
add_test(NAME tlu_abi_ref_tests COMMAND test_tlu_abi_ref)
