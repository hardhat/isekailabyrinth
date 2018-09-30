#define byte unsigned char

#include "actions.h"
#include "player.h"
#include "level.h"

struct Player hero[6];
int heroCount;
struct Player enemy[6];
int enemyCount;

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
