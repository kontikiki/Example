################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/src/PIDLoop.c \
../Lib/src/Pixy2.c \
../Lib/src/Pixy2SPI.c \
../Lib/src/rcservo.c 

OBJS += \
./Lib/src/PIDLoop.o \
./Lib/src/Pixy2.o \
./Lib/src/Pixy2SPI.o \
./Lib/src/rcservo.o 

C_DEPS += \
./Lib/src/PIDLoop.d \
./Lib/src/Pixy2.d \
./Lib/src/Pixy2SPI.d \
./Lib/src/rcservo.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/src/%.o Lib/src/%.su: ../Lib/src/%.c Lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/user/STM32Cube/Example/11.PIXY2_SPI_TIM_3/STM32CubeIDE/Lib/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib-2f-src

clean-Lib-2f-src:
	-$(RM) ./Lib/src/PIDLoop.d ./Lib/src/PIDLoop.o ./Lib/src/PIDLoop.su ./Lib/src/Pixy2.d ./Lib/src/Pixy2.o ./Lib/src/Pixy2.su ./Lib/src/Pixy2SPI.d ./Lib/src/Pixy2SPI.o ./Lib/src/Pixy2SPI.su ./Lib/src/rcservo.d ./Lib/src/rcservo.o ./Lib/src/rcservo.su

.PHONY: clean-Lib-2f-src

