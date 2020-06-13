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

void BFS(int** mp, bool* v, int n, int cur) {
	stack<int> s;
	s.push(cur);
	
	for (int i; !s.empty();) {
		i = s.top();
		s.pop();
		v[i] = false;
		
		for (int j = 0; j < n; j++) {
			if (mp[i][j] != 0 && v[j]) {
				s.push(j);
			}
		}
	}
}

int main()
{
	int** mp;
	bool* v;

	int res = 0;

	int n;
	int s;

	cin >> n;
	cin >> s;

	v = new bool[n];
	mp = new int* [n];

	for (int i = 0; i < n; i++) {
		mp[i] = new int[n];
		v[i] = true;

		for (int j = 0; j < n; j++) {
			cin >> mp[i][j];
		}
	}

	BFS(mp, v, n, s - 1);
	
	for (int i = 0; i < n; i++) {
		if (!v[i])
			res++;
	}

	cout << res;
}