/*
 * Integer.cpp
 *
 *  Created on: 14 сент. 2020 г.
 *      Author: borzenkov
 */

#include <iostream>
#include "Integer.h"

Integer::Integer():value(0)
{
	std::cout << "Create new Integer" << std::endl;
	PrintValue();
}

Integer::~Integer() {
	// TODO Auto-generated destructor stub
}

