temp = input()
print(len([i for i, x in enumerate(input()) if temp[i] != x]))