# -*- coding: UTF-8 -*-
import numpy as np

NOIZE_AMPLITUDE = 0
#step = np.pi/mesurePerPeriod
MEGER_PER_PERIOD = 512 # измерений за 20 мс
Fseti = 50 # Гц
MEGERS_PER_SECOND = MEGER_PER_PERIOD * Fseti
ts = 1/MEGERS_PER_SECOND

print('MEGERS_PER_SECOND: ', MEGERS_PER_SECOND, 'кол-во измерений в секунду')
print('ts: ', ts, ',c - время между отсчетами измерений')

# f0 - частота сигнала
# t - время генерации
def GenerateX(f0, t):
    n = int(t/ts)
    print('n =',n)
    np_x = np.linspace(0, 2*np.pi*f0*(n-1)*ts, n)
    return np_x


def RadianToDegree(np_rad):
    np_deg = 180 * np_rad/np.pi
    return np_deg


def GetSinus(_np_x, signal_amplitude, faze_shift_deg, noise_level, zero_shift):

    faze_shift_rad = np.pi * faze_shift_deg/180
    rnd = np.random.normal(size=_np_x.size) * noise_level
    sinus = rnd + signal_amplitude * np.sin(_np_x + faze_shift_rad)

    return sinus
    

