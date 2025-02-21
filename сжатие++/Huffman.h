#pragma once
#include <iostream>
#define SIZE 256
#define BIT8 8
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
string bit_string2encode_text(string encode_string_,int& tail_);
string symb_bit(int lenght_, unsigned symb_);
string encode_text2bit_string(string encode_text_);
string bit_string2decode_text(string bit_string_, Node* root_);