# -*- coding: UTF-8 -*-
import numpy as np


ZERO_SHIFT = 2048*2048
adc_v = 0
v = 0
zh = 0
AD_ACC = 0


index = 0
def read_ADC1(np_y):
    global index
    result = 0
    
    if index < np_y.size:
        result = np_y[index]
        index += 1
    
    return result

def Execute_ADC(np_y):
    global adc_v
    global v
    global zh
    global AD_ACC
    global ZERO_SHIFT

    adc_v = read_ADC1(np_y)
    zh = ZERO_SHIFT
    zh = zh - (zh/2048) + adc_v
    ZERO_SHIFT = zh

    v = adc_v - (zh/2048)

    return v
        

def ZeroShift(np_y):
    index = 0
    resultList = list()

    for _y in np_y:
        resultList.append(Execute_ADC(np_y))
        
    return np.array(resultList)
