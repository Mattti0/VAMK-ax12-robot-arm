MCU					= attiny85
XTAL	      = 8000000
#PROGRAMMER 	= stk500v1
#PORT	   		= /dev/tty.usbmodem1421
#BAUD       	= 19200
#TARGET   	= MODBUS
COMPILE    	= avr-gcc -Wall -Os -DF_CPU=$(XTAL) -mmcu=$(MCU)
MODBUSPORT	= demo.c mbcrc.c portevent.c portserial.c porttimer.c
DIR					= ./modbus/
FREEMB			= $(DIR)mbfunccoils.c mbfuncdiag.c mbfuncdisc.c


all: usb clean build upload

usb:
	ls /dev/cu.*


	
#build:
#	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
#	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o
#	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex
#	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

#upload:
#	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(FILENAME).hex:i 

clean:
	rm main.o
	rm main.elf
	rm main.hex