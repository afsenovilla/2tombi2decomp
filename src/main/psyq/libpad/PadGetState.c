// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// ASPSX 2.79
// Source: Tombi-Decomp (matched C of the same Psy-Q function).
typedef struct C { char p0[0x10]; struct C *self; char p1[0x1c]; char *q; char p2[3]; unsigned char a, b, c; char p3[15]; unsigned char st; } C;
extern C *(*_padFuncPort2Info)(void);
int PadGetState(void)
{
    C *c = _padFuncPort2Info();
    if (c->a || c->b || (c != c->self && c->c) || *c->q) {
        switch (c->st) {
        case 3: return 1;
        case 2: return 1;
        case 6: return 4;
        }
    }
    return c->st;
}
