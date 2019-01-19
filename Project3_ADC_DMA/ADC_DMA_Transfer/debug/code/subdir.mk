################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/buffer.c \
../code/conversion.c \
../code/main.c \
../code/project2.c \
../code/uart.c 

OBJS += \
./code/buffer.o \
./code/conversion.o \
./code/main.o \
./code/project2.o \
./code/uart.o 

C_DEPS += \
./code/buffer.d \
./code/conversion.d \
./code/main.d \
./code/project2.d \
./code/uart.d 


# Each subdirectory must supply rules for building sources it contributes
code/%.o: ../code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -DDEBUG -DCPU_MKL25Z128VLK4 -DFRDM_KL25Z -DFREEDOM -I../../../../../../platform/osa/inc -I../../../../../../platform/utilities/inc -I../../../../../../platform/CMSIS/Include -I../../../../../../platform/devices -I../../../../../../platform/devices/MKL25Z4/include -I../../../../../../platform/devices/MKL25Z4/startup -I../../../../../../platform/hal/inc -I../../../../../../platform/drivers/inc -I../../../../../../platform/system/inc -I../../../.. -I"H:\KDS studio\examples\frdmkl25z\demo_apps\hello_world_1\kds\header" -I"H:\KDS studio\examples\frdmkl25z\demo_apps\hello_world_1\kds\code" -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


