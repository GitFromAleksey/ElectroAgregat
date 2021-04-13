import os
import numpy as np
import matplotlib.pyplot as plt

SelfFileName = os.path.basename(__file__)


# f0 - частота сигнала, Гц
# A - амплитуда сигнала
# ts - время дискретизации, сек
# time - время генерации сигнала
# ShiftZero - сдвиг относительно оси "х" о.е. амплитуды
# ShiftPhaseDegree - сдвиг фазы в градусах
def GetSinus(f0, A, ts, time, ShiftZero, ShiftPhaseDegree):
    print()
    print(SelfFileName,'-> Sinus generate begin:')
    
    T = 1/f0 # период, сек
    fs = 1/ts # частота дискретизации, Гц
    n = time/ts # кол-во отсчетов
    #ts = T/n # промежуток времени кантования, сек/отсчёт
    ShiftPhaseRadian = (ShiftPhaseDegree/180)*np.pi # сдвиг фазы в радианах(для рассчёта)
    n_array = np.arange(0, n, 1) # n отсчётов с шагом 1 (массив)
    
    print('f0 = ', f0, ',Гц - частота сигнала')
    print('ts = ', ts, ',сек - период дискретизации')
    print('fs = ', fs, ',Гц - частота дискретизации')
    print('A = ', A, ', амплитуда сигнала')
    print('ShiftPhaseDegree = ', ShiftPhaseDegree, ', градусы')
    print('ShiftPhaseRadian = ', ShiftPhaseRadian, ', радианы')
    
    print('T = ', T, ',сек - период сигнала')
    print('n = ', n, ', кол-во отсчётов')
    
    
    _tn = n_array * ts
    _x = 2 * np.pi * f0 * _tn
    _y = A * np.sin(_x + ShiftPhaseRadian) + ShiftZero

    print(SelfFileName,'<- Sinus generate end.\n')
          
    return _tn, _y


# подмешивание шума
def GenerateNoize(np_signal, noize_amplitude):
    print(SelfFileName,'.GenerateNoize -> noize_amplitude:',noize_amplitude)
    if noize_amplitude == 0:
        return np_signal
    array_size = len(np_signal)
#     noize_amplitude = np.amax(np_signal)
    rnd = np.random.randint( 0, noize_amplitude, size = array_size)
    data_array = np_signal + rnd
    return data_array
