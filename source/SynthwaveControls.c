#include <synthwave/controls.h>

#include <exec/types.h>
#include <exec/lists.h>
#include <exec/nodes.h>
#include <exec/memory.h>
 
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/utility.h>

#define MAX_ACTIONS 4

struct Button
{
  struct Node mm_Node;
  string action[MAX_ACTIONS];
  param  button;
  param  now, last;
};

struct MouseAxis
{
  struct Node mm_Node;
  string action[MAX_ACTIONS];
  param  nowX, lastX;
  param  nowY, lastY;
  param  deltaX, deltaY;
};

struct JoyAxis
{
  struct Node mm_Node;
  string action[MAX_ACTIONS];
  param  nowX, lastX;
  param  nowY, lastY;
  param  deltaX, deltaY;
};

static struct List actions = {0};
static struct List buttons = {0};
static struct List mouseAxis = {0};
static struct List joyAxis = {0};

void Controls_AddControl(string action, param control)
{
}

void Controls_RemoveControl(string action, param control)
{
}
