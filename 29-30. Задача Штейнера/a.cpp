#include <iostream>
#include <fstream>

using namespace std;

const int size_key = 10;
const int size_value = 20;


int main()
{
		char *temp = new char[size_key + size_value + 3];
		char *tmp = temp + size_key + 1;

		temp[size_key + size_value + 1] = '\n';
		temp[size_key + size_value + 2] = '\0';

		for (int j = 0; j < 10e6; j++) 
		{
			for (int i = 0; i < size_key; i++)
			{
				temp[i] = 'A' + rand() % 26;
			}

			temp[size_key] = ' ';

			for (int i = 0; i < size_value; i++)
			{
				tmp[i] = 'a' + rand() % 26;
			}

			cout << temp;
		}
		
	return 0;
}
