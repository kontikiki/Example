################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lib/adxl345.c \
../Lib/mui.c \
../Lib/mui_u8g2.c \
../Lib/u8g2_bitmap.c \
../Lib/u8g2_box.c \
../Lib/u8g2_buffer.c \
../Lib/u8g2_button.c \
../Lib/u8g2_circle.c \
../Lib/u8g2_cleardisplay.c \
../Lib/u8g2_d_memory.c \
../Lib/u8g2_d_setup.c \
../Lib/u8g2_font.c \
../Lib/u8g2_fonts.c \
../Lib/u8g2_hvline.c \
../Lib/u8g2_input_value.c \
../Lib/u8g2_intersection.c \
../Lib/u8g2_kerning.c \
../Lib/u8g2_line.c \
../Lib/u8g2_ll_hvline.c \
../Lib/u8g2_message.c \
../Lib/u8g2_polygon.c \
../Lib/u8g2_selection_list.c \
../Lib/u8g2_setup.c \
../Lib/u8log.c \
../Lib/u8log_u8g2.c \
../Lib/u8log_u8x8.c \
../Lib/u8x8_8x8.c \
../Lib/u8x8_byte.c \
../Lib/u8x8_cad.c \
../Lib/u8x8_capture.c \
../Lib/u8x8_d_a2printer.c \
../Lib/u8x8_d_gp1247ai.c \
../Lib/u8x8_d_gp1287ai.c \
../Lib/u8x8_d_gu800.c \
../Lib/u8x8_d_hd44102.c \
../Lib/u8x8_d_il3820_296x128.c \
../Lib/u8x8_d_ist3020.c \
../Lib/u8x8_d_ist3088.c \
../Lib/u8x8_d_ist7920.c \
../Lib/u8x8_d_ks0108.c \
../Lib/u8x8_d_lc7981.c \
../Lib/u8x8_d_ld7032_60x32.c \
../Lib/u8x8_d_ls013b7dh03.c \
../Lib/u8x8_d_max7219.c \
../Lib/u8x8_d_pcd8544_84x48.c \
../Lib/u8x8_d_pcf8812.c \
../Lib/u8x8_d_pcf8814_hx1230.c \
../Lib/u8x8_d_s1d15300.c \
../Lib/u8x8_d_s1d15721.c \
../Lib/u8x8_d_s1d15e06.c \
../Lib/u8x8_d_sbn1661.c \
../Lib/u8x8_d_sed1330.c \
../Lib/u8x8_d_sh1106_64x32.c \
../Lib/u8x8_d_sh1106_72x40.c \
../Lib/u8x8_d_sh1107.c \
../Lib/u8x8_d_sh1108.c \
../Lib/u8x8_d_sh1122.c \
../Lib/u8x8_d_ssd1305.c \
../Lib/u8x8_d_ssd1306_128x32.c \
../Lib/u8x8_d_ssd1306_128x64_noname.c \
../Lib/u8x8_d_ssd1306_2040x16.c \
../Lib/u8x8_d_ssd1306_48x64.c \
../Lib/u8x8_d_ssd1306_64x32.c \
../Lib/u8x8_d_ssd1306_64x48.c \
../Lib/u8x8_d_ssd1306_72x40.c \
../Lib/u8x8_d_ssd1306_96x16.c \
../Lib/u8x8_d_ssd1306_96x40.c \
../Lib/u8x8_d_ssd1309.c \
../Lib/u8x8_d_ssd1316.c \
../Lib/u8x8_d_ssd1317.c \
../Lib/u8x8_d_ssd1318.c \
../Lib/u8x8_d_ssd1320.c \
../Lib/u8x8_d_ssd1322.c \
../Lib/u8x8_d_ssd1325.c \
../Lib/u8x8_d_ssd1326.c \
../Lib/u8x8_d_ssd1327.c \
../Lib/u8x8_d_ssd1329.c \
../Lib/u8x8_d_ssd1362.c \
../Lib/u8x8_d_ssd1606_172x72.c \
../Lib/u8x8_d_ssd1607_200x200.c \
../Lib/u8x8_d_st7511.c \
../Lib/u8x8_d_st75160.c \
../Lib/u8x8_d_st75256.c \
../Lib/u8x8_d_st7528.c \
../Lib/u8x8_d_st75320.c \
../Lib/u8x8_d_st7565.c \
../Lib/u8x8_d_st7567.c \
../Lib/u8x8_d_st7571.c \
../Lib/u8x8_d_st7586s_erc240160.c \
../Lib/u8x8_d_st7586s_jlx384160.c \
../Lib/u8x8_d_st7586s_s028hn118a.c \
../Lib/u8x8_d_st7586s_ymc240160.c \
../Lib/u8x8_d_st7588.c \
../Lib/u8x8_d_st7920.c \
../Lib/u8x8_d_stdio.c \
../Lib/u8x8_d_t6963.c \
../Lib/u8x8_d_uc1601.c \
../Lib/u8x8_d_uc1604.c \
../Lib/u8x8_d_uc1608.c \
../Lib/u8x8_d_uc1609.c \
../Lib/u8x8_d_uc1610.c \
../Lib/u8x8_d_uc1611.c \
../Lib/u8x8_d_uc1617.c \
../Lib/u8x8_d_uc1638.c \
../Lib/u8x8_d_uc1701_dogs102.c \
../Lib/u8x8_d_uc1701_mini12864.c \
../Lib/u8x8_debounce.c \
../Lib/u8x8_display.c \
../Lib/u8x8_fonts.c \
../Lib/u8x8_gpio.c \
../Lib/u8x8_input_value.c \
../Lib/u8x8_message.c \
../Lib/u8x8_selection_list.c \
../Lib/u8x8_setup.c \
../Lib/u8x8_string.c \
../Lib/u8x8_u16toa.c \
../Lib/u8x8_u8toa.c 

OBJS += \
./Lib/adxl345.o \
./Lib/mui.o \
./Lib/mui_u8g2.o \
./Lib/u8g2_bitmap.o \
./Lib/u8g2_box.o \
./Lib/u8g2_buffer.o \
./Lib/u8g2_button.o \
./Lib/u8g2_circle.o \
./Lib/u8g2_cleardisplay.o \
./Lib/u8g2_d_memory.o \
./Lib/u8g2_d_setup.o \
./Lib/u8g2_font.o \
./Lib/u8g2_fonts.o \
./Lib/u8g2_hvline.o \
./Lib/u8g2_input_value.o \
./Lib/u8g2_intersection.o \
./Lib/u8g2_kerning.o \
./Lib/u8g2_line.o \
./Lib/u8g2_ll_hvline.o \
./Lib/u8g2_message.o \
./Lib/u8g2_polygon.o \
./Lib/u8g2_selection_list.o \
./Lib/u8g2_setup.o \
./Lib/u8log.o \
./Lib/u8log_u8g2.o \
./Lib/u8log_u8x8.o \
./Lib/u8x8_8x8.o \
./Lib/u8x8_byte.o \
./Lib/u8x8_cad.o \
./Lib/u8x8_capture.o \
./Lib/u8x8_d_a2printer.o \
./Lib/u8x8_d_gp1247ai.o \
./Lib/u8x8_d_gp1287ai.o \
./Lib/u8x8_d_gu800.o \
./Lib/u8x8_d_hd44102.o \
./Lib/u8x8_d_il3820_296x128.o \
./Lib/u8x8_d_ist3020.o \
./Lib/u8x8_d_ist3088.o \
./Lib/u8x8_d_ist7920.o \
./Lib/u8x8_d_ks0108.o \
./Lib/u8x8_d_lc7981.o \
./Lib/u8x8_d_ld7032_60x32.o \
./Lib/u8x8_d_ls013b7dh03.o \
./Lib/u8x8_d_max7219.o \
./Lib/u8x8_d_pcd8544_84x48.o \
./Lib/u8x8_d_pcf8812.o \
./Lib/u8x8_d_pcf8814_hx1230.o \
./Lib/u8x8_d_s1d15300.o \
./Lib/u8x8_d_s1d15721.o \
./Lib/u8x8_d_s1d15e06.o \
./Lib/u8x8_d_sbn1661.o \
./Lib/u8x8_d_sed1330.o \
./Lib/u8x8_d_sh1106_64x32.o \
./Lib/u8x8_d_sh1106_72x40.o \
./Lib/u8x8_d_sh1107.o \
./Lib/u8x8_d_sh1108.o \
./Lib/u8x8_d_sh1122.o \
./Lib/u8x8_d_ssd1305.o \
./Lib/u8x8_d_ssd1306_128x32.o \
./Lib/u8x8_d_ssd1306_128x64_noname.o \
./Lib/u8x8_d_ssd1306_2040x16.o \
./Lib/u8x8_d_ssd1306_48x64.o \
./Lib/u8x8_d_ssd1306_64x32.o \
./Lib/u8x8_d_ssd1306_64x48.o \
./Lib/u8x8_d_ssd1306_72x40.o \
./Lib/u8x8_d_ssd1306_96x16.o \
./Lib/u8x8_d_ssd1306_96x40.o \
./Lib/u8x8_d_ssd1309.o \
./Lib/u8x8_d_ssd1316.o \
./Lib/u8x8_d_ssd1317.o \
./Lib/u8x8_d_ssd1318.o \
./Lib/u8x8_d_ssd1320.o \
./Lib/u8x8_d_ssd1322.o \
./Lib/u8x8_d_ssd1325.o \
./Lib/u8x8_d_ssd1326.o \
./Lib/u8x8_d_ssd1327.o \
./Lib/u8x8_d_ssd1329.o \
./Lib/u8x8_d_ssd1362.o \
./Lib/u8x8_d_ssd1606_172x72.o \
./Lib/u8x8_d_ssd1607_200x200.o \
./Lib/u8x8_d_st7511.o \
./Lib/u8x8_d_st75160.o \
./Lib/u8x8_d_st75256.o \
./Lib/u8x8_d_st7528.o \
./Lib/u8x8_d_st75320.o \
./Lib/u8x8_d_st7565.o \
./Lib/u8x8_d_st7567.o \
./Lib/u8x8_d_st7571.o \
./Lib/u8x8_d_st7586s_erc240160.o \
./Lib/u8x8_d_st7586s_jlx384160.o \
./Lib/u8x8_d_st7586s_s028hn118a.o \
./Lib/u8x8_d_st7586s_ymc240160.o \
./Lib/u8x8_d_st7588.o \
./Lib/u8x8_d_st7920.o \
./Lib/u8x8_d_stdio.o \
./Lib/u8x8_d_t6963.o \
./Lib/u8x8_d_uc1601.o \
./Lib/u8x8_d_uc1604.o \
./Lib/u8x8_d_uc1608.o \
./Lib/u8x8_d_uc1609.o \
./Lib/u8x8_d_uc1610.o \
./Lib/u8x8_d_uc1611.o \
./Lib/u8x8_d_uc1617.o \
./Lib/u8x8_d_uc1638.o \
./Lib/u8x8_d_uc1701_dogs102.o \
./Lib/u8x8_d_uc1701_mini12864.o \
./Lib/u8x8_debounce.o \
./Lib/u8x8_display.o \
./Lib/u8x8_fonts.o \
./Lib/u8x8_gpio.o \
./Lib/u8x8_input_value.o \
./Lib/u8x8_message.o \
./Lib/u8x8_selection_list.o \
./Lib/u8x8_setup.o \
./Lib/u8x8_string.o \
./Lib/u8x8_u16toa.o \
./Lib/u8x8_u8toa.o 

C_DEPS += \
./Lib/adxl345.d \
./Lib/mui.d \
./Lib/mui_u8g2.d \
./Lib/u8g2_bitmap.d \
./Lib/u8g2_box.d \
./Lib/u8g2_buffer.d \
./Lib/u8g2_button.d \
./Lib/u8g2_circle.d \
./Lib/u8g2_cleardisplay.d \
./Lib/u8g2_d_memory.d \
./Lib/u8g2_d_setup.d \
./Lib/u8g2_font.d \
./Lib/u8g2_fonts.d \
./Lib/u8g2_hvline.d \
./Lib/u8g2_input_value.d \
./Lib/u8g2_intersection.d \
./Lib/u8g2_kerning.d \
./Lib/u8g2_line.d \
./Lib/u8g2_ll_hvline.d \
./Lib/u8g2_message.d \
./Lib/u8g2_polygon.d \
./Lib/u8g2_selection_list.d \
./Lib/u8g2_setup.d \
./Lib/u8log.d \
./Lib/u8log_u8g2.d \
./Lib/u8log_u8x8.d \
./Lib/u8x8_8x8.d \
./Lib/u8x8_byte.d \
./Lib/u8x8_cad.d \
./Lib/u8x8_capture.d \
./Lib/u8x8_d_a2printer.d \
./Lib/u8x8_d_gp1247ai.d \
./Lib/u8x8_d_gp1287ai.d \
./Lib/u8x8_d_gu800.d \
./Lib/u8x8_d_hd44102.d \
./Lib/u8x8_d_il3820_296x128.d \
./Lib/u8x8_d_ist3020.d \
./Lib/u8x8_d_ist3088.d \
./Lib/u8x8_d_ist7920.d \
./Lib/u8x8_d_ks0108.d \
./Lib/u8x8_d_lc7981.d \
./Lib/u8x8_d_ld7032_60x32.d \
./Lib/u8x8_d_ls013b7dh03.d \
./Lib/u8x8_d_max7219.d \
./Lib/u8x8_d_pcd8544_84x48.d \
./Lib/u8x8_d_pcf8812.d \
./Lib/u8x8_d_pcf8814_hx1230.d \
./Lib/u8x8_d_s1d15300.d \
./Lib/u8x8_d_s1d15721.d \
./Lib/u8x8_d_s1d15e06.d \
./Lib/u8x8_d_sbn1661.d \
./Lib/u8x8_d_sed1330.d \
./Lib/u8x8_d_sh1106_64x32.d \
./Lib/u8x8_d_sh1106_72x40.d \
./Lib/u8x8_d_sh1107.d \
./Lib/u8x8_d_sh1108.d \
./Lib/u8x8_d_sh1122.d \
./Lib/u8x8_d_ssd1305.d \
./Lib/u8x8_d_ssd1306_128x32.d \
./Lib/u8x8_d_ssd1306_128x64_noname.d \
./Lib/u8x8_d_ssd1306_2040x16.d \
./Lib/u8x8_d_ssd1306_48x64.d \
./Lib/u8x8_d_ssd1306_64x32.d \
./Lib/u8x8_d_ssd1306_64x48.d \
./Lib/u8x8_d_ssd1306_72x40.d \
./Lib/u8x8_d_ssd1306_96x16.d \
./Lib/u8x8_d_ssd1306_96x40.d \
./Lib/u8x8_d_ssd1309.d \
./Lib/u8x8_d_ssd1316.d \
./Lib/u8x8_d_ssd1317.d \
./Lib/u8x8_d_ssd1318.d \
./Lib/u8x8_d_ssd1320.d \
./Lib/u8x8_d_ssd1322.d \
./Lib/u8x8_d_ssd1325.d \
./Lib/u8x8_d_ssd1326.d \
./Lib/u8x8_d_ssd1327.d \
./Lib/u8x8_d_ssd1329.d \
./Lib/u8x8_d_ssd1362.d \
./Lib/u8x8_d_ssd1606_172x72.d \
./Lib/u8x8_d_ssd1607_200x200.d \
./Lib/u8x8_d_st7511.d \
./Lib/u8x8_d_st75160.d \
./Lib/u8x8_d_st75256.d \
./Lib/u8x8_d_st7528.d \
./Lib/u8x8_d_st75320.d \
./Lib/u8x8_d_st7565.d \
./Lib/u8x8_d_st7567.d \
./Lib/u8x8_d_st7571.d \
./Lib/u8x8_d_st7586s_erc240160.d \
./Lib/u8x8_d_st7586s_jlx384160.d \
./Lib/u8x8_d_st7586s_s028hn118a.d \
./Lib/u8x8_d_st7586s_ymc240160.d \
./Lib/u8x8_d_st7588.d \
./Lib/u8x8_d_st7920.d \
./Lib/u8x8_d_stdio.d \
./Lib/u8x8_d_t6963.d \
./Lib/u8x8_d_uc1601.d \
./Lib/u8x8_d_uc1604.d \
./Lib/u8x8_d_uc1608.d \
./Lib/u8x8_d_uc1609.d \
./Lib/u8x8_d_uc1610.d \
./Lib/u8x8_d_uc1611.d \
./Lib/u8x8_d_uc1617.d \
./Lib/u8x8_d_uc1638.d \
./Lib/u8x8_d_uc1701_dogs102.d \
./Lib/u8x8_d_uc1701_mini12864.d \
./Lib/u8x8_debounce.d \
./Lib/u8x8_display.d \
./Lib/u8x8_fonts.d \
./Lib/u8x8_gpio.d \
./Lib/u8x8_input_value.d \
./Lib/u8x8_message.d \
./Lib/u8x8_selection_list.d \
./Lib/u8x8_setup.d \
./Lib/u8x8_string.d \
./Lib/u8x8_u16toa.d \
./Lib/u8x8_u8toa.d 


# Each subdirectory must supply rules for building sources it contributes
Lib/%.o Lib/%.su: ../Lib/%.c Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I"C:/Users/user/STM32Cube/Example/I2C_ADXL345/STM32CubeIDE/Lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lib

clean-Lib:
	-$(RM) ./Lib/adxl345.d ./Lib/adxl345.o ./Lib/adxl345.su ./Lib/mui.d ./Lib/mui.o ./Lib/mui.su ./Lib/mui_u8g2.d ./Lib/mui_u8g2.o ./Lib/mui_u8g2.su ./Lib/u8g2_bitmap.d ./Lib/u8g2_bitmap.o ./Lib/u8g2_bitmap.su ./Lib/u8g2_box.d ./Lib/u8g2_box.o ./Lib/u8g2_box.su ./Lib/u8g2_buffer.d ./Lib/u8g2_buffer.o ./Lib/u8g2_buffer.su ./Lib/u8g2_button.d ./Lib/u8g2_button.o ./Lib/u8g2_button.su ./Lib/u8g2_circle.d ./Lib/u8g2_circle.o ./Lib/u8g2_circle.su ./Lib/u8g2_cleardisplay.d ./Lib/u8g2_cleardisplay.o ./Lib/u8g2_cleardisplay.su ./Lib/u8g2_d_memory.d ./Lib/u8g2_d_memory.o ./Lib/u8g2_d_memory.su ./Lib/u8g2_d_setup.d ./Lib/u8g2_d_setup.o ./Lib/u8g2_d_setup.su ./Lib/u8g2_font.d ./Lib/u8g2_font.o ./Lib/u8g2_font.su ./Lib/u8g2_fonts.d ./Lib/u8g2_fonts.o ./Lib/u8g2_fonts.su ./Lib/u8g2_hvline.d ./Lib/u8g2_hvline.o ./Lib/u8g2_hvline.su ./Lib/u8g2_input_value.d ./Lib/u8g2_input_value.o ./Lib/u8g2_input_value.su ./Lib/u8g2_intersection.d ./Lib/u8g2_intersection.o ./Lib/u8g2_intersection.su ./Lib/u8g2_kerning.d ./Lib/u8g2_kerning.o ./Lib/u8g2_kerning.su ./Lib/u8g2_line.d ./Lib/u8g2_line.o ./Lib/u8g2_line.su ./Lib/u8g2_ll_hvline.d ./Lib/u8g2_ll_hvline.o ./Lib/u8g2_ll_hvline.su ./Lib/u8g2_message.d ./Lib/u8g2_message.o ./Lib/u8g2_message.su ./Lib/u8g2_polygon.d ./Lib/u8g2_polygon.o ./Lib/u8g2_polygon.su ./Lib/u8g2_selection_list.d ./Lib/u8g2_selection_list.o ./Lib/u8g2_selection_list.su ./Lib/u8g2_setup.d ./Lib/u8g2_setup.o ./Lib/u8g2_setup.su ./Lib/u8log.d ./Lib/u8log.o ./Lib/u8log.su ./Lib/u8log_u8g2.d ./Lib/u8log_u8g2.o ./Lib/u8log_u8g2.su ./Lib/u8log_u8x8.d ./Lib/u8log_u8x8.o ./Lib/u8log_u8x8.su ./Lib/u8x8_8x8.d ./Lib/u8x8_8x8.o ./Lib/u8x8_8x8.su ./Lib/u8x8_byte.d ./Lib/u8x8_byte.o ./Lib/u8x8_byte.su ./Lib/u8x8_cad.d ./Lib/u8x8_cad.o ./Lib/u8x8_cad.su ./Lib/u8x8_capture.d ./Lib/u8x8_capture.o ./Lib/u8x8_capture.su ./Lib/u8x8_d_a2printer.d ./Lib/u8x8_d_a2printer.o ./Lib/u8x8_d_a2printer.su ./Lib/u8x8_d_gp1247ai.d ./Lib/u8x8_d_gp1247ai.o ./Lib/u8x8_d_gp1247ai.su ./Lib/u8x8_d_gp1287ai.d ./Lib/u8x8_d_gp1287ai.o ./Lib/u8x8_d_gp1287ai.su ./Lib/u8x8_d_gu800.d ./Lib/u8x8_d_gu800.o ./Lib/u8x8_d_gu800.su ./Lib/u8x8_d_hd44102.d ./Lib/u8x8_d_hd44102.o ./Lib/u8x8_d_hd44102.su ./Lib/u8x8_d_il3820_296x128.d ./Lib/u8x8_d_il3820_296x128.o ./Lib/u8x8_d_il3820_296x128.su ./Lib/u8x8_d_ist3020.d ./Lib/u8x8_d_ist3020.o ./Lib/u8x8_d_ist3020.su ./Lib/u8x8_d_ist3088.d ./Lib/u8x8_d_ist3088.o ./Lib/u8x8_d_ist3088.su ./Lib/u8x8_d_ist7920.d ./Lib/u8x8_d_ist7920.o ./Lib/u8x8_d_ist7920.su ./Lib/u8x8_d_ks0108.d ./Lib/u8x8_d_ks0108.o ./Lib/u8x8_d_ks0108.su ./Lib/u8x8_d_lc7981.d ./Lib/u8x8_d_lc7981.o ./Lib/u8x8_d_lc7981.su ./Lib/u8x8_d_ld7032_60x32.d ./Lib/u8x8_d_ld7032_60x32.o ./Lib/u8x8_d_ld7032_60x32.su ./Lib/u8x8_d_ls013b7dh03.d ./Lib/u8x8_d_ls013b7dh03.o ./Lib/u8x8_d_ls013b7dh03.su ./Lib/u8x8_d_max7219.d ./Lib/u8x8_d_max7219.o ./Lib/u8x8_d_max7219.su ./Lib/u8x8_d_pcd8544_84x48.d ./Lib/u8x8_d_pcd8544_84x48.o ./Lib/u8x8_d_pcd8544_84x48.su ./Lib/u8x8_d_pcf8812.d ./Lib/u8x8_d_pcf8812.o ./Lib/u8x8_d_pcf8812.su ./Lib/u8x8_d_pcf8814_hx1230.d ./Lib/u8x8_d_pcf8814_hx1230.o ./Lib/u8x8_d_pcf8814_hx1230.su ./Lib/u8x8_d_s1d15300.d ./Lib/u8x8_d_s1d15300.o ./Lib/u8x8_d_s1d15300.su ./Lib/u8x8_d_s1d15721.d ./Lib/u8x8_d_s1d15721.o ./Lib/u8x8_d_s1d15721.su ./Lib/u8x8_d_s1d15e06.d ./Lib/u8x8_d_s1d15e06.o ./Lib/u8x8_d_s1d15e06.su ./Lib/u8x8_d_sbn1661.d ./Lib/u8x8_d_sbn1661.o ./Lib/u8x8_d_sbn1661.su ./Lib/u8x8_d_sed1330.d ./Lib/u8x8_d_sed1330.o ./Lib/u8x8_d_sed1330.su ./Lib/u8x8_d_sh1106_64x32.d ./Lib/u8x8_d_sh1106_64x32.o ./Lib/u8x8_d_sh1106_64x32.su ./Lib/u8x8_d_sh1106_72x40.d ./Lib/u8x8_d_sh1106_72x40.o ./Lib/u8x8_d_sh1106_72x40.su ./Lib/u8x8_d_sh1107.d ./Lib/u8x8_d_sh1107.o ./Lib/u8x8_d_sh1107.su ./Lib/u8x8_d_sh1108.d ./Lib/u8x8_d_sh1108.o ./Lib/u8x8_d_sh1108.su ./Lib/u8x8_d_sh1122.d ./Lib/u8x8_d_sh1122.o ./Lib/u8x8_d_sh1122.su ./Lib/u8x8_d_ssd1305.d ./Lib/u8x8_d_ssd1305.o ./Lib/u8x8_d_ssd1305.su ./Lib/u8x8_d_ssd1306_128x32.d ./Lib/u8x8_d_ssd1306_128x32.o ./Lib/u8x8_d_ssd1306_128x32.su ./Lib/u8x8_d_ssd1306_128x64_noname.d ./Lib/u8x8_d_ssd1306_128x64_noname.o ./Lib/u8x8_d_ssd1306_128x64_noname.su ./Lib/u8x8_d_ssd1306_2040x16.d ./Lib/u8x8_d_ssd1306_2040x16.o ./Lib/u8x8_d_ssd1306_2040x16.su ./Lib/u8x8_d_ssd1306_48x64.d ./Lib/u8x8_d_ssd1306_48x64.o ./Lib/u8x8_d_ssd1306_48x64.su ./Lib/u8x8_d_ssd1306_64x32.d ./Lib/u8x8_d_ssd1306_64x32.o ./Lib/u8x8_d_ssd1306_64x32.su ./Lib/u8x8_d_ssd1306_64x48.d ./Lib/u8x8_d_ssd1306_64x48.o ./Lib/u8x8_d_ssd1306_64x48.su ./Lib/u8x8_d_ssd1306_72x40.d ./Lib/u8x8_d_ssd1306_72x40.o ./Lib/u8x8_d_ssd1306_72x40.su ./Lib/u8x8_d_ssd1306_96x16.d ./Lib/u8x8_d_ssd1306_96x16.o ./Lib/u8x8_d_ssd1306_96x16.su ./Lib/u8x8_d_ssd1306_96x40.d ./Lib/u8x8_d_ssd1306_96x40.o ./Lib/u8x8_d_ssd1306_96x40.su ./Lib/u8x8_d_ssd1309.d ./Lib/u8x8_d_ssd1309.o ./Lib/u8x8_d_ssd1309.su ./Lib/u8x8_d_ssd1316.d ./Lib/u8x8_d_ssd1316.o ./Lib/u8x8_d_ssd1316.su ./Lib/u8x8_d_ssd1317.d ./Lib/u8x8_d_ssd1317.o ./Lib/u8x8_d_ssd1317.su ./Lib/u8x8_d_ssd1318.d ./Lib/u8x8_d_ssd1318.o ./Lib/u8x8_d_ssd1318.su ./Lib/u8x8_d_ssd1320.d ./Lib/u8x8_d_ssd1320.o ./Lib/u8x8_d_ssd1320.su ./Lib/u8x8_d_ssd1322.d ./Lib/u8x8_d_ssd1322.o ./Lib/u8x8_d_ssd1322.su ./Lib/u8x8_d_ssd1325.d ./Lib/u8x8_d_ssd1325.o ./Lib/u8x8_d_ssd1325.su ./Lib/u8x8_d_ssd1326.d ./Lib/u8x8_d_ssd1326.o ./Lib/u8x8_d_ssd1326.su ./Lib/u8x8_d_ssd1327.d ./Lib/u8x8_d_ssd1327.o ./Lib/u8x8_d_ssd1327.su ./Lib/u8x8_d_ssd1329.d ./Lib/u8x8_d_ssd1329.o ./Lib/u8x8_d_ssd1329.su ./Lib/u8x8_d_ssd1362.d ./Lib/u8x8_d_ssd1362.o ./Lib/u8x8_d_ssd1362.su ./Lib/u8x8_d_ssd1606_172x72.d ./Lib/u8x8_d_ssd1606_172x72.o ./Lib/u8x8_d_ssd1606_172x72.su ./Lib/u8x8_d_ssd1607_200x200.d ./Lib/u8x8_d_ssd1607_200x200.o ./Lib/u8x8_d_ssd1607_200x200.su ./Lib/u8x8_d_st7511.d ./Lib/u8x8_d_st7511.o ./Lib/u8x8_d_st7511.su ./Lib/u8x8_d_st75160.d ./Lib/u8x8_d_st75160.o ./Lib/u8x8_d_st75160.su ./Lib/u8x8_d_st75256.d ./Lib/u8x8_d_st75256.o ./Lib/u8x8_d_st75256.su ./Lib/u8x8_d_st7528.d ./Lib/u8x8_d_st7528.o ./Lib/u8x8_d_st7528.su ./Lib/u8x8_d_st75320.d ./Lib/u8x8_d_st75320.o
	-$(RM) ./Lib/u8x8_d_st75320.su ./Lib/u8x8_d_st7565.d ./Lib/u8x8_d_st7565.o ./Lib/u8x8_d_st7565.su ./Lib/u8x8_d_st7567.d ./Lib/u8x8_d_st7567.o ./Lib/u8x8_d_st7567.su ./Lib/u8x8_d_st7571.d ./Lib/u8x8_d_st7571.o ./Lib/u8x8_d_st7571.su ./Lib/u8x8_d_st7586s_erc240160.d ./Lib/u8x8_d_st7586s_erc240160.o ./Lib/u8x8_d_st7586s_erc240160.su ./Lib/u8x8_d_st7586s_jlx384160.d ./Lib/u8x8_d_st7586s_jlx384160.o ./Lib/u8x8_d_st7586s_jlx384160.su ./Lib/u8x8_d_st7586s_s028hn118a.d ./Lib/u8x8_d_st7586s_s028hn118a.o ./Lib/u8x8_d_st7586s_s028hn118a.su ./Lib/u8x8_d_st7586s_ymc240160.d ./Lib/u8x8_d_st7586s_ymc240160.o ./Lib/u8x8_d_st7586s_ymc240160.su ./Lib/u8x8_d_st7588.d ./Lib/u8x8_d_st7588.o ./Lib/u8x8_d_st7588.su ./Lib/u8x8_d_st7920.d ./Lib/u8x8_d_st7920.o ./Lib/u8x8_d_st7920.su ./Lib/u8x8_d_stdio.d ./Lib/u8x8_d_stdio.o ./Lib/u8x8_d_stdio.su ./Lib/u8x8_d_t6963.d ./Lib/u8x8_d_t6963.o ./Lib/u8x8_d_t6963.su ./Lib/u8x8_d_uc1601.d ./Lib/u8x8_d_uc1601.o ./Lib/u8x8_d_uc1601.su ./Lib/u8x8_d_uc1604.d ./Lib/u8x8_d_uc1604.o ./Lib/u8x8_d_uc1604.su ./Lib/u8x8_d_uc1608.d ./Lib/u8x8_d_uc1608.o ./Lib/u8x8_d_uc1608.su ./Lib/u8x8_d_uc1609.d ./Lib/u8x8_d_uc1609.o ./Lib/u8x8_d_uc1609.su ./Lib/u8x8_d_uc1610.d ./Lib/u8x8_d_uc1610.o ./Lib/u8x8_d_uc1610.su ./Lib/u8x8_d_uc1611.d ./Lib/u8x8_d_uc1611.o ./Lib/u8x8_d_uc1611.su ./Lib/u8x8_d_uc1617.d ./Lib/u8x8_d_uc1617.o ./Lib/u8x8_d_uc1617.su ./Lib/u8x8_d_uc1638.d ./Lib/u8x8_d_uc1638.o ./Lib/u8x8_d_uc1638.su ./Lib/u8x8_d_uc1701_dogs102.d ./Lib/u8x8_d_uc1701_dogs102.o ./Lib/u8x8_d_uc1701_dogs102.su ./Lib/u8x8_d_uc1701_mini12864.d ./Lib/u8x8_d_uc1701_mini12864.o ./Lib/u8x8_d_uc1701_mini12864.su ./Lib/u8x8_debounce.d ./Lib/u8x8_debounce.o ./Lib/u8x8_debounce.su ./Lib/u8x8_display.d ./Lib/u8x8_display.o ./Lib/u8x8_display.su ./Lib/u8x8_fonts.d ./Lib/u8x8_fonts.o ./Lib/u8x8_fonts.su ./Lib/u8x8_gpio.d ./Lib/u8x8_gpio.o ./Lib/u8x8_gpio.su ./Lib/u8x8_input_value.d ./Lib/u8x8_input_value.o ./Lib/u8x8_input_value.su ./Lib/u8x8_message.d ./Lib/u8x8_message.o ./Lib/u8x8_message.su ./Lib/u8x8_selection_list.d ./Lib/u8x8_selection_list.o ./Lib/u8x8_selection_list.su ./Lib/u8x8_setup.d ./Lib/u8x8_setup.o ./Lib/u8x8_setup.su ./Lib/u8x8_string.d ./Lib/u8x8_string.o ./Lib/u8x8_string.su ./Lib/u8x8_u16toa.d ./Lib/u8x8_u16toa.o ./Lib/u8x8_u16toa.su ./Lib/u8x8_u8toa.d ./Lib/u8x8_u8toa.o ./Lib/u8x8_u8toa.su

.PHONY: clean-Lib
