#pragma once

#include <cstddef>
#include <string>

class MongoDatabase {
public:

	static MongoDatabase *getInstance( );

	void connect(std::string connectionString);

private:

	static MongoDatabase *instance;

	MongoDatabase( );

};

