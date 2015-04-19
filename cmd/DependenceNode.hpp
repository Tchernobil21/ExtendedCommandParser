#ifndef DEPENDENCENODE_H

#define DEPENDENCENODE_H

#include <iostream>
#include <set>

namespace cmd
{
	class DependenceNode
	{
		public:
			DependenceNode();
			bool checkDependences(const std::set<std::string> & currentDependences) const;
			bool isLeaf() const;
			DependenceNode * getLeftNode() const;
			DependenceNode * getRightNode() const;
			std::string getValue() const;
			void setLeftNode(DependenceNode * leftNode);
			void setRightNode(DependenceNode * rightNode);
			void setValue(const std::string value);
			~DependenceNode();
		private:
			DependenceNode * leftNode;
			DependenceNode * rightNode;
			std::string value;
	};
}

#endif /* end of include guard: DEPENDENCENODE_H */
