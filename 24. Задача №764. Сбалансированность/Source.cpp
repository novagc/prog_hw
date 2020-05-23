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
#include <random>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <regex>
#include <tuple>
#include <map>
#include <set>

using namespace std;

template<class T>
struct Node // ячейка дерева
{
    T data;

    Node<T>* left; // левый потомок
    Node<T>* right; // правый потомок
    Node<T>* parent; // родитель
    
    int dep;
    int dif;

    Node(T value, Node<T>* par = NULL)
    {
        data = value;
        left = NULL;
        right = NULL;
        parent = par;

        dep = 1;
        dif = 0;
    }

    void CalcDif()
    {
        dif = (right == NULL ? 0 : right->dep) - (left == NULL ? 0 : left->dep);
    }

    bool operator >(Node<T> node)
    {
        return data > node.data;
    }
};

template<class T>
struct BinTree
{
    Node<T>* root; // корневой элемент
    int count = 0;

    BinTree()
    {
        root = NULL;
    }

    void Add(T value)
    {
        Node<T>* temp = new Node<T>(value);

        if (count == 0)
        {
            root = temp;
            count++;
        }
        else
        {
            int res = Add(temp, root);

            if (!res)
                delete temp;
            else
                count++;
        }
    }

    bool Add(Node<T>* node, Node<T>* cur)
    {
        if (cur->data == node->data)
            return false;

        if (cur->data > node->data)
        {
            if (cur->right != NULL)
            {
                Add(node, cur->right);

                if (cur->right->dep == cur->dep)
                    cur->dep++;
            }
            else
            {
                cur->right = node;
                
                if (cur->dep == 1)
                    cur->dep++;
            }
        }
        else
        {
            if (cur->left != NULL)
            {
                Add(node, cur->left);

                if (cur->left->dep == cur->dep)
                    cur->dep++;
            }
            else
            {
                cur->left = node;

                if (cur->dep == 1)
                    cur->dep++;
            }
        }

        cur->CalcDif();

        return true;
    }

    bool IsBalanced()
    {
        return count > 2 ? CalcDif(root) : true;
    }

    bool CalcDif(Node<T>* cur)
    {
        bool l = true;
        bool r = true;

        if (cur->left != NULL)
            l = CalcDif(cur->left);

        if (cur->right != NULL)
            r = CalcDif(cur->right);

        return (abs(cur->dif) <= 1) && l && r;
    }

    Node<T>* FindNode(T value)
    {
        Node<T>* temp = root;

        while (temp != NULL && temp->data != value) // перебираем элементы, пока не находим нужный или пока не переберём все
            temp = temp->data > value ? temp->left : temp->right;

        return temp;
    }

    Node<T>* FindNextNode(T value)
    {
        return FindNextNode(FindNode(value));
    }

    Node<T>* FindNextNode(Node<T>* temp) //Взято из интернетов
    {
        Node<T>* res;

        if (temp == NULL)
            return NULL;
        if (temp->right != NULL)
            return FindMinNode(temp->right);

        res = temp->parent;

        while (res != NULL && temp == res->right)
        {
            temp = res;
            res = res->parent;
        }

        return res;
    }

    Node<T>* FindMinNode(Node<T>* temp)
    {
        if (temp == NULL)
            throw "Empty tree";

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    Node<T>* FindMaxNode(Node<T>* temp)
    {
        if (temp == NULL)
            throw "Empty tree";

        while (temp->right != NULL)
            temp = temp->right;

        return temp;
    }

    T Min()
    {
        return FindMinNode(root)->data;
    }

    T Max()
    {
        return FindMaxNode(root)->data;
    }

    Node<T>* DeleteNode(T value)
    {
        return DeleteNode(FindNode(value));
    }

    Node<T>* DeleteNode(Node<T>* node)
    {
        Node<T>* res;
        Node<T>* temp;

        if (node->left == NULL || node->right == NULL)
            res = node;
        else
            res = FindNextNode(node->data);

        if (res->left != NULL)
            temp = res->left;
        else
            temp = res->right;

        if (temp != NULL)
            temp->parent = res->parent;

        if (res->parent == NULL)
            root = temp;
        else
        {
            if (res == (res->parent)->left)
                (res->parent)->left = temp;
            else
                (res->parent)->right = temp;
        }

        if (res != node)
            node->data = res->data;

        return res;
    }

    void print(int type = 0, char sep = ' ')
    {
        if (type == 0)
            LKP(root, sep);
        else if (type > 0)
            KLP(root, sep);
        else
            LPK(root, sep);
    }

    void LKP(Node<T>* node, char sep) // левый корень правый
    {
        if (node->left != NULL)
            LKP(node->left, sep);

        cout << node->data << sep;

        if (node->right != NULL)
            LKP(node->right, sep);
    }

    void KLP(Node<T>* node, char sep) // корень левый правый
    {
        cout << node->data << sep;

        if (node->left != NULL)
            KLP(node->left, sep);

        if (node->right != NULL)
            KLP(node->right, sep);
    }

    void LPK(Node<T>* node, char sep) // левый правый корень
    {
        if (node->left != NULL)
            LPK(node->left, sep);

        if (node->right != NULL)
            LPK(node->right, sep);

        cout << node->data << sep;
    }
};


int main()
{
    BinTree<int> bt;
    int temp;

    for (cin >> temp; temp != 0; cin >> temp)
        bt.Add(temp);

    cout << (bt.IsBalanced() ? "YES" : "NO");

	return 0;
}
