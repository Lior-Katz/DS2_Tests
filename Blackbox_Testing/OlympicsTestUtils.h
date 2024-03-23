//
// Created by Lior on 23/03/2024.
//

#ifndef DATASTRUCTURES2_OLYMPICSTESTUTILS_H
#define DATASTRUCTURES2_OLYMPICSTESTUTILS_H

#include <sstream>
#include <string>
#include "../utils.h"

// Enum for operation types
enum OpType
{
	ADD_TEAM, REMOVE_TEAM, ADD_PLAYER, REMOVE_PLAYER, PLAY_GAME, PLAY_TOURNAMENT
};

// Function to convert opType enum to string
std::string opTypeToString(OpType op)
{
	switch (op)
	{
		case ADD_TEAM:
			return "Add Team";
		case REMOVE_TEAM:
			return "Remove Team";
		case ADD_PLAYER:
			return "Add Player";
		case REMOVE_PLAYER:
			return "Remove Player";
		case PLAY_GAME:
			return "Play Game";
		case PLAY_TOURNAMENT:
			return "Play Tournament";
		default:
			return "Unknown Operation";
	}
}

template <class T, class S>
std::string& operator+(std::string& str, const std::pair<T, S>& p);

// string operator += with pair<T, S>
template <class T, class S>
std::string& operator+=(std::string& str, std::pair<T, S> p)
{
	str += std::to_string(p.first) + ", " + std::to_string(p.second);
	return str;
}

template <typename S>
std::string errMsg(OpType op, S operand, StatusType expected, StatusType actual);

// Function to generate error message for operations with expected and actual statuses and values
template <typename T, typename S>
std::string errMsg(OpType op, S operand, StatusType expected, StatusType actual, T valExp, T valActual);

// Function to generate error message for operations with only expected and actual values
template <typename T, typename S>
std::string errMsg(OpType op, S operand, T valExp, T valActual);

// Function to generate error message for operations with expected and actual statuses
template <typename S>
std::string errMsg(OpType op, S operand, StatusType expected, StatusType actual)
{
	std::string string;
	string += opTypeToString(op) +  " of ";
	string += operand;
	string += " failed.\n";
	if (expected != actual)
	{
		string + "Expected result " + str(expected) + ", Actual: " + str(actual) + "\n";
	}
	return string;
}

// Function to generate error message for operations with expected and actual statuses and values
template <typename T, typename S>
std::string errMsg(OpType op, S operand, StatusType expected, StatusType actual, T valExp, T valActual)
{
	std::string str;
	str += errMsg(op, operand, expected, actual);
	if (valExp != valActual)
	{
		str += "Expected value: " + valExp + ", Actual: " + valActual + "\n";
	}
	return str;
}

// Function to generate error message for operations with only expected and actual values
template <typename T, typename S>
std::string errMsg(OpType op, S operand, T valExp, T valActual)
{
	std::string str;
	str += opTypeToString(op) + " of " + operand + " failed.\n";
	str += "Expected value: " + valExp + ", Actual: " + valActual + "\n";
	return str;
}

//template <class T, class S>
//std::string& operator+=(std::string& str, const std::pair<T, S>& p)
//{
//	str += p.first + ", " + p.second;
//	return str;
//}




#endif //DATASTRUCTURES2_OLYMPICSTESTUTILS_H
