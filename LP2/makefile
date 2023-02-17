src := $(patsubst src/%.c,%,$(wildcard src/*.c))
all: $(src)

$(src):
	gcc -Wall ./src/$@.c ../lib/our_ints.c ../lib/our_doubles.c -I ../lib -o ./comp/$@ 