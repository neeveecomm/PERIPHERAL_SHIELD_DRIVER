################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/BH1745_DRIVER.c \
../source/mtb.c \
../source/semihost_hardfault.c 

OBJS += \
./source/BH1745_DRIVER.o \
./source/mtb.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/BH1745_DRIVER.d \
./source/mtb.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/BH1745_DRIVER/board" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/BH1745_DRIVER/source" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/BH1745_DRIVER" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/BH1745_DRIVER/drivers" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/BH1745_DRIVER/CMSIS" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/BH1745_DRIVER/utilities" -I"/Users/neevee/Documents/MCUXpressoIDE_11.1.0/workspace/BH1745_DRIVER/startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


