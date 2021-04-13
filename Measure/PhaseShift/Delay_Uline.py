# -*- coding: UTF-8 -*-
import numpy as np


def Delay_Uline(np_v):
    print('Run: ',__name__, '.Delay_Uline')
    cnt = 0
    size = np_v.size
    while cnt < size:
        if cnt < 128:
            np_v = np.append(np_v, np_v[1])
            np_v = np.delete(np_v, 1)
        cnt = cnt + 1

    return np_v
