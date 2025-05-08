/*
 * uart.h
 *
 * Created: 8/9/2024 5:22:02 AM
 *  Author: duwa2
 */ 


#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lcd.h"
#include "uart.h"

#define ACCESS_GRANTED_TAG_ID 0x39123B

#define RED_LED PC0
#define GREEN_LED PC1
#define BLUE_LED PC2
#define YELLOW_LED PC3
#define BUZZER PC4
#define RELAY_PIN PC5

int main(void) {
    // Initialize LCD
    initLcdPorts();
    Lcd_init();

    DDRC |= 0xFF;

    // Turn off relay initially (ensure low output)
    PORTC |= (1 << RELAY_PIN);

    // Initialize UART with baud rate 9600
    UART_Init(103); // 9600 baud for 16 MHz clock

    // Display welcome message
    Lcd_CmdWrite(0x80);
    Lcd_displayMessage("Welcome to ESD");
    Lcd_CmdWrite(0xC0);
    Lcd_displayMessage("Group 7");
    _delay_ms(2000);
    Lcd_clear();

    // Display instruction to place access card
    Lcd_CmdWrite(0x80);
    Lcd_displayMessage("Place your access");
    Lcd_CmdWrite(0xC0);
    Lcd_displayMessage("card");
    _delay_ms(1000);

    while (1) {
        if (UCSR0A & (1 << RXC0)) {
            bool call_extract_tag = false;
            int ssvalue = UART_Receive();

            if (ssvalue == 2) {
                buffer_index = 0;
            } else if (ssvalue == 3) {
                call_extract_tag = true;
            }

            if (buffer_index >= BUFFER_SIZE) {
                buffer_index = 0;
                continue;
            }

            buffer[buffer_index++] = ssvalue;

            if (call_extract_tag && buffer_index == BUFFER_SIZE) {
                unsigned long tag_id = extract_tag();

                Lcd_clear();
                Lcd_CmdWrite(0x80);
                if (tag_id == ACCESS_GRANTED_TAG_ID) {
                    Lcd_displayMessage("Access Granted");
                    _delay_ms(1000);
                    PORTC |= (1<<GREEN_LED) | (1 << BUZZER);
                    _delay_ms(1000);
                    PORTC &= ~(1<<GREEN_LED);
                    PORTC &= ~(1 << BUZZER); // Fixed BUZZER turn-off logic
                    Lcd_clear();
                    Lcd_CmdWrite(0x80);
                    Lcd_displayMessage("Welcome Vidyan");
                    Lcd_CmdWrite(0xC0);
                    Lcd_displayMessage("Initiating...");

                    // Activate relay for charging
                    PORTC &= ~(1 << RELAY_PIN);

                    _delay_ms(1000);
                    Lcd_clear();
                    Lcd_CmdWrite(0x80);
                    Lcd_displayMessage("Charging...");
                    PORTC |= (1<<YELLOW_LED);

                    // Countdown from 50 seconds
                    for (int i = 50; i > 0; i--) {
                        char countdown_msg[16];
                        sprintf(countdown_msg, "You have %ds", i);

                        // Update the display with remaining time
                        Lcd_CmdWrite(0xC0);
                        Lcd_displayMessage(countdown_msg);

                        _delay_ms(1000);  // 1 second delay for countdown
                    }

                    // Turn off yellow LED after charging is done
                    PORTC &= ~(1 << YELLOW_LED);

                    // Turn off relay after charging is done
                    PORTC |= (1 << RELAY_PIN);

                    Lcd_clear();
                    Lcd_CmdWrite(0x80);
                    Lcd_displayMessage("Disconnecting...");
                    _delay_ms(2000);
                } else {
                    Lcd_displayMessage("Access Denied");
                    _delay_ms(1000);
                    PORTC |= (1<<RED_LED) | (1 << BUZZER);
                    _delay_ms(500);
                    PORTC &= ~(1<<RED_LED);
                    PORTC &= ~(1 << BUZZER);  // Fixed BUZZER turn-off logic
                    _delay_ms(500);
                    PORTC |= (1<<RED_LED) | (1 << BUZZER);
                    _delay_ms(500);
                    PORTC &= ~(1<<RED_LED);
                    PORTC &= ~(1 << BUZZER);  // Fixed BUZZER turn-off logic
                }

                _delay_ms(2000);

                // Reset display to show instruction
                Lcd_clear();
                Lcd_CmdWrite(0x80);
                Lcd_displayMessage("Place your access");
                Lcd_CmdWrite(0xC0);
                Lcd_displayMessage("card");

                buffer_index = 0;
            }
        }
    }
}
