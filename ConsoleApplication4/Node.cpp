#include "stdafx.h"
#include "Node.h"
#include<iostream>


Node::Node()
{
}


Node::~Node()
{
}
void Node::addChildren(Node* N)
{
	children.push_back(N);
}
int Node::numberofChildren()
{
	return children.size();
}
Node* Node::childat(int i)
{
	if (i>=0&&i<children.size())
	return children[i];
	cout << "Error: out of bound for children vector";
	return NULL;
}
void Node::assignSpin(int i)
{
	spin = i;
}
int Node::returnSpin()
{
	return spin;
}
void Node::assignNumber(int i)
{
	number = i;
}
int Node::returnNumber()
{
	return number;
}
bool Node::exist(int _number)
{
	bool result=false;
	if (_number == number)//it exist
		return true;
	else
	{
		for (int i = 0; i < children.size(); i++)
		{
			result = children[i]->exist(_number);
			if (result == true)//it existed no need to check more
				break;
		}
	}
	return result;
}
int Node::spinAt(int _number)
{
	int x = -100;//check if spin is found or not
	if (_number == number)
		return spin;
	else
	{
		for (int i = 0; i < children.size(); i++)
		{
			x = children[i]->spinAt(_number);
			if (x != -100)//if it is found no need to further search
				break;
		}
	}
	return x;
}
void Node::addItoJ(int i, int j, int _weight)
{
	if (i == number)
	{
		/*If you have found the node you want add the other node to its children*/
		Node* N = new Node;
		N->assignNumber(j);
		weights.push_back(_weight);
		addChildren(N);
	}
	else
	{
		for (int k = 0; k < children.size(); k++)
			children[k]->addItoJ(i, j,_weight);
	}
}
void Node::addtoTree(int i, int j, int _weight)
{
	if (exist(i))//one of the nodes i or j must be already added to tree we find that and add the other one as its child
	{
		if (!exist(j))
			addItoJ(i, j,_weight);
	}
	else
	{
		if (exist(j))
			addItoJ(j, i, _weight);
	}
}
void Node::printTree()
{
	cout << " n= "<< number<< ", s="<<spin<<", ";
	for (int i = 0; i < children.size(); i++)
		children[i]->printTree();
}
void Node::assignWeight(int _weight)
{
	weight = _weight;
}
int Node::returnWeight()
{
	return weight;
}
void Node::assignWeightToNode(int i, int _weight)
{
	if (i == number)
	{
		weight = _weight;
	}
	else
	{
		for (int k = 0; k < children.size(); k++)
			children[k]->assignWeightToNode(i, _weight);
	}
}
void Node::calculateSpin()
{
	/*this is the most important function what we do is we decide the spin of a leaf based on its weight, if its weigh is 0 it is 
	undecided and unimporant at the moment so we consider it at zero and when its paretn got its spin we find the best spin for this node later*/
	if (children.size() == 0)
	{
		if (weight < 0)
			spin = 1;
		if (weight == 0)
			spin = 0;
		if (weight > 0)
			spin = -1;
		return;
	}
	for (int i = 0; i < children.size(); i++)
		children[i]->calculateSpin();//calculate the spin for all children
	int negativespin=0;
	int positivespin=0;
	//check if + or - sign for spin provides a better resu;t, if it does not matter, we can fix it
	//later when its parent got its spin
	for (int i = 0; i < children.size(); i++)
	{
		negativespin += (-1)*children[i]->returnSpin()*weights[i];
		positivespin += children[i]->returnSpin()*weights[i];
	}
	negativespin += (-1)*weight;
	positivespin += weight;
	if (positivespin < negativespin)
		spin = 1;
	if (positivespin == negativespin)
		spin = 0;
	if (positivespin > negativespin)
		spin = -1;
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->returnSpin() == 0)//we fix the 0 spins and find the best spin for it
		{
			if (spin*weights[i] > 0)
				children[i]->assignSpin(-1);
			else
				children[i]->assignSpin(1);
		}
	}
	return;
}
int Node::calculateEnergy()
{
	
	if (children.size() == 0)//its a leaf no children to find energy
	{
		Energy = spin*weight;
		return Energy;
	}
	for (int i = 0; i < children.size(); i++)
	{
		Energy += children[i]->calculateEnergy();//the energy of all children
	}
	for (int i = 0; i < children.size(); i++)
	{
		Energy += weights[i]*children[i]->spin*spin;//the energy of all weights
	}
	Energy += spin*weight;//the energy of the node itself
	return Energy;
}
string Node::Signs(int n)
{
	/*this function changes the spins to signs*/
	string s = "";
	for (int i = 0; i < n; i++)
	{
		if (spinAt(i) == -1)
			s += '-';
		else
			s += '+';
	}
	return s;

}
