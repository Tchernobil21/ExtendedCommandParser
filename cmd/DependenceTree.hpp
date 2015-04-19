#ifndef DEPENDENCETREE_H

#define DEPENDENCETREE_H

#include <iostream>
#include <set>
#include <algorithm>

#include "DependenceNode.hpp"

namespace cmd
{
	class DependenceTree
	{
		public:
			DependenceTree();
			void parseFromString(const std::string booleanString);
			bool checkDependences(const std::set<std::string> & currentDependences) const;
			void setFirstNode(DependenceNode * firstNode);
			std::string toString() const;
			~DependenceTree();
		private:
			void parseFromStringRec(DependenceNode * node, const std::string booleanString); 
			std::string removeWrappingParentheses(const std::string booleanString) const;
			int findFirst(const std::string booleanString, const std::string chain) const;
			std::string toStringRec(const DependenceNode * node) const;
			DependenceNode * firstNode;
	};
}

#endif /* end of include guard: DEPENDENCETREE_H */
