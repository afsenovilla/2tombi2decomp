#ifndef PSYQ_ALL_H
#define PSYQ_ALL_H
/* The Psy-Q library headers (include/psyq, fetched by tools/setup_native.sh): the context of library drafts.
 * A draft defines its function with m2c's types (s32/u32 for long): it includes this header with
 * `#define NAME NAME_hdr` around it so the header's prototype of that one function does not clash. */
#include "pt/common.h"
#include "psyq/sys/types.h"
#include "psyq/libetc.h"
#include "psyq/libgte.h"
#include "psyq/libgpu.h"
#include "psyq/libcd.h"
#include "psyq/libspu.h"
#include "psyq/libsnd.h"
#include "psyq/libpress.h"
#include "m2c.h"
#endif
