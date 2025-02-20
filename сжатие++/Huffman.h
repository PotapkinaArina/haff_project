#pragma once
#include <iostream>
#define SIZE 256
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
void encode(Node* root, string str, string sCodes[]);
string encode_string(const vector<unsigned char>& givenStr, const string sCodes[]);