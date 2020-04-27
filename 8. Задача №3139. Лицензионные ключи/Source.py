alphabet = {'0' : 0, '1' : 1, '2' : 2, '3' : 3, '4' : 4, '5' : 5, '6' : 6, '7' : 7, '8' : 8, '9' : 9, 'A' : 10, 'B' : 11, 'C' : 12, 'D' : 13, 'E' : 14, 'F' : 15, 'G' : 16, 'H' : 17, 'I' : 18, 'J' : 19, 'K' : 20, 'L' : 21, 'M' : 22, 'N' : 23, 'O' : 24, 'P' : 25, 'Q' : 26, 'R' : 27, 'S' : 28, 'T' : 29, 'U' : 30, 'V' : 31, 'W' : 32, 'X' : 33, 'Y' : 34, 'Z' : 35}
n, p = map(int, input().split())
temp = [True] * p
stack = []
for i in range(n):
    stack.append([alphabet[x] for x in input() if x != '-'])
    temp[sum(stack[-1]) % p] = False
contSum = -1
for i, x in enumerate(temp):
    if x:
        contSum = i
        break
if contSum == -1 or contSum > 875:
    print('Impossible')
else:
    result = [0] * 25
    for i in range(contSum // 35):
        result[i] = 'Z'
    if contSum != 875:
        result[contSum // 35] = [x for x in alphabet.keys() if alphabet[x] == contSum % 35][0]
    for i in range(5):
        for j in range(5):
            print(result[i * 5 + j], end='')
        if i != 4:
            print(end='-')