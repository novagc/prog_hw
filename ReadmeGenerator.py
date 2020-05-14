import urllib.parse
pat = '''# ДЗ по Основам алгоритмизации
**Группа:** Б8119-02.03.01.сцт

**Подгруппа:** 1 (Сущенко Андрей Андреевич)

**Я:** Хворостина В.В.

## Задачи

'''

url = 'https://github.com/novagc/prog_hw/tree/master/'

readme = open('README.md', 'w', encoding='utf-8')
temp = [x[:-1] if x[-1] == '\n' else x for x in open('dirs.txt', 'r', encoding='utf-8').readlines()]

readme.write(pat)

for x in temp:
	readme.write(f'[{x}]({url}{urllib.parse.quote(x)})\n')