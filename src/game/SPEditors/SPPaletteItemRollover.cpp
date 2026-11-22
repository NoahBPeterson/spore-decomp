// src/game/SPEditors/SPPaletteItemRollover.cpp -- migrated from slice(s) s005ecf80 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPaletteItemRollover.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// Declaration-only base view. No object or vtable is emitted here.
class cSPUIPropertyLayout {
 public:
  virtual bool Shutdown();  // 0x00828be0; ECX receiver, AL result, no stack arguments.
  void SetFlag(int value);  // 0x00828020
  void SetKey(const wchar_t* key, int tag);  // 0x00827fc0
  void SetRootWindowId(unsigned int id);     // 0x00c87bc0
  uint8_t Init();           // 0x00828250
  ~cSPUIPropertyLayout();   // 0x00828670
};

// Embedded layout object at +0x0c (vtable at +0).
class cSPUILayout {
 public:
  void* FindWindowByID(int id, int flag);  // 0x008105b0
};

// Read a virtual-method pointer out of an object's vtable at byte offset n.
template <typename Fn>
static Fn vslot(void* object, unsigned int n) {
  return (Fn)(*(void**)((char*)(*(void**)object) + n));
}

// 3-slot refcounted object (Release at vtable +0x08), as the slice's cRefObj3.
class cRefObj3 {
 public:
  virtual void _pv0();
  virtual void _pv1();
  virtual void Release();  // +0x08
};

void* __cdecl SPUIHelpers_GetLayoutManager(int tag);                 // 0x00805070
void* __fastcall cSPUILayoutManager_GetWorldMainWindow(void* self);  // 0x00810620
void operator delete(void*);

// ---- items of slice s005ecf80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cSPPaletteItemRollover_s005e_cf80 {
 public:
  char pad00[0x0c];
  char mLayout[0x78 - 0x0c];    // +0x0c  embedded cSPUILayout object
  void* mWinPrice;              // +0x78
  void* mWinVerbIcons;          // +0x7c
  void* mWinAbilityLines;       // +0x80
  void* mWinName;               // +0x84
  void* mWinHeader;             // +0x88
  char  pad8c[4];
  void* mInfo;                  // +0x90
  void* mAbilities;             // +0x94
  int   mInitFlags;             // +0x98  (three flag bytes packed)
  void* mField9c;               // +0x9c
  void* mIconImageGroup;        // +0xa0
  int   mFieldA4;               // +0xa4
  int   mFieldA8;               // +0xa8
  int   mFieldAc;               // +0xac
  int   mFieldB0;               // +0xb0
  int   mFieldB4;               // +0xb4
  bool  mFieldB8;               // +0xb8
  bool  mFieldB9;               // +0xb9
  char  padBa[2];
  float mFieldBc;               // +0xbc
  float mFieldC0;               // +0xc0

  cSPPaletteItemRollover_s005e_cf80(bool flag);
  void* ScalarDeletingDtor(unsigned int flags);
  void AddBox(int arg);
  void GetAreaPair(int* out);
  void ResetRollover();
  uint8_t Init();
  bool Shutdown();
  void Destroy();
};  // namespace SP
}
// ---- items of slice s005ecf80 end

// @ 0x005ed360
namespace SP {
cSPPaletteItemRollover_s005e_cf80::cSPPaletteItemRollover_s005e_cf80(bool flag)
{
  // Base layout ctor.
  ((void (__thiscall*)(cSPPaletteItemRollover_s005e_cf80*))0x008286d0)(this);
  mWinPrice = 0;
  mWinVerbIcons = 0;
  mWinAbilityLines = 0;
  mWinName = 0;
  mWinHeader = 0;
  mInfo = 0;
  mAbilities = 0;
  mFieldA4 = 0;
  mFieldAc = 0;
  mFieldB0 = 0;
  mFieldB4 = 0;
  *(void**)this = (void*)0x013f9854;
  *(void**)((char*)this + 4) = (void*)0x013f9844;
  mFieldB8 = true;
  mFieldB9 = flag;
  mFieldBc = 0.0f;
  mInitFlags = 0;
  mField9c = 0;
  mFieldA8 = 0;
  mIconImageGroup = 0;
  ((cSPUIPropertyLayout*)this)->SetKey(L"EditorPaletteItemRollover", 0x40464100);
  ((cSPUIPropertyLayout*)this)->SetRootWindowId(0x5011ad2);
}
}  // namespace SP

// @ 0x005ed420
namespace SP {
uint8_t cSPPaletteItemRollover_s005e_cf80::Init()
{
  if (!mFieldB8)
    return 1;
  const uint8_t initResult = ((cSPUIPropertyLayout*)this)->Init();
  if (!initResult)
    return initResult;

  cSPUILayout* layout = (cSPUILayout*)mLayout;   // embedded layout at +0x0c
  if ((mWinPrice = layout->FindWindowByID(0x5011ad2, 1)) == 0)
    goto cleanup;

  vslot<void (__thiscall*)(void*, int)>(mWinPrice, 0x5c)(mWinPrice, -1);
  ((cSPUIPropertyLayout*)this)->SetFlag(0);

  mWinVerbIcons = layout->FindWindowByID(0x125f2c4f, 1);
  mWinAbilityLines = layout->FindWindowByID(0x325f2c75, 1);
  mWinName = layout->FindWindowByID(0xb33c8204, 1);
  mAbilities = layout->FindWindowByID(0x70524f6b, 1);
  mWinHeader = layout->FindWindowByID(0x23288a3, 1);
  mInitFlags = (int)layout->FindWindowByID(0x666b472, 1);
  mField9c = layout->FindWindowByID(0x5c89991, 1);
  mInfo = layout->FindWindowByID(0x4c01a78, 1);

  if (mInfo != 0) {
    float* price = (float*)vslot<void* (__thiscall*)(void*)>(mWinPrice, 0x38)(mWinPrice);
    const float x0 = price[0];
    const float y0 = price[1];
    const float x1 = price[2];
    const float y1 = price[3];
    float* info = (float*)vslot<void* (__thiscall*)(void*)>(mInfo, 0x38)(mInfo);
    const float ix0 = info[0];
    const float iy1 = info[3];
    const float ix1 = info[2];
    mFieldBc = (y1 - y0) - iy1;
    mFieldC0 = (x1 - x0) - (ix1 - ix0);
  }

  mIconImageGroup = layout->FindWindowByID(0x64a8a83, 1);
  mFieldA4 = (int)layout->FindWindowByID(0x64a7e23, 1);
  mFieldA8 = (int)layout->FindWindowByID(0x685d26a, 1);
  mFieldAc = (int)layout->FindWindowByID(0x440b6b8, 1);

  if (vslot<int (__thiscall*)(void*)>(mWinPrice, 0x10)(mWinPrice) == 0) {
    void* mgr = SPUIHelpers_GetLayoutManager(0x5b598f6);
    void* world = cSPUILayoutManager_GetWorldMainWindow(mgr);
    vslot<void (__thiscall*)(void*, void*)>(world, 0xd8)(world, mWinPrice);
  }

cleanup:
  if (mFieldB4) {
    int obj = mFieldB4;
    mFieldB4 = 0;
    vslot<void (__thiscall*)(void*)>((void*)obj, 8)((void*)obj);
  }
  mFieldB8 = false;
  return initResult;
}
}  // namespace SP

// @ 0x005ed650
namespace SP {
bool cSPPaletteItemRollover_s005e_cf80::Shutdown()
{
  if (mWinPrice != 0) {
    if (((void* (__thiscall*)(void*))(*(void***)mWinPrice)[4])(mWinPrice) != 0) {
      void* parent = ((void* (__thiscall*)(void*))(*(void***)mWinPrice)[4])(mWinPrice);
      ((void (__thiscall*)(void*, void*))(*(void***)parent)[55])(parent, mWinPrice);
    }
  }
  mFieldB8 = true;
  if (mFieldB4 != 0) {
    void* previous = *(void* volatile*)&mFieldB4;
    if (previous != 0) {
      mFieldB4 = 0;
      ((int (__thiscall*)(void*))(*(void***)previous)[2])(previous);
    }
  }
  return ((cSPUIPropertyLayout*)this)->cSPUIPropertyLayout::Shutdown();
}
}  // namespace SP

// @ 0x005ed6c0
namespace SP {
void cSPPaletteItemRollover_s005e_cf80::ResetRollover()
{
  if (!mFieldB8)
    ((cSPUIPropertyLayout*)this)->SetFlag(0);
  if (mFieldB4) {
    cRefObj3* pB4 = *(cRefObj3* volatile*)&mFieldB4;
    if (pB4) {
      mFieldB4 = 0;
      pB4->Release();
    }
  }
}
}  // namespace SP

// @ 0x005ed700
namespace SP {
void* cSPPaletteItemRollover_s005e_cf80::ScalarDeletingDtor(unsigned int flags)
{
  cRefObj3* p4 = (cRefObj3*)mFieldB4;
  if (p4 != 0)
    p4->Release();
  cRefObj3* p0 = (cRefObj3*)mFieldB0;
  if (p0 != 0)
    p0->Release();
  ((cSPUIPropertyLayout*)this)->~cSPUIPropertyLayout();
  if (flags & 1)
    operator delete(this);
  return this;
}
}  // namespace SP
