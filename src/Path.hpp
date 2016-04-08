#ifndef PATH_HPP
#define PATH_HPP

#include "Blob.hpp"

#include <vector>

using namespace std;

class Path
{
	public:
		Path();
		Path(Blob *blob);
		~Path();

		void addBlob(Blob *blob);
		vector<Blob *> * getBlobVector();
		Blob *getLastBlob();

		void setLife(int life);
		int getDuration();
		bool isAlive();

		void setHeading(Point2f heading);
		Point getHeading();

	private:
		Point2f heading;
		vector<Blob *> *blobs;
		Blob *ptrLastBlob;

		int nLife;
		int remainingLife;

};

#endif // !PATH_HPP
