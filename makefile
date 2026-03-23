CC=cc
CPP=g++
CFLAGS= -O4
LDFLAGS=

all: enumerator

tools:  enumerator

enumerator: src/enumerator.o src/enumerator_util.o src/enumerator_premapper.o
	${CPP} -o enumerator ${CFLAGS} src/enumerator.cpp src/enumerator_util.cpp src/enumerator_premapper.cpp ${LDFLAGS} 

