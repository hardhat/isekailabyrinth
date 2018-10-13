#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define byte unsigned char

#include "level.h"
#include "player.h"
#include "actions.h"

#define M_BATTLE 0

const char *rankName[]={
	"Knight",
	"Baron",
	"Viscount",
	"Earl",
	"Marquis",
	"Duke",
	"Archduke",
	"Despot",
	"King",
	"High King",
	"Emperor"
};
#define RANKCOUNT 11

byte enemyReady;
extern struct EnemyPlan enemyPlan;


void newgame()
{
	enemyReady=1;
}

void drawMapTile(byte x,byte y,byte tile)
{
	printf("%c ",'0'+tile);
}

void drawLine(int y)
{
	byte *from=map+y*MAPWIDTH;
	int i;

	for(i=0;i<6;i++) {
		drawMapTile(i,y,from[i]);
	}
	printf("\n");
}

void drawMap(int pass)
{
	int i,y;
	int health=0;

	for(y=0;y<6;y++) {
		drawLine(y);
	}
	for(i=0;i<heroCount;i++) {
		health+=hero[i].hp;
	}
	if(health==0) {
		printf(" GAME OVER! ");
		exit(0);
	}
}

void updateMap(int pass)
{
	updateLevelMap();
		
	if(enemyReady) updateEnemy(enemyPlan.mode);
}

void showMessage(const char *message)
{
	printf("Message: %s\n",(char *)message);
}

int main()
{
	int pass=0;
	int drawMode=0;
	int gameMode=M_BATTLE;

	
	newgame();
	drawMap(0);

	while(1) {
		// update the state of the character.
		if(gameMode==M_BATTLE) {
			updateMap(pass);
		}

		if(drawMode==1) {
			drawMap(pass);
		}
		
		pass++;
		if(pass==3) {
			drawMode=0;
			pass=0;
		}
		printf("end of line\n");
	}
}

