#include <stdlib.h>
#include <stdlib.h>
#include <stdlib.h>
#include <coleco.h>
#include <getput1.h>
#include <comp.h>

extern const byte bitmapColRLE[];
extern const byte zx7BitmapColor[];
extern const byte zx7BitmapPattern[];
extern byte NAMERLE[];
extern byte SPATTERNRLE[];
extern byte PATTERNRLE[];
extern byte COLORRLE[];
extern byte SPRITESINIT[];
extern int SPRITESINITSIZE;


//int drawScreen; // double buffered drawing.
byte gameMode;
byte cursorx,cursory;
byte frame;

enum MapType {
	MT_GRASS,
	MT_BUSH,
	MT_ROCK,
	MT_WATER,
};

struct Map {
	byte row[15];
} map[11];

const char *initialMap[]={
	"===============",
	"=www......ww..=",
	"=www.....www..=",
	"=........=www.=",
	"=........=....=",
	"=..=...h......=",
	"=.............=",
	"=..ww==..www..=",
	"=.ww...www.ww.=",
	"=..ww...www...=",
	"===============",
};

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

void showtitle()
{
	screen_off();
	screen_mode_2_bitmap();
	//show_picture(bitmapColRLE);
	zx7(0x0000,zx7BitmapPattern);
	zx7(0x2000,zx7BitmapColor);
	screen_on();
}

void init()
{
	byte buffer[64];
	int i;
	screen_off();
    screen_mode_2_bitmap();
	sprites_16x16();
    load_colorrle(COLORRLE);
    load_patternrle(PATTERNRLE);
    //load_namerle(NAMERLE);
	fill_vram(0x1800,6144,20);
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

    load_spatternrle(SPATTERNRLE);
	screen_on();
}

void newgame()
{
	int i,j;
	budCount=0;
	flowerCount=0;
	flowerTimer=0;
	
	for(j=0;j<11;j++) {
		for(i=0;i<15;i++) {
			int t=MT_GRASS;
			switch(initialMap[j][i]) {
			case '=':
				t=MT_BUSH;
				break;
			case 'r':
				t=MT_ROCK;
				break;
			case 'w':
				t=MT_WATER;
				break;
			}
			map[j].row[i]=t;
		}
	}
	cursorx=128-8;
	cursory=64;

	sprites[0].y=cursory;
	sprites[0].x=cursorx;
	sprites[0].pattern=7*4;
	sprites[0].colour=15;

	for(i=1;i<32;i++) {
		sprites[i].y=192;
		sprites[i].x=0;
		sprites[i].pattern=0;
		sprites[i].colour=1;
	}
}

const byte tileList[6][4]={
	//MT_GRASS,
	{0x80,0x88,0x81,0x89},
	//MT_BUSH,
	{0x82,0x8a,0x83,0x8b},
	//MT_ROCK,
	{0x84,0x8c,0x85,0x8d},
	//MT_WATER,
	{0x86,0x8e,0x87,0x8f},
};

void drawMapTile(byte x,byte y,byte tile)
{
	put_frame(tileList[tile],x+x+2,y+y,2,2);
	//int o=0x1802+(x<<1)+(x<<6);
	//put_vram(o,tileList[tile],2);
	//put_vram(o+32,tileList[tile]+2,2);
}

void drawLine(int y)
{
	byte buffer[64];
	byte *buf=buffer;
	byte *from=map[y].row;
	int i;

	buffer[30]=0x20;
	buffer[31]=0x20;
	buffer[62]=0x20;
	buffer[63]=0x20;
	
	for(i=0;i<15;i++) {
		char c=from[i];
		*buf=tileList[c][0];
		buf[32]=tileList[c][2];
		buf++;
		*buf=tileList[c][1];
		buf[32]=tileList[c][3];
		buf++;
	}
	// keep away from the extreme left, in case it is cut off.
	put_vram((0x1802)+(y<<6),buffer,64);
}

void drawMap(int pass)
{
	int y;
	if(pass==0) {
		for(y=0;y<6;y++) {
			drawLine(y);
		}
	} else if(pass==1) {
		for(y=6;y<11;y++) {
			drawLine(y);
		}
	}
	if(health==0) {
		print_at(8,20," GAME OVER! ");
		if(joypad_1&FIRE1) newgame();
	}
}

void updateMap(int pass)
{
	byte i,j;
	
	switch(pass) {
	case 0:
		break;
	case 1:
		break;
	case 2:
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
	
	frame++;
}

void main()
{
	int pass=0;
	int drawMode=0;
#if 1
	disable_nmi();
	showtitle();
	enable_nmi();
	delay(120);
	//disable_nmi();
#endif

	disable_nmi();
	screen_mode_2_bitmap();
    screen_on();
	
	init();
	newgame();
	cls();
	drawMap(0);
	drawMap(1);
	gameMode=M_FIELD;

	while(1) {
		disable_nmi();
		// update the state of the character.
		if(gameMode==M_FIELD) {
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

