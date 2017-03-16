#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <lcd.h>
#include <keypad.h>
#include <spi.h>
#include <thermo.h>

struct Flags {
  int temp_flag;
  int time_flag;
  int hour_flag;
  int mins_flag;
  };

char main_screen(void);
int set_temp(struct Flags *flags);
int set_hours(struct Flags *flags);
int set_minutes(struct Flags *flags);
void show_timer(int, int);

int main(void) {
  lcd_init(LCD_DISP_ON);
  spi_init_master();
  init_max();

  short ext_temp;
  short int_temp;
  char ext_str[15];
  char int_str[15];

  //int h = 60;
  //int m = 60;
  //int s = 60;

  int temp;
  int hours = 60;
  int minutes = 60;
  int seconds = 60;
  
  int size = (int)((ceil(log10(hours))+1)*sizeof(char));
  char t[size];
  char h[size];
  char m[size];
  char s[size];

  //sprintf(t, "%d", temp);
  sprintf(h, "%d", hours);
  sprintf(m, "%d", minutes);

  //lcd_gotoxy(0,1);
  //lcd_puts("Time:");
  //lcd_gotoxy(6,1);
  //lcd_puts(h);
  //lcd_puts(":");
  //lcd_puts(m);
  //lcd_puts(":");
  //lcd_puts("00");
  //cd_gotoxy(1,0);
  //for(hours = 1; hours > 0; hours--) {
  hours = 0;
  minutes = 1;
  while(hours >= 0 && minutes >= 0 && seconds > 0) {
    char tmp = 0;
    
    sprintf(h, "%d", hours);
    lcd_clrscr();
    if(hours < 10)
      lcd_puts("0");
    lcd_puts(h);
    lcd_puts(":");

    //minutes = 60;
    
    while(minutes > 0) {
      tmp = 0;

      minutes--;

      sprintf(m, "%d", minutes);
      lcd_clrscr();
      if(hours < 10)
        lcd_puts("0");
      lcd_puts(h);
      lcd_puts(":");
      if(minutes < 10)
        lcd_puts(":0");
      else
        lcd_puts(":");
      lcd_puts(m);
      lcd_puts(":");

      seconds = 60;
      
      while(seconds > 0) {
        tmp = 0;

        seconds--;
        
        sprintf(s, "%d", seconds);
        lcd_clrscr();
        if(hours < 10)
          lcd_puts("0");
        lcd_puts(h);
        lcd_puts(":");
        if(minutes < 10)
          lcd_puts(":0");
        else
          lcd_puts(":");
        lcd_puts(m);
        if(seconds < 10) 
          lcd_puts(":0");
        else
          lcd_puts(":");
        lcd_puts(s);

        _delay_ms(1000);
        }
      }

    hours--;

    if(hours == 0)
      minutes = 60;
    
    //seconds = 60;
    }

  lcd_clrscr();
  lcd_puts("Test Complete");

  //char choice = '0';
  //unsigned char test = '0';

  /* DO NOT DELETE
  while(1) {
    read_max();
    ext_temp = read_ext_temp();
    int_temp = read_int_temp();
    ext_temp = to_degf(ext_temp);
    int_temp = to_degf(int_temp);

    sprintf(ext_str, "%d", ext_temp);
    sprintf(int_str, "%d", int_temp);

    lcd_clrscr();
    lcd_puts(ext_str);
    lcd_gotoxy(0,1);
    lcd_puts(int_str);
    _delay_ms(1000);
    }
    */

  /*
  char key;
  int temp = 0;
  int hours = 0;
  int minutes = 0;
  struct Flags flags;

  flags.temp_flag = 0;
  flags.time_flag = 0;

  lcd_init(LCD_DISP_ON);
  keypad_init();

  while(flags.temp_flag == 0 || flags.time_flag == 0) {
    key = main_screen();
    _delay_ms(5);

    if(key == 'A') {
      lcd_clrscr();
      temp = set_temp(&flags);
      key = 'z';
      }
    if(key == 'B') {
      lcd_clrscr();
      hours = set_hours(&flags);
      minutes = set_minutes(&flags);
      key = 'z';

      if(flags.hour_flag == 1 && flags.mins_flag == 1)
        flags.time_flag = 1;
      }
    }

  lcd_clrscr();

  int size = (int)((ceil(log10(temp))+1)*sizeof(char));
  char t[size];
  char h[size];
  char m[size];

  sprintf(t, "%d", temp);
  sprintf(h, "%d", hours);
  sprintf(m, "%d", minutes);

  lcd_gotoxy(0,1);
  lcd_puts("Time:");
  lcd_gotoxy(6,1);
  lcd_puts(h);
  lcd_puts(":");
  lcd_puts(m);
  lcd_puts(":");
  lcd_puts("00");
  */
  }

char main_screen() {
  char key;

  lcd_puts("A: Enter Temp");
  lcd_gotoxy(0,1);
  lcd_puts("B: Enter Time");

  while(1) {
    key = get_key();
    _delay_ms(5);

    if(key == 'A' || key == 'B' || key == '*')
      break;
    }

  return key;
  }

int set_temp(struct Flags *flags) {
  char key;
  char tmp[4];
  int i = 0;
  int temp = 0;

  lcd_puts("Enter Temp:");
  lcd_gotoxy(0,1);
  lcd_puts("#: Done");
  lcd_gotoxy(12,0);

  while(1) {
    key = get_key();
    _delay_ms(5);

    if(key != 'z' && key != '#') {
      tmp[i] = key;
      lcd_putc(key);
      i++;
      }

    if(key == '#') {
      tmp[3] = '\0';
      flags->temp_flag = 1;
      break;
      }
    }

  key = 'z';
  lcd_clrscr();

  sscanf(tmp, "%d", &temp);
  return temp;
  }

int set_hours(struct Flags *flags) {
  char key;
  char tmp[3];
  int i = 0;
  int hours = 0;

  lcd_puts("Enter Hours:");
  lcd_gotoxy(0,1);
  lcd_puts("#: Done");
  lcd_gotoxy(13,0);

  while(1) {
    key = get_key();
    _delay_ms(5);

    if(key != 'z' && key != '#') {
      tmp[i] = key;
      lcd_putc(key);
      i++;
      }

    if(key == '#') {
      tmp[2] = '\0';
      flags->hour_flag = 1;
      break;
      }
    }

  key = 'z';
  lcd_clrscr();

  sscanf(tmp, "%d", &hours);
  return hours;
  }

int set_minutes(struct Flags *flags) {
  char key;
  char tmp[3];
  int i = 0;
  int mins = 0;

  lcd_puts("Enter Min:");
  lcd_gotoxy(0,1);
  lcd_puts("#: Done");
  lcd_gotoxy(11,0);

  while(1) {
    key = get_key();
    _delay_ms(5);

    if(key != 'z' && key != '#') {
      tmp[i] = key;
      lcd_putc(key);
      i++;
      }

    if(key == '#') {
      tmp[2] = '\0';
      flags->mins_flag = 1;
      break;
      }
    }

  key = 'z';
  lcd_clrscr();

  sscanf(tmp, "%d", &mins);
  return mins;
  }
