#pragma once


#include <thread>
#include <chrono>
#include <cstdint>

#include "MongoDatareader.h"
#include "MongoDatabase.h"


#include <ndds\ndds_cpp.h>


class TurbineSamplePublisher :
	public MongoDatareader {
public:
	TurbineSamplePublisher( );

	void processData(std::auto_ptr<mongo::DBClientCursor> cursor);

	~TurbineSamplePublisher( );
private:
	DDSDomainParticipant* participant;
	DDSTopic *topic;
	DDSKeyedStringDataWriter * writer;
	DDS_InstanceHandle_t handle;

};

