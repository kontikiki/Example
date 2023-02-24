################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Pixy2/Pixy2.c \
../Pixy2/Pixy2SPI.c 

OBJS += \
./Pixy2/Pixy2.o \
./Pixy2/Pixy2SPI.o 

C_DEPS += \
./Pixy2/Pixy2.d \
./Pixy2/Pixy2SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Pixy2/%.o Pixy2/%.su: ../Pixy2/%.c Pixy2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/user/STM32Cube/Example/SPI_PIXY2/STM32CubeIDE/Pixy2" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Pixy2

clean-Pixy2:
	-$(RM) ./Pixy2/Pixy2.d ./Pixy2/Pixy2.o ./Pixy2/Pixy2.su ./Pixy2/Pixy2SPI.d ./Pixy2/Pixy2SPI.o ./Pixy2/Pixy2SPI.su

.PHONY: clean-Pixy2

