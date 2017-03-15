#ifndef SPI_H
#define SPI_H
/**************************************************************************
  Title   :  C header file for SPI implementation on an AVR microcontroller
  Author  :  Tom Steckmeyer
  File    :
  Software:  AVR-GCC 4.x
  Hardware:  Developed using an atmega32u4 but may be used with many other
             AVR microcontrollers.
***************************************************************************/

/**
 * @author Tom Steckmeyer
 * @copyright (C) 2017 Tom Steckmeyer, GNU General Public License Version 3
 *
 * @file
 * @defgroup tstec_spi SPI Library <spi.h>
 * @code #include <spi.h> @endcode
 *
 * @brief Basic routines for SPI communication on an AVR
 *
 * @author Tom Steckmeyer
 *
 * @version 1.0
 *
 * @copyright (C) 2017 Tom Steckmeyer, GNU General Public License Version 3
 */

#include <avr/io.h>

/**
 * @name Definition for SPI port
 * Default is PORTB however it may need to be changed depending on the MCU being used
 */
#define SPI_PORT      PORTB
#define SPI_DDR       DDRB
#define SPI_MISO_BIT  3
#define SPI_MOSI_BIT  2
#define SPI_SCK_BIT   1
#define SPI_SS_BIT    0

/**
 * @name Functions
 */

/**
 * @brief Initialize device as master
 * @param none
 * @return none
 */
void spi_init_master(void);

/**
 * @brief Initialize device as slave
 * @param none
 * @return none
 */
void spi_init_slave(void);

/**
 * @brief Read data from slave device
 * @param data to trigger read from slave
 * @return data from slave device
 */
unsigned char spi_read(void);

void spi_write(unsigned char);

#endif
