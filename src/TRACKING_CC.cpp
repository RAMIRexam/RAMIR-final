/*
TRACKER_CC = "tracker Counted Check"
*/

#include "TRACKING_CC.hpp"




TRACKING_CC::TRACKING_CC(Data * data) : AbstractTracking(data)
{

}


TRACKING_CC::~TRACKING_CC()
{
}

void TRACKING_CC::saveSettings()
{
}



void TRACKING_CC::track()
{
	int trackerLife = 10;


	vector<Path *> *paths = ptrData->getPathVector();
	vector<Blob *> *blobs = ptrData->getFrameBlobVector();

	ptrData->getLastImage()->copyTo(*out);

	
	/*
	/	Tests:
	/		(1) Check if all trackers is processed at the end
	/
	*/


	/***** CODE TO PUZZLE LAST VERSION WITH THIS *****/
	vector<Path*> trackers;
	vector<Path*> ACTrackers;

	for (Path *p : *paths) {
		if (p->isCountedCheck()) {
			ACTrackers.push_back(p);
		}
		else {
			trackers.push_back(p);
		}
	}
	/**************************************************/



	//MOVE BLOBS TO ACTRACKERS
	if (ACTrackers.size() > 0) {									//if there exists already counted trackers, the blobs belonging to this trackers must first be removed
		ACTrackers = intersectionTest(blobs, ACTrackers);			//intersectionTest will move blobs to "already counted trackers"
	}

	//CREATE NEW TRACKERS FOR ALL BLOBS
	if (trackers.size() == 0) {
		for (Blob* b : *blobs) {									//No trackers exists. All blobs will turn to a tracker
			
			Path *p = new Path(b, trackerLife);

			p->processed = true;									//DEBUG, blob has been added this iteration
			trackers.push_back(p);
		}
	}

	else {
		trackers = intersectionTest(blobs, trackers);				//there already exists trackers, intersectionTest will move blobs to trackers

		for (Blob* b : *blobs) {									//iterate throught the rest of the blobs and create trackers for them
			Path *p = new Path(b, trackerLife);

			p->processed = true;
			trackers.push_back(p);

		}

		for (Path *p : trackers) {
			if (!p->processed) {									//if tracker is not processed, fill it with emptyblob
				p->addBlob(new Blob());								//construct and add an emptyblob
				p->processed = true;
			}
		}
	}



	//DELETE TRACKERS IF DEAD
	for (unsigned int j = 0; j < trackers.size(); j++){
		Path *p = trackers.at(j);
		//Path *p = *paths->begin() + j;
		assert(p->processed == true);								//(1) DEBUG
	
		if (!p->isAlive())
		{
			trackers.erase(trackers.begin() + j);
			delete p;
		}	
	}
	//DELETE ACTRACKERS IF DEAD
	for (unsigned int j = 0; j < ACTrackers.size(); j++) {
		Path *p = ACTrackers.at(j);
		//Path *p = *paths->begin() + j;
		assert(p->processed == true);								//(1) DEBUG

		if (!p->isAlive())
		{
			ACTrackers.erase(ACTrackers.begin() + j);
			delete p;
		}
	}


	for (Path *t : trackers) { t->processed = false; }				//reset processed for next iteration
	for (Path *t : ACTrackers) { t->processed = false; }			//reset processed for next iteration


	///** make trackers and ACtrackers to paths again****/
	vector<Path*>* tempPath = new vector<Path*>();
	for (Path* p : trackers) {
		tempPath->push_back(p);
	}
	for (Path* p : ACTrackers) {
		tempPath->push_back(p);
	}
	/****************************************************/
	
	ptrData->removeAllPaths();
	
	for (Path* p : *tempPath) {
		ptrData->addPath(p);
	}

	ptrData->addImage(out);
	

}



/**************************************************************************************************************************************
/	Iterates throught all trackers and checks if their last matched blob intersect with one of them in the scene. If a blob intersects
/	it will be added to the tracker and removed from the blobvector.
**************************************************************************************************************************************/

vector<Path*> TRACKING_CC::intersectionTest(vector<Blob*>* blobs, vector<Path*> paths) {
	/*
	/	Tests:
	/		(1) Blob from getLastBlob, shall never return an emptyblob
	/		(2) -
	/
	*/

	int i = paths.size() - 1;
	while (i >= 0) {															//Check tracker from front (oldest tracker shall be checked first)
		Path* p = paths[i];

		vector<Blob*>* restBlobs = new vector<Blob*>();
		Blob* bestBlob = new Blob();															//constructs an emptyblob 

		assert(bestBlob->isEmpty());											//new constructed blobs shall be empty

		double minBhatta = DBL_MAX;
		vector<Mat> isBlobs;													//InterSecting Blobs

		int blobcounter = 0;													//DEBUG
		int numberBlobs = blobs->size();										//DEBUG

		while (blobs->size() > 0) {
			blobcounter++;														//DEBUG

			Blob *b = blobs->back();
			blobs->pop_back();													//Pop makes shure other intersecting blobs than the best is ignored
			
			assert(1 == 1);

			assert(!p->getLastBlob()->isEmpty());								//(1) DEBUG

			if ((b->getRect() & p->getLastBlob()->getRect()).area() > 0) {			//intersection test
				Mat hist1 = b->getHist();
				Mat hist2 = p->getLastBlob()->getHist();

				double bhatta = compareHist(b->getHist(), p->getLastBlob()->getHist(), CV_COMP_BHATTACHARYYA);

				if (bhatta < minBhatta) {
					minBhatta = bhatta;

					bestBlob = b;
				}
			}
			else { restBlobs->push_back(b); }
		}
		assert(blobcounter == numberBlobs);										//if blob is pop'ed, will all blobs still be iterated?

		*blobs = *restBlobs;

		if (!bestBlob->isEmpty()) {												//If intersection
			p->addBlob(bestBlob); 
		}					
		
		else { 
			Blob *emptyBlob = new(Blob);
			assert(emptyBlob->isEmpty());
			p->addBlob(emptyBlob); 
		}

		p->processed = true;
		i--;
	}
	return paths;
}
