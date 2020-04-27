#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <string>
#include <vector>
#include <cstdio>
#include <queue>
#include <stack>
#include <ctime>
#include <cmath>
#include <regex>
#include <map>
#include <set>

using namespace std;

template<class T>
struct Node // ячейка
{
    Node(T value)
    {
        this->next = NULL;
        this->value = value;
    }

    Node* next; // указатель на следующую ячейку
    T value; // значение, хранимое в ячейке
};

template<class T>
struct Stack
{
    long long count;

    Node<T>* head; // указатель на левую границу

    Stack()
    {
        count = 0;

        head = new Node<T>(0);

        head->next = NULL;
    }

    void PushFront(T value) // аналогично PushBack
    {
        Node<T>* temp = new Node<T>(value);

        temp->next = head->next;
        head->next = temp;

        count++;
    }

    T PopFront() // аналогично PopBack
    {
        if (count > 0)
        {
            T temp = head->next->value;
            Node<T>* toDelete = head->next;
            count--;

            head->next = head->next->next;

            delete toDelete;
            return temp;
        }
        else
        {
            throw "Empty queue";
        }
    }

    T First()
    {
        if (count > 0)
            return head->next->value;
        else
            throw "Empty queue";
    }

    long long Count()
    {
        return count;
    }

    bool IsEmpty()
    {
        return count == 0;
    }

    void Clear()
    {
        Node<T>* temp = head->next;
        Node<T>* next;

        for(int i = 0; i < count; i++)
        {
            next = temp->next;
            delete temp;
            temp = next;
        }

        head->next = NULL;
        count = 0;
    }

    void Print(Node<T>* t)
    {
        if (t != NULL)
        {
            Print(t->next);
            cout << t->value << ' ';
        }
    }
};


int main()
{
    ifstream input("input.txt");
    freopen("output.txt", "w", stdout);
    Stack<int> stack;
    string command;
    bool err = false;
    try
    {
        while (!input.eof())
        {
            getline(input, command);
            if (command == "")
                break;

            if (command[0] == '-')
                stack.PopFront();
            else 
            {
                string temp = command.substr(1);
                stack.PushFront(atoi(temp.c_str()));
            }
        }

        if (stack.Count() == 0)
        {
            cout << "EMPTY";
        }
        else
        {
            stack.Print(stack.head->next);  
        }
    }
    catch (...)
    {
        cout << "ERROR";
    }
	return 0;
}