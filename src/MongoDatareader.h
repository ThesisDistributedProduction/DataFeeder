#pragma once
#include <memory>

#include "IncludeMongo.h"


class MongoDatareader {
public:

	virtual void processData(std::auto_ptr<mongo::DBClientCursor> cursor) = 0;

};