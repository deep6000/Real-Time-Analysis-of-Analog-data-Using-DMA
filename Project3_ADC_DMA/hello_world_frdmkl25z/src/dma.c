/*
 * dma.c
 *
 */
#include "dma.h"
#include "fsl_debug_console.h"





void dma_init(void)
{


	DMA_Ptr = &DMA_Value[index];
	// Enable clocks
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK; 
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	
	// Config DMA Mux for ADC operation
	// Disable DMA Mux channel first
	DMAMUX0_CHCFG0 = DMA_MUX_DISABLE;
	
	// Configure DMA
	DMA_SAR0 = (uint32_t)&ADC0_RA;
	DMA_DAR0 = (uint32_t)DMA_Ptr;
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(Buffer_Size); // 64 bytes (16 bits) per transfer
	
	DMA_DCR0 |= (DMA_DCR_EINT_MASK|		// Enable interrupt
				 DMA_DCR_ERQ_MASK |		// Enable peripheral request
				 DMA_DCR_CS_MASK  |
				 DMA_DCR_SSIZE(2) |		// Set source size to 32 bits
				 DMA_DCR_DINC_MASK|		// Set increments to destination address
				 DMA_DCR_DMOD(0)  |     // Destination address modulo disabled
				 DMA_DCR_DSIZE(2));		// Set destination size of 32 bits
	
	// Enable DMA channel and source
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(ADC_SOURCE); // Enable DMA channel and set ADC0 as source

	// Enable interrupt
	NVIC_EnableIRQ(DMA0_IRQn);

}




void DMA0_IRQHandler(void)
{


//	PRINTF("INTERRUPT DMA \r\n");
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	// Clear Done Flag
//	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;	// Clear Done Flag
	index =( index+1) % (Buffer_Size);
	DMA_Ptr = &DMA_Value[index];
	DMA_DAR0= (uint32_t)DMA_Ptr;
	DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(Buffer_Size);		// Set byte count register
	DMA_Transfer_Complete=1;

}
