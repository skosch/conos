all: objects

objects: main.o
	gplink -o test.hex -a inhx32 main.o

main.o: main.asm
	gpasm -c -p p16f877 -w 2 main.asm

clean:
	rm -rf *o
