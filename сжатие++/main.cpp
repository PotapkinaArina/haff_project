#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include "Huffman.h"
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
