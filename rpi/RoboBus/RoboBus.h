#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>
#include <sys/socket.h>


//RTU values
#define RTU_DEVICE "/dev/ttyUSB0"
#define RTU_BAUDRATE 9600
#define RTU_PARITY N
#define RTU_BITS 8
#define RTU_STOP_BITS 1

void RoboBus_Init(modbus_t *ctx);


