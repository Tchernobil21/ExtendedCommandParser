#include "DependenceTree.hpp"

namespace cmd
{
	DependenceTree::DependenceTree()
	{
		this->firstNode = 0;
	}

	void DependenceTree::parseFromString(const std::string booleanString)
	{
		std::string formatedString = booleanString;
		formatedString.erase(std::remove(formatedString.begin(), formatedString.end(), ' '), formatedString.end());

		this->firstNode = new DependenceNode();
		this->parseFromStringRec(this->firstNode, formatedString);
	}

	void DependenceTree::parseFromStringRec(DependenceNode * node, const std::string booleanString)
	{
		if(node == 0)
			return;

		std::string tmpString = this->removeWrappingParentheses(booleanString);
		DependenceNode * leftNode = 0;
		DependenceNode * rightNode = 0;

		int splitIndex;

		if((splitIndex = this->findFirst(tmpString, "|")) > -1)
		{
			node->setValue("|");
			leftNode = new DependenceNode();
			rightNode = new DependenceNode();
		}
		else if((splitIndex = this->findFirst(tmpString, "&")) > -1)
		{
			node->setValue("&");
			leftNode = new DependenceNode();
			rightNode = new DependenceNode();
		}
		else if((splitIndex = this->findFirst(tmpString, "!")) > -1)
		{
			node->setValue("!");
			rightNode = new DependenceNode();
		}
		else
		{
			node->setValue(tmpString);
		}

		node->setLeftNode(leftNode);
		node->setRightNode(rightNode);

		this->parseFromStringRec(leftNode, tmpString.substr(0, splitIndex));
		this->parseFromStringRec(rightNode, tmpString.substr(splitIndex + 1, tmpString.length() - splitIndex - 1));
	}

	std::string DependenceTree::removeWrappingParentheses(const std::string booleanString) const
	{
		if(booleanString[0] != '(' || booleanString[booleanString.length() - 1] != ')')
			return std::string(booleanString);
		else
		{
			int parenthesesCount = 1;
			unsigned int i = 1;

			while(i < booleanString.length() && parenthesesCount > 0)
			{
				if(booleanString[i] == '(')
					++parenthesesCount;
				if(booleanString[i] == ')')
					--parenthesesCount;
				++i;
			}

			if(i == booleanString.length())
			{
				return booleanString.substr(1, booleanString.length() - 2);
			}
			else
			{
				return std::string(booleanString);
			}
		}
	}

	int DependenceTree::findFirst(const std::string booleanString, const std::string chain) const
	{
		int parenthesesCount = 0;

		for(unsigned int i = 0; i <= booleanString.length() - chain.length(); ++i)
		{
			if(booleanString[i] == '(')
				++parenthesesCount;
			if(booleanString[i] == ')')
				--parenthesesCount;

			if(parenthesesCount == 0 && booleanString.substr(i, chain.length()) == chain)
			{
				return i;
			}
		}

		return -1;
	}

	bool DependenceTree::checkDependences(const std::set<std::string> & currentDependences) const
	{
		if(this->firstNode != 0)
		{
			return this->firstNode->checkDependences(currentDependences);
		}
		else
		{
			return true;
		}
	}

	void DependenceTree::setFirstNode(DependenceNode * firstNode)
	{
		this->firstNode = firstNode;
	}

	std::string DependenceTree::toString() const
	{
		return toStringRec(this->firstNode);
	}

	std::string DependenceTree::toStringRec(const DependenceNode * node) const
	{
		if(node == 0)
			return std::string("");

		std::string leftStr = "";
		std::string rightStr = "";

		DependenceNode * left = node->getLeftNode();
		DependenceNode * right = node->getRightNode();

		if(node->getValue() == "&")
		{
			if(!left->isLeaf() && left->getValue() != "&")
				leftStr = "(" + toStringRec(left) + ")";
			else
				leftStr = toStringRec(left);

			if(!right->isLeaf() && right->getValue() != "&")
				rightStr = "(" + toStringRec(right) + ")";
			else
				rightStr = toStringRec(right);
		}
		else
		{
			leftStr = toStringRec(left);
			rightStr = toStringRec(right);
		}

		return leftStr + " " + node->getValue() + " " + rightStr;
	}

	DependenceTree::~DependenceTree()
	{
		delete this->firstNode;
	}
}
