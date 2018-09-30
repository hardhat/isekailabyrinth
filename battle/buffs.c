#define byte unsigned char

#include "player.h"

const struct Buffs playerType[]={
	{"KNIGHT", 1,7,3,0,1, 3,{5,2,0,0,0,0,0,0},{3,2,1,1, 1,1,1,0},{7,3,0,0,0,0,0,0},{3,2,0,0, 0,0,0,0},50},
	{"WARRIOR",2,3,3,0,2, 5,{5,0,2,0,0,0,0,0},{2,1,2,1, 1,1,1,0},{5,3,0,0,0,0,0,0},{2,0,3,0, 0,0,0,0},60},
	{"RANGER", 3,3,2,0,2, 9,{5,0,0,4,0,0,0,0},{3,1,1,2, 1,1,1,0},{4,0,0,4,0,0,0,0},{3,0,0,3, 0,0,0,0},70},
	{"ROGUE",  4,5,1,0,1,17,{2,0,0,0,3,0,0,0},{2,1,1,1, 2,1,1,0},{3,0,0,0,4,0,0,0},{2,0,0,0, 2,0,0,0},100},
	{"MAGE",   3,4,2,7,3,31,{2,4,4,4,4,1,0,0},{1,3,3,3, 3,3,0,0},{2,1,1,1,1,1,0,0},{1,1,1,1, 1,1,0,0},60},
	{"CLERIC", 3,1,1,7,3,65,{2,0,0,0,0,0,4,0},{1,1,1,1, 1,1,4,0},{2,0,0,0,0,4,0,0},{1,1,1,1, 1,1,0,0},100},
	{"GOBLIN", 1,2,2,},
	{"ORC",    2,8,2,},
	{"CYCLOPS",1,8,3,},
};
const int maxPlayerType=9;

const struct Buffs weaponType[]={
	{"STICK",0,0,0,0,1,},
	{"BROAD SWORD",7,0,0,0,1,},
	{"RAPIER",5,0,0,0,1,},
	{"SHORT SWORD",3,0,0,0,1,},
	{"DAGGAR",2,0,0,0,1,},
	{"MAGIC STAFF",2,0,5,0,1,},
	{"HEALING WAND",2,0,8,0,65,},
	{"BLOWING STAFF",2,0,5,0,16,},
	{"SKY WAND",5,0,9,0,16,81,},
};
const int maxWeaponType=9;

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

