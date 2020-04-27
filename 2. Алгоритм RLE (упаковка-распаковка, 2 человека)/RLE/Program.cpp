#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <regex>
#include <map>
#include <set>

using namespace std;

void Encode(string path)
{
    ifstream input (path, ios::binary | ios::in);
    ofstream output(path + "_encoded", ios::binary | ios::out);

    char count = 0;

    char temp[128];
    char byte = 0;
    char prevByte = 0;
    
    bool type;

    while (!input.eof())
    {
        if (count == 0)
        {
            input.read((char*)&byte, 1);
            count++;
            temp[0] = byte;
        }
        else if (count == 1)
        {
            input.read((char*)&byte, 1);
            type = byte == temp[0];
            temp[1] = byte;
            count++;
        }
        else
        {
            input.read((char*)&byte, 1);
            
            if (type != (byte == temp[count - 1]) || count == 127)
            {
                if (type)
                {
                    output.write((char*)&count, 1);
                    output.write((char*)&(temp[0]), 1);
                }
                else
                {
                    count = -count;
                    output.write((char*)&count, 1);
                    for (int i = 0; i < -count; i++)
                        output.write((char*)&(temp[i]), 1);
                }

                count = 0;
            }

            temp[count++] = byte;
        }
    }
    if (count != 0)
    {
        if (type)
        {
            output.write((char*)&count, 1);
            output.write((char*)&(temp[0]), 1);
        }
        else
        {
            count = -count;
            output.write((char*)&count, 1);

            for (int i = 0; i < -count; i++)
                output.write((char*)&(temp[i]), 1);
        }
    }
    input.close();
    output.close();
}

void Decode(string path)
{
    ifstream input (path, ios::binary | ios::in);
    ofstream output(path + "_decoded", ios::binary | ios::out);

    char byte;
    char temp;

    while (!input.eof())
    {
        input.read((char *)(&byte), 1);
        if(byte > 0)
        {
            input.read((char*)(&temp), 1);
            for (int i = 0; i < byte; i++)
                output.write((char*)(&temp), 1);
        }
        else
        {
            for(int i = 0; i < -byte; i++)
            {
                input.read((char*)(&temp), 1);
                output.write((char*)(&temp), 1);
            }
        }
    }
    input.close();
    output.close();
}

int main()
{
    setlocale(LC_ALL, "Russian");
    
    string path;
    int command;

    cout << "Путь к файлу: ";
    cin >> path;

    cout << "1) Заархивировать\n2) Разархивировать\n";
    cin >> command;

    switch (command)
    {
        case 1:
            Encode(path);
            break;
        case 2:
            Decode(path);
            break;
        default:
            break;
    }

    return 0;
}