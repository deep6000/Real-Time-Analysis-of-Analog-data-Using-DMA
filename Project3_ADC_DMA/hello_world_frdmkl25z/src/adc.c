/*****************************************************************************************************************
 * adc.c
 *
 *  Created on: 11-Dec-2018
 *      Author: Madhumitha Tokalanahalli and Deepesh Sonigra
 *
 ****************************************************************************************************************/
#include "MKL25Z4.h"
#include "adc.h"
#include "fsl_debug_console.h"


void ADC_Init()
{
	/* Enable Clocks for ADC */
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;	// ADC0 clock
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;	// PortB clock
	SIM_CLKDIV1 |= SIM_CLKDIV1_OUTDIV4(2);

	/* Calibrate ADC */
	ADC_Calib();

	/*Configure ADC */

	ADC0_CFG1 = 0; 						// Reset register

	ADC0_CFG1 |= (ADC_CFG1_MODE(3)  |  	// 16 bits mode
				  ADC_CFG1_ADICLK(0)|	// Input Bus Clock divided by 2(10-12.5 MHz out of reset (FEI mode))
				  ADC_CFG1_ADIV(3))| 	// Clock divide by 8 (1.25 - 1.56 MHz)
				 ADC_CFG1_ADLSMP(1);


	ADC0_SC3 = 0; 	// Reset SC3
	ADC0_SC1A |= ADC_SC1_DIFF_MASK | ADC_SC1_AIEN(0); // Disable module// Differential inputs
	ADC0_SC3 |= ADC_SC3_ADCO_MASK;


	ADC0_SC2 |= ADC_SC2_DMAEN_MASK;   // DMA Enable
	ADC0_SC1A &= ~ADC_SC1_ADCH_MASK;

}


int ADC_Calib()
{
	ADC0_CFG1 |= (ADC_CFG1_ADICLK(1) |   //Input Clock Bus divided by 2
				  ADC_CFG1_MODE(3)   |   //16-bit Resolution Mode with 2's Compliment Output
				  ADC_CFG1_ADIV(3));  	 // Clock divide by 8 (2.5-3 Mhz)


	ADC0_SC3  |= (ADC_SC3_CAL_MASK);      //Start calibration process

	while(ADC0_SC3 & ADC_SC3_CAL_MASK);	  //Wait for Calibration Process to end

	/*If a fault has occurred during calibration, CALF would be set*/
	if(ADC0_SC3 & ADC_SC3_CALF_MASK)
		return 1;

	/* Initialize 16-bit variable in RAM */
	uint16_t Calib_Register = 0;
	/* Set Plus-Side Gain Register */
	Calib_Register += ADC0_CLPD + ADC0_CLPS + ADC0_CLP4 + ADC0_CLP3 +
			 	 	  ADC0_CLP2 + ADC0_CLP1 + ADC0_CLP0;

	Calib_Register = Calib_Register >> 1;

	Calib_Register |= 0x8000;				//Set MSB

	ADC0_PG = Calib_Register;

	/* Set Minus-Side Gain Register */
	Calib_Register += ADC0_CLMS +ADC0_CLMD + ADC0_CLM4 + ADC0_CLM3 +
				 	  ADC0_CLM2 + ADC0_CLM1 + ADC0_CLM0;

	Calib_Register = Calib_Register >> 1;

	Calib_Register |= 0x8000;				//Set MSB

	ADC0_MG = Calib_Register;

	return 0;

}

unsigned short ADC_Read(unsigned char ch)
{

	ADC0_SC1A = (ch & ADC_SC1_ADCH_MASK);      // Write to SC1A to start conversion

	while(ADC0_SC2 & ADC_SC2_ADACT_MASK); 	// Wait till conversion is completed

	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK)); // Run until the conversion is complete
	return ADC0_RA;

}
