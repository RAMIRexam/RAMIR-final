#ifndef STATISTIC_HPP
#define STATISTIC_HPP

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Statistic
{
	public:
		static void saveStat(string filename, string str);

	private:
		static ofstream ofile;

};

#endif // !STATISTIC_HPP