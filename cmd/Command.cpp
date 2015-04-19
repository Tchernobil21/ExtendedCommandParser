#include "Command.hpp"

namespace cmd
{
	Command::Command(const std::string name, const std::string description, const std::string author, const std::string version)
	{
		this->name = name;
		this->description = description;
		this->author = author;
		this->version = version;
		this->remainingTargetsAllowed = false;
		this->cmdIsValid = false;
	}

	void Command::addPossiblePlus(Plus * plus)
	{
		this->arguments[plus->getName()] = plus;
		if(plus->getShortcut() != "")
		{
			this->argumentsShortcutsToNames[plus->getShortcut()] = plus->getName();
			this->argumentsNamesToShortcuts[plus->getName()] = plus->getShortcut();
		}
	}

	void Command::addPossiblePlus(const std::string name, const std::string shortcut, const std::string description)
	{
		Plus * plus = new Plus(name, shortcut, description);
		this->addPossiblePlus(plus);
	}

	void Command::addPossibleMinus(Minus * minus)
	{
		this->arguments[minus->getName()] = minus;
		if(minus->getShortcut() != "")
		{
			this->argumentsShortcutsToNames[minus->getShortcut()] = minus->getName();
			this->argumentsNamesToShortcuts[minus->getName()] = minus->getShortcut();
		}
	}

	void Command::addPossibleMinus(const std::string name, const std::string shortcut, const std::string description, Validator * validator)
	{
		Minus * minus = new Minus(name, shortcut, description, validator);
		this->addPossibleMinus(minus);
	}

	void Command::addPossibleTarget(Target * target)
	{
		this->arguments[target->getName()] = target;
		this->targetsNames.push_back(target->getName());
	}

	void Command::addPossibleTarget(const std::string name, const std::string description, Validator * validator)
	{
		Target * target = new Target(name, description, validator);
		this->addPossibleTarget(target);
	}

	void Command::addDependence(const std::string argumentNameOrShortcut, DependenceTree * dependenceTree)
	{
		std::string argumentName = this->extractArgumentName(argumentNameOrShortcut);
		this->dependences[argumentName] = dependenceTree;
	}

	void Command::addDependence(const std::string argumentNameOrShortcut, const std::string booleanDependences)
	{
		DependenceTree * tree = new DependenceTree();
		tree->parseFromString(booleanDependences);

		this->addDependence(argumentNameOrShortcut, tree);
	}

	std::string Command::extractArgumentName(const std::string argumentNameOrShortcut) const
	{
		if(this->arguments.find(argumentNameOrShortcut) != this->arguments.end())
			return std::string(argumentNameOrShortcut);
		else
		{
			std::map<std::string, std::string>::const_iterator it = this->argumentsShortcutsToNames.find(argumentNameOrShortcut);
			if(it != this->argumentsShortcutsToNames.end())
				return it->second;
			else
				return std::string("");
		}
	}

	void Command::allowRemainingTargets(bool state)
	{
		this->remainingTargetsAllowed = state;
	}

	Argument * Command::getArgument(const std::string argumentNameOrShortcut) const
	{
		std::string argumentName = this->extractArgumentName(argumentNameOrShortcut);
		std::set<std::string>::const_iterator setIt = this->validArgumentsNames.find(argumentName);
		std::map<std::string, Argument*>::const_iterator mapIt = this->arguments.find(argumentName);

		if(setIt == this->validArgumentsNames.end() || mapIt == this->arguments.end())
			return 0;
		else
		{
			return mapIt->second;
		}
	}

	std::vector<std::string> Command::getRemainingTargets() const
	{
		return this->remainingTargets;
	}

	void Command::parse(int argc, const char ** argv)
	{
		this->cmdIsValid = false;

		std::vector<std::string> args;

		for(int i = 1; i < argc; ++i)
		{
			args.push_back(std::string(argv[i]));
		}

		expandArgs(args);
		parseArgs(args);
		checkDependences();

		if(!this->remainingTargetsAllowed && this->remainingTargets.size() > 0)
			throw std::string("No remaining targets are allowed");

		this->cmdIsValid = true;
	}

	void Command::expandArgs(std::vector<std::string> & args) const
	{
		std::string tmpArgName = "";
		std::vector<std::string> tmpArgs;

		for(unsigned int i = 0; i < args.size(); ++i)
		{
			if(args[i][0] == '-' && (args[i][1] < '0' || args[i][1] > '9'))
			{
				if(args[i][1] == '-')
				{
					tmpArgName = this->extractArgumentName(args[i].substr(2, args[i].length() - 2));
				}
				else
				{
					tmpArgName = this->extractArgumentName(args[i].substr(1, args[i].length() - 1));
				}

				if(tmpArgName == "")
					throw std::string(args[i] + " is not a valid argument.");
				else
					tmpArgs.push_back("--" + tmpArgName);
			}
			else if(args[i][0] == '+')
			{
				for(unsigned int j = 1; j < args[i].length(); ++j)
				{
					tmpArgName = this->extractArgumentName(args[i].substr(j, 1));

					if(tmpArgName == "")
						throw std::string(args[i] + " is not a valid argument.");
					else
						tmpArgs.push_back("--" + tmpArgName);
				}
			}
			else
			{
				tmpArgs.push_back(args[i]);
			}
		}

		args = tmpArgs;
	}

	void Command::parseArgs(std::vector<std::string> & args)
	{
		unsigned int i = 0;
		unsigned int targetIndex = 0;
		std::map<std::string, Argument*>::iterator argIt;

		while(i < args.size())
		{
			if(targetIndex >= this->targetsNames.size() && targetsNames.size() > 0)
			{
				this->remainingTargets.push_back(args[i++]);
				continue;
			}

			if(args[i].substr(0,2) == "--")
			{
				argIt = this->arguments.find(args[i].substr(2, args[i].length() - 2));
			}
			else
			{
				argIt = this->arguments.find(this->targetsNames[targetIndex++]);
			}

			if(argIt != this->arguments.end())
			{
				argIt->second->parseFromVector(i, args);
				this->validArgumentsNames.insert(argIt->second->getName());
			}
			else
			{
				throw std::string(argIt->second->getName() + " parse failed for an unknown reason.");
			}
		}
	}

	void Command::checkDependences() const
	{
		std::set<std::string> argsNamesAndShortcuts;
		std::set<std::string>::const_iterator validIt = this->validArgumentsNames.begin();
		std::map<std::string, DependenceTree*>::const_iterator depIt;
		std::map<std::string, std::string>::const_iterator shortcutsIt;

		for(; validIt != this->validArgumentsNames.end(); ++validIt)
		{
			argsNamesAndShortcuts.insert(*validIt);

			if((shortcutsIt = this->argumentsNamesToShortcuts.find(*validIt)) != this->argumentsNamesToShortcuts.end())
			{
				argsNamesAndShortcuts.insert(shortcutsIt->second);
			}
		}
		
		if((depIt = this->dependences.find("")) != this->dependences.end())
		{
			if(!depIt->second->checkDependences(argsNamesAndShortcuts))
			{
				throw std::string("Arguments are required :\n\t" + depIt->second->toString());
			}
		}

		for(validIt = this->validArgumentsNames.begin(); validIt != this->validArgumentsNames.end(); ++validIt)
		{
			if((depIt = this->dependences.find(*validIt)) != this->dependences.end())
			{
				if(!depIt->second->checkDependences(argsNamesAndShortcuts))
				{
					throw std::string(*validIt + " has dependences :\n\t" + depIt->second->toString());
				}
			}
		}

	}

	bool Command::isValid() const
	{
		return this->cmdIsValid;
	}

	std::string Command::help() const
	{
		std::string helpStr = this->name + "\n\n";
		helpStr += "version : " + this->version + "\n";
		helpStr += "author : " + this->author + "\n";
		helpStr += "description : " + this->description + "\n\n";
		std::map<std::string, Argument*>::const_iterator argIt = this->arguments.begin();
		std::map<std::string, DependenceTree*>::const_iterator depIt = this->dependences.find("");

		if(depIt != this->dependences.end())
		{
			helpStr += "REQUIRED ARGUMENTS\n";
			helpStr += depIt->second->toString() + "\n\n";
		}

		if(this->targetsNames.size() > 0)
		{
			helpStr += "TARGETS\n";

			for(unsigned int i = 0; i < this->targetsNames.size(); ++i)
			{
				if((argIt = this->arguments.find(this->targetsNames[i])) != this->arguments.end())
				{
					helpStr += argIt->second->toString() + "\n\n";
				}
			}
		}

		helpStr += "ARGUMENTS\n";
		bool isTarget;

		for(argIt = this->arguments.begin(); argIt != this->arguments.end(); ++argIt)
		{
			isTarget = false;
			for(unsigned int i = 0; i < this->targetsNames.size(); ++i)
			{
				if(this->targetsNames[i] == argIt->second->getName())
				{
					isTarget = true;
					break;
				}
			}

			if(isTarget)
				continue;

			helpStr += argIt->second->toString();
			depIt = this->dependences.find(argIt->second->getName());

			if(depIt != this->dependences.end())
			{
				helpStr += "\n\tDependences :" + depIt->second->toString() + ".";
			}

			helpStr += "\n\n";
		}

		return helpStr;
	}

	Command::~Command()
	{
		std::map<std::string, Argument*>::iterator argIt = this->arguments.begin();

		for(; argIt != this->arguments.end(); ++argIt)
		{
			delete argIt->second;
			argIt->second = 0;
		}

		std::map<std::string, DependenceTree*>::iterator depIt = this->dependences.begin();

		for(; depIt != this->dependences.end(); ++depIt)
		{
			delete depIt->second;
			depIt->second = 0;
		}
	}
}
