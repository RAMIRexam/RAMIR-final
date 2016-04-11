#include "Application.hpp"


//==================CONSTRUCTOR====DESTRUCTOR=============



Application::Application()
{
	try	{
		input = new Input();
	} catch (char *strException) {
		throw strException;
	}

	display = new Display();

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

	display = new Display();	

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

	display = new Display();
	display->createWindow("Settings");

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
	
	delete segmentObjectVector;
	delete filterObjectVector;
	delete detectionObjectVector;
	delete trackingObjectVector;
	
}


//==============================================================


#include "Settings.hpp"

/**
	Starts the application and handles all traffic between 
	the different objects.
*/
void Application::start()
{
	Mat frame;
	Data data;
	
	//addSegment(new ROI_BG(&data));
	addSegment(new BGS(&data));


	addFilter(new ERODE(&data));
	addFilter(new DILATE(&data));

	addDetection(new DETECTION(&data));

	addTracking(new TRACKING(&data));

	addCounting(new COUNTER_ONE(&data));

	display->createWindow("TEST1");
	display->createWindow("TEST2");
	display->createWindow("TEST3");
	display->createWindow("TEST4");

	while (cv::waitKey(1) != 27)
	{
		frame = input->getImage();
		
		display->resizeImage(&frame);

		data.addImage(&frame);

		display->showImage(data.getImage(), 0);

		for (AbstractSegment *s : *segmentObjectVector) {
			s->segment();
		}
		display->showImage(data.getLastImage(), 2);
		for (AbstractFilter *f : *filterObjectVector) {
			f->filter();
		}
		display->showImage(data.getLastImage(), 3);
		for (AbstractDetection *d : *detectionObjectVector) {
			d->detect();
		}

		for (AbstractTracking *t : *trackingObjectVector) {
			t->track();
		}

		for (AbstractCounting *c : *countingObjectVector) {
			c->count();
		}
		display->showImage(data.getLastImage(), 1);

		data.clearImages();

	}

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



