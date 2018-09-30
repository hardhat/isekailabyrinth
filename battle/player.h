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
	byte afinity;	// method: AT_* physical, magic type
	byte baseAtk[8];	// method
	byte gainAtk[8];	// method
	byte baseDef[8];	// method
	byte gainDef[8];	// method
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

extern const struct Buffs playerType[], armorType[], weaponType[];
extern const int maxPlayerType, maxArmorType, maxWeaponType;

#define MAXHERO 6
extern struct Player hero[MAXHERO];
extern int heroCount;
#define MAXENEMY 6
extern struct Player enemy[MAXENEMY];
extern int enemyCount;

// factors in level, playerType, weaponType, armorType
void calculatePlayerBuffs(struct Player *player);
// returns exp gained from attacking.
int attackPlayer(struct Player *target, int power, int type);
// returns attack with critical, etc. built in
int calculateAttackPower(struct Player *source, int method);


// enemy.c
void updateEnemies();
