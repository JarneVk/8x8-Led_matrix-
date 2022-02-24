# Makefile
#
# targets:
#   all:    compiles the source code
#   test:   tests the isp connection to the mcu
#   flash:  writes compiled hex file to the mcu's flash memory
#   fuse:   writes the fuse bytes to the MCU
#   disasm: disassembles the code for debugging
#   clean:  removes all .hex, .elf, and .o files in the source code and library directories
ifeq ($(OS),Windows_NT)
SHELL=cmd
endif

# parameters (change this stuff accordingly)
# project name1
PRJ_SLAVE = Slave
# project name2
PRJ_MASTER = Master
# avr mcu
MCU = atmega4809
# mcu clock frequency (default atmega4809 clock = 3.3333 Mhz)
CLK = 3333333
# avr programmer (and port if necessary)
# e.g. PRG = usbtiny -or- PRG = arduino -P /dev/tty.usbmodem411, curiosity nano: pkobn_updi
PRG = pkobn_updi
# fuse values for avr: low, high, and extended
# these values are from an Arduino Uno (ATMega328P)
# see http://www.engbedded.com/fusecalc/ for other MCUs and options
# LFU = 0xFF	#!
# HFU = 0xDE	#!
# EFU = 0x05	#!
# program source files (not including external libraries)
SRC_SLAVE = ./Slave/main.c
SRC_MASTER = ./Master/main.c
SRC = uart.c 
OUTPUT_SLAVE = ./Slave_build/
OUTPUT_MASTER = ./Master_build/
# where to look for external libraries (consisting of .c/.cpp files and .h files)
# e.g. EXT = ../../EyeToSee ../../YouSART
EXT = ./

#Voor windows foward slash (fuck you windows)
BLANK :=

#################################################################################################
# \/ stuff nobody needs to worry about until such time that worrying about it is appropriate \/ #
#################################################################################################

# include path
INCLUDE := $(foreach dir, $(EXT), -I$(dir))
# c flags
#CFLAGS    = -Wall -DF_CPU=$(CLK) -mmcu=$(MCU) $(INCLUDE) -B ./atmega4809
CFLAGS    = -x c -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -Wall -mmcu=atmega4809 -B ".\atmega4809" -c -std=gnu99 #-MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"
LINKERFLAGS =  -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=atmega4809 -B ".\atmega4809"  

# executables
AVRDUDE = avrdude -c $(PRG) -p $(MCU)
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE    = avr-size --format=avr --mcu=$(MCU)
CC      = avr-gcc

# generate list of objects
CFILES_SLAVE  = $(SRC) $(SRC_SLAVE)
CFILES_MASTER = $(SRC) $(SRC_MASTER)
EXTC         := $(foreach dir, $(EXT), $(wildcard $(dir)/*.c))
#OBJ_SLAVE    := $(foreach dir, $(CFILES_SLAVE),$(OUTPUT_SLAVE)$(subst .c,.o,$(notdir $(dir)))) $(EXTC:.c=.o)
OBJ_SLAVE    := $(CFILES_SLAVE:.c=.o) $(EXTC:.c=.o)
OBJ_MASTER    = $(CFILES_MASTER:.c=.o) $(EXTC:.c=.o)

# user targets
# compile all files
all: $(PRJ_SLAVE).hex $(PRJ_MASTER).hex
	
slave: $(PRJ_SLAVE).hex

master: $(PRJ_MASTER).hex

# test programmer connectivity
test:
	$(AVRDUDE) -v

# flash program to mcu (nog niet af)
flash: all
	$(AVRDUDE) -U flash:w:$(PRJ).hex:i

# write fuses to mcu (moet nog is bezien worden)
# fuse:
# 	$(AVRDUDE) -U lfuse:w:$(LFU):m -U hfuse:w:$(HFU):m -U efuse:w:$(EFU):m

# generate disassembly files for debugging
disasm_slave: $(PRJ_SLAVE).elf
	$(OBJDUMP) -d $(OUTPUT_SLAVE)$(PRJ_SLAVE).elf > $(OUTPUT_SLAVE)$(PRJ_SLAVE).txt

disasm_master: $(PRJ_MASTER).elf
	$(OBJDUMP) -d $(OUTPUT_MASTER)$(PRJ_MASTER).elf > $(OUTPUT_MASTER)$(PRJ_MASTER).txt

# remove compiled files
clean:
ifeq ($(OS),Windows_NT)
	del /q $(subst /,\$(BLANK),$(OUTPUT_SLAVE))*.hex
	del /q $(subst /,\$(BLANK),$(OUTPUT_SLAVE))*.elf
	del /q $(subst /,\$(BLANK),$(OUTPUT_MASTER))*.hex
	del /q $(subst /,\$(BLANK),$(OUTPUT_MASTER))*.elf
	$(foreach dir, $(subst /,\,$(dir $(SRC))), del /q $(dir)*.o;)
	$(foreach dir, $(subst /,\,$(dir $(SRC_SLAVE))), del /q $(dir)*.o;)
	$(foreach dir, $(subst /,\,$(dir $(SRC_MASTER))), del /q $(dir)*.o;)
else
	rm -f $(OUTPUT_SLAVE)*.hex $(OUTPUT_SLAVE)*.elf
	rm -f $(OUTPUT_MASTER)*.hex $(OUTPUT_MASTER)*.elf
	$(foreach dir, $(SRC), rm -f $(dir $(dir))/*.o;)
	$(foreach dir, $(SRC_SLAVE), rm -f $(dir $(dir))/*.o;)
	$(foreach dir, $(SRC_MASTER), rm -f $(dir $(dir))/*.o;)
endif

# other targets
# objects from c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OUTPUT_SLAVE):
ifeq ($(OS),Windows_NT)
	-mkdir $(subst /,\,$(subst ./,,$(OUTPUT_SLAVE)))
else
	mkdir -p $(OUTPUT_SLAVE)
endif

$(OUTPUT_MASTER):
ifeq ($(OS),Windows_NT)
	-mkdir $(subst /,\,$(subst ./,,$(OUTPUT_MASTER)))
else
	mkdir -p $(OUTPUT_MASTER)
endif

# elf files
$(PRJ_SLAVE).elf: $(OUTPUT_SLAVE) $(OBJ_SLAVE)
	$(CC) -o $(OUTPUT_SLAVE)$(PRJ_SLAVE).elf $(OBJ_SLAVE) -Wl,-Map="$(OUTPUT_SLAVE)$(PRJ_SLAVE).map" $(LINKERFLAGS)

$(PRJ_MASTER).elf: $(OUTPUT_MASTER) $(OBJ_MASTER)
	$(CC) -o $(OUTPUT_MASTER)$(PRJ_MASTER).elf $(OBJ_MASTER) -Wl,-Map="$(OUTPUT_MASTER)$(PRJ_MASTER).map" $(LINKERFLAGS)


# hex files
$(PRJ_SLAVE).hex: $(PRJ_SLAVE).elf
ifeq ($(OS),Windows_NT)
	del /q $(subst /,\,$(OUTPUT_SLAVE)\$(PRJ_SLAVE)).hex
else
	rm -f $(OUTPUT_SLAVE)$(PRJ_SLAVE).hex
endif
	$(OBJCOPY) -j .text -j .data -O ihex $(OUTPUT_SLAVE)$(PRJ_SLAVE).elf $(OUTPUT_SLAVE)$(PRJ_SLAVE).hex
	$(SIZE) $(OUTPUT_SLAVE)$(PRJ_SLAVE).elf

$(PRJ_MASTER).hex: $(PRJ_MASTER).elf
ifeq ($(OS),Windows_NT)
	del /q $(subst /,\,$(OUTPUT_MASTER)\$(PRJ_MASTER)).hex
else
	rm -f $(OUTPUT_MASTER)$(PRJ_MASTER).hex
endif
	$(OBJCOPY) -j .text -j .data -O ihex $(OUTPUT_MASTER)$(PRJ_MASTER).elf $(OUTPUT_MASTER)$(PRJ_MASTER).hex
	$(SIZE) $(OUTPUT_MASTER)$(PRJ_MASTER).elf