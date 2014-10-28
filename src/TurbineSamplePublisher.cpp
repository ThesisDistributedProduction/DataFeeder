#include "TurbineSamplePublisher.h"

#define DEFAULT_DOMAIN_ID           0
#define TOPIC_NAME                  "Cluster 1"

using namespace std;

TurbineSamplePublisher::TurbineSamplePublisher( ) {

	auto con = DDS_Mannager::getInstance( );
	writer = con->getDataReader( );
//	handle = writer->register_instance(*instance);
}


void TurbineSamplePublisher::processData(auto_ptr<mongo::DBClientCursor> cursor) {

	auto SLEEP_TIME = chrono::milliseconds(150);

	uint64_t lastTime = 0;

	while( cursor->more( ) ) {
		mongo::BSONObj obj = cursor->next( );
		mongo::Date_t date = obj["TimeStamp"].Date( );

		cout << date.toString( ) << "Timestamp: " << date.millis << endl;
		cout << "diff: " << date.millis - lastTime << endl;
		//cout << date.jsonString(mongo::JsonStringFormat::Strict, false) << endl;
		//cout << obj.jsonString(mongo::JsonStringFormat::JS, true, 1) << endl;

		auto instance = auto_ptr<Turbine>(new Turbine());
		instance->turbineId = obj["Turbine"].numberInt();
		instance->setPoint = obj["AssignPowerRef"].numberInt();
		instance->currentProduction = obj["ActivePower"].numberInt( );
		instance->maxProduction = obj["AvailablePower"].numberInt( );

		DDS_InstanceHandle_t instance_handle = writer->register_instance(*instance);

		writer->write(*instance, instance_handle);
		lastTime = date.millis;
		this_thread::sleep_for(SLEEP_TIME);
	}


}

TurbineSamplePublisher::~TurbineSamplePublisher( ) { }
