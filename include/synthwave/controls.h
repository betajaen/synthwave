#ifndef SYNTHWAVE_CONTROLS_H
#define SYNTHWAVE_CONTROLS_H

#include <synthwave/synthwave.h>

enum ControlName
{
  CN_MouseXY    = 256,
  CN_JoyXY      = 257,
  CN_MouseLMB   = 258,
  CN_MouseRMB   = 259,
  CN_JoyButton  = 260,
};

void Controls_Add(string action, param control);
void Controls_Remove(string action, param control);

#endif
