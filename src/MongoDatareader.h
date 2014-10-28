#pragma once
#include <memory>
#include <thread>
#include <chrono>
#include <cstdint>

#if defined(_WIN32)
	#include <Windows.h>
#endif

#include <mongo/client/dbclient.h>
#include <mongo/bson/bson.h>



class MongoDatareader {
public:
	void processData(std::auto_ptr<mongo::DBClientCursor> cursor) {

		auto SLEEP_TIME = std::chrono::milliseconds(150);

		uint64_t lastTime;

		while( cursor->more( ) ) {
			mongo::BSONObj obj = cursor->next( );
			mongo::Date_t date = obj["TimeStamp"].Date();

			std::cout << date.toString() << "Timestamp: " << date.millis << std::endl;
			std::cout << "diff: " << date.millis - lastTime << std::endl;
			//std::cout << date.jsonString(mongo::JsonStringFormat::Strict, false) << std::endl;
			//std::cout << obj.jsonString(mongo::JsonStringFormat::JS, true, 1) << std::endl;
			lastTime = date.millis;
			std::this_thread::sleep_for(SLEEP_TIME);
		}


	}

	//void processData(std::auto_ptr<mongo::DBClientCursor> cursor) {
	//	std::cout << "Recived: " << cursor->itcount( ) << std::endl;

	//}
};