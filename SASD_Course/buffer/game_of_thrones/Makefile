# Makefile for this hacklet

PROJECT := game_of_thrones

CC       := gcc
CFLAGS   := -fno-stack-protector
LD       := $(CC)
LDFLAGS  := 
LIBS     :=

SOURCE     := $(wildcard *.c)
OBJECTS    := $(SOURCE:%.c=%.o)
DEPENDS    := $(SOURCE:%.c=%.d)

all: $(PROJECT)

$(PROJECT): $(OBJECTS)
	@echo [LD] $@
	@$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIBS)

%.o: %.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -o $@ -c -MMD $<

run:
	@./exploit

clean:
	@rm -f $(PROJECT) $(OBJECTS) $(DEPENDS)

-include $(DEPENDS)
