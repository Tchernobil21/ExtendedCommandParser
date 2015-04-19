#ifndef BASICPARSERESULT_H

#define BASICPARSERESULT_H

#include "ParseResult.hpp"

namespace cmd
{
	template<class T>
	class BasicParseResult : public ParseResult
	{
		public:
			BasicParseResult<T>(T value) : ParseResult(), value(value) {}
			T getValue() const
			{
				return this->value;
			}
			virtual ~BasicParseResult<T>() {}
		protected:
			T value;
	};
}

#endif /* end of include guard: BASICPARSERESULT_H */
