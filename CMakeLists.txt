project(Google_tests)
add_subdirectory(lib)
add_subdirectory(Blackbox_Testing)
add_subdirectory(Whitebox_Testing)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run
               Blackbox_Testing/HashTableTest.cpp
               Whitebox_Testing/HashTableTest.cpp
               Whitebox_Testing/AVLTreeTest.cpp
               )

target_link_libraries(Google_Tests_run gtest gtest_main)
