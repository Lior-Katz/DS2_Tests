//
// Created by Lior on 16/03/2024.
//

#ifndef DATASTRUCTURES2_UTILS_H
#define DATASTRUCTURES2_UTILS_H

#include "../wet2util.h"

#define NEW_STATUS_TYPE \
X(SUCCESS, "Success") \
X(ALLOCATION_ERROR, "Allocation Error") \
X(INVALID_INPUT, "Invalid Input") \
X(FAILURE, "Failure")

#define X(name, str) name,
enum newStatusType
{
	NEW_STATUS_TYPE
};
#undef X

#define X(name, str) str,
constexpr const char* status_type_strings[] = {NEW_STATUS_TYPE};
#undef X

std::string str(StatusType status);

#define SUCCESS (StatusType::SUCCESS)
#define FAILURE (StatusType::FAILURE)
#define ALLOCATION_ERROR (StatusType::ALLOCATION_ERROR)
#define INVALID_INPUT (StatusType::INVALID_INPUT)
#endif //DATASTRUCTURES2_UTILS_H
