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

template<typename TT_cont>
void Print(TT_cont const& cont)
{
    copy(cont.begin(), cont.end(), ostream_iterator<typename TT_cont::value_type>(cout, " "));
    cout << endl;
}

void SetLongestIncreasingSubsequence(deque<int> const& numbers, deque<int>& subsequence)
{
    int         numbers_size = numbers.size();
    deque<int>   seq_lens(numbers_size, 1);
    deque<int>   prev_indexes(numbers_size);
    int         seq_len_max = 1;
    int         last_ind = 0;

    for (int i = 1; i < numbers_size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (numbers[j] < numbers[i] && seq_lens[j] + 1 > seq_lens[i])
            {
                seq_lens[i] = seq_lens[j] + 1;
                prev_indexes[i] = j;

                if (seq_lens[i] > seq_len_max)
                {
                    seq_len_max = seq_lens[i];
                    last_ind = i;
                }
            }
        }
    }

    while (int(subsequence.size()) < seq_len_max)
    {
        subsequence.push_front(numbers[last_ind]);
        last_ind = prev_indexes[last_ind];
    }
}

int main()
{
    int n, temp;
    deque<int> numbers;
    deque<int> subsequence;

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        numbers.push_back(temp);
    }

    SetLongestIncreasingSubsequence(numbers, subsequence);
    cout << subsequence.size() << '\n';
    Print(subsequence);

    return 0;
}