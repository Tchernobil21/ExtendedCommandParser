#include "Minus.hpp"

namespace cmd
{
	Minus::Minus(const std::string name, const std::string shortcut, const std::string description, Validator * validator) : PrefixedArgument(name, shortcut, description), Validable(validator) {}

	std::string Minus::toString() const
	{
		std::string argStr = "-" + this->shortcut + ", --" + this->name + " <" + this->validator->getType() + ">\n\t" + this->description;
		
		std::string validatorStr;
		if((validatorStr = this->validator->toString()) != "")
		{
			argStr += "\n\tValidity conditions : " + validatorStr + ".";
		}

		return argStr;
	}

	void Minus::parseFromVector(unsigned int & i, const std::vector<std::string> & args)
	{
		if(++i >= args.size() || args[i].substr(0,2) == "--")
			throw std::string(this->name + " should have a parameter :\n\t" + this->validator->toString());

		if(!this->validator->parseAndValidate(args[i++]))
		{
			throw std::string(this->name + " parse failed :\n\t" + this->validator->toString() + ".");
		}
	}

	Minus::~Minus() {}
}
