CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: organizar_mensagens_rx organizar_mensagens_tx

organizar_mensagens_rx: organizar_mensagens_rx.c
	gcc $(CFLAGS) organizar_mensagens_rx.c -o organizar_mensagens_rx $(LDFLAGS)

organizar_mensagens_tx: organizar_mensagens_tx.c
	gcc $(CFLAGS) organizar_mensagens_tx.c -o organizar_mensagens_tx $(LDFLAGS)

clean:
	rm -f organizar_mensagens_rx                       