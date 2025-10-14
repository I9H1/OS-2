TARGET = thread
SRCS = thread.c

CC=gcc
RM=rm
CFLAGS= -g -fsanitize=address -fsanitize=leak -Wall -Wextra -Werror
LIBS=-lpthread
INCLUDE_DIR="."

all: ${TARGET}

${TARGET}: ${SRCS}
	${CC} ${CFLAGS} -I${INCLUDE_DIR} ${SRCS} ${LIBS} -o ${TARGET}

clean:
	${RM} -f *.o ${TARGET}
