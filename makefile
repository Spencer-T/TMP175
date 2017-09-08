CFLAGS= -Wall -Wshadow -Wwrite-strings -Wsign-compare -Wfloat-equal \
	-mcpu=cortex-a8 -mfloat-abi=hard -mfpu=neon \
	-Wmissing-noreturn -Wbad-function-cast \
	-Wmissing-prototypes -Winline -Wredundant-decls -O3 \


# all: example_01 example_02 example_03 example_04
all: example_06

# example_01: example_01.o BeagleBone_gpio.o
#	gcc $(CFLAGS) -o $@ $+
#	strip $@

# example_02: example_02.o BeagleBone_gpio.o
#	gcc $(CFLAGS) -o $@ $+
#	strip $@

# example_05: example_05.o beagle_gpio.o beagle_hd44780.o
#	gcc $(CFLAGS) -o $@ $+
#	strip $@

# example_03: example_03.o beagle_gpio.o beagle_hd44780.o
#        gcc $(CFLAGS) -o $@ $+
#        strip $@

example_06: example_06.o beagle_gpio.o beagle_hd44780.o
	gcc $(CFLAGS) -o $@ $+
#	gcc $(CFLAGS) -o $@ $+
	strip $@

clean:
#	rm -f a.out *.o example_01 example_02 example_03 example_04
	rm -f a.out *.o example_05 example_06

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $+
