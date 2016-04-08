#ifndef DILATE_HPP
#define DILATE_HPP

#include "AbstractFilter.hpp"

#include <opencv2\imgproc.hpp>

class DILATE : public AbstractFilter
{
public:
	DILATE(Data *data);
	~DILATE();

	// Inherited via AbstractFilter
	void filter();
	void saveSettings();

private:
	Mat element;
	int dilateSize;
	int dilateType; 

	//=======================================================================================
	//MORPH_RECT = 0,	//!< a rectangular structuring element:  \f[E_{ij}=1\f]
	//MORPH_CROSS = 1,	//!< a cross-shaped structuring element:
						//!< \f[E_{ij} =  \fork{1}{if i=\texttt{anchor.y} or j=\texttt{anchor.x}}{0}{otherwise}\f]
	//MORPH_ELLIPSE = 2 //!< an elliptic structuring element, that is, a filled ellipse inscribed
						//!< into the rectangle Rect(0, 0, esize.width, 0.esize.height)
	//=======================================================================================

	static void setSize(int value, void *userData);
	static void setType(int value, void *userData);
};

#endif // !DILATE_HPP
