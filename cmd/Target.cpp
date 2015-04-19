#include "Target.hpp"

namespace cmd
{
	Target::Target(const std::string name, const std::string description, Validator * validator) : Argument(name, description), Validable(validator) { }

	std::string Target::toString() const
	{
		std::string targetStr = this->name + " <" + this->validator->getType() + ">\n\t" + this->description;
		std::string validatorStr = this->validator->toString();

		if(validatorStr != "")
			targetStr += "\n\tValidity conditions : " + this->validator->toString() + ".";

		return targetStr;
	}

	void Target::parseFromVector(unsigned int & i, const std::vector<std::string> & args)
	{
		if(!this->validator->parseAndValidate(args[i++]))
		{
			throw std::string(this->name + " parse failed :\n\t" + this->validator->toString() + ".");
		}

		if(i < args.size() && args[i].substr(0,2) == "--")
			throw std::string("Arguments should not be after the targets.");
	}

	Target::~Target() { }
}
