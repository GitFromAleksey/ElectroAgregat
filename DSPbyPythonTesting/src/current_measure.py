import sys
import numpy as np
import matplotlib.pyplot as plt


print('Разбор старого алгоритма измерения тока:')


ADC_MIN = 0 # минимальное значение АЦП
ADC_MAX = 0xFFF # максимальное значение АЦП
ADC_VALUE = 100 # величина входного сигнала

AD_SAMPL = 62 # количество сэмплов измерений


NUMBER_OF_SAMPLES = AD_SAMPL * 10 # количество отсчётов входного сигнала

NOIZE_AMPLITUDE_PERCENT = 30 # амплитуда шума входного сигнала
NOIZE_AMPLITUDE = (NOIZE_AMPLITUDE_PERCENT*ADC_VALUE)/100

# генерация входной последовательности данных ацп
def GenerateInputSequence(noize_amplitude, array_size):
    rnd = np.random.randint( 0, noize_amplitude, size = array_size)
    data_array = np.zeros(NUMBER_OF_SAMPLES,'int') + ADC_VALUE + rnd
    return data_array

# старый фильтр из АД8
def AdcAverageCalcOld(np_input_sequence):
    result_list = [] # список результирующего значения
    AdTempResult_list = [] # список значений аккумулятора данных
    AdTempResult = int(0) # аккумулятор данных
    result = int(0)
    countAD = AD_SAMPL+2 # счётчик отсчётов(сэмплов)
    for data in np_input_sequence:
        AdTempResult_list.append(AdTempResult)
        result_list.append(result)
        if countAD > 0:
            countAD -= 1
            AdTempResult = AdTempResult + data
        else:
            countAD = AD_SAMPL+2
            result = AdTempResult >> 6
            AdTempResult = 0
    return np.array(result_list)

# фильтр скользящего среднего
def AdcRunningAverageCalc(np_input_sequence, div_shift):
    avg_value_list = []
    data_accum = int(0) # аккумулятор данных
    for data in np_input_sequence:
        data_accum -= data_accum >> div_shift
        data_accum += data
        avg_value_list.append(data_accum >> div_shift)

    return np.array(avg_value_list)

# цифровая имитация емкостного фильтра
def DigitRcFiltrFloat(np_input_sequence):
    FILTR_SPS = 1300 # частота входной последовательности Гц
    FILTR_T_SEC = 0.1 # емкость цифрового конденсатора
    K = FILTR_T_SEC * FILTR_SPS
    print('K =',K)
    accumulator = 0 # аккумулятор данных
    data_prev = 0
    d_out = []
    for data in np_input_sequence:
        accumulator = (accumulator + data)
        accumulator = accumulator - data_prev
        data_prev = (accumulator / K)
        d_out.append(data_prev)
        
    return np.array(d_out)

def DigitRcFiltrFixPoint(np_input_sequence):
    FILTR_SPS = 150 # частота входной последовательности Гц
    FILTR_T_SEC = 0.1 # емкость цифрового конденсатора
    DIV = 16
    K = int(1/(FILTR_T_SEC * FILTR_SPS)*(1<<DIV))
    print('K =',K)
    accumulator = int(0) # аккумулятор данных
    data_prev = int(0)
    d_out = []
    for data in np_input_sequence:
        accumulator = (accumulator + data)
        accumulator = accumulator - data_prev
        data_prev = (accumulator * K)>>DIV
        d_out.append(data_prev)
        
    return np.array(d_out)

# ФИЛЬТ НИЗКИХ ЧАСТОТ
# Подбор коэффициента фильтра
# t = (1-K) * dt / K - период времени, который отделяет слишком быстрые изменения от требуемых
# dt — время итерации
def SimpleLowPassFilter(np_input_sequence):
    pot = 0 #  обработанный фильтром сигнал
    K = 0.08 # коэффициент фильтра, который варьируется от 0,0 до 1,0
    d_out = []
    for pot_raw in np_input_sequence:
        pot = (1-K)*pot + K*pot_raw
        d_out.append(pot)

    return np.array(d_out)

# пиковый фильтр
# np_input_sequence - входящая последовательность данных
# max_peak_oe - пиковое максимальное значение изменения данных в относительных единицах
def PeakFilter(np_input_sequence, max_peak):
##    prev_data = 0
    result_list = []
    for raw_data in np_input_sequence:
        if len(result_list) > 0:
            aver = sum(result_list)/len(result_list)
            if abs(raw_data - aver) > max_peak:
                raw_data = aver

        result_list.append(int(raw_data))

    return np.array(result_list)

# перевод в относительные единицы
def ConvertToRelativeUnit(np_input_sequence):
    if np.max(np_input_sequence) > 0:
        return np_input_sequence/np.max(np_input_sequence)
    else:
        return 0
    

def main(argv):
 ##    data_array = np.arange(10) # массив от 0 до 10

    data_array = GenerateInputSequence(NOIZE_AMPLITUDE, NUMBER_OF_SAMPLES)
    peak_filtr = PeakFilter(data_array, 3)
    
    average_old = AdcAverageCalcOld(data_array)

    input_data = peak_filtr
    move_avg_result_list = AdcRunningAverageCalc(input_data, 4)
    rc_filtr = DigitRcFiltrFixPoint(input_data)
    simple_lo_pass = SimpleLowPassFilter(input_data)
    
##    X = np.fft.fft(data_array)

    fig, ax = plt.subplots()

    ax.grid(which="major", linewidth=1.2)
    ax.grid(which="minor", linestyle="--", color="gray", linewidth=0.5)

    ax.plot(ConvertToRelativeUnit(data_array), label="AdTempResult_list")
    ax.plot(ConvertToRelativeUnit(peak_filtr), label="peak_filtr")

    ax.plot(ConvertToRelativeUnit(average_old), label="result_list")
    ax.plot(ConvertToRelativeUnit(move_avg_result_list), label="move_avg_result_list")
    ax.plot(ConvertToRelativeUnit(rc_filtr), label="rc_filtr")
    ax.plot(ConvertToRelativeUnit(simple_lo_pass), label="simple_lo_pass")
    
    ax.legend()
    
    plt.show()
    
    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv))
