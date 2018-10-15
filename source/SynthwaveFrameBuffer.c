#include <synthwave/synthwave.h>
#include <synthwave/assert.h>
#include <synthwave/memory.h>

#include <proto/graphics.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <intuition/intuition.h>
#include <graphics/gfxbase.h>
#include <hardware/custom.h>

// ; d0.w	chunkyx [chunky-pixels]
// ; d1.w	chunkyy [chunky-pixels]
// ; d2.w	offsx [screen-pixels]
// ; d3.w	offsy [screen-pixels]
// ; a0	chunkyscreen
// ; a1	BitMap
// _c2p1x1_8_c5_bm
void c2p1x1_8_c5_bm(REG(d0, WORD chunkyx),
                    REG(d1, WORD chunkyy), 
                    REG(d2, WORD offsx), 
                    REG(d3, WORD offsy), 
                    REG(a0, UBYTE* chunkyscreen), 
                    REG(a1, struct BitMap* bitmap));

typedef struct _PlanarFrameBuffer
{
  struct Screen*         screen;
  struct Window*         window;
  struct ScreenBuffer*   screenBuffer[2];
  struct MsgPort*        displayPort;
  struct MsgPort*        safePort;
  i16                    currentBuffer;
  boolean                safeToWrite;
  boolean                safeToChange;
  i16                    width;
  i16                    height;
} PlanarFrameBuffer;

ptr FrameBuffer_PlanarNew(ptr screen, i16 width, i16 height, i16 depth)
{
  ExpectParamNotNull(screen);
  ExpectParamPositiveAndNotZero(width);
  ExpectParamPositiveAndNotZero(height);
  ExpectParamPositiveAndNotZero(depth);

  PlanarFrameBuffer* fb = New(PlanarFrameBuffer);
  fb->screen = Cast(struct Screen*) screen;

  fb->displayPort = CreateMsgPort();
  Assert(fb->displayPort != NULL, "GFX", "Couldn't open DisplayPort MsgPort");
  fb->safePort = CreateMsgPort();
  Assert(fb->safePort != NULL, "GFX", "Couldn't open SafePort MsgPort");

  fb->screenBuffer[0] = AllocScreenBuffer(fb->screen, NULL, SB_SCREEN_BITMAP);
  Assert(fb->screenBuffer[0] != NULL, "GFX", "Could not allocate screen buffer 0");
  fb->screenBuffer[1] = AllocScreenBuffer(fb->screen, NULL, 0);
  Assert(fb->screenBuffer[1] != NULL, "GFX", "Could not allocate screen buffer 1");

  fb->screenBuffer[0]->sb_DBufInfo->dbi_DispMessage.mn_ReplyPort = fb->displayPort;
  fb->screenBuffer[0]->sb_DBufInfo->dbi_SafeMessage.mn_ReplyPort = fb->safePort;
  fb->screenBuffer[1]->sb_DBufInfo->dbi_DispMessage.mn_ReplyPort = fb->displayPort;
  fb->screenBuffer[1]->sb_DBufInfo->dbi_SafeMessage.mn_ReplyPort = fb->safePort;

  fb->safeToWrite = TRUE;
  fb->safeToChange = TRUE;
  fb->currentBuffer = 1;
  fb->width = width;
  fb->height = height;

  fb->window = OpenWindowTags(
    0,
    WA_Left,  0,
    WA_Top,   0,
    WA_Width, width,
    WA_Height,  height,
    WA_Title,   NULL,
    WA_CustomScreen, (ULONG) fb->screen,
    WA_Backdrop, TRUE,
    WA_Borderless, TRUE,
    WA_DragBar, FALSE,
    WA_Activate, TRUE,
    WA_SmartRefresh, TRUE,
    WA_NoCareRefresh, TRUE,
    WA_ReportMouse, TRUE,
    WA_RMBTrap, TRUE,
    WA_IDCMP, IDCMP_RAWKEY|IDCMP_MOUSEMOVE|IDCMP_MOUSEBUTTONS|IDCMP_ACTIVEWINDOW|IDCMP_INACTIVEWINDOW,
    TAG_END
  );
  
  Assert(fb->window != NULL, "GFX", "Could not open hardware window");

  WaitTOF();

  return fb;
}

void  FrameBuffer_PlanarDelete(ptr frameBuffer)
{
  ExpectParamNotNull(frameBuffer);

  PlanarFrameBuffer* fb = Cast(PlanarFrameBuffer*) frameBuffer;

  if (fb->window != NULL)
  {
    ClearPointer(fb->window);
    CloseWindow(fb->window);
    fb->window = NULL;
  }

  if (fb->screenBuffer[0] != NULL)
  {
    WaitBlit();
    FreeScreenBuffer(fb->screen, fb->screenBuffer[0]);
    fb->screenBuffer[0] = NULL;
  }
  
  if (fb->screenBuffer[1] != NULL)
  {
    WaitBlit();
    FreeScreenBuffer(fb->screen, fb->screenBuffer[1]);
    fb->screenBuffer[1] = NULL;
  }

  if (fb->safePort != NULL)
  {
    if (!fb->safeToWrite)
    {
      while (!GetMsg(fb->safePort))
      {
        Wait(1L << (fb->safePort->mp_SigBit));
      }
    }
    DeleteMsgPort(fb->safePort);
    fb->safePort = NULL;
  }

  if (fb->displayPort != NULL)
  {
    if (!fb->safeToChange)
    {
      while(!GetMsg(fb->displayPort))
      {
        Wait(1L << (fb->displayPort->mp_SigBit));
      }
    }
    DeleteMsgPort(fb->displayPort);
    fb->displayPort = NULL;
  }

  Delete(fb);
}

byteptr  FrameBuffer_ChunkyNew(i16 width, i16 height)
{
  ExpectParamPositiveAndNotZero(width);
  ExpectParamPositiveAndNotZero(height);
  integer size = width * height;
  byteptr frameBuffer = Cast(byteptr) AllocVec(size, MEMF_FAST | MEMF_CLEAR);
  return frameBuffer;
}

void FrameBuffer_ChunkyDelete(byteptr frameBuffer)
{
  ExpectParamNotNull(frameBuffer);
  FreeVec(frameBuffer);
}

void FrameBuffer_Flip(byteptr source, ptr target)
{
  ExpectParamNotNull(source);
  ExpectParamNotNull(target);

  PlanarFrameBuffer* frameBuffer = Cast(PlanarFrameBuffer*) target;
  
  // Copy.
  c2p1x1_8_c5_bm(frameBuffer->width, frameBuffer->height, 0, 0, source, frameBuffer->screenBuffer[frameBuffer->currentBuffer]->sb_BitMap);

  // Flip.
  if (ChangeScreenBuffer(frameBuffer->screen, frameBuffer->screenBuffer[frameBuffer->currentBuffer]))
  {
    frameBuffer->currentBuffer = 1 - frameBuffer->currentBuffer;
    WaitTOF();
  }

}
