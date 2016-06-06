#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "bad_circle_exception.h"

using namespace std;

void BadCircleException::DisplayError()
{
	cout << _errorMessage;
}