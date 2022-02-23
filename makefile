# # simple AVR Makefile
# #
# # written by michael cousins (http://github.com/mcous)
# # released to the public domain

# # Makefile
# #
# # targets:
# #   all:    compiles the source code
# #   test:   tests the isp connection to the mcu
# #   flash:  writes compiled hex file to the mcu's flash memory
# #   fuse:   writes the fuse bytes to the MCU
# #   disasm: disassembles the code for debugging
# #   clean:  removes all .hex, .elf, and .o files in the source code and library directories

# # parameters (change this stuff accordingly)
# # project name
# #PRJ = main
# # avr mcu
# MCU = atmega4809
# # mcu clock frequency
# CLK = 3333333
# # avr programmer (and port if necessary)
# # e.g. PRG = usbtiny -or- PRG = arduino -P /dev/tty.usbmodem411
# PRG = pkobn_updi
# # fuse values for avr: low, high, and extended
# # these values are from an Arduino Uno (ATMega328P)
# # see http://www.engbedded.com/fusecalc/ for other MCUs and options
# #LFU = 0xFF
# #HFU = 0xDE
# #EFU = 0x05
# # program source files (not including external libraries)
# SRC = $(PRJ).c uart.c
# # where to look for external libraries (consisting of .c/.cpp files and .h files)
# # e.g. EXT = ../../EyeToSee ../../YouSART
# EXT =


# #################################################################################################
# # \/ stuff nobody needs to worry about until such time that worrying about it is appropriate \/ #
# #################################################################################################

# # include path
# INCLUDE := $(foreach dir, $(EXT), -I$(dir))
# # c flags
# CFLAGS    = -Wall -Os -DF_CPU=$(CLK) -mmcu=$(MCU) $(INCLUDE)
# # any aditional flags for c++
# CPPFLAGS =

# # executables
# AVRDUDE = avrdude -c $(PRG) -p $(MCU)
# OBJCOPY = avr-objcopy
# OBJDUMP = avr-objdump
# SIZE    = avr-size --format=avr --mcu=$(MCU)
# CC      = avr-gcc

# # generate list of objects
# CFILES    = $(filter %.c, $(SRC))
# EXTC     := $(foreach dir, $(EXT), $(wildcard $(dir)/*.c))
# CPPFILES  = $(filter %.cpp, $(SRC))
# EXTCPP   := $(foreach dir, $(EXT), $(wildcard $(dir)/*.cpp))
# OBJ       = $(CFILES:.c=.o) $(EXTC:.c=.o) $(CPPFILES:.cpp=.o) $(EXTCPP:.cpp=.o)

# # user targets
# # compile all files
# all: Slave.hex Master.hex

# slave:Slave.hex

# master:Master.hex

# # test programmer connectivity
# test:
# 	$(AVRDUDE) -v

# # flash program to mcu
# flash: all
# 	$(AVRDUDE) -U flash:w:$(PRJ).hex:i

# # write fuses to mcu
# fuse:
# 	$(AVRDUDE) -U lfuse:w:$(LFU):m -U hfuse:w:$(HFU):m -U efuse:w:$(EFU):m

# # generate disassembly files for debugging
# disasm: $(PRJ).elf
# 	$(OBJDUMP) -d $(PRJ).elf

# # remove compiled files
# clean:
# 	ifeq ($(OS),Windows_NT)
# 		del /q *.hex *.elf *.o
# 		$(foreach dir, $(EXT), del /q $(dir)/*.o;)
# 	else
# 		rm -f *.hex *.elf *.o
# 		$(foreach dir, $(EXT), rm -f $(dir)/*.o;)
# 	endif

# # other targets
# # objects from c files
# .c.o:
# 	$(CC) $(CFLAGS) -c $< -o $@

# # objects from c++ files
# .cpp.o:
# 	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# # elf file
# Master.elf: $(OBJ)
# 	$(CC) $(CFLAGS) -o Master.elf $(OBJ)

# Slave.elf: $(OBJ)
# 	$(CC) $(CFLAGS) -o Slave.elf $(OBJ)

# # hex file
# Master.hex: Master.elf
# 	ifeq ($(OS),Windows_NT)
# 		del /q Master.hex
# 	else
# 		rm -f Master.hex
# 	endif
# 	$(OBJCOPY) -j .text -j .data -O ihex Master.elf Master.hex
# 	$(SIZE) Master.elf

# Slave.hex: Slave.elf
# 	ifeq ($(OS),Windows_NT)
# 		del /q Slave.hex
# 	else
# 		rm -f Slave.hex
# 	endif
# 	$(OBJCOPY) -j .text -j .data -O ihex Slave.elf Slave.hex
# 	$(SIZE) Slave.elf

# 	# simple AVR Makefile
#
# written by michael cousins (http://github.com/mcous)
# released to the public domain

# Makefile
#
# targets:
#   all:    compiles the source code
#   test:   tests the isp connection to the mcu
#   flash:  writes compiled hex file to the mcu's flash memory
#   fuse:   writes the fuse bytes to the MCU
#   disasm: disassembles the code for debugging
#   clean:  removes all .hex, .elf, and .o files in the source code and library directories

# parameters (change this stuff accordingly)
# project name1
PRJ_SLAVE = Slave
# project name2
PRJ_MASTER = Master
# avr mcu
MCU = atmega4809
# mcu clock frequency
CLK = 16000000
# avr programmer (and port if necessary)
# e.g. PRG = usbtiny -or- PRG = arduino -P /dev/tty.usbmodem411
PRG = usbtiny
# fuse values for avr: low, high, and extended
# these values are from an Arduino Uno (ATMega328P)
# see http://www.engbedded.com/fusecalc/ for other MCUs and options
LFU = 0xFF
HFU = 0xDE
EFU = 0x05
# program source files (not including external libraries)
SRC_SLAVE = ./Slave/main.c
SRC_MASTER = ./Master/main.c
SRC = uart.c
OUTPUT_SLAVE = ./Slave_build/
OUTPUT_MASTER = ./Master_build/
# where to look for external libraries (consisting of .c/.cpp files and .h files)
# e.g. EXT = ../../EyeToSee ../../YouSART
EXT = ./


#################################################################################################
# \/ stuff nobody needs to worry about until such time that worrying about it is appropriate \/ #
#################################################################################################

# include path
INCLUDE := $(foreach dir, $(EXT), -I$(dir))
# c flags
CFLAGS    = -Wall -DF_CPU=$(CLK) -mmcu=$(MCU) $(INCLUDE) -B ./atmega4809


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
$(info $(OBJ_SLAVE))
# user targets
# compile all files
all: $(PRJ_SLAVE).hex $(PRJ_MASTER).hex
	
slave: $(PRJ_SLAVE).hex

master: $(PRJ_MASTER).hex

# test programmer connectivity
test:
	$(AVRDUDE) -v

# flash program to mcu
flash: all
	$(AVRDUDE) -U flash:w:$(PRJ).hex:i

# write fuses to mcu
fuse:
	$(AVRDUDE) -U lfuse:w:$(LFU):m -U hfuse:w:$(HFU):m -U efuse:w:$(EFU):m

# generate disassembly files for debugging
disasm: $(PRJ).elf
	$(OBJDUMP) -d $(OUTPUT)$(PRJ).elf

# remove compiled files
clean:
	rm -f $(OUTPUT_SLAVE)*.hex $(OUTPUT_SLAVE)*.elf
	rm -f $(OUTPUT_MASTER)*.hex $(OUTPUT_MASTER)*.elf
	$(foreach dir, $(SRC), rm -f $(dir $(dir))/*.o;)
	$(foreach dir, $(SRC_SLAVE), rm -f $(dir $(dir))/*.o;)
	$(foreach dir, $(SRC_MASTER), rm -f $(dir $(dir))/*.o;)

# other targets
# objects from c files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OUTPUT_SLAVE):
	mkdir -p $(OUTPUT_SLAVE)


$(OUTPUT_MASTER):
	mkdir -p $(OUTPUT_MASTER)
	

# elf files
$(PRJ_SLAVE).elf: $(OUTPUT_SLAVE) $(OBJ_SLAVE)
	@echo $(OBJ_SLAVE)
	$(CC) $(CFLAGS) -o $(OUTPUT_SLAVE)$(PRJ_SLAVE).elf $(OBJ_SLAVE)

$(PRJ_MASTER).elf: $(OUTPUT_MASTER) $(OBJ_MASTER)
	@echo $(OBJ_MASTER)
	$(CC) $(CFLAGS) -o $(OUTPUT_MASTER)$(PRJ_MASTER).elf $(OBJ_MASTER)


# hex files
$(PRJ_SLAVE).hex: $(PRJ_SLAVE).elf
	rm -f $(OUTPUT_SLAVE)$(PRJ_SLAVE).hex
	$(OBJCOPY) -j .text -j .data -O ihex $(OUTPUT_SLAVE)$(PRJ_SLAVE).elf $(OUTPUT_SLAVE)$(PRJ_SLAVE).hex
	$(SIZE) $(OUTPUT_SLAVE)$(PRJ_SLAVE).elf

$(PRJ_MASTER).hex: $(PRJ_MASTER).elf
	rm -f $(OUTPUT_MASTER)$(PRJ_MASTER).hex
	$(OBJCOPY) -j .text -j .data -O ihex $(OUTPUT_MASTER)$(PRJ_MASTER).elf $(OUTPUT_MASTER)$(PRJ_MASTER).hex
	$(SIZE) $(OUTPUT_MASTER)$(PRJ_MASTER).elf