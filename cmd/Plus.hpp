#ifndef PLUS_H

#define PLUS_H

#include "PrefixedArgument.hpp"

namespace cmd
{
	class Plus : public PrefixedArgument
	{
		public:
			Plus(const std::string name, const std::string shortcut, const std::string description);
			virtual std::string toString() const;
			virtual void parseFromVector(unsigned int & i, const std::vector<std::string> & args);
			virtual ~Plus();
	};
}

#endif /* end of include guard: PLUS_H */
