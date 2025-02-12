#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#define SIZE 256
using namespace std;

//нода для очереди и дерева
struct Node
{
	unsigned char symb;
	unsigned char isSymb;
	unsigned int freq;
	Node* left, * right, * next;
};


//добавление ноды на дерево
Node* putNode(unsigned char symb, unsigned int freq, Node* left, Node* right)
{
	Node* node = new Node(); 
	node->symb = symb;
	node->left = left;
	node->right = right;

	return node;
}

int main()
{
	FILE* fr = fopen("input.txt", "rb");
	if (!fr)
		return -1;
	fseek(fr, 0L, SEEK_END);
	long length = ftell(fr);
	fseek(fr, 0, SEEK_SET);

	int freq[SIZE] = { 0 }; //массив частот
	for (int i = 0; i < length; ++i)
	{
		freq[(unsigned char)fgetc(fr)]++;
	}
	fclose(fr);

	int symb_count = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (freq[i] != 0) cout << freq[i] << endl;
		symb_count++;
	}
	return 0;
}