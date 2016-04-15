#ifndef INPUT_HPP
#define INPUT_HPP

#include <opencv2\opencv.hpp>

using namespace cv;

class Input
{
	public:
		Input(bool repeat = true);		//OPEN DEFAULT CAMERA
		Input(int camera, bool repeat = true);		//OPEN CAMERA
		Input(char * filename, bool repeat = true);	//OPEN VIDEOFILE
		~Input();

		Mat getImage();

	private:
		bool repeat;
		char *videoStream;
		VideoCapture *capture;
};

#endif // !INPUT_HPP