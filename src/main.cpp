/*
Copyright RAMIR (Räkning av människor i rörelse)
Del2 i Examensarbete - implementering av projektalgoritmen (egna bildanalysalgoritmer)".

År 2016
Emil Andersson and Niklas Schedin
*/

#include "Application.hpp"

#include <stdlib.h>

using namespace std;

int main()
{
	try {
		Application app("humanwalk5.avi");

		app.start();

	} catch (char *str) {
		cout << str << endl;
		getchar();
		return -1;
	}

	

	return 0;
}