import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

def GetDataFromFile(fileName):
    print(u'Чтение из файла: ', fileName)
    f_in = open(fileName, 'r')
    file_content = f_in.read().replace('\n','')
    f_in.close()

    split_content = file_content.split(',')

    data = list()
    for line in split_content:
        if len(line) > 0:
            data.append(int(line))
    print(u'Размер считанного массива: ', len(data))
    
    return np.array(data)
