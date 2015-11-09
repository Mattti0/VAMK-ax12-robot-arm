F_CPU=8000000
MCU=atmega128
C_FLAGS= -lm
BOARD=-DF_CPU=$(F_CPU) -mmcu=$(MCU) 
INCLUDES=-I./include -I./drivers
DRIVERS= ./drivers/AX12.c ./drivers/USART_driver.c ./drivers/HCSR04.c 
DRIVERS_OBJ= ./drivers/AX12.o ./drivers/USART_driver.o ./drivers/HCSR04.o 

hex:
	@echo 'Compiling drivers'
	avr-gcc -Os $(BOARD) $(INCLUDES) -c $(DRIVERS) $(C_FLAGS)
	mv *.o ./drivers
	@echo 'Compailing program'
	avr-gcc -Os $(BOARD) $(INCLUDES) -c main.c $(C_FLAGS)
	@echo 'Linking files'
	avr-gcc $(BOARD) -o atmel.elf $(DRIVERS_OBJ) main.o
	@echo 'Making hex'
	avr-objcopy -O ihex atmel.elf atmel.hex
	rm *.o $(DRIVERS_OBJ)
	