# Real-Time-Analysis-of-Analog-data
Prevented data corruption by implementing a Direct Memory Access for real-time analog to digital data.
Automatic testing and verification of the functionalities using C-Unit Unit testing platform.

In this project we set up a channel of the KL25Z onboard analog-to-digital converter (ADC) for continuous sampling
of an input signal. 
Sampled data will be moved from the ADC to memory using the direct memory access (DMA) controller.
We will be receiving continuous data from the onboard ADC into double-buffered memory. 
An interrupt triggers data processing by the application and results of the analysis are outputted to the UART.
