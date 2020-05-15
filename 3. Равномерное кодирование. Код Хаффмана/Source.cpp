#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>
#include <limits.h>

#include <algorithm>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <regex>
#include <map>
#include <set>

using namespace std;

struct Node
{
	char key;
	int freq;
	Node* left;
	Node* right;
	Node(char _key, int _freq) { 
		key = _key; 
		left = NULL;
		right = NULL; 
		freq = _freq; 
	}
};

bool Compare(Node* f, Node* s)
{
	return f->freq < s->freq;
}

class HTree
{
public:
	Node* root;
	string* eTable;
	string str;
	string code;
	int countTable[256]{ 0 };

	HTree(string _str)
	{
		root = NULL;
		str = _str;
		Build();
	}

	void Build()
	{
		
		int stCount = 0;
		Node** st = new Node* [256];

		for (int i = 0; i < str.length(); i++)
			countTable[str[i]]++;

		for (int i = 0; i < 256; i++)
		{
			if (countTable[i])
			{
				st[stCount++] = new Node(i, countTable[i]);
			}
		}

		int unic = stCount;

		while (stCount > 1)
		{
			sort(st, st + stCount, Compare);
			st[0] = Combine(st[0], st[1]);
			stCount--;
			st[1] = st[stCount];
		}

		root = st[0];
		MakeTable();
	}

	Node* Combine(Node* f, Node* s)
	{
		Node* temp = new Node('#', f->freq + s->freq);
		temp->left = f;
		temp->right = s;
		return temp;
	}

	void MakeTable()
	{
		eTable = new string[256]{ "" };
		Traversal(root, "");
	}

	void Traversal(Node* node, string code)
	{
		if (node->key != '#')
			eTable[node->key] = code;

		if (node->left && node->right)
		{
			Traversal(node->left, code + '0');
			Traversal(node->right, code + '1');
		}
	}

	bool IsLeaf(string str)
	{
		return !GetNode(str)->left;
	}

	Node* GetNode(string str)
	{
		Node* node = root;
		for (int i = 0; i < str.length(); i++)
		{
			node = str[i] == '0' ? node->left : node->right;
		}
		return node;
	}

	string Encode()
	{
		for (int i = 0; i < str.length(); i++)
		{
			code += eTable[str[i]];
		}
		return code;
	}

	string Decode()
	{
		string temp = "";
		string result = "";
		for (int i = 0; i < code.length(); i++)
		{
			temp += code[i];
			if (IsLeaf(temp))
			{
				result += GetNode(temp)->key;
				temp = "";
			}
		}
		return result;
	}
};

int main()
{
	ifstream input("input.txt", ios::in);
	freopen("output.txt", "w", stdout);

	string all = "";
	string temp;

	while (true) {
		getline(input, temp);
		all += temp;
		
		if (input.eof())
			break;

		all += "\n";
	}

	HTree tree(all);

	for (int i = 0; i < 256; i++)
		if (tree.countTable[i])
			cout << '"' << char(i) << '"' << ":\t" << tree.countTable[i] << '\n';

	cout << "\n\n\n";

	for (int i = 0; i < 256; i++)
		if (tree.eTable[i] != "")
			cout << (char)i << " " << tree.eTable[i] << '\n';

	cout << "\n\n\n";

	cout << tree.Encode() << '\n';

	cout << "\n\n\n";

	cout << tree.Decode() << '\n';

	return 0;
}