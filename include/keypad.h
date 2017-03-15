#ifndef KEYPAD_H
#define KEYPAD_H
/*******************************************************************
  Title   :  C header file for a 4x4 membrane keypad
  Author  :  Tom Steckmeyer
  File    :
  Software:  AVR-GCC 4.x
  Hardware:  Developed using an atmega32u4 but may be used with many
             other AVR microcontrollers.
********************************************************************/

/**
 * @mainpage
 * Collection of libraries for AVR-GCC
 * @author Tom Steckmeyer
 * @copyright (C) 2017 Tom Steckmeyer, GNU General Public License Version 3
 *
 * @file
 * @defgroup tstec_keypad Keypad Library <keypad.h>
 * @code #include <keypad.h> @endcode
 *
 * @brief Basic routines to retrive the value of a key pressed on a 4x4 membrane keypad
 *
 * @author Tom Steckmeyer
 *
 * @version 1.0
 *
 * @copyright (C) 2017 Tom Steckmeyer, GNU General Public License Version 3
 */

#include <avr/io.h>
#include <util/delay.h>

/**
 * @name Definition for keypad port
 * Default is PORTD however it may need to be changed depending on the MCU being used.
 */
#define KEYPAD_DDR  DDRD
#define KEYPAD_PORT PORTD
#define KEYPAD_PIN  PIND

/**
 * @name Functions
 */

/**
 * @brief Initalize the keypad by setting the high end of DDR to output and the low end to input.
 * (rows = output; columns = input)
 * @param none
 * @return none
 */
void keypad_init(void);

/**
 * @brief Decode the binary value of the pressed key by reading the value of the column
 * pin followed by the value of the row pin.
 * @param none
 * @return hex value of the selected key
 */
unsigned char decode_key(void);

/**
 * @brief Decode the value of the pressed key
 * @param none
 * @return face value of selected key
 */
unsigned char get_key(void);

#endif /* KEYPAD_H */
