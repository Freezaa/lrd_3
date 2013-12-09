/*
 * regionen.h
 *
 *  Created on: 07.12.2013
 *      Author: sebastianstauch
 */

#ifndef REGIONEN_H_
#define REGIONEN_H_

#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

char c;
char rgb[3];
char white = 0xFF;
char black = 0x00;
//char threshold[3] = { 0x0F, 0x11, 0x11 };
int cnt = 0;
int start;
int filesize;
ifstream mypic;
ofstream myoutpic;

struct pixel_color{
	char r;
	char g;
	char b;
} a_pixel_color, treshold_ref;
char threshold[3] = { 0x0F, 0x11, 0x11 };

void color_pixel_black(int x, int y);
void color_pixel_white(int x, int y);
int get_pixel_color(struct pixel_color* pixel_rgb, int x, int y);
int size();
int filter();



#endif /* REGIONEN_H_ */
