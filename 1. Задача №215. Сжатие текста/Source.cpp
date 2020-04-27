#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <algorithm>
#include <tuple>
#include <list>

using namespace std;

int main()
{
    int r, n;
    
    cin >> r >> n;

    vector<string> longVar(r);
    vector<string> shortVar (r);

    getline(cin, longVar[0]);

    for (int i = 0; i < r; i++)
    {
        getline(cin, longVar[i]);
        getline(cin, shortVar[i]);
    }

    for (int i = 0; i < n; i++)
    {
        string temp;
        getline(cin, temp);

        vector<string> ans(temp.size() + 1);
        ans[0] = "";

        for (int j = 1; j <= temp.size(); j++)
        {
            ans[j] = ans[j - 1] + temp[j - 1];

            for (int k = 0; k < r; k++)
            {
                int l = longVar[k].size();

                if (l <= j && temp.compare(j - l, l, longVar[k]) == 0 && ans[j - l].size() + 1 < ans[j].size())
                    ans[j] = ans[j - l] + shortVar[k];
            }
        }

        cout << ans[temp.size()] << '\n';
    }

    return 0;
}