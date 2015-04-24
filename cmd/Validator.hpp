#ifndef VALIDATOR_H

#define VALIDATOR_H

#include <iostream>
#include <sstream>

namespace cmd
{
	class Validator
	{
		public:
			Validator() {}
			virtual bool parseAndValidate(const std::string strValue) = 0;
			virtual std::string getType() const = 0;
			virtual std::string toString() const = 0; // must be ...
			virtual ~Validator() {}
	};
}

#endif /* end of include guard: VALIDATOR_H */
