
#include "Application.hpp"

#include <stdlib.h>

using namespace std;

int main()
{
	try {
		Application app("humanwalk1.avi");

		app.start();

	} catch (char *str) {
		cout << str << endl;
		getchar();
		return -1;
	}
	
	

	return 0;
}