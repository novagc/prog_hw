n = int(input())
temp = list(map(int, input().split()))
if n == 1:
	print(0)
elif n == 2:
	if temp[0] == temp[1]:
		print(1)
	else:
		print(0)
else:
	res = 0
	cur = False
	li = n - 1
	for i in range(1, n):
		if temp[i - 1] != temp[i]:
			cur = temp[i] > temp[i - 1]
			li = i
			break
		res += 1
	for i in range(i + 1, n):
		if temp[i] == temp[i - 1]:
			res += 1
		else:
			if (temp[i] > temp[i - 1]) == cur:
				res += 1
			else:
				cur = temp[i] > temp[i - 1]
	print(res)