import os
import sys
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import SignalGenerate as sg
from test.test_argparse import Sig

print('Starting python test')


def main(argv):
    # получение пути к этому файлу
    dir = os.path.dirname(os.path.dirname(__file__))
    # путь к скомпилированному си файлу
    execute_file_dir = os.path.join(dir,'Debug\DSPbyPythonTesting.exe')
    # путь к файлу сгенерированной входной последовательности данных
    data_sequence_file_name = 'data.txt'
    data_file_dir = os.path.join(dir,'Debug\\' + data_sequence_file_name)
    
    data_out_file_name = 'data_out.txt' # файл с обработанными данными
    data_out_file_dir = os.path.join(dir,'Debug\\' + data_out_file_name)
     
#     print('execute_file_dir:\n', execute_file_dir)
#     print('data_file_dir:\n', data_file_dir)
    
    # открытие файла для записи входной последовательности данных
    f = open(data_file_dir, 'w')
    if not f:
        print('Ошибка открытия файла',data_sequence_file_name)
        f.close()
        return
    
    adc_amplitude = int(0xFFF/2) # половина амплитуды разрешения АЦП
    zero_shift = adc_amplitude # постоянная составляющая сигнала
    # генерация последовательности сигнала
    #                      (f0, A, ts, time, ShiftZero, ShiftPhaseDegree)
    t, signal = sg.GetSinus(1, adc_amplitude, .01, 2, zero_shift, 0)
    signal = sg.GenerateNoize(signal, 1000)
 
#     signal = signal.round(3)
    signal_int = signal.astype(int)
    
    for data in signal.astype(int):
        f.write(str(data) + '\n')
#         print(str(data))
    
    f.close()
    # вызов исполняемой программы на си
    subprocess.call([execute_file_dir,data_file_dir,data_out_file_dir])

## ----------------------------------------------------------------------------
    # открытие файла для чтения обработанных данных
    f = open(data_out_file_dir, 'r')
    if not f:
        print('Ошибка открытия файла',data_out_file_dir)
        f.close()
        return
    
    content = f.readlines()
    content = [x.strip() for x in content]
    int_content = [int(x) for x in content]
    
    processed_data = np.array(int_content)
#     print(processed_data)
    
    f.close()
    

    # постройка графиков из файла от исполняемой программы
    fig, ax = plt.subplots()
    
    ax.set_title("Графики входного и фильтрованного сигнала", fontsize=10)
    # название горизонтальной оси
    ax.set_xlabel("Time", fontsize=10)
    # название вертикальной оси
    ax.set_ylabel("Signal value", fontsize=10)
    
    # мелкая сектка
    ax.grid(which="major", linestyle="-", linewidth=1.2)
#     ax.grid(which="minor", linestyle="--", color="gray", linewidth=0.5)
    
    # штрихи на осях
    ax.tick_params(which='major', length=3, width=2)
    
    ax.plot(signal_int, label="Input data")
    ax.plot(processed_data, label="Filtred data")
    
    ax.legend()
    
    plt.show()


if __name__ == '__main__':
    sys.exit(main(sys.argv))
