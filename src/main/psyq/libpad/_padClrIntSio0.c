// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.86
// Source: Tombi-Decomp (matched C of the same Psy-Q function).
extern int *PAD_INTR;
extern unsigned short *PAD_SIO;
extern int chkRC2wait();

int _padClrIntSio0(void)
{
    int *is = PAD_INTR;
    unsigned short *j = PAD_SIO;
    *is = -0x81;
    if (j[2] & 0x80) {
        do {
            if (chkRC2wait()) return 0;
        } while (PAD_SIO[2] & 0x80);
    }
    PAD_SIO[5] |= 0x10;
    return 1;
}
