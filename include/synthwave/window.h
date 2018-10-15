#ifndef SYNTHWAVE_WINDOW_H
#define SYNTHWAVE_WINDOW_H

#include <synthwave/synthwave.h>

ptr   Screen_New(param width, param height, param depth);
void  Screen_Delete(ptr screen);

ptr   Window_New(param width, param height, string caption);
void  Window_Delete(ptr window);
integer Window_Poll(ptr window);

#endif
