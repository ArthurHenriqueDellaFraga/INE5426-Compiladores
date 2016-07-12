# My Little Makefile
CC=clang++
OUTPUT=teste
FILESYSTEM = ../../Projeto2/boost_1_60_0/stage/lib/libboost_filesystem.a
SYSTEM = ../../Projeto2/boost_1_60_0/stage/lib/libboost_system.a
BOOST = ../../Projeto2/boost_1_60_0/

all: clang

clang: *.cpp
	${CC} -I ${BOOST} -o ${OUTPUT} *.cpp ${FILESYSTEM} ${SYSTEM}

execute: all
	./${OUTPUT}
