src := $(patsubst src/%.c,%,$(wildcard src/*.c))
all: $(src)

$(src):
	gcc -Wall ./src/$@.c ../lib/festa/festa1.c ../lib/festa/lista.c -I ../lib/festa -o ./comp/$@ 