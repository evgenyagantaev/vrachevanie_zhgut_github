/*
 * diagnost_obj.c
 *
 *  Created on: Sep 18, 2016
 *      Author: root
 */

#include "diagnost_obj.h"
#include "recreation_curve_obj.h"
#include "timer_1hz_obj.h"

//debug
//#include "usart.h"
//extern UART_HandleTypeDef huart1;

void diagnost_init()
{
	status = 0;
	DIAGNOSTICSINTERVAL = 2;
	tachiThreshold = TACHYTHRESHOLD;

	greencounter = yellowCounter = redCounter = blackCounter = 0;
	state = previousState = 0;

	lastDisplayedPulse = 444;

	walkingRunningStopMarker = 0;

	startPulse = 0;

}//end diagnost_init


//************************ properties ***************************************

   int getStatus()
   {return status;}

   long getInterval()
   {return DIAGNOSTICSINTERVAL;}

   void setInterval(long interval)
   {DIAGNOSTICSINTERVAL = interval;}

   void setLastDisplayedPulse(int pulse)
   {
      lastDisplayedPulse = pulse;
   }

   int getLastDisplayedPulse()
   {return lastDisplayedPulse;}

   int getTachiThreshold()
   {return tachiThreshold;}


   //********************** end properties *************************************



//---------------------------------------------------------------------------
// Method performs diagnostics
void makeDiagnosis(int pulse, int walkingDetected, int runningDetected,
				 int position)
{

	if(walkingDetected || runningDetected || (position == 8))
	{
		walkingRunningStopMarker = timer1hz_get_tick();
		if(lastDisplayedPulse != 444)
			tachiThreshold = lastDisplayedPulse + startPulseAdd;
	}
	else // no walking, no running
	{
		uint32_t noLocomotionPeriod = timer1hz_get_tick() - walkingRunningStopMarker;

	   // during start pulse set period, set start pulse
	   if(noLocomotionPeriod < timeToGetStartPulse)
	   {
		  tachiThreshold = lastDisplayedPulse + startPulseAdd;
		  recreation_set_start_pule(lastDisplayedPulse + startPulseAdd);
		  recreation_set_start_time(timer1hz_get_tick());
	   }
	   else
		   tachiThreshold = recreation_get_current_level();
	}// end if(walkingDetected || runningDetected || (position == 8))

	if(tachiThreshold < TACHYTHRESHOLD)
		tachiThreshold = TACHYTHRESHOLD;

	// debug
	/*
	char message[64];  // remove when not debugging
	sprintf(message, "%dI%d\r\n", tachiThreshold, tachiThreshold);
	HAL_UART_Transmit(&huart1, (uint8_t *)message, strlen(message), 500);  // for production board
	//*/


	/*
	if(walkingDetected || runningDetected || (position == 8))
	{
		status = 1;
	}
	else
	//*/


	if(pulse == 0) // asistoly
	{
		//printf ("OPERATOR_CONDITION %d\r\n", 3);	// hard wounded
		status = 4;
	}
	else if(pulse < HARDBRADYTHRESHOLD) // hard bradycardia
	{
		//printf ("OPERATOR_CONDITION %d\r\n", 3);	// hard wounded
		status = 3;
	}
	else if(pulse < BRADYTHRESHOLD) // light bradycardia
	{
		//printf ("OPERATOR_CONDITION %d\r\n", 2);	// light wounded
		status = 2;
	}
	else if(pulse < 300)
	{
		if(pulse > tachiThreshold) // tachycardia
		{
		   if(pulse > HARDTACHYTHRESHOLD) // hard tachycardia
		   {
				 //printf ("OPERATOR_CONDITION %d\r\n", 3);	// hard wounded
				 status = 3;
		   }
		   else     // light tachycardia
		   {
				 //printf ("OPERATOR_CONDITION %d\r\n", 2);	// light wounded
				 status = 2;
		   }
		}
		else
		{
				//printf ("OPERATOR_CONDITION %d\r\n", 1);	// �����������
				status = 1;
		}
	}
	else // pulse >= 300
	status = 0;

	if(status == 4)
	{
		blackCounter++;
		redCounter = 0;
		yellowCounter = 0;
		greencounter = 0;
	}
	else if(status == 3)
	{
		blackCounter = 0;
		redCounter++;
		yellowCounter = 0;
		greencounter = 0;

	}
	else if(status == 2)
	{
		blackCounter = 0;
		redCounter = 0;
		yellowCounter++;
		greencounter = 0;
	}
	else
	{
		blackCounter = 0;
		redCounter = 0;
		yellowCounter = 0;
		greencounter++;
	}


	// ������ ���� ������� ������ ���� ��������� ����������� �������� ���������� ���
	if(yellowCounter >= numberOfRepeatingStatesToSwitch)	// ����� ���������
	{
		 yellowCounter = numberOfRepeatingStatesToSwitch;
		 state = 2;
	}
	else if(redCounter >= numberOfRepeatingStatesToSwitch)	// ����� ����������
	{
		 redCounter = numberOfRepeatingStatesToSwitch;
		 state = 3;
	}
	else if(blackCounter >= numberOfRepeatingStatesToSwitch)	// ����� ���������
	{
		blackCounter = numberOfRepeatingStatesToSwitch;
		state = 4;
	}
	else if(greencounter >= numberOfRepeatingStatesToSwitch)
	{
		greencounter = numberOfRepeatingStatesToSwitch;
		 state = 1;
	}
	else
		 state = previousState;

	previousState = state;
	status = state;


}

//--------------------------end----------------------------------------------


