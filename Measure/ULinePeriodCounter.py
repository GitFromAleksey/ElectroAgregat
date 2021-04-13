# -*- coding: UTF-8 -*-
import numpy as np

PERIOD_TIMEOUT = 512
PERIOD_DEFAULT = 8192
LINE_PAUSE_DEFAULT = 20

Period_Counter_ULine = 0
Period_ULine = 0
l = 0
ULine_old = 0
Line_pause = 0

def ULinePeriodCount(v):
    global Line_pause
    global Period_Counter_ULine
    global ULine_old
    global Period_ULine
    global l

    Period_Counter_ULine += 1
    if Period_Counter_ULine < PERIOD_TIMEOUT:
        if Line_pause == 0:
            if ((v < 0) and (ULine_old >= 0)) or ((v > 0) and (ULine_old <= 0)):
                l = Period_ULine/128
                Period_ULine = Period_ULine - l + Period_Counter_ULine
                Period_Counter_ULine = 0
                ULine_old = v
                Line_pause = LINE_PAUSE_DEFAULT
    else:
        Period_Counter_ULine = 0
        Period_ULine = 0
        ULine_old = 100
        Period_ULine = PERIOD_DEFAULT
    
    if Line_pause > 0:
        Line_pause = Line_pause - 1

    freq = FreqAccount(Period_ULine)
    
    return freq

def FreqAccount(period):
    result = 0
    div = 0xFA0000

    if period > (0.7*0x8000):
        result = div/period

    return result



def ULinePeriodCounter(np_v):
    ResultList = list()

    for v in np_v:
        ResultList.append(ULinePeriodCount(v))

    return np.array(ResultList)
