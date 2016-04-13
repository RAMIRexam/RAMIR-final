/*
Copyright RAMIR (Räkning av människor i rörelse)
Del2 i Examensarbete - implementering av projektalgoritmen (egna bildanalysalgoritmer)".

År 2016
Emil Andersson and Niklas Schedin
*/

#include "Application.hpp"


//==================CONSTRUCTOR====DESTRUCTOR=============



Application::Application()
{
	try	{
		input = new Input();
	} catch (char *strException) {
		throw strException;
	}

	//USED TO CREATE UNIQUE NAME FOR SAVED IMAGES
	nImagesSaved = 0;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char buffer[256];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", ltm);
	dateTime = buffer;
	
	display = new Display();
	display->createWindow("Settings");

	data = new Data();

	segmentObjectVector		= new vector<AbstractSegment *>();
	filterObjectVector		= new vector<AbstractFilter *>();
	detectionObjectVector	= new vector<AbstractDetection *>();
	trackingObjectVector	= new vector<AbstractTracking *>();
	countingObjectVector	= new vector<AbstractCounting *>();
}





Application::Application(int a)
{
	try {
		input = new Input(a);
	} catch (char *strException) {
		throw strException;
	}

	//USED TO CREATE UNIQUE NAME FOR SAVED IMAGES
	nImagesSaved = 0;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char buffer[256];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", ltm);
	dateTime = buffer;

	
	display = new Display();	
	display->createWindow("Settings");

	data = new Data();

	segmentObjectVector		= new vector<AbstractSegment *>();
	filterObjectVector		= new vector<AbstractFilter *>();
	detectionObjectVector	= new vector<AbstractDetection *>();
	trackingObjectVector	= new vector<AbstractTracking *>();
	countingObjectVector	= new vector<AbstractCounting *>();
}





Application::Application(char *str)
{
	try {
		input = new Input(str);
	} catch (char *strException) {
		throw strException;
	}

	//USED TO CREATE UNIQUE NAME FOR SAVED IMAGES
	nImagesSaved = 0;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	char buffer[256];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", ltm);
	dateTime = buffer;

	display = new Display();
	display->createWindow("Settings");

	data = new Data();

	segmentObjectVector		= new vector<AbstractSegment *>();
	filterObjectVector		= new vector<AbstractFilter *>();
	detectionObjectVector	= new vector<AbstractDetection *>();
	trackingObjectVector	= new vector<AbstractTracking *>();
	countingObjectVector	= new vector<AbstractCounting *>();
}



Application::~Application()
{
	delete input;
	delete display;
	delete data;
	
	delete segmentObjectVector;
	delete filterObjectVector;
	delete detectionObjectVector;
	delete trackingObjectVector;
	
}


//==============================================================




/**
	Starts the application and handles all traffic between 
	the different objects.
*/
void Application::start()
{
	Mat frame;
	

	/*Emil test (shall be done once?)***********/
	frame = input->getImage();

	display->resizeImage(&frame);

	data->addImage(&frame);
	/*******************************************/

	
	//addSegment(new ROI_BG(&data));
	addSegment(new MOG_BGS_HSV(data));

	//FILTER
	addFilter(new ERODE(data));
	addFilter(new DILATE(data));

	//DETECTION
	addDetection(new DETECTION(data));

	//TRACKING
	addTracking(new TRACKING(data));

	//addTracking(new TRACKING_CC(data));

	addCounting(new COUNTER_CC(data));

	display->createWindow("TEST1");
	display->createWindow("TEST2");


	while (!buttonControl())
	{
		frame = input->getImage();
		
		display->resizeImage(&frame);

		data->addImage(&frame);

		display->showImage(data->getImage(), 0);

		for (AbstractSegment *s : *segmentObjectVector) {
			s->segment();
		}
	
		for (AbstractFilter *f : *filterObjectVector) {
			f->filter();
		}

		for (AbstractDetection *d : *detectionObjectVector) {
			d->detect();
		}

		for (AbstractTracking *t : *trackingObjectVector) {
			t->track();
		}

		for (AbstractCounting *c : *countingObjectVector) {
			c->count();
		}
		display->showImage(data->getLastImage(), 1);
		lastImage = *data->getLastImage();

		data->clearImages();
	}

	//SAVE SETTINGS FOR EACH OBJECT
	saveSettings();
	}





void Application::addSegment(AbstractSegment *obj)
{
	segmentObjectVector->push_back(obj);
}





void Application::addFilter(AbstractFilter *obj)
{
	filterObjectVector->push_back(obj);
}




void Application::addDetection(AbstractDetection *obj)
{
	detectionObjectVector->push_back(obj);
}





void Application::addTracking(AbstractTracking *obj)
{
	trackingObjectVector->push_back(obj);
}





void Application::addCounting(AbstractCounting * obj)
{
	countingObjectVector->push_back(obj);
}




//=============PRIVATE FUNCTIONS=======================


bool Application::buttonControl()
{
	bool quit = false;
	switch (waitKey(1))
	{
		case 27:
			quit = true;
			break;
		case 82:
			record();
			break;
		case 112:
			pause();
			break;
	}
	return quit;
}



void Application::record()
{
	string t1 = dateTime + "_" + Tools::int2String(nImagesSaved++) + ".jpg";
	imwrite(t1, lastImage);
}



void Application::pause()
{
	while (waitKey(1) != 112) {
		if (waitKey(1) == 82)
		{
			record();
		}
	};
}



void Application::saveSettings()
{
	//SAVE SETTINGS FOR EACH OBJECT
	for (AbstractSegment *s : *segmentObjectVector) {
		s->saveSettings();
	}

	for (AbstractFilter *f : *filterObjectVector) {
		f->saveSettings();
	}

	for (AbstractDetection *d : *detectionObjectVector) {
		d->saveSettings();
	}

	for (AbstractTracking *t : *trackingObjectVector) {
		t->saveSettings();
	}

	for (AbstractCounting *c : *countingObjectVector) {
		c->saveSettings();
	}
}






