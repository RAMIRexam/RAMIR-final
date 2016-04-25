#include "COUNTER_ONE_HYST.hpp"


//=====================CONSTRUCTOR DESTRUCTOR======================
COUNTER_ONE_HYST::COUNTER_ONE_HYST(Data *data) : AbstractCounting(data)
{
	downCnt = 0;
	upCnt = 0;

	textColorLeftB = rand() % 255;
	textColorLeftG = rand() % 255;
	textColorLeftR = rand() % 255;

	textColorRightB = rand() % 255;
	textColorRightG = rand() % 255;
	textColorRightR = rand() % 255;
}




COUNTER_ONE_HYST::~COUNTER_ONE_HYST()
{
}
//=================================================================




void COUNTER_ONE_HYST::count()
{
	int size;
	vector<Blob *> *blobs;
	vector<Path *> *paths = ptrData->getPathVector();

	ptrData->getLastImage()->copyTo(*out);



	//CHECK IF BLOB HAS MOVED OUT OF HYSTERES AREA
	int lineHyst = 20;
	for (Path *p : *paths)
	{
		if (p->isCountedCheck()
			&& p->getLastBlob()->getCentroid().y < (ptrData->getLastImage()->rows / 2) - lineHyst
			&& p->getLastBlob()->getCentroid().y > (ptrData->getLastImage()->rows / 2) + lineHyst)
		{
			p->setCounted(false);
		}
	}



	//CHECK IF BLOBS HAVE CROSSED THE COUNTING LINE
	for (Path *p : *paths)
	{
		blobs = p->getBlobVector();
		size = blobs->size();

		if (p->getHeading().y < 0 && !blobs->at(size - 1)->isEmpty() && !blobs->at(size - 2)->isEmpty()		//CHECKS IF BLOB HAS PASSED FROM RIGHT TO LEFT OVER THE COUNTING LINE
			&& blobs->at(size - 1)->getCentroid().y <= ptrData->getLastImage()->rows / 2
			&& blobs->at(size - 2)->getCentroid().y > ptrData->getLastImage()->rows / 2
			&& !p->isCountedCheck())
		{
			upCnt++;
			p->setCounted(true);

			textColorRightB = rand() % 255;
			textColorRightG = rand() % 255;
			textColorRightR = rand() % 255;
		}
		else if (p->getHeading().y > 0 && !blobs->at(size - 1)->isEmpty() && !blobs->at(size - 2)->isEmpty()	//CHECKS IF BLOB HAS PASSED FROM LEFT TO RIGHT OVER THE COUNTING LINE
			&& blobs->at(size - 1)->getCentroid().y >= ptrData->getLastImage()->rows / 2
			&& blobs->at(size - 2)->getCentroid().y < ptrData->getLastImage()->rows / 2
			&& !p->isCountedCheck())
		{
			downCnt++;
			p->setCounted(true);

			textColorLeftB = rand() % 255;
			textColorLeftG = rand() % 255;
			textColorLeftR = rand() % 255;
		}
	}

	//DRAW COUNTERS ON IMAGE
	putText(*out, Tools::int2String(upCnt), Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(textColorRightB, textColorRightG, textColorRightR), 2);
	putText(*out, Tools::int2String(downCnt), Point(ptrData->getLastImage()->cols - 50, ptrData->getLastImage()->rows - 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(textColorLeftB, textColorLeftG, textColorLeftR), 2);

	//DRAW COUNTING LINES
	line(*out, Point(0, out->rows / 2), Point(out->cols, out->rows / 2), Scalar(255, 0, 0), 2);

	//DRAW HYSTERES LINES
	line(*out, Point(0, out->rows / 2 - lineHyst), Point(out->cols, out->rows / 2 - lineHyst), Scalar(0, 0, 127), 2);
	line(*out, Point(0, out->rows / 2 + lineHyst), Point(out->cols, out->rows / 2 + lineHyst), Scalar(0, 0, 127), 2);

	ptrData->addImage(out);
}


void COUNTER_ONE_HYST::saveSettings()
{
}


void COUNTER_ONE_HYST::postExecution()
{
	cout << "Up counter: " << upCnt << endl;
	cout << "Down counter: " << downCnt << endl;
}