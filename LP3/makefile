src := $(patsubst src/%.c,%,$(wildcard src/*.c))
all: $(src)

$(src):
	gcc -Wall ./src/$@.c ../lib/monstro.c ../lib/jogador.c -I ../lib -o ./comp/$@ 