################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board/transceiver/frame.cpp \
C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.cpp \
C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.cpp 

OBJS += \
./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/frame.o \
./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.o \
./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.o 

CPP_DEPS += \
./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/frame.d \
./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.d \
./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.d 


# Each subdirectory must supply rules for building sources it contributes
desenet-common/platform/nucleo-stm32l476rg/board/transceiver/frame.o: C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board/transceiver/frame.cpp desenet-common/platform/nucleo-stm32l476rg/board/transceiver/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DIDE_STM32CUBEIDE -DTC_STM32CUBEIDE -DUSE_DISPLAY -DDISPLAY_DRIVER_SSD1608 -c -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/.." -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/../src" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/platform/nucleo-stm32l476rg" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/mcu" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/platform-common" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/platform-common/board" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/mdw" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/mdw/desenet" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.o: C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.cpp desenet-common/platform/nucleo-stm32l476rg/board/transceiver/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DIDE_STM32CUBEIDE -DTC_STM32CUBEIDE -DUSE_DISPLAY -DDISPLAY_DRIVER_SSD1608 -c -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/.." -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/../src" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/platform/nucleo-stm32l476rg" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/mcu" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/platform-common" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/platform-common/board" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/mdw" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/mdw/desenet" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.o: C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.cpp desenet-common/platform/nucleo-stm32l476rg/board/transceiver/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DIDE_STM32CUBEIDE -DTC_STM32CUBEIDE -DUSE_DISPLAY -DDISPLAY_DRIVER_SSD1608 -c -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/.." -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/../src" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/ide-stm32cubeide/platform/nucleo-stm32l476rg" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/mcu" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/nucleo-stm32l476rg/board" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/platform-common" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform/platform-common/board" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/platform" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/mdw" -I"C:/Users/stues/Documents/DESEM/7_Project/DESEM_project/work/desenet-sensor/src/common/mdw/desenet" -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-desenet-2d-common-2f-platform-2f-nucleo-2d-stm32l476rg-2f-board-2f-transceiver

clean-desenet-2d-common-2f-platform-2f-nucleo-2d-stm32l476rg-2f-board-2f-transceiver:
	-$(RM) ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/frame.cyclo ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/frame.d ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/frame.o ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/frame.su ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.cyclo ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.d ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.o ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrfspi.su ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.cyclo ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.d ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.o ./desenet-common/platform/nucleo-stm32l476rg/board/transceiver/nrftransceiver.su

.PHONY: clean-desenet-2d-common-2f-platform-2f-nucleo-2d-stm32l476rg-2f-board-2f-transceiver

