#pragma once

#include <memory>
#include <cstdlib>
#include <boost/date_time/posix_time/posix_time.hpp>

class MongoPrepairedQuery {
public:
	const std::string DB = "turbineLog";
	const std::string TIME_STAMP_FIELD = "TimeStamp";
	const std::string FIXED_DATE = "2014-10-18";

	MongoPrepairedQuery(std::string collection, std::string timeFrom, std::string timeTo) {
		this->collection = collection;
		timeStampLow = MakeTime(FIXED_DATE + " " + timeFrom + ".000");
		timeStampHigh = MakeTime(FIXED_DATE + " " + timeTo + ".000");
	}

	std::auto_ptr<mongo::Query> getQuery( ) {
		mongo::BSONObj json = BSON(TIME_STAMP_FIELD << mongo::GTE << timeStampLow << mongo::LT << timeStampHigh);
		
		mongo::Query q(json);
		q.sort(TIME_STAMP_FIELD);

		return std::auto_ptr<mongo::Query>(new mongo::Query(q));
	}

	std::string getCollection( ) {
		return DB + "." + collection;
	}

private:

	mongo::Date_t MakeTime(std::string str) {
		boost::posix_time::ptime time(boost::posix_time::time_from_string(str));
		return mongo::Date_t(mktime(&to_tm(time)) * 1000);
	}

	std::string collection;
	mongo::Query query;
	mongo::Date_t timeStampLow;
	mongo::Date_t timeStampHigh;

};