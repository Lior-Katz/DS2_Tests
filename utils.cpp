//
// Created by Lior on 16/03/2024.
//

#include "utils.h"

std::string str(StatusType status)
{
	return status_type_strings[static_cast<int>(status)];
}
