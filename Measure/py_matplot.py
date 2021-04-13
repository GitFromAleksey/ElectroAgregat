# -*- coding: UTF-8 -*-
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import math

f = open('log.txt')
_str = f.read()
print('from file:\n',_str)

plt.title(u'График')
plt.xlabel(u'лось х')
plt.ylabel(u'лось у')
plt.grid()

#x = np.arange(0,2*np.pi,0.00001)
#x = np.fromfile('log.txt',int)
x = np.array([str(i) for i in _str])
print('from numpy:\n',x)
#y = np.sin(x)
#print(x)#print(x,y)

#plt.plot(x)#plt.plot(x,y)
#plt.plot([1,1.2,2,6,7,2,3,4])

plt.show()
