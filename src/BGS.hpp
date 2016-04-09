#ifndef BGS_HPP
#define BGS_HPP

#include "AbstractSegment.hpp"
#include "Input.hpp"

class BGS : public AbstractSegment
{
	public:
		BGS(Data *data);
		~BGS();

		// Inherited via AbstractSegment
		void segment();
		void saveSettings();

	private:
		bool firstRun;
		Mat model;
};

#endif // !BGS_HPP



