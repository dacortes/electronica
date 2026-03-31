################################################################################
#                               COLOR DEFINITIONS                              #
################################################################################
END = \033[m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
LIGTH = \033[1m
DARK = \033[2m
ITALIC = \033[3m

SUCCESS = $(LIGTH)$(GREEN)[SUCCESS]$(END)
WARNING = $(LIGTH)$(YELLOW)[WARNING]$(END)
INFO = $(LIGTH)$(BLUE)[INFO]$(END)
ERROR = $(LIGTH)$(RED)[ERROR]$(END)

################################################################################
#                               BUILD VARIABLES                                #
################################################################################

MCU := atmega328p
PORT := /dev/ttyACM0
FREQUENCY_CPU := 16000000UL
CFLAGS := -g -Wall -mcall-prologues -mmcu=$(MCU) -Os -DF_CPU=$(FREQUENCY_CPU)
LDFLAGS := -Wl,-gc-sections -Wl,-relax
CC := avr-gcc
RMV = rm -rf
FLAGS_ASM := -MD -MF

SRC_DIR = src/
SOURCES := main.c

SRC := $(addprefix $(SRC_DIR), $(SOURCES))

DIRECTORY_OBJ = .obj
DIRECTORY_DEP = .dep


INCLUDES = $(addprefix -I, ./inc)

OBJECTS = $(addprefix $(DIRECTORY_OBJ)/, $(SOURCES:.c=.o))
DEPENENCIES = $(addprefix $(DIRECTORY_DEP)/, $(SOURCES:.c=.d))
DIRS_TO_CREATE = $(DIRECTORY_OBJ) $(DIRECTORY_DEP)

TARGET = main
ELF = $(DIRECTORY_OBJ)/$(TARGET).elf
HEX = $(TARGET).hex

################################################################################
#                               DEFAULT TARGET                                 #
################################################################################
all: dir $(HEX)
	@printf "$(SUCCESS) Build completed!\n"

$(HEX): $(ELF)
	@printf "$(INFO) Creating hex file...\n"
	avr-objcopy -R .eeprom -O ihex $< $@
	@printf "$(SUCCESS) Created: $(HEX)\n"

$(ELF): $(OBJECTS)
	@printf "$(INFO) Linking objects...\n"
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
	@printf "$(SUCCESS) Created: $(ELF)\n"

################################################################################
#                               DIRECTORY CREATION                             #
################################################################################
dir:
	@for DIR in $(DIRS_TO_CREATE); do \
		if [ ! -d $$DIR ]; then \
			mkdir -p $$DIR; \
			printf "$(BLUE)$(LIGTH)Creating directory:$(END) $$DIR\n"; \
		else \
			printf "$(BLUE)$(LIGTH)Directory already exists:$(END) $$DIR\n"; \
		fi \
	done

$(DIRECTORY_OBJ)/%.o: $(SRC_DIR)/%.c | $(DIRECTORY_OBJ) $(DIRECTORY_DEP)
	@printf "$(INFO) Compiling $< ...\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MF $(DIRECTORY_DEP)/$*.d -c $< -o $@
	@printf "$(SUCCESS) Created: $@\n"

-include $(DEPENENCIES)

################################################################################
#                               CLEAN TARGET                                   #
################################################################################
clean:
	@printf "$(INFO) Cleaning...\n"
	$(RMV) $(DIRECTORY_OBJ) $(DIRECTORY_DEP) $(HEX)
	@printf "$(SUCCESS) Clean completed!\n"

################################################################################
#                               PROGRAM TARGET                                 #
################################################################################
program: $(HEX)
	@printf "$(INFO) Programming Arduino Uno...\n"
	avrdude -p $(MCU) -c arduino -P $(PORT) -b 115200 -U flash:w:$(HEX)
	@printf "$(SUCCESS) Programming completed!\n"

re:
	clean all

.SILENT:
.PHONY: all clean re dir