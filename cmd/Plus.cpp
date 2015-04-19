#include "Plus.hpp"

namespace cmd
{
	Plus::Plus(const std::string name, const std::string shortcut, const std::string description) : PrefixedArgument(name, shortcut.substr(0,1), description) {}

	std::string Plus::toString() const
	{
		std::string argStr = "+/-" + this->shortcut + ", --" + this->name + "\n\t" + this->description;
		
		return argStr;
	}

	void Plus::parseFromVector(unsigned int & i, const std::vector<std::string> & args)
	{
		++i;
	}

	Plus::~Plus() {}
}
