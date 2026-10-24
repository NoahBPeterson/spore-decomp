// Slice s00e20860 (batch gold6, worker 44). Region 0x00e20860-0x00e217c0.
// Mixed bag: Swarm/Simulator transform helpers (Swarm::MapDescription,
// Simulator::cCreatureAbility, cSPTransform/cSPBoundingBox) plus a few
// cSPUIPosseItem methods (state machine, blink_for_a_motive, distress helpers).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef          short s16;
typedef          char  s8;

// ---- external callees (address in comment) ------------------------------
void* __cdecl operator_new(u32 size, const char* file, int, int, int, int); // 0xf473a0
void  __cdecl operator_delete_(void*);                                      // 0xf47380
void* __cdecl FUN_0067dcc0();        // 0x0067dcc0 SP::MessageServer()
void* __cdecl FUN_0067cad0();        // 0x0067cad0 cSPBoundingBox::AddBoundingBox()
void* __cdecl FUN_006c10e0();        // 0x006c10e0 Sound/Audio::GetSystemAT
void* __cdecl FUN_00b3d350();        // 0x00b3d350 SP::PlanetModel()
void* __cdecl FUN_00b88590(void*);   // 0x00b88590 SP::cPlanetModel::GetContinent
void  __cdecl FUN_00478db0(void*);   // 0x00478db0
void* __cdecl FUN_0080fac0(void*, void*, int);  // 0x0080fac0 cSPUILayeredObject::MethodFAC0
void  __cdecl FUN_0080ea50(void*);   // 0x0080ea50 RemoveAllModels
void  __cdecl FUN_0080d790(void*, int, int);    // 0x0080d790
void  __cdecl FUN_004099b0(float);   // 0x004099b0 EA::Swarm::cTransform::PreRotateY
void  __cdecl FUN_00579a90(void*, const wchar_t*); // 0x00579a90 wstring::range_initialize
void  __cdecl FUN_00537dc0(void*, const void*);    // 0x00537dc0 cSPTransformOps::Assign
void  __cdecl FUN_0041cb40(void*, const void*);    // 0x0041cb40 Matrix3::Assign
void  __cdecl FUN_006bac90(void*, void*);          // 0x006bac90
void  __cdecl FUN_006b9440(void*);                 // 0x006b9440 Basis3::Build
void  __cdecl FUN_004e0850(void*, const wchar_t*, ...); // 0x004e0850 wstring format
void  __cdecl FUN_00881ea0(double, void*, int, const wchar_t*); // 0x00881ea0 SetNumberString
void  __cdecl FUN_0077d1d0(void*);   // 0x0077d1d0 Simulator::cCreatureAbility ctor
void* __cdecl FUN_004558a0(void*, void*, int); // 0x004558a0 VectorInsertU32
void  __cdecl FUN_0061df40(void*);   // 0x0061df40 MessageBasicRC ctor wrapper
void* __cdecl FUN_00421c80(void*);   // 0x00421c80 SlotMessage::Construct
void  __cdecl WStr_Append(void*, const wchar_t*); // 0x00429580
void* __cdecl FUN_008061c0(void*, int); // 0x008061c0 SPUIHelpers::GetImageFromLayout
u32   __cdecl FUN_007f5eb0(u32, u32, float); // 0x007f5eb0 Color::Lerp
void  __cdecl FUN_00808210(void*, float);    // 0x00808210 SetWindowScale
void  __cdecl FUN_00e205e0(void*);   // 0x00e205e0 (same obj, thiscall reg-arg)
void  __cdecl FUN_00e20f10(void*, void*); // 0x00e20f10 (same obj)

// Win32 / runtime helpers used by the installer state machine.
extern "C" char* __stdcall GetCommandLineA();
extern "C" unsigned long __stdcall GetCurrentProcessId();
extern "C" double __cdecl sqrt(double);
void __cdecl EA_ConvertToString16(wchar_t* out, const char* in);

extern float DAT_016ac208, DAT_016ac20c, DAT_016ac210;   // Translation
extern float DAT_016ac214[9];                            // rotation
extern float DAT_016a0dd0, DAT_016a0dd4, DAT_016a0dd8;   // offset vector
extern float DAT_016a0d80;                               // divisor
extern float DAT_013f4fd0;                               // 2^32
extern float DAT_0148054c;                               // 2*pi
extern float DAT_01488774;                               // 0.1f
extern float DAT_013ec4d0;                               // 1.0f clamp
extern float DAT_01485720;                               // 1.0f
extern const wchar_t DAT_01480584[], DAT_01480588[];

// ======================================================================
// 0x00e20860 - big state-machine driver for the item installer wizard.
// `this` fields (retail layout):
//   +0x08 void* mpObject;   +0x10 bool(*)(void) IsReady;
//   +0x1c bool(*)(u32,void*) ; +0x24 bool(*)(u32,void*);
//   +0x2c bool(*)(void*,void*,u32,void*) check; +0x30 void(*)(u32,void*,void*);
//   +0x3c int mState;  +0x54 cInstallItem* mpItems; +0x58 int mCount;
//   +0x5c int mIndex;  +0x64 cControlValue mValue;
// This is a register-arg static helper in an unnamed TU; kept as a free
// function taking `this` in ecx (thiscall) - equivalence-only.
// ======================================================================

// ----------------------------------------------------------------------
// tiny cSPUIPosseItem-ish and misc helpers used by the byte-exact ones
// ----------------------------------------------------------------------

// @ 0x00e21590
// returns one of two wide-string constants based on index
const wchar_t* __stdcall FUN_00e21590(int idx) {
  switch (idx) {
  case 1:  return (const wchar_t*)0x3d99184;
  case 0:
  default: return (const wchar_t*)0x3d99162;
  }
}

// @ 0x00e21620
void __stdcall FUN_00e21620(u32* out) {
  out[0] = 0;
  out[1] = 1;
}

// ----------------------------------------------------------------------
// cSPUIPosseItem retail layout (shifted -4 from the dev PDB after the bases)
// ----------------------------------------------------------------------
class cSPUIPosseItem;

// @ 0x00e215b0
// true when mDistress[0] <= mDistress[1]
int __fastcall FUN_00e215b0(cSPUIPosseItem* self) {
  return *(const s32*)((const char*)self + 0xa8) <= *(const s32*)((const char*)self + 0xac);
}

// @ 0x00e21700
struct VObj1 { void** vtbl; };
bool __cdecl FUN_00e21700(void* p) {
  VObj1* w = (VObj1*)p;
  ((void(__thiscall*)(VObj1*, int))w->vtbl[0xb8 / 4])(w, 1);
  return true;
}

// @ 0x00e21720
bool __cdecl FUN_00e21720(void* p) {
  VObj1* w = (VObj1*)p;
  ((void(__thiscall*)(VObj1*, int))w->vtbl[0xb8 / 4])(w, 2);
  return true;
}

// ----------------------------------------------------------------------
// Swarm model object (a renderable model referenced by the transform
// helpers). Retail layout:
//   +0x00 RefObj* mpRef (interface whose +0 is a vtable);
//   +0x04 u32 mRefFlags; +0x08 u16 mFlags; +0x0a s16 mRefCount;
//   +0x0c float mPosX, +0x10 mPosY, +0x14 mPosZ, +0x18 float mAngle;
//   +0x40 s32 mRefCountObject;
// ----------------------------------------------------------------------
struct RefObj { void** vtbl; };   // +0x00 vtable

struct SwModel {
  RefObj* mpRef;          // +0x00
  u32    mRefFlags;       // +0x04
  u16    mFlags;          // +0x08
  s16    mRefCount;       // +0x0a
  float  mPosX;           // +0x0c
  float  mPosY;           // +0x10
  float  mPosZ;           // +0x14
  float  mAngle;          // +0x18
  u8     pad1c[0x40 - 0x1c];
  s32    mRefCountObject; // +0x40
};

// virtual release at RefObj vtbl +0x170: (this=mpRef, model, bool)
void SwModel_Release(SwModel* m, bool unk) {
  RefObj* r = m->mpRef;
  ((void(__thiscall*)(RefObj*, SwModel*, int))r->vtbl[0x170 / 4])(r, m, unk);
}

// A pair of SwModel* helpers (this in ecx, one float stack arg).
struct SwModelPair {
  SwModel* p0;            // +0x00
  SwModel* p1;            // +0x04
  void*    p2;            // +0x08
};

// @ 0x00e20d30
void __fastcall FUN_00e20d30(SwModelPair* self, s32, float angle) {
  if (self->p0) {
    self->p0->mRefCount++;
    self->p0->mAngle = angle;
  }
  if (self->p1) {
    self->p1->mRefCount++;
    self->p1->mAngle = angle;
  }
}

// @ 0x00e20d60
void __fastcall FUN_00e20d60(SwModelPair* self, s32) {
  if (self->p0) {
    self->p0->mPosX += DAT_016a0dd0;
    self->p0->mPosY += DAT_016a0dd4;
    self->p0->mPosZ += DAT_016a0dd8;
    self->p0->mFlags |= 4;
    self->p0->mRefCount++;
  }
  if (self->p1) {
    self->p1->mPosX += DAT_016a0dd0;
    self->p1->mPosY += DAT_016a0dd4;
    self->p1->mPosZ += DAT_016a0dd8;
    self->p1->mFlags |= 4;
    self->p1->mRefCount++;
  }
}

// @ 0x00e20e00
void __fastcall FUN_00e20e00(SwModelPair* self) {
  if (self->p0) {
    SwModel* m = self->p0;
    self->p0 = 0;
    if (m->mRefCountObject <= 1)
      SwModel_Release(m, (m->mRefFlags >> 31) != 0);
    else
      m->mRefCountObject--;
  }
  if (self->p1) {
    SwModel* m = self->p1;
    self->p1 = 0;
    if (m->mRefCountObject <= 1)
      SwModel_Release(m, (m->mRefFlags >> 31) != 0);
    else
      m->mRefCountObject--;
  }
}

// @ 0x00e20e80
void __fastcall FUN_00e20e80(SwModelPair* self) {
  if (self->p0) {
    SwModel* m = self->p0;
    self->p0 = 0;
    if (m->mRefCountObject <= 1)
      SwModel_Release(m, (m->mRefFlags >> 31) != 0);
    else
      m->mRefCountObject--;
  }
  if (self->p1) {
    SwModel* m = self->p1;
    self->p1 = 0;
    if (m->mRefCountObject <= 1)
      SwModel_Release(m, (m->mRefFlags >> 31) != 0);
    else
      m->mRefCountObject--;
  }
  if (self->p2) {
    void* m = self->p2;
    self->p2 = 0;
    ((void(__thiscall*)(void*))(*(void***)m)[8 / 4])(m);
  }
}

// @ 0x00e21040
// Rotate both models by `frame` and refresh their transforms.
void __fastcall FUN_00e21040(SwModelPair* self, s32, s32 frame) {
  if (!self->p0)
    return;
  float f = (float)frame;
  if (frame < 0)
    f += DAT_013f4fd0;
  f = (f / DAT_016a0d80) * DAT_0148054c;
  ((void(__thiscall*)(void*, float))FUN_004099b0)((char*)self->p0 + 8, f);
  ((void(__thiscall*)(void*, float))FUN_004099b0)((char*)self->p1 + 8, f);
  FUN_00e20f10(self->p0, (float*)&DAT_016a0dd0);
  FUN_00e20f10(self->p1, (float*)&DAT_016a0dd0);
}

// @ 0x00e21530
// Set a posse-item image from a layout, unless it already equals mLastImageID.
void __fastcall FUN_00e21530(void* self_, void*, int id, void* layout, void* extra) {
  int cur = *(int*)((char*)self_ + 0x6c);
  if (id == cur)
    return;
  void* img = FUN_008061c0(layout, id);
  ((void(__thiscall*)(void*, int, void*, void*))(*(void***)self_)[0xa0 / 4])(self_, id, img, extra);
}

// @ 0x00e215d0
// Change mState (a window-state value) only if it actually differs.
void __fastcall FUN_00e215d0(void* self_, s32, u8 flags) {
  u32 state;
  if (flags & 1) {
    bool b = (flags & 2) != 0;
    state = b * 2 + 2;
  } else {
    state = (flags & 2) | 1;
  }
  if (*(u32*)((char*)self_ + 0x94) == state)
    return;
  ((void(__thiscall*)(void*, u32))(*(void***)self_)[0xd0 / 4])(self_, state);
}

// ----------------------------------------------------------------------
// cSPUIPosseItem retail layout (dev-PDB offsets shifted by -4 onward from
// mState). Only the members used by this slice are named.
// ----------------------------------------------------------------------
class cSPUIPosseItem2 {
public:
  void**  vtbl;                 // +0x00
  u8      pad04[0x94 - 0x04];
  s32     mState;               // +0x94 (retail; PDB 0x98)
  u8      pad98[0xa8 - 0x98];
  s32     mDistress[3];         // +0xa8 (retail; PDB 0xac)
  u8      padb4[0xb8 - 0xb4];
  u32     mBlinkerColorFrom;    // +0xb8 (retail; PDB 0xc0)
  u32     mBlinkerColorTo;      // +0xbc
  float   mBlinkerScaleFrom;    // +0xc0
  float   mBlinkerScaleTo;      // +0xc4
};

// @ 0x00e21640
// Blink the given window's colour/scale for the motive at index `idx`.
bool __fastcall cSPUIPosseItem_blink_for_a_motive(cSPUIPosseItem2* self, s32, void* window,
                                                  int idx, float t) {
  if (self->mDistress[idx - 1] == 2 /* kDistressHigh */) {
    float scale = (self->mBlinkerScaleTo - self->mBlinkerScaleFrom) * t + self->mBlinkerScaleFrom;
    u32 color = FUN_007f5eb0(self->mBlinkerColorFrom, self->mBlinkerColorTo, t);
    ((void(__thiscall*)(void*, u32))(*(void***)window)[0x5c / 4])(window, color);
    FUN_00808210(window, scale);
    return true;
  }
  if (0.1f > t) {
    ((void(__thiscall*)(void*, u32))(*(void***)window)[0x5c / 4])(window, 0xffffffff);
    FUN_00808210(window, 1.0f);
  }
  return 0.1f <= t;
}

// @ 0x00e21750
void __fastcall FUN_00e21750(void* self_, s32, void* obj, u32 kind, u32) {
  void* inner = ((void*(__thiscall*)(void*))(*(void***)obj)[0x14 / 4])(obj);
  u32 r = ((u32(__thiscall*)(void*, u32))(*(void***)inner)[0x48 / 4])(inner, kind);
  ((void(__thiscall*)(void*, void*, u32, u32))(*(void***)self_)[0x40 / 4])(self_, obj, kind, r);
}

// @ 0x00e217c0
// Sort predicate over two creature objects (planet/continent then order id).
bool __cdecl FUN_00e217c0(void* a, void* b) {
  if (!a || !b)
    return false;
  s32 ia = *(s32*)((char*)a + 0xb1c);
  s32 ib = *(s32*)((char*)b + 0xb1c);
  if (ia != ib)
    return ia < ib;
  if (ia != 2) {
    void* pm = FUN_00b3d350();
    if (pm) {
      void* oa = *(void**)((char*)a + 0x34);
      void* ca = FUN_00b88590(
          ((void*(__thiscall*)(void*))(*(void***)oa)[0x2c / 4])(oa));
      void* ob = *(void**)((char*)b + 0x34);
      void* cb = FUN_00b88590(
          ((void*(__thiscall*)(void*))(*(void***)ob)[0x2c / 4])(ob));
      if (ca != cb)
        return ca < cb;
    }
  }
  return *(u32*)((char*)a + 0x24) < *(u32*)((char*)b + 0x24);
}

// ======================================================================
// Swarm/Simulator composite-effect helpers
// ======================================================================
struct MapDescription {
  void** vtbl;      // +0x00 vtbl_Swarm::MapDescription
  u16    w4;        // +0x04
  u16    w6;        // +0x06
  void*  p8;        // +0x08 (points to +0xc)
  u8     data[0x10c - 0xc];
};

struct SimAbility {                 // Simulator::cCreatureAbility
  u8     pad0[0xc];
  void** vecCur;                    // +0x0c
  void** vecEnd;                    // +0x10
};

// @ 0x00e210b0
// Attach a Swarm::MapDescription + a Simulator::cCreatureAbility to `effect`.
void __cdecl FUN_00e210b0(void* effect) {
  if (!effect)
    return;
  *(u32*)((char*)effect + 4) |= 0x12;

  MapDescription* md = (MapDescription*)operator_new(0x10c, "Simulator", 0, 0, 0, 0);
  if (md) {
    md->w4 = 0x206;
    md->w6 = 0x100;
    md->vtbl = (void**)0x1453948;   // vtbl_Swarm::MapDescription
    md->p8 = (char*)md + 0xc;
  }
  float* f = (float*)((char*)md + 0xc);
  f[0] = 1.0f; f[1] = 0.0f; f[2] = 0.0f; f[3] = 0.0f;
  f[4] = 0.0f; f[5] = 1.0f; f[6] = 0.0f; f[7] = 0.0f;
  f[8] = 0.0f; f[9] = 0.0f; f[10] = 1.0f; f[11] = 0.0f;
  f[12] = 0.0f; f[13] = 0.0f; f[14] = 0.0f; f[15] = 1.0f;

  SimAbility* ca = (SimAbility*)operator_new(0x1c, "Simulator", 0, 0, 0, 0);
  if (ca)
    FUN_0077d1d0(ca);

  void** cur = ca->vecCur;
  void*  mdv = md;
  if (cur < ca->vecEnd) {
    ca->vecCur = cur + 1;
    if (cur)
      *cur = mdv;
  } else {
    FUN_004558a0(cur, &mdv, 0);
  }
  void* box = FUN_0067cad0();            // cSPBoundingBox::AddBoundingBox
  void* sys = ((void*(__thiscall*)(void*))FUN_006c10e0)(box);
  ((void(__thiscall*)(void*, void*, void*, int))(*(void***)sys)[0xa4 / 4])(sys, effect, ca, -1);
}

// @ 0x00e213f0
// Update a loc-format text label: when `flag` is set show a clamped
// percentage without a raw value, otherwise show the raw value.
bool __cdecl FUN_00e213f0(void* obj, float value, char flag) {
  if (!obj)
    return false;
  wchar_t buf[42];

  if (flag) {
    if (value < 0.0f) value = 0.0f;
    float cap = DAT_013ec4d0;
    if (value > cap) value = cap;
    void* lbl = ((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(obj, 0x10edf11);
    if (lbl) {
      ((void(__thiscall*)(void*, float))(*(void***)lbl)[4 / 4])(lbl, 0.0f);
      return true;
    }
    lbl = ((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(obj, 0xeeee8218);
    if (!lbl)
      return false;
    FUN_00881ea0((double)value, buf, 0x20, L"%-F%-p");
    wchar_t* p = buf;
    while (p[0]) p++;
    *(u32*)p  = 0x00250020;   // append L" %"
    p[2] = 0;
    ((void(__thiscall*)(void*, wchar_t*))(*(void***)lbl)[0x80 / 4])(lbl, buf);
    return true;
  }

  void* lbl = ((void*(__thiscall*)(void*, u32))(*(void***)obj)[0xc / 4])(obj, 0xeeee8218);
  if (!lbl)
    return false;
  FUN_00881ea0((double)value, buf, 0x20, L"%-F%-p");
  ((void(__thiscall*)(void*, wchar_t*))(*(void***)lbl)[0x80 / 4])(lbl, buf);
  return true;
}

// ----------------------------------------------------------------------
// cSPTransform (0x40 bytes): translation + scale + 3x3 rotation.
// ----------------------------------------------------------------------
struct cSPTransform {
  u32   mFlags;       // +0x00 (low 16 used as flag word by peers)
  u32   pad04;        // +0x04
  float mTx;          // +0x08
  float mTy;          // +0x0c
  float mTz;          // +0x10
  u32   mModCount;    // +0x14
  u32   mPad18;       // +0x18
  float mScale;       // +0x1c
  float mRot[9];      // +0x20
};

// A cSPUILayeredObject (has vtbl; used as a "local" in FUN_00e21260).
struct LayeredLocal {
  void** vtbl;        // +0x00
  u32    field04;     // +0x04
  u8     data08[0x40 - 0x08];
};

// container of 3 layered local pointers
struct LayeredTriple {
  LayeredLocal* p0;   // +0x00
  LayeredLocal* p1;   // +0x04
  LayeredLocal* p2;   // +0x08
};

// places the canonical identity transform (translation = DAT_016ac208..)
static void BuildBaseTransform(cSPTransform* t) {
  t->mTx = DAT_016ac208;
  t->mTy = DAT_016ac20c;
  t->mTz = DAT_016ac210;
  t->mModCount = 0;
  t->mFlags = 0;
  t->mScale = 1.0f;
  FUN_0041cb40(t->mRot, DAT_016ac214);   // Matrix3::Assign
}

// @ 0x00e21260
// Replace the layered local at self+8 (ref-counted), then place both
// locals with a freshly built transform and (re)attach their effects.
void __fastcall FUN_00e21260(LayeredTriple* self, s32, void* a, void* b, LayeredLocal* newLocal) {
  LayeredLocal* old = self->p2;
  if (newLocal != old) {
    if (newLocal)
      ((void(__thiscall*)(LayeredLocal*))(*(void***)newLocal)[4 / 4])(newLocal);  // AddRef
    self->p2 = newLocal;
    if (old)
      ((void(__thiscall*)(LayeredLocal*))(*(void***)old)[8 / 4])(old);            // Release
  }

  cSPTransform xform;
  BuildBaseTransform(&xform);
  if (self->p0) {
    FUN_00537dc0(&xform, (char*)self->p0 + 8);   // cSPTransformOps::Assign(dst, &p0->transform)
  } else {
    xform = xform;   // keep the base transform (p0 null)
  }

  if (newLocal) {
    FUN_0080ea50(newLocal);                      // RemoveAllModels
    FUN_00478db0(FUN_0080fac0(self->p0->field04 ? (void*)self->p0->field04 : 0, 0, 0));
    FUN_00478db0(FUN_0080fac0(*(void**)((char*)self->p1 + 4), 0, 0));
    FUN_0080d790(newLocal, 1, 1);
    self->p0->field04 |= 1;
    ((LayeredLocal*)self->p1)->field04 |= 1;
    FUN_00537dc0((char*)self->p0 + 8, &xform);
    FUN_00537dc0((char*)self->p1 + 8, &xform);
    FUN_00e210b0(self->p0);
    FUN_00e210b0(self->p1);
  }
}

// @ 0x00e20f10
// Orient `model`'s bounding-box basis along the direction `dir`.
void __cdecl FUN_00e20f10(void* model, float* dir) {
  void* sys = FUN_006c10e0();                     // Sound/Audio get
  void* ob  = ((void*(__thiscall*)(void*, void*))(*(void***)sys)[0xa8 / 4])(sys, model);
  if (!ob)
    return;
  void* basis = *(void**)((char*)ob + 8);

  float x = dir[0], y = dir[1], z = dir[2];
  float inv = 1.0f / (float)sqrt((double)(x * x + y * y + z * z));

  cSPTransform xf;
  xf.mFlags = 0;
  xf.mTx = DAT_016ac208;
  xf.mTy = DAT_016ac20c;
  xf.mTz = DAT_016ac210;
  xf.mModCount = 0;
  xf.mScale = 1.0f;
  FUN_0041cb40(xf.mRot, DAT_016ac214);           // Matrix3::Assign

  float n[3];
  n[0] = x * inv;
  n[1] = y * inv;
  n[2] = z * inv;

  float pos[3];
  pos[0] = 0.0f; pos[1] = 0.0f; pos[2] = 1.0f;
  FUN_006bac90(n, pos);
  FUN_006b9440(basis);                            // Basis3::Build
}

// ----------------------------------------------------------------------
// 0x00e20860 - item-installer wizard state machine.
// `this` retail layout (all named by role/offset):
//   +0x08 void* mpObject;          (checked non-null)
//   +0x10 bool (*mpfnIsReady)(void);
//   +0x1c bool (*mpfnTest)(u32 contentId, void* out);
//   +0x24 bool (*mpfnTest2)(u32 contentId, void* out);
//   +0x2c bool (*mpfnCheck)(void*, void*, u32 pid, void* cmdline);
//   +0x30 void (*mpfnEval)(u32 contentId, void* value, void* out);
//   +0x3c int  mState;
//   +0x54 cInstallItem* mpItems;
//   +0x58 int  mItemCount;
//   +0x5c int  mIndex;
//   +0x64 int  mControlValue;
// ----------------------------------------------------------------------
struct cInstallItem {
  float  f00;        // +0x00
  u8     pad04[0x10 - 4];
  u32    mContentId; // +0x10  (4 dwords of id at 0x10..0x1f)
  u8     pad20[0x2c - 0x20];
  u8     mbChecked;  // +0x2c
  u8     mbInstalled;// +0x2d
  u8     pad2e[0x38 - 0x2e];
};

struct cInstaller {
  u8     pad00[0x08];
  void*  mpObject;      // +0x08
  u8     pad0c[0x10 - 0x0c];
  bool (*mpfnIsReady)(void);                                   // +0x10
  u8     pad14[0x1c - 0x14];
  bool (*mpfnTest)(u32, void*);                                // +0x1c
  bool (*mpfnTest2)(u32, void*);                               // +0x24
  bool (*mpfnCheck)(void*, void*, u32, void*);                 // +0x2c
  void (*mpfnEval)(u32, void*, void*);                         // +0x30
  u8     pad34[0x3c - 0x34];
  int    mState;        // +0x3c
  u8     pad40[0x54 - 0x40];
  cInstallItem* mpItems;// +0x54
  int    mItemCount;    // +0x58
  int    mIndex;        // +0x5c
  u8     pad60[0x64 - 0x60];
  int    mControlValue; // +0x64
};

// Append one "<InstallItem ContentId=\"%s\"/>" entry for an installed item.
static void FormatInstallItem(cInstallItem* it) {
  wchar_t id[4];
  *(u32*)id = it->mContentId;
  FUN_004e0850(&id, L"<InstallItem ContentId=\"%s\"/>", it->mContentId, 0, 0, 0);
  WStr_Append(id, id);
}

// Minimal UI::BehaviorMessage (0x40 bytes) used by the wizard.
struct BehaviorMessage {
  void** vtbl;      // +0x00
  u32    mRefCount; // +0x04
  s32    mSub;      // +0x08 (index 2)
  u8     pad0c[0x30 - 0x0c];
  u32    mKind;     // +0x30 (index 0xc)
  u8     pad34[0x38 - 0x34];
  u32    mF38;      // +0x38
};

static BehaviorMessage* MakeBehaviorMessage() {
  BehaviorMessage* m = (BehaviorMessage*)operator_new(0x40, "App", 0, 0, 0, 0);
  if (!m)
    return 0;
  m->mKind = 0;
  m->vtbl = (void**)0x13eb90c;     // vtbl_UI::BehaviorMessage
  m->mRefCount = 0;                // locked xchg in retail
  m->vtbl = (void**)0x13eb844;     // derived vtable
  m->mF38 = 0;
  ((void(__thiscall*)(BehaviorMessage*))m->vtbl[1])(m);
  return m;
}

static void PostMessage(u32 kind, void* payload) {
  void* srv = FUN_0067dcc0();      // MessageServer
  ((void(__thiscall*)(void*, u32, void*, int))(*(void***)srv)[0x14 / 4])(srv, kind, payload, 0);
}

// @ 0x00e20860
void __fastcall FUN_00e20860(cInstaller* self, s32) {
  if (!self->mpObject)
    return;

  bool ready = self->mpfnIsReady();
  if (!ready && self->mState != 9) {
    BehaviorMessage* m = MakeBehaviorMessage();
    if (!m) {
      // allocation failed: nothing to post
    } else {
      m->mKind = 0x5d676ed;
      m->mSub  = 0;
      PostMessage(m->mKind, m);
    }
    if (self->mState == 2)
      FUN_00e205e0(self);
    self->mState = 9;
    if (m)
      ((void(__thiscall*)(BehaviorMessage*))m->vtbl[2])(m);
    return;
  }

  switch (self->mState) {
  case 1: {
    void* out = 0;
    bool r = self->mpfnTest(self->mpItems[self->mIndex].mContentId, &out);
    self->mState = r ? 2 : 9;
    break;
  }
  case 2: {
    s32 out = 0;
    self->mpfnEval(self->mpItems[self->mIndex].mContentId, &self->mControlValue, &out);
    if (out == 7 || out == 8 || out == 9 || out == 10) {
      BehaviorMessage* m = MakeBehaviorMessage();
      FUN_0061df40(m);
      m->mKind = 0x5d676ed;
      switch (out) {
        case 7:  m->mSub = 1; break;
        case 8:  m->mSub = 2; break;
        case 9:  m->mSub = 0; break;
        case 10: m->mSub = 3; break;
      }
      PostMessage(m->mKind, m);
      FUN_00e205e0(self);
      self->mState = 9;
      ((void(__thiscall*)(BehaviorMessage*))m->vtbl[2])(m);
      return;
    }
    if (self->mControlValue == 100) {
      cInstallItem* it = &self->mpItems[self->mIndex];
      it->mbChecked = 0;
      it->mbInstalled = 1;
      self->mIndex++;
      if (self->mIndex < self->mItemCount) {
        self->mControlValue = 0;
        self->mState = 1;
        return;
      }
      self->mState = 0xb;
      PostMessage(0x5d66be3, 0);
      return;
    }
    break;
  }
  case 3: {
    // Build the "<InstallItems>...</InstallItems>" payload and hand it off.
    for (int i = 0, off = 0; i < self->mItemCount; i++, off += sizeof(cInstallItem)) {
      cInstallItem* it = (cInstallItem*)((char*)self->mpItems + off);
      if (it->mbInstalled)
        FormatInstallItem(it);
    }
    const char* cmd = GetCommandLineA();
    wchar_t cmdline[260];
    EA_ConvertToString16(cmdline, cmd);
    unsigned pid = GetCurrentProcessId();
    wchar_t out[260];
    bool ok = self->mpfnCheck(out, (void*)pid, pid, cmdline);
    if (!ok) {
      BehaviorMessage* m = MakeBehaviorMessage();
      m->mKind = 0x5d676ed;
      m->mSub = 4;
      PostMessage(m->mKind, m);
      self->mState = 9;
      ((void(__thiscall*)(BehaviorMessage*))m->vtbl[2])(m);
    } else if (pid == 0) {
      BehaviorMessage* m = MakeBehaviorMessage();
      FUN_0061df40(m);
      m->mKind = 0x5d676ed;
      m->mSub = 4;
      PostMessage(m->mKind, m);
      self->mState = 9;
      ((void(__thiscall*)(BehaviorMessage*))m->vtbl[2])(m);
    } else if (pid == 3) {
      void* srv = FUN_0067dcc0();
      ((void(__thiscall*)(void*, void*, void*, int, int))(*(void***)srv)[0x18 / 4])(srv, (void*)0x0153c326, 0, 0, 0);
      self->mState = 0xb;
    }
    break;
  }
  case 4:
  case 6: {
    void* out = 0;
    bool r = self->mpfnTest2(self->mpItems[self->mIndex].mContentId, &out);
    if (r)
      self->mState = (self->mState != 6 ? 2 : 5);
    break;
  }
  }
}
