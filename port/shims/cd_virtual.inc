/* ================================================================== libcd: a virtual disc (included by psyq.c)
 *
 * The player's disc is read as extracted files (game/usa/: the ISO9660 tree as the bootstrap extracts it; --data
 * DIR names another).  CdSearchFile opens the file and gives it a made-up position on a virtual disc: each file
 * gets its own range of 2048-byte sectors, so a Setloc anywhere inside a file (the game seeks into TOMBA2.DAT /
 * TOMBA2.IMG by sector offsets from TOMBA2.IDX) maps back to that file.  CdRead copies at once; the data-ready path
 * (CdControl ReadN / ReadS + CdReadyCallback + CdGetSector) delivers a few sectors per vblank. */
const char *port_data_dir = "game/usa";
int port_trace_cd;
int port_cd_open(const char *path) { (void)path; return -1; }
#define CD_FIRST_LBA 1000
typedef struct { char name[64]; int fd, lba, nsec; unsigned size; } CdFile;
static CdFile cd_files[64];
static int n_cd_files, cd_next_lba = CD_FIRST_LBA;
static int cd_pos;                     /* next LBA */
static void *cd_ready_cb, *cd_sync_cb, *cd_read_cb, *cd_data_cb;
static u8 cd_mode = 0x80, cd_last_com;
static int cd_reading;                 /* ReadN / ReadS in progress: sectors are delivered on vblanks */
static u8 cd_sector[2352];
static int cd_sector_off;              /* CdGetSector read offset into cd_sector (bytes) */

static void cd_call(void *fn, u32 a, u32 b) {
    void (*f)(u32, u32) = (void (*)(u32, u32))fn;
    if ((u32)fn >= 0x80000000u && (u32)fn < 0x80200000u) f = (void (*)(u32, u32))port_resolve_call((u32)fn, "cd callback");
    f(a, b);
}
static int up(int c) { return c >= 'a' && c <= 'z' ? c - 32 : c; }
static void lba_to_loc(int lba, u8 *p);
static CdFile *cd_find_lba(int lba) {
    for (int i = 0; i < n_cd_files; i++)
        if (lba >= cd_files[i].lba && lba < cd_files[i].lba + cd_files[i].nsec) return &cd_files[i];
    return 0;
}
int port_cd_read_sectors(int lba, int count, void *dst, int bytes) {
    u8 *d = dst;
    for (int i = 0; i < count; i++, d += bytes) {
        CdFile *f = cd_find_lba(lba + i);
        if (!f) { port_printf("[port] CD read of lba %d: no file there (frame %d)\n", lba + i, port_frame); return -1; }
        long long off = (long long)(lba + i - f->lba) * 2048;
        int skip = bytes > 2048 ? 12 : 0;    /* 2340-byte reads: the sector header (BCD position, mode 2) and the
                                                subheader (data, form 1), then the data (the game checks the position) */
        for (int k = 0; k < bytes; k++) d[k] = 0;
        if (skip) { lba_to_loc(lba + i, d); d[3] = 2; d[6] = d[10] = 0x08; }
        int got = port_pread(f->fd, d + skip, 2048, off);
        (void)got;
        if (port_trace_cd) port_printf("[port] cd: lba %d = %s sector %d\n", lba + i, f->name, lba + i - f->lba);
    }
    return 0;
}
static int bcd(u8 b) { return (b >> 4) * 10 + (b & 15); }
static u8 tobcd(int v) { return (u8)((v / 10) << 4 | (v % 10)); }
static int loc_to_lba(const u8 *p) { return (bcd(p[0]) * 60 + bcd(p[1])) * 75 + bcd(p[2]) - 150; }
static void lba_to_loc(int lba, u8 *p) { lba += 150; p[0] = tobcd(lba / 4500); p[1] = tobcd(lba / 75 % 60); p[2] = tobcd(lba % 75); p[3] = 0; }

typedef struct { u8 pos[4]; u32 size; char name[16]; } CdlFILE;
CdlFILE *CdSearchFile(CdlFILE *fp, char *name) {
    char rel[64]; int n = 0;
    const char *s = name;
    while (*s == '\\' || *s == '/') s++;
    for (; *s && *s != ';' && n < 63; s++) rel[n++] = *s == '\\' ? '/' : (char)up(*s);
    rel[n] = 0;
    CdFile *f = 0;
    for (int i = 0; i < n_cd_files; i++) {
        int k = 0; while (rel[k] && rel[k] == cd_files[i].name[k]) k++;
        if (!rel[k] && !cd_files[i].name[k]) { f = &cd_files[i]; break; }
    }
    if (!f) {
        char path[512]; int o = 0;
        for (const char *d = port_data_dir; *d && o < 400; d++) path[o++] = *d;
        path[o++] = '/';
        for (int k = 0; rel[k] && o < 510; k++) path[o++] = rel[k];
        path[o] = 0;
        int fd = port_open(path);
        if (fd < 0 || n_cd_files == 64) {
            port_printf("[port] CdSearchFile(\"%s\"): %s not found (frame %d)\n", name, path, port_frame);
            return 0;
        }
        f = &cd_files[n_cd_files++];
        for (int k = 0; k <= n; k++) f->name[k] = rel[k];
        f->fd = fd;
        f->size = (unsigned)port_filesize(fd);
        f->nsec = (int)((f->size + 2047) / 2048);
        f->lba = cd_next_lba;
        cd_next_lba += f->nsec + 16;
        port_printf("[port] CdSearchFile(\"%s\"): %s, %u bytes, virtual lba %d (frame %d)\n", name, path, f->size, f->lba, port_frame);
    }
    lba_to_loc(f->lba, fp->pos);
    fp->size = f->size;
    for (int k = 0; k < 16; k++) fp->name[k] = k < n ? rel[k] : 0;
    return fp;
}

int CdInit(void) { return 1; }
int CdReset(int m) { return 1; }
int CdStatus(void) { return 0x02; }
int CdMode(void) { return cd_mode; }
int CdLastCom(void) { return cd_last_com; }
int CdSetDebug(int l) { return 0; }
void CdFlush(void) {}
int CdControl(u8 com, u8 *param, u8 *result) {
    cd_last_com = com;
    if ((com == 2 /* Setloc */ || com == 0x15 || com == 0x16) && param) {
        cd_pos = loc_to_lba(param);
        if (port_trace_cd) port_printf("[port] cd: Setloc lba %d (frame %d)\n", cd_pos, port_frame);
    }
    if ((com == 6 /* ReadN */ || com == 0x1B /* ReadS */)) {
        if (param) cd_pos = loc_to_lba(param);
        cd_reading = 1;
        if (port_trace_cd) port_printf("[port] cd: Read%s from lba %d (frame %d)\n", com == 6 ? "N" : "S", cd_pos, port_frame);
    }
    if (com == 9 /* Pause */ || com == 8 /* Stop */ || com == 0x0A /* Init */) cd_reading = 0;
    if (com == 14 /* Setmode */ && param) cd_mode = param[0];
    if (result) { result[0] = 0x02; for (int i = 1; i < 8; i++) result[i] = 0; }
    if (cd_sync_cb && com != 2) cd_call(cd_sync_cb, 2 /* CdlComplete */, (u32)result);
    return 1;
}
int CdControlF(u8 com, u8 *param) { return CdControl(com, param, 0); }
int CdControlB(u8 com, u8 *param, u8 *result) { return CdControl(com, param, result); }
int CdSync(int mode, u8 *result) { if (result) result[0] = 0x02; return 2; /* CdlComplete */ }
int CdReady(int mode, u8 *result) { return cd_reading ? 1 : 2; }
void *CdSyncCallback(void *f) { void *o = cd_sync_cb; cd_sync_cb = f; return o; }
void *CdReadyCallback(void *f) { void *o = cd_ready_cb; cd_ready_cb = f; return o; }
void *CdReadCallback(void *f) { void *o = cd_read_cb; cd_read_cb = f; return o; }
void *CdDataCallback(void *f) { void *o = cd_data_cb; cd_data_cb = f; return o; }
int CdGetSector(void *buf, int words) {
    u8 *d = buf; int n = words * 4;
    for (int i = 0; i < n; i++) d[i] = cd_sector_off + i < (int)sizeof cd_sector ? cd_sector[cd_sector_off + i] : 0;
    cd_sector_off += n;
    return 1;
}
int CdGetSector2(void *buf, int words) { return CdGetSector(buf, words); }
int CdDataSync(int mode) { return 0; }
int CdRead(int sectors, u32 *buf, int mode) {
    int bytes = (mode & 0x20) ? 2340 : 2048;
    if (port_verbose || port_trace_cd) port_printf("[port] CdRead lba %d, %d sectors -> %p (frame %d)\n", cd_pos, sectors, buf, port_frame);
    if (port_cd_read_sectors(cd_pos, sectors, buf, bytes)) { port_printf("[port] CdRead failed at lba %d (frame %d)\n", cd_pos, port_frame); return 0; }
    cd_pos += sectors; cd_reads++; cd_sectors += sectors;
    if (cd_read_cb) cd_call(cd_read_cb, 2 /* CdlComplete */, 0);
    return 1;
}
int CdReadSync(int mode, u8 *result) { if (result) result[0] = 0x02; return 0; }
int CdReadBreak(void) { return 0; }
int CdMix(void *att) { return 1; }
int CdIntToPos(int i, u8 *p) { lba_to_loc(i, p); return (int)p; }
int CdPosToInt(u8 *p) { return loc_to_lba(p); }
int port_cd_stats(int *sectors) { *sectors = cd_sectors; return cd_reads; }
/* the data-ready path: up to 4 sectors per vblank (double speed is 150 sectors/s, 3 per PAL vblank) */
static void cd_vblank(void) {
    for (int k = 0; k < 4 && cd_reading && cd_ready_cb; k++) {
        int bytes = (cd_mode & 0x20) ? 2340 : 2048;
        if (port_cd_read_sectors(cd_pos, 1, cd_sector, bytes)) { cd_reading = 0; break; }
        cd_sector_off = 0;
        cd_pos++; cd_sectors++;
        static u8 res[8] = { 0x22 };
        cd_call(cd_ready_cb, 1 /* CdlDataReady */, (u32)res);
    }
}
/* streaming (movies): not supported yet; StGetNext reports no frame */
int CdRead2(int mode) { return 1; }
void StSetRing(void *a, int b) {}
void StClearRing(void) {}
void StUnSetRing(void) {}
int StFreeRing(void *a) { return 0; }
int StGetNext(void **a, void **b) { return 1; }
void StSetStream(int a, int b, int c, void *d, void *e) {}
void StSetMask(int a, int b, int c) {}
/* MDEC (movies) */
void DecDCTReset(int m) {}
int DecDCTin(void *p, int m) { return 0; }
int DecDCTout(void *p, int n) { return 0; }
int DecDCTinSync(int m) { return 0; }
int DecDCToutSync(int m) { return 0; }
void *DecDCToutCallback(void *f) { return 0; }
void *DecDCTinCallback(void *f) { return 0; }
int DecDCTvlc(void *a, void *b) { return 0; }
int DecDCTvlcSize(int n) { return 0; }
int DecDCTBufSize(void *p) { return 0; }
