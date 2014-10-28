#pragma once


#include <thread>
#include <chrono>
#include <cstdint>
#include <cstddef>

#include "MongoDatareader.h"
#include "MongoDatabase.h"


#include <ndds\ndds_cpp.h>
#include "DataInterface\TurbineSupport.h"


class TurbineSamplePublisher :
	public MongoDatareader {
public:
	TurbineSamplePublisher( );

	void processData(std::auto_ptr<mongo::DBClientCursor> cursor);

	~TurbineSamplePublisher( );
private:
	DDSDomainParticipant* participant;
	DDSPublisher *publisher;
	DDSTopic *topic;
	TurbineDataWriter *writer;
	//DDS_InstanceHandle_t handle;

};

