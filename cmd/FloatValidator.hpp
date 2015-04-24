#ifndef FLOATVALIDATOR_H

#define FLOATVALIDATOR_H

#include "RangeValidator.hpp"

namespace cmd
{
	class FloatValidator : public RangeValidator<float>
	{
		public:
			FloatValidator() : RangeValidator<float>() {}
			FloatValidator(const std::string & constrafloats) : RangeValidator<float>(constrafloats) {}
			virtual std::string getType() const { return std::string("float"); }
			virtual ~FloatValidator() {}
	};
}

#endif /* end of include guard: FLOATVALIDATOR_H */
