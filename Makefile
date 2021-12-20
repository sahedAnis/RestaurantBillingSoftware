CC      = gcc

CFLAGS  = -Wall -Wextra
CFLAGS += -g

app: app.c
	${CC} ${CFLAGS} -o app app.c

