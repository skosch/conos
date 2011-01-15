all: hex

hex: main lcd 
	gplink -o main.hex -a inhx32 main.o lcd18.o

main: main.asm
	gpasm -c -p p18f4620 -w 2 main.asm

lcd: lcd18.asm
	gpasm -c -p p18f4620 -w 2 lcd18.asm





clean:
	rm -rf *o


send: main.hex
	pk2cmd -pPIC18F4620 -m -f/home/sebastian/conos/silence/main.hex

sim: main.hex main.cod
	gpsim -pp18f4620 -s main.cod main.hex