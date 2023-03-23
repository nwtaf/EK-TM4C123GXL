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
#define Function_Set_4bit 0x28 //001010-- //handles font size and lines of LCD (cannot display two lines for 5x10 char font)
#define Display_On        0x0F //00001111 //display on, cursor on, blinking cursor
#define Entry_Mode_Set    0x06 //00000110 //increment by 1, no shift
#define Clear_Display     0x01 //clear display and sets DDRAM address 0 in Address Counter (AC)
#define Return_Home       0x02 //00000001- //sets DDRAM address 0 in AC. Returns display from shifted to original position. Takes 1.52ms

/*unchecked from online sources. Use table 6 of datasheet to check
#define moveCursorRight   0x06
#define moveCursorLeft    0x08
#define shiftDisplayRight 0x1C
#define shiftDisplayLeft  0x18
#define cursorBlink       0x0F
#define cursorOff         0x0C
#define cursorOn          0x0E
#define Function_set_8bit 0x38 //001110-- //ew
#define FirstRow          0x80*/

void LCD_init(void);  /* LCD initialization function */
void pulseLCDEnable(void);
void sendChar(char c);
void sendInstruction(uint8_t instruction);
void sendStr(char *str);
#endif /* LCD_Driver */
