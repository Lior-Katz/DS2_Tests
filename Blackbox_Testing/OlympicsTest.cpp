//
// Created by Lior on 23/03/2024.
//
#include <gtest/gtest.h>
#include <string>
#include <algorithm>
#include "../../olympics24a2.h"
#include "OlympicsTestUtils.h"
#include "OlympicsTestFixtures.h"

// Test case to add teams with valid teamIds in an empty Olympics instance
TEST_F(EmptyOlympics, AddTeamsValidIds)
{
	// Arrange
	const int numTeams = 10;
	StatusType expectedRes = SUCCESS;
	
	// Act & Assert
	for (int i = 1; i <= numTeams; ++i)
	{
		// Act
		StatusType res = olympics.add_team(i);
		
		// Assert
		EXPECT_EQ(res, expectedRes) << errMsg(ADD_TEAM, i, expectedRes, res);
	}
	
	// Check if teams were added successfully
	EXPECT_EQ(olympics.teamsHashTable.get_size(), numTeams);
}

// Test case to add teams with invalid (<= 0) teamIds in an empty Olympics instance
TEST_F(EmptyOlympics, AddTeamsInvalidIds)
{
	// Arrange
	const int invalidIds[] = {0, -1, -2, -3, -4}; // Including various invalid teamIds
	StatusType expectedRes = INVALID_INPUT;
	
	// Act & Assert
	for (int invalidId : invalidIds)
	{
		// Act
		StatusType res = olympics.add_team(invalidId);
		
		// Assert
		EXPECT_EQ(res, expectedRes) << errMsg(ADD_TEAM, invalidId, expectedRes, res);
	}
	
	// Check if no teams were added
	EXPECT_EQ(olympics.teamsHashTable.get_size(), 0);
}

// Test case to add teams with existing teamIds in an Olympics instance with pre-existing teams
TEST_F(InitializedOlympicsTeamsOnly, AddTeamsExistingIds)
{
	// Arrange
	StatusType expectedRes = FAILURE;
	
	// Act & Assert
	for (int existingId : existingIds)
	{
		// Act
		StatusType res = olympics.add_team(existingId);
		
		// Assert
		EXPECT_EQ(res, expectedRes) << errMsg(ADD_TEAM, existingId, expectedRes, res);
	}
	
	// Check if no additional teams were added
	EXPECT_EQ(olympics.teamsHashTable.get_size(), existingIds.size()); // 30 teams added in fixture setup
}

// Test case to remove a team with a valid teamId
TEST_F(InitializedOlympicsTeamsOnly, RemoveValidTeam)
{
	// Arrange
	const int teamId = 1;
	const auto expectedRes = SUCCESS;
	
	// Act
	const auto res = olympics.remove_team(teamId);
	
	// Assert
	EXPECT_EQ(res, expectedRes) << errMsg(REMOVE_TEAM, teamId, expectedRes, res);
	// Check if the team is actually removed
	EXPECT_EQ(olympics.teamsHashTable.get_size(), existingIds.size() - 1); // Check if teams hash table size is reduced
	EXPECT_EQ(olympics.teamsHashTable.find(teamId).status(), FAILURE); // Check if team is not found in the hash table
	EXPECT_EQ(olympics.teamsById.find(teamId).status(),
			  FAILURE); // Check if team is not found in the teamsById AVL tree
	EXPECT_EQ(olympics.teamsByStrength.find({teamId, 0}).status(),
			  FAILURE); // Check if team is not found in the teamsByStrength AVL tree
}

// Test case to remove a team with an invalid (<= 0) teamId
TEST_F(InitializedOlympicsTeamsOnly, RemoveInvalidTeamId)
{
	// Arrange
	const int invalidTeamId = 0;
	const auto expectedRes = INVALID_INPUT;
	
	// Act
	const auto res = olympics.remove_team(invalidTeamId);
	
	// Assert
	EXPECT_EQ(res, expectedRes) << errMsg(REMOVE_TEAM, invalidTeamId, expectedRes, res);
	// Check if no team was removed
	EXPECT_EQ(olympics.teamsHashTable.get_size(), existingIds.size()); // No team should be removed
}

// Test case to remove a non-existent team
TEST_F(InitializedOlympicsTeamsOnly, RemoveNonExistentTeam)
{
	// Arrange
	auto copy = existingIds;
	std::sort(copy.begin(), copy.end());
	const int nonExistentTeamId = copy.back() + 1; // bigger than max element
	const auto expectedRes = FAILURE;
	
	// Act
	const auto res = olympics.remove_team(nonExistentTeamId);
	
	// Assert
	EXPECT_EQ(res, expectedRes) << errMsg(REMOVE_TEAM, nonExistentTeamId, expectedRes, res);
	// Check if no team was removed
	EXPECT_EQ(olympics.teamsHashTable.get_size(), existingIds.size()); // No team should be removed
}

// Test case to remove all teams in the Olympics using valid teamIds
TEST_F(InitializedOlympicsTeamsOnly, RemoveAllTeams)
{
	// Arrange
	const auto expectedRes = SUCCESS;
	
	// Act & Assert
	for (int teamId : existingIds)
	{
		// Act
		const auto res = olympics.remove_team(teamId);
		
		// Assert
		EXPECT_EQ(res, expectedRes) << errMsg(REMOVE_TEAM, teamId, expectedRes, res);
		// Check if the team is actually removed
		EXPECT_EQ(olympics.teamsHashTable.find(teamId).status(),
				  FAILURE); // Check if team is not found in the hash table
		EXPECT_EQ(olympics.teamsById.find(teamId).status(),
				  FAILURE); // Check if team is not found in the teamsById AVL tree
		EXPECT_EQ(olympics.teamsByStrength.find({teamId, 0}).status(),
				  FAILURE); // Check if team is not found in the teamsByStrength AVL tree
	}
	
	// Check if all teams were successfully removed
	EXPECT_EQ(olympics.teamsHashTable.get_size(), 0); // Check if teams hash table size is zero
}

// Test case to add a player to an existing team with valid playerStrength
TEST_F(InitializedOlympicsTeamsOnly, AddPlayerToExistingTeam)
{
	// Arrange
	const int teamId = existingIds.front(); // Use the first team ID from existingIds
	const int playerStrength = 50; // Assuming player strength is 50
	const auto expectedRes = SUCCESS;
	
	// Act
	const auto res = olympics.add_player(teamId, playerStrength);
	// Assert
	EXPECT_EQ(res, expectedRes) << errMsg(ADD_PLAYER, std::make_pair(teamId, playerStrength), expectedRes, res);
	// Check if the player is added to the team
}

// Test case to add a player to a non-existent team
TEST_F(InitializedOlympicsTeamsOnly, AddPlayerToNonExistentTeam)
{
	// Arrange
	auto copy = existingIds;
	std::sort(copy.begin(), copy.end());
	const int nonExistentTeamId = copy.back() + 1; // Assuming team with ID larger than any in existingIds
	const int playerStrength = 50; // Assuming player strength is 50
	const auto expectedRes = FAILURE;
	
	// Act
	const auto res = olympics.add_player(nonExistentTeamId, playerStrength);
	
	// Assert
	EXPECT_EQ(res, expectedRes)
						<< errMsg(ADD_PLAYER, std::make_pair(nonExistentTeamId, playerStrength), expectedRes, res);
}

// Test case to add multiple players to a team
TEST_F(InitializedOlympicsTeamsOnly, AddMultiplePlayersToTeam)
{
	// Arrange
	const int teamId = existingIds.front(); // Use the first team ID from existingIds
	const int playerStrength1 = 50; // Assuming player strength is 50 for the first player
	const int playerStrength2 = 60; // Assuming player strength is 60 for the second player
	const auto expectedRes = SUCCESS;
	
	// Act
	const auto res1 = olympics.add_player(teamId, playerStrength1);
	const auto res2 = olympics.add_player(teamId, playerStrength2);
	
	// Assert
	EXPECT_EQ(res1, expectedRes) << errMsg(ADD_PLAYER, std::make_pair(teamId, playerStrength1), expectedRes, res1);
	EXPECT_EQ(res2, expectedRes) << errMsg(ADD_PLAYER, std::make_pair(teamId, playerStrength2), expectedRes, res2);
}

