# Makefile for this hacklet

PROJECT := floaty

CC       := gcc -m32
CFLAGS   := -Wall -Wextra -pedantic -O3 -std=c99 -g -fstack-protector-all -pie
LD       := $(CC)
LDFLAGS  := -std=c99 -g -Wl,-z,relro -Wl,-z,now -Wl,-u,callofbugs -pie
LIBS     := -lm

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
