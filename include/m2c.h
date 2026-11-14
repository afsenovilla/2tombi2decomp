#ifndef M2C_H
#define M2C_H
/* The few names m2c's --valid-syntax drafts use, so a draft compiles as it comes out (tools/libsweep.py).
 * M2C_FIELD(p, T *, off): the field of type T at byte offset off of p. Replace by real struct fields over time. */
typedef int M2C_UNK;
typedef signed char M2C_UNK8;
typedef short M2C_UNK16;
typedef int M2C_UNK32;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((signed char *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
#endif
