#ifndef MINUS_H

#define MINUS_H

#include "PrefixedArgument.hpp"
#include "Validable.hpp"

namespace cmd
{
	class Minus : public PrefixedArgument, public Validable
	{
		public:
			Minus(const std::string name, const std::string shortcut, const std::string description, Validator * validator);
			virtual std::string toString() const;
			virtual void parseFromVector(unsigned int & i, const std::vector<std::string> & args);
			virtual ~Minus();
	};
}

#endif /* end of include guard: MINUS_H */
