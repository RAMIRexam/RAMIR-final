#include "TRACKING.hpp"



TRACKING::TRACKING(Data * data) : AbstractTracking(data)
{
}


TRACKING::~TRACKING()
{
}




void TRACKING::track()
{
	vector<Path *> *paths = ptrData->getPathVector();
	vector<Blob *> *blobs = ptrData->getFrameBlobVector();

	ptrData->getLastImage()->copyTo(*out);

	if (paths->size() == 0 && blobs->size() > 0) //INIT. IF PATHS DON'T ALREADY EXIST
	{
		for (Blob *b : *blobs)
		{
			ptrData->addPath(new Path(b));
		}
	}
	else if (blobs->size() > 0 || paths->size() > 0) //INSERT BLOBS IN ALREADY EXISTING PATHS
	{
		bool blobAdded;
		for (unsigned int j = 0; j < paths->size(); j++)
		{
			blobAdded = false;
			Path *p = paths->at(j);

			//CHECK IF BLOBS OVERLAP
			for (unsigned int i = 0; i < blobs->size(); i++)
			{
				if ((p->getLastBlob()->getRect() & blobs->at(i)->getRect()).area() > 0) //CHECKS FOR THE FISRT BLOBS THAT OVERLAP
				{
					Blob *b = blobs->at(i);
					line(*out, b->getCentroid(), p->getLastBlob()->getCentroid(), Scalar(255, 0, 0), 2); //TEST CODE!
					p->setHeading(b->getCentroid() - p->getLastBlob()->getCentroid());
					
					p->addBlob(b);	//ADD BLOB TO PATH
					blobs->erase(blobs->begin() + i); //REMOVE BLOB FROM VECTOR OF BLOBS

					blobAdded = true;


					break;
				}
			}

			//ADD EMPTY BLOB IF THERE WERE NO BLOB FOUND FOR THE PATH
			if (!blobAdded)
			{
				if (!p->isAlive())
				{	
					paths->erase(paths->begin() + j);
					delete p;
				}
				else
				{
					p->addBlob(new Blob());
				}
			}
		}

		//INSERT REMAINING BLOBS INTO NEW PATHS	
		for (Blob *b : *blobs)
		{
			ptrData->addPath(new Path(b));
		}
		ptrData->addImage(out);
	}
}

void TRACKING::saveSettings()
{
}
