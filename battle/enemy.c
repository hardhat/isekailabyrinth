#define byte unsigned char

#include "level.h"
#include "player.h"

#if 0
char reachMap[MAPCOUNT];

void putReach(int cell,int value)
{
	if(cell<0 || cell>=MAPCOUNT) return;
	if(reachMap[cell]!=127) return;
	reachMap[cell]=value;
}

void calculateReach(int cell, int mobility)
{
	int i;
	for(i=0;i<MAPCOUNT;i++) {
		int x=i%MAPWIDTH;
		int y=i/MAPWIDTH;
		reachMap[i]=127;
		if(map[i]==255) continue;	// empty cell
		reachMap[i]=map[i]&128?-16:16;
	}
	// grow around cell
	if(cell<1 || cell>=MAPCOUNT-1) return;
	reachMap[cell]=0;
	for(i=1;i<=mobility;i++) {
		if(cell-MAPWIDTH*i>0) putReach(cell-MAPWIDTH*i,i);
		if(cell-i>0) putReach(cell-i,i);
		if(cell+MAPWIDTH*i<MAPCOUNT) putReach(cell+MAPWIDTH*i,i);
		if(cell+i<MAPCOUNT) putReach(cell+i,i);
	}
}
#endif

void movePlayer(struct Player *player,int direction)
{
	const int dx[4]={1,0,-1,0};
	const int dy[4]={0,MAPWIDTH,0,-MAPWIDTH};

	if(direction<0) return;

	player->cell+=dx[direction];
	player->cell+=dy[direction];
}

int directionToTarget(int sx,int sy,int tx,int ty)
{
	int dx=sx-tx,dy=sy-ty;
	if(dx<0) dx=-dx;
	if(dy<0) dy=-dy;
	if(dx+dy<=1) return -1;
	if(dx>dy) return sx>tx?0:2;
	return sy>ty?1:3;
}

int distanceToTarget(int sx,int sy,int tx,int ty)
{
	int dx=sx-tx,dy=sy-ty;
	if(dx<0) dx=-dx;
	if(dy<0) dy=-dy;
	return dx+dy;
}


struct Player *calculateNearestHero(int sx,int sy)
{
	int i;

	struct Player *closest=hero+0;
	int closestDistance=MAPWIDTH+MAPHEIGHT;
	for(i=0;i<heroCount;i++) {
		int tx=hero[i].cell%MAPWIDTH;
		int ty=hero[i].cell/MAPWIDTH;
		int d=distanceToTarget(sx,sy,tx,ty);

		if(d<closestDistance) {
			closest=hero+i;
			closestDistance=d;
		}
	}

	return closest;
}

void planEnemy(struct Player *source)
{
	// choose potion, heal, melee attack, range attack
	struct Player *target;
	int mobility;
	int type=source->type&127;
	int tx,ty,sx,sy;
	int method=AT_PHYSICAL;
	int attack=calculateAttackPower(source,method);

	if(source->hp==0) return;	// dead!
	mobility=playerType[source->type].mobility;
	mobility-=weaponType[source->type].mobility;
	mobility-=armorType[source->type].mobility;
	//calculateReach(source->cell,mobility);
	// choose heal, attack
	// movement
	sx=source->cell%MAPWIDTH;
	sy=source->cell/MAPWIDTH;
	target=calculateNearestHero(sx,sy);
	tx=target->cell%MAPWIDTH;
	ty=target->cell/MAPWIDTH;
	while(mobility>0) {
		int direction;

		sx=source->cell%MAPWIDTH;
		sy=source->cell%MAPHEIGHT;
		direction=directionToTarget(sx,sy,tx,ty);
		movePlayer(source,direction);
		mobility--;
	}

	// apply attack
	attackPlayer(target,attack,method);
}

void updateEnemies()
{
	int i;
	for(i=0;i<enemyCount;i++) {
		planEnemy(enemy+i);
	}
}
