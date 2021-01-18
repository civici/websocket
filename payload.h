#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define byte 		uint8_t
#define twobyte 	uint16_t
#define fourbyte 	uint64_t


typedef struct FRAME{


	byte firstbyte;
	byte secbyte;

	int input_strlen;
	int bytes_to_send;
	byte* payload;
	byte fin;
	byte opcode;
	byte mask;
	int payload_data_len;
	int payload_index;
	int payload_len_bytes;
}FRAME;

FRAME* make_frame(char* input);

char* parse_frame(char* input, int bytes);