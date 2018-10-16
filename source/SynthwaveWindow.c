#include <synthwave/synthwave.h>

#include <proto/graphics.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <intuition/intuition.h>
#include <graphics/gfxbase.h>
#include <hardware/custom.h>

u32 FindBestScreenMode(u32 width, u32 height, u32 numPlanes)
{
  u32 modeId = INVALID_ID;

  modeId = BestModeID(
    BIDTAG_NominalWidth, width,
    BIDTAG_NominalHeight, height,
    BIDTAG_DesiredWidth, width,
    BIDTAG_DesiredHeight, height,
    BIDTAG_Depth, numPlanes,
    BIDTAG_MonitorID, VGA_MONITOR_ID,
    TAG_END
  );

  if (modeId == INVALID_ID)
  {
    modeId = BestModeID(
      BIDTAG_NominalWidth, width,
      BIDTAG_NominalHeight, height,
      BIDTAG_DesiredWidth, width,
      BIDTAG_DesiredHeight, height,
      BIDTAG_Depth, numPlanes,
      BIDTAG_MonitorID, PAL_MONITOR_ID,
      TAG_END
    );
 }

 if (modeId == INVALID_ID)
 {
    modeId = BestModeID(
      BIDTAG_NominalWidth, width,
      BIDTAG_NominalHeight, height,
      BIDTAG_DesiredWidth, width,
      BIDTAG_DesiredHeight, height,
      BIDTAG_Depth, numPlanes,
      BIDTAG_MonitorID, NTSC_MONITOR_ID,
      TAG_END
    );
 }

 AssertF(modeId != INVALID_ID, "GFX", "Could not valid screen mode for {i}x{i}x{i}", width, height, numPlanes);

 return modeId;
}

typedef struct _SWindow
{
  struct Window*      window; /* Amiga window. */
  boolean closewin;           /* Flag used to end program */
} SWindow;

ptr Screen_New(param width, param height, param depth)
{
  u32 screenMode = FindBestScreenMode(width, height, depth);
  
  AssertF(screenMode != -1, "Screen", "Could not open find screenmode! Size={i}x{i}x{i}", width, height, depth);
  
  struct Screen* screen = OpenScreenTags(
      0,
      SA_DisplayID,  screenMode,
      SA_Width,      width,
      SA_Height,     height,
      SA_Depth,      depth,
      SA_Type,       CUSTOMSCREEN,
      SA_Overscan,   OSCAN_TEXT,
      SA_AutoScroll, FALSE,
      SA_ShowTitle,  FALSE,
      SA_Draggable,  FALSE,
      SA_Exclusive,  TRUE,
      TAG_DONE
    );
  
  AssertF(screen != NULL, "Screen", "Could not open screen! Size={i}x{i}x{i}, ScreenMode={x}", width, height, depth, screenMode);
  
  SInfoF("Screen", "Opened Screen {i}x{i}x{i}", width, height, depth);
  
  WaitTOF();
  return screen;
}

void  Screen_Delete(ptr screen)
{
  ExpectParamNotNull(screen);
  CloseScreen(Cast(struct Screen*) screen);
}

ptr Window_New(param width, param height, string caption)
{

   struct Window* win = OpenWindowTags(NULL,
     WA_Width, width,
     WA_Height, height,
     WA_IDCMP, IDCMP_CLOSEWINDOW,
     WA_Flags, WFLG_SIZEGADGET | WFLG_DRAGBAR | WFLG_DEPTHGADGET | WFLG_CLOSEGADGET | WFLG_ACTIVATE,
     WA_Title, (ULONG) caption,
     WA_PubScreenName, (ULONG) "Workbench", // @TODO
     TAG_DONE
   );
   Assert(win != NULL, "Window", "Window could not be opened");

   SWindow* window = New(SWindow);
   window->window = win;
   window->closewin = FALSE;
   
   return window;
}

void  Window_Delete(ptr window)
{
  ExpectParamNotNull(window);

  SWindow* win = Cast(SWindow*)(window);

  if (win->window)
  {
    CloseWindow(win->window);
  }

  Delete(win);
}

integer Window_Poll(ptr window)
{
#if 0
  SWindow* win = Cast(SWindow*)(window);
  struct Window* w = win->window;
  
  Wait(1L << w->UserPort->mp_SigBit);
  struct IntuiMessage* msg = GT_GetIMsg(w->UserPort);
  ULONG msgClass = msg->Class;
  GT_ReplyIMsg(msg);

  if (msgClass == IDCMP_CLOSEWINDOW)
  {
    win->closewin = TRUE;
    return -1;
  }
#endif
  return 0;
}
