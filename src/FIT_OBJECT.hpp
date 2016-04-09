#ifndef FIT_OBJECT_HPP
#define FIT_OBJECT_HPP

#include "AbstractDetection.hpp"

#include <vector>

using namespace std;

/**
	Requires a detection function that can extract the blobs from the image before
*/
class FIT_OBJECT : public AbstractDetection
{
	public:
		FIT_OBJECT(Data *data);
		~FIT_OBJECT();

		// Inherited via AbstractFilter
		void filter();
		void saveSettings();

	private:

};

#endif // !FIT_OBJECT_HPP

