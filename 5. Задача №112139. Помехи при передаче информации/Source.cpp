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

vector<vector<int> > cache;
string a, b;

int dp(int i, int j)
{
    if (i < 0) {
        return j + 1;
    }
    if (j < 0) {
        return i + 1;
    }
    if (cache[i][j] == -1) {
        cache[i][j] = 1 + dp(i - 1, j);
        cache[i][j] = min(cache[i][j], 1 + dp(i, j - 1));
        if (a[i] == b[j]) {
            cache[i][j] = min(dp(i - 1, j - 1), cache[i][j]);
        }
        else {
            cache[i][j] = min(cache[i][j], 1 + dp(i - 1, j - 1));
        }

    }
    return cache[i][j];
}

int main()
{

    int n, m;
    cin >> n >> a >> m >> b;
    int l1 = a.length(), l2 = b.length();
    for (int i = 0; i < l1; ++i)
    {
        vector<int> c;
        for (int j = 0; j < l2; ++j)
        {
            c.push_back(-1);
        }
        cache.push_back(c);
    }

    cout << dp(a.length() - 1, b.length() - 1) << endl;
    return 0;
}