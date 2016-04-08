#ifndef SETTINGS_HPP
#define SETTINGS_HPP

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

		static string intToString(int value);
		static int stringToInt(string str);
};

#endif // !SETTINGS_HPP


