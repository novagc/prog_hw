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

vector < vector <int>> g;
vector <int> used;
map <int, int> par;

int dfs(int v) {
    if (used[v]) 
        return 0;

    used[v] = 1;

    for (int u : g[v]) {
        if (par[u + 1] == 0 || dfs(par[u + 1] - 1)) {
            par[u + 1] = v + 1;
            return 1;
        }
    }

    return 0;
}

int main() {
    int n, s;
    cin >> n >> s;
    g.resize(n + s);
    for (int i = 0; i < s; i++) {
        for (int j = 0, now; j < n; j++) {
            cin >> now;

            if (now == 1) {
                g[i].push_back(s + j);
                g[s + j].push_back(i);
            }
        }
    }
    for (int i = 0; i < n + s; i++) {
        used.clear();
        used.resize(n + s, 0);

        dfs(i);
    }

    int k = 0;

    for (auto _ : par) {
        k += 1;
    }

    cout << k / 2;
}