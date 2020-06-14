import os
import fnmatch as fm

temp = [x[:-1] if x[-1] == '\n' else x for x in open('dirs.txt', 'r', encoding='utf-8').readlines()]

for dir in temp:
	if dir[0] == '!':
		if not os.path.exists(f'./{dir[1:]}'):
			os.mkdir(f'./{dir[1:]}')
		continue

	if not os.path.exists(f'./{dir}'):
		os.mkdir(f'./{dir}')
	
	if len([x for x in os.listdir(f'./{dir}') if fm.fnmatch(x, 'Source.*')]) == 0:
		open(f'./{dir}/Source.cpp', 'w', encoding='utf-8').close()