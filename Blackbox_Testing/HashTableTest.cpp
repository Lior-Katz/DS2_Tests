//
// Created by Lior on 16/03/2024.
//
#include "gtest/gtest.h"
#include "../../HashTable.h"
#include "../utils.h"

#include <vector>
#include <utility>

enum opType
{
	INSERT, REMOVE, FIND
};

template <typename T, typename S>
std::string str(std::pair<T, S> p)
{
	return std::to_string(p.first) + ", " + std::to_string(p.second);
}

std::string str(int n)
{
	return std::to_string(n);
}

template <typename T, typename S>
std::string errMsg(opType op, S operand, StatusType expected, StatusType actual, T valActual, T valExp);

template <typename S>
std::string errMsg(opType op, S operand, StatusType expected, StatusType actual);

template <typename T, typename S>
std::string errMsg(opType op, S operand, T valExp, T valActual);

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
		auto res = emptyTable.insert(i, i * 10);
		auto expected = SUCCESS;
		EXPECT_EQ(res, expected) << errMsg(INSERT, i, expected, res);
	}
	
	// Verify the inserted elements
	for (int i = 0; i < 20; ++i)
	{
		auto result = emptyTable.find(i);
		auto expectedStatus = SUCCESS;
		auto expectedValue = i * 10;
		EXPECT_EQ(result.status(), expectedStatus)
							<< errMsg(FIND, i, expectedStatus, result.status(), result.ans(), expectedValue);
	}
}

TEST_F(HashTableWithElements, Insertion_ExistingElement)
{
	// Insertion failure due to already existing key
	auto res1 = table.insert(20, 150);
	auto expected1 = SUCCESS;
	EXPECT_EQ(res1, expected1) << errMsg(INSERT, 20, expected1, res1);
	
	auto res2 = table.insert(20, 150);
	auto expected2 = FAILURE;
	EXPECT_EQ(res2, expected2) << errMsg(INSERT, 20, expected2, res2);
}

TEST_F(HashTableWithElements, Insertion_AllocationError)
{
	// Test allocation error
	// (assuming allocation error is simulated within HashTable implementation)
	// auto res = table.insert(30, 300);
	// auto expected = ALLOCATION_ERROR;
	// EXPECT_EQ(res, expected) << errMsg(INSERT, res, expected, 30);
}

// Test removal of elements
TEST_F(HashTableWithElements, Removal_ExistingElement)
{
	// Remove existing elements
	for (int i = 0; i < 20; ++i)
	{
		auto res = table.remove(i);
		auto expected = SUCCESS;
		EXPECT_EQ(res, expected) << errMsg(REMOVE, i, expected, res);
	}
}

TEST_F(EmptyHashTable, Removal_NonExistentElement)
{
	// Attempt to remove non-existent element
	auto res = table.remove(25);
	auto expected = FAILURE;
	EXPECT_EQ(res, expected) << errMsg(REMOVE, 25, expected, res);
}

TEST_F(EmptyHashTable, Removal_EmptyTable)
{
	// Attempt to remove from an empty table
	HashTable<int, int> emptyTable;
	auto res = emptyTable.remove(5);
	auto expected = FAILURE;
	EXPECT_EQ(res, expected) << errMsg(REMOVE, 5, expected, res);
}

// Test finding elements
TEST_F(HashTableWithElements, Find_ExistingElement)
{
	// Finding existing elements
	for (int i = 0; i < 20; ++i)
	{
		auto result = table.find(i);
		auto expectedStatus = SUCCESS;
		auto expectedValue = i * 10;
		EXPECT_EQ(result.status(), expectedStatus)
							<< errMsg(FIND, i, expectedStatus, result.status(), result.ans(), expectedValue);
	}
}

TEST_F(EmptyHashTable, Find_NonExistentElement)
{
	// Finding non-existent element
	auto nonExistentResult = table.find(25);
	auto expected = FAILURE;
	EXPECT_EQ(nonExistentResult.status(), expected) << errMsg(FIND, 25, expected, nonExistentResult.status());
}

TEST_F(EmptyHashTable, Find_EmptyTable)
{
	// Test finding on an empty table
	HashTable<int, int> emptyTable;
	auto emptyResult = emptyTable.find(5);
	auto expected = FAILURE;
	EXPECT_EQ(emptyResult.status(), expected) << errMsg(FIND, 5, expected, emptyResult.status());
}

// Test insertion of elements causing collisions with longer input
TEST_F(HashTableWithCollisions, Insertion_Collissions)
{
	// Inserting elements causing collisions
	for (auto pair : inputs)
	{
		auto res = emptyTable.insert(pair.first, pair.second);
		auto expected = SUCCESS;
		EXPECT_EQ(res, expected) << errMsg(INSERT, pair.first, expected, res);
	}
	
	// Verify the inserted elements
	for (auto pair : inputs)
	{
		auto result = emptyTable.find(pair.first);
		auto expectedStatus = SUCCESS;
		auto expectedValue = pair.second;
		EXPECT_EQ(result.status(), expectedStatus) << errMsg(FIND, pair.first, expectedStatus, result.status());
		EXPECT_EQ(result.ans(), expectedValue) << errMsg(FIND, pair.first, result.ans(), expectedValue);
	}
}

// Test removal of elements causing collisions with longer input
TEST_F(HashTableWithCollisions, Removal_WithCollissions)
{
	// Remove elements causing collisions
	for (auto pair : inputs)
	{
		auto res = table.remove(pair.first);
		auto expected = SUCCESS;
		EXPECT_EQ(res, expected) << errMsg(REMOVE, pair.first, expected, res);
	}
	
	// Verify the removed elements
	for (auto pair : inputs)
	{
		auto res = table.find(pair.first);
		auto expected = FAILURE;
		EXPECT_EQ(res.status(), FAILURE) << errMsg(FIND, pair.first, expected, res.status());
	}
}

// Test finding elements causing collisions with longer input
TEST_F(HashTableWithCollisions, Find_WithCollisions)
{
	for (auto pair : inputs)
	{
		auto result = table.find(pair.first);
		auto expectedStatus = SUCCESS;
		auto expectedValue = pair.second;
		EXPECT_EQ(result.status(), expectedStatus)
							<< errMsg(FIND, pair.first, expectedStatus, result.status());
		EXPECT_EQ(result.ans(), expectedValue)
							<< errMsg(FIND, pair.first, result.ans(), expectedValue);
	}
}

// Test insertion on an empty HashTable after removing all elements
TEST_F(HashTableWithElements, Insert_AfterEmptyTable)
{
	// Remove all elements from the table
	for (int i = 0; i < 20; ++i)
	{
		auto res = table.remove(i);
		auto expected = SUCCESS;
		EXPECT_EQ(res, expected) << errMsg(REMOVE, i, expected, res);
	}
	
	// Attempt to perform insertions on an empty table
	auto res1 = table.insert(25, 250);
	auto res2 = table.insert(30, 300);
	EXPECT_EQ(res1, SUCCESS) << errMsg(INSERT, 25, SUCCESS, res1);
	EXPECT_EQ(res2, SUCCESS) << errMsg(INSERT, 30, SUCCESS, res2);
	
	// Verify the inserted elements
	auto res3 = table.find(25);
	auto res4 = table.find(30);
	EXPECT_EQ(res3.status(), SUCCESS) << errMsg(FIND, 25, SUCCESS, res3.status());
	EXPECT_EQ(res3.ans(), 250) << errMsg(FIND, 25, 250, res3.ans());
	EXPECT_EQ(res4.status(), SUCCESS) << errMsg(FIND, 30, SUCCESS, res4.status());
	EXPECT_EQ(res4.ans(), 300) << errMsg(FIND, 30, 300, res4.ans());
}

// Test removal on an empty HashTable after removing all elements
TEST_F(HashTableWithElements, Remove_AfterEmptyTable)
{
	// Remove all elements from the table
	for (int i = 0; i < 20; ++i)
	{
		auto res = table.remove(i);
		auto expected = SUCCESS;
		EXPECT_EQ(res, expected) << errMsg(REMOVE, i, expected, res);
	}
	
	// Attempt to perform removals on an empty table
	auto res1 = table.remove(25);
	auto res2 = table.remove(30);
	EXPECT_EQ(res1, FAILURE) << errMsg(REMOVE, 25, FAILURE, res1);
	EXPECT_EQ(res2, FAILURE) << errMsg(REMOVE, 30, FAILURE, res2);
	
	
	// Verify the removed elements
	auto res3 = table.find(25);
	auto res4 = table.find(30);
	EXPECT_EQ(res3.status(), FAILURE) << errMsg(FIND, 25, FAILURE, res3.status());
	EXPECT_EQ(res4.status(), FAILURE) << errMsg(FIND, 30, FAILURE, res4.status());
}

// Test finding on an empty HashTable after removing all elements
TEST_F(HashTableWithElements, FindOnEmptyTable)
{
	// Remove all elements from the table
	for (int i = 0; i < 20; ++i)
	{
		auto res = table.remove(i);
		auto expected = SUCCESS;
		EXPECT_EQ(res, expected) << errMsg(REMOVE, i, expected, res);
	}
	
	// Attempt to find elements on an empty table
	auto res3 = table.find(25);
	auto res4 = table.find(30);
	EXPECT_EQ(res3.status(), FAILURE) << errMsg(FIND, 25, FAILURE, res3.status());
	EXPECT_EQ(res4.status(), FAILURE) << errMsg(FIND, 30, FAILURE, res4.status());}

template <typename T, typename S>
std::string errMsg(opType op, S operand, StatusType expected, StatusType actual, T valActual, T valExp)
{
	std::string opStr;
	switch (op)
	{
		case INSERT:
			opStr = "Insertion";
			break;
		case REMOVE:
			opStr = "Removal";
			break;
		case FIND:
			opStr = "Finding";
			break;
		default:
			return "";
	}
	std::string msg = opStr + " of " + str(operand) + " failed.";
	if (expected != actual)
	{
		msg += "Expected result " + str(expected) + ", Actual: " + str(actual) + "\n";
	}
	if (valExp != valActual)
	{
		msg += "Expected value: " + str(valExp) + ", Actual: " + str(valActual);
	}
	return msg;
}

template <typename S>
std::string errMsg(opType op, S operand, StatusType expected, StatusType actual)
{
	std::string opStr;
	switch (op)
	{
		case INSERT:
			opStr = "Insertion";
			break;
		case REMOVE:
			opStr = "Removal";
			break;
		case FIND:
			opStr = "Finding";
			break;
		default:
			return "";
	}
	std::string msg = opStr + " of " + str(operand) + " failed.";
	if (expected != actual)
	{
		msg += "Expected result " + str(expected) + ", Actual: " + str(actual) + "\n";
	}
	return msg;
}

template <typename T, typename S>
std::string errMsg(opType op, S operand, T valExp, T valActual)
{
	std::string opStr;
	switch (op)
	{
		case INSERT:
			opStr = "Insertion";
			break;
		case REMOVE:
			opStr = "Removal";
			break;
		case FIND:
			opStr = "Finding";
			break;
		default:
			return "";
	}
	std::string msg = opStr + " of " + str(operand) + " failed.";
	if (valExp != valActual)
	{
		msg += "Expected value: " + str(valExp) + ", Actual: " + str(valActual);
	}
	return msg;
}



