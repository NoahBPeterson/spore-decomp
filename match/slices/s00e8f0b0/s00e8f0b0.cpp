// Slice s00e8f0b0 (batch hk2, slice 3). Region 0x00e8f120-0x00e8f1bd.
// SP::cMineralView::UpdateLoyaltyBar (159 bytes).
#include "types.h"

void* operator_new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0 EA 6-arg new

struct cSPUIMeter_e8f0 {
  void* Init(unsigned a, unsigned b, unsigned c, const wchar_t* name, unsigned d);  // 0x00e06a10 thiscall, ret 0x14, returns this
  void  Shutdown(int flag);       // 0x00e06940 SP::cSPUIMeter::Shutdown, thiscall
  void  Func_e06ca0(unsigned v);  // 0x00e06ca0 thiscall, ret 4
  void  Func_e06cf0(void* obj);   // 0x00e06cf0 thiscall, ret 4
};

struct cMineralView_e8f0 {
  uint32_t pad[3];                // base cSpatialObjectView header up to +0xc
  void*    mpObject;              // +0x0c  EA::AutoRefCount<cSpatialObject> (raw pointer)

  cSPUIMeter_e8f0* UpdateLoyaltyBar(cSPUIMeter_e8f0* p, char bShow, unsigned hdr);  // 0x00e8f120
};

// @ 0x00e8f120
cSPUIMeter_e8f0* cMineralView_e8f0::UpdateLoyaltyBar(cSPUIMeter_e8f0* p, char bShow, unsigned hdr) {
  if (bShow != 0) {
    unsigned v;
    if (mpObject) {
      void* obj = mpObject;
      v = ((unsigned (__thiscall*)(void*, unsigned))((*(void***)obj)[46]))(obj, 0x403df5f);
    } else {
      v = 0;
    }
    if (p == 0) {
      cSPUIMeter_e8f0* np;
      void* mem = operator_new(0x50, (const char*)0x013f6b3c, 0, 0, 0, 0);
      if (mem) {
        np = (cSPUIMeter_e8f0*)((cSPUIMeter_e8f0*)mem)->Init(hdr, 0x3ffb28c, 0x4d428c1, L"CivConversionBar", 0xe9f70df9);
      } else {
        np = 0;
      }
      np->Func_e06ca0(v);
      np->Func_e06cf0(mpObject);
      return np;
    }
    return p;
  }
  if (p) { p->Shutdown(1); p = 0; }
  return p;
}
