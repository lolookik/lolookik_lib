#include "lolookik_lib.h"


/*****************************************************************************/
//round number
int round(double a)
{
	int a;
	//b>0?((((int)(10*b)%10)>5?ceil(b):floor(b)):(((int)(-10*b)%10)>5?ceil(-1*b):floor(-1*b)));//O_o' scratching my eyes!
	if(b>0)
		a = ((int)(10*b)%10)>5?ceil(b):floor(b);
	else
	{
		b = -b;
		a = ((int)(10*b)%10)>5?ceil(b):floor(b);
		a = -a;
	}

	return a;
}

/*****************************************************************************/
//quick square root of a number, for Quake 3 Arena game engine
float Q_sqrt( float number )
{
  long i;
  float x2, y;
  const float threehalfs = 1.5F;
 
  x2 = number * 0.5F;
  y = number;
  i = * ( long * ) &y; // evil floating point bit level hacking 
  i = 0x5f3759df - ( i >> 1 ); // what the fuck? 
  y = * ( float * ) &i;
  y = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration 
  // y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed 
 
  #ifndef Q3_VM
  #ifdef __linux__
  assert( !isnan(y) ); // bk010122 - FPE?  
  #endif
  #endif
  return number*y;
}

/*****************************************************************************/
//like matlab's
int bwselect(IplImage* src, IplImage* dest, int x, int y)
{
	int i, j, w, h;
	int val;
	CvPoint seed;
	CvScalar PouetPouet;

	w = dest->width;
	h = dest->height;

	seed.x=x;
	seed.y=y;
	cvCopy(src, dest);

	PouetPouet.val[0] = 55;
	cvFloodFill(dest, seed, PouetPouet);

	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			val = cvGetReal2D(dest, i, j);
			if(val==55)
				cvSetReal2D(dest, i, j, 255);
			else
				cvSetReal2D(dest, i, j, 0);
		}
	}

	return 0;
}


/*****************************************************************************/
//the rectangular bounding box of a specific shape
int bounding_box(IplImage* image, int* X, int* Y)
{
	CvSeq *seq;
	CvMemStorage *mem;
	CvRect rectBox;
	IplImage *buf;
	//IplImage *bufFiltered;
	
	mem = cvCreateMemStorage();
	buf = cvCreateImage(cvSize(image->width, image->height), image->depth, 1);
	cvCopy(image, buf);
	cvFindContours ( buf, mem, &seq, sizeof( CvContour ), CV_RETR_EXTERNAL );
	rectBox = cvBoundingRect( seq);
	seq = seq->h_next;

	cvReleaseImage(&buf);
	cvReleaseMemStorage ( &mem );
	X[0] = rectBox.x;
	X[1] = rectBox.x+rectBox.width;
	Y[0] = rectBox.y;
	Y[1] = rectBox.y+rectBox.height;

	return 0;
}

/*****************************************************************************/
/**
* OpenCV equivalent of Matlab's bwareaopen.
* image must be 8 bits, 1 channel, black and white (objects)
* with values 0 and 255 respectively
*/
void bwareaopen(IplImage* image, int size)
{
	CvMemStorage *storage;
	CvSeq *contour;
	IplImage *input;
	double area;

	if (image == NULL || size == 0)
		return;

	input = cvCloneImage(image);
	storage = cvCreateMemStorage(0);

	cvFindContours(input, storage, &contour, sizeof (CvContour),
		CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

	while(contour)
	{
		area = cvContourArea(contour, CV_WHOLE_SEQ, 1);

		if (-size <= area && area <= 0)
		{
			// removes white dots
			cvDrawContours(image, contour, CV_RGB(0,0,0), CV_RGB(0,0,0),
				-1, CV_FILLED, 8, cvPoint(0, 0));
		}
		/*else if (0 < area && area <= size)
		{
		// fills in black holes
		CV_RGB(0xff,0xff,0xff), -1, CV_FILLED, 8, cvPoint(0,0));
		}*/

		contour = contour->h_next;
	}

	cvReleaseMemStorage(&storage);
	cvReleaseImage(&input);
}	
