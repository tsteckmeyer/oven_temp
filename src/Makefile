##########  Project Specific Details  ##########

MCU 	= atmega32u4
F_CPU 	= 16000000UL
BAUD	= 9600UL

##  Project Header FIles  ##
LIBDIR 	= ../include

##########  Programmer Defaults  ##########

##  Change this for either avr109 or buspirate
PROGRAMMER = buspirate
##  Arguments for programmer such as location
PROGRAMMER_ARGS = -P /dev/ttyUSB0

##########  Program Locations  ##########

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

##########  Makefile Details  ##########

##  Project Name
TARGET = main
#TARGET = $(lastword $(subst /, ,$(CURDIR)))

##########  Object Files  ##########

SOURCES = $(wildcard *.c $(LIBDIR)/*.c)
OBJECTS = $(SOURCES:.c=.o)
HEADERS = $(SOURCES:.c=.h)

##  Compiler Options
CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I. -I$(LIBDIR)
CFLAGS = -Os -g -std=gnu99 -Wall
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -ffunction-sections -fdata-sections

LDFLAGS = -Wl,-Map,$(TARGET).map
LDFLAGS += -Wl,--gc-sections

TARGET_ARCH = -mmcu=$(MCU)

##  Explicit Pattern Rules
##  .c files to .o files
%.o: %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

%.eeprom: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%.lst: %.elf
	$(OBJDUMP) -S $< > $@

.PHONY: all disassemble disasm eeprom size clean squeaky_clean flash fuses

all: $(TARGET).hex

debug:
	@echo
	@echo "Source Files:" $(SOURCES)
	@echo "MCU, F_CPU, BAUD:" $(MCU), $(F_CPU), $(BAUD)
	@echo

##  Create listing file from .elf
disassemble: $(TARGET).lst

disasm: disassemble

##  Show program size
size: $(TARGET).elf
	$(AVRSIZE) -C --mmcu=$(MCU) $(TARGET).elf

clean: rm -f $(TARGET) $(TARGET).hex $(TARGET).obj \
	$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(TARGET).eeprom

squeaky_clean:
	rm -f *.elf *.hex *.obj *.o *.d *.eep *.lst *.lss *.sym *.map *~ *.eeprom

##########  Programmer Specific Details  ##########

flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

##  Alias for flash
program: flash

flash_eeprom: $(TARGET).eeprom
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) $(PROGRAMMER_ARGS) -U eeprom:w:$<

avrdude_terminal:
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) $(PROGRAMMER_ARGS) -nt

