#pragma once

#include <ndds\ndds_cpp.h>
#include "DataInterface\TurbineSupport.h"

#include <stdexcept>

class DDS_Mannager {
public:
	static DDS_Mannager *getInstance( );

	TurbineDataWriter *getDataReader( );

private:
	static DDS_Mannager *instance;
	DDS_Mannager( );
	~DDS_Mannager( );

	DDSDomainParticipant* participant;
	DDSPublisher *publisher;
	DDSTopic *topic;
	//DDS_InstanceHandle_t handle;
};

