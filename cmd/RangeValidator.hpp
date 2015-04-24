#ifndef RANGEVALIDATOR_H

#define RANGEVALIDATOR_H

#include <iostream>
#include <vector>

#include "BasicValidator.hpp"
#include "Range.hpp"

namespace cmd
{
	template<typename T>
	class RangeValidator : public BasicValidator<T>
	{
		public:
			RangeValidator() : BasicValidator<T>() {}
			RangeValidator(const std::string & constraints) : BasicValidator<T>()
			{
				extractConstraints(constraints);
			}
			virtual bool parseAndValidate(const std::string strValue)
			{
				try
				{
					this->value = this->strToCurrentType(strValue);
					return validate();
				}
				catch(const std::string & ex)
				{
					return false;
				}
			}
			bool validate() const
			{
				for(unsigned int i = 0; i < this->ranges.size(); ++i)
				{
					if(this->ranges[i].contains(this->value))
						return true;
				}

				return (this->ranges.size() == 0);
			}
			virtual std::string toString() const
			{
				if(this->ranges.size() > 0)
				{
					std::string str = "must be in [ " + this->ranges[0].toString();

					for(unsigned int i = 1; i < this->ranges.size(); ++i)
					{
						str += ", " + this->ranges[i].toString();
					}

					str += " ]";
					return str;
				}
				else
				{
					return std::string("");
				}
			}
			virtual ~RangeValidator() {}
		protected:
			void extractConstraints(const std::string & rangesStr)
			{
				std::string tmpFirst;
				std::string tmpStr;

				for(unsigned int i = 0; i < rangesStr.length(); ++i)
				{
					if(rangesStr[i] == ':')
					{
						tmpFirst = tmpStr;
						tmpStr = "";
					}
					else if(rangesStr[i] == ',')
					{
						this->addRange(tmpFirst, tmpStr);
						tmpStr = "";
					}
					else
						tmpStr += rangesStr[i];
				}

				this->addRange(tmpFirst, tmpStr);
			}

			void addRange(const std::string & first, const std::string & second)
			{
				if(first == "")
					this->ranges.push_back(Range<T>(-Range<T>::inf(), this->strToCurrentType(second)));
				else if(second == "")
					this->ranges.push_back(Range<T>(this->strToCurrentType(first), Range<T>::inf()));
				else
					this->ranges.push_back(Range<T>(this->strToCurrentType(first), this->strToCurrentType(second)));
			}

			std::vector< Range<T> > ranges;
	};
}

#endif /* end of include guard: RANGEVALIDATOR_H */
