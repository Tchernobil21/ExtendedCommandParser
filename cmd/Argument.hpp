#ifndef ARGUMENT_H

#define ARGUMENT_H

#include <iostream>
#include <vector>

namespace cmd
{
	class Argument
	{
		public:
			Argument(const std::string name, const std::string description);
			std::string getName();
			std::string getDescription();
			virtual std::string toString() const = 0;
			virtual void parseFromVector(unsigned int & i, const std::vector<std::string> & args) = 0;
			virtual ~Argument();

		protected:
			std::string name;
			std::string description;
	};
}

#endif /* end of include guard: ARGUMENT_H */
