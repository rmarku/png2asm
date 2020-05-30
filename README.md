# png2asm

This program convert an png image to a GNU compatible ASM file.

From a png like this:

![](nave.png)

invoquing 

```shell script
png2asm nave.png nave.s
```

to assembly like this:

```asm
.text
.global nave

nave:
    .xword 32 	// width
    .xword 15 	// height
    .byte 0x00	// R
    .byte 0x00	// G
    .byte 0x00	// B
    .byte 0x00	// A
    .byte 0x00	// R
    .byte 0x00	// G
    .byte 0x00	// B
    .byte 0x00	// A
    .byte 0x00	// R
```