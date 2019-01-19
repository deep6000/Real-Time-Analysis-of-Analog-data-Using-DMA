/*
 * main.h
 *
 *  Created on: Nov 6, 2018
 *      Author: user1
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

/* Macro for Peak-Level Metering */
#define PeakLvlMet_Decay 0.5
//#define PRINT_ADC_COUNT

/* Global Variables for Peak-Level Metering */
int16_t PeakLvlMet_Peak= 0;
int16_t PeakLvlMet_PeakMax = 0;

/* Look Up Table for Calculation of Logarithmic dBFS Values */
const float PeakLvlMet_LookUp[32] = 	  {  -30.10, -24.08, -20.56, -18.06,
											 -16.12, -14.53, -13.20, -12.04,
											 -11.01, -10.10, -09.27, -08.51,
											 -07.82, -07.18, -06.58, -06.02,
											 -05.49, -04.99, -04.52, -04.08,
											 -03.65, -03.25, -02.86, -02.49,
											 -02.14, -01.80, -01.47, -01.15,
											 -00.85, -00.56, -00.27,  00.00   };

#endif /* MAIN_H_ */
