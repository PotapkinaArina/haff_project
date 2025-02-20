#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include "Huffman.h"
#define SIZE 256
using namespace std;


int main()
{   
    string fileName;
    cout << "Enter name of the file: ";
    cin >> fileName;

    ifstream input(fileName, ios::binary);

    int freq[SIZE] = { 0 }; 

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

    Node* root = createTree(freq);
 
}
