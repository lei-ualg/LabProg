src := $(patsubst src/%.c,%,$(wildcard src/*.c))
all: $(src)

$(src):
	gcc -Wall ./src/$@.c ../lib/P1/submission.c -I ../lib/P1 -o ./comp/$@ 