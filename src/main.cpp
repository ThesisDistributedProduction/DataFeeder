
#include <vector>
#include <memory>

#include "MongoDatabase.h"
#include "TurbineSamplePublisher.h"

using namespace std;

#define HOSTNAME "localhost"

int main(int argc, char *argv[]) {
	try {
		MongoDatabase *db = MongoDatabase::getInstance( );
		MongoDatabase::setVerbose(true);
		db->connect(HOSTNAME);
		string startTime = "16:00:00";
		string stopTime  = "17:00:00";

		TurbineSamplePublisher reader(true);
		vector<string> collections = { "Turbine3000363Log", "Turbine3000364Log", "Turbine3000365Log", "Turbine3000366Log" };

		MongoPrepairedQuery query(collections[0], startTime, stopTime);
		db->query(query, reader);

		reader.processData( );
		
	} catch( const std::exception &e ) {
		cout << "caught " << e.what( ) << endl;
	}

}