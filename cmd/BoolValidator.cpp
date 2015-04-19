#include "BoolValidator.hpp"

namespace cmd
{
	BoolValidator::BoolValidator() { }

	ParseResult * BoolValidator::parse(const std::string strValue) const
	{
		bool value;

		if(strValue == "yes" || strValue == "y" || strValue == "true")
			value = true;
		else if(strValue == "no" || strValue == "n" || strValue == "false")
			value = false;
		else
			return 0;

		return new BasicParseResult<bool>(value);
	}

	bool BoolValidator::validate(const ParseResult & parseResult) const
	{
		try
		{
			dynamic_cast<const BasicParseResult<bool> &>(parseResult);
		}
		catch(const std::exception & e)
		{
			return false;
		}

		return true;
	}

	std::string BoolValidator::getType() const
	{
		return std::string("bool");
	}

	std::string BoolValidator::toString() const
	{
		std::string str = "must be in [ yes, no, y, n, true, false ]";

		return str;
	}

	BoolValidator::~BoolValidator() {}
}
