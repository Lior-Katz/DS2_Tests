project(Blackbox)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Blackbox_test HashTableTest.cpp)

target_link_libraries(Blackbox_test gtest gtest_main)