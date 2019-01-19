/**********************************************************************************************************************
 * adc.h
 *
 *  Created on: 11-Dec-2018
 *      Author: Madhumitha Tolakanahalli Pradeep and Deepesh Sonigra
 *********************************************************************************************************************/


#ifndef INC_ADC_H_
#define INC_ADC_H_


/*
 * @brief Initialize ADC
 *
 *  Initialize ADC to operate in Channel 0
 *  Differential Mode and 16-bit Resolution
 *
 */
void ADC_Init();

/*
 * @brief Calibrate ADC
 *
 *  Calibrate ADC to operate in Channel 0
 *  Differential Mode and 16-bit Resolution
 *  Set up Positive and Negative Side Gains
 *
 * @return Status condition of the function call
 *
 */
int ADC_Calib();
/*
 * @brief Read ADC
 *
 *
 * @param ch : Number of the channel from which reading is to be performed
 *
 * @return : Result of conversion performed by the ADC
 *
 */
unsigned short ADC_Read(unsigned char ch);

#endif /* INC_ADC_H_ */
