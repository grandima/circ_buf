#include <string>

class BadCircleException
{
public:
	BadCircleException(std::string error) : _errorMessage(error) {}

	void DisplayError();

private:
	std::string _errorMessage;

};