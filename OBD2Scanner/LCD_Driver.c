/*TivaC LaunchPad Pin	HD44780U LCD Pin
TivaC LCD  LCD Abbrev.
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
      Pin16 Backlight GND
*/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/tm4c123gh6pm.h"/* include register defintion file of TM4C123GH6PM */
#include "driverlib/LCD_Driver.h"

/* prototypes of LCD functions */ 
void LCD_init(void);  /* LCD initialization function */
void pulseLCDEnable(void);
void sendChar(char c); //writes ASCII character
void sendInstruction(uint8_t instruction); //sends an instruction
void sendStr(char *str); //sends a string (array of chars that is null ('\0') terminated)

/* Default LCD and GPIOB initialization Function (10 ms before able to submit instructions)
 On reset, the LCD will:
 1. Display Clear
 2. Function Set (8 bit interface data, 1 line display, 0x5 character font)
 3. Display on/off control (display off, cursor off, blinking off)
 4. Entry mode set (incremented by 1, no shift)*/ 

void LCD_init(void){
	char str1[] = "Hello, World!";
	char *HW = str1;
	
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
	sendInstruction(0x01); //clear display
	sendInstruction(0x02); //return home
	SysCtlDelay(20373333); //>1.52ms for extra long execution time of return home instruction
	sendInstruction(0x0C); //display on/off control 
	GPIOPinWrite(GPIO_PORTB_BASE, RS, RS); //RS high for data writes
	SysCtlDelay(1); //>40ns for address set-up time (RS)
	UARTprintf("LCD initialization successful... \n");
	sendStr(HW);//pointer will work
	//sendStr(str1);//idk if this will work
	/*sendChar('H');
	sendChar('E');
	sendChar('L');
	sendChar('L');
	sendChar('0');*/
}
void pulseLCDEnable() {
	GPIOPinWrite(GPIO_PORTB_BASE, EN, EN); //enable high
	SysCtlDelay(8); //pulse width > 450ns
	GPIOPinWrite(GPIO_PORTB_BASE, EN, 0x00); //enable low
	SysCtlDelay(1500); //wait for > 37us between commands 1480 is more correct
}

void sendChar(char c) {
	//make sure RS is high before calling this function
	GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, c & 0xF0); //upper nibble
	pulseLCDEnable();
	GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, (c << 4) & 0xF0); //lower nibble
	pulseLCDEnable();
	UARTprintf("Sent char %c: \n",c);
}

void sendInstruction(uint8_t instruction){
	GPIOPinWrite(GPIO_PORTB_BASE, RS, 0x00); //RS low for instruction writes
	SysCtlDelay(1); //>40ns for address set-up time (RS)
	GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, instruction & 0xF0); //upper nibble
	pulseLCDEnable();
	GPIOPinWrite(GPIO_PORTB_BASE, D7| D6 | D5 | D4, (instruction << 4) & 0xF0); //lower nibble
	pulseLCDEnable();
	UARTprintf("Sent instruction %u: \n",instruction);
	GPIOPinWrite(GPIO_PORTB_BASE, RS, RS); //RS high for data writes
	SysCtlDelay(1);
}

void sendStr(char *str){
	for (int i = 0; i < strlen(str); i++) {
        	sendChar(str[i]);
	}
}
