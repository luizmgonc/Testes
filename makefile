CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: organizar_mensagens

organizar_mensagens: organizar_mensagens.c
	gcc $(CFLAGS) organizar_mensagens.c -o organizar_mensagens $(LDFLAGS)

clean:
	rm -f organizar_mensagens                       