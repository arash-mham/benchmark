// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <ctype.h>
#include<string>
#include<vector>
#include <hash_map>
#include <map>
#include"Node.h"
using namespace std;

map <int, int> H_map;//a hash map for weights of nodes

map<int, map<int, int> > J_map;//A hash map for weights of edges
vector<int>* connectionsArray;
int numberofNodes;
int numberofWeights;
vector<string> breakLine(string line)
{
	/*this function takes a line from a file and break it to a vector of strings by splitting at spaces*/
	vector<string> v;
	string s;
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')//split at space
		{
			if (s != "")//no empty string should be added to the file
			{
				v.push_back(s);//add to the vector if a space pops up
				s = "";
			}
		}
		else
		{
			s += line[i];//create the strinfg
		}
	}
	if (s != "")
		v.push_back(s);//check for the last strings to be added
	return v;

}
int* bruteforce()
{
	
	int possibleConditions = (int)pow(2, numberofNodes);//all possible conditions are 2^n
	int results [2];//the first entry is the minimum value the second is the configuration
	results[0] = 10000;
	int* S = new int[numberofNodes];
	
	for (int i = 0; i < possibleConditions; i++)//all possible conditions can be checked by bits of an integer value from 0 to 2^n
	{
		for (int j = 0; j < numberofNodes; j++)
		{
			int test = i & (int)pow(2, j);//find the ith bit
			if (test == 0)//check if its zero or one
				S[j] = -1;
			else
				S[j] = 1;
		}
		int FirstPartEnergy = 0;
		for (int k = 0; k < numberofNodes; k++)
		{
			FirstPartEnergy += S[k] * H_map[k];//Calculate the first part of the enery function
		}
		int SecondPartEnergy = 0;
		for (int k = 0; k < numberofNodes; k++)
		{
			for (int l = 0; l < numberofNodes; l++)
			{
				if (l > k)
				{
					SecondPartEnergy += J_map[k][l] * S[l] * S[k];//calculate the second part of the energy function
				}
			}
		}
		int TotalEnergy = FirstPartEnergy + SecondPartEnergy;//find the total energy function
		if (TotalEnergy < results[0])//check if it is minimum
		{
			results[0] = TotalEnergy;//update energy
			results[1] = i;//update bit configuration
		}

	}
	return results;
}
void readFile(string s)
{
	/*this method reads a file with a path at a given string and makes two hash maps for H and J and ignores comments*/
	string line;
	vector<string>vector_lines;
	fstream myfile;
	myfile.open(s);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.size() != 0)
			{
				vector<string> v;
				v = breakLine(line);
				if (v.size() != 0)
				{
					if (v[0] == "p")//check if the first string starts with p
					{
						numberofNodes = stoi(v[2]);
						numberofWeights = stoi(v[3]);
						connectionsArray = new vector<int>[numberofNodes];

					}
					else if (v[0] != "c")//ignore comments
					{
						if (v[0] == v[1])//check if the weight is for node or for edges
						{
							int key = stoi(v[0]);
							int data = stoi(v[2]);
							H_map[key] = data;//weight is for nodes
						}
						else
						{
							int key1 = stoi(v[0]);
							int key2 = stoi(v[1]);
							int data = stoi(v[2]);
							J_map[key1][key2] = data;//weight is for edges
							J_map[key2][key1] = data;
							connectionsArray[key1].push_back(key2);
						}
					}
				}
				
			}
		}

	}
	else
	{
		cout << "there is an error for opening the file!(reading)";
	}
	myfile.close();
	
}
Node* BuildTree()
{
	/*this functions builds the tree based on the hash function that we made for weights*/
	Node* N = new Node;
	N->assignNumber(0);
	for (int i = 0; i < numberofNodes; i++)//Note that it is not N^2 as we just only keep the connectivity of the graph that is sparse and cannot be a graph
	{
		for (int j = 0; j < connectionsArray[i].size(); j++)
			N->addtoTree(i, connectionsArray[i][j], J_map[i][connectionsArray[i][j]]);
	}
	for (int i = 0; i < numberofNodes; i++)
		N->assignWeightToNode(i, H_map[i]);
	return N;
}
string ByteofInt(int i)
{
	/*converts an integer number to signs*/
	string res="";
	int check = i;
	while (check > 0)
	{
		int j = check % 2;
		if (j == 0)
			res+='-';
		else
			res+='+';
		check = check / 2;
	}
	return res;
}
void Output()
{
	Node* N = BuildTree();
	N->calculateSpin();
	cout << N->calculateEnergy() << "\n";
	cout << N->Signs(numberofNodes)<<"\n";//creates the signs for the result configuration
}
void Output_BruteForce()//output the result of brute force algorithm
{
	int* results;
	results = bruteforce();//take the results from the brute force algorith results[0] is energy results[1] is configuration as an int. 
	int check = results[1];

	cout << "min Energy is " << results[0] << " the configuration is ";
	string s2 = ByteofInt(check);//bits of thsi integer number is the answer so it should be converted to + - signs
	cout << s2 << "\n";
}
int _tmain(int argc, _TCHAR* argv[])
{
	string s = "C:\\Users\\Tina\\Desktop\\files\\testFiles\\NOTES.txt";//You should include the path of the text files here
		

	readFile(s);
	

	Output();//efficient algorithm
	//Output_BruteForce();//check for vailifity
	int i;
	cin >> i;
	return 0;
}

