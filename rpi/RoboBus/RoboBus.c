#include "RoboBus.h"

int main (int argc, char *argv[]) {

	modbus_t *ctx;
	modbus_mapping_t *mb_mapping;
	int rc, i, header_length;

	RoboBus_Init(ctx);
	mb_mapping = modbus_mapping_new(
		UT_BITS_ADDRESS + UT_BITS_NB,
		UT_INPUT_BITS_ADDRESS + UT_INPUT_BITS_NB,
		UT_INPUT_REGISTERS_ADDRESS + UT_INPUT_REGISTERS_NB);

	if(mb_mapping == null) {

		fprintf(stderr, "Failed to allocate the mapping %s\n, modbus_strerror(errno));
		modbus_free(ctx);
		return -1;
	}

	if(mb_mapping->nb_bits != UT_BITS_ADDRESS + UT_BITS_NB) {

		printf("Invalid nb bits (%d != %d)\n", UT_BITS_ADDRESS + UT_BITS_NB, mb_mapping->nb_bits);
		modbus_free(ctx)
		return -1;
	}

	if(mb_mapping->nb_input_bits != UT_INPUT_BITS_ADDRESS , UT_INPUT_BITS_NB) {

		printf("Invalid nb input bits: %d\n", UT_INPUT_BITS_ADDRESS + UT_INPUT_BITS_NB);
		modbus_free(ctx)
		return -1;
	}

	if(mb_mapping->nb_registers != UT_REGISTERS_ADDRESS , UT_REGISTERS_NB) {

		printf("Invalid nb registers: %d\n", UT_REGISTERS_ADDRESS + UT_REGISTERS_NB);
		modbus_free(ctx)
		return -1;
	}

	if(mb_mapping->nb_input_registers != UT_INPUT_REGISTERS_ADDRESS , UT_INPUT_REGISTERS_NB) {

		printf("Invalid nb input registers: %d\n", UT_INPUT_REGISTERS_ADDRESS + UT_INPUT_REGISTERS_NB);
		modbus_free(ctx)
		return -1;
	}

	// Input status

	modbus_set_bits_from_bytes(mb_mapping->tab_input_bits,
				UT_INPUT_BITS_ADDRESS, UT_INPUT_BITS_NB,
				UT_INPUT_BITS_TAB);

	// Input Registers
	for(i=0; i < UT_INPUT_REGISTERS_NB; i++) {
		mb_mapping->tab_input_registers[UT_INPUT_REGISTERS_ADDRESS+i] =
			UT_INPUT_REGISTERS_TAB[i];

	}

	for(;;) {
		do {
			rc=modbus_receive(ctx, query);
		}while (rc==0);

		if (rc == -1 && errno != EMBBADCRC) {
¨		break;
		}

		if (query[header_length] == 0x03) {

			if(MODBUS_GET_INT16_FROM_INT8(query, header_length +3,
			== UT_REGISTERS_NB_SPECIAL) {
			printf("Set an incorrect number of values\n");
			MODBUS_SET_INT16_TO_INT8(query, header_length +3,
						UT_REGISTERS_NB_SPECIAL -1);
			}
			else if(MODBUS_GET_INT16_FROM_INT8(query, header_length +1)
				== UT_REGISTERS_ADDRESS_SPECIAL) {
			printf("Reply to this special register address by an exception\n");
			modbus_reply_exception(ctx, query,
						MODBUS_EXCEPTOPM_SLAVE_OR_SERVER_BUSY);
			continue;
			}
		}
	}


}
