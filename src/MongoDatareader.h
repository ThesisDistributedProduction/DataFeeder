#pragma once
#include <memory>

#include "IncludeMongo.h"


class MongoDatareader {
public:

	virtual void giveDataCursor(std::auto_ptr<mongo::DBClientCursor> cursor) = 0;

};