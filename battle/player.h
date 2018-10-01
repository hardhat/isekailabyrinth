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

enum EnemyMode {
	EM_NEWTURN,	// Start planning a new turn for the enemies
	EM_MOVE,	// Making a plan to move
	EM_MOVING,	// Animation system is waiting for completion on this move
	EM_ACTION,	// Making a plan for an action
	EM_ACTING,	// Animation system is waiting for completion of this action
	EM_APPLY,	// Apply the action
	EM_DONETURN,// This enemy is done
};

struct EnemyPlan {
	byte mode;
	
	byte id;		// current enemy that is active.
	byte mobility;	// how much movement this enemy has left before their action
	byte direction;		// direction to move to in mode EM_MOVING
	
	struct Player *target;	// what we plan to deliver
	byte power;
	byte method;
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

// hero.c
void initHeroParty();

// enemy.c
struct EnemyPlan *updateEnemy(int mode);
