#include "FloatValidator.hpp"

namespace cmd
{
	FloatValidator::FloatValidator()
	{
		this->epsilon = 1.0e-6;
		this->hasMinimum = false;
		this->hasMaximum = false;
		this->hasPossibleValues = false;
		this->hasImpossibleValues = false;

		this->possibleValues = 0;
		this->impossibleValues = 0;
	}

	FloatValidator::FloatValidator(const std::string conditionsString)
	{
		this->epsilon = 1.0e-6;
		this->hasMinimum = false;
		this->hasMaximum = false;
		this->hasPossibleValues = false;
		this->hasImpossibleValues = false;

		this->possibleValues = 0;
		this->impossibleValues = 0;

		this->parseConditionsFromString(conditionsString);
	}

	void FloatValidator::parseConditions(const std::map<std::string, std::string> & conditions)
	{
		char * end;
		std::map<std::string, std::string>::const_iterator it;

		if((it = conditions.find("min")) != conditions.end())
		{
			this->setMinimum(strtod(it->second.c_str(), &end));
		}
		if((it = conditions.find("max")) != conditions.end())
		{
			this->setMaximum(strtod(it->second.c_str(), &end));
		}
		if((it = conditions.find("in")) != conditions.end())
		{
			this->setPossibleValues(*this->tableStringToFloatSet(it->second));
		}
		if((it = conditions.find("nin")) != conditions.end())
		{
			this->setImpossibleValues(*this->tableStringToFloatSet(it->second));
		}
	}

	std::set<float> * FloatValidator::tableStringToFloatSet(const std::string tableString) const
	{
		char * end;
		std::set<float> * tmpValues = new std::set<float>();
		std::string tmpString;

		for(unsigned int i = 0; i < tableString.length(); ++i)
		{
			if(tableString[i] == ',')
			{
				tmpValues->insert(strtod(tmpString.c_str(), &end));
				tmpString = "";
			}
			else
			{
				tmpString += tableString[i];
			}
		}

		if(tmpString != "")
		{
			tmpValues->insert(strtod(tmpString.c_str(), &end));
		}

		return tmpValues;
	}

	ParseResult * FloatValidator::parse(const std::string strValue) const
	{
		char * end;
		float value = strtod(strValue.c_str(), &end);
		if(*end)
			return 0;
		else
			return new BasicParseResult<float>(value);
	}

	bool FloatValidator::validate(const ParseResult & parseResult) const
	{
		float value;

		try
		{
			const BasicParseResult<float> & castedResult = dynamic_cast<const BasicParseResult<float> &>(parseResult);
			value = castedResult.getValue();
		}
		catch(const std::exception & e)
		{
			return false;
		}

		if(this->hasMinimum && (value < this->minimum - this->epsilon))
			return false;

		if(this->hasMaximum && (value > this->maximum + this->epsilon))
			return false;

		if(this->hasPossibleValues && (!containsWithEpsilon(*(this->possibleValues), value)))
			return false;

		if(this->hasImpossibleValues && (containsWithEpsilon(*(this->impossibleValues), value)))
			return false;

		return true;
	}

	bool FloatValidator::containsWithEpsilon(const std::set<float> & values, float value) const
	{
		std::set<float>::iterator it = values.begin();
		std::set<float>::iterator end = values.end();

		for(; it != end; ++it)
		{
			if(value > *it - this->epsilon && value < *it + this->epsilon)
			{
				return true;
			}
		}

		return false;
	}

	std::string FloatValidator::getType() const
	{
		return std::string("float");
	}

	std::string FloatValidator::toString() const
	{
		if(!this->hasMinimum && !this->hasMaximum && !this->hasPossibleValues && !this->hasImpossibleValues)
			return std::string("");

		std::string str = "must be ";
		std::vector<std::string> conditions;

		if(this->hasMinimum)
			conditions.push_back(std::string("greater or equal to " + this->floatToStr(this->minimum)));
		if(this->hasMaximum)
			conditions.push_back(std::string("lower or equal to " + this->floatToStr(this->maximum)));
		if(this->hasPossibleValues)
		{
			std::set<float>::iterator it = this->possibleValues->begin();
			std::set<float>::iterator end = this->possibleValues->end();

			std::string possibleStr = "in [ " + this->floatToStr(*it);
			for(++it; it != end; ++it)
			{
				possibleStr += ", " + this->floatToStr(*it);
			}
			possibleStr += " ]";

			conditions.push_back(possibleStr);
		}
		if(this->hasImpossibleValues)
		{
			std::set<float>::iterator it = this->impossibleValues->begin();
			std::set<float>::iterator end = this->impossibleValues->end();

			std::string impossibleStr = "not in [ " + this->floatToStr(*it);
			for(++it; it != end; ++it)
			{
				impossibleStr += ", " + this->floatToStr(*it);
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

	std::string FloatValidator::floatToStr(float i) const
	{
		std::ostringstream ss;
		ss << i;
		return ss.str();
	}

	void FloatValidator::setMinimum(float minimum)
	{
		this->minimum = minimum;
		this->hasMinimum = true;
	}

	void FloatValidator::setMaximum(float maximum)
	{
		this->maximum = maximum;
		this->hasMaximum = true;
	}

	void FloatValidator::setPossibleValues(const std::set<float> & possibleValues)
	{
		this->possibleValues = &possibleValues;
		this->hasPossibleValues = true;
	}

	void FloatValidator::setImpossibleValues(const std::set<float> & impossibleValues)
	{
		this->impossibleValues = &impossibleValues;
		this->hasImpossibleValues = true;
	}

	FloatValidator::~FloatValidator()
	{
		delete this->possibleValues;
		this->possibleValues = 0;

		delete this->impossibleValues;
		this->impossibleValues = 0;
	}
}
