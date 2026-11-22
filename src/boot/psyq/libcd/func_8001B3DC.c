// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/iso9660.c, function CD_cachefile.
#include "common.h"
extern char D_800109B0[];
extern char D_80010950[];
extern char D_80010970[];
extern char D_80010994[];
extern s32 D_80010990[];
extern s32 D_8001098C[];
typedef unsigned char u_char;
typedef unsigned long u_long;
typedef struct {
 u_char minute;
 u_char second;
 u_char sector;
 u_char track;
} CdlLOC;
typedef struct {
 CdlLOC pos;
 u_long size;
 char name[16];
} CdlFILE;
CdlLOC *CdIntToPos(int i, CdlLOC *p) ;
typedef union {
    int addr;
    CdlLOC i;
} LBA;
typedef struct {
    int num;
    int parentNum;
    LBA lba;
    char name[0x20];
} CdlDIR;
extern int D_800268D8;
extern int D_80026BE8;
extern CdlFILE D_80039EE0[64];
extern CdlDIR D_8003A4E0[128];
extern unsigned char D_8003BAE0[0x800];
int D_8001B678(int n_sectors, int sector_no, unsigned char* ptr);
int D_8001B678(int n_sectors, int sector_no, unsigned char* ptr);

s32 func_8001B3DC(s32 dirNum) {
    LBA entryLba;
    u8* entry;
    s32 i;
    short* namePtr;
    if (dirNum == D_80026BE8) {
        return 1;
    }
    if (D_8001B678(1, (D_8003A4E0 - 1)[dirNum].lba.addr, D_8003BAE0) != 1) {
        if (D_800268D8 > 0) {
            printf(D_80010950);
        }
        return -1;
    }
    if (D_800268D8 > 1) {
        printf(D_80010970);
    }
    entry = D_8003BAE0;
    i = 0;
    while (entry < D_8003BAE0 + sizeof(D_8003BAE0)) {
        if (entry[0] == 0) {
            break;
        }
        entryLba.i = ((LBA*)&entry[2])->i;
        CdIntToPos(entryLba.addr, &D_80039EE0[i].pos);
        ((LBA*)&D_80039EE0[i].size)->i = ((LBA*)&entry[0xA])->i;
        switch (i) {
        case 0:
            namePtr = (short*)D_80039EE0[i].name;
            __builtin_memcpy(namePtr, D_8001098C, 2);
            break;
        case 1:
            namePtr = (short*)D_80039EE0[i].name;
            __builtin_memcpy(namePtr, D_80010990, 3);
            break;
        default:
            memcpy(D_80039EE0[i].name, &entry[0x21], entry[0x20]);
            D_80039EE0[i].name[entry[0x20]] = '\0';
            break;
        }
        if (D_800268D8 > 1) {
            printf(D_80010994, D_80039EE0[i].pos.minute,
                   D_80039EE0[i].pos.second, D_80039EE0[i].pos.sector, D_80039EE0[i].size,
                   D_80039EE0[i].name);
        }
        entry += entry[0];
        if (++i >= 64) {
            break;
        }
    }
    D_80026BE8 = dirNum;
    if (i < 64) {
        D_80039EE0[i].name[0] = '\0';
    }
    if (D_800268D8 > 1) {
        printf(D_800109B0, i);
    }
    return 1;
}
