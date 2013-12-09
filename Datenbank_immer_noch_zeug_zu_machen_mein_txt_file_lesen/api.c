#include "api.h"

int create_database()
{
	if (mysql_real_connect(con, "127.0.0.1", "root", "root_pswd",
		NULL, 3306, NULL, 0) == NULL)
	{
		printf("%s\n", mysql_error(con));
		mysql_close(con);
		exit(0);
	}

	if (mysql_query(con, "CREATE DATABASE stars"))
	{
		printf("%s\n", mysql_error(con));
		mysql_close(con);
		exit(0);
	}

	

	mysql_close(con);
	return 0;
}


int connect_db()
{
	if (mysql_real_connect(con, "127.0.0.1", "test", "test123", "stars", 3306, NULL, 0) == NULL)
	{
		printf("error");
		return 1;
	}
	return 0;
}

void disconnect_db()
{
	mysql_close(con);
}

void create_tables()
{
	connect_db();
	mysql_query(con, "CREATE TABLE angles(Id1 INT, Id2 INT, Id3 INT, beta DOUBLE, alpha1 DOUBLE, alpha2 DOUBLE)");
	mysql_query(con, "CREATE TABLE coordinates(Id DOUBLE,x DOUBLE,y DOUBLE, z DOUBLE, mag DOUBLE)");
}


void insert_into_angles(angle_type* ang)
{
	sprintf(query, "INSERT INTO angles VALUES(%d, %d, %d, %le, %le, %le)", ang->id1, ang->id2, ang->id3, ang->beta, ang->alpha1, ang->alpha2);
	mysql_query(con, query);
}

void insert_into_coordinates(coordinate_type* coord)
{
	sprintf(query, "INSERT INTO coordinates VALUES(%le, %le, %le, %le, %le)", coord->id, coord->x, coord->y, coord->z, coord->mag);
	mysql_query(con, query);
}

void fill_database()
{
	
	coordinate_type coord1;
	coordinate_type *c = &coord1;
	c->z = 0.0;

	FILE *catalog;

	catalog = fopen("hip_red_1.txt", "r");

	while (feof(catalog) == 0){
		fscanf(catalog, "%le", &c->id);
		fscanf(catalog, "%le", &c->x);
		fscanf(catalog, "%le", &c->y);
		fscanf(catalog, "%le", &c->mag);
		/*
		printf("id: %le \n", c->id);
		printf("x: %le \n", c->x);
		printf("y: %le \n", c->y);
		printf("mag: %le \n", c->mag);*/
		insert_into_coordinates(c);
	}

	fclose(catalog);
}

int main()
{

	con = mysql_init(NULL);
	create_tables();
    fill_database();


	disconnect_db();
	return 0;
	

	//create_database();
	
}