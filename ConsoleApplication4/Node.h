#pragma once
#include<vector>
using namespace std;
class Node
{
private:
	vector<Node*> children;
	vector<int> weights;//weight for edges (children)
	int spin;
	int number;//key of the node
	int weight;//Node weight
	void addItoJ(int i, int j,int weight);//this function adds the node j to i or i to j with its weight 

	
public:
	Node();
	~Node();
	void addChildren(Node*);//adds a child to an already included node
	int numberofChildren();//returns the number of the children of a node
	int Energy=0;//sum of energy of a node
	Node* childat(int);//return ith child of a node
	void assignSpin(int);//assign a spin number to a node
	int returnSpin();//returns the spin of a node
	void assignWeight(int);//assign a wright number to a node
	int returnWeight();//returns the wright of a node
	void assignNumber(int);//assigns an integer to the key of node
	int returnNumber();//return he key
	bool exist(int);//checks if a node with a key available
	void addtoTree(int, int, int);//adds a node with a wright to the tree
	void printTree();//prints the tree for debugging
	void assignWeightToNode(int, int);//assigns a weight to a node
	void calculateSpin();//calculates the spin based on the dynamic programming algorithms
	int calculateEnergy();//calculates the sum of energy for each node and retrurn the total eneregy
	string Signs(int);//return the configuration as a series of signs
	int spinAt(int _number);//return the spin of a node with key _number
};

