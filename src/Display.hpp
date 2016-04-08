#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <vector>

#include <opencv2\opencv.hpp>

using namespace cv;
using namespace std;

class Display
{
	public:
		Display();
		~Display();

		void resizeImage(Mat * img);
		void showImage(Mat * img, int windowIndex);
		void createWindow(char * str);


	private:
		vector<char *> *windowNamesVector;
		vector<Size *> *windowSizeVector;
};

#endif // !DISPLAY_HPP
