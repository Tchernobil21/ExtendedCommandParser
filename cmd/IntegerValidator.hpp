#ifndef INTEGERVALIDATOR_H

#define INTEGERVALIDATOR_H

#include "RangeValidator.hpp"

namespace cmd
{
	class IntegerValidator : public RangeValidator<int>
	{
		public:
			IntegerValidator() : RangeValidator<int>() {}
			IntegerValidator(const std::string & constraints) : RangeValidator<int>(constraints) {}
			virtual std::string getType() const { return std::string("int"); }
			virtual ~IntegerValidator() {}
	};
}

#endif /* end of include guard: INTEGERVALIDATOR_H */
