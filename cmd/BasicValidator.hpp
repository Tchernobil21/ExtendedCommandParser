#ifndef BASICVALIDATOR_H

#define BASICVALIDATOR_H

#include <iostream>

#include "Validator.hpp"

namespace cmd
{
	template<typename T>
	class BasicValidator : public Validator
	{
		public:
			BasicValidator() : Validator() {}
			T getValue()
			{
				return this->value;
			}
			void smartCastIn(T & value) const
			{
				value = this->value;
			}
			T strToCurrentType(std::string s)
			{
				T v;
				std::stringstream stream(s);
				stream >> v;
				if(stream.fail())
				{
					throw std::string("Cast failed.");
				}
				return v;
			}
			virtual ~BasicValidator() {}
		protected:
			T value;
	};
}

#endif /* end of include guard: BASICVALIDATOR_H */
