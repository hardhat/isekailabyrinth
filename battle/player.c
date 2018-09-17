#define byte unsigned char

#include "actions.h"
#include "player.h"
#include "level.h"

char reachMap[MAPCOUNT];

// factors in level, playerType, weaponType, armorType
void calculatePlayerBuffs(struct Player *player)
{
	struct Buffs *base=playerType+player->type;
	struct Buffs *weapon=weaponType+player->weapon;
	struct Buffs *armor=armorType+player->armor;
	
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

	power-=playerType[target->type].resistance[method];
	power-=weaponType[target->weapon].resistance[method];
	power-=armorType[target->armor].resistance[method];

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

void planPlayer(struct Player *source)
{
	// choose potion, heal, melee attack, range attack
	int mobility;
	int healWorth,healCell;
	int attackWorth,attackCell;
	int type=source->type&127;

	mobility=playerType[source->type].mobility;
	mobility-=weaponType[source->type].mobility;
	mobility-=armorType[source->type].mobility;
	calculateReach(source->cell,mobility);
	// choose heal, attack
	// movement

	// TODO: apply luck here for critical hit
	// apply attack
	
}

