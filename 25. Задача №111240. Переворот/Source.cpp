#define _CRT_SECURE_NO_WARNINGS
#define ll long long

#include <stdio.h>
#include <limits.h>

#include <algorithm>
#include <stdexcept>
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

struct Node {
	int data;
	int priority;
	int min_val;
	int subtree_size;
	bool reversed;
	Node* left;
	Node* right;

	Node()
	{
		subtree_size = 0;
		data = 0;
		min_val = 0;
		priority = 0;
		left = NULL;
		right = NULL;
		reversed = false;
	}

	Node(int _data, int _priority, Node* _parent = NULL, Node* _left = NULL, Node* _right = NULL)
	{
		subtree_size = 1;
		data = _data;
		min_val = _data;
		priority = _priority;
		left = _left;
		right = _right;
		reversed = false;
	}

	int Min(Node* a, Node* b) 
	{
		if (a == NULL && b == NULL)
			return 1e9 + 1;
		else if (a == NULL)
			return b->min_val;
		else if (b == NULL)
			return a->min_val;
		else
			return min(a->min_val, b->min_val);
	}

	void Recalc() 
	{
		subtree_size = (left == NULL ? 0 : left->subtree_size) + (right == NULL ? 0 : right->subtree_size) + 1;
		min_val = min(Min(left, right), data);
	}
};

struct Treap {
public:
	Node* root;

	Treap()
	{
		root = NULL;
	}

	Treap(int x, int y)
	{
		root = new Node(x, y);
	}

	void Push(Node* root) 
	{
		if (root == NULL || !root->reversed) return;

		swap(root->left, root->right);
		root->reversed = false;

		if (root->left != NULL) root->left->reversed ^= true;
		if (root->right != NULL) root->right->reversed ^= true;
	}

	void Merge(Node* L, Node* R) 
	{
		Merge(L, R, root);
	}

	void Merge(Node* L, Node* R, Node*& root) 
	{
		Push(L);
		Push(R);

		if (L == NULL) 
		{
			root = R;
			return;
		}
		else if (R == NULL) 
		{
			root = L;
			return;
		}
		else if (L->priority > R->priority) 
		{
			root = L;
			Merge(L->right, R, root->right);
		}
		else 
		{
			root = R;
			Merge(L, R->left, root->left);
		}

		root->Recalc();
	}


	void Split(int idx, Node*& L, Node*& R) 
	{
		Split(idx, L, R, root);
	}

	void Split(int idx, Node*& L, Node*& R, Node* root) 
	{
		Push(root);

		int sL = root->left != NULL ? root->left->subtree_size + 1 : 1;
		if (sL <= idx) 
		{
			L = root;
			if (root->right != NULL)
				Split(idx - sL, root->right, R, root->right);
			else R = NULL;

			root->Recalc();

		}
		else 
		{
			R = root;
			if (root->left != NULL)
				Split(idx, L, root->left, root->left);
			else L = NULL;

			root->Recalc();
		}
	}

	void PushBack(int data) 
	{
		int priority = rand();

		if (root == NULL) 
			root = new Node(data, priority);
		else 
			Merge(root, new Node(data, priority), root);
	}

	void PushAfter(int idx, int data) 
	{
		if (root != NULL) {
			Node* tmp = new Node;

			Split(idx, root, tmp);

			Merge(root, new Node(data, rand()));
			Merge(root, tmp);
		}
		else 
			root = new Node(data, rand());
	}

	int MinOf(int idxA, int idxB) 
	{
		idxB -= idxA - 1;

		Node* middle(new Node);
		Node* right (new Node);

		Split(idxA - 1, root, middle);
		Split(idxB, middle, right, middle);

		int ret = middle->min_val;

		Merge(root, middle);
		Merge(root, right);

		return ret;
	}

	void Reverce(int idxA, int idxB) 
	{
		idxB -= idxA - 1;

		Node* middle(new Node); 
		Node* right (new Node);

		Split(idxA - 1, root, middle);
		Split(idxB, middle, right, middle);

		middle->reversed ^= true;

		Merge(root, middle);
		Merge(root, right);
	}

	void InorderTraversal() 
	{
		InorderTraversal(root);
	}

	void InorderTraversal(Node* root) 
	{
		Push(root);

		if (root != NULL) {
			InorderTraversal(root->left);

			cout << root->data << ' ';

			InorderTraversal(root->right);
		}
	}

	void Move(int begin, int end) 
	{
		end -= begin - 1;

		Treap middle, right;

		Split(begin - 1, root, middle.root);

		middle.Split(end, middle.root, right.root, middle.root);

		Merge(root, right.root);
		Merge(middle.root, root);
	}

	int& operator[] (int idx) 
	{
		Node* curr = root;
		while (curr->left != NULL && curr->left->subtree_size != idx) 
		{
			if (curr->left->subtree_size > idx)
			{
				curr = curr->left;
			}
			else
			{
				curr = curr->right;
				idx -= curr->subtree_size;
			}
		}

		if (curr == NULL)
			if (curr->left == NULL)
				return curr->data;
			else
				throw out_of_range("no item with that index");
	}
};



int main() 
{
	int n; 
	int m;
	int a;
	int b;
	int tmp;
	int cmd;

	Treap tr;

	cin >> n >> m;

	while (n-- > 0) 
	{
		cin >> tmp;
		tr.PushBack(tmp);
	}

	while (m-- > 0) 
	{
		cin >> cmd >> a >> b;

		switch (cmd) 
		{
			case 1:
				tr.Reverce(a, b);
				break;

			case 2:
				cout << tr.MinOf(a, b) << endl;
				break;
		}
	}
}