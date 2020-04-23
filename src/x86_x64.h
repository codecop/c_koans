#include <stdint.h>
#define UPTR (UINTPTR_MAX > 0xffffffffU ? 8U : 4U)

#if UPTR == 8U
#define UPTR_STRING "0000000000000400"
#else
#define UPTR_STRING "00000400"
#endif
