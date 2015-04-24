#ifndef BOOLEANVALIDATOR_H

#define BOOLEANVALIDATOR_H

#include <iostream>

#include "BasicValidator.hpp"

namespace cmd
{
	class BooleanValidator : public BasicValidator<bool>
	{
		public:
			BooleanValidator() : BasicValidator<bool>() {}
			virtual bool parseAndValidate(const std::string strValue)
			{
				if(strValue == "yes" || strValue == "y" || strValue == "true")
					this->value = true;
				else if(strValue == "no" || strValue == "n" || strValue == "false")
					this->value = false;
				else
					return false;

				return true;
			}
			virtual std::string getType() const { return std::string("bool"); }
			virtual std::string toString() const
			{
				return std::string("must be in [ yes, no, y, n, true, false ]");
			}
			virtual ~BooleanValidator() {}
	};
}

#endif /* end of include guard: BOOLEANVALIDATOR_H */
