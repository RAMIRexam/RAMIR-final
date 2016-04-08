#ifndef DATA_HPP
#define DATA_HPP

#include "Path.hpp"

#include <opencv2\core.hpp>

class Data
{
	public:
		Data();
		~Data();

		void addImage(Mat *img);
		Mat *getImage(int index = 0);
		Mat *getLastImage();
		void clearImages();

		void addPath(Path *path);
		vector<Path *> * getPathVector();

		//===============================
		void setFrameBlobVector(vector<Blob*> *blobVector);
		vector<Blob *> * getFrameBlobVector();
		void clearFrameBlobVector();
		//===============================





	private:
		int nImageCnt;

		vector<Mat *> *images;
		vector<Path *> *paths;
		vector<Blob *> *frameBlobs;
};

#endif // !DATA_HPP

