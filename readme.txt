This is SVN project for Embedded systems designing collabration of courses.
  including these courses:
    Fieldbus & internet (+Teemu Mahlamäki doing rpi side for modbus)
    Embedded systems design

Raspberry pi code is in rpi folder and avr (including modbus library) is in avr folder.

Used HW:
  4x AX12 servos
  STK500 with STK501 (atmega128)
  raspberry pi
  2x RS485 driver (unknown)
  Buffer chip (unknown) to communicate with 3-wire servo
  
SW structure
  +---trunk
      +---avr
      |   +---src
      |   |   +---include (own made drivers)
      |   |   |   +---err_t.h
      |   |   |   +---USARTdriver.h
      |   |   |   +---USARTdriver.c
      |   |   |   +---AX12.h
      |   |   |   \---AX12.c
      |   |   +---template.c
      |   |   \---main.c
      |   +---freemodbus
      +---rpi
      |   +---src
      \---readme.txt (this file)