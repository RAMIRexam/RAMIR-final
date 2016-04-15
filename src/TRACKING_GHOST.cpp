#include "TRACKING_GHOST.hpp"



TRACKING_GHOST::TRACKING_GHOST(Data * data) : AbstractTracking(data)
{
}


TRACKING_GHOST::~TRACKING_GHOST()
{
}




void TRACKING_GHOST::track()
{

	vector<Path *> *paths = ptrData->getPathVector();
	vector<Blob *> *blobs = ptrData->getFrameBlobVector();

	ptrData->getLastImage()->copyTo(*out);

	if (paths->size() == 0 && blobs->size() > 0) //INIT. IF PATHS DON'T ALREADY EXIST
	{
		for (Blob *b : *blobs)
		{
			ptrData->addPath(new Path(b, 25));
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

					if (b->getArea() >= p->getMeanArea() * 1.2)
					{
						p->addHeading(b->getCentroid() - p->getLastBlob()->getCentroid());
						p->addArea(b->getArea());
					}

					p->addBlob(b);	//ADD BLOB TO PATH

					blobs->erase(blobs->begin() + i); //REMOVE BLOB FROM VECTOR OF BLOBS

					blobAdded = true;

					//DRAW HEADING VECTOR
					line(*out, b->getCentroid(), b->getCentroid() + p->getHeading(), Scalar(255, 0, 0), 2); //TEST CODE!

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
					//PREDICTS NEXT LOCATION
					Blob *b = new Blob(p->getHeading() + p->getLastBlob()->getCentroid(), true);
					b->setArea(p->getMeanArea());
					
					p->addHeading(b->getCentroid() - p->getLastBlob()->getCentroid());
					p->addArea(b->getArea());

					p->addBlob(b);
					
					line(*out, p->getLastBlob()->getCentroid(), p->getHeading() + p->getLastBlob()->getCentroid(), Scalar(0, 0, 255), 2);
				}
			}
			
		}

		//INSERT REMAINING BLOBS INTO NEW PATHS	
		for (Blob *b : *blobs)
		{
			ptrData->addPath(new Path(b, 25));
		}
		ptrData->addImage(out);
	}
}

void TRACKING_GHOST::saveSettings()
{
}
