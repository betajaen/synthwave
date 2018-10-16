#include <synthwave/synthwave.h>

#include <proto/exec.h>

struct ExecBase*      ExecBase = NULL;
struct DosLibrary*    DOSBase = NULL;
struct IntuitionBase* IntuitionBase = NULL;
struct GfxBase*       GfxBase = NULL;

static const string libNames[Lib__Count] = {
  "exec.library",
  "dos.library",
  "intuition.library",
  "graphics.library"
};

static u32 libOpen[Lib__Count] = {
  0,
  0,
  0,
  0
};

static struct Library** libPtrs[Lib__Count] = {
  (struct Library**) &ExecBase,
  (struct Library**) &DOSBase,
  (struct Library**) &IntuitionBase,
  (struct Library**) &GfxBase
};

void OpenLibVers(LibName name, u32 minVersion)
{
  if (name == Lib_Exec)
  {
    ExecBase = Cast(struct ExecBase*) 4L;
    return;
  }

  u32 count = libOpen[name];
  if (count == 0)
  {
    struct Library** libPtr = libPtrs[name];
    (*libPtr) = OpenLibrary(libNames[name], minVersion);
    AssertF((*libPtr) != NULL, "Lib", "Could not open library {0}", libNames[name]);
    SInfoF("Lib", "Opened {s}", libNames[name]);
    libOpen[name] = 1;
  }
  else
  {
    libOpen[name] = count + 1;
  }

}

void CloseLib(LibName name)
{
  if (name != Lib_Exec)
  {
    u32 count = libOpen[name];

    if (count > 0)
    {
      count--;
      libOpen[name] = count;

      if (count == 0)
      {
        struct Library** libPtr = libPtrs[name];
        SInfoF("Lib", "Closing {s}", libNames[name]);
        CloseLibrary((*libPtr));
        (*libPtr) = NULL;
      }
    }
  }
}

void CloseLibs()
{
  for(param ii=Lib__Count-1;ii > -1;ii--)
  {
    CloseLib((LibName) ii);
  }
}
