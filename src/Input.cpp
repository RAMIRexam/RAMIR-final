#include "Input.hpp"




//===================CONSTRUCTOR  DESTRUCTOR===============


Input::Input()
{
	capture = new VideoCapture(0);
	videoStream = NULL;

	if (!capture->isOpened())
		throw "Could not open videocapture!";
}

Input::Input(int a)
{
	capture = new VideoCapture(a);
	videoStream = NULL;

	if (!capture->isOpened())
		throw "Could not open videocapture!";
}

Input::Input(char *a)
{
	capture = new VideoCapture(a);
	videoStream = a;

	if (!capture->isOpened())
		throw "Could not open videocapture!";
}


Input::~Input()
{
	delete capture;
}


//=========================================================



Mat Input::getImage()
{
	Mat frame;
	*capture >> frame;

	if (frame.empty() && *videoStream != NULL)
	{
		capture->release();
		capture->open(videoStream);

		*capture >> frame;
	}

	return frame;
}
