# Makefile for this hacklet

PROJECT := simple_ret2libc

CC       := gcc
CFLAGS 	 := -std=c99 -fno-stack-protector -O0 -Wl,-z,norelro -no-pie -static-libgcc
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
