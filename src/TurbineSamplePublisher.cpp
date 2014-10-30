#include "TurbineSamplePublisher.h"

using namespace std;

TurbineSamplePublisher::TurbineSamplePublisher(bool verbose) {
	this->verbose = verbose;
	auto con = DDS_Mannager::getInstance();
	writer = con->getDataReader( );
//	handle = writer->register_instance(*instance);
}

void TurbineSamplePublisher::giveDataCursor(auto_ptr<mongo::DBClientCursor> cursor) {
	this->cursor = cursor;
}


void TurbineSamplePublisher::processData() {
	auto SLEEP_TIME = chrono::milliseconds(150);

	uint64_t lastTime = 0;

	while( cursor->more( ) ) {
		mongo::BSONObj obj = cursor->next( );
		mongo::Date_t date = obj["TimeStamp"].Date( );

		auto instance = auto_ptr<TurbineExt>(new TurbineExt( ));
		instance->turbineId = obj["Turbine"].numberInt( ) - 3000362;
		instance->setPoint = obj["AssignPowerRef"].numberInt( );
		instance->currentProduction = obj["ActivePower"].numberInt( );
		instance->maxProduction = obj["AvailablePower"].numberInt( );

		if( verbose ) {
			cout << date.toString( ) << "Timestamp: " << date.millis << endl;
			cout << "diff: " << date.millis - lastTime << endl;
			cout << instance->toString( ) << endl;
			cout << endl;
			//cout << date.jsonString(mongo::JsonStringFormat::Strict, false) << endl;
			//cout << obj.jsonString(mongo::JsonStringFormat::JS, true, 1) << endl;
		}

		DDS_InstanceHandle_t instance_handle = writer->register_instance(*instance);

		writer->write(*instance, instance_handle);
		lastTime = date.millis;
		this_thread::sleep_for(SLEEP_TIME);
	}
}
