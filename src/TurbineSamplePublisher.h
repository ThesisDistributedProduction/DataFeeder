#pragma once


#include <thread>
#include <chrono>
#include <cstdint>
#include <cstddef>

#include "MongoDatareader.h"
#include "MongoDatabase.h"

#include "DDS_Mannager.h"

class TurbineSamplePublisher :
	public MongoDatareader {
public:
	TurbineSamplePublisher( );

	void processData(std::auto_ptr<mongo::DBClientCursor> cursor);

	~TurbineSamplePublisher( );
private:
	TurbineDataWriter *writer;

};

