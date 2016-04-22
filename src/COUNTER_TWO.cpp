#include "COUNTER_TWO.hpp"


//=====================CONSTRUCTOR DESTRUCTOR======================
COUNTER_TWO::COUNTER_TWO(Data * data) : AbstractCounting(data)
{
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

		if (p->getHeading().y < 0 && !blobs->at(size - 1)->isEmpty() && !blobs->at(size - 2)->isEmpty()		//CHECKS IF BLOB HAS PASSED FROM RIGHT TO LEFT OVER THE COUNTING LINE
			&& blobs->at(size - 1)->getCentroid().y <= (2 * ptrData->getLastImage()->rows) / 5
			&& blobs->at(size - 2)->getCentroid().y > (2 * ptrData->getLastImage()->rows) / 5)
		{
			ptrData->upCnt++;
		}
		else if (p->getHeading().y > 0 && !blobs->at(size - 1)->isEmpty() && !blobs->at(size - 2)->isEmpty()	//CHECKS IF BLOB HAS PASSED FROM LEFT TO RIGHT OVER THE COUNTING LINE
			&& blobs->at(size - 1)->getCentroid().y >= (3 * ptrData->getLastImage()->rows) / 5
			&& blobs->at(size - 2)->getCentroid().y < (3 * ptrData->getLastImage()->rows) / 5)
		{
			ptrData->downCnt++;
		}
	}

	//DRAW COUNTERS ON IMAGE
	putText(*out, Tools::int2String(ptrData->upCnt), Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
	putText(*out, Tools::int2String(ptrData->downCnt), Point(ptrData->getLastImage()->cols - 50, ptrData->getLastImage()->rows - 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);

	//DRAW COUNTING LINES
	line(*out, Point(0, (2 * out->rows) / 5), Point(out->cols, (2 * out->rows) / 5), Scalar(255, 0, 0), 2);
	line(*out, Point(0, (3 * out->rows) / 5), Point(out->cols, (3 * out->rows) / 5), Scalar(255, 0, 0), 2);

	ptrData->addImage(out);
}


void COUNTER_TWO::saveSettings()
{
}
