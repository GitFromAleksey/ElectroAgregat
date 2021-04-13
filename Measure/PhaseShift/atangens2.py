# -*- coding: UTF-8 -*-
import numpy as np
import GetDataFromFile as getData

TANGENS_ARRAY = getData.GetDataFromFile("tg_int.txt")


def search_in_table(v):
    global TANGENS_ARRAY

    res = 0
    tan_inx = 0

    while (tan_inx < TANGENS_ARRAY.size) and (v > TANGENS_ARRAY[tan_inx]):
        tan_inx = tan_inx + 1
    res = tan_inx

    #print('tan_inx: ', tan_inx)
    return res


def atangens2(np_sin, np_cos):
    print('Run: ',__name__, '.atangens2')

    cnt = 0
    size = np_sin.size
    
    res = list()
    atan = list()

    sin = 0
    cos = 0
    sin_abs = 0
    cos_abs = 0
    cos_min_val = 0.0000001
    
    while cnt < size:
        if (np_cos[cnt] > cos_min_val) or (np_cos[cnt] < -cos_min_val):
            res_tmp = 0
            sin = np_sin[cnt]
            cos = np_cos[cnt]
            sin_abs = abs(sin)
            cos_abs = abs(cos)

            if sin_abs < cos_abs:
                res_tmp = search_in_table(sin_abs*32768/cos_abs)
            else:
                #res_tmp = 2048 - search_in_table(cos_abs*32768/sin_abs)
                res_tmp = 0x1000 - search_in_table(cos_abs*32768/sin_abs)

            if cos >= 0:
                if sin >= 0:
                    pass
                else:
                     res_tmp = 0x4000 - res_tmp#res_tmp = 16384 - res_tmp
            else:
                if sin >= 0:
                    res_tmp = 8192 - res_tmp #res_tmp = 0x2000 - res_tmp
                else:
                    res_tmp = 8192 + res_tmp

            res.append((90 * res_tmp)/4096)
        else:
            if cnt > 0:
                res.append(res[cnt-1])
            else:
                res.append(0)
            
        cnt = cnt + 1

    return np.array(res)
    
