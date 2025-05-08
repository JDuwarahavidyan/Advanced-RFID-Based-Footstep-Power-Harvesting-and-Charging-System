/*
 * usar.h
 *
 * Created: 10/8/2024 3:12:16 PM
 *  Author: duwa2
 */ 


#ifndef USAR_H_
#define USAR_H_

#define F_CPU 16000000UL
#define BAUD 9600
#define BAUD_PRESCALE ((F_CPU / (BAUD * 16UL)) - 1)

void uart_init();
void uart_transmit(unsigned char data);
unsigned char uart_receive();

// Function to initialize UART communication
void uart_init() {
	// Set baud rate
	UBRR0H = (uint8_t)(BAUD_PRESCALE >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALE);
	// Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Function to receive a character via UART
unsigned char uart_receive() {
	// Wait for data to be received
	while (!(UCSR0A & (1 << RXC0)));
	// Get and return received data from buffer
	return UDR0;
}




#endif /* USAR_H_ */