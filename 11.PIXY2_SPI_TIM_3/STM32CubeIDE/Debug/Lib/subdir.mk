################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/PIDLoop.c \
../Lib/Pixy2.c \
../Lib/Pixy2SPI.c \
../Lib/rcservo.c 

OBJS += \
./Lib/PIDLoop.o \
./Lib/Pixy2.o \
./Lib/Pixy2SPI.o \
./Lib/rcservo.o 

C_DEPS += \
./Lib/PIDLoop.d \
./Lib/Pixy2.d \
./Lib/Pixy2SPI.d \
./Lib/rcservo.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o Lib/%.su: ../Lib/%.c Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/user/STM32Cube/Example/PIXY2_SPI_TIM_3/STM32CubeIDE/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib

clean-Lib:
	-$(RM) ./Lib/PIDLoop.d ./Lib/PIDLoop.o ./Lib/PIDLoop.su ./Lib/Pixy2.d ./Lib/Pixy2.o ./Lib/Pixy2.su ./Lib/Pixy2SPI.d ./Lib/Pixy2SPI.o ./Lib/Pixy2SPI.su ./Lib/rcservo.d ./Lib/rcservo.o ./Lib/rcservo.su

.PHONY: clean-Lib

