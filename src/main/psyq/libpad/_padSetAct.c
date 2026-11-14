// CC gcc-2.8.1-psx
// FLAGS -O2 -G0
// ASPSX 2.79
void _padSetAct(char *p, int a, char b)
{
    *(int *)(p + 0x28) = a;
    p[0x34] = b;
}
