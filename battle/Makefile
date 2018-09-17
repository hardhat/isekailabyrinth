OBJ=player.rel level.rel main.rel

all: result.rom

main.rel: main.c
	sdcc -I.. -mz80 --opt-code-speed --max-allocs-per-node 4000 -c --std-c99 main.c

player.rel: player.c
	sdcc -I.. -mz80 -c --std-c99 player.c

level.rel: level.c
	sdcc -I.. -mz80 -c --std-c99 level.c

result.rom: $(OBJ)
	sdcc -mz80 --code-loc 0x8024 --data-loc 0x7000 --no-std-crt0 ../crtcv.rel ../cvlib.lib ../getput.lib $(OBJ)
	psp-objcopy --input-target=ihex --output-target=binary crtcv.ihx result.rom
	ls -l *.rom

clean:
	-rm *.rel *.asm *.lst *.sym *.noi *.map *.lk *.ihx

