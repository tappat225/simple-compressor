

CC = gcc
FLAGS = -g -Wall
TARGET = compressor
SRC = ./*.c

${TARGET}: ${SRC}
	${CC} -o ${TARGET} ${FLAGS} ${SRC}

.PHONY: clean

clean:
	rm -f ./*.o ${TARGET}


