################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/I2C.c \
../src/IR.c \
../src/Interface.c \
../src/PWM.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/interrupt.c \
../src/matrix.c \
../src/projectWekker.c \
../src/timer.c 

OBJS += \
./src/I2C.o \
./src/IR.o \
./src/Interface.o \
./src/PWM.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/interrupt.o \
./src/matrix.o \
./src/projectWekker.o \
./src/timer.o 

C_DEPS += \
./src/I2C.d \
./src/IR.d \
./src/Interface.d \
./src/PWM.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/interrupt.d \
./src/matrix.d \
./src/projectWekker.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


