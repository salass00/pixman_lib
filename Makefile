TARGET  := pixman-1.library
VERSION := 53

CC     := ppc-amigaos-gcc
STRIP  := ppc-amigaos-strip
AR     := ppc-amigaos-ar
RANLIB := ppc-amigaos-ranlib

BUILDSYS := $(shell uname -s)

# Only use host argument if cross-compiling
ifneq ($(BUILDSYS),AmigaOS)
	HOSTARG := --host=ppc-amigaos
else
	HOSTARG := 
endif

PIXMANDIR := pixman-0.34.0

OPTIMIZE := -O2 -fomit-frame-pointer
DEBUG    := -g
INCLUDES := -I./include -I./$(PIXMANDIR)/pixman
WARNINGS := -Wall -Wwrite-strings -Werror

CFLAGS  := $(OPTIMIZE) $(DEBUG) $(INCLUDES) $(WARNINGS)
LDFLAGS := -static
LIBS    := pixman-build/pixman/.libs/libpixman-1.a

main_SRCS := main/Obtain.c main/Release.c
main_OBJS := $(main_SRCS:.c=.o)

SRCS := init.c $(main_SRCS)
OBJS := $(SRCS:.c=.o)

.PHONY: all
all: $(TARGET) libpixman-1.a

init.o: $(TARGET)_rev.h pixman_vectors.c pixman_vectors.h

$(main_OBJS): pixman_vectors.h

pixman-build/Makefile: $(PIXMANDIR)/configure
	mkdir -p pixman-build
	rm -rf pixman-build/*
	cd pixman-build && ../$(PIXMANDIR)/configure --prefix=/SDK/local/newlib $(HOSTARG) --disable-shared --disable-libpng

.PHONY: build-pixman
build-pixman: pixman-build/Makefile
	$(MAKE) -C pixman-build

$(TARGET): $(OBJS) build-pixman
	$(CC) $(LDFLAGS) -nostartfiles -o $@.debug $(OBJS) $(LIBS)
	$(STRIP) -R.comment -o $@ $@.debug

libpixman-1.a: static/autoinit_pixman_base.o static/autoinit_pixman_main.o static/stubs.o
	$(AR) -crv $@ $^
	$(RANLIB) $@

.PHONY: clean
clean:
	rm -f $(TARGET).debug *.o main/*.o lib*.a static/*.o
	rm -rf pixman-build

.PHONY: revision
revision:
	bumprev $(VERSION) $(TARGET)

