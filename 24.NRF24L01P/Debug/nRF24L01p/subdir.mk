################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../nRF24L01p/nrf24l01p.c 

OBJS += \
./nRF24L01p/nrf24l01p.o 

C_DEPS += \
./nRF24L01p/nrf24l01p.d 


# Each subdirectory must supply rules for building sources it contributes
nRF24L01p/%.o nRF24L01p/%.su nRF24L01p/%.cyclo: ../nRF24L01p/%.c nRF24L01p/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/STM32CubeIDE/workspace_1.13.1/NRF24L01P/nRF24L01p" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-nRF24L01p

clean-nRF24L01p:
	-$(RM) ./nRF24L01p/nrf24l01p.cyclo ./nRF24L01p/nrf24l01p.d ./nRF24L01p/nrf24l01p.o ./nRF24L01p/nrf24l01p.su

.PHONY: clean-nRF24L01p

