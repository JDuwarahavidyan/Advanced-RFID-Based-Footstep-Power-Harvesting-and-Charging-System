/*
 * uart.h
 *
 * Created: 8/9/2024 5:22:02 AM
 *  Author: duwa2
 */ 


#ifndef UART_H_
#define UART_H_

#define BUFFER_SIZE 14
#define DATA_SIZE 10
#define DATA_TAG_SIZE 8


volatile uint8_t buffer[BUFFER_SIZE];
volatile int buffer_index = 0;

void UART_Init(unsigned int ubrr);
unsigned char UART_Receive(void);
unsigned long extract_tag(void);
unsigned long hexstr_to_value(char *str, unsigned int length);

void UART_Init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

unsigned char UART_Receive(void) {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

unsigned long extract_tag(void) {
	uint8_t *msg_data_tag = buffer + 3;
	return hexstr_to_value((char *)msg_data_tag, DATA_TAG_SIZE);
}

unsigned long hexstr_to_value(char *str, unsigned int length) {
	char copy[length + 1];
	for (int i = 0; i < length; i++) {
		copy[i] = str[i];
	}
	copy[length] = '\0';
	return strtoul(copy, NULL, 16);
}



#endif /* UART_H_ */