#include <util/delay.h>
#include "spi.h"
#include "thermo.h"

char data[4];

void init_max() {
  read_max();
}

void read_max() {
  int i = 3;

  SPI_PORT &= ~(1<<SPI_SS_BIT);
  for(i = 3; i >= 0; i--) {
    data[i] = spi_read();
    }
  SPI_PORT |= (1<<SPI_SS_BIT);
}

short read_ext_temp() {
  char aux;
  short temp;

  aux = data[2] >> 2;
  temp = data[3];
  temp <<= 6;
  temp += aux;

  return temp /= 4;
}

short read_int_temp() {
  char aux;
  short temp;
  
  temp = data[1];
  temp<<=4;
  aux=data[0]>>4;
  temp=data[1]<<4;
  temp+=aux;

  return temp/=16;
}

short to_degf(short temp) {
  short t = 0;

  t = ((temp*90)/50)+32;

  return t;
}
