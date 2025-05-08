/*
 * lcd.h
 *
 * Created: 10/8/2024 11:49:41 AM
 *  Author: duwa2
 */ 


#ifndef LCD_H_
#define LCD_H_


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LcdDataBus PORTA
#define LcdControlBus PORTA
#define LcdDataBusDirnReg DDRA

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

void initLcdPorts(void)
{
	LcdDataBusDirnReg |= 0xF0; // LCD Data pins to o/p (PD4-PD7)
	DDRA |= 0x07;              // LCD control pins (RS, RW, EN) as output
}

void Lcd_CmdWrite(char cmd)
{
	LcdDataBus = (cmd & 0xF0);            // Set upper 4 bits of the command
	LcdControlBus &= ~(1 << LCD_RS);       // Set RS pin to LOW
	LcdControlBus &= ~(1 << LCD_RW);       // Set RW pin to LOW
	LcdControlBus |= (1 << LCD_EN);        // Generate High-to-Low pulse
	_delay_ms(10);
	LcdControlBus &= ~(1 << LCD_EN);       // Clear EN pin

	_delay_ms(10);

	LcdDataBus = ((cmd << 4) & 0xF0);      // Set lower 4 bits of the command
	LcdControlBus &= ~(1 << LCD_RS);       // Set RS pin to LOW
	LcdControlBus &= ~(1 << LCD_RW);       // Set RW pin to LOW
	LcdControlBus |= (1 << LCD_EN);        // Generate High-to-Low pulse
	_delay_ms(10);
	LcdControlBus &= ~(1 << LCD_EN);       // Clear EN pin

	_delay_ms(10);
}

void Lcd_DataWrite(char dat)
{
	LcdDataBus = (dat & 0xF0);             // Set upper 4 bits of the data
	LcdControlBus |= (1 << LCD_RS);        // Set RS pin to HIGH
	LcdControlBus &= ~(1 << LCD_RW);       // Set RW pin to LOW
	LcdControlBus |= (1 << LCD_EN);        // Generate High-to-Low pulse
	_delay_ms(10);
	LcdControlBus &= ~(1 << LCD_EN);       // Clear EN pin

	_delay_ms(10);

	LcdDataBus = ((dat << 4) & 0xF0);      // Set lower 4 bits of the data
	LcdControlBus |= (1 << LCD_RS);        // Set RS pin to HIGH
	LcdControlBus &= ~(1 << LCD_RW);       // Set RW pin to LOW
	LcdControlBus |= (1 << LCD_EN);        // Generate High-to-Low pulse
	_delay_ms(10);
	LcdControlBus &= ~(1 << LCD_EN);       // Clear EN pin

	_delay_ms(10);
}

void Lcd_init(void)
{
	LcdControlBus &= ~(1 << LCD_RW);  // Ensure RW is LOW (write mode)
	_delay_ms(100);
	Lcd_CmdWrite(0x02);       // Initialize in 4-bit mode
	_delay_ms(5);
	Lcd_CmdWrite(0x28);       // 4-bit, 2-line, 5x7 format
	_delay_ms(5);
	Lcd_CmdWrite(0x0C);       // Display ON, Cursor OFF
	_delay_ms(5);
	Lcd_CmdWrite(0x06);       // Increment cursor to right
	_delay_ms(5);
	Lcd_CmdWrite(0x01);       // Clear display
	_delay_ms(5);
}

void Lcd_clear(void)
{
	Lcd_CmdWrite(0x01);       // Clear the LCD display
	_delay_ms(10);
}

void Lcd_displayMessage(const char* message)
{
	while (*message)
	{
		Lcd_DataWrite(*message);  // Write each character to the LCD
		message++;
	}
}

void Lcd_shiftLeft(void)
{
	Lcd_CmdWrite(0x18);       // Shift display to the left
	_delay_ms(300);
}

void Lcd_shiftRight(void)
{
	Lcd_CmdWrite(0x1C);       // Shift display to the right
	_delay_ms(300);
}




#endif /* LCD_H_ */