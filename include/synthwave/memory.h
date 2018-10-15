#ifndef SYNTHWAVE_MEMORY_H
#define SYNTHWAVE_MEMORY_H

#include <synthwave/synthwave.h>

ptr Ram_Alloc(i32 size);
ptr Ram_AllocChip(i32 size);
void Ram_Free(ptr memory);

#define New(T)      ((T*) (Ram_Alloc(SizeOf(T))))
#define Delete(OBJ) Ram_Free(OBJ)

#endif
