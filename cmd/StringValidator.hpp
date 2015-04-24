#ifndef STRINGVALIDATOR_H

#define STRINGVALIDATOR_H

#include <iostream>
#include <set>

#include "BasicValidator.hpp"

namespace cmd
{
	class StringValidator : public BasicValidator<std::string>
	{
		public:
			StringValidator() : BasicValidator<std::string>() {}
			StringValidator(const std::string & constraints) : BasicValidator<std::string>()
			{
				this->extractConstraints(constraints);
			}
			virtual bool parseAndValidate(const std::string strValue)
			{
				this->value = strValue;
				return validate();
			}
			bool validate() const
			{
				if(this->possibleValues.find(this->value) != this->possibleValues.end())
					return true;

				return (this->possibleValues.size() == 0);
			}
			virtual std::string getType() const { return std::string("str"); }
			virtual std::string toString() const
			{
				if(this->possibleValues.size() > 0)
				{
					std::set<std::string>::const_iterator it = this->possibleValues.begin();
					std::string str = "must be in [ " + *it++;

					for(; it != this->possibleValues.end(); ++it)
					{
						str += ", " + *it;
					}

					str += " ]";
					return str;
				}
				else
				{
					return std::string("");
				}
			}
			virtual ~StringValidator() {}
		protected:
			void extractConstraints(const std::string & constraints)
			{
				std::string tmpStr;

				for(unsigned int i = 0; i < constraints.length(); ++i)
				{
					if(constraints[i] == ',')
					{
						this->possibleValues.insert(tmpStr);
						tmpStr = "";
					}
					else
					{
						tmpStr += constraints[i];
					}
				}

				this->possibleValues.insert(tmpStr);
			}

			std::set<std::string> possibleValues;
	};
}

#endif /* end of include guard: STRINGVALIDATOR_H */
