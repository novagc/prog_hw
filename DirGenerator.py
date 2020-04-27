import os
[os.mkdir(x) for x in ['./' + y for y in [x[:-1] if x[-1] == '\n' else x for x in open('dirs.txt', 'r',encoding='utf-8').readlines()]] if not os.path.exists(x)]
[open(z, 'w', encoding='utf-8').close() for z in ['./' + y + './Source.cpp' for y in [x[:-1] if x[-1] == '\n' else x for x in open('dirs.txt', 'r',encoding='utf-8').readlines()]] if not os.path.exists(z)]