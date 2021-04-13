import numpy as np

T = 0.0005 # постоянная времени
SPS = 25600 # частота дискретизации
K = T*SPS

Dacc = 0
Duot = 0

def filtr(np_y):
    global K
    global Dacc
    global Duot

    result = list()
    Dout = 0
    
    for Din in np_y:
        Dacc = Dacc + Din - Dout
        Dout = Dacc/K
        result.append(Dout)

    return np.array(result)
