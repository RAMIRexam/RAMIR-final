#include "COUNTER_CC.hpp"



COUNTER_CC::COUNTER_CC(Data *data) : AbstractCounting(data)
{
	//eeline coordinates
	int cols = ptrData->getImage()->cols;
	int rows = ptrData->getImage()->rows;
	
	eelineX = cols / 2;
	upperLineY = 0;
	lowerLineY = rows;


	//Two points defining the eeline
	upperPoint = new Point(eelineX, upperLineY);
	lowerPoint = new Point(eelineX, lowerLineY);

	bool pauseForLineCheckDEBUG = true;				//Debug variable

	minTrackToBeCounted = 0;						//How many tracks an object has to be tracked before it accepted into the ACTracker

	//COUNTERS
	rightMovCnt = 0;
	leftMovCnt = 0;

}


COUNTER_CC::~COUNTER_CC()
{
}


/**********************************************************************************************
	Check if the first blob detected in path has passed the eeline (entry exit line) 


***********************************************************************************************/

/**************************************************************************************************************************************
/	Checks whether a person shall be counted (moved from trackers to ACTrackers)
/	Counts the person if it has moved from the sSOL (start side of line) to the other side. Possible sides: LEFTSIDE_OFLINE / RIGHTSIDE_OFLINE
**************************************************************************************************************************************/
void COUNTER_CC::count()
{
	/*
	/	Tests:
	/		(1) tracker.size in == tracker.size out
	/		(2) -
	/		(3)	trackers start side of line and current side of line must be either LEFTSIDE_OFLINE or RIGHTSIDE_OFLINE
	*/

	vector<Path *> *paths = ptrData->getPathVector();
	ptrData->getLastImage()->copyTo(*out);


	//*UPDATE THE TRACKERS CURRENT SIDE OF LINE
	for (Path* p : *paths) {
		
		int curSOL = LSCheck(p->getLastBlob()->getCentroid());									//compares the location of the eeline and the feeded position (blob position)
		p->set_curSOL(curSOL);

		if (p->get_staSOL() == LINESIDE_NOTDEFINED) {											//I first time (staSOL (start side of line) not set)
			p->set_staSOL(curSOL);
		}
		
	}


	//*CHECK IF TRACKERS SHALL BE COUNTED
	for (Path* p : *paths) {
		
		if (!p->isCountedCheck()) {
			assert(p->get_curSOL() == LINESIDE_RIGHT || p->get_curSOL() == LINESIDE_LEFT);			//(3) DEBUG
			assert(p->get_staSOL() == LINESIDE_RIGHT || p->get_staSOL() == LINESIDE_LEFT);			//(3) DEBUG

			if (p->get_curSOL() != p->get_staSOL() && p->getNrBlobs() > minTrackToBeCounted) {		//tracker shall be counted (has moved from one side to another)
				if (p->get_curSOL() == LINESIDE_RIGHT) { rightMovCnt++; }							//increment movement from left to right counter
				else { leftMovCnt++; }																//increment movement from right to left counter

				p->setCounted(true);
			}
		}
	}
	


	//DRAW THE EELINE
	line(*out, Point(eelineX, upperLineY), Point(eelineX, lowerLineY), Scalar(255, 0, 0), 2);

	//DRAW COUNTERS ON IMAGE
	putText(*out, Tools::int2String(leftMovCnt), Point(30, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
	putText(*out, Tools::int2String(rightMovCnt), Point(ptrData->getLastImage()->cols - 50, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);


	ptrData->addImage(out);


}

void COUNTER_CC::saveSettings()
{
}

/**************************************************************************************************************************************
/	Line-side check, checks on which side of the line an object is
/	If the object is exactly on the line, it's said to be on the right side
**************************************************************************************************************************************/
int COUNTER_CC::LSCheck(Point2f blobPoint){
	/*
	/	Tests:
	/		(1) the entry/exit-line shall be vertical
	/		(2) manual objectcheck, object on the right or left side
	/
	*/
		
	int blobx = blobPoint.x;
	int bloby = blobPoint.y;

	assert(upperPoint->x == lowerPoint->x);			//(1) DEBUG

	if (blobx - upperPoint->x < 0) {				//If the blob is on the left side of the eeline. Upperpoint->x or y doesnt matter (shall be vertical)
		if (pauseForLineCheckDEBUG) {				//(2) DEBUG, 
			pauseForLineCheckDEBUG = false;			//(2) DEBUG, PLEASE CHECK SO OBJECT REALLY IS ON LEFT SIDE (add breakpoint)
		}

		return LINESIDE_LEFT;						//if blob is on the left side
	}
	else {
		if (!pauseForLineCheckDEBUG) {				//(2) DEBUG
			pauseForLineCheckDEBUG = true;			//(2) DEBUG, PLEASE CHECK SO OBJECT REALLY IS ON RIGHT SIDE (add breakpoint)
		}
		return LINESIDE_RIGHT;						//if blob is on the right side
	}

	ptrData->addImage(out);

}

