#ifndef BOOLVALIDATOR_H

#define BOOLVALIDATOR_H

#include "Validator.hpp"
#include "BasicParseResult.hpp"

namespace cmd
{
	class BoolValidator : public Validator
	{
		public:
			BoolValidator();
			virtual std::string getType() const;
			virtual std::string toString() const; // must be ...
			virtual ~BoolValidator();
		protected:
			ParseResult * parse(const std::string strValue) const;
			bool validate(const ParseResult & parseResult) const;
	};
}

#endif /* end of include guard: BOOLVALIDATOR_H */
