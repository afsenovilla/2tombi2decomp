// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: psyz (github.com/Xeeynamo/psyz, MIT) decomp/src/libcd/iso9660.c, function CD_cachefile.
#include "common.h"
extern char D_8001C54C[];
extern char D_8001C4EC[];
extern char D_8001C50C[];
extern char D_8001C530[];
extern s32 D_8001C52C[];
extern s32 D_8001C528[];
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
extern int D_800ABFC4;
extern int D_800AC2D4;
extern CdlFILE D_80102768[64];
extern CdlDIR D_80102D68[128];
extern unsigned char D_80104368[0x800];
int D_8008C1EC(int n_sectors, int sector_no, unsigned char* ptr);
int D_8008C1EC(int n_sectors, int sector_no, unsigned char* ptr);

s32 func_8008BF50(s32 dirNum) {
    LBA entryLba;
    u8* entry;
    s32 i;
    short* namePtr;
    if (dirNum == D_800AC2D4) {
        return 1;
    }
    if (D_8008C1EC(1, (D_80102D68 - 1)[dirNum].lba.addr, D_80104368) != 1) {
        if (D_800ABFC4 > 0) {
            printf(D_8001C4EC);
        }
        return -1;
    }
    if (D_800ABFC4 > 1) {
        printf(D_8001C50C);
    }
    entry = D_80104368;
    i = 0;
    while (entry < D_80104368 + sizeof(D_80104368)) {
        if (entry[0] == 0) {
            break;
        }
        entryLba.i = ((LBA*)&entry[2])->i;
        CdIntToPos(entryLba.addr, &D_80102768[i].pos);
        ((LBA*)&D_80102768[i].size)->i = ((LBA*)&entry[0xA])->i;
        switch (i) {
        case 0:
            namePtr = (short*)D_80102768[i].name;
            __builtin_memcpy(namePtr, D_8001C528, 2);
            break;
        case 1:
            namePtr = (short*)D_80102768[i].name;
            __builtin_memcpy(namePtr, D_8001C52C, 3);
            break;
        default:
            memcpy(D_80102768[i].name, &entry[0x21], entry[0x20]);
            D_80102768[i].name[entry[0x20]] = '\0';
            break;
        }
        if (D_800ABFC4 > 1) {
            printf(D_8001C530, D_80102768[i].pos.minute,
                   D_80102768[i].pos.second, D_80102768[i].pos.sector, D_80102768[i].size,
                   D_80102768[i].name);
        }
        entry += entry[0];
        if (++i >= 64) {
            break;
        }
    }
    D_800AC2D4 = dirNum;
    if (i < 64) {
        D_80102768[i].name[0] = '\0';
    }
    if (D_800ABFC4 > 1) {
        printf(D_8001C54C, i);
    }
    return 1;
}
