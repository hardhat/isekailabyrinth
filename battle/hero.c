#define byte unsigned char

#include "player.h"

void initHeroParty()
{
	heroCount=1;
	hero[0].level=1;
	hero[0].type=0;	// knight
	hero[0].armor=0;	// plain clothes
	hero[0].weapon=0;	// fists
	hero[0].cell=0;
	hero[0].exp=(1+hero[0].level)*hero[0].level/2;
	calculatePlayerBuffs(hero);
}
