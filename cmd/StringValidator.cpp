#include "StringValidator.hpp"

namespace cmd
{
	StringValidator::StringValidator()
	{
		this->hasPossibleValues = false;

		this->possibleValues = 0;
	}

	StringValidator::StringValidator(const std::string conditionsString)
	{
		this->hasPossibleValues = false;

		this->possibleValues = 0;

		this->parseConditionsFromString(conditionsString);
	}

	void StringValidator::parseConditions(const std::map<std::string, std::string> & conditions)
	{
		std::map<std::string, std::string>::const_iterator it;

		if((it = conditions.find("in")) != conditions.end())
		{
			this->setPossibleValues(*this->tableStringToStringSet(it->second));
		}
	}

	std::set<std::string> * StringValidator::tableStringToStringSet(const std::string tableString) const
	{
		std::set<std::string> * tmpValues = new std::set<std::string>();
		std::string tmpString;

		for(unsigned int i = 0; i < tableString.length(); ++i)
		{
			if(tableString[i] == ',')
			{
				tmpValues->insert(tmpString);
				tmpString = "";
			}
			else
			{
				tmpString += tableString[i];
			}
		}

		if(tmpString != "")
		{
			tmpValues->insert(tmpString);
		}

		return tmpValues;
	}

	ParseResult * StringValidator::parse(const std::string strValue) const
	{
		return new BasicParseResult<std::string>(strValue);
	}

	bool StringValidator::validate(const ParseResult & parseResult) const
	{
		std::string value;

		try
		{
			const BasicParseResult<std::string> & castedResult = dynamic_cast<const BasicParseResult<std::string> &>(parseResult);
			value = castedResult.getValue();
		}
		catch(const std::exception & e)
		{
			return false;
		}

		if(this->hasPossibleValues && (this->possibleValues->find(value) == this->possibleValues->end()))
			return false;

		return true;
	}

	std::string StringValidator::getType() const
	{
		return std::string("str");
	}

	std::string StringValidator::toString() const
	{
		if(!this->hasPossibleValues)
			return std::string("");

		std::string str = "must be ";

		if(this->hasPossibleValues)
		{
			std::set<std::string>::iterator it = this->possibleValues->begin();
			std::set<std::string>::iterator end = this->possibleValues->end();

			std::string possibleStr = "in [ " + *it;
			for(++it; it != end; ++it)
			{
				possibleStr += ", " + *it;
			}
			possibleStr += " ]";
			str += possibleStr;
		}

		return str;
	}

	void StringValidator::setPossibleValues(const std::set<std::string> & possibleValues)
	{
		this->possibleValues = &possibleValues;
		this->hasPossibleValues = true;
	}

	StringValidator::~StringValidator()
	{
		delete this->possibleValues;
		this->possibleValues = 0;
	}
}
