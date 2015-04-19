#include "DependenceNode.hpp"

namespace cmd
{
	DependenceNode::DependenceNode()
	{
		this->leftNode = 0;
		this->rightNode = 0;
	}

	bool DependenceNode::checkDependences(const std::set<std::string> & currentDependences) const
	{
		if(this->isLeaf())
		{
			return currentDependences.find(value) != currentDependences.end();
		}
		else
		{
			bool leftValid = (this->leftNode == 0) ? false : this->leftNode->checkDependences(currentDependences);
			bool rightValid = (this->rightNode == 0) ? false : this->rightNode->checkDependences(currentDependences);

			if(value == "&")
			{
				return leftValid && rightValid;
			}
			else if(value == "|")
			{
				return leftValid || rightValid;
			}
			else if(value == "!")
			{
				return ! rightValid;
			}
			else
			{
				return false;
			}
		}
	}

	bool DependenceNode::isLeaf() const
	{
		return (this->leftNode == 0 && this->rightNode == 0);
	}

	DependenceNode * DependenceNode::getLeftNode() const
	{
		return this->leftNode;
	}

	DependenceNode * DependenceNode::getRightNode() const
	{
		return this->rightNode;
	}

	std::string DependenceNode::getValue() const
	{
		return this->value;
	}

	void DependenceNode::setLeftNode(DependenceNode * leftNode)
	{
		this->leftNode = leftNode;
	}

	void DependenceNode::setRightNode(DependenceNode * rightNode)
	{
		this->rightNode = rightNode;
	}

	void DependenceNode::setValue(const std::string value)
	{
		this->value = value;
	}

	DependenceNode::~DependenceNode()
	{
		delete this->leftNode;
		delete this->rightNode;
	}
}
