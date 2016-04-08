#include "COUNTER_TWO.hpp"


//=====================CONSTRUCTOR DESTRUCTOR======================
COUNTER_TWO::COUNTER_TWO(Data * data) : AbstractCounting(data)
{
	left2Right = 0;
	right2Left = 0;
}


COUNTER_TWO::~COUNTER_TWO()
{
}
//=================================================================


void COUNTER_TWO::count()
{
	int size;
	vector<Blob *> *blobs;
	vector<Path *> *paths = ptrData->getPathVector();

	ptrData->getLastImage()->copyTo(*out);

	for (Path *p : *paths)
	{
		blobs = p->getBlobVector();
		size = blobs->size();

		if (p->getHeading().x < 0 && !blobs->at(size - 1)->isEmpty() && !blobs->at(size - 2)->isEmpty()		//CHECKS IF BLOB HAS PASSED FROM RIGHT TO LEFT OVER THE COUNTING LINE
			&& blobs->at(size - 1)->getCentroid().x <= ptrData->getLastImage()->cols / 3
			&& blobs->at(size - 2)->getCentroid().x >= ptrData->getLastImage()->cols / 3)
		{
			right2Left++;
		}
		else if (p->getHeading().x > 0 && !blobs->at(size - 1)->isEmpty() && !blobs->at(size - 2)->isEmpty()	//CHECKS IF BLOB HAS PASSED FROM LEFT TO RIGHT OVER THE COUNTING LINE
			&& blobs->at(size - 1)->getCentroid().x >= 2 * ptrData->getLastImage()->cols / 3
			&& blobs->at(size - 2)->getCentroid().x <= 2 * ptrData->getLastImage()->cols / 3)
		{
			left2Right++;
		}
	}

	//DRAW COUNTERS ON IMAGE
	putText(*out, Tools::int2String(right2Left), Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
	putText(*out, Tools::int2String(left2Right), Point(ptrData->getLastImage()->cols - 50, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);

	//DRAW COUNTING LINES
	line(*out, Point(out->cols / 3, 0), Point(out->cols / 3, out->rows), Scalar(255, 0, 0), 2);
	line(*out, Point(2 * out->cols / 3, 0), Point(2 * out->cols / 3, out->rows), Scalar(255, 0, 0), 2);


	ptrData->addImage(out);
}

void COUNTER_TWO::saveSettings()
{
}
