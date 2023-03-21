/*TivaC LCD  LCD Abbrev.
      Pin1  GND
      Pin2  V+
      Pin3  Contrast
PB1   Pin4  RS
      Pin5  RW
PB0   Pin6  E  
      Pin7  D0
      Pin8  D1
      Pin9  D2
      Pin10 D3
PB4   Pin11 D4
PB5   Pin12 D5
PB6   Pin13 D6
PB7   Pin14 D7
      Pin15 Backlight V+
      Pin16 Backlight GND*/

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/tm4c123gh6pm.h"/* include register defintion file of TM4C123GH6PM */
#include "driverlib/LCD_Driver.h"
 
void LCD_init(void);  /* LCD initialization function */
void sendStrToLCD(char *str);	/* Send string to LCD function */
void pulseLCDEnable(void);
void sendNibbleToLCD(uint8_t nibble);
void sendDataToLCD(uint8_t value); / *writes ASCII character */
void sendCMDToLCD(uint8_t command); /*Used to send commands to LCD */

/* Defualt LCD and GPIOB initialization Function (10 ms before able to submit instructions)
 On LCD reset :
 1. Display Clear
 2. Function Set (8 bit interface data, 1 line display, 0x5 character font)
 3. Display on/off control (display off, cursor off, blinking off)
 4. Entry mode set (incremented by 1, no shift)*/ 

void LCD_init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //Enable the GPIOB peripheral, including enabling the clock to GPIOB. Function takes 5 clock cycles.
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB)) {} //Wait for the GPIOB module to be ready
    UARTprintf("GPIOB module Ready. \n");

    SysCtlDelay(400000); //delay for 10ms to let default LCD reset/power on sequence finish
    
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, D4 | D5 | D6 | D7 | RS | EN);
    GPIOPinWrite(GPIO_PORTB_BASE, D4 | D5 | D6 | D7 | RS | EN, 0x00); //RS low for instruction writes
    SysCtlDelay(1); //>40ns for address set-up time (RS)
    
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x20); //4 bit mode (this is the only 8 bit command, make sure D3..D0 are grounded)
    pulseLCDEnable();
		GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x20); //function set
    pulseLCDEnable();
			
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x00); //clear display first nibble
    pulseLCDEnable(); 
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x10); //clear display second nibble
    pulseLCDEnable();
			
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x00); //return home first nibble
    pulseLCDEnable();
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x20); //return home second nibble
    pulseLCDEnable();
    SysCtlDelay(20373333); //>1.52ms for extra long execution time of return home instruction
		           
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x00); //display on/off control first nibble
    pulseLCDEnable();
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0xC0); //display on/off control second nibble
    pulseLCDEnable();
    
    GPIOPinWrite(GPIO_PORTB_BASE, RS, RS); //RS high for data writes
    SysCtlDelay(1); //>40ns for address set-up time (RS)
    
    UARTprintf("LCD initialization successful... \n");
    
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x40); //'H'
    pulseLCDEnable();
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x80);
    pulseLCDEnable();
		
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x40); //'I'
    pulseLCDEnable();
    GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, 0x90); //
    pulseLCDEnable();
}

void pulseLCDEnable() {
	GPIOPinWrite(GPIO_PORTB_BASE, EN, EN); //enable high
	SysCtlDelay(8); //pulse width > 450ns
	GPIOPinWrite(GPIO_PORTB_BASE, EN, 0x00); //enable low
	SysCtlDelay(1500); //wait for > 37us between commands 1480 is more correct
}

void sendCMDToLCD(uint8_t command){ //check this
	GPIOPinWrite(GPIO_PORTB_BASE, RS, LOW); // Set the LCD RS signal to low to indicate command mode
	sendDataToLCD(command);
    if (command < 4) SysCtlDelay(80000); // 2ms delay for commands 1 and 2
    else SysCtlDelay(1600); //40us delay for other commands */
	GPIOPinWrite(GPIO_PORTB_BASE, RS, HIGH); // Set the LCD RS signal to high to indicate data mode
}

void sendDataToLCD(uint8_t value) {
    sendNibbleToLCD((value >> 4) & 0x0F);// Send the high nibble of the character
    sendNibbleToLCD(value & 0x0F); // Send the low nibble of the character
	UARTprintf("Sent value %u: \n",(unsigned short)value);
}
