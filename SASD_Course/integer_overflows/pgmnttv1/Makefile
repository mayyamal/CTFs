# Makefile for this hacklet

PROJECT := pgmnttv1

CC       := clang -m32
CFLAGS   := -Wall -Wextra -pedantic -std=c99 -g -fno-stack-protector -fno-pie
LD       := $(CC)
LDFLAGS  := -std=c99 -g -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack -fno-pie -Wl,-u,codeofbugs
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
