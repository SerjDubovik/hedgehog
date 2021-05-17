###############################################################################
# Makefile for the project hedgehog_C_HD44780_PWM
###############################################################################

## General Flags
PROJECT = hedgehog_C_HD44780_PWM
MCU = atmega16
TARGET = hedgehog_C_HD44780_PWM.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -O0 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=hedgehog_C_HD44780_PWM.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"D:\AVR C project\hedgehog_C_HD44780_PWM\." 

## Objects that must be built in order to link
OBJECTS = hedgehog_C_HD44780_PWM.o HD44780.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) hedgehog_C_HD44780_PWM.hex hedgehog_C_HD44780_PWM.eep hedgehog_C_HD44780_PWM.lss size

## Compile
hedgehog_C_HD44780_PWM.o: ../hedgehog_C_HD44780_PWM.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

HD44780.o: ../HD44780.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) hedgehog_C_HD44780_PWM.elf dep/* hedgehog_C_HD44780_PWM.hex hedgehog_C_HD44780_PWM.eep hedgehog_C_HD44780_PWM.lss hedgehog_C_HD44780_PWM.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

