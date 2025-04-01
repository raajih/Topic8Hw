#pragma once
/** @file PrecondViolatedExcep.h */

#include <stdexcept>
#include <string>
using namespace std;
class PrecondViolatedExcep : public logic_error
{
public:
	PrecondViolatedExcep(const string& message = "");
}; // end PrecondViolatedExcep

PrecondViolatedExcep::PrecondViolatedExcep(const string& message) :
	logic_error("Precondition Violated Exception: " + message)
{
}