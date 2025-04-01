#pragma once
/** @file NotFoundException.h */

#include <stdexcept>
#include <string>
using namespace std;
class NotFoundException : public logic_error
{
	public:
		NotFoundException(const string& message = "");
}; // end NotFoundException

NotFoundException::NotFoundException(const string& message) :
	logic_error("Not Found Exception: " + message)
{}