#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#define SIZE 256
using namespace std;

struct Node
{
    unsigned char symb;
    unsigned int freq;
    Node* left, * right;
};


//���������� ���� �� ������
Node* createNode(unsigned char symb, unsigned int freq, Node* left, Node* right)
{
    Node* node = new Node();
    node->symb = symb;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp //��� ����������� ���������� ������� �� ������� 
{
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};

Node* createTree(const int freq[])
{
    //�������� ������� � �����������
    priority_queue<Node*, vector<Node*>, comp> pq;
    for (int i = 0; i < SIZE; i++)
    {
        if (freq[i] != 0)
        {
            Node* newNode = createNode(char(i), freq[i], nullptr, nullptr);
            pq.push(newNode); //������ ���� � �������
        }
    }
    //�������� ������ �� ������ �������
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

//������� ���������
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

//���� ���������� �������� ������ � ������ �����
string encode_string(const vector<unsigned char>& givenStr, const string sCodes[])
{
    string encodedStr = ""; //�������� ������ � ���� �����
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

int main()
{
    string fileName;
    cout << "Enter name of the file: ";
    cin >> fileName;

    ifstream input(fileName, ios::binary);

    int freq[SIZE] = { 0 }; //������ ������

    vector<unsigned char> givenStr;
    unsigned char byte;
    while (input.read(reinterpret_cast<char*>(&byte), 1))
    {
        givenStr.push_back(byte);
    }
    input.close();

    for (unsigned char c : givenStr)
    {
        freq[c]++;
    }

    for (int i = 0; i < SIZE; i++)
    {
        if (freq[i] != 0) cout << freq[i] << ' ' << char(i) << endl;
    }

    Node* root = createTree(freq);

    string sCodes[SIZE];
    encode(root, "", sCodes);
    for (int s = 0; s < SIZE; s++)
    {
        if (!(sCodes[s].empty()))
            cout << sCodes[s] << char(s) << endl;
    }

    encode_string(givenStr, sCodes);

    return 0;
}
