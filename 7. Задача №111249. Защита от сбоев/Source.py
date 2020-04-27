temp = input()
print(temp[:-1] + str(sum([int(x) for x in list(temp[:-1])]) % 2 if temp[-1] == 'e' else (sum([int(x) for x in list(temp[:-1])]) + 1) % 2))