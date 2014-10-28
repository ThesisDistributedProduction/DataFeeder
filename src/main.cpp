
#if defined(_WIN32)
	#include <winsock2.h>
	#include <Windows.h>
#endif

#include "MongoDatabase.h"
#include "TurbineSamplePublisher.h"


using namespace std;

const string HOSTNAME = "localhost";

int main(int argc, char *argv[]) {
	try {
		MongoDatabase *db = MongoDatabase::getInstance( );
		MongoDatabase::setVerbose(true);
		db->connect(HOSTNAME);
		
		MongoPrepairedQuery query("03:00:00", "04:00:00");
		TurbineSamplePublisher reader;
		db->query(query, reader);

	} catch( const std::exception &e ) {
		cout << "caught " << e.what( ) << endl;
	}



}