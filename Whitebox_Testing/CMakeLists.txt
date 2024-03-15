project(Whitebox)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Whitebox_test AVLTreeTest.cpp)

target_link_libraries(Whitebox_test gtest gtest_main)

