
// ----------------------------------------------------------------------------
unsigned int read_ADC1(unsigned char channel)
{
	unsigned int adc_res;

	adc_res = ((MDR_ADC->ADC1_RESULT) & 0x00000fff);
	MDR_ADC->ADC1_CFG &= 0xfffff40f;
	MDR_ADC->ADC1_CFG |= (channel<<4);

	return adc_res;
}
// ----------------------------------------------------------------------------
void Calculate_RMS(void)
{
	unsigned int i, iChannel;

	for(iChannel = 0; iChannel < CHANNELS_COUNT; iChannel++)
	{
		ll_acc  = 0; 

		for(i = 0; i < RMS_SUMM_COUNT; i++)
			ll_acc += RMS_16[iChannel][i];

		RESULT_VALUE[iChannel] = sqrt(ll_acc/RMS_SAMPLES/RMS_SUMM_COUNT);
	}	
	// for Power
	ll_acc  = 0; 
	for(i = 0; i < RMS_SUMM_COUNT; i++)
		ll_acc += RMS_16[CHANNELS_COUNT][i]; 

	RESULT_VALUE[CHANNELS_COUNT] = ll_acc/RMS_SAMPLES/RMS_SUMM_COUNT;
}
// ----------------------------------------------------------------------------
const unsigned int PERIOD_TIMEOUT = 512;	// 0x200
const unsigned int PERIOD_DEFAULT = 8192;	// 0x2000
unsigned long ULinePeriodCounter(signed long v)
{
	unsigned long l;

	if( (++Period_Counter_ULine < PERIOD_TIMEOUT) )
	{
		if( (Line_pause == 0) )
		{
			if( ( v < 0 && ULine_old >= 0) || (v > 0 && ULine_old <= 0) )
			{
				l = Period_ULine>>7;	// Period_ULine/128
				Period_ULine = Period_ULine - l + Period_Counter_ULine;
				Period_Counter_ULine = 0;
				ULine_old = v;
				Line_pause = 20;
			}
		}
	}
	else // timeout
	{
		Period_Counter_ULine = 0;
		Period_ULine = 0;
		ULine_old = 100;
		Period_ULine = PERIOD_DEFAULT;
	}	

	if( Line_pause )
		{ --Line_pause; }

	return Period_ULine;
}
// ----------------------------------------------------------------------------
const unsigned int DELAY_LEN = 128;	// 0x80
int Delay_ULine(int v)
{
	int ret_v = DelayULine[DelayULineIndex];

	DelayULine[DelayULineIndex] = v;

	if( ++DelayULineIndex == DELAY_LEN )
		DelayULineIndex = 0;

	return ret_v;
}
// ----------------------------------------------------------------------------
unsigned long ZERO_SHIFT[] ={2048*2048, 0, 2048*2048, 2048*2048};
const unsigned int CHANNELS_COUNT = 4;
unsigned long long AD_ACC[CHANNELS_COUNT+1]; // +1 для мощности

void Execute_ADC(void)
{
	unsigned char _adc_channel_cur  = ADC_CHANNELS[CHANNEL_INDEX];
	unsigned char _adc_channel_next = ADC_CHANNELS[CHANNEL_INDEX_NEXT];
	int v ;
	int adc_v = read_ADC1(_adc_channel_next);
	unsigned long zh = ZERO_SHIFT[CHANNEL_INDEX];

	if( _adc_channel_cur != CHANNEL_UBAT )
	{
		zh = zh - (zh >> 11) + adc_v;
		ZERO_SHIFT[CHANNEL_INDEX] = zh;
	}

	v = adc_v - (zh >> 11);

	AD_ACC[CHANNEL_INDEX] += v*v; // UL

	if( ++CHANNEL_INDEX == CHANNELS_COUNT)
		CHANNEL_INDEX = 0;
	if( ++CHANNEL_INDEX_NEXT == CHANNELS_COUNT)
		CHANNEL_INDEX_NEXT = 0;

// Отдельно для мощности
	switch( _adc_channel_cur )
	{
		case CHANNEL_ULINE:
			ULineCurrent = v;
			ULineDelayed = Delay_ULine(v);
			ULinePeriod = (ULine > 5 ) ? ULinePeriodCounter(v) : 0;	// ULine - RMS value of U line
			break;
		
		case CHANNEL_IGEN:
			v = (v >= 0)? v: 0 - v;
			IGenDelayed = Delay_IGen( v );
			break;

		case CHANNEL_UGEN:
			UGenCurrent = v;
			UGenDelayed = Delay_UGen( v );
				// freq
			UGenPeriod = ( UGen > 5 )? UGenPeriodCounter( v ) : 0;
			v = (v >= 0) ? v: (0 - v);
			v *= IGenDelayed;
			AD_ACC[ CHANNELS_COUNT ] += v; // UL
			break;
	}
	if( ++CtRms == CHANNELS_COUNT*RMS_SAMPLES )
	{
		unsigned int i;

		for(i = 0; i < (CHANNELS_COUNT + 1); i++) // +1 для мощности
		{
			RMS_16[i][RMS_HEAD] = AD_ACC[i];
			AD_ACC[i] = 0;
		}
		CtRms = 0;

		if( ++RMS_HEAD == RMS_SUMM_COUNT )
			RMS_HEAD = 0;
	}
}
// ----------------------------------------------------------------------------
void ADC_IRQHandler(void)
{	
	Execute_ADC();
}
// ----------------------------------------------------------------------------
void start_ADC1(void)
{
	MDR_ADC->ADC1_STATUS = (1<<4);
	MDR_ADC->ADC1_CFG |= 2;
}
// ----------------------------------------------------------------------------
// этот таймер для измерения
void Timer1_IRQHandler(void)  // f = 102400 Hz
{
	if(MDR_TIMER1->STATUS & 0x2) //CNT = ARR 

	start_ADC1();

	MDR_TIMER1->STATUS = 0;
}
// ----------------------------------------------------------------------------
void init_ADC1(void)
{
	// для преобразования нужно 28 тактов синхронизации
	// PORTD
	MDR_RST_CLK->PER_CLOCK |= 0x1000000;
	// 17bit - ADC PCLK_EN
	MDR_RST_CLK->PER_CLOCK |= 0x20000;
	// ADC_C1_SEL = CPU_C1 = 16 MHz/2 = 8 MHz
	// 5bit - ADC_C2_SEL = ADC_C1 = 8 MHz
	MDR_RST_CLK->ADC_MCO_CLOCK = 0x20;
	
	// 8000000/28 = 285714,3 Гц количество преобразований в секунду
	// 285714,3/4канала = 71428,6 Гц - частота преобразований одного канала
	// 28*(1/8000000) = 0,0000035 c = 3.5 мкс - на одно преобразование
	// 1/71428,6 = 0,000014 c = 14.0 мкс - на одно преобразование одного канала

	// 1/102400 = 0,0000098 с = 9.8 мкс - период таймера
	// 102400/4 = 25600 Гц - количество преобразований одного канала в секунду
	// 25600/50Гц = 512 - преобразований на период 50Гц
	// 1/(102400/4) = 0,000039 = 39 мкс - период м.у запуском преобразований

	// 13bit ADC_CLK_EN
	MDR_RST_CLK->ADC_MCO_CLOCK |= 0x2000;

	MDR_ADC->ADC1_CFG = 0;
	MDR_ADC->ADC1_CFG |= 4;	// ADC CLK
	MDR_ADC->ADC1_CFG |= 1;	// adc = on
	MDR_ADC->ADC1_STATUS = (1<<4);

	NVIC_EnableIRQ(ADC_IRQn);
}
// ----------------------------------------------------------------------------
void InitTimer1(void)
{
	MDR_RST_CLK->TIM_CLOCK = 0x7000000;	// включение частоты HCLK 64 MHz
	MDR_RST_CLK->PER_CLOCK	|= 0x4000;	// TIMER1
	MDR_TIMER1->CNTRL		= 0;
	MDR_TIMER1->CNT			= 0;		// CT
	MDR_TIMER1->ARR			= 1250/2;	// = 625 - 102400 Hz
	MDR_TIMER1->PSG			= 0x0;		// FTim2 = clk/2
	MDR_TIMER1->CNTRL		= 0x1;		// CNT_EN
	MDR_TIMER1->IE			= 0x2;		// CNT = ARR
	NVIC->ISER[0]			|= 0x4000;	// Timer1
}	
// ----------------------------------------------------------------------------










