// Slice s005ecf80: SP::cSPPaletteItemRollover (rollover item UI) plus the name-generator
// dispatcher at 0x005ecf80.  Layout offsets taken from the binary.
#include "types.h"

#define PV(n) virtual void _pv##n();

// Read a virtual-method pointer out of an object's vtable at byte offset n.
template <typename Fn>
static Fn vslot(void* object, unsigned int n) {
  return (Fn)(*(void**)((char*)(*(void**)object) + n));
}

namespace eastl {
// Fixed-width string used by the name generator (3 pointers + empty allocator).
template <typename T>
struct basic_string {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator;  // empty; padded to 4 (string is 16 bytes)

  void RangeInitialize(const T* p);  // 0x00579a90
};
}  // namespace eastl

// A render-target-like object whose Render() slot is called directly after AddBoundingBox.
class cRenderTarget {
 public:
  void Render();
};

// 3-slot refcounted object (Release at vtable +0x08).
class cRefObj3 {
 public:
  PV(0) PV(1)
  virtual void Release();  // +0x08
};

void* __stdcall AddBoundingBox(void* box, int arg, int flag);

// cSPUIPropertyLayout base: vtable +0, refcount +4, layout object +0x0c.
class cSPUIPropertyLayout {
 public:
  PV(0) PV(1)
  ~cSPUIPropertyLayout();                  // 0x00828670
  void SetFlag(int value);                 // 0x00828020
  uint8_t Init();                          // 0x00828250
  bool func24();                           // 0x00828be0
  void SetKey(const wchar_t* key, int tag);  // 0x00827fc0
  void SetRootWindowId(unsigned int id);   // 0x00c87bc0
};

// Embedded layout object at +0x0c (vtable at +0).
class cSPUILayout {
 public:
  void* FindWindowByID(int id, int flag);  // 0x008105b0
};
void* __cdecl SPUIHelpers_GetLayoutManager(int tag);                     // 0x00805070
void* __fastcall cSPUILayoutManager_GetWorldMainWindow(void* self);      // 0x00810620

namespace SP {
class cSPPaletteItemRollover {
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

  cSPPaletteItemRollover(bool flag);
  void* ScalarDeletingDtor(unsigned int flags);

  void AddBox(int arg);
  void GetAreaPair(int* out);
  void ResetRollover();
  uint8_t Init();
  void Destroy();
};

// @ 0x005ED340
void cSPPaletteItemRollover::GetAreaPair(int* out) {
  struct IntPair {
    int a;
    int b;
  };
  *(IntPair*)out = *(IntPair*)((char*)this + 0x1c);
}

// @ 0x005ED320
void cSPPaletteItemRollover::AddBox(int arg) {
  void* box = mWinPrice;
  void* target = AddBoundingBox(box, arg, 1);
  ((cRenderTarget*)target)->Render();
}

// @ 0x005ED6C0
void cSPPaletteItemRollover::ResetRollover() {
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

// @ 0x005ED360
// Constructor: run the CPL base ctor, install the two vtables, zero the window
// pointers and refcounted slots, then key the layout and set its root window id.
cSPPaletteItemRollover::cSPPaletteItemRollover(bool flag) {
  // Base layout ctor.
  ((void (__thiscall*)(cSPPaletteItemRollover*))0x008286d0)(this);
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

// @ 0x005ED420
uint8_t cSPPaletteItemRollover::Init() {
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

// @ 0x005ED650
void cSPPaletteItemRollover::Destroy() {
  if (mWinPrice != 0) {
    if (vslot<int (__thiscall*)(void*)>(mWinPrice, 0x10)(mWinPrice) != 0) {
      void* w = vslot<void* (__thiscall*)(void*)>(mWinPrice, 0x10)(mWinPrice);
      vslot<void (__thiscall*)(void*, void*)>(w, 0xdc)(w, mWinPrice);
    }
  }
  mFieldB8 = true;
  if (mFieldB4 != 0) {
    cRefObj3* p = *(cRefObj3* volatile*)&mFieldB4;
    if (p != 0) {
      mFieldB4 = 0;
      vslot<void (__thiscall*)(void*)>(p, 8)(p);
    }
  }
  ((cSPUIPropertyLayout*)this)->func24();
}

// @ 0x005ED700
// Scalar deleting destructor: release the two refcounted slots, run the base
// destructor, then free the object when the low bit of `flags` is set.
void* cSPPaletteItemRollover::ScalarDeletingDtor(unsigned int flags) {
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

// ---------------------------------------------------------------------------------------------
// 0x005ecf80: a name-generating dispatcher.  The `this` object (ecx) holds a set of
// string vectors; `key` (arg 1) selects which ones feed the generator, and the result
// string (arg 2) is written and returned.
// String-collection shapes stored inside the name generator (sizes measured from
// the field offsets the binary uses).
struct NameVec20 { uint32_t mWords[5]; };    // 20-byte string vector
struct NameVec28 { uint32_t mWords[7]; };    // 28-byte string collection
struct NameVec40 { uint32_t mWords[10]; };   // 40-byte string collection
struct NameVec60 { uint32_t mWords[15]; };   // 60-byte string collection

class cSPNameGenerator {
 public:
  uint32_t pad00[5];           // +0x00
  NameVec20 mVec14;            // +0x14
  NameVec20 mVec28;            // +0x28
  NameVec20 mVec3c;            // +0x3c
  NameVec20 mVec50;            // +0x50
  NameVec20 mVec64;            // +0x64
  NameVec20 mVec78;            // +0x78
  NameVec20 mVec8c;            // +0x8c
  NameVec20 mVecA0;            // +0xa0
  uint32_t padB4[10];          // +0xb4
  NameVec60 mVecDc;            // +0xdc
  NameVec60 mVec118;           // +0x118
  NameVec60 mVec154;           // +0x154
  NameVec60 mVec190;           // +0x190
  NameVec60 mVec1cc;           // +0x1cc
  NameVec60 mVec208;           // +0x208
  uint8_t mFlag244;            // +0x244
  uint8_t pad245[3];
  NameVec40 mVec248;           // +0x248
  NameVec40 mVec270;           // +0x270
  NameVec40 mVec298;           // +0x298
  NameVec40 mVec2c0;           // +0x2c0
  NameVec40 mVec2e8;           // +0x2e8
  NameVec40 mVec310;           // +0x310
  NameVec40 mVec338;           // +0x338
  NameVec40 mVec360;           // +0x360
  NameVec28 mVec388;           // +0x388
  NameVec20 mVec3a4;           // +0x3a4
  uint8_t mFlag3b8;            // +0x3b8
  uint8_t mFlag3b9;            // +0x3b9
  uint8_t pad3ba;
  uint8_t mFlag3bb;            // +0x3bb
  uint8_t mFlag3bc;            // +0x3bc
  uint8_t mFlag3bd;            // +0x3bd
  uint8_t mFlag3be;            // +0x3be
  uint8_t mFlag3bf;            // +0x3bf

  void* CreateRandomName(void* out, void* vec, bool flag);                    // 0x005ebb00
  void* PickName(void* out, void* a, void* b, void* c, void* d, bool flag);   // 0x005ec370
  void* CreateRandomCompoundName(void* out, void* a, void* b, void* c, void* d,
                                 void* e, bool flag);                          // 0x005eb540
  void* GetName(void* out, unsigned int key);                                 // 0x005ecf80
};

extern void* gDefaultWStr;   // 0x015f0a1c

// @ 0x005ECF80
// Dispatch on the part key: pick the right set of string vectors for the part and
// generate a name into `out`.  Unknown keys (and unset names) produce an empty string.
void* cSPNameGenerator::GetName(void* out, unsigned int key) {
  char* const o = (char*)out;
  if ((int)key < 0x7e1310b) {
    if (key == 0x7e1310a) {
      if (!mFlag244) {
        CreateRandomName(o, &mVec3a4, true);
        return out;
      }
      if (mFlag3b8)
        PickName(o, &mVec270, &mVec388, &mVec3a4, this, true);
      else
        CreateRandomCompoundName(o, &mVec270, &mVecA0, &mVec388, &mVec3a4, this, true);
      return out;
    }
    if ((int)key < 0x3dee115) {
      if (key == 0x3dee114) {
        if (!mFlag244) {
          CreateRandomName(o, &mVec8c, false);
          return out;
        }
        if (mFlag3bf)
          PickName(o, &mVec360, &mVec388, &mVec3a4, &mVec8c, false);
        else
          CreateRandomCompoundName(o, &mVec360, &mVec208, &mVec388, &mVec3a4, &mVec8c, false);
        return out;
      }
      if (key == 0xba1fd5ac) {
        if (!mFlag244) {
          CreateRandomName(o, &mVec78, false);
          return out;
        }
        if (mFlag3be)
          PickName(o, &mVec338, &mVec388, &mVec3a4, &mVec78, false);
        else
          CreateRandomCompoundName(o, &mVec338, &mVec1cc, &mVec388, &mVec3a4, &mVec78, false);
        return out;
      }
      if (key == 0xdeb2d943) {
        if (!mFlag244) {
          CreateRandomName(o, &mVec28, false);
          return out;
        }
        PickName(o, &mVec298, &mVec388, &mVec3a4, &mVec28, false);
        return out;
      }
      goto empty_string;
    }
    if (key == 0x55ea490) {
      if (!mFlag244) {
        CreateRandomName(o, &mVec50, false);
        return out;
      }
      if (mFlag3bc)
        PickName(o, &mVec2e8, &mVec388, &mVec3a4, &mVec50, false);
      else
        CreateRandomCompoundName(o, &mVec2e8, &mVec118, &mVec388, &mVec3a4, &mVec50, false);
      return out;
    }
    goto empty_string;
  }
  if (key == 0x51aa76bb) {
    if (!mFlag244) {
      CreateRandomName(o, &mVec3c, false);
      return out;
    }
    if (mFlag3bb)
      PickName(o, &mVec2c0, &mVec388, &mVec3a4, &mVec3c, false);
    else
      CreateRandomCompoundName(o, &mVec2c0, &mVec190, &mVec388, &mVec3a4, &mVec3c, false);
    return out;
  }
  if (key == 0x58f4c251) {
    if (!mFlag244) {
      CreateRandomName(o, &mVec64, false);
      return out;
    }
    if (mFlag3bd)
      PickName(o, &mVec310, &mVec388, &mVec3a4, &mVec64, false);
    else
      CreateRandomCompoundName(o, &mVec310, &mVec154, &mVec388, &mVec3a4, &mVec64, false);
    return out;
  }
  if (key == 0x7cab064c) {
    if (!mFlag244) {
      CreateRandomName(o, &mVec14, true);
      return out;
    }
    if (mFlag3b9)
      PickName(o, &mVec248, &mVec388, &mVec3a4, &mVec14, true);
    else
      CreateRandomCompoundName(o, &mVec248, &mVecDc, &mVec388, &mVec3a4, &mVec14, true);
    return out;
  }

empty_string:
  {
    eastl::basic_string<wchar_t>* s = (eastl::basic_string<wchar_t>*)o;
    s->mpBegin = 0;
    s->mpEnd = 0;
    s->mpCapacity = 0;
    s->RangeInitialize((const wchar_t*)gDefaultWStr);
  }
  return out;
}
