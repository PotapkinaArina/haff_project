#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Huffman.h"
using namespace std;

Node* createNode(unsigned char symb, unsigned int freq, Node* left, Node* right)
{
	Node* node = new Node();
	node->symb = symb;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

Node* createTree(const int freq[])
{
	//создание очереди с приоритетом
	priority_queue<Node*, vector<Node*>, comp> pq;
	for (int i = 0; i < SIZE; i++)
	{
		if (freq[i] != 0)
		{
			Node* newNode = createNode(char(i), freq[i], nullptr, nullptr);
			pq.push(newNode); //кладем ноду в очередь
		}
	}
	//создание дерева на основе очереди
	while (pq.size() != 1)
	{
		Node* left = pq.top();
		pq.pop();
		Node* right = pq.top();
		pq.pop();
		int false_node_sum = left->freq + right->freq;
		Node* newFalseNode = createNode('\0', false_node_sum, left, right);
		pq.push(newFalseNode);
	}
	Node* root = pq.top();
	return root;
}

//функция кодировки
void encode(Node* root, string str, string sCodes[])
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right)
	{
		sCodes[root->symb] = str;
		return;
	}
	encode(root->left, str + '0', sCodes);
	encode(root->right, str + '1', sCodes);
}

//сюда передается исходная строка и массив кодов
string encode_string(const vector<unsigned char>& givenStr, const string sCodes[])
{
	string encodedStr = ""; //исходная строка в виде кодов
	for (int i = 0; i < givenStr.size(); ++i)
	{
		unsigned char byte = givenStr[i];
		string code = sCodes[byte];
		if (!code.empty())
		{
			encodedStr += code;
		}
	}
	cout << encodedStr << endl;
	return encodedStr;
}