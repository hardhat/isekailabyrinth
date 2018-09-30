#define byte unsigned char

#include "level.h"
#include "player.h"

byte map[MAPCOUNT]={
	0,0,0,0,0,0,
	0,0,0,2,0,0,
	1,0,0,0,2,0,
	0,0,0,2,0,0,
	0,0,0,0,0,0,
	0,0,0,0,0,0,
};

void updateLevelMap()
{
	int i;
	
	for(i=0;i<MAPCOUNT;i++) {
		map[i]=0;
	}
	for(i=0;i<enemyCount;i++) {
		map[enemy[i].cell]=2;
	}
	for(i=0;i<heroCount;i++) {
		map[hero[i].cell]=1;
	}
}
