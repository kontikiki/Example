################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/ssd1306.c \
../Lib/ssd1306_fonts.c \
../Lib/ssd1306_tests.c 

OBJS += \
./Lib/ssd1306.o \
./Lib/ssd1306_fonts.o \
./Lib/ssd1306_tests.o 

C_DEPS += \
./Lib/ssd1306.d \
./Lib/ssd1306_fonts.d \
./Lib/ssd1306_tests.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o Lib/%.su: ../Lib/%.c Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/user/STM32Cube/Example/ssd1306_spi/STM32CubeIDE/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib

clean-Lib:
	-$(RM) ./Lib/ssd1306.d ./Lib/ssd1306.o ./Lib/ssd1306.su ./Lib/ssd1306_fonts.d ./Lib/ssd1306_fonts.o ./Lib/ssd1306_fonts.su ./Lib/ssd1306_tests.d ./Lib/ssd1306_tests.o ./Lib/ssd1306_tests.su

.PHONY: clean-Lib

