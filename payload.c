#include "payload.h"

FRAME* make_frame(char* input){

	FRAME* f = malloc(sizeof(FRAME));
	byte masking_key[4] = {19, 35, 71, 31};
	f->fin = 1;
	f->opcode = 1;
	f->firstbyte = f->fin * 128 + f->opcode;

	f->mask = 1;

	f->input_strlen = strlen(input);

	if (f->input_strlen <= 125){
		//printf("input strlen < 125, %d\n", f->input_strlen);
		f->secbyte = f->mask * 128 + f->input_strlen;
		//printf("first byte: %d sec byte: %d\n", f->firstbyte, f->secbyte);
		int byt = 6 + f->input_strlen;
		f->payload = calloc(byt, 1);
		f->payload[0] = f->firstbyte;
		f->payload[1] = f->secbyte;
		for (int i = 0; i < 4; i++){
			f->payload[2 + i] = masking_key[i];
		}
		for (int i = 0; i < f->input_strlen; i++){
			f->payload[6 + i] = input[i] ^ masking_key[i % 4];
		}
		f->bytes_to_send = 6 + f->input_strlen;
	} else if (f->input_strlen <= 65535){
		//printf("input strlen < 125, %d\n", f->input_strlen);
		f->secbyte = f->mask * 128 + 126;
		int byt = 8 + f->input_strlen;
		f->payload = calloc(byt, 1);
		f->payload[0] = f->firstbyte;
		f->payload[1] = f->secbyte;
		f->payload[2] = f->input_strlen / 256;
		f->payload[3] = f->input_strlen % 256;
		//printf("fbyte: %d, sbyte: %d tbyte: %d fbyte: %d\n", f->payload[0], f->payload[1], f->payload[2], f->payload[3]);
		for (int i = 0; i < 4; i++){
			f->payload[4 + i] = masking_key[i];
		}

		for (int i = 0; i < f->input_strlen; i++){
			f->payload[8 + i] = input[i] ^ masking_key[i % 4];
		}
		f->bytes_to_send = 8 + f->input_strlen;
		//printf("\nbytes to send :%d\n", f->bytes_to_send);
	}
	
	return f;

}

char* parse_frame(char* input, int bytes){


	int fin = 128;
	int opcode = input[0] - 128;
	int len = input[1];
	char* payload;
	if (len <= 125){

		payload = calloc(len + 1, 1);
		for (int i = 0; i < len; i++){
			payload[i] = input[i + 2];
		}
		payload[len] = 0;
	} 
	else if (len == 126) {
		
		int payload_len = (byte) input[2] * 256 + (byte) input[3];
		
		payload = calloc(payload_len + 1, 1);
		for (int i = 0; i < payload_len; i++){
			payload[i] = input[i + 4];
		}
		payload[payload_len] = 0;
	}

	return payload;

}