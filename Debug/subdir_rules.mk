################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
at24c04.obj: ../at24c04.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="at24c04.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

delay.obj: ../delay.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="delay.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ds1307.obj: ../ds1307.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="ds1307.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

i2c_gpio.obj: ../i2c_gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="i2c_gpio.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

i2c_interface.obj: ../i2c_interface.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="i2c_interface.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

isrDefs.obj: ../isrDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="isrDefs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

myClocksWithCrystals.obj: ../myClocksWithCrystals.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="myClocksWithCrystals.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

myGpio.obj: ../myGpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="myGpio.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

myLcd.obj: ../myLcd.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="myLcd.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

myprintf.obj: ../myprintf.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="myprintf.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sys_log.obj: ../sys_log.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="sys_log.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

utils.obj: ../utils.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-msp430_20.8.0.STS/include" --include_path="C:/Users/mamat/workspace_v07/LCD_ASCII/driverlib/MSP430FR5xx_6xx" --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="utils.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


