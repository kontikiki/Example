################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../u8g2/mui.c \
../u8g2/mui_u8g2.c \
../u8g2/u8g2_bitmap.c \
../u8g2/u8g2_box.c \
../u8g2/u8g2_buffer.c \
../u8g2/u8g2_button.c \
../u8g2/u8g2_circle.c \
../u8g2/u8g2_cleardisplay.c \
../u8g2/u8g2_d_memory.c \
../u8g2/u8g2_d_setup.c \
../u8g2/u8g2_font.c \
../u8g2/u8g2_fonts.c \
../u8g2/u8g2_hvline.c \
../u8g2/u8g2_input_value.c \
../u8g2/u8g2_intersection.c \
../u8g2/u8g2_kerning.c \
../u8g2/u8g2_line.c \
../u8g2/u8g2_ll_hvline.c \
../u8g2/u8g2_message.c \
../u8g2/u8g2_polygon.c \
../u8g2/u8g2_selection_list.c \
../u8g2/u8g2_setup.c \
../u8g2/u8log.c \
../u8g2/u8log_u8g2.c \
../u8g2/u8log_u8x8.c \
../u8g2/u8x8_8x8.c \
../u8g2/u8x8_byte.c \
../u8g2/u8x8_cad.c \
../u8g2/u8x8_capture.c \
../u8g2/u8x8_d_a2printer.c \
../u8g2/u8x8_d_gp1247ai.c \
../u8g2/u8x8_d_gp1287ai.c \
../u8g2/u8x8_d_gu800.c \
../u8g2/u8x8_d_hd44102.c \
../u8g2/u8x8_d_il3820_296x128.c \
../u8g2/u8x8_d_ist3020.c \
../u8g2/u8x8_d_ist3088.c \
../u8g2/u8x8_d_ist7920.c \
../u8g2/u8x8_d_ks0108.c \
../u8g2/u8x8_d_lc7981.c \
../u8g2/u8x8_d_ld7032_60x32.c \
../u8g2/u8x8_d_ls013b7dh03.c \
../u8g2/u8x8_d_max7219.c \
../u8g2/u8x8_d_pcd8544_84x48.c \
../u8g2/u8x8_d_pcf8812.c \
../u8g2/u8x8_d_pcf8814_hx1230.c \
../u8g2/u8x8_d_s1d15300.c \
../u8g2/u8x8_d_s1d15721.c \
../u8g2/u8x8_d_s1d15e06.c \
../u8g2/u8x8_d_sbn1661.c \
../u8g2/u8x8_d_sed1330.c \
../u8g2/u8x8_d_sh1106_64x32.c \
../u8g2/u8x8_d_sh1106_72x40.c \
../u8g2/u8x8_d_sh1107.c \
../u8g2/u8x8_d_sh1108.c \
../u8g2/u8x8_d_sh1122.c \
../u8g2/u8x8_d_ssd1305.c \
../u8g2/u8x8_d_ssd1306_128x32.c \
../u8g2/u8x8_d_ssd1306_128x64_noname.c \
../u8g2/u8x8_d_ssd1306_2040x16.c \
../u8g2/u8x8_d_ssd1306_48x64.c \
../u8g2/u8x8_d_ssd1306_64x32.c \
../u8g2/u8x8_d_ssd1306_64x48.c \
../u8g2/u8x8_d_ssd1306_72x40.c \
../u8g2/u8x8_d_ssd1306_96x16.c \
../u8g2/u8x8_d_ssd1306_96x40.c \
../u8g2/u8x8_d_ssd1309.c \
../u8g2/u8x8_d_ssd1316.c \
../u8g2/u8x8_d_ssd1317.c \
../u8g2/u8x8_d_ssd1318.c \
../u8g2/u8x8_d_ssd1320.c \
../u8g2/u8x8_d_ssd1322.c \
../u8g2/u8x8_d_ssd1325.c \
../u8g2/u8x8_d_ssd1326.c \
../u8g2/u8x8_d_ssd1327.c \
../u8g2/u8x8_d_ssd1329.c \
../u8g2/u8x8_d_ssd1362.c \
../u8g2/u8x8_d_ssd1606_172x72.c \
../u8g2/u8x8_d_ssd1607_200x200.c \
../u8g2/u8x8_d_st7511.c \
../u8g2/u8x8_d_st75160.c \
../u8g2/u8x8_d_st75256.c \
../u8g2/u8x8_d_st7528.c \
../u8g2/u8x8_d_st75320.c \
../u8g2/u8x8_d_st7565.c \
../u8g2/u8x8_d_st7567.c \
../u8g2/u8x8_d_st7571.c \
../u8g2/u8x8_d_st7586s_erc240160.c \
../u8g2/u8x8_d_st7586s_jlx384160.c \
../u8g2/u8x8_d_st7586s_s028hn118a.c \
../u8g2/u8x8_d_st7586s_ymc240160.c \
../u8g2/u8x8_d_st7588.c \
../u8g2/u8x8_d_st7920.c \
../u8g2/u8x8_d_stdio.c \
../u8g2/u8x8_d_t6963.c \
../u8g2/u8x8_d_uc1601.c \
../u8g2/u8x8_d_uc1604.c \
../u8g2/u8x8_d_uc1608.c \
../u8g2/u8x8_d_uc1609.c \
../u8g2/u8x8_d_uc1610.c \
../u8g2/u8x8_d_uc1611.c \
../u8g2/u8x8_d_uc1617.c \
../u8g2/u8x8_d_uc1638.c \
../u8g2/u8x8_d_uc1701_dogs102.c \
../u8g2/u8x8_d_uc1701_mini12864.c \
../u8g2/u8x8_debounce.c \
../u8g2/u8x8_display.c \
../u8g2/u8x8_fonts.c \
../u8g2/u8x8_gpio.c \
../u8g2/u8x8_input_value.c \
../u8g2/u8x8_message.c \
../u8g2/u8x8_selection_list.c \
../u8g2/u8x8_setup.c \
../u8g2/u8x8_string.c \
../u8g2/u8x8_u16toa.c \
../u8g2/u8x8_u8toa.c 

OBJS += \
./u8g2/mui.o \
./u8g2/mui_u8g2.o \
./u8g2/u8g2_bitmap.o \
./u8g2/u8g2_box.o \
./u8g2/u8g2_buffer.o \
./u8g2/u8g2_button.o \
./u8g2/u8g2_circle.o \
./u8g2/u8g2_cleardisplay.o \
./u8g2/u8g2_d_memory.o \
./u8g2/u8g2_d_setup.o \
./u8g2/u8g2_font.o \
./u8g2/u8g2_fonts.o \
./u8g2/u8g2_hvline.o \
./u8g2/u8g2_input_value.o \
./u8g2/u8g2_intersection.o \
./u8g2/u8g2_kerning.o \
./u8g2/u8g2_line.o \
./u8g2/u8g2_ll_hvline.o \
./u8g2/u8g2_message.o \
./u8g2/u8g2_polygon.o \
./u8g2/u8g2_selection_list.o \
./u8g2/u8g2_setup.o \
./u8g2/u8log.o \
./u8g2/u8log_u8g2.o \
./u8g2/u8log_u8x8.o \
./u8g2/u8x8_8x8.o \
./u8g2/u8x8_byte.o \
./u8g2/u8x8_cad.o \
./u8g2/u8x8_capture.o \
./u8g2/u8x8_d_a2printer.o \
./u8g2/u8x8_d_gp1247ai.o \
./u8g2/u8x8_d_gp1287ai.o \
./u8g2/u8x8_d_gu800.o \
./u8g2/u8x8_d_hd44102.o \
./u8g2/u8x8_d_il3820_296x128.o \
./u8g2/u8x8_d_ist3020.o \
./u8g2/u8x8_d_ist3088.o \
./u8g2/u8x8_d_ist7920.o \
./u8g2/u8x8_d_ks0108.o \
./u8g2/u8x8_d_lc7981.o \
./u8g2/u8x8_d_ld7032_60x32.o \
./u8g2/u8x8_d_ls013b7dh03.o \
./u8g2/u8x8_d_max7219.o \
./u8g2/u8x8_d_pcd8544_84x48.o \
./u8g2/u8x8_d_pcf8812.o \
./u8g2/u8x8_d_pcf8814_hx1230.o \
./u8g2/u8x8_d_s1d15300.o \
./u8g2/u8x8_d_s1d15721.o \
./u8g2/u8x8_d_s1d15e06.o \
./u8g2/u8x8_d_sbn1661.o \
./u8g2/u8x8_d_sed1330.o \
./u8g2/u8x8_d_sh1106_64x32.o \
./u8g2/u8x8_d_sh1106_72x40.o \
./u8g2/u8x8_d_sh1107.o \
./u8g2/u8x8_d_sh1108.o \
./u8g2/u8x8_d_sh1122.o \
./u8g2/u8x8_d_ssd1305.o \
./u8g2/u8x8_d_ssd1306_128x32.o \
./u8g2/u8x8_d_ssd1306_128x64_noname.o \
./u8g2/u8x8_d_ssd1306_2040x16.o \
./u8g2/u8x8_d_ssd1306_48x64.o \
./u8g2/u8x8_d_ssd1306_64x32.o \
./u8g2/u8x8_d_ssd1306_64x48.o \
./u8g2/u8x8_d_ssd1306_72x40.o \
./u8g2/u8x8_d_ssd1306_96x16.o \
./u8g2/u8x8_d_ssd1306_96x40.o \
./u8g2/u8x8_d_ssd1309.o \
./u8g2/u8x8_d_ssd1316.o \
./u8g2/u8x8_d_ssd1317.o \
./u8g2/u8x8_d_ssd1318.o \
./u8g2/u8x8_d_ssd1320.o \
./u8g2/u8x8_d_ssd1322.o \
./u8g2/u8x8_d_ssd1325.o \
./u8g2/u8x8_d_ssd1326.o \
./u8g2/u8x8_d_ssd1327.o \
./u8g2/u8x8_d_ssd1329.o \
./u8g2/u8x8_d_ssd1362.o \
./u8g2/u8x8_d_ssd1606_172x72.o \
./u8g2/u8x8_d_ssd1607_200x200.o \
./u8g2/u8x8_d_st7511.o \
./u8g2/u8x8_d_st75160.o \
./u8g2/u8x8_d_st75256.o \
./u8g2/u8x8_d_st7528.o \
./u8g2/u8x8_d_st75320.o \
./u8g2/u8x8_d_st7565.o \
./u8g2/u8x8_d_st7567.o \
./u8g2/u8x8_d_st7571.o \
./u8g2/u8x8_d_st7586s_erc240160.o \
./u8g2/u8x8_d_st7586s_jlx384160.o \
./u8g2/u8x8_d_st7586s_s028hn118a.o \
./u8g2/u8x8_d_st7586s_ymc240160.o \
./u8g2/u8x8_d_st7588.o \
./u8g2/u8x8_d_st7920.o \
./u8g2/u8x8_d_stdio.o \
./u8g2/u8x8_d_t6963.o \
./u8g2/u8x8_d_uc1601.o \
./u8g2/u8x8_d_uc1604.o \
./u8g2/u8x8_d_uc1608.o \
./u8g2/u8x8_d_uc1609.o \
./u8g2/u8x8_d_uc1610.o \
./u8g2/u8x8_d_uc1611.o \
./u8g2/u8x8_d_uc1617.o \
./u8g2/u8x8_d_uc1638.o \
./u8g2/u8x8_d_uc1701_dogs102.o \
./u8g2/u8x8_d_uc1701_mini12864.o \
./u8g2/u8x8_debounce.o \
./u8g2/u8x8_display.o \
./u8g2/u8x8_fonts.o \
./u8g2/u8x8_gpio.o \
./u8g2/u8x8_input_value.o \
./u8g2/u8x8_message.o \
./u8g2/u8x8_selection_list.o \
./u8g2/u8x8_setup.o \
./u8g2/u8x8_string.o \
./u8g2/u8x8_u16toa.o \
./u8g2/u8x8_u8toa.o 

C_DEPS += \
./u8g2/mui.d \
./u8g2/mui_u8g2.d \
./u8g2/u8g2_bitmap.d \
./u8g2/u8g2_box.d \
./u8g2/u8g2_buffer.d \
./u8g2/u8g2_button.d \
./u8g2/u8g2_circle.d \
./u8g2/u8g2_cleardisplay.d \
./u8g2/u8g2_d_memory.d \
./u8g2/u8g2_d_setup.d \
./u8g2/u8g2_font.d \
./u8g2/u8g2_fonts.d \
./u8g2/u8g2_hvline.d \
./u8g2/u8g2_input_value.d \
./u8g2/u8g2_intersection.d \
./u8g2/u8g2_kerning.d \
./u8g2/u8g2_line.d \
./u8g2/u8g2_ll_hvline.d \
./u8g2/u8g2_message.d \
./u8g2/u8g2_polygon.d \
./u8g2/u8g2_selection_list.d \
./u8g2/u8g2_setup.d \
./u8g2/u8log.d \
./u8g2/u8log_u8g2.d \
./u8g2/u8log_u8x8.d \
./u8g2/u8x8_8x8.d \
./u8g2/u8x8_byte.d \
./u8g2/u8x8_cad.d \
./u8g2/u8x8_capture.d \
./u8g2/u8x8_d_a2printer.d \
./u8g2/u8x8_d_gp1247ai.d \
./u8g2/u8x8_d_gp1287ai.d \
./u8g2/u8x8_d_gu800.d \
./u8g2/u8x8_d_hd44102.d \
./u8g2/u8x8_d_il3820_296x128.d \
./u8g2/u8x8_d_ist3020.d \
./u8g2/u8x8_d_ist3088.d \
./u8g2/u8x8_d_ist7920.d \
./u8g2/u8x8_d_ks0108.d \
./u8g2/u8x8_d_lc7981.d \
./u8g2/u8x8_d_ld7032_60x32.d \
./u8g2/u8x8_d_ls013b7dh03.d \
./u8g2/u8x8_d_max7219.d \
./u8g2/u8x8_d_pcd8544_84x48.d \
./u8g2/u8x8_d_pcf8812.d \
./u8g2/u8x8_d_pcf8814_hx1230.d \
./u8g2/u8x8_d_s1d15300.d \
./u8g2/u8x8_d_s1d15721.d \
./u8g2/u8x8_d_s1d15e06.d \
./u8g2/u8x8_d_sbn1661.d \
./u8g2/u8x8_d_sed1330.d \
./u8g2/u8x8_d_sh1106_64x32.d \
./u8g2/u8x8_d_sh1106_72x40.d \
./u8g2/u8x8_d_sh1107.d \
./u8g2/u8x8_d_sh1108.d \
./u8g2/u8x8_d_sh1122.d \
./u8g2/u8x8_d_ssd1305.d \
./u8g2/u8x8_d_ssd1306_128x32.d \
./u8g2/u8x8_d_ssd1306_128x64_noname.d \
./u8g2/u8x8_d_ssd1306_2040x16.d \
./u8g2/u8x8_d_ssd1306_48x64.d \
./u8g2/u8x8_d_ssd1306_64x32.d \
./u8g2/u8x8_d_ssd1306_64x48.d \
./u8g2/u8x8_d_ssd1306_72x40.d \
./u8g2/u8x8_d_ssd1306_96x16.d \
./u8g2/u8x8_d_ssd1306_96x40.d \
./u8g2/u8x8_d_ssd1309.d \
./u8g2/u8x8_d_ssd1316.d \
./u8g2/u8x8_d_ssd1317.d \
./u8g2/u8x8_d_ssd1318.d \
./u8g2/u8x8_d_ssd1320.d \
./u8g2/u8x8_d_ssd1322.d \
./u8g2/u8x8_d_ssd1325.d \
./u8g2/u8x8_d_ssd1326.d \
./u8g2/u8x8_d_ssd1327.d \
./u8g2/u8x8_d_ssd1329.d \
./u8g2/u8x8_d_ssd1362.d \
./u8g2/u8x8_d_ssd1606_172x72.d \
./u8g2/u8x8_d_ssd1607_200x200.d \
./u8g2/u8x8_d_st7511.d \
./u8g2/u8x8_d_st75160.d \
./u8g2/u8x8_d_st75256.d \
./u8g2/u8x8_d_st7528.d \
./u8g2/u8x8_d_st75320.d \
./u8g2/u8x8_d_st7565.d \
./u8g2/u8x8_d_st7567.d \
./u8g2/u8x8_d_st7571.d \
./u8g2/u8x8_d_st7586s_erc240160.d \
./u8g2/u8x8_d_st7586s_jlx384160.d \
./u8g2/u8x8_d_st7586s_s028hn118a.d \
./u8g2/u8x8_d_st7586s_ymc240160.d \
./u8g2/u8x8_d_st7588.d \
./u8g2/u8x8_d_st7920.d \
./u8g2/u8x8_d_stdio.d \
./u8g2/u8x8_d_t6963.d \
./u8g2/u8x8_d_uc1601.d \
./u8g2/u8x8_d_uc1604.d \
./u8g2/u8x8_d_uc1608.d \
./u8g2/u8x8_d_uc1609.d \
./u8g2/u8x8_d_uc1610.d \
./u8g2/u8x8_d_uc1611.d \
./u8g2/u8x8_d_uc1617.d \
./u8g2/u8x8_d_uc1638.d \
./u8g2/u8x8_d_uc1701_dogs102.d \
./u8g2/u8x8_d_uc1701_mini12864.d \
./u8g2/u8x8_debounce.d \
./u8g2/u8x8_display.d \
./u8g2/u8x8_fonts.d \
./u8g2/u8x8_gpio.d \
./u8g2/u8x8_input_value.d \
./u8g2/u8x8_message.d \
./u8g2/u8x8_selection_list.d \
./u8g2/u8x8_setup.d \
./u8g2/u8x8_string.d \
./u8g2/u8x8_u16toa.d \
./u8g2/u8x8_u8toa.d 


# Each subdirectory must supply rules for building sources it contributes
u8g2/%.o u8g2/%.su u8g2/%.cyclo: ../u8g2/%.c u8g2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/user/STM32CubeIDE/workspace_1.11.2/gps_test_refactoring/u8g2" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-u8g2

clean-u8g2:
	-$(RM) ./u8g2/mui.cyclo ./u8g2/mui.d ./u8g2/mui.o ./u8g2/mui.su ./u8g2/mui_u8g2.cyclo ./u8g2/mui_u8g2.d ./u8g2/mui_u8g2.o ./u8g2/mui_u8g2.su ./u8g2/u8g2_bitmap.cyclo ./u8g2/u8g2_bitmap.d ./u8g2/u8g2_bitmap.o ./u8g2/u8g2_bitmap.su ./u8g2/u8g2_box.cyclo ./u8g2/u8g2_box.d ./u8g2/u8g2_box.o ./u8g2/u8g2_box.su ./u8g2/u8g2_buffer.cyclo ./u8g2/u8g2_buffer.d ./u8g2/u8g2_buffer.o ./u8g2/u8g2_buffer.su ./u8g2/u8g2_button.cyclo ./u8g2/u8g2_button.d ./u8g2/u8g2_button.o ./u8g2/u8g2_button.su ./u8g2/u8g2_circle.cyclo ./u8g2/u8g2_circle.d ./u8g2/u8g2_circle.o ./u8g2/u8g2_circle.su ./u8g2/u8g2_cleardisplay.cyclo ./u8g2/u8g2_cleardisplay.d ./u8g2/u8g2_cleardisplay.o ./u8g2/u8g2_cleardisplay.su ./u8g2/u8g2_d_memory.cyclo ./u8g2/u8g2_d_memory.d ./u8g2/u8g2_d_memory.o ./u8g2/u8g2_d_memory.su ./u8g2/u8g2_d_setup.cyclo ./u8g2/u8g2_d_setup.d ./u8g2/u8g2_d_setup.o ./u8g2/u8g2_d_setup.su ./u8g2/u8g2_font.cyclo ./u8g2/u8g2_font.d ./u8g2/u8g2_font.o ./u8g2/u8g2_font.su ./u8g2/u8g2_fonts.cyclo ./u8g2/u8g2_fonts.d ./u8g2/u8g2_fonts.o ./u8g2/u8g2_fonts.su ./u8g2/u8g2_hvline.cyclo ./u8g2/u8g2_hvline.d ./u8g2/u8g2_hvline.o ./u8g2/u8g2_hvline.su ./u8g2/u8g2_input_value.cyclo ./u8g2/u8g2_input_value.d ./u8g2/u8g2_input_value.o ./u8g2/u8g2_input_value.su ./u8g2/u8g2_intersection.cyclo ./u8g2/u8g2_intersection.d ./u8g2/u8g2_intersection.o ./u8g2/u8g2_intersection.su ./u8g2/u8g2_kerning.cyclo ./u8g2/u8g2_kerning.d ./u8g2/u8g2_kerning.o ./u8g2/u8g2_kerning.su ./u8g2/u8g2_line.cyclo ./u8g2/u8g2_line.d ./u8g2/u8g2_line.o ./u8g2/u8g2_line.su ./u8g2/u8g2_ll_hvline.cyclo ./u8g2/u8g2_ll_hvline.d ./u8g2/u8g2_ll_hvline.o ./u8g2/u8g2_ll_hvline.su ./u8g2/u8g2_message.cyclo ./u8g2/u8g2_message.d ./u8g2/u8g2_message.o ./u8g2/u8g2_message.su ./u8g2/u8g2_polygon.cyclo ./u8g2/u8g2_polygon.d ./u8g2/u8g2_polygon.o ./u8g2/u8g2_polygon.su ./u8g2/u8g2_selection_list.cyclo ./u8g2/u8g2_selection_list.d ./u8g2/u8g2_selection_list.o ./u8g2/u8g2_selection_list.su ./u8g2/u8g2_setup.cyclo ./u8g2/u8g2_setup.d ./u8g2/u8g2_setup.o ./u8g2/u8g2_setup.su ./u8g2/u8log.cyclo ./u8g2/u8log.d ./u8g2/u8log.o ./u8g2/u8log.su ./u8g2/u8log_u8g2.cyclo ./u8g2/u8log_u8g2.d ./u8g2/u8log_u8g2.o ./u8g2/u8log_u8g2.su ./u8g2/u8log_u8x8.cyclo ./u8g2/u8log_u8x8.d ./u8g2/u8log_u8x8.o ./u8g2/u8log_u8x8.su ./u8g2/u8x8_8x8.cyclo ./u8g2/u8x8_8x8.d ./u8g2/u8x8_8x8.o ./u8g2/u8x8_8x8.su ./u8g2/u8x8_byte.cyclo ./u8g2/u8x8_byte.d ./u8g2/u8x8_byte.o ./u8g2/u8x8_byte.su ./u8g2/u8x8_cad.cyclo ./u8g2/u8x8_cad.d ./u8g2/u8x8_cad.o ./u8g2/u8x8_cad.su ./u8g2/u8x8_capture.cyclo ./u8g2/u8x8_capture.d ./u8g2/u8x8_capture.o ./u8g2/u8x8_capture.su ./u8g2/u8x8_d_a2printer.cyclo ./u8g2/u8x8_d_a2printer.d ./u8g2/u8x8_d_a2printer.o ./u8g2/u8x8_d_a2printer.su ./u8g2/u8x8_d_gp1247ai.cyclo ./u8g2/u8x8_d_gp1247ai.d ./u8g2/u8x8_d_gp1247ai.o ./u8g2/u8x8_d_gp1247ai.su ./u8g2/u8x8_d_gp1287ai.cyclo ./u8g2/u8x8_d_gp1287ai.d ./u8g2/u8x8_d_gp1287ai.o ./u8g2/u8x8_d_gp1287ai.su ./u8g2/u8x8_d_gu800.cyclo ./u8g2/u8x8_d_gu800.d ./u8g2/u8x8_d_gu800.o ./u8g2/u8x8_d_gu800.su ./u8g2/u8x8_d_hd44102.cyclo ./u8g2/u8x8_d_hd44102.d ./u8g2/u8x8_d_hd44102.o ./u8g2/u8x8_d_hd44102.su ./u8g2/u8x8_d_il3820_296x128.cyclo ./u8g2/u8x8_d_il3820_296x128.d ./u8g2/u8x8_d_il3820_296x128.o ./u8g2/u8x8_d_il3820_296x128.su ./u8g2/u8x8_d_ist3020.cyclo ./u8g2/u8x8_d_ist3020.d ./u8g2/u8x8_d_ist3020.o ./u8g2/u8x8_d_ist3020.su ./u8g2/u8x8_d_ist3088.cyclo ./u8g2/u8x8_d_ist3088.d ./u8g2/u8x8_d_ist3088.o ./u8g2/u8x8_d_ist3088.su ./u8g2/u8x8_d_ist7920.cyclo ./u8g2/u8x8_d_ist7920.d ./u8g2/u8x8_d_ist7920.o ./u8g2/u8x8_d_ist7920.su ./u8g2/u8x8_d_ks0108.cyclo ./u8g2/u8x8_d_ks0108.d ./u8g2/u8x8_d_ks0108.o ./u8g2/u8x8_d_ks0108.su ./u8g2/u8x8_d_lc7981.cyclo ./u8g2/u8x8_d_lc7981.d ./u8g2/u8x8_d_lc7981.o ./u8g2/u8x8_d_lc7981.su ./u8g2/u8x8_d_ld7032_60x32.cyclo ./u8g2/u8x8_d_ld7032_60x32.d ./u8g2/u8x8_d_ld7032_60x32.o ./u8g2/u8x8_d_ld7032_60x32.su ./u8g2/u8x8_d_ls013b7dh03.cyclo ./u8g2/u8x8_d_ls013b7dh03.d ./u8g2/u8x8_d_ls013b7dh03.o ./u8g2/u8x8_d_ls013b7dh03.su ./u8g2/u8x8_d_max7219.cyclo ./u8g2/u8x8_d_max7219.d ./u8g2/u8x8_d_max7219.o ./u8g2/u8x8_d_max7219.su ./u8g2/u8x8_d_pcd8544_84x48.cyclo ./u8g2/u8x8_d_pcd8544_84x48.d ./u8g2/u8x8_d_pcd8544_84x48.o ./u8g2/u8x8_d_pcd8544_84x48.su ./u8g2/u8x8_d_pcf8812.cyclo ./u8g2/u8x8_d_pcf8812.d ./u8g2/u8x8_d_pcf8812.o ./u8g2/u8x8_d_pcf8812.su ./u8g2/u8x8_d_pcf8814_hx1230.cyclo ./u8g2/u8x8_d_pcf8814_hx1230.d ./u8g2/u8x8_d_pcf8814_hx1230.o ./u8g2/u8x8_d_pcf8814_hx1230.su ./u8g2/u8x8_d_s1d15300.cyclo ./u8g2/u8x8_d_s1d15300.d ./u8g2/u8x8_d_s1d15300.o ./u8g2/u8x8_d_s1d15300.su ./u8g2/u8x8_d_s1d15721.cyclo ./u8g2/u8x8_d_s1d15721.d ./u8g2/u8x8_d_s1d15721.o ./u8g2/u8x8_d_s1d15721.su ./u8g2/u8x8_d_s1d15e06.cyclo ./u8g2/u8x8_d_s1d15e06.d ./u8g2/u8x8_d_s1d15e06.o ./u8g2/u8x8_d_s1d15e06.su ./u8g2/u8x8_d_sbn1661.cyclo ./u8g2/u8x8_d_sbn1661.d ./u8g2/u8x8_d_sbn1661.o ./u8g2/u8x8_d_sbn1661.su ./u8g2/u8x8_d_sed1330.cyclo ./u8g2/u8x8_d_sed1330.d ./u8g2/u8x8_d_sed1330.o ./u8g2/u8x8_d_sed1330.su ./u8g2/u8x8_d_sh1106_64x32.cyclo ./u8g2/u8x8_d_sh1106_64x32.d ./u8g2/u8x8_d_sh1106_64x32.o ./u8g2/u8x8_d_sh1106_64x32.su ./u8g2/u8x8_d_sh1106_72x40.cyclo ./u8g2/u8x8_d_sh1106_72x40.d ./u8g2/u8x8_d_sh1106_72x40.o ./u8g2/u8x8_d_sh1106_72x40.su ./u8g2/u8x8_d_sh1107.cyclo ./u8g2/u8x8_d_sh1107.d ./u8g2/u8x8_d_sh1107.o ./u8g2/u8x8_d_sh1107.su ./u8g2/u8x8_d_sh1108.cyclo ./u8g2/u8x8_d_sh1108.d ./u8g2/u8x8_d_sh1108.o ./u8g2/u8x8_d_sh1108.su ./u8g2/u8x8_d_sh1122.cyclo ./u8g2/u8x8_d_sh1122.d ./u8g2/u8x8_d_sh1122.o ./u8g2/u8x8_d_sh1122.su ./u8g2/u8x8_d_ssd1305.cyclo ./u8g2/u8x8_d_ssd1305.d ./u8g2/u8x8_d_ssd1305.o ./u8g2/u8x8_d_ssd1305.su ./u8g2/u8x8_d_ssd1306_128x32.cyclo ./u8g2/u8x8_d_ssd1306_128x32.d ./u8g2/u8x8_d_ssd1306_128x32.o ./u8g2/u8x8_d_ssd1306_128x32.su ./u8g2/u8x8_d_ssd1306_128x64_noname.cyclo ./u8g2/u8x8_d_ssd1306_128x64_noname.d ./u8g2/u8x8_d_ssd1306_128x64_noname.o ./u8g2/u8x8_d_ssd1306_128x64_noname.su ./u8g2/u8x8_d_ssd1306_2040x16.cyclo ./u8g2/u8x8_d_ssd1306_2040x16.d ./u8g2/u8x8_d_ssd1306_2040x16.o ./u8g2/u8x8_d_ssd1306_2040x16.su
	-$(RM) ./u8g2/u8x8_d_ssd1306_48x64.cyclo ./u8g2/u8x8_d_ssd1306_48x64.d ./u8g2/u8x8_d_ssd1306_48x64.o ./u8g2/u8x8_d_ssd1306_48x64.su ./u8g2/u8x8_d_ssd1306_64x32.cyclo ./u8g2/u8x8_d_ssd1306_64x32.d ./u8g2/u8x8_d_ssd1306_64x32.o ./u8g2/u8x8_d_ssd1306_64x32.su ./u8g2/u8x8_d_ssd1306_64x48.cyclo ./u8g2/u8x8_d_ssd1306_64x48.d ./u8g2/u8x8_d_ssd1306_64x48.o ./u8g2/u8x8_d_ssd1306_64x48.su ./u8g2/u8x8_d_ssd1306_72x40.cyclo ./u8g2/u8x8_d_ssd1306_72x40.d ./u8g2/u8x8_d_ssd1306_72x40.o ./u8g2/u8x8_d_ssd1306_72x40.su ./u8g2/u8x8_d_ssd1306_96x16.cyclo ./u8g2/u8x8_d_ssd1306_96x16.d ./u8g2/u8x8_d_ssd1306_96x16.o ./u8g2/u8x8_d_ssd1306_96x16.su ./u8g2/u8x8_d_ssd1306_96x40.cyclo ./u8g2/u8x8_d_ssd1306_96x40.d ./u8g2/u8x8_d_ssd1306_96x40.o ./u8g2/u8x8_d_ssd1306_96x40.su ./u8g2/u8x8_d_ssd1309.cyclo ./u8g2/u8x8_d_ssd1309.d ./u8g2/u8x8_d_ssd1309.o ./u8g2/u8x8_d_ssd1309.su ./u8g2/u8x8_d_ssd1316.cyclo ./u8g2/u8x8_d_ssd1316.d ./u8g2/u8x8_d_ssd1316.o ./u8g2/u8x8_d_ssd1316.su ./u8g2/u8x8_d_ssd1317.cyclo ./u8g2/u8x8_d_ssd1317.d ./u8g2/u8x8_d_ssd1317.o ./u8g2/u8x8_d_ssd1317.su ./u8g2/u8x8_d_ssd1318.cyclo ./u8g2/u8x8_d_ssd1318.d ./u8g2/u8x8_d_ssd1318.o ./u8g2/u8x8_d_ssd1318.su ./u8g2/u8x8_d_ssd1320.cyclo ./u8g2/u8x8_d_ssd1320.d ./u8g2/u8x8_d_ssd1320.o ./u8g2/u8x8_d_ssd1320.su ./u8g2/u8x8_d_ssd1322.cyclo ./u8g2/u8x8_d_ssd1322.d ./u8g2/u8x8_d_ssd1322.o ./u8g2/u8x8_d_ssd1322.su ./u8g2/u8x8_d_ssd1325.cyclo ./u8g2/u8x8_d_ssd1325.d ./u8g2/u8x8_d_ssd1325.o ./u8g2/u8x8_d_ssd1325.su ./u8g2/u8x8_d_ssd1326.cyclo ./u8g2/u8x8_d_ssd1326.d ./u8g2/u8x8_d_ssd1326.o ./u8g2/u8x8_d_ssd1326.su ./u8g2/u8x8_d_ssd1327.cyclo ./u8g2/u8x8_d_ssd1327.d ./u8g2/u8x8_d_ssd1327.o ./u8g2/u8x8_d_ssd1327.su ./u8g2/u8x8_d_ssd1329.cyclo ./u8g2/u8x8_d_ssd1329.d ./u8g2/u8x8_d_ssd1329.o ./u8g2/u8x8_d_ssd1329.su ./u8g2/u8x8_d_ssd1362.cyclo ./u8g2/u8x8_d_ssd1362.d ./u8g2/u8x8_d_ssd1362.o ./u8g2/u8x8_d_ssd1362.su ./u8g2/u8x8_d_ssd1606_172x72.cyclo ./u8g2/u8x8_d_ssd1606_172x72.d ./u8g2/u8x8_d_ssd1606_172x72.o ./u8g2/u8x8_d_ssd1606_172x72.su ./u8g2/u8x8_d_ssd1607_200x200.cyclo ./u8g2/u8x8_d_ssd1607_200x200.d ./u8g2/u8x8_d_ssd1607_200x200.o ./u8g2/u8x8_d_ssd1607_200x200.su ./u8g2/u8x8_d_st7511.cyclo ./u8g2/u8x8_d_st7511.d ./u8g2/u8x8_d_st7511.o ./u8g2/u8x8_d_st7511.su ./u8g2/u8x8_d_st75160.cyclo ./u8g2/u8x8_d_st75160.d ./u8g2/u8x8_d_st75160.o ./u8g2/u8x8_d_st75160.su ./u8g2/u8x8_d_st75256.cyclo ./u8g2/u8x8_d_st75256.d ./u8g2/u8x8_d_st75256.o ./u8g2/u8x8_d_st75256.su ./u8g2/u8x8_d_st7528.cyclo ./u8g2/u8x8_d_st7528.d ./u8g2/u8x8_d_st7528.o ./u8g2/u8x8_d_st7528.su ./u8g2/u8x8_d_st75320.cyclo ./u8g2/u8x8_d_st75320.d ./u8g2/u8x8_d_st75320.o ./u8g2/u8x8_d_st75320.su ./u8g2/u8x8_d_st7565.cyclo ./u8g2/u8x8_d_st7565.d ./u8g2/u8x8_d_st7565.o ./u8g2/u8x8_d_st7565.su ./u8g2/u8x8_d_st7567.cyclo ./u8g2/u8x8_d_st7567.d ./u8g2/u8x8_d_st7567.o ./u8g2/u8x8_d_st7567.su ./u8g2/u8x8_d_st7571.cyclo ./u8g2/u8x8_d_st7571.d ./u8g2/u8x8_d_st7571.o ./u8g2/u8x8_d_st7571.su ./u8g2/u8x8_d_st7586s_erc240160.cyclo ./u8g2/u8x8_d_st7586s_erc240160.d ./u8g2/u8x8_d_st7586s_erc240160.o ./u8g2/u8x8_d_st7586s_erc240160.su ./u8g2/u8x8_d_st7586s_jlx384160.cyclo ./u8g2/u8x8_d_st7586s_jlx384160.d ./u8g2/u8x8_d_st7586s_jlx384160.o ./u8g2/u8x8_d_st7586s_jlx384160.su ./u8g2/u8x8_d_st7586s_s028hn118a.cyclo ./u8g2/u8x8_d_st7586s_s028hn118a.d ./u8g2/u8x8_d_st7586s_s028hn118a.o ./u8g2/u8x8_d_st7586s_s028hn118a.su ./u8g2/u8x8_d_st7586s_ymc240160.cyclo ./u8g2/u8x8_d_st7586s_ymc240160.d ./u8g2/u8x8_d_st7586s_ymc240160.o ./u8g2/u8x8_d_st7586s_ymc240160.su ./u8g2/u8x8_d_st7588.cyclo ./u8g2/u8x8_d_st7588.d ./u8g2/u8x8_d_st7588.o ./u8g2/u8x8_d_st7588.su ./u8g2/u8x8_d_st7920.cyclo ./u8g2/u8x8_d_st7920.d ./u8g2/u8x8_d_st7920.o ./u8g2/u8x8_d_st7920.su ./u8g2/u8x8_d_stdio.cyclo ./u8g2/u8x8_d_stdio.d ./u8g2/u8x8_d_stdio.o ./u8g2/u8x8_d_stdio.su ./u8g2/u8x8_d_t6963.cyclo ./u8g2/u8x8_d_t6963.d ./u8g2/u8x8_d_t6963.o ./u8g2/u8x8_d_t6963.su ./u8g2/u8x8_d_uc1601.cyclo ./u8g2/u8x8_d_uc1601.d ./u8g2/u8x8_d_uc1601.o ./u8g2/u8x8_d_uc1601.su ./u8g2/u8x8_d_uc1604.cyclo ./u8g2/u8x8_d_uc1604.d ./u8g2/u8x8_d_uc1604.o ./u8g2/u8x8_d_uc1604.su ./u8g2/u8x8_d_uc1608.cyclo ./u8g2/u8x8_d_uc1608.d ./u8g2/u8x8_d_uc1608.o ./u8g2/u8x8_d_uc1608.su ./u8g2/u8x8_d_uc1609.cyclo ./u8g2/u8x8_d_uc1609.d ./u8g2/u8x8_d_uc1609.o ./u8g2/u8x8_d_uc1609.su ./u8g2/u8x8_d_uc1610.cyclo ./u8g2/u8x8_d_uc1610.d ./u8g2/u8x8_d_uc1610.o ./u8g2/u8x8_d_uc1610.su ./u8g2/u8x8_d_uc1611.cyclo ./u8g2/u8x8_d_uc1611.d ./u8g2/u8x8_d_uc1611.o ./u8g2/u8x8_d_uc1611.su ./u8g2/u8x8_d_uc1617.cyclo ./u8g2/u8x8_d_uc1617.d ./u8g2/u8x8_d_uc1617.o ./u8g2/u8x8_d_uc1617.su ./u8g2/u8x8_d_uc1638.cyclo ./u8g2/u8x8_d_uc1638.d ./u8g2/u8x8_d_uc1638.o ./u8g2/u8x8_d_uc1638.su ./u8g2/u8x8_d_uc1701_dogs102.cyclo ./u8g2/u8x8_d_uc1701_dogs102.d ./u8g2/u8x8_d_uc1701_dogs102.o ./u8g2/u8x8_d_uc1701_dogs102.su ./u8g2/u8x8_d_uc1701_mini12864.cyclo ./u8g2/u8x8_d_uc1701_mini12864.d ./u8g2/u8x8_d_uc1701_mini12864.o ./u8g2/u8x8_d_uc1701_mini12864.su ./u8g2/u8x8_debounce.cyclo ./u8g2/u8x8_debounce.d ./u8g2/u8x8_debounce.o ./u8g2/u8x8_debounce.su ./u8g2/u8x8_display.cyclo ./u8g2/u8x8_display.d ./u8g2/u8x8_display.o ./u8g2/u8x8_display.su ./u8g2/u8x8_fonts.cyclo ./u8g2/u8x8_fonts.d ./u8g2/u8x8_fonts.o ./u8g2/u8x8_fonts.su ./u8g2/u8x8_gpio.cyclo ./u8g2/u8x8_gpio.d ./u8g2/u8x8_gpio.o ./u8g2/u8x8_gpio.su ./u8g2/u8x8_input_value.cyclo ./u8g2/u8x8_input_value.d ./u8g2/u8x8_input_value.o ./u8g2/u8x8_input_value.su ./u8g2/u8x8_message.cyclo ./u8g2/u8x8_message.d ./u8g2/u8x8_message.o ./u8g2/u8x8_message.su ./u8g2/u8x8_selection_list.cyclo ./u8g2/u8x8_selection_list.d ./u8g2/u8x8_selection_list.o ./u8g2/u8x8_selection_list.su ./u8g2/u8x8_setup.cyclo ./u8g2/u8x8_setup.d ./u8g2/u8x8_setup.o ./u8g2/u8x8_setup.su ./u8g2/u8x8_string.cyclo ./u8g2/u8x8_string.d ./u8g2/u8x8_string.o ./u8g2/u8x8_string.su ./u8g2/u8x8_u16toa.cyclo ./u8g2/u8x8_u16toa.d ./u8g2/u8x8_u16toa.o ./u8g2/u8x8_u16toa.su ./u8g2/u8x8_u8toa.cyclo ./u8g2/u8x8_u8toa.d ./u8g2/u8x8_u8toa.o ./u8g2/u8x8_u8toa.su

.PHONY: clean-u8g2

