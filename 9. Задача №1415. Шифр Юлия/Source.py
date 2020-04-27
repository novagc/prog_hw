alphabet, word, k = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ', input(), int(input())
print(''.join([alphabet[(alphabet.find(x) - k) % 26] for x in word]))