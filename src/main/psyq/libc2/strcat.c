// CC gcc-2.7.2-psx
// FLAGS -O2 -G0
// AS gnu
#include "common.h"
s32 strlen(s8 *);

s8 *strcat(s8 *arg0, s8 *arg1) {
    s8 *temp_v1;
    s8 temp_v0;
    if (arg0 == NULL) return NULL;
    if (arg1 == NULL) return NULL;
    if (&arg0[strlen(arg0)] != &arg1[strlen(arg1)]) {
        temp_v1 = arg0;
        while (*arg0++ != '\0') {}
        arg0--;
        do {
            temp_v0 = *arg1++;
            *arg0++ = temp_v0;
        } while (temp_v0 != '\0');
        return temp_v1;
    }
    return NULL;
}
