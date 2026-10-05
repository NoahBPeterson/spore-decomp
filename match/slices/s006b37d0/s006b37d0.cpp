// Slice s006b37d0: SP default save areas / save-area job holder.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS-.
#include "s006b37d0.h"

// @ 0x6b42f0
bool Counter40::Inc() {
  if (m40 != 0) {
    ++m40;
    return true;
  }
  return false;
}

// @ 0x6b4390
uint32_t FUN_006b4390(ObjSec6** p) {
  ObjSec6* o = *p;
  if (o != 0) {
    return o->sec.Call0c(0x6492c5f);
  }
  return 0;
}

// @ 0x6b43b0
JobHolder6::JobHolder6() : mutex(0, 1) {}

// @ 0x6b4340
JobHolder6::~JobHolder6() {}

JobPtr6::~JobPtr6() {
  if (p != 0) {
    ((Job6*)p)->GetStatus();
  }
}

// @ 0x6b4730
void FUN_006b4730() {
  g_1604b80 = 1;
  new (&g_jobHolder6) JobHolder6();
}

// @ 0x6b4780
void FUN_006b4780() {
  g_jobHolder6.~JobHolder6();
  g_1604b80 = 0;
}

// @ 0x6b37d0  (partial)
void SP_CreateDefaultSaveAreas() {}

// @ 0x6b4010  (partial)
void SP_SaveNamedResource() {}

// @ 0x6b4400  (partial)
void FUN_006b4400() {}

// @ 0x6b4490  (partial)
void FUN_006b4490() {}

// @ 0x6b4610  (partial)
void FUN_006b4610() {}
