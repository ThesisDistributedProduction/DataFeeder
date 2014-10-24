#include "MongoDatabase.h"

#include <WinSock2.h>
#include <mongo/client/dbclient.h>


MongoDatabase *MongoDatabase::instance = NULL;

MongoDatabase *MongoDatabase::getInstance( ) {
	if( instance == NULL ) {
		instance = new MongoDatabase();
	}
	return instance;
}


void MongoDatabase::connect(std::string connectionString) {

}


MongoDatabase::MongoDatabase( ) {
	mongo::client::initialize( );
}