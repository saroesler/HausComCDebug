################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ConfFile.c \
../HausComC.c \
../Receive.c \
../Transmit.c 

OBJS += \
./ConfFile.o \
./HausComC.o \
./Receive.o \
./Transmit.o 

C_DEPS += \
./ConfFile.d \
./HausComC.d \
./Receive.d \
./Transmit.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


