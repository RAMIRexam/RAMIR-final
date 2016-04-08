#include "ROI_BG.hpp"



ROI_BG::ROI_BG(Data * data) : AbstractSegment(data)
{
}




ROI_BG::~ROI_BG()
{
}




/**
	Creates a ROI in the center of the last image
*/
void ROI_BG::segment()
{
	width = 200;								//width of ROI
	height = ptrData->getLastImage()->rows;		//height of ROI
	x = ptrData->getLastImage()->cols / 2;
	y = ptrData->getLastImage()->rows / 2;

	Mat ROI(*ptrData->getLastImage(), Rect(x - width / 2, y - height / 2, width, height));
	*out = ROI;
	ptrData->addImage(out);
}



void ROI_BG::saveSettings()
{
}
