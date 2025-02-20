#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "Huffman.h"

#define BIT8 8
#define SIZE 256

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

string bit_string2encode_text(string encode_string_)
{
	string encode_text = "";
	int lenght = encode_string_.size();
	int tail = lenght % BIT8;
	char symbol = 0;
	for (int i = 0; i < lenght; i++) {
		symbol <<= 1;
		symbol += encode_string_[i] - '0';
		if (i % BIT8 == BIT8 - 1) {
			encode_text + symbol;
			symbol = 0;
		}
	}
	encode_text += symbol;
	return encode_text;
}

string symbol_byte(int lenght_, unsigned symbol_)
{
	string byte(lenght_, ' ');
	for (int i = 0; i < lenght_; i++) {
		byte[lenght_ - 1 - i] = '0' + symbol_ % 2;
		symbol_ /= 2;
	}
	return byte;
}

string encode_text2bit_string(string encode_text_)
{
	string bit_string = "";
	string bytes[SIZE];
	//int tail;
	int lenght = encode_text_.size();
	for (int i = 0; i < lenght - 1; i++) {
		unsigned char symbol = encode_text_[i];
		if (bytes[symbol] == "")
			bytes[symbol] = symbol_byte(BIT8, symbol);
	}
	//bit_string += symbol_byte(tail, encode_text_[lenght - 1]);
	return bit_string;
}

string bit_string2decode_text(string bit_string_, Node* root_)
{
	string decode_text;
	Node* root = root_;
	for (int i = 0; i < bit_string_.size(); i++) {
		if (bit_string_[i] == '0')
			root_ = root_->left;
		else
			root_ = root_->right;
		if (!root_->left && !root_->right) {
			decode_text += root_->symb;
			root_ = root;
		}
	}
	return decode_text;
}
