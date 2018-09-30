#define byte unsigned char

#include "player.h"

const struct Buffs playerType[]={
	{"KNIGHT", 1,7,3,0,1, 3,{5,2,0,0,0,0,0,0},{3,2,1,1, 1,1,1,0},{7,3,0,0,0,0,0,0},{3,2,0,0, 0,0,0,0},50},
	{"WARRIOR",2,3,3,0,2, 5,{5,0,2,0,0,0,0,0},{2,1,2,1, 1,1,1,0},{5,3,0,0,0,0,0,0},{2,0,3,0, 0,0,0,0},60},
	{"RANGER", 3,3,2,0,2, 9,{5,0,0,4,0,0,0,0},{3,1,1,2, 1,1,1,0},{4,0,0,4,0,0,0,0},{3,0,0,3, 0,0,0,0},70},
	{"ROGUE",  4,5,1,0,1,17,{2,0,0,0,3,0,0,0},{2,1,1,1, 2,1,1,0},{3,0,0,0,4,0,0,0},{2,0,0,0, 2,0,0,0},100},
	{"MAGE",   3,4,2,7,3,31,{2,4,4,4,4,1,0,0},{1,3,3,3, 3,3,0,0},{2,1,1,1,1,1,0,0},{1,1,1,1, 1,1,0,0},60},
	{"CLERIC", 3,1,1,7,3,65,{2,0,0,0,0,0,4,0},{1,1,1,1, 1,1,4,0},{2,0,0,0,0,4,0,0},{1,1,1,1, 1,1,0,0},100},
	{"GOBLIN",},
	{"ORC",},
};
const int maxPlayerType=8;

const struct Buffs weaponType[]={
	{"BROAD SWORD",},
	{"RAPIER",},
	{"SHORT SWORD",},
	{"DAGGAR",},
	{"MAGIC STAFF",},
	{"HEALING WAND",},
};
const int maxWeaponType=6;

const struct Buffs armorType[]={
	{"PLAIN CLOTHES",},
	{"LEATHER ARMOR",},
	{"HARD LEATHER ARMOR",},
	{"CHAIN MAIL",},
	{"PLATE ARMOR",},
	{"MAGIC ROBE",},
	{"HOLY ROBE",},
};
const int maxArmorType=7;

