#include "stdafx.h"
#include "ConData.h"

namespace Command
{
	// Recognize the command
	std::string Recognize(std::string);
	std::string CutArg(std::string, int);
	// Make command
	BOOL Make(ConData, std::string);
}