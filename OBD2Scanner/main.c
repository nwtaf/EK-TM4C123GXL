#define PART_TM4C1233H6PM 1
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/tm4c123gh6pm.h"
#include "driverlib/LCD_Driver.h"

uint32_t clkscalevalue = 6;

void InitUARTConsole(void);
void LED_Init(void);
void LED_Write(uint32_t);

int main(void)
{
	//Delay_cycles = (Delay_time * SysClock_frequency)/3, adjust for units; SysCtlDelay(unit) = 3 delay cycles per unit
  SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ); //SysCtlClockSet to 40MHz, one cycle = 25ns. 
	InitUARTConsole();
	UARTprintf("*****************************************************\n");
	UARTprintf("systemclock frequency is: %d Hz\n", SysCtlClockGet());
	LCD_init();
	while(1){
	}
}

void InitUARTConsole(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // Enable GPIO port A which is used for UART0 pins
    GPIOPinConfigure(GPIO_PA0_U0RX); // Configure the pin muxing for UART0 functions on port A0
    GPIOPinConfigure(GPIO_PA1_U0TX); // Configure the pin muxing for UART0 functions on port A1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); // Enable UART0 so that we can configure the clock
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC); // Use the internal 16MHz oscillator as the UART clock source
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1); // Select the alternate (UART) function for these pins
    UARTStdioConfig(0, 9600, 16000000); // Initialize the UART for console I/O. 9600 BAUD
		UARTprintf("Console Initialization Successfull...\n");
}
void LED_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x20;
	GPIO_PORTF_DEN_R  |= 0x0E;
	GPIO_PORTF_DIR_R  |= 0x0E;
	UARTprintf("LED initialization successful... \n");
}
}
