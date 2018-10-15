#ifndef SYNTHWAVE_FRAMEBUFFER_H
#define SYNTHWAVE_FRAMEBUFFER_H

#include <synthwave/synthwave.h>

ptr FrameBuffer_PlanarNew(ptr screen, i16 width, i16 height, i16 depth);
void  FrameBuffer_PlanarDelete(ptr frameBuffer);

byteptr FrameBuffer_ChunkyNew(i16 width, i16 height);
void    FrameBuffer_ChunkyDelete(byteptr frameBuffer);
void    FrameBuffer_Flip(byteptr source, ptr target);

#endif
