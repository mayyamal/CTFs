# Makefile for this hacklet

PROJECT := unwanted_redirect

CC       := gcc -m32
CFLAGS   := -std=c99 -pedantic -Wno-format-security -O0 -ggdb
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
