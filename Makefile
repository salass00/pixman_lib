TARGET  := pixman-1.library
VERSION := 53

CC     := ppc-amigaos-gcc
STRIP  := ppc-amigaos-strip
AR     := ppc-amigaos-ar
RANLIB := ppc-amigaos-ranlib
RM     := rm -f

PIXMANDIR := pixman-0.34.0

CFLAGS  := -O2 -fomit-frame-pointer -g -I./include -I./$(PIXMANDIR)/pixman -Wall -Wwrite-strings -Werror

main_SRCS := main/Obtain.c main/Release.c
main_OBJS := $(main_SRCS:.c=.o)

SRCS := init.c $(main_SRCS)
OBJS := $(SRCS:.c=.o)

.PHONY: all
all: $(TARGET) libpixman-1.a

init.o: $(TARGET)_rev.h pixman_vectors.c pixman_vectors.h

$(main_OBJS): pixman_vectors.h

pixman-build:
	mkdir $@

pixman-build/pixman/.libs/libpixman-1.a: pixman-build
	cd pixman-build && ../$(PIXMANDIR)/configure --prefix=/SDK/local/newlib --host=ppc-amigaos --disable-shared --disable-libpng
	$(MAKE) -C pixman-build

$(TARGET): $(OBJS) pixman-build/pixman/.libs/libpixman-1.a
	$(CC) -nostartfiles -o $@.debug $^
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

