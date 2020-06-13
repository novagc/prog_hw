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

void calc(int** mp, string* v, int n, int& r1, int& r2) {
	r1 = 0;
	r2 = 0;

	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (mp[i][j] != 0) {
				if (v[i] == v[j]) {
					r1++;
				}
				else {
					r2++;
				}
			}
		}
	}
}

int main()
{
	int** mp;
	string* v;
	
	int r1 = 0;
	int r2 = 0;

	int n;

	cin >> n;

	v = new string[n];
	mp = new int* [n];

	for (int i = 0; i < n; i++) {
		mp[i] = new int[n];

		for (int j = 0; j < n; j++) {
			cin >> mp[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	calc(mp, v, n, r1, r2);

	cout << r1 << ' ' << r2;
}
