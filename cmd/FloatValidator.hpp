#ifndef FLOATVALIDATOR_H

#define FLOATVALIDATOR_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <sstream>

#include "Validator.hpp"
#include "BasicParseResult.hpp"

namespace cmd
{
	class FloatValidator : public Validator
	{
		public:
			FloatValidator();
			FloatValidator(const std::string conditionsString);
			virtual void parseConditions(const std::map<std::string, std::string> & conditions);
			virtual std::string getType() const;
			virtual std::string toString() const; // must be ...
			void setEpsilon(float epsilon);
			void setMinimum(float minimum);
			void setMaximum(float maximum);
			void setPossibleValues(const std::set<float> & possibleValues);
			void setImpossibleValues(const std::set<float> & impossibleValues);
			virtual ~FloatValidator();
		protected:
			ParseResult * parse(const std::string strValue) const;
			bool validate(const ParseResult & parseResult) const;
			std::set<float> * tableStringToFloatSet(const std::string tableString) const;

			float epsilon;
			float minimum;
			float maximum;
			const std::set<float> * possibleValues;
			const std::set<float> * impossibleValues;

			bool hasMinimum;
			bool hasMaximum;
			bool hasPossibleValues;
			bool hasImpossibleValues;
		private:
			std::string floatToStr(float i) const;
			bool containsWithEpsilon(const std::set<float> & values, float value) const;
	};
}

#endif /* end of include guard: FLOATVALIDATOR_H */
