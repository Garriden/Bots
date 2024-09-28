#include "Logs.h"

void LogFile(std::string message)
{
	std::string s = std::to_string(GetDay())   + 
					std::to_string(GetMonth()) + 
					std::to_string(GetYear())  + 
					".txt";
	std::string base = "["						 +
					   std::to_string(GetHour()) + ":" +
					   std::to_string(GetMin())  + ":" +
					   std::to_string(GetSec()) + 
						"] ";

	std::string filename(s);
	std::ofstream file_out;

	file_out.open(filename, std::ios_base::app);
	file_out << base << message << std::endl;
	file_out.close();

	std::cout << message << std::endl;
}