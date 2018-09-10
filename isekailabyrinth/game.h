enum GameMode {
	M_MENU,
	// Action
	M_MAP,
	M_EQUIP,
	M_BATTLE,
	M_BREW,
	M_SHOP,
	// Game Over
	M_SUMMARY,
};

enum StatusType {
	STAT_DEAD,
	STAT_NORMAL,
	STAT_ENRAGED,
	STAT_POISONED,
	STAT_PARALIZED,
	STAT_ASLEEP,
	STAT_STONE,
};

enum SpellType {
	ST_WATER,
	ST_FIRE,
	ST_EARTH,
	ST_WIND,
	ST_LIGHTNING,
	ST_HOLY,
	ST_SPACE,
};

enum SpellLevel {
	SL_BALL,
	SL_WALL,
	SL_STORM,

	SL_EXPLOSION,
	SL_BARRIER,
	SL_DISASTER,

	SL_CHAOS,
	SL_FORTRESS,
	SL_CALAMITY,
};

enum PlayerType {
	PT_FIGHTER,
	PT_MAGE,
	PT_PREIST,
	PT_MAGICALSWORDSMAN,	// balanced, but more exp to level up
	PT_THEIF,
};

enum EnemyType {
	ET_SLIME = 128,
	ET_BEE,
	ET_NEEDLEWOOD,
	ET_SLOWRABBIT,
	ET_KOBOLD,
	ET_CATERPILLER,
	ET_FLYTRAP,
	ET_BEEPSHEEP,
	ET_GOBLIN,
	ET_ANT,
	ET_NATIVEOLIVE,
	ET_ESCAPEGOAT,
	ET_ORC,
	ET_SPIDER,
	ET_RUBSHRUB,
	ET_MABREEM,
	ET_TROLL,
	ET_CYCLOPS,
	ET_MINOTAR,
	
};

enum WeaponType {
	WT_FIST,
	WT_DAGGER,
	WT_SHORTSWORD,
	WT_RAPIER,
	WT_DUALSWORDS,
	WT_LONGSWORD,
	WT_HAMMER,
	WT_AXE,
	WT_BOW,
	WT_DURANDAL,
	WT_EXCALIBUR,
	WT_MASAMUNE,
	WT_WALLACE,
	WT_GOUJIAN,
	WT_CHILJIDO,
	WT_KUSANAGI,
};

struct Player {
	byte type;
	byte status;
	byte level;
	byte affinity; 	// water, fire, air, earth, light, dark, space, holy
	byte att;
	byte def;
	byte agi;		// dodge, etc.
	byte luck;		// critical hit, etc.
	byte maxHp;
	byte maxMp;

	byte hp;
	byte mp;
	
	byte exp;

	byte x,y;
};

extern struct Player hero[12];
extern struct Player enemy[12];
extern byte enemyCount;

enum InventoryType {
	MT_COIN,

	MT_CORE,

	MT_HEALTHPOTION,
	MT_MAGICPOTION,
	MT_STATUSPOTION,

	MT_RING,
	MT_BOOTS,
	MT_HAT,
	MT_JACKET,
	MT_GLOVES,
	MT_GREEVES,
};

extern struct Inventory {
	byte type;
	int quantity;
} inventory[16];
