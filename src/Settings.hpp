#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "Tools.hpp"

#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Settings
{
	public:
		static void saveToFile(char *str, int value);
		static int loadFromFile(char *str);

	private:
		static ofstream ofile;
		static ifstream ifile;

		static void loadFile(string *fileData);
		static int find(string data, string str);
};

#endif // !SETTINGS_HPP


