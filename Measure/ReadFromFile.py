import matplotlib as mpl
import matplotlib.pyplot as plt

FILE_NAME_IN = "tg_in_hex.txt"
FILE_NAME_OUT = "out_" + FILE_NAME_IN

f_in = open(FILE_NAME_IN, 'r')
content = f_in.read()
f_in.close()

split_content = content.split(',')

f_out = open(FILE_NAME_OUT, 'w')
tg_int = list()

for word in split_content:
    #dig = int(word.strip(),0)
    dig = word.strip()
    tg_int.append(dig)
    f_out.write(str(dig) + ',\n')

f_out.close()

print(u'Количество точек построения = ', len(tg_int))
print(u'Первое значение списка = ', tg_int[0])
print(u'Последнее значение списка = ', tg_int[len(tg_int)-1])

plt.title(u'График тангенса')
plt.xlabel(u'Ось Х')
plt.ylabel(u'Ось - int atantbl[]')
plt.grid(True)
#plt.plot(tg_int)

plt.show()



