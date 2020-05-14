import os
import fnmatch as fm 

temp = [x[:-1] if x[-1] == '\n' else x for x in open('dirs.txt', 'r', encoding='utf-8').readlines()]

for dir in [x for x in temp if os.path.exists(f'./{x}')]:
	files = [x for x in os.listdir(f'./{dir}') if fm.fnmatch(x, 'snap_screen*')]
	if len(files) == 1:
		os.rename(f'./{dir}/{files[0]}', f'./{dir}/res.png')
	else:
		for file, index in enumerate(files):
			os.rename(f'./{dir}/{file}', f'./{dir}/{index + 1}.png')