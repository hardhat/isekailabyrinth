OBJ=main.o player.o enemy.o hero.o level.o buffs.o
CFLAGS=-I..

all: battle

clean:
	-rm *.o

player.o: ../player.c
	gcc -c ../player.c

enemy.o: ../enemy.c
	gcc -c ../enemy.c

hero.o: ../hero.c
	gcc -c ../hero.c

level.o: ../level.c
	gcc -c ../level.c

buffs.o: ../buffs.c
	gcc -c ../buffs.c

battle: $(OBJ)
	gcc -o battle $(OBJ)
