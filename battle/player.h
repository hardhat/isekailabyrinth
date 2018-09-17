struct Player {
	byte type;
	byte level;
	byte cell; // position on the map
	byte hp;
	byte mp;
	byte maxHp;
	byte maxMp;
	byte armor;
	byte weapon;
	byte exp;	// experience needed to level up
};

struct Buffs {
	const char *name;
	char mobility;
	byte baseHp;
	byte gainHp;
	byte baseMp;
	byte gainMp;
	byte afinity;	// magic
	byte resistance[8];	// magic
	byte luck;	// dodge or critical hit likelyhood.  out of 255
};

enum AffinityType {
	AT_PHYSICAL,
	AT_FIRE,
	AT_WATER,
	AT_EARTH,
	AT_WIND,
	AT_LIGHTNING,
	AT_HOLY,
	AT_SPACE,
};

enum AffinityMask {
	AM_PHYSICAL=1,
	AM_FIRE=2,
	AM_WATER=4,
	AM_EARTH=8,
	AM_WIND=16,
	AM_LIGHTNING=32,
	AM_HOLY=64,
	AM_SPACE=128,
};

extern struct Buffs *playerType, *armorType, *weaponType;
extern int maxPlayerType, maxArmorType, maxWeaponType;

// factors in level, playerType, weaponType, armorType
void calculatePlayerBuffs(struct Player *player);
// returns exp gained from attacking.
int attackPlayer(struct Player *target, int power, int type);

