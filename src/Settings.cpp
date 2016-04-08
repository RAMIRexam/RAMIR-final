#include "Settings.hpp"


ofstream Settings::ofile;
ifstream Settings::ifile;


/*
	Saves setting to file. Either by changing the value of an already
	existing setting or add a new to the end of file.
*/
void Settings::saveToFile(char * str, int value)
{
	string fileData;
	loadFile(&fileData);

	int nameIndex = fileData.find(str);		//FIND THE SETTING IF IT EXSIST
	if (nameIndex != string::npos)
	{
		//CHANGE THE VALUE OF THE SETTING
		int firstMark = fileData.find("\"", nameIndex);
		int secondMark = fileData.find("\"", firstMark + 1);

		fileData.erase(firstMark + 1, secondMark - firstMark - 1);
		fileData.insert(firstMark + 1, intToString(value));
	}
	else
	{
		//ADD SETTING TO THE END OF THE FILE
		fileData = fileData + str + "=\"" + intToString(value) + "\"\n";
	}


	//SAVE 
	ofile.open("Settings.txt");
	if (ofile.is_open())
	{
		ofile << fileData.c_str();

		ofile.flush();
		ofile.close();
	}
}




int Settings::loadFromFile(char * str)
{
	string fileData;
	loadFile(&fileData);

	int nameIndex = fileData.find(str);		//FIND THE SETTING IF IT EXSIST
	if (nameIndex != string::npos)
	{
		//CHANGE THE VALUE OF THE SETTING
		int firstMark = fileData.find("\"", nameIndex);
		int secondMark = fileData.find("\"", firstMark + 1);

		return stringToInt(fileData.substr(firstMark + 1, secondMark - 1));
	}
	return 0;
}



/*
	Loads the settings file
*/
void Settings::loadFile(string *fileData)
{
	string buffer;

	ifile.open("Settings.txt");
	if (ifile.is_open())
	{
		int i = 0;
		while (getline(ifile, buffer))	//READ ENTIRE FILE
		{
			*fileData = *fileData + buffer;
		}
		ifile.close();
	}
}



/*
	Convert int to string
*/
string Settings::intToString(int value)
{
	ostringstream ostream;

	ostream << value;

	return ostream.str();
}


/*
	Convert string to int
*/
int Settings::stringToInt(string str)
{
	int value;
	istringstream istream(str);

	istream >> value;

	return value;
}
