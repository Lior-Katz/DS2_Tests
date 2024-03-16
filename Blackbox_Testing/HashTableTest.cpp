//
// Created by Lior on 16/03/2024.
//
#include <gtest/gtest.h>
#include "../../HashTable.h"
#include "../utils.h"

#include <vector>
#include <utility>


#define SUITE HashTableTest

// Fixture for HashTable tests with empty table
class EmptyHashTable : public ::testing::Test
{
protected:
	HashTable<int, int> table;
};

// Fixture for HashTable tests with pre-inserted elements
class HashTableWithElements : public ::testing::Test
{
protected:
	HashTable<int, int> table;
	
	void SetUp() override
	{
		// Initialize the HashTable with some elements
		for (int i = 0; i < 20; ++i)
		{
			table.insert(i, i * 10);
		}
	}
};

class HashTableWithCollisions : public ::testing::Test
{
protected:
	HashTable<int, int> emptyTable;
	
	HashTable<int, int> table;
	
	std::vector<std::pair<int, int>> inputs;
	
	void SetUp() override
	{
		// Populate the inputs vector with elements engineered to cause collisions
		// Inserting numbers that are multiples of 7, 8, and 9 to cause collisions
		for (int i = 1; i < 50; ++i)
		{
			inputs.push_back(std::make_pair(i, i * 70));
			inputs.push_back(std::make_pair(i * 50, i * 80));
			inputs.push_back(std::make_pair(i * 51, i * 90));
		}
		// Initialize the HashTable with elements engineered to cause collisions
		// Inserting numbers that are multiples of 7, 8, and 9 to cause collisions
		for (auto pair : inputs)
		{
			table.insert(pair.first, pair.second);
		}
	}
};
// Test insertion of new elements
TEST(SUITE, Insertion_NewElement)
{
	HashTable<int, int> emptyTable;
	
	// Insertion of 20 new elements
	for (int i = 0; i < 20; ++i)
	{
		EXPECT_EQ(emptyTable.insert(i, i * 10), SUCCESS);
	}
	
	// Verify the inserted elements
	for (int i = 0; i < 20; ++i)
	{
		output_t<int> result = emptyTable.find(i);
		EXPECT_EQ(result.status(), SUCCESS);
		EXPECT_EQ(result.ans(), i * 10);
	}
}

TEST_F(HashTableWithElements, Insertion_ExistingElement)
{
	// Insertion failure due to already existing key
	EXPECT_EQ(table.insert(20, 150), SUCCESS);
	EXPECT_EQ(table.insert(20, 150), FAILURE);
}

TEST_F(HashTableWithElements, Insertion_AllocationError)
{
	// Test allocation error
	// (assuming allocation error is simulated within HashTable implementation)
	// EXPECT_EQ(table.insert(30, 300), StatusType::ALLOCATION_ERROR);
}

// Test removal of elements
TEST_F(HashTableWithElements, Removal_ExistingElement)
{
	// Remove existing elements
	for (int i = 0; i < 20; ++i)
	{
		EXPECT_EQ(table.remove(i), SUCCESS);
	}
}

TEST_F(EmptyHashTable, Removal_NonExistentElement)
{
	// Attempt to remove non-existent element
	EXPECT_EQ(table.remove(25), FAILURE);
}

TEST_F(EmptyHashTable, Removal_EmptyTable)
{
	// Attempt to remove from an empty table
	HashTable<int, int> emptyTable;
	EXPECT_EQ(emptyTable.remove(5), FAILURE);
}

// Test finding elements
TEST_F(HashTableWithElements, Find_ExistingElement)
{
	// Finding existing elements
	for (int i = 0; i < 20; ++i)
	{
		output_t<int> result = table.find(i);
		EXPECT_EQ(result.status(), SUCCESS);
		EXPECT_EQ(result.ans(), i * 10);
	}
}

TEST_F(EmptyHashTable, Find_NonExistentElement)
{
	// Finding non-existent element
	output_t<int> nonExistentResult = table.find(25);
	EXPECT_EQ(nonExistentResult.status(), FAILURE);
}

TEST_F(EmptyHashTable, Find_EmptyTable)
{
	// Test finding on an empty table
	HashTable<int, int> emptyTable;
	output_t<int> emptyResult = emptyTable.find(5);
	EXPECT_EQ(emptyResult.status(), FAILURE);
}

// Test insertion of elements causing collisions with longer input
TEST_F(HashTableWithCollisions, Insertion_Collissions)
{
	// Inserting elements causing collisions
	for (auto pair : inputs)
	{
		//
		auto res = emptyTable.insert(pair.first, pair.second);
		// convert res to string
		EXPECT_EQ(res, SUCCESS) << "Failed to insert (" << pair.first << ", " << pair.second << "); " << "Status: "
								<< str(res) << std::endl;
	}
	
	// Verify the inserted elements
	for (auto pair : inputs)
	{
		output_t<int> result = emptyTable.find(pair.first);
		EXPECT_EQ(result.status(), SUCCESS);
		EXPECT_EQ(result.ans(), pair.second);
	}
}

// Test removal of elements causing collisions with longer input
TEST_F(HashTableWithCollisions, Removal_WithCollissions)
{
	// Remove elements causing collisions
	for (auto pair : inputs)
	{
		EXPECT_EQ(table.remove(pair.first), SUCCESS);
	}
	
	// Verify the removed elements
	for (auto pair : inputs)
	{
		EXPECT_EQ(table.find(pair.first).status(), FAILURE);
	}
}

// Test finding elements causing collisions with longer input
TEST_F(HashTableWithCollisions, Find_WithCollissions)
{
	for (auto pair : inputs)
	{
		output_t<int> result = table.find(pair.first);
		EXPECT_EQ(result.status(), SUCCESS)
							<< "Failed to find " << pair.first << ";" << "Status: " << str(result.status())
							<< std::endl;
		EXPECT_EQ(result.ans(), pair.second)
							<< "Incorrect value. Expected: " << pair.second << ", Actual: " << result.ans()
							<< std::endl;
	}
}

// Test insertion on an empty HashTable after removing all elements
TEST_F(HashTableWithElements, Insert_AfterEmptyTable)
{
	// Remove all elements from the table
	for (int i = 0; i < 20; ++i)
	{
		EXPECT_EQ(table.remove(i), SUCCESS);
	}
	
	// Attempt to perform insertions on an empty table
	EXPECT_EQ(table.insert(25, 250), SUCCESS);
	EXPECT_EQ(table.insert(30, 300), SUCCESS);
	
	// Verify the inserted elements
	EXPECT_EQ(table.find(25).status(), SUCCESS);
	EXPECT_EQ(table.find(25).ans(), 250);
	EXPECT_EQ(table.find(30).status(), SUCCESS);
	EXPECT_EQ(table.find(30).ans(), 300);
}

// Test removal on an empty HashTable after removing all elements
TEST_F(HashTableWithElements, Remove_AfterEmptyTable)
{
	// Remove all elements from the table
	for (int i = 0; i < 20; ++i)
	{
		EXPECT_EQ(table.remove(i), SUCCESS);
	}
	
	// Attempt to perform removals on an empty table
	EXPECT_EQ(table.remove(25), FAILURE);
	EXPECT_EQ(table.remove(30), FAILURE);
	
	// Verify the removed elements
	EXPECT_EQ(table.find(25).status(), FAILURE);
	EXPECT_EQ(table.find(30).status(), FAILURE);
}

// Test finding on an empty HashTable after removing all elements
TEST_F(HashTableWithElements, FindOnEmptyTable)
{
	// Remove all elements from the table
	for (int i = 0; i < 20; ++i)
	{
		EXPECT_EQ(table.remove(i), SUCCESS);
	}
	
	// Attempt to find elements on an empty table
	EXPECT_EQ(table.find(25).status(), FAILURE);
	EXPECT_EQ(table.find(30).status(), FAILURE);
}
