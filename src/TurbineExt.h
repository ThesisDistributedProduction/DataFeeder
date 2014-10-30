#pragma once

#include "DataInterface\Turbine.h"
#include <string>
#include <cstdio>

class TurbineExt : public Turbine {
public:
	std::string toString( ) {
		const int BUFFER_SIZE = 512;
		char buffer[BUFFER_SIZE];

		sprintf(
			buffer, 
			"TurbineID: %i with setpoint %i\nProducing: %i of max: %i", 
			this->turbineId, this->setPoint, this->currentProduction, this->maxProduction);

		return std::string(buffer);
	}

};




