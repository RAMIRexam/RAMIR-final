#include "Statistic.hpp"

ofstream Statistic::ofile;

void Statistic::saveStat(string filename, string str)
{
	ofile.open(filename + ".csv", ios::app);
	if (ofile.is_open())
	{
		ofile << str << endl;
	}
	ofile.close();
}
