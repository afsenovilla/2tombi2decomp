/* Compiler probe: small MAIN.EXE functions written to find the compiler (docs/COMPILER.md). */
extern volatile unsigned char D_800BE82C;
extern void f_CloseCooperativeWorkerThread(int);
extern void f_SetCdAudioMixEnabled(int);
extern int CdControlB(unsigned char, unsigned char *, unsigned char *);

void f_SetIdentityMatrix(long *m)
{
    m[0] = 0x1000; m[1] = 0;
    m[2] = 0x1000; m[3] = 0;
    m[4] = 0x1000; m[5] = 0;
    m[6] = 0; m[7] = 0;
}



void f_StopVoicePlayback(void)
{
    unsigned char result[8];

    f_CloseCooperativeWorkerThread(2);
    D_800BE82C = 0;
    f_SetCdAudioMixEnabled(0);
    while (CdControlB(9, 0, 0) == 0)
        ;
}
