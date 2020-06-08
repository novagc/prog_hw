n = int(input())
mp = [list(map(bool, map(int, input().split()))) for _ in range(n)]
res = [False] * n

def Calc(i):
	res[i] = True
	for j in range(n):
		if (mp[i][j] or mp[j][i]) and not res[j]:
			Calc(j)

Calc(0)
print('NO' if False in res else 'YES')