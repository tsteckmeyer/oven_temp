#include "spi.h"

/*
 * Initialize a device as the master in SPI
 * Parameters: none
 * Return:     none
 */
void spi_init_master() {
  /* Set MOSI, SCK, and SS as output, all others input */
  SPI_DDR = (1<<SPI_MOSI_BIT) | (1<<SPI_SCK_BIT) | (1<<SPI_SS_BIT);

  /* Enable SPI, Master, and set clock rate.  This must match the
     slave device. */
  SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPHA) | (1<<SPR1) | (1<<SPR0);
  }

/*
 * Initialize a device as a slave in SPI
 * Parameters: none
 * Return:     none
 */
void spi_init_slave() {
  /* Set MISO as output, all others input */
  SPI_DDR = (1<<SPI_MISO_BIT);

  /* Enable SPI */
  SPCR = (1<<SPE);
  }

/*
 * Transmit data from the slave to the master.
 * Parameters: none
 * Return:     One byte of data from SPDR register as a char
 */
unsigned char spi_read() {
  unsigned char data = 0; /* Data must be loaded on the SPDR register to begin transmission */

  SPDR = data;                 /* Load tmp data to the SPDR to initialize transmission */
  while(!(SPSR & (1<<SPIF)));  /* Transmit data */
  data = SPDR;                 /* Assign data to data variable */

  return data;
  }

/*
 * Write data from master to slave
 * Parameters: Data to be written
 * Return:     none
 */
void spi_write(unsigned char data) {
  SPDR = data;                 /* Load data to be transmitted to the SPDR which starts transmission */
  while(!(SPSR & (1<<SPIF)));  /* Transfer data */
  }
