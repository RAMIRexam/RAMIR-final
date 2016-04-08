#ifndef INPUT_HPP
#define INPUT_HPP

#include <opencv2\opencv.hpp>

using namespace cv;

class Input
{
	public:
		Input();		//OPEN DEFAULT CAMERA
		Input(int);		//OPEN CAMERA
		Input(char *);	//OPEN VIDEOFILE
		~Input();

		Mat getImage();

	private:
		char *videoStream;
		VideoCapture *capture;
};

#endif // !INPUT_HPP