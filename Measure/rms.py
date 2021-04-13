# -*- coding: UTF-8 -*-
import numpy as np
import math

CHANNELS_COUNT = 1
RMS_SAMPLES = 512
RMS_SUMM = 16


def Calculate_RMS(np_zh_y):
    global RMS_SUMM

    AD_ACC = 0
    RMS_SAMPLES_COUNTER = 0
    RMS_16 = 0
    RMS_SUMM_COUNTER = 0
    RMS_RESULT = list()
    tmp = 0
    
    for y in np_zh_y:
        AD_ACC += y*y
        RMS_SAMPLES_COUNTER += 1
        if RMS_SAMPLES_COUNTER >= RMS_SAMPLES:
            RMS_SAMPLES_COUNTER = 0
            RMS_16 += AD_ACC
            AD_ACC = 0
            RMS_SUMM_COUNTER += 1
            if RMS_SUMM_COUNTER >= RMS_SUMM:
                RMS_SUMM_COUNTER = 0
                tmp = math.sqrt((RMS_16/RMS_SUMM)/RMS_SAMPLES)
                RMS_16 = 0
        RMS_RESULT.append(tmp)
    
    return np.array(RMS_RESULT)
















