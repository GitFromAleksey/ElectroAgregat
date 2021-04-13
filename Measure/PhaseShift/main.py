# -*- coding: UTF-8 -*-
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np

import GetDataFromFile as getData
import GetData as gd
import Delay_Uline as dul
import atangens2 as atan

MESURE_PER_PERIOD = 512
AMPLITUDE = 4095 #12 bit
TIME = 0.040 # second

def main():
    print('Run: ',__name__, '.main')

    np_x = gd.GenerateX(50, TIME)
    np_x_degree = gd.RadianToDegree(np_x)
    np_y = gd.GetSinus(np_x, AMPLITUDE, 0, 0, 0)
    np_y_delay = dul.Delay_Uline(np_y)
    np_atan = atan.atangens2(np_y, np_y_delay)

    np_x_51 = gd.GenerateX(55, TIME)
    np_x_51_degree = gd.RadianToDegree(np_x_51)
    np_y_51 = gd.GetSinus(np_x_51, AMPLITUDE, 0, 0, 0)
    np_y_51_delay = dul.Delay_Uline(np_y_51)
    np_51_atan = atan.atangens2(np_y, np_y_51_delay)


    plt.plot(np_x_degree, np_y/np.amax(np_y))
    plt.plot(np_x_degree, np_y_delay/np.amax(np_y_delay))
    plt.plot(np_x_degree, np_atan/(np.amax(np_atan)))

    #plt.plot(np_x_degree, np_y_51/np.amax(np_y_51))


    PhaseShift = np_atan - np_51_atan
    print( 'np.amin(PhaseShift):', np.amin(PhaseShift) )
    print( 'np.amax(PhaseShift):', np.amax(PhaseShift) )
    #plt.plot( np_x_degree, PhaseShift/np.amin(PhaseShift) )

    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    main()
