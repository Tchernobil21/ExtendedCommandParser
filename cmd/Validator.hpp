#ifndef VALIDATOR_H

#define VALIDATOR_H

#include <iostream>
#include <map>

#include "ParseResult.hpp"

namespace cmd
{
	class Validator
	{
		public:
			Validator();
			void parseConditionsFromString(const std::string conditionsString);
			virtual void parseConditions(const std::map<std::string, std::string> & conditions);
			bool parseAndValidate(const std::string strValue);
			ParseResult * getParseResult() const;
			virtual std::string getType() const = 0;
			virtual std::string toString() const = 0; // must be ...
			virtual ~Validator();
		protected:
			std::map<std::string, std::string> * extractConditions(const std::string conditionsString) const;
			virtual ParseResult * parse(const std::string strValue) const = 0;
			virtual bool validate(const ParseResult & parseResult) const = 0;
			ParseResult * parseResult;
	};
}

#endif /* end of include guard: VALIDATOR_H */
