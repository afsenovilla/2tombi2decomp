// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
// Source: Tombi-Decomp (matched C of the same Psy-Q function).
#if defined(VERSION_SCUS_94236)
extern void (*_padFuncClrInfo)(unsigned char *);

void _dirFailAuto(unsigned char *o)
{
    int s = o[0x46];
    unsigned int t;
    *(int *)(o + 0x4c) = *(int *)(o + 0x4c) + 1;
    if (s == 0)
        goto tail;
    if (s == 1) {
        t = o[0x4a];
        if (t > 1) {
            o[0x49] = 2;
            o[0x46] = 0xff;
            return;
        }
        o[0x4a] = t + 1;
        return;
    }
    t = o[0x4a];
    if (t <= 3) {
        o[0x4a] = t + 1;
        return;
    }
    if (o[0x49] != 0)
        _padFuncClrInfo(o);
tail:
    if (**(unsigned char **)(o + 0x3c) != 0xf3) {
        **(unsigned char **)(o + 0x30) = 0xff;
        (*(unsigned char **)(o + 0x30))[1] = 0;
        o[0xe8] = 0;
    }
}
#elif defined(VERSION_BETA_980203)
extern void (*_padFuncClrInfo)(unsigned char *);

void _dirFailAuto(unsigned char *o)
{
    int s = o[0x46];
    unsigned int t;
    *(int *)(o + 0x4c) = *(int *)(o + 0x4c) + 1;
    if (s == 0)
        goto tail;
    if (s == 1) {
        t = o[0x4a];
        if (t > 1) {
            o[0x49] = 2;
            o[0x46] = 0xff;
            return;
        }
        o[0x4a] = t + 1;
        return;
    }
    t = o[0x4a];
    if (t <= 3) {
        o[0x4a] = t + 1;
        return;
    }
    if (o[0x49] != 0)
        _padFuncClrInfo(o);
tail:
    if (**(unsigned char **)(o + 0x3c) != 0xf3) {
        **(unsigned char **)(o + 0x30) = 0xff;
        (*(unsigned char **)(o + 0x30))[1] = 0;
        o[0xe8] = 0;
    }
}
#else
extern void (*_padFuncClrInfo)(unsigned char *);

void _dirFailAuto(unsigned char *o)
{
    int s = o[0x46];
    unsigned int t;
    *(int *)(o + 0x4c) = *(int *)(o + 0x4c) + 1;
    if (s == 0)
        goto tail;
    if (s == 1) {
        t = o[0x4a];
        if (t > 10) {
            o[0x49] = 2;
            o[0x46] = 0xff;
            return;
        }
        o[0x4a] = t + 1;
        return;
    }
    t = o[0x4a];
    if (t <= 10) {
        o[0x4a] = t + 1;
        return;
    }
    if (o[0x49] != 0)
        _padFuncClrInfo(o);
tail:
    if (**(unsigned char **)(o + 0x3c) != 0xf3) {
        **(unsigned char **)(o + 0x30) = 0xff;
        (*(unsigned char **)(o + 0x30))[1] = 0;
        o[0xe8] = 0;
        o[0x35] = 0;
    }
}
#endif
