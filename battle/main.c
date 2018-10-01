#include <stdlib.h>
#include <stdlib.h>
#include <stdlib.h>
#include <coleco.h>
#include <getput1.h>
#include <comp.h>

#include "level.h"
#include "player.h"
#include "actions.h"

#define M_BATTLE 0

const char *rankName[]={
	"Knight",
	"Baron",
	"Viscount",
	"Earl",
	"Marquis",
	"Duke",
	"Archduke",
	"Despot",
	"King",
	"High King",
	"Emperor"
};
#define RANKCOUNT 11

const byte spritepattern[]={
	0xf0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0xf0,0,0,0,0,0,0,0,0,
	0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
	0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,
};

const byte tilepattern[]={
	0xaa,0x55,0xaa,0x55,0xaa,0x55,0xaa,0x55,
};

byte cursorx,cursory;
byte enemyReady;
extern struct EnemyPlan enemyPlan;


void init()
{
	byte buffer[64];
	int i;
	screen_off();
    screen_mode_2_bitmap();
	sprites_16x16();
    //load_colorrle(COLORRLE);
	fill_vram(0,6144,0xf4);
	for(i=0x1024;i<1536;i+=8) {
		put_vram(8912+i,tilepattern,8);
	}
    //load_patternrle(PATTERNRLE);
    //load_namerle(NAMERLE);
    load_ascii();

#if 1	// for emulators, works without this on the real hardware.
	for(i=0;i<2048;i+=64) {
		get_vram(i,buffer,64);
		put_vram(2048+i,buffer,64);
		put_vram(4096+i,buffer,64);
		get_vram(8192+i,buffer,64);
		put_vram((8192+2048)+i,buffer,64);
		put_vram((8192+4096)+i,buffer,64);
	}
#endif

    //load_spatternrle(SPATTERNRLE);
	put_vram(0xc800,spritepattern,32);
	screen_on();
}

void newgame()
{
	int i;
	cursorx=128-8;
	cursory=64;

	sprites[0].y=cursory;
	sprites[0].x=cursorx;
	sprites[0].pattern=0;
	sprites[0].colour=1;

	for(i=1;i<32;i++) {
		sprites[i].y=192;
		sprites[i].x=0;
		sprites[i].pattern=0;
		sprites[i].colour=1;
	}
	
	enemyReady=1;
}

const byte tileList[4][16]={
	//MT_EMPTY,
	{0x80,0x88,0x90,0x98,
	 0x81,0x89,0x91,0x99,
	 0x82,0x8a,0x92,0x9a,
	 0x83,0x8b,0x93,0x9b},
	//MT_HERO,
	{0x84,0x8c,0x94,0x9c,
	 0x85,'H' ,'E' ,0x9d,
	 0x86,'R' ,'O' ,0x9e,
	 0x87,0x8f,0x97,0x9f},
	//MT_ENEMY,
	{0xa0,0xa8,0xb0,0xb8,
	 0xa1,'E' ,'N' ,0xb9,
	 0xa2,'E' ,'M' ,0xba,
	 0xa3,'Y' ,0xb3,0xbb},
};

void drawMapTile(byte x,byte y,byte tile)
{
	put_frame(tileList[tile],(x<<2)+2,(y<<2),4,4);
}

void drawLine(int y)
{
	byte *from=map+y*MAPWIDTH;
	int i;

	for(i=0;i<6;i++) {
		drawMapTile(i,y,from[i]);
	}
}

void drawMap(int pass)
{
	int i,y;
	int health=0;

	if(pass==0) {
		for(y=0;y<3;y++) {
			drawLine(y);
		}
	} else if(pass==1) {
		for(y=3;y<6;y++) {
			drawLine(y);
		}
	}
	for(i=0;i<heroCount;i++) {
		health+=hero[i].hp;
	}
	if(health==0) {
		print_at(8,20," GAME OVER! ");
		if(joypad_1&FIRE1) newgame();
	}
}

void updateMap(int pass)
{
	//byte i,j;
	
	switch(pass) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		updateLevelMap();
		
		if(enemyReady) updateEnemy(enemyPlan.mode);
		break;
	}
}

void updateSprites()
{

	if(joypad_1&LEFT) cursorx-=2;
	if(cursorx<32) cursorx=32;
	if(joypad_1&RIGHT) cursorx+=2;
	if(cursorx>224) cursorx=224;
	if(joypad_1&UP) cursory-=2;
	if(cursory<16) cursory=16;
	if(joypad_1&DOWN) cursory+=2;
	if(cursory>144) cursory=144;

	// cursor
	sprites[0].y=cursory;
	sprites[0].x=cursorx;

	//updatesprites(0,30);
	put_vram(0x1b00,sprites,128);
}

void showMessage(const char *message)
{
	print_at(0,1,(char *)message);
}

void main()
{
	int pass=0;
	int drawMode=0;
	int gameMode=M_BATTLE;

	disable_nmi();
	
	init();
	newgame();
	cls();
	drawMap(0);
	drawMap(1);
	
	enable_nmi();

	while(1) {
		disable_nmi();
		// update the state of the character.
		if(gameMode==M_BATTLE) {
			updateSprites();
			updateMap(pass);
		} else {
			fill_vram(0x1b00,204,128);
		}

		if(drawMode==1) {
			drawMap(pass);
		}
		
		pass++;
		if(pass==3) {
			drawMode=0;
			pass=0;
		}

		enable_nmi();
		delay(1);
	}
}

void nmi()
{
}

const byte sound1[]={0xff};

const struct Sound {
	const byte *sound;
	byte *table;
} snd_table[]={
	{sound1,SOUNDAREA1},
};

