#ifndef PARSERESULT_H

#define PARSERESULT_H

#include <iostream>

namespace cmd
{
	class ParseResult
	{
		public:
			ParseResult(){}
			virtual ~ParseResult() = 0;
	};

	inline ParseResult::~ParseResult() {}
}

#endif /* end of include guard: PARSERESULT_H */
