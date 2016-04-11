#ifndef PATH_HPP
#define PATH_HPP

#include "Blob.hpp"
#include "Definitions.hpp"

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

		bool isCountedCheck();
		void setCounted(bool counted);

		bool processed;							//DEBUG, Used in TRACKING_CC to make shure the path has been processed in some way at the end of the code

	private:
		Point2f heading;
		vector<Blob *> *blobs;
		Blob *ptrLastBlob;

		int nLife;
		int remainingLife;

		bool isCounted;							//True if the pedestrian has passed the countingline

		int curSOL;								//current Side Of Line, which side of the line the object currently is
		int staSOL;								//start Side Of Line, which side of the line the object was when it was first detected


};

#endif // !PATH_HPP
