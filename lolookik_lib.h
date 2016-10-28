#ifndef __LOLOOKIK_LIB_H__
#define __LOLOOKIK_LIB_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//opencv2.4.x legacy
#include <cxcore.h>
#include <cv.h>
#include <highgui.h>

#define __PI__ 3.14159265

/*****************************************************************************/
//round number
int round(double);

/*****************************************************************************/
//quick square root of a number, for Quake 3 Arena game engine
float Q_sqrt(float);

/*****************************************************************************/
//select an image region that share a value with the given coordinates
int bwselect(IplImage*, IplImage*, int, int);

/*****************************************************************************/
//creates a 1-pixel margin all around the image
void setBorderToWhite(IplImage*);

/*****************************************************************************/
//matlab's bwareaopen right from the net =)
void bwareaopen(IplImage*, int);


#endif //__LOLOOKIK_LIL_H__
