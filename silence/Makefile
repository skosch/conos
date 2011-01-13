all: hex

hex: main lcd macros
	gplink -o main.hex -a inhx32 main.o lcd.o macros.o

main: main.asm
	gpasm -c -p p16f877 -w 2 main.asm

lcd: lcd.asm
	gpasm -c -p p16f877 -w 2 lcd.asm

macros: macros.asm
	gpasm -c -p p16f877 -w 2 macros.asm


clean:
	rm -rf *o


send: main.hex
	pk2cmd -p -m -f/home/sebastian/conos/silence/main.hex