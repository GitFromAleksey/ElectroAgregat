//============================================================================
// Name        : DigitalSignalProcessing.cpp
// Author      : Борзенков
// Version     :
// Copyright   : Your copyright notice
// Description : Это модуль для тестирования Си функций обработки данных
//               Запускается скриптом start_test.py, который формирует
//               последовательность данных и записывает их в файл.
//               Затем start_test.py запускает эту исполняемую откомпилированную
//               *.exe программую и передаёт ей имена файла входных данных и
//               выходных данных, в которые программа выводит результат вычислений.
//               После этого start_test.py строит графики входных и выходных данных!
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "MovingAverage.h"
#include "RcFiltr.h"
#include "LowPassFilter.h"


using namespace std;


int main(int argc, char*argv[])
{
	t_MoveAvg moveAvg;
	t_RcFiltr rcFiltr;
	t_low_pass_filter loPasFiltr;

	std::cout << "\n  !!! C-file Start !!!" << std::endl;

	FILE *f_in;
	FILE *f_out;
	// имена файлов получаются из входных параметров
	char *data_sequence_file_name = argv[1];
	char *data_out_file_name = argv[2];
	char line[50]; // массив для чтения строк из файла

	// настройка тестируемых фильтров
	MoveAvgInit(&moveAvg, 3);
	RcFiltrInit( &rcFiltr, FILTR_T_SEC, FILTR_SPS, FILTR_FIX_POINT_POS);
	LowPassFilterInit(&loPasFiltr, 0.3, 8);

	printf("Input data sequence file name:\n %s\n", data_sequence_file_name);
	printf("Output data sequence file name:\n %s\n", data_out_file_name);

	// открываем файл с входящими данными
	if((f_in = fopen(data_sequence_file_name, "r")) == NULL)
	{
		printf("error open file %s", data_sequence_file_name);
		return -1;
	}
	// открываем файл для записи обработанных данных
	if((f_out = fopen(data_out_file_name, "w")) == NULL)
	{
		printf("error open file %s", data_out_file_name);
		return -1;
	}

	// цикл обработки и вывода данных в файл
	uint32_t data_in = 0;
	int data_out = 0;
	while(fgets(line, 50, f_in) != NULL)
	{
		// чтение входной последовательности из файла
		data_in = (uint32_t)atoi(line);
		data_out = 0;

		// обработка фильтрами входной последовательности
		MoveAvgCalc(&moveAvg, data_in);
		RcFiltrCalc(&rcFiltr, data_in);
		LowPassFilterCalc(&loPasFiltr, data_in);

		// вывод обработанных данных в файл
		data_out = (int)rcFiltr.Dout;
//		data_out = (int)moveAvg.avgValue;
//		data_out = (int)loPasFiltr.data_out;
		fprintf(f_out, "%u\n", data_out);
	}

	fclose(f_in);
	fclose(f_out);

	return 0;
}
