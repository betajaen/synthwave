#ifndef SYNTHWAVE_EVENTS_H
#define SYNTHWAVE_EVENTS_H

#include <synthwave/synthwave.h>

typedef union _EventParam
{
  ptr pointer;
  integer val;
  struct { param x, y; } xy;
} EventParam;

typedef void(*Action)(EventParam p);

void Action_Add(string name, Action action);
void Action_Remove(string name);
void Action_RemoveAll();

void Emit(string name, EventParam p);

inline void EmitPtr(string name, ptr ptr)
{
  EventParam p;
  p.pointer = ptr;
  Emit(name, p);
}

inline void EmitVal(string name, integer ptr)
{
  EventParam p;
  p.val = ptr;
  Emit(name, p);
}

inline void EmitXY(string name, param x, param y)
{
  EventParam p;
  p.xy.x = x;
  p.xy.y = y;
  Emit(name, p);
}

#endif
