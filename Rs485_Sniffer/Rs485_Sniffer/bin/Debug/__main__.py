import os
import sys
import json
import matplotlib as mpl
import matplotlib.pyplot as plt
import numpy as np
import argparse

##LOG_FILE_NAME = 'log_8_9.7.2020.json'

def GetAllNambersOfBlocks(file_name):
    _file = open(file_name,'r')
    numbersList = list()
    for line in _file:
        line_json = json.loads(line)

        isFind = False
        for item in numbersList:
            if line_json['NumberBlock'] == item:
                isFind = True
                break
        if isFind == False:
            numbersList.append(line_json['NumberBlock'])


    _file.close()
    return numbersList
##        break
        

def GetParamsList(file_name, block_number):
    _file = open(file_name,'r')
    params_list = list()
    for line in _file:
        line_json = json.loads(line)
        if line_json['NumberBlock'] == block_number:
            for param in line_json:
                params_list.append(param)
            _file.close()
            return params_list

def GetParamValues(file_name, param, block_number):
    _file = open(file_name,'r')
    values_list = list()
    for line in _file:
        line_json = json.loads(line)
        if line_json['NumberBlock'] == block_number:
##            values_list.append(int(line_json[param]))
            values_list.append(int(line_json[param]))
    return values_list

def Plot(np_data, title):
    fig, ax = plt.subplots()
    ax.set_title(title)
    ax.grid(which="major", linewidth=1.2)
    ax.grid(which="minor", linestyle="--", color="gray", linewidth=0.5)
    ax.hlines(np.amax(np_data), 0, (len(np_data)-1), color='r', linestyle = '--')
    ax.text( 0, np.amax(np_data), 'max:'+str(np.amax(np_data)) )
    ax.hlines(np.mean(np_data), 0, (len(np_data)-1), color='b', linestyle = '--')
    ax.text( 0, np.mean(np_data), 'mean:'+str(int(np.mean(np_data))) )
    plt.ylim( 0, np.amax(np_data) + np.amax(np_data)/10)
    plt.gcf().canvas.set_window_title(title)
    ax.plot( np_data)

def main(argv):
    file_name = ''
    BlockNumber = -1
    ParamsList = []
    if len(argv) > 1:
        file_name = argv[1]
        if len(argv) > 2:
            BlockNumber = argv[2]
    else:
        file_name = str(input('Enter a Log File Name(json):'))

    BlockNumbersList = GetAllNambersOfBlocks(file_name)
    print(BlockNumbersList)
    if BlockNumber == -1:
        BlockNumber = str(input('Enter a BlockNamber:'))
    print('Entered BlockNumber - ', BlockNumber)

    if len(argv) > 2:
        ParamsList = GetParamsList(file_name, BlockNumber)
        skip_param_list = ['RegS_','RegimParal','StatusSet','ErrorSum','StatizmVozbPud','NumberRegim','RegimWork_LO','RegS_LO','RegS_CAN','StatusGen','RegimWork','NumberBlock','RegS','DeviceName','DateTime','RegimWork','55','ErrorWork_LO','StatusPud','ErrorWork_HI']
        for param in ParamsList:
            print(param)
            skip_flag = False
            for skip in skip_param_list:
                if skip == param:
                    skip_flag = True
                    break
            if skip_flag == True:
                continue
            values_list = GetParamValues(file_name, param, BlockNumber)
            np_values = np.asarray(values_list)
            Plot(np_values, param)
    else:
        ParamsList = GetParamsList(file_name, BlockNumber)
        print(ParamsList)
        ParamName = str(input('Enter a Param Name:'))
        values_list = GetParamValues(file_name, ParamName, BlockNumber)
    ##    np_values = np.array([ elem for elem in values_list])
        np_values = np.asarray(values_list)
        Plot(np_values, ParamName)

    plt.show()
    return 0

if __name__ == '__main__':
    sys.exit(main(sys.argv))
