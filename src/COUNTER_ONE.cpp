#include "COUNTER_ONE.hpp"


//=====================CONSTRUCTOR DESTRUCTOR======================
COUNTER_ONE::COUNTER_ONE(Data *data) : AbstractCounting(data)
{
	textColorLeftB = rand() % 255;
	textColorLeftG = rand() % 255;
	textColorLeftR = rand() % 255;

	textColorRightB = rand() % 255;
	textColorRightG = rand() % 255;
	textColorRightR = rand() % 255;
}




COUNTER_ONE::~COUNTER_ONE()
{
}
//=================================================================




void COUNTER_ONE::count()
{
	int size;
	vector<Blob *> *blobs;
	vector<Path *> *paths = ptrData->getPathVector();

	ptrData->getLastImage()->copyTo(*out);


	//CHECK IF BLOBS HAVE CROSSED THE COUNTING LINE
	for (Path *p : *paths)
	{	
		blobs = p->getBlobVector();
		size = blobs->size();

		if (p->getHeading().y < 0 && !blobs->at(size - 1)->isEmpty() && !blobs->at(size - 2)->isEmpty()		//CHECKS IF BLOB HAS PASSED FROM RIGHT TO LEFT OVER THE COUNTING LINE
			&& blobs->at(size - 1)->getCentroid().y <= ptrData->getLastImage()->rows / 2 
			&& blobs->at(size - 2)->getCentroid().y > ptrData->getLastImage()->rows / 2)
		{
			ptrData->upCnt++;
			p->setCounted(true);

			textColorRightB = rand() % 255;
			textColorRightG = rand() % 255;
			textColorRightR = rand() % 255;
		}
		else if (p->getHeading().y > 0 && !blobs->at(size - 1)->isEmpty() && !blobs->at(size - 2)->isEmpty()	//CHECKS IF BLOB HAS PASSED FROM LEFT TO RIGHT OVER THE COUNTING LINE
			&& blobs->at(size - 1)->getCentroid().y >= ptrData->getLastImage()->rows / 2
			&& blobs->at(size - 2)->getCentroid().y < ptrData->getLastImage()->rows / 2)
		{
			ptrData->downCnt++;
			p->setCounted(true);

			textColorLeftB = rand() % 255;
			textColorLeftG = rand() % 255;
			textColorLeftR = rand() % 255;
		}
	}
	
	//DRAW COUNTERS ON IMAGE
	putText(*out, Tools::int2String(ptrData->upCnt), Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(textColorRightB, textColorRightG, textColorRightR), 2);
	putText(*out, Tools::int2String(ptrData->downCnt), Point(ptrData->getLastImage()->cols - 50, ptrData->getLastImage()->rows - 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(textColorLeftB, textColorLeftG, textColorLeftR), 2);

	//DRAW COUNTING LINES
	line(*out, Point(0, out->rows / 2), Point(out->cols, out->rows / 2), Scalar(255, 0, 0), 2);

	ptrData->addImage(out);
}


void COUNTER_ONE::saveSettings()
{
}
