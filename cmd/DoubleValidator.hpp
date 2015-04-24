#ifndef DOUBLEVALIDATOR_H

#define DOUBLEVALIDATOR_H

#include "RangeValidator.hpp"

namespace cmd
{
	class DoubleValidator : public RangeValidator<double>
	{
		public:
			DoubleValidator() : RangeValidator<double>() {}
			DoubleValidator(const std::string & constradoubles) : RangeValidator<double>(constradoubles) {}
			virtual std::string getType() const { return std::string("double"); }
			virtual ~DoubleValidator() {}
	};
}

#endif /* end of include guard: DOUBLEVALIDATOR_H */
