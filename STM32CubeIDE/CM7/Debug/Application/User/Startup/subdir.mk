################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/User/Startup/startup_stm32h747xihx.s 

S_DEPS += \
./Application/User/Startup/startup_stm32h747xihx.d 

OBJS += \
./Application/User/Startup/startup_stm32h747xihx.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Startup/%.o: ../Application/User/Startup/%.s Application/User/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"D:/touchgfx_projects/pinpad/pinpad/STM32CubeIDE/CM7/Application/User/gui" -I"D:/touchgfx_projects/pinpad/pinpad/STM32CubeIDE/CM7/chacha" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Application-2f-User-2f-Startup

clean-Application-2f-User-2f-Startup:
	-$(RM) ./Application/User/Startup/startup_stm32h747xihx.d ./Application/User/Startup/startup_stm32h747xihx.o

.PHONY: clean-Application-2f-User-2f-Startup

