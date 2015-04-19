#ifndef VALIDABLE_H

#define VALIDABLE_H

#include "Validator.hpp"
#include "BasicParseResult.hpp"

namespace cmd
{
	class Validable
	{
		public:
			Validable() {}

			Validable(Validator * validator)
			{
				this->validator = validator;
			}

			bool hasValidator() const
			{
				return (this->validator != 0);
			}

			Validator * getValidator() const
			{
				return this->validator;
			}

			void setValidator(Validator * validator)
			{
				this->validator = validator;
			}

			template<typename T>
			void smartCastIn(T & value)
			{
				if(!this->hasValidator())
					return;

				ParseResult * parseResult = this->getValidator()->getParseResult();
				BasicParseResult<T> * castedResult = dynamic_cast<BasicParseResult<T> *>(parseResult);
				value = castedResult->getValue();
			}

			virtual ~Validable()
			{
				delete this->validator;
				this->validator = 0;
			}
		protected:
			Validator * validator;
	};
}

#endif /* end of include guard: VALIDABLE_H */
