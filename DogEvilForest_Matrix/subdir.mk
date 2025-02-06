################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Board.cpp \
../Dog.cpp \
../mainGame.cpp 

CPP_DEPS += \
./Board.d \
./Dog.d \
./mainGame.d 

OBJS += \
./Board.o \
./Dog.o \
./mainGame.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./Board.d ./Board.o ./Dog.d ./Dog.o ./mainGame.d ./mainGame.o

.PHONY: clean--2e-

