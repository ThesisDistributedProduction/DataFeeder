#include "TurbineSamplePublisher.h"

#define DEFAULT_DOMAIN_ID           0
#define TOPIC_NAME                  "News Example"
#define WRITER_HANDLE								"SOME_NAME"



TurbineSamplePublisher::TurbineSamplePublisher( ) {
	auto factory = DDSDomainParticipantFactory::get_instance( );

	participant = factory->create_participant(
		DEFAULT_DOMAIN_ID,
		DDS_PARTICIPANT_QOS_DEFAULT,
		NULL,                    // no listener
		DDS_STATUS_MASK_NONE);   // no listener callbacks

	if( participant == NULL ) {
		throw new std::runtime_error("! Unable to create DomainParticipant");
	}

	topic = participant->create_topic(
		TOPIC_NAME,
		DDSKeyedStringTypeSupport::get_type_name( ),
		DDS_TOPIC_QOS_DEFAULT,
		NULL,                    // no listener
		DDS_STATUS_MASK_NONE);    // no listener callbacks
	if( topic == NULL ) {
		throw std::runtime_error("! Unable to create topic");
	}

	DDSDataWriter* dataWriter = participant->create_datawriter(
		topic,
		DDS_DATAWRITER_QOS_DEFAULT,
		NULL,           /* listener */
		DDS_STATUS_MASK_NONE);
	if( dataWriter == NULL ) {
		throw std::runtime_error("Unable to create DataWriter");
	}

	writer = DDSKeyedStringDataWriter::narrow(dataWriter);

	handle = writer->register_instance(WRITER_HANDLE);
}


void TurbineSamplePublisher::processData(std::auto_ptr<mongo::DBClientCursor> cursor) {

	auto SLEEP_TIME = std::chrono::milliseconds(150);

	uint64_t lastTime;

	while( cursor->more( ) ) {
		mongo::BSONObj obj = cursor->next( );
		mongo::Date_t date = obj["TimeStamp"].Date( );

		std::cout << date.toString( ) << "Timestamp: " << date.millis << std::endl;
		std::cout << "diff: " << date.millis - lastTime << std::endl;
		//std::cout << date.jsonString(mongo::JsonStringFormat::Strict, false) << std::endl;
		//std::cout << obj.jsonString(mongo::JsonStringFormat::JS, true, 1) << std::endl;

		writer->write("Timestamp", date.toString( ).c_str( ), handle);
		lastTime = date.millis;
		std::this_thread::sleep_for(SLEEP_TIME);
	}


}

//void TurbineSamplePublisher::processData(std::auto_ptr<mongo::DBClientCursor> cursor) {
//	std::cout << "Recived: " << cursor->itcount( ) << std::endl;

//}


TurbineSamplePublisher::~TurbineSamplePublisher( ) { }
