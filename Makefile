CC = g++

CFLAGS =-g -WAll


all: enigma

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $^

enigma: main.o Enigma.o Rotor.o Reflector.o PlugBoard.o
	g++ main.o Enigma.o Rotor.o Reflector.o PlugBoard.o -o enigma

clean:
	rm *.o enigma

run: enigma
	./enigma 