#pragma once


#include <thread>
#include <chrono>
#include <cstdint>
#include <cstddef>
#include <memory>

#include "MongoDatareader.h"
#include "MongoDatabase.h"

#include "DDS_Mannager.h"
#include "TurbineExt.h"

class TurbineSamplePublisher :
	public MongoDatareader {
public:
	TurbineSamplePublisher(bool verbose = false);

	void giveDataCursor(std::auto_ptr<mongo::DBClientCursor> cursor);
	void processData( );
private:

	TurbineDataWriter *writer;
	bool verbose;
	std::auto_ptr<mongo::DBClientCursor> cursor;

};

