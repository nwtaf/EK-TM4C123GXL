#ifndef LCD_Driver
#define LCD_Driver

#define EN GPIO_PIN_0 /*from GPIO.h*/
#define RS GPIO_PIN_1
#define D4 GPIO_PIN_4
#define D5 GPIO_PIN_5
#define D6 GPIO_PIN_6
#define D7 GPIO_PIN_7

/*define useful symbolic names for LCD instructions/commands
  from table 6 of datasheet */
#define FunctionSet4Bit     0x20 //Must be first command
#define ClearDisplay        0x01 //sets DDRAM address 0 in AC. Returns display from shifted to original position. Takes 1.52ms
#define ReturnHome          0x02 //see table 6 for description, dont forget extra long execution time (add delay)
#define DisplayOn           0x0C
#define MoveCursorStartRow2 0xC0
#define MoveCursorStartRow1 0x80 //Check this, but it should work
/*#define moveCursorRight     0x06
#define moveCursorLeft      0x08
#define shiftDisplayRight   0x1C
#define shiftDisplayLeft    0x18
#define cursorBlink         0x0F
#define cursorOff           0x0C
#define cursorOn            0x0E
#define Function_set_8bit   0x38 //alternative first command */


void LCD_init(void);  /* LCD initialization function */
void pulseLCDEnable(void);
void sendChar(char c); //writes ASCII character
void sendInstruction(uint8_t instruction); //sends an instruction
void sendStr(char *str); //sends a string (array of chars that is null ('\0') terminated)
#endif /* LCD_Driver */
