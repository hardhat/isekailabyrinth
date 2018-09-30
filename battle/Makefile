OBJ=player.rel enemy.rel level.rel buffs.rel main.rel

all: result.rom

main.rel: main.c
	sdcc -I.. -mz80 --opt-code-speed --max-allocs-per-node 4000 -c --std-c99 main.c

player.rel: player.c actions.h player.h level.h
	sdcc -I.. -mz80 -c --std-c99 player.c

enemy.rel: enemy.c actions.h player.h level.h
	sdcc -I.. -mz80 -c --std-c99 enemy.c

level.rel: level.c level.h player.h
	sdcc -I.. -mz80 -c --std-c99 level.c

buffs.rel: buffs.c player.h
	sdcc -I.. -mz80 -c --std-c99 buffs.c

result.rom: $(OBJ)
	sdcc -mz80 --code-loc 0x8024 --data-loc 0x7000 --no-std-crt0 ../crtcv.rel ../cvlib.lib ../getput.lib $(OBJ)
	psp-objcopy --input-target=ihex --output-target=binary crtcv.ihx result.rom
	ls -l *.rom

clean:
	-rm *.rel *.asm *.lst *.sym *.noi *.map *.lk *.ihx

