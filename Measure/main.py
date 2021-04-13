# -*- coding: UTF-8 -*-
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import math

import sys
import getopt

import ULinePeriodCounter
import GetData
import ZeroShift
import rms
import RcFiltr

AMPLITUDE_ADC = 4095 # 12 bit
AMPLITUDE_FREQ = 500 # номинальная частота колебаний
MESURES_PER_PERIOD = 512 # количество измерений за период 50Гц
PERIODS = 300 # количество колебаний которое нужно сгенерировать
#step = np.pi/mesurePerPeriod


def CreatePlot():
    plt.title(u'График sin(x)')
    plt.xlabel(u'Лось X')
    plt.ylabel(u'Лось Y')
    plt.grid(True)
    return plt

def GraphicPlot(plot, x, y, scale):
    plot.plot(x,y/scale)

def graphicPlot(x, y):
    plt.title(u'График фильтрации КДГ')
    plt.xlabel(u'Лось X')
    plt.ylabel(u'Лось Y')
    plt.grid()
    plt.plot(x,y)
    plt.show()

def main():
    x = GetData.generate_X_sequence(PERIODS, MESURES_PER_PERIOD)
    y = GetData.account_Y_sequence(x, AMPLITUDE_ADC)
    
    plot = CreatePlot()
    GraphicPlot(plot, x, y, AMPLITUDE_ADC)

    zh = ZeroShift.ZeroShift(y)
    GraphicPlot(plot, x, zh, AMPLITUDE_ADC)

    zh_filtr = RcFiltr.filtr(zh)
    GraphicPlot(plot, x, zh_filtr, AMPLITUDE_ADC)

    freq = ULinePeriodCounter.ULinePeriodCounter(zh_filtr)
    GraphicPlot(plot, x, freq, AMPLITUDE_FREQ)
    print('freq Max = ', np.amax(freq))

    RMS_zh = rms.Calculate_RMS(zh)
    GraphicPlot(plot, x, RMS_zh, AMPLITUDE_ADC)

    RMS_filtr = rms.Calculate_RMS(zh_filtr)
    GraphicPlot(plot, x, RMS_filtr, AMPLITUDE_ADC)

    plot.show()

if __name__ == "__main__":
    main()
