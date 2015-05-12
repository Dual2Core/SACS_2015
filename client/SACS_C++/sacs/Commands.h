#include "stdafx.h"
#include "ConData.h"
#include "SessionManager.h"

namespace Command
{
	// Recognize the command
	std::string Recognize(std::string);
	std::string CutArg(std::string, int);
	// Make command
	BOOL Make(ConData, std::string, SessionManager&);
	// Transform message to http request format
	void Transform(std::string&);
}