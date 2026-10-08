// Slice s00dc77d0 (batch hk2, slice 5). Region 0x00dc7e00-0x00dc7ea7.
// Order object Init: copies src fields, swaps the visual-effect AutoRefCount (+0x94), applies the
// effect with the order's +0x78 value, and releases the animating-creature ref at +0x9c.
#include "types.h"

struct cSrc5 {                     // param_2: object pointer at +0, uint at +0x14
  void*    mpObj;                  // +0x00 AutoRefCount<T> (raw pointer)
  uint32_t pad0[4];                // +0x04..+0x13
  uint32_t mVal;                   // +0x14
};

struct cSub5 {                     // sub-object at +0x64 (size 0x14)
  uint8_t pad[0x14];
  void SetFrom(cSrc5* src);        // 0x00ca0940 thiscall, ret 4
};

struct cMgr5 {                     // returned by FUN_00b3d290 (cdecl, no args)
  uint32_t Get();                  // 0x00ac15e0 thiscall, returns eax
};

struct cEffect5 {                  // EA::Swarm::cIVisualEffect (AutoRefCount target at +0x94)
  void Apply(uint32_t v);          // 0x00bdf6d0 thiscall, ret 4
};

struct cAnim5 {                    // SP::cAnimatingCreature (AutoRefCount target at +0x9c)
  void Release();                  // 0x00a05270 thiscall
};

void*    __cdecl FUN_00b3d290();   // 0x00b3d290 (returns a global-derived manager pointer)

struct cConvertCityOrder5 {
  uint8_t   pad0[0x64];
  cSub5     mSub64;                // +0x64
  uint32_t  m78;                   // +0x78
  uint8_t   pad1[0x90 - 0x7c];
  uint32_t  mGen90;                // +0x90
  void*     mEffect94;             // +0x94 AutoRefCount<cIVisualEffect>
  uint32_t  m98;                   // +0x98
  void*     mAnim9c;               // +0x9c AutoRefCount<cAnimatingCreature>
  uint8_t   pad2[0xac - 0xa0];
  uint8_t   mbFlagAC;              // +0xac

  void Init(cSrc5* src);           // 0x00dc7e00 thiscall, ret 4
};

// @ 0x00dc7e00
void cConvertCityOrder5::Init(cSrc5* src) {
  mSub64.SetFrom(src);
  cMgr5* mgr = (cMgr5*)FUN_00b3d290();
  mGen90 = mgr->Get();

  void* obj = src->mpObj;
  void* nw;
  if (obj) {
    nw = ((void* (__thiscall*)(void*, uint32_t))((*(void***)obj)[3]))(obj, 0x3d5c477);
  } else {
    nw = 0;
  }
  void* old = mEffect94;
  if (nw != old) {
    if (nw) ((void (__thiscall*)(void*))((*(void***)nw)[0]))(nw);
    mEffect94 = nw;
    if (old) ((void (__thiscall*)(void*))((*(void***)old)[1]))(old);
  }
  m98 = src->mVal;
  ((cEffect5*)mEffect94)->Apply(m78);
  if (mAnim9c) {
    cAnim5* a = (cAnim5*)mAnim9c;
    mAnim9c = 0;
    a->Release();
  }
  mbFlagAC = 0;
}
