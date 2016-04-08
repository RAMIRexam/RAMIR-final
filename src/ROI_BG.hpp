#ifndef ROI_BG_HPP
#define ROI_BG_HPP

#include "AbstractSegment.hpp"

class ROI_BG : public AbstractSegment
{
	public:
		ROI_BG(Data *data);
		~ROI_BG();

		// Inherited via AbstractSegment
		void segment();
		void saveSettings();

	private:
		int x;
		int y;
		int width;
		int height;
};

#endif // !ROI_HPP



