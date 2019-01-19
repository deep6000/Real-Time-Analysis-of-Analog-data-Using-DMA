/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////
// SDK Included Files
#include <stdio.h>
#include "board.h"
#include "fsl_lptmr_driver.h"
#include "fsl_debug_console.h"
#include "adc.h"
#include "dma.h"
#include "main.h"

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////
// Timer period: 500000uS
#define TMR_PERIOD         500000U
#if defined(TWR_KV46F150M)
#define LPTMR0_IDX LPTMR_IDX
#endif

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////


/*
 * @brief Main function
 */
int main (void)
{


    // Initialize standard SDK demo application pins
    hardware_init();
    ADC_Init();
    dma_init();

    // Print the initial banner
    PRINTF("\r\nHello World!\r\n\r\n");

    while(1)
    {
    	if(DMA_Transfer_Complete)
    	{
    		PeakLvlMet_Calc();
    		DMA_Transfer_Complete=0;
    	}
    }
}

void PeakLvlMet_Calc()
{
	int16_t peaklvlmetindex = 0;
	char _to_display[20];

	PeakLvlMet_Peak = DMA_Value[0];  //Initialize the Peak to first ADC Value

	for( int i = 0; i< ADC_READS ; i++ )
	{
		/*Calculate the Absolute Value of Peak ADC Value */
		if(DMA_Value[i] < 0)
			DMA_Value[i] = abs(DMA_Value[i]);

		if(PeakLvlMet_Peak < DMA_Value[i])
				PeakLvlMet_Peak = DMA_Value[i];

		peaklvlmetindex = (int)DMA_Value[i]/1024;
		PRINTF("\n_Linear Value at DMA_Value[%d] = %d \t dBFS Value at DMA_Value[%d] = %f \r\n",i,DMA_Value[i],i,PeakLvlMet_LookUp[peaklvlmetindex]);
	}

	if(PeakLvlMet_Peak > PeakLvlMet_PeakMax)
		PeakLvlMet_PeakMax = PeakLvlMet_Peak;
	else
		PeakLvlMet_PeakMax *= PeakLvlMet_Decay;

	peaklvlmetindex = (int)PeakLvlMet_PeakMax/1024;
	PRINTF("\n\nMaximum Peak Value (Linear) = %d \t Maximum Peak Value (dBFS) = %f\r\n\n",PeakLvlMet_PeakMax,PeakLvlMet_LookUp[peaklvlmetindex]);



}
