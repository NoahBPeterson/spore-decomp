// Slice s00b181d0 (bfs2 #47).
//
// SP::cGameData and related simulator/editor data classes. Two trivial virtual
// hooks are implemented faithfully; the remainder are incomplete skeletons
// (see partial.txt). Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE.
#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;

namespace SP {

// cGameData: the +0x21 byte and the vtable used by the two implemented hooks.
struct cGameData {
  void* vtbl0;                 // +0x00
  char  pad04[0x21 - 0x04];
  u8    mb21;                  // +0x21

  bool WriteSerializableObjectCheck();   // 0x00b183e0
  void NotifyDirty(bool b);              // 0x00b189a0
};

}  // namespace SP

using SP::cGameData;

// @ 0x00b183e0
bool cGameData::WriteSerializableObjectCheck() {
  return mb21 == 0;
}

// @ 0x00b189a0
void cGameData::NotifyDirty(bool b) {
  if (!b)
    ((void(__thiscall*)(void*))(*(void***)this)[7])(this);
}

// ---------------------------------------------------------------------------
// Remaining functions: incomplete skeletons, listed in partial.txt.
// ---------------------------------------------------------------------------
// @ 0x00b181d0
void Skel_b181d0() {}
// @ 0x00b182f0
void Skel_b182f0() {}
// @ 0x00b183f0
void Skel_b183f0() {}
// @ 0x00b18400
void Skel_b18400() {}
// @ 0x00b18490
void Skel_b18490() {}
// @ 0x00b184c0
void Skel_b184c0() {}
// @ 0x00b18530
void Skel_b18530() {}
// @ 0x00b18550
void Skel_b18550() {}
// @ 0x00b18590
void Skel_b18590() {}
// @ 0x00b18660
void Skel_b18660() {}
// @ 0x00b186b0
void Skel_b186b0() {}
// @ 0x00b18760
void Skel_b18760() {}
// @ 0x00b188b0
void Skel_b188b0() {}
// @ 0x00b18960
void Skel_b18960() {}
// @ 0x00b189c0
void Skel_b189c0() {}
// @ 0x00b18d50
void Skel_b18d50() {}
// @ 0x00b18d90
void Skel_b18d90() {}
// @ 0x00b18db0
void Skel_b18db0() {}
// @ 0x00b18dd0
void Skel_b18dd0() {}
// @ 0x00b18e40
void Skel_b18e40() {}
// @ 0x00b18e70
void Skel_b18e70() {}
// @ 0x00b18ef0
void Skel_b18ef0() {}
// @ 0x00b18f70
void Skel_b18f70() {}
// @ 0x00b18f90
void Skel_b18f90() {}
// @ 0x00b19000
void Skel_b19000() {}
// @ 0x00b19180
void Skel_b19180() {}
// @ 0x00b19290
void Skel_b19290() {}
