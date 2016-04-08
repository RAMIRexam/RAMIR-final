#include "Tools.hpp"



string Tools::int2String(int value)
{
	ostringstream converter;
	converter << value;
	return converter.str();
}



int Tools::string2Int(char * value)
{
	int result;
	istringstream converter(value);
	converter >> result;
	return result;
}
