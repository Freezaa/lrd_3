/*
 * vectormath.cpp
 *
 *  Created on: 08.12.2013
 *      Author: sebastianstauch
 */
#include <math.h>
#include "vectormath.h"

double length2D(double x1, double y1, double x2, double y2){
  return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
};


