// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
struct Ref { virtual int AddRef(); virtual int Release(); };
extern Ref* g_166ae74;
// @ 0x00951d10
void FUN_00951d10(Ref* p) {
  Ref* old = g_166ae74;
  if (p == old) return;
  if (p) p->AddRef();
  g_166ae74 = p;
  if (old) old->Release();
}
