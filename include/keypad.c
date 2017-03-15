/*
 * Title:     4x4 Membrane Keypad library
 * Author:    Tom Steckmeyer
 * File:
 * Software:  AVR-GCC
 * Target:    any AVR device, adjustments may need to be made to the fine keypad.h 
 *
 * DESCRIPTION
 *       Basic routines for adding a 4x4 membrane keyboard to an AVR based electronics
 *       projects.  This file was created and tested using an atmega32u4.  PORTx may
 *       need to be changed depending on the device used in the project.  The port definition
 *       is located in the keypad.h file.
 *
 * USAGE
 *       See the C include file keypad.h for a description of each function
 */
#include "keypad.h"
#include "lcd.h"

/*
 * Initializes the DDR and PORT registers.  The higher four bits of the register set to output
 * and the lower four bits are set to input.  Pull-up resistors are then set for the lower four
 * bits.
 * Parameters: none
 * Return:     none
 */
void keypad_init() {
  KEYPAD_DDR = 0xf0; /* set rows to output and columns to input */
  KEYPAD_PORT = 0x0f; /* turn on pull-up resistors for columns (input pins) */
}

/*
 * Decodes the register value of the pressed key
 * Parameters: none
 * Return:    hex value of the pressed key
 */
unsigned char decode_key() {
  unsigned char key = 'z';
  unsigned char column, c;
  unsigned char row, r;

  /* Loop through the columns until the column corresponding to the pressed button is found */
  for(c = 0; c < 0x04; c++) {
    _delay_ms(5);
    column = KEYPAD_PIN & 0x0f; /* get the column bit from PINx */

    if(column != 0x0f) {
      column ^= 0x0f; /* mask out all but the activated column */
      
      /* Loop through the rows until the row corresponding to the pressed button is found */
      for(r = 0; r < 0x04; r++) {
        KEYPAD_DDR ^= 0xff;  /* Switch the ouput pins to input */
        _delay_ms(5);
        KEYPAD_PORT ^= 0xff; /* Set the pull-up resistors for the new inputs */
        _delay_ms(5);
        
        row = KEYPAD_PIN & 0xf0; /* get the row bits from PINx */

        if(row != 0xf0) {
          row ^= 0xf0; /* mask out all but the activated row */
          
          key = row + column; /* add the column and row bits */
          break;
        }
      }
    }
  }
  
  KEYPAD_DDR ^= 0xff;   /* Reset the DDR register */
  KEYPAD_PORT ^= 0xff;  /* Reset the PORT register */

  return key;
}

/*
 * Decode the hex value of the pressed key
 * Parameters: none
 * Return:     face value of pressed key as unsigned char
 */
unsigned char get_key() {
  unsigned char key;
  
  _delay_ms(5);
  key = decode_key();  /* Get the hex value of the button that is pressed */

  /* Decode the hex value of the key and return a number, letter, or symbol */
  switch(key) {
    case 0x88: key='1'; break;
    case 0x84: key='2'; break;
    case 0x82: key='3'; break;
    case 0x81: key='A'; break;
    case 0x48: key='4'; break;
    case 0x44: key='5'; break;
    case 0x42: key='6'; break;
    case 0x41: key='B'; break;
    case 0x18: key='7'; break;
    case 0x14: key='8'; break;
    case 0x12: key='9'; break;
    case 0x11: key='C'; break;
    case 0x28: key='*'; break;
    case 0x24: key='0'; break;
    case 0x22: key='#'; break;
    case 0x21: key='D'; break;
    default: key='z';
  }

  return key;
}
