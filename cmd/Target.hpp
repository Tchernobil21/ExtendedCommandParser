#ifndef TARGET_H

#define TARGET_H

#include "Argument.hpp"
#include "Validable.hpp"

namespace cmd
{
	class Target : public Argument, public Validable
	{
		public:
			Target(const std::string name, const std::string description, Validator * validator);
			virtual std::string toString() const;
			virtual void parseFromVector(unsigned int & i, const std::vector<std::string> & args);
			virtual ~Target();
	};
}

#endif /* end of include guard: TARGET_H */
