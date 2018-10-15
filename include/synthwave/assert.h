#ifndef SYNTHWAVE_LOG_H
#define SYNTHWAVE_LOG_H

#include <synthwave/synthwave.h>

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

#endif
