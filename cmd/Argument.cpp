#include "Argument.hpp"

namespace cmd
{
	Argument::Argument(const std::string name, const std::string description)
	{
		this->name = name;
		this->description = description;
	}

	std::string Argument::getName()
	{
		return this->name;
	}

	std::string Argument::getDescription()
	{
		return this->description;
	}

	Argument::~Argument() { }
}
