//                                                                                                                     
//                                               88                                                                    
//                                        ,d     88                                                                    
//                                        88     88                                                                    
//  ,adPPYba,  8b       d8  8b,dPPYba,  MM88MMM  88,dPPYba,   8b      db      d8  ,adPPYYba,  8b       d8   ,adPPYba,  
//  I8[    ""  `8b     d8'  88P'   `"8a   88     88P'    "8a  `8b    d88b    d8'  ""     `Y8  `8b     d8'  a8P_____88  
//   `"Y8ba,    `8b   d8'   88       88   88     88       88   `8b  d8'`8b  d8'   ,adPPPPP88   `8b   d8'   8PP"""""""  
//  aa    ]8I    `8b,d8'    88       88   88,    88       88    `8bd8'  `8bd8'    88,    ,88    `8b,d8'    "8b,   ,aa  
//  `"YbbdP"'      Y88'     88       88   "Y888  88       88      YP      YP      `"8bbdP"Y8      "8"       `"Ybbd8"'  
//                 d8'                                                                                                 
//                d8'                                                                                                  
//                                                                                                                     
//       (c) Robin Southern 2018 https://github.com/betajaen/synthwave https://opensource.org/licenses/MIT             
//                                                                                                                     


#ifndef SYNTHWAVE_H
#define SYNTHWAVE_H

#include <exec/types.h>
#include <synthwave/vendor/SDI_compiler.h>


//! Plain Old Data and Number-likes
//! 
//! Cheat Sheet:
//! 
//! Integers                    -- uinteger (ULONG), integer (LONG)
//! Numbers                     -- unsigned: u8, u16, u32  signed: i8, i16, i32
//! Boolean                     -- boolean, b8, b16, b32
//! Char                        -- char
//!
typedef BYTE   byte;
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
typedef BOOL   boolean;
typedef BYTE   b8;
typedef SHORT  b16;
typedef LONG   b32;



#define SizeOf(T)       ((integer) sizeof(T))
#define Cast(T)         (T)
#define _ToString(_1)   #_1
#define ToString(_1)    _ToString(_1)
#define FileLine        __FILE__ ":" ToString(__LINE__)


//! Amiga Libraries
//! 
//! Cheat Sheet:
//!
//! OpenLib, OpenLibVers                      --  Open Library (ref-counted)
//! CloseLib                                  --  Close Library (ref-counted)
//! CloseLibs                                 --  Close Opened libraries

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

//! Open an Amiga Kickstart library. If the library is already opened, then the number
//! of users will be increased, so future closing of the library won't close early.
void OpenLibVers(LibName name, u32 minVersion);
//! Try and close an Amiga library, if the library is used multiple times, then it is closed
//! after the last use.
void CloseLib(LibName name);
//! Close all libraries, regardless of users
void CloseLibs();
//! Open an Amiga Kickstart library, with the best version.
inline void OpenLib(LibName name)
{
  OpenLibVers(name, 0);
}

//! Wait an amount of time, where one tick is 1/50th of a second.
void WaitTicks(uinteger time);

//! Assertion and Logging Macros and Functions
//! 
//! Cheat Sheet:
//!
//! SInfo, SInfoF                             --  Log information text (formatted or as is) to the Amiga shell.
//! Log, LogF                                 --  Just write text (formatted or as is) to the Amgia shell.
//! Assert, AssertF                           --  Assert if condition is false (formatted or as is).
//! AssertAlways, AssertAlwaysF               --  Throw an assertion (formatted or as is) immediately.
//! ExpectParamNotNull, ExpectParam...        --  Throw an assertion if a parameter is unexpected.
//! 
//! Formatting:
//! 
//! Formating is 'python-like' formatting.
//! 
//! SInfoF("MSG", "Hello my name is {s} and I am using my Amiga {i}", myName, 1200");
//!   > MSG Hello my name is Robin and I am using my Amiga 1200
//! 
//! {i}                                       -- Integer  (u8, u16, u32, i8, i16, i32, integer, uinteger)
//! {x}                                       -- Integer as hexadecimal (u8, u16, u32, i8, i16, i32, integer, uinteger)
//! {s}                                       -- Null terminated string (string)
//! {p}                                       -- Pointer (ptr, byteptr)
//! 
//! Markup:
//! 
//! FmtBold                                   -- Format constant string in bold text
//! FmtItalic                                 -- Format constant string in italic text
//!
#define FmtBold(T)   "\33[1m" T "\33[22m"
#define FmtItalic(T) "\33[3m" T "\33[23m"

void _DoAssert(integer rc);
void Log(string text);
void LogF(string text, ...);

#define SInfoF(SYSTEM, TEXT, ...)   LogF(FmtBold(SYSTEM) "  " TEXT "\n", __VA_ARGS__)
#define SInfo(SYSTEM, TEXT)         Log(FmtBold(SYSTEM) "  " TEXT "\n")

#define _AssertImplF(SYSTEM, TEXT, ...)           LogF(FmtBold("\nException!!\n") FileLine "\n" FmtBold(SYSTEM) "  " TEXT "\n", __VA_ARGS__); _DoAssert(0);
#define _AssertImpl(SYSTEM, TEXT)                 Log(FmtBold("\nException!!\n") FileLine "\n" FmtBold(SYSTEM) "  " TEXT "\n"); _DoAssert(0);

#define AssertAlwaysF(SYSTEM, FAILURE_TEXT, ...)  _AssertImplF(SYSTEM, FAILURE_TEXT, __VA_ARGS__)
#define AssertAlways(SYSTEM, FAILURE_TEXT)        _AssertImpl(SYSTEM, FAILURE_TEXT)
#define AssertF(COND, SYSTEM, FAILURE_TEXT, ...)  if (!(COND)) { _AssertImplF(SYSTEM, FAILURE_TEXT, __VA_ARGS__); }
#define Assert(COND, SYSTEM, FAILURE_TEXT)        if (!(COND)) { _AssertImpl(SYSTEM, FAILURE_TEXT) }

#define ExpectParamNotNull(PARAM)          if (PARAM == NULL) { Log(FmtBold("\nInvalid Parameter!!\n") ToString(PARAM) " is null at " FileLine "\n"); _DoAssert(0); }
#define ExpectParamNotNegative(PARAM)      if (!(PARAM < 0))     { LogF(FmtBold("\nInvalid Parameter!!\n") ToString(PARAM) " is not negative ({0}) at " FileLine "\n", (PARAM)); _DoAssert(0); }
#define ExpectParamPositiveAndNotZero(PARAM)   if (!(PARAM > 0))     { LogF(FmtBold("\nInvalid Parameter!!\n") ToString(PARAM) " is not positive and not zero ({0}) at " FileLine "\n", (PARAM)); _DoAssert(0); }
#define ExpectParamPositive(PARAM)             if (!(PARAM >= 0))     { LogF(FmtBold("\nInvalid Parameter!!\n") ToString(PARAM) " is not positive ({0}) at " FileLine "\n", (PARAM)); _DoAssert(0); }


//! Memory alllocation
//! 
//! Cheat Sheet:
//!
//! Ram_Alloc, Ram_AllocChip, Ram_Fre         --  Allocate (chip or fast), Deallocate memory or arrays
//! New, Delete                               --  New and Delete C-style Objects
//!
ptr Ram_Alloc(i32 size);
ptr Ram_AllocChip(i32 size);
void Ram_Free(ptr memory);

#define New(T)      ((T*) (Ram_Alloc(SizeOf(T))))
#define Delete(OBJ) Ram_Free(OBJ)



#endif
