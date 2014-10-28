#include "TurbineSamplePublisher.h"

#define DEFAULT_DOMAIN_ID           0
#define TOPIC_NAME                  "Cluster 1"
#define WRITER_HANDLE								"SOME_NAME"

using namespace std;

TurbineSamplePublisher::TurbineSamplePublisher( ) {
	auto factory = DDSDomainParticipantFactory::get_instance( );

	participant = factory->create_participant(
		DEFAULT_DOMAIN_ID,
		DDS_PARTICIPANT_QOS_DEFAULT,
		NULL,                    // no listener
		DDS_STATUS_MASK_NONE);   // no listener callbacks

	if( participant == NULL ) {
		throw new runtime_error("! Unable to create DomainParticipant");
	}

	publisher = participant->create_publisher(
		DDS_PUBLISHER_QOS_DEFAULT,
		NULL,										 // no listener
		DDS_STATUS_MASK_NONE);	 // no listener callbacks
	if( publisher == NULL ) {
		throw runtime_error("create_publisher error");
	}

	auto retcode = TurbineTypeSupport::register_type(
		participant, 
		TurbineTypeSupport::get_type_name( ));
	if( retcode != DDS_RETCODE_OK ) {
		throw runtime_error("register_type error " + retcode);
	}

	topic = participant->create_topic(
		TOPIC_NAME,
		TurbineTypeSupport::get_type_name( ),
		DDS_TOPIC_QOS_DEFAULT,
		NULL,                    // no listener
		DDS_STATUS_MASK_NONE);    // no listener callbacks
	if( topic == NULL ) {
		throw runtime_error("! Unable to create topic");
	}

	DDSDataWriter *dataWriter = participant->create_datawriter(
		topic,
		DDS_DATAWRITER_QOS_DEFAULT,
		NULL,           /* listener */
		DDS_STATUS_MASK_NONE);
	if( dataWriter == NULL ) {
		throw runtime_error("Unable to create DataWriter");
	}

	writer = TurbineDataWriter::narrow(dataWriter);

//	handle = writer->register_instance(*instance);
}


void TurbineSamplePublisher::processData(auto_ptr<mongo::DBClientCursor> cursor) {

	auto SLEEP_TIME = chrono::milliseconds(150);

	uint64_t lastTime;

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

//void TurbineSamplePublisher::processData(auto_ptr<mongo::DBClientCursor> cursor) {
//	cout << "Recived: " << cursor->itcount( ) << endl;

//}


TurbineSamplePublisher::~TurbineSamplePublisher( ) {
	//auto factory = DDSDomainParticipantFactory::get_instance( );
	//participant->delete_contained_entities( );

	//factory->delete_participant(participant);
}
