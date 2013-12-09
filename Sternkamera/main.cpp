/*
 * main.cpp
 *
 *  Created on: 05.12.2013
 *      Author: sebastianstauch
 */

#include "regionen.h"
#include <iostream>

int regionCnt = 2;
struct Sternhimmelmatrix{ int ObjId; int Helligkeit; int value;};

Sternhimmelmatrix shm[640][864];
Sternhimmelmatrix bhm[640][864];

void color_pixel_black(int x, int y){

	int offset = (y * 3) + (x  * 863* 3);
	myoutpic.seekp(offset + start, ios::beg);
	myoutpic.put(black);
	myoutpic.put(black);
	myoutpic.put(black);
}

void color_pixel_white(int x, int y){

	int offset = (y * 3)  + (x * 863 * 3);
	myoutpic.seekp(offset + start, ios::beg);
	myoutpic.put(white);
	myoutpic.put(white);
	myoutpic.put(white);
}

int get_pixel_color(struct pixel_color* pixel_rgb, int x, int y){

	mypic.open("bildout.bmp");
	int offset = (y * 3) + (x  * 863 * 3);
	mypic.seekg(offset+start, ios::beg);
	pixel_rgb->b = mypic.get();
	pixel_rgb->g = mypic.get();
	pixel_rgb->r = mypic.get();
	//mypic.read(&pixel_rgb->b, 1);
	//mypic.read(&pixel_rgb->g, 1);
	//mypic.read(&pixel_rgb->r, 1);
	/*printf("%d", (short unsigned int)pixel_rgb->b);
	printf("%d", (short unsigned int)pixel_rgb->g);
	printf("%d \n", (short unsigned int)pixel_rgb->r); */
	mypic.close();
	if (pixel_rgb->b != 0 || pixel_rgb->g != 0 || pixel_rgb->r != 0 ){
		return 1;
	}
	else {
		return 0;
	}
}

int size(){
	mypic.open("bild.BMP");
	for (int a = 0; a < 10; a++)
	{
		mypic.get();
	}
	start = mypic.get();	   			//Offset der Bilddaten in Byte vom Beginn der Datei an
	mypic.seekg(0, ios::end);   				//Suche Ende der Datei
	filesize = mypic.tellg();				//Dateigröße
	mypic.close();
	return 0;
}

int filter(){

	ofstream myfile;
	string filepath = "/Users/sebastianstauch/desktop/Matrix.txt";
    myfile.open (filepath.c_str(), ios::app);
	myoutpic.open("bildout.bmp");
	mypic.open("bild.BMP");
	pixel_color* color;
	color = &a_pixel_color;

	pixel_color* tr_hold;
	tr_hold = &treshold_ref;
	tr_hold->r = 0x0F;
	tr_hold->g = 0x11;
	tr_hold->b = 0x11;
	int sz = 0;
	int lines = 0;

	while (mypic.good())    				// Solange extrahierte Daten gültig
	{
		cnt += 3;
		color->r = mypic.get();
		color->g = mypic.get();
		color->b = mypic.get();
		//c = mypic.get();       				// lese Byte aus der Datei
		if (mypic.good())
			//printf("%d\n\r",(short unsigned int)c);		// Gebe Bytewert aus
		if ((cnt) > start&&(cnt) < filesize - 1)   		// Solange wir im Bildbereich sind
		{
			if ((short unsigned int)color->r >= tr_hold->r || (short unsigned int)color->g >= tr_hold->g || (short unsigned int)color->b >= tr_hold->b)
			{

				myoutpic.put(white);
				myoutpic.put(white);
				myoutpic.put(white);
				shm[lines][sz].value = 1;
				shm[lines][sz].Helligkeit = color->r;
				sz++;
				if((sz % 864) == 0){
				lines++;
				sz = 0;
				}

			}
			else{
				myoutpic.put(black);
				myoutpic.put(black);
				myoutpic.put(black);
				shm[lines][sz].value = 0;
				sz++;
				if((sz % 864) == 0){
					lines++;
					sz = 0;
				}
			}
		}
			else{
					myoutpic.put(color->r);
					myoutpic.put(color->g);
					myoutpic.put(color->b);
		    }
	}

	mypic.close();           // schließe Datei
	myoutpic.close();
	myfile.close();
	return 0;
}
// creates a matrixfile of the bmp
int matrixSternhimmel(){
	ofstream myfile;
	string filepath = "/Users/sebastianstauch/desktop/Matrix.txt";
    myfile.open (filepath.c_str(), ios::app);
		for (int a = 640; a > 0; a--){
			for (int b = 0; b < 864; b++){
				myfile  << shm[a][b].value;
				bhm[639-a][b].value = shm[a][b].value;
				bhm[639-a][b].Helligkeit = shm[a][b].Helligkeit;
			}
			myfile << "\n";
		}
	    myfile.close();
		return 0;
}

int recN(int a, int b){

	if (bhm[a-1][b-1].value == 1){ bhm[a-1][b-1].value = regionCnt; recN(a-1,b-1);}
	if (bhm[a][b-1].value == 1){bhm[a][b-1].value = regionCnt; recN(a,b-1);}
    if (bhm[a-1][b].value == 1){bhm[a-1][b].value = regionCnt; recN(a-1,b);}
    if (bhm[a-1][b+1].value == 1){bhm[a-1][b+1].value = regionCnt; recN(a-1,b+1);}
    if (bhm[a][b+1].value == 1){bhm[a][b+1].value = regionCnt; recN(a,b+1);}
    if (bhm[a+1][b-1].value == 1){bhm[a+1][b-1].value = regionCnt; recN(a+1,b-1);}
    if (bhm[a+1][b].value == 1){bhm[a+1][b].value = regionCnt; recN(a+1,b);}
    if (bhm[a+1][b+1].value == 1){bhm[a+1][b+1].value = regionCnt; recN(a+1,b+1);}

	return 0;
}

int regionenMakierung(){

	for (int a = 0; a < 640; a++){
		for (int b = 0;b < 864; b++){
			if (bhm[a][b].value == 1){
				bhm[a][b].value = regionCnt;
				recN(a,b);
				regionCnt++;
			}
		}
	}
	return 0;

}

int calcSchwerpunkt(){

	ofstream myfile;
	string filepath = "/Users/sebastianstauch/desktop/Sterne.txt";
	myfile.open (filepath.c_str(), ios::app);
	int starid = 0;
	double schwerpunktX;
	double schwerpunktY;
	double bright = 0;
	int lc = 0;

	myfile << "ID" << "    X" << "    Y"  << "   brightness" << "\n";

	for(int i = 2; i <= regionCnt; i++){
		starid = i-1;
		for (int a = 0; a < 640; a++){
			for (int b = 0;b < 864; b++){
				if (bhm[a][b].value == i){
					schwerpunktX += b;
					schwerpunktY += a;
					lc++;
					bright += bhm[a][b].Helligkeit;

				}
			}
		}

		schwerpunktX = schwerpunktX/lc;
		schwerpunktY = schwerpunktX/lc;
		bright = bright/lc;

		myfile << starid << "   " << schwerpunktX << " "  << schwerpunktY << " " << bright << "\n";
		schwerpunktX = 0;
		schwerpunktY = 0;
		bright = 0;
		lc = 0;
	}

    myfile.close();
	return 0;

}



int main() {


	size();
	filter();
	// create bhm Sternhimmelmatrix
	matrixSternhimmel();
	regionenMakierung();
	cout << regionCnt;
	calcSchwerpunkt();

	return 0;
}
