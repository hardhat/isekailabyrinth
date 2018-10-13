#define byte unsigned char

#include "level.h"
#include "player.h"

struct EnemyPlan enemyPlan;

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

void resetEnemy()
{
	enemyCount=0;
}

int newEnemy(int type, int level, int armor, int weapon, int cell)
{
	int id=enemyCount++;
	struct Player *player=enemy+id;

	if(id>6) return 0;
	player->type=type;
	player->level=level;
	player->armor=armor;
	player->weapon=weapon;
	player->cell=cell;
	calculatePlayerBuffs(player);
	player->mp=player->maxMp;
	player->hp=player->maxHp;
}

void movePlayer(struct Player *player,int direction)
{
	const int dx[4]={1,0,-1,0};
	const int dy[4]={0,MAPWIDTH,0,-MAPWIDTH};

	if(direction<0 || direction==255) return;

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
	int type=source->type&127;

	enemyPlan.method=AT_PHYSICAL;
	enemyPlan.power=calculateAttackPower(source,enemyPlan.method);

	if(source->hp==0) return;	// dead!
	enemyPlan.mobility=playerType[type].mobility;
	enemyPlan.mobility-=weaponType[type].mobility;
	enemyPlan.mobility-=armorType[type].mobility;

	//calculateReach(source->cell,mobility);
	// choose heal, attack
}

void moveEnemy(struct Player *source)
{
	int tx,ty,sx,sy;

	// movement
	sx=source->cell%MAPWIDTH;
	sy=source->cell/MAPWIDTH;
	enemyPlan.target=calculateNearestHero(sx,sy);
	tx=enemyPlan.target->cell%MAPWIDTH;
	ty=enemyPlan.target->cell/MAPWIDTH;
	
	sx=source->cell%MAPWIDTH;
	sy=source->cell%MAPHEIGHT;
	enemyPlan.direction=directionToTarget(sx,sy,tx,ty);
	enemyPlan.mobility--;
}

struct EnemyPlan *updateEnemy(int mode)
{
	struct Player *active;
	
	switch(mode) {
	case EM_NEWTURN:
		enemyPlan.mode=EM_MOVE;
		enemyPlan.id=0;
		// fall through
	case EM_MOVE:
		active=enemy+enemyPlan.id;
		enemyPlan.direction=255;
		planEnemy(active);
		
		enemyPlan.mode=EM_MOVING;
		// fall through
	case EM_MOVING:
		active=enemy+enemyPlan.id;
		movePlayer(active,enemyPlan.direction);

		if(enemyPlan.mobility>0) {
			moveEnemy(active);
			if(enemyPlan.direction!=255) break;
		}
		enemyPlan.mode=EM_ACTION;
		break;
	case EM_ACTION:	// was planned at the plan step
		enemyPlan.mode=EM_ACTING;
		break;
	case EM_ACTING:	// animating
		enemyPlan.mode=EM_APPLY;
		break;
	case EM_APPLY:	// damage dealt
		attackPlayer(enemyPlan.target,enemyPlan.power,enemyPlan.method);

		if(enemyPlan.id+1<enemyCount) {
			enemyPlan.id++;
			enemyPlan.mode=EM_MOVE;
		} else {
			enemyPlan.mode=EM_DONETURN;
		}
		break;
	case EM_DONETURN:
		break;
	}
	
	return &enemyPlan;
}
