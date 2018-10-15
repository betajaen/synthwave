#include <synthwave/synthwave.h>

#include <proto/exec.h>

ptr Ram_Alloc(i32 size)
{
  return AllocVec(size, MEMF_FAST | MEMF_CLEAR);
}

ptr Ram_AllocChip(i32 size)
{
  return AllocVec(size, MEMF_CHIP | MEMF_CLEAR);
}

void Ram_Free(ptr memory)
{
  FreeVec(memory);
}
