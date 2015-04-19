#include "Validator.hpp"

namespace cmd
{
	Validator::Validator()
	{
		this->parseResult = 0;
	}

	void Validator::parseConditionsFromString(const std::string conditionsString)
	{
		std::map<std::string, std::string> * conditions = this->extractConditions(conditionsString);
		this->parseConditions(*conditions);
		delete conditions;
	}

	void Validator::parseConditions(const std::map<std::string, std::string> & conditions) { }

	std::map<std::string, std::string> * Validator::extractConditions(const std::string conditionsString) const
	{
		std::map<std::string, std::string> * conditions = new std::map<std::string, std::string>();

		std::string tmpCondition;
		std::string tmpString = "";

		for(unsigned int i = 0; i < conditionsString.length(); ++i)
		{
			if(conditionsString[i] == '=')
			{
				tmpCondition = tmpString;
				tmpString = "";
			}
			else if(conditionsString[i] == ';')
			{
				(*conditions)[tmpCondition] = tmpString;
				tmpString = "";
			}
			else
			{
				tmpString += conditionsString[i];
			}
		}

		if(tmpCondition != "")
		{
			(*conditions)[tmpCondition] = tmpString;
		}

		return conditions;
	}

	bool Validator::parseAndValidate(const std::string strValue)
	{
		this->parseResult = this->parse(strValue);
		if(this->parseResult != 0)
			return this->validate(*this->parseResult);
		else
			return false;
	}

	ParseResult * Validator::getParseResult() const
	{
		return this->parseResult;
	}

	Validator::~Validator()
	{
		delete this->parseResult;
		this->parseResult = 0;
	}
}
