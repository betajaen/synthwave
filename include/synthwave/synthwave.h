#ifndef SYNTHWAVE_H
#define SYNTHWAVE_H

#include <exec/types.h>
#include <synthwave/vendor/SDI_compiler.h>

typedef BYTE   byte;
typedef BOOL   boolean;
typedef BYTE   i8;
typedef UBYTE  u8;
typedef WORD   i16;
typedef UWORD  u16;
typedef LONG   i32;
typedef ULONG  u32;
typedef VOID*  ptr;
typedef BYTE*  byteptr;
typedef STRPTR string;
typedef ULONG  uinteger;
typedef LONG   integer;
typedef WORD   param;

#define SizeOf(T)       ((integer) sizeof(T))
#define Cast(T)         (T)
#define _ToString(_1)   #_1
#define ToString(_1)    _ToString(_1)
#define FileLine        __FILE__ ":" ToString(__LINE__)

extern struct ExecBase*      ExecBase;
extern struct DosLibrary*    DOSBase;
extern struct IntuitionBase* IntuitionBase;
extern struct GfxBase*       GfxBase;

typedef enum _LibName
{
  Lib_Exec,
  Lib_DOS,
  Lib_Intuition,
  Lib_Graphics,
  Lib__Count
} LibName;

void OpenLibVers(LibName name, u32 minVersion);
void CloseLib(LibName name);
void CloseLibs();

inline void OpenLib(LibName name)
{
  OpenLibVers(name, 0);
}

void WaitTicks(uinteger time);

#endif
