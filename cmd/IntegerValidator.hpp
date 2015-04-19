#ifndef INTEGERVALIDATOR_H

#define INTEGERVALIDATOR_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <sstream>

#include "Validator.hpp"
#include "BasicParseResult.hpp"

namespace cmd
{
	class IntegerValidator : public Validator
	{
		public:
			IntegerValidator();
			IntegerValidator(const std::string conditionsString);
			virtual void parseConditions(const std::map<std::string, std::string> & conditions);
			virtual std::string getType() const;
			virtual std::string toString() const; // must be ...
			void setMinimum(int minimum);
			void setMaximum(int maximum);
			void setPossibleValues(const std::set<int> & possibleValues);
			void setImpossibleValues(const std::set<int> & impossibleValues);
			virtual ~IntegerValidator();
		protected:
			ParseResult * parse(const std::string strValue) const;
			bool validate(const ParseResult & parseResult) const;
			std::set<int> * tableStringToIntegerSet(const std::string tableString) const;

			int minimum;
			int maximum;
			const std::set<int> * possibleValues;
			const std::set<int> * impossibleValues;

			bool hasMinimum;
			bool hasMaximum;
			bool hasPossibleValues;
			bool hasImpossibleValues;
		private:
			std::string intToStr(int i) const;
	};
}

#endif /* end of include guard: INTEGERVALIDATOR_H */
