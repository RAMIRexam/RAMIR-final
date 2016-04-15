#include "Input.hpp"




//===================CONSTRUCTOR  DESTRUCTOR===============


Input::Input(bool rep)
{
	repeat = rep;										//true if the program shall loop forever
	capture = new VideoCapture(0);
	videoStream = NULL;

	if (!capture->isOpened())
		throw "Could not open videocapture!";
}

Input::Input(int camera, bool rep)
{
	repeat = rep;										//true if the program shall loop forever
	capture = new VideoCapture(camera);
	videoStream = NULL;

	if (!capture->isOpened())
		throw "Could not open videocapture!";
}

Input::Input(char *a, bool rep)
{
	repeat = rep;										//true if the program shall loop forever
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

	if (frame.empty() && *videoStream != NULL && repeat)				//Video has ended, shall repeat
	{
		capture->release();
		capture->open(videoStream);

		*capture >> frame;
	}

	return frame;
}
