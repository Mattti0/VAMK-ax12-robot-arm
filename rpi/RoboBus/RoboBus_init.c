#include "RoboBus.h"

/********************************************************************************
*										*
*										*
********************************************************************************/

void RoboBus_Init(modbus_t *ctx) {

ctx = modbus_new_rtu(RTU_DEVICE, RTU_BAUDRATE, 'RTU_PARITY', RTU_BITS, RTU_STOP_BITS);
modbus_set_slave(ctx, SERVER_ID);
query = malloc(MODBUS_RTU_MAX_ADU_LENGTH);
header_length = modbus_get_header_length(ctx);



}
