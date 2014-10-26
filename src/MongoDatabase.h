#pragma once

#include <cstddef>
#include <string>

#if defined(_WIN32)
	#include <winsock2.h>
	#include <windows.h>
#endif
#include <mongo/client/dbclient.h>
#include <mongo/bson/bson.h>

#include "MongoDatareader.h"
#include "MongoPrepariedQuery.h"


class MongoDatabase {
public:
	static MongoDatabase *getInstance( );
	static void setVerbose( bool value );

	void connect(std::string connectionString);
	MongoDatareader MongoDatabase::query(MongoPrepairedQuery query);
private:
	static MongoDatabase *instance;
	static bool isVerbose;

	MongoDatabase( );

};

