#include "PrefixedArgument.hpp"

namespace cmd
{
	PrefixedArgument::PrefixedArgument(const std::string name, const std::string shortcut, const std::string description) : Argument(name, description)
	{
		this->shortcut = shortcut;
	}

	std::string PrefixedArgument::getShortcut() const
	{
		return this->shortcut;
	}

	PrefixedArgument::~PrefixedArgument() { }
}
