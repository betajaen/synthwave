#include <synthwave/events.h>
#include <synthwave/memory.h>
#include <synthwave/assert.h>

#include <proto/exec.h>

struct ActionBinding
{
  struct Node node;
  Action      action;
};

static struct List actions = { 0 };

void Action_Add(string name, Action action)
{
  ExpectParamNotNull(name);
  ExpectParamNotNull(action);

  struct ActionBinding* binding = Cast(struct ActionBinding*) New(struct ActionBinding);
  AssertF(binding != NULL, "Action", "Out of memory for action '{s}'", name);

  binding->node.ln_Name = name;
  binding->action = action;
  AddTail(&actions, Cast(struct Node*) binding);
}

void Action_Remove(string name)
{
  ExpectParamNotNull(name);
  struct Node* node = FindName(&actions, name);
  AssertF(node != NULL, "Action", "Action for '{s}' was not found", name);
  Remove(node);
  Delete(node);
}

void Action_RemoveAll()
{
  struct Node* node = actions.lh_Head;
  while(node != NULL)
  {
    struct Node* next = node->ln_Succ;
    Delete(node);
    node = next;
  }
  actions.lh_Head = 0;
  actions.lh_Tail = 0;
  actions.lh_TailPred = 0;
  actions.lh_Type = 0;
  actions.l_pad = 0;
}

void Emit(string name, EventParam p)
{
  ExpectParamNotNull(name);
  struct Node* node = FindName(&actions, name);
  AssertF(node != NULL, "Action", "Action for '{s}' was not found", name);
  struct ActionBinding* binding = Cast(struct ActionBinding*) node;
  binding->action(p);
}
