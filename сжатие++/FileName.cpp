#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#define SIZE 256
using namespace std;

//���� ��� ������� � ������
struct Node
{
	unsigned char symb;
	unsigned char isSymb;
	unsigned int freq;
	Node* left, * right, * next;
};


//���������� ���� �� ������
Node* putNode(unsigned char symb, unsigned int freq, Node* left, Node* right)
{
	Node* node = new Node(); 
	node->symb = symb;
	node->left = left;
	node->right = right;

	return node;
}

void encode(Node* root, string str, string sCodes[])
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right)
	{
		for (int s = 0; s < SIZE; ++s)
		{
			if (sCodes[s].empty())
			{
				sCodes[s] = str;
				return;
			}
		}
	}
	encode(root->left, str + '0', sCodes);
	encode(root->right, str + '1', sCodes);
}

int main()
{
	FILE* fr = fopen("input.txt", "rb");
	if (!fr)
		return -1;
	fseek(fr, 0L, SEEK_END);
	long length = ftell(fr);
	fseek(fr, 0, SEEK_SET);

	int freq[SIZE] = { 0 }; //������ ������
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

	string sCodes[SIZE];

	return 0;
}