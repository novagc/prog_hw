#define _CRT_SECURE_NO_WARNINGS
#define ll long long
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
struct Node // ячейка очереди
{
    Node *next; // указатель на следующую ячейку
    T value; // значение, хранимое в ячейке

    Node(T value)
    {
        this->next = NULL;
        this->value = value;
    }

};

template<class T>
struct Queue
{
    long long count; // кол-во элементов в очереди

    Node<T> *first; // указатель на первый элемент в очереди
    Node<T> *last; // указатель на последний элемент в очереди
    Node<T> *middle;

    Queue()
    {
        count = 0;
        first = NULL;
        last = NULL;
        middle = NULL;
    }

    void Push(T value)
    {
        Node<T> *temp = new Node<T>(value); // сначала создаём новую ячейку

        // если очередь не пустая
        // следующей за последней ячейкой в очереди будет наша новая ячейка
        // указатель на последний элемент будет указывать на нашу новую ячейку
        if(count > 0) 
        {
            last->next = temp;
            last = temp;

            if (count % 2 == 0)
                middle = middle->next;
        }
        else
        {
            first = temp;
            last = temp;    
            middle = temp;
        }

        //увеличиваем кол-во элементов на 1
        count++;
    }

    void CoolPush(T value)
    {
        if(count > 1)
        {
            Node<T> *temp = new Node<T>(value);
            temp->next = middle->next;
            middle->next = temp;

            if (count % 2 == 0)
                middle = temp;

            count++;
        }
        else
        {
            Push(value);
        }
        
    }

    T Pop()
    {
        T temp = first->value; // сохраняем значение
        Node<T> * toDelete = first; // сохраняем указатель на ячейку, которую нужно удалить
        first = first->next; // теперь первым элементом в очереди будет следующая ячейка

        if (count % 2 == 0 && count > 1 )
        {
            middle = middle->next;
        }
        else if (count == 1)
        {
            middle = NULL;
        }

        count--;
        delete toDelete; // удаляем старую ненужную ячейку 

        return temp; // возвращаем значение
    }

    T First()
    {
        return first->value; // возвращаем значение первого элемента
    }

    T Last()
    {
        return last->value; // возвращаем значение последнего элемента
    }

    long long Count()
    {
        return count;
    }

    void Clear()
    {
        //в temp хранится указатель на ячейку, которую будем удалять
        //в next хранится следующая за temp ячейка
        Node<T> *temp = first;
        Node<T> *next;
        
        //удаляем ячейки, пока не удалим все
        while(temp != NULL)
        {
            next = temp->next;
            delete temp;
            temp = next;
        }

        //обнуяем все значения
        first = NULL;
        last = NULL;
        count = 0;
    }
};

int main()
{
    Queue<ll> q;

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    char command;
    ll temp;
    int n;
    
    cin >> n;

    for(int i = 0; i < n; i++)
    {
        cin >> command;
        if (command == '+')
        {
            cin >> temp;
            q.Push(temp);
        }
        else if (command == '-')
        {
            cout << q.Pop() << '\n';
        }
        else if (command == '*')
        {
            cin >> temp;
            q.CoolPush(temp);
        }
    }

    return 0;
}