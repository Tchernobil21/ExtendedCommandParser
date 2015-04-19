#include "IntegerValidator.hpp"

namespace cmd
{
	IntegerValidator::IntegerValidator()
	{
		this->hasMinimum = false;
		this->hasMaximum = false;
		this->hasPossibleValues = false;
		this->hasImpossibleValues = false;

		this->possibleValues = 0;
		this->impossibleValues = 0;
	}

	IntegerValidator::IntegerValidator(const std::string conditionsString)
	{
		this->hasMinimum = false;
		this->hasMaximum = false;
		this->hasPossibleValues = false;
		this->hasImpossibleValues = false;

		this->possibleValues = 0;
		this->impossibleValues = 0;

		this->parseConditionsFromString(conditionsString);
	}

	void IntegerValidator::parseConditions(const std::map<std::string, std::string> & conditions)
	{
		char * end;
		std::map<std::string, std::string>::const_iterator it;

		if((it = conditions.find("min")) != conditions.end())
		{
			this->setMinimum(strtol(it->second.c_str(), &end, 10));
		}
		if((it = conditions.find("max")) != conditions.end())
		{
			this->setMaximum(strtol(it->second.c_str(), &end, 10));
		}
		if((it = conditions.find("in")) != conditions.end())
		{
			this->setPossibleValues(*this->tableStringToIntegerSet(it->second));
		}
		if((it = conditions.find("nin")) != conditions.end())
		{
			this->setImpossibleValues(*this->tableStringToIntegerSet(it->second));
		}
	}

	std::set<int> * IntegerValidator::tableStringToIntegerSet(const std::string tableString) const
	{
		char * end;
		std::set<int> * tmpValues = new std::set<int>();
		std::string tmpString;

		for(unsigned int i = 0; i < tableString.length(); ++i)
		{
			if(tableString[i] == ',')
			{
				tmpValues->insert(strtol(tmpString.c_str(), &end, 10));
				tmpString = "";
			}
			else
			{
				tmpString += tableString[i];
			}
		}

		if(tmpString != "")
		{
			tmpValues->insert(strtol(tmpString.c_str(), &end, 10));
		}

		return tmpValues;
	}

	ParseResult * IntegerValidator::parse(const std::string strValue) const
	{
		char * end;
		int value = strtol(strValue.c_str(), &end, 10);
		if(*end)
			return 0;
		else
			return new BasicParseResult<int>(value);
	}

	bool IntegerValidator::validate(const ParseResult & parseResult) const
	{
		int value;

		try
		{
			const BasicParseResult<int> & castedResult = dynamic_cast<const BasicParseResult<int> &>(parseResult);
			value = castedResult.getValue();
		}
		catch(const std::exception & e)
		{
			return false;
		}

		if(this->hasMinimum && (value < this->minimum))
			return false;

		if(this->hasMaximum && (value > this->maximum))
			return false;

		if(this->hasPossibleValues && (this->possibleValues->find(value) == this->possibleValues->end()))
			return false;

		if(this->hasImpossibleValues && (this->impossibleValues->find(value) != this->impossibleValues->end()))
			return false;

		return true;
	}

	std::string IntegerValidator::getType() const
	{
		return std::string("int");
	}

	std::string IntegerValidator::toString() const
	{
		if(!this->hasMinimum && !this->hasMaximum && !this->hasPossibleValues && !this->hasImpossibleValues)
			return std::string("");

		std::string str = "must be ";
		std::vector<std::string> conditions;

		if(this->hasMinimum)
			conditions.push_back(std::string("greater or equal to " + this->intToStr(this->minimum)));
		if(this->hasMaximum)
			conditions.push_back(std::string("lower or equal to " + this->intToStr(this->maximum)));
		if(this->hasPossibleValues)
		{
			std::set<int>::iterator it = this->possibleValues->begin();
			std::set<int>::iterator end = this->possibleValues->end();

			std::string possibleStr = "in [ " + this->intToStr(*it);
			for(++it; it != end; ++it)
			{
				possibleStr += ", " + this->intToStr(*it);
			}
			possibleStr += " ]";

			conditions.push_back(possibleStr);
		}
		if(this->hasImpossibleValues)
		{
			std::set<int>::iterator it = this->impossibleValues->begin();
			std::set<int>::iterator end = this->impossibleValues->end();

			std::string impossibleStr = "not in [ " + this->intToStr(*it);
			for(++it; it != end; ++it)
			{
				impossibleStr += ", " + this->intToStr(*it);
			}
			impossibleStr += " ]";

			conditions.push_back(impossibleStr);
		}

		std::vector<std::string>::iterator it = conditions.begin();
		std::vector<std::string>::iterator end = conditions.end();

		for(; it + 1 != end; ++it)
		{
			str += *it + ", ";
		}

		if(conditions.size() > 1)
		{
			str.replace(str.rfind(", "), 2, " and ");
		}

		str += *it;

		return str;
	}

	std::string IntegerValidator::intToStr(int i) const
	{
		std::ostringstream ss;
		ss << i;
		return ss.str();
	}

	void IntegerValidator::setMinimum(int minimum)
	{
		this->minimum = minimum;
		this->hasMinimum = true;
	}

	void IntegerValidator::setMaximum(int maximum)
	{
		this->maximum = maximum;
		this->hasMaximum = true;
	}

	void IntegerValidator::setPossibleValues(const std::set<int> & possibleValues)
	{
		this->possibleValues = &possibleValues;
		this->hasPossibleValues = true;
	}

	void IntegerValidator::setImpossibleValues(const std::set<int> & impossibleValues)
	{
		this->impossibleValues = &impossibleValues;
		this->hasImpossibleValues = true;
	}

	IntegerValidator::~IntegerValidator()
	{
		delete this->possibleValues;
		this->possibleValues = 0;

		delete this->impossibleValues;
		this->impossibleValues = 0;
	}
}
