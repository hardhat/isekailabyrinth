#define byte unsigned char

#include "actions.h"
#include "player.h"
#include "level.h"

struct Player hero[6];
int heroCount;
struct Player enemy[6];
int enemyCount;

char reachMap[MAPCOUNT];

// factors in level, playerType, weaponType, armorType
void calculatePlayerBuffs(struct Player *player)
{
	const struct Buffs *base=playerType+(player->type&127);
	const struct Buffs *weapon=weaponType+player->weapon;
	const struct Buffs *armor=armorType+player->armor;
	
	int level=player->level;

	player->exp=level+10;
	player->maxHp=base->baseHp+base->gainHp*level;
	player->maxHp+=weapon->baseHp+weapon->gainHp*level;
	player->maxHp+=armor->baseHp+armor->gainHp*level;

	player->maxMp=base->baseMp+base->gainMp*level;
	player->maxMp+=weapon->baseMp+weapon->gainMp*level;
	player->maxMp+=armor->baseMp+armor->gainMp*level;

}

// returns exp gained from attacking.
int attackPlayer(struct Player *target, int power, int method)
{
	int health=target->hp;
	int level=target->level;

	const struct Buffs *base=playerType+(target->type&127);
	const struct Buffs *weapon=weaponType+target->weapon;
	const struct Buffs *armor=armorType+target->armor;

	power-=base->baseDef[method]+base->gainDef[method]*level;
	power-=weapon->baseDef[method]+weapon->gainDef[method]*level;
	power-=armor->baseDef[method]+armor->gainDef[method]*level;

	if(power<0) {
		showMessage("No Effect");
		return 0;
	}
	if(method == AT_HOLY) {
		target->hp+=power;
	} else {
		// TODO: apply luck here to dodge
		target->hp-=power;
		if(target->hp<=0) {
			showMessage("Target dies");
			target->hp=0;
			return target->level;
		}
	}

	return 0;
}

int calculateAttackPower(struct Player *source, int method)
{
	int level=source->level;
	int power=0;
	
	const struct Buffs *base=playerType+source->type;
	const struct Buffs *weapon=weaponType+source->weapon;
	const struct Buffs *armor=armorType+source->armor;

	power-=base->baseAtk[method]+base->gainAtk[method]*level;
	power-=weapon->baseAtk[method]+weapon->gainAtk[method]*level;
	power-=armor->baseAtk[method]+armor->gainAtk[method]*level;

	if(power<0) {
		showMessage("No Effect");
		return 0;
	}

	return 0;
}

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

void movePlayer(struct Player *player,int direction)
{
	const int dx[4]={1,0,-1,0};
	const int dy[4]={0,MAPWIDTH,0,-MAPWIDTH};

	if(direction<0) return;

	player->cell+=dx[direction];
	player->cell+=dy[direction];
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

void planPlayer(struct Player *source)
{
	// choose potion, heal, melee attack, range attack
	struct Player *target;
	int mobility;
	int type=source->type&127;
	int tx,ty,sx,sy;
	int method=AT_PHYSICAL;
	int attack=calculateAttackPower(source,method);

	mobility=playerType[source->type].mobility;
	mobility-=weaponType[source->type].mobility;
	mobility-=armorType[source->type].mobility;
	calculateReach(source->cell,mobility);
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

