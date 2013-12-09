#ifndef API
#define API


#include <my_global.h>
#include <mysql.h>
#include <stdio.h>


//using namespace std;

typedef struct angle angle_type;
struct angle{
	int id1;
	int id2;
	int id3;
	double beta;
	double alpha1;
	double alpha2;
};

typedef struct coordinate coordinate_type;
struct coordinate{
	double id;
	double x;
	double y; 
	double z;
	double mag;
};

char query[1024];
MYSQL *con;

void insert_into_angles(angle_type* ang);
void insert_into_coordinates(coordinate_type* coord);
int connect_db();
void disconnect_db();
int create_database();
void create_tables();
void fill_database();



#endif