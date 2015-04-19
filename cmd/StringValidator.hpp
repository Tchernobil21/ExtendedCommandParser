#ifndef STRINGVALIDATOR_H

#define STRINGVALIDATOR_H

#include <iostream>
#include <set>

#include "Validator.hpp"
#include "BasicParseResult.hpp"

namespace cmd
{
	class StringValidator : public Validator
	{
		public:
			StringValidator();
			StringValidator(const std::string conditions);
			virtual void parseConditions(const std::map<std::string, std::string> & conditions);
			virtual std::string getType() const;
			virtual std::string toString() const;
			void setPossibleValues(const std::set<std::string> & possibleValues);
			virtual ~StringValidator();

		protected:
			ParseResult * parse(const std::string strValue) const;
			bool validate(const ParseResult & parseResult) const;
			std::set<std::string> * tableStringToStringSet(const std::string tableString) const;

			const std::set<std::string> * possibleValues;

			bool hasPossibleValues;
	};
}

#endif /* end of include guard: STRINGVALIDATOR_H */
