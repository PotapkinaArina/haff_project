#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Huffman.h"
using namespace std;


int main()
{
    string fileName;
    int choice;
    cout << "Enter name of the file to process: ";
    cin >> fileName;
    cout << "\nWould you like to compress or decompress this file? Enter 1 or 2 respectively: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
            if (fileName == "encode.txt")
            {
                cout << "This file is for decoding!" << endl;
                break;
            }

            ifstream input(fileName, ios::binary);
            char point = '.';
            size_t pos = fileName.find_last_of(point);
            string format = fileName.substr(pos + 1);

            int freq[SIZE] = { 0 }; //массив частот

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

            int tail = 0;

            ofstream encode;
            encode.open("encode.txt", ios::binary);
            encode << bit_string2encode_text(encode_string(givenStr, sCodes), tail);
            encode.close();

            //создание дата-файла
            ofstream data("data.txt", ios::binary);
            data << "format-" << format << endl;
            data << "tail-" << tail << endl;

            for (int i = 0; i < SIZE; i++)
            {
                if (sCodes[i].size() != 0)
                {
                    data << char(i) << ' ' << sCodes[i] << endl;
                }
            }
            data.close();

            cout << "\nCompression done!" << endl;
            break;
        }
        case 2:
        {
            if (fileName != "encode.txt")
            {
                cout << "This file is not for decoding!" << endl;
                break;
            }

            ifstream data_("data.txt", ios::binary);
            string line;
            string format;
            int tail = 0;
            while (std::getline(data_, line))
            {
                if (line.find("format-") != std::string::npos) 
                {
                    format = line.substr(line.find("-") + 1);
                }
                else if (line.find("tail-") != std::string::npos) 
                {
                    tail = stoi(line.substr(line.find("-") + 1)); // Извлечение итога из строки
                }
            }
            data_.close();

            ifstream input_("encode.txt", ios::binary);
            string encode_text;
            char ch;
            while (input_.get(ch)) 
            {
                encode_text += ch;
            }
            input_.close();

            string str = encode_text2bit_string(encode_text);

            string dec = "decoded." + format;
            ofstream decode(dec, ios::binary);
            decode << bit_string2decode_text(str, root);
            decode.close();

            cout << "\nDecompression done!" << endl;
            break;
        }
    }
}

