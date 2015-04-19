#ifndef COMMAND_H

#define COMMAND_H

#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "Argument.hpp"
#include "Minus.hpp"
#include "Plus.hpp"
#include "Target.hpp"
#include "ParseResult.hpp"
#include "DependenceTree.hpp"

namespace cmd
{
	class Command
	{
		public:
			Command(const std::string name, const std::string description, const std::string author, const std::string version);
			void addPossiblePlus(Plus * plus);
			void addPossiblePlus(const std::string name, const std::string shortcut, const std::string description);
			void addPossibleMinus(Minus * minus);
			void addPossibleMinus(const std::string name, const std::string shortcut, const std::string description, Validator * validator);
			void addPossibleTarget(Target * target);
			void addPossibleTarget(const std::string name, const std::string description, Validator * validator);
			void addDependence(const std::string argumentNameOrShortcut, DependenceTree * dependenceTree);
			void addDependence(const std::string argumentNameOrShortcut, const std::string booleanDependences);
			void allowRemainingTargets(bool state);
			Argument * getArgument(const std::string argumentNameOrShortcut) const;
			template<typename T>
			T * get(const std::string plusNameOrShortcut) const
			{
				try
				{
					T * arg = dynamic_cast<T*>(this->getArgument(plusNameOrShortcut));
					return arg;
				}
				catch(const std::string & ex)
				{
					return 0;
				}
			}
			std::vector<std::string> getRemainingTargets() const;
			void parse(int argc, const char ** argv);
			bool isValid() const;
			std::string help() const;
			~Command();
		private:
			std::string extractArgumentName(const std::string argumentNameOrShortcut) const;
			void expandArgs(std::vector<std::string> & args) const;
			void parseArgs(std::vector<std::string> & args);
			void checkDependences() const;

			std::string name;
			std::string description;
			std::string author;
			std::string version;
			std::map<std::string, Argument*> arguments;
			std::map<std::string, std::string> argumentsShortcutsToNames;
			std::map<std::string, std::string> argumentsNamesToShortcuts;
			std::vector<std::string> targetsNames;
			std::vector<std::string> remainingTargets;
			bool remainingTargetsAllowed;
			std::map<std::string, DependenceTree*> dependences;
			std::set<std::string> validArgumentsNames;

			bool cmdIsValid;
	};
}

#endif /* end of include guard: COMMAND_H */
