#include "MongoDatabase.h"

using namespace mongo;
using namespace std;

DBClientConnection MongoDatabase::db;
MongoDatabase *MongoDatabase::instance = NULL;
bool MongoDatabase::isVerbose = false;

MongoDatabase *MongoDatabase::getInstance( ) {
	if( instance == NULL ) {
		instance = new MongoDatabase( );
	}

	return instance;
}

void MongoDatabase::setVerbose(bool value) {
	isVerbose = value;
}

MongoDatabase::MongoDatabase( ) {
	mongo::client::initialize( );
}

void MongoDatabase::connect(string connectionString) {
	db.connect(connectionString);

	if( isVerbose ) {
		cout << "Connecting to database: " << connectionString << endl;
	}
}


//MongoDatareader MongoDatabase::query(MongoPrepairedQuery query) {
void MongoDatabase::query(MongoPrepairedQuery query, MongoDatareader &reader) {
	if( isVerbose ) {
		cout << "quering database with:" << query.getQuery()->toString() << endl;
	}

	auto_ptr<DBClientCursor> cursor = db.query(query.getCollection( ), (*query.getQuery()));
	reader.processData(cursor);
}

