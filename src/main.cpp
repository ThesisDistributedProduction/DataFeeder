
#include "MongoDatabase.h"

using namespace std;

const string HOSTNAME = "localhost";

int main(int argc, char *argv[]) {
	try {
		MongoDatabase *db = MongoDatabase::getInstance( );
		MongoDatabase::setVerbose(true);
		db->connect(HOSTNAME);

		MongoPrepairedQuery query("03:00:00", "04:00:00");
		db->query(query);

	} catch( const mongo::DBException &e ) {
		cout << "caught " << e.what( ) << endl;
	}



}