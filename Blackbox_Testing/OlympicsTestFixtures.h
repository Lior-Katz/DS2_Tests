//
// Created by Lior on 23/03/2024.
//

#ifndef DATASTRUCTURES2_OLYMPICSTESTFIXTURES_H
#define DATASTRUCTURES2_OLYMPICSTESTFIXTURES_H
#include "gtest/gtest.h"
#include "../../olympics24a2.h"
// Fixture for testing in an empty Olympics instance
class EmptyOlympics : public ::testing::Test
{
protected:
	// Declare Olympics object
	olympics_t olympics = olympics_t();
};

// Fixture for testing with pre-existing teams (no players)
class InitializedOlympicsTeamsOnly : public ::testing::Test
{
protected:
	// Declare Olympics object
	olympics_t olympics;
	
	// Vector to hold existing team IDs
	std::vector<int> existingIds;
	
	// Fixture setup with pre-existing teams
	void SetUp() override
	{
		// Initialize Olympics object with pre-existing teams
		const int numTeams = 30; // Number of teams to initialize
		for (int i = 1; i <= numTeams; ++i)
		{
			olympics.add_team(i);
			existingIds.push_back(i); // Add team ID to the vector
		}
	}
	
	// TearDown() is called after each test case
	void TearDown() override
	{
		// Clean up any objects or variables initialized in SetUp()
	}
};
#endif //DATASTRUCTURES2_OLYMPICSTESTFIXTURES_H
