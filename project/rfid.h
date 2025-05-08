/*
 * rfid.h
 *
 * Created: 10/8/2024 11:47:54 AM
 *  Author: duwa2
 */ 


#ifndef RFID_H_
#define RFID_H_

#include "usart.h"

#ifndef bit_is_clear
#define bit_is_clear(sfr, bit) (!(sfr & (1 << bit)))
#endif

// RDM6300 frame constants
#define RFID_FRAME_SIZE 14
#define START_BYTE 0x02
#define END_BYTE 0x03

// Function to read a valid 14-byte frame from RDM6300
int read_rdm6300_frame(char *rfid_tag) {
	char rfid_frame[RFID_FRAME_SIZE];
	uint8_t received_byte;
	int i = 0;

	// Wait for start byte (0x02)
	while ((received_byte = uart_receive()) != START_BYTE);

	// Read the next 12 bytes (10 UID ASCII + 2 checksum)
	for (i = 0; i < RFID_FRAME_SIZE - 2; i++) {
		rfid_frame[i] = uart_receive();
	}

	// Verify the end byte (0x03)
	if (uart_receive() != END_BYTE) {
		return 0; // Invalid frame
	}

	// Extract the 10 ASCII bytes representing the UID
	for (i = 0; i < 10; i++) {
		rfid_tag[i] = rfid_frame[i];
	}

	return 1; // Valid frame
}





#endif /* RFID_H_ */