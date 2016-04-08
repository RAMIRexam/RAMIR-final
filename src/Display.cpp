#include "Display.hpp"



//===============CONSTRUCTOR  DESTRUCTOR=====================

Display::Display()
{
	windowNamesVector = new vector<char *>();
	windowSizeVector = new vector<Size *>();
}


Display::~Display()
{
	destroyAllWindows();
	delete windowNamesVector;
	delete windowSizeVector;
}


//===========================================================





void Display::resizeImage(Mat * img)
{
	double multiplier = 1.0;

	int width = img->cols * multiplier;
	int height = img->rows * multiplier;

	Size size(width, height);
	resize(*img, *img, size);
}





/**
	Can show images in a 2x2 grid
*/
void Display::showImage(Mat * img, int windowIndex)
{
	if (windowSizeVector->at(windowIndex) == NULL)
	{
		Size *s = new Size(img->cols, img->rows);
		windowSizeVector->at(windowIndex) = s;
	}

	if (windowIndex % 2 == 0)
	{
		moveWindow(

			windowNamesVector->at(windowIndex),										//WINDOW NAME
			(5 + img->cols)*(windowIndex % 2),										//X
			(40 + windowSizeVector->at(0)->height)*(windowIndex / 2)				//Y

		); //Position windows in a gridlayout
	}
	else
	{
		moveWindow( 

			windowNamesVector->at(windowIndex),														//WINDOW NAME
			5 + windowSizeVector->at((windowIndex % 2) - 1 +  2 * (windowIndex / 2))->width,		//X
			(40 + windowSizeVector->at(0)->height)*(windowIndex / 2)								//Y

		); //Position windows in a gridlayout
	}
	
	imshow(windowNamesVector->at(windowIndex), *img);
}






void Display::createWindow(char *str)
{
	if (str != "Settings") //Exclude window named "Settings" from the positioning algorithm
	{
		namedWindow(str, WINDOW_AUTOSIZE);
		windowNamesVector->push_back(str);
		windowSizeVector->push_back(nullptr);
	} 
	else
	{
		namedWindow(str, WINDOW_NORMAL);
	}
}



//================================================================




