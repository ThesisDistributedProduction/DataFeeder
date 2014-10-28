#include "DDS_Mannager.h"

#define DEFAULT_DOMAIN_ID           0
#define TOPIC_NAME                  "Cluster 1"


using namespace std;

DDS_Mannager *DDS_Mannager::instance = NULL;

DDS_Mannager *DDS_Mannager::getInstance( ) {
	if( instance == NULL ) {
		instance = new DDS_Mannager( );
	}

	return instance;
}

DDS_Mannager::DDS_Mannager( ) {
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

}

TurbineDataWriter *DDS_Mannager::getDataReader( ) {
	DDSDataWriter *dataWriter = participant->create_datawriter(
		topic,
		DDS_DATAWRITER_QOS_DEFAULT,
		NULL,           /* listener */
		DDS_STATUS_MASK_NONE);
	if( dataWriter == NULL ) {
		throw runtime_error("Unable to create DataWriter");
	}
	return TurbineDataWriter::narrow(dataWriter);
}


DDS_Mannager::~DDS_Mannager( ) { 
	auto factory = DDSDomainParticipantFactory::get_instance( );
	participant->delete_contained_entities( );

	factory->delete_participant(participant);
}
