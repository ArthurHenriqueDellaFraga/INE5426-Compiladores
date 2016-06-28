# My Little Makefile
FLEX=flex
BISON=bison
CC=clang++
PARAM=-std=c++11 -fcxx-exceptions -Wno-deprecated-register
OUTPUT=myparse

BOOST=-I boost_1_60_0

all: flex yacc clang

clang: *.cpp *.h
	${CC} ${BOOST} -o ${OUTPUT} *.cpp ${LLVMPARAM} ${PARAM}

yacc: parser.y
	${BISON} --defines=parser.h --output=parser.cpp parser.y

flex: scanner.l
	${FLEX} -o scanner.cpp scanner.l

clean:
	rm parser.cpp parser.h scanner.cpp ${OUTPUT}

test: all
	./${OUTPUT} < input_example

execute: all
	./${OUTPUT}

yacc_debug: parser.y
	${BISON} --defines=parser.h --output=parser.cpp --debug parser.y

debug: flex yacc_debug clang
