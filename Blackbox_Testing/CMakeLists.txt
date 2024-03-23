project(Blackbox)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Blackbox_test
		../utils.h
		../utils.cpp
		HashTableTest.cpp
		OlympicsTest.cpp
		../../olympics24a2.cpp
		../../olympics24a2.h
		../../Team.cpp
		../../Team.h
		../../AVL_Tree.h
		../../Player.cpp
		../../Player.h
		OlympicsTestFixtures.h
		OlympicsTestUtils.h)

target_link_libraries(Blackbox_test gtest gtest_main)