#include <synthwave/synthwave.h>
#include <synthwave/vendor/SDI_stdarg.h>
#include <proto/dos.h>

void PPrintCString(string str)
{
  if (DOSBase != NULL)
  {
    PutStr(str);
  }
}

char* integerToString(i32 a, i32 base)
{
  static char buffer[30 + 1 + 1];
  static const char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  if (base < 2 || base > 36) {
    return NULL;
  }

  char* p = &buffer[sizeof(buffer) - 1];
  *p = '\0';

  i32 an = a < 0 ? a : -a;  

  do
  {
    *(--p) = digits[-(an % base)];
    an /= base;
  } while (an);

  if (a < 0) {
    *(--p) = '-';
  }

  return p;
}

void _DoAssert(integer rc)
{
  Exit(rc); //?
}

void Log(string text)
{
  PPrintCString(text);
}

void LogF(string  text, ...)
{
  static char buffer[128] = {0};

  char* t = &buffer[0];
  char* e = &buffer[127];

  VA_LIST args;
  VA_START(args, text);
  i32* a = (i32*) args;

  while(t < e)
  {
    char ch = *text++;
    
    if (ch == '\0')
      break;
    
    if (ch == '{')
    {
      char peek = *text;

      if (peek == '}')
      {
          text++;

          i32 iVal = (i32) (*a++);
          char* numString = integerToString(iVal, 10);
          while(t < e)
          {
            if (*numString == '\0')
              break;
            *t++ = *numString++;
          }

          continue;
      }
      else if (peek == 'i')
      {
        char peek2 = text[1];

        if (peek2 == '}')
        {
          text += 2;

          i32 iVal = (i32) (*a++);
          char* numString = integerToString(iVal, 10);
          while(t < e)
          {
            if (*numString == '\0')
              break;
            *t++ = *numString++;
          }
          
          continue;
        }
      }
      else if (peek == 'x')
      {
        char peek2 = text[1];

        if (peek2 == '}')
        {
          text += 2;

          i32 iVal = (i32) (*a++);
          char* numString = integerToString(iVal, 16);
          while(t < e)
          {
            if (*numString == '\0')
              break;
            *t++ = *numString++;
          }
          
          continue;
        }
      }
      else if (peek == 'p')
      {
        char peek2 = text[1];

        if (peek2 == '}')
        {
          text += 2;

          i32 iVal = (i32) (*a++);
          if (t < e)
            *t++ = '0';
          if (t < e)
            *t++ = 'x';
          if (t < e)
          {
            char* numString = integerToString(iVal, 16);
            while(t < e)
            {
              if (*numString == '\0')
                break;
              *t++ = *numString++;
            }
          }
          continue;
        }
      }
      else if (peek == 's')
      {
        char peek2 = text[1];

        if (peek2 == '}')
        {
          text += 2;

          char* sVal = (char*) (*a++);
          while(t < e)
          {
            if (*sVal == '\0')
              break;
            *t++ = *sVal++;
          }
          
          continue;
        }
      }
      else if (peek == 'b')
      {
        char peek2 = text[1];

        if (peek2 == '}')
        {
          text += 2;

          i32 bVal = (i32) (*a++);
          char* sVal = bVal == 0 ? "False" : "True";

          while(t < e)
          {
            if (*sVal == '\0')
              break;
            *t++ = *sVal++;
          }
          
          continue;
        }
      }
      else if (peek == '{' || peek == '\0')
      {
        ch = '{';
        text++;
      }
    }

    *t++ = ch;
  }

  *t++ = '\0';

  VA_END(args);
  PPrintCString(&buffer[0]);
}
