#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>

#include <algorithm>
#include <iostream>
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
        this->previous = NULL;
        this->value = value;
    }

    Node* previous; // указатель на предыдущую ячейку
    Node* next; // указатель на следующую ячейку
    T value; // значение, хранимое в ячейке
};

template<class T>
struct Cl
{
    long long count;

    Node<T>* head;
    Node<T>* tail;
    Node<T>* curr;

    Cl()
    {
        count = 0;
        head = NULL;
        tail = NULL;
        curr = NULL;
    }

    void Add(T value)
    {
        Node<T>* temp = new Node<T>(value);

        if (count == 0)
        {
            head = temp;
            tail = temp;

            temp->next = temp;
            temp->previous = temp;
            
            curr = temp;
        }
        else
        {
            temp->next = head;
            head->previous = temp;

            temp->previous = tail;
            tail->next = temp;
            tail = temp;
        }

        count++;
    }

    void Next()
    {
        curr = curr->next;
    }

    void Previous()
    {
        curr = curr->previous;
    }

    T Value()
    {
        return curr->value;
    }

    T Remove()
    {
        T temp = Value();

        if (curr == curr->next)
        {
            head = NULL;
            tail = NULL;

            delete curr;

            curr = NULL;
        }
        else
        {
            curr->next->previous = curr->previous;
            curr->previous->next = curr->next;

            if (curr == head)
            {
                head = curr->next;
            }
            if (curr == tail)
            {
                tail = curr->previous;
            }

            Node<T>* n = curr->next;
            delete curr;
            curr = n;
        }

        count--;
        return temp;
    }

    long long Count()
    {
        return count;
    }

    void Clear()
    {
        Node<T>* temp = head->next;
        Node<T>* next;

        while (temp != temp->next)
        {
            next = temp->next;
            Remove(temp);
            temp = next;
        }

        head = NULL;
        tail = head;
        count = 0;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;

    Cl<int> _;

    for (int i = 1; i <= n; i++)
    {
        _.Add(i);
    }

    for (; _.Count() > 0;)
    {
        for (int i = 1; i < k; i++)
        {
            _.Next();
        }
        cout << _.Remove() << ' ';
    }

	return 0;
}