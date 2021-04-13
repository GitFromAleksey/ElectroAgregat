# -*- coding: UTF-8 -*-
import numpy as np

#ZERO_SHIFT = 2048/2
NOIZE_AMPLITUDE = 200
mesurePerPeriod = 512
step = np.pi/mesurePerPeriod


def generate_X_sequence(periods, mesuresPerPeriod):
    return np.linspace(0, 2*periods*np.pi, mesuresPerPeriod*periods)

def account_Y_sequence(x_sequence, amplitude_adc):
    ZERO_SHIFT = amplitude_adc/2
    amplitude = ZERO_SHIFT

    rnd = np.random.normal(size=x_sequence.size) * NOIZE_AMPLITUDE
    sinus = ZERO_SHIFT + np.sin(x_sequence) * amplitude
    result = rnd + sinus

    print('rnd.amax',np.amax(rnd)/amplitude_adc)
    
    return result

