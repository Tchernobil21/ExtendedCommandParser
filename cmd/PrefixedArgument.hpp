#ifndef PREFIXEDARGUMENT_H

#define PREFIXEDARGUMENT_H

#include "Argument.hpp"

namespace cmd
{
	class PrefixedArgument : public Argument
	{
		public:
			PrefixedArgument(const std::string name, const std::string shortcut, const std::string description);
			std::string getShortcut() const;
			virtual std::string toString() const = 0;
			virtual ~PrefixedArgument();

		protected:
			std::string shortcut;
	};
}

#endif /* end of include guard: PREFIXEDARGUMENT_H */
