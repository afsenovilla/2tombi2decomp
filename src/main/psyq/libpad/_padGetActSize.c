// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
int _padGetActSize(unsigned char *p)
{
    int a = ((p[0xe3] + 1) >> 1) * 4;
    int b = ((p[0xe9] * 5 + 3) & 0xffc) + 4;
    return a + b + *(unsigned short *)(p + 0xec);
}
