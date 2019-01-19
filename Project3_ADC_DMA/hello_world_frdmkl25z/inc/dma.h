
/*
 * dma.h
 *
 *  Created on: Nov 25, 2014
 *      Author: Manuel Alejandro
 */

#ifndef DMA_H_
#define DMA_H_

#include "MKL25Z4.h"

#define  ADC_READS 64
#define Buffer_Size 128
#define DMA_MUX_DISABLE 0x00
#define ADC_SOURCE 40



int16_t  DMA_Value[Buffer_Size]; // 2 times the buffer size
uint16_t *DMA_Ptr;
uint16_t index=0;





volatile uint16_t DMA_Transfer_Complete = 0;



void dma_init(void);
void DMA0_IRQHandler(void);

#endif /* DMA_H_ */
