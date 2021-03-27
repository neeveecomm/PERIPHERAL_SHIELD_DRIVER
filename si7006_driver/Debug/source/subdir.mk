################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/si7006.c 

OBJS += \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/si7006.o 

C_DEPS += \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/si7006.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/si7006_driver/board" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/si7006_driver/source" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/si7006_driver" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/si7006_driver/drivers" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/si7006_driver/CMSIS" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/si7006_driver/utilities" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/si7006_driver/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


