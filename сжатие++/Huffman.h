#pragma once
#include <iostream>
using namespace std;

struct Node
{
	unsigned char symb;
	unsigned int freq;
	Node* left, * right;
};

struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

Node* createNode(unsigned char symb, unsigned int freq, Node* left, Node* right);
Node* createTree(const int freq[]);