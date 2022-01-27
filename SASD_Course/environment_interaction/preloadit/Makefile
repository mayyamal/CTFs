# Makefile for this hacklet

PROJECT := preloadit

CC       := gcc
CFLAGS   := -std=c99 -Wl,-z,relro -Wl,-z,now -pedantic -O0 -ggdb
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
	@chmod 111 $@

%.o: %.c
	@echo [CC] $<
	@$(CC) $(CFLAGS) -o $@ -c -MMD $<

run:
	@./exploit

clean:
	@rm -f $(PROJECT) $(OBJECTS) $(DEPENDS)

-include $(DEPENDS)
