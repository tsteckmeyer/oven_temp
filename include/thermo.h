#ifndef THERMO_H
#define THERMO_H

/**
 * @author Tom Steckmeyer
 * @copyright (C) 2017 Tom Steckmeyer, GNU General Public License Version 3
 *
 * @file
 * @defgroup tstec_thermo Thermocouple Library <thermo.h>
 * @code #include <thermo.h> @endcode
 *
 * @brief Basic routines to communicate with a MAX31855 Thermocouple-to-Digital
 *        Converter
 *
 * @author Tom Steckmeyer
 *
 * @version 1.0
 *
 * @copyright (C) 2017 Tom Steckmeyer, GNU General Public License Version 3
 */

#include <avr/io.h>

/**
 * @name Functions
 */

/**
 * @brief Initialize the MAX31855
 * @param none
 * @return none
 */
void init_max();

/**
 * @brief Read the raw value of the MAX31855
 * @param none
 * @return none
 */
void read_max();

/**
 * @brief Read the reference junction temperature
 * @param none
 * @return Returns the reference temperature data D[15:4]
 */
short read_ext_temp();

/**
 * @brief Read the thermocouple temperature data
 * @param none
 * @return Returns the thermocouple temperature data D[31:18]
 */
short read_int_temp();

/**
 * @brief Converts temperature data to Fahrenheit
 * @param Temperature to be converted
 * @return Converted temperature
 */
short to_degf(short);

#endif
