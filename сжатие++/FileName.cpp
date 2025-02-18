#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
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


//добавление ноды на дерево
Node* createNode(unsigned char symb, unsigned int freq, Node* left, Node* right)
{
    Node* node = new Node();
    node->symb = symb;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

struct comp //для выставления приориетов очереди по частоте 
{
    bool operator()(Node* l, Node* r)
    {
        return l->freq > r->freq;
    }
};

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
string encode_string(const string& str, const string sCodes[])
{
    string encodedStr = ""; //исходная строка в виде кодов
    for (int i = 0; i < str.length(); ++i)
    {
        char c = str[i];
        string code = sCodes[(int)c];
        if (code.empty())
            continue;
        encodedStr += code;
    }
    cout << encodedStr << endl;
    return encodedStr;
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

    string givenStr = "";
    for (int i = 0; i < length; ++i)
    {
        char c = fgetc(fr);
        freq[(unsigned char)c]++;
        givenStr += c;
    }
    fclose(fr);

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