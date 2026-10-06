// Slice s00b181d0 (bfs2 #47).
//
// SP::cGameData and neighbouring simulator input/camera helpers (0x00b181d0-0x00b19440).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-  (the two oldest manifest lines use the
// same source without /fp:fast /GS-; they are trivial and match either way)
#include "types.h"

typedef unsigned int u32;
typedef unsigned char u8;
typedef unsigned short u16;

struct Vec3 {
  float x, y, z;
};

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)
inline float sqrtf_(float x) { return (float)sqrt((double)x); }
extern "C" unsigned __int64 __rdtsc();
#pragma intrinsic(__rdtsc)

struct IRef {
  virtual int AddRef();
  virtual int Release();
};
struct IPawn {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual bool IsA();
  virtual void v21();
  virtual bool IsB();
};
struct IObj {
  virtual int AddRef();
  virtual int Release();
  virtual void v2();
  virtual IPawn* Query(unsigned id);
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual int GetKind();
};
struct IServer {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void Post5(unsigned id, int a, int b);
  virtual void Post6(unsigned id, int a, int b, int c);
  virtual void v7();
  virtual void v8();
  virtual void Reg9(void* p, unsigned id);
  virtual void v10();
  virtual void Reg11(void* p, unsigned id, unsigned x);
};
struct IWinMgr {
  virtual void v0();
  virtual void* Get4();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual void v20();
  virtual void v21();
  virtual void v22();
  virtual void v23();
  virtual void v24();
  virtual void v25();
  virtual void v26();
  virtual void v27();
  virtual void v28();
  virtual void v29();
  virtual void v30();
  virtual void v31();
  virtual void v32();
  virtual int Get84();
};
struct IRootB {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual IObj* Get34();
  virtual void v14();
  virtual void Get3c(void* out, int z);
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual void v20();
  virtual void v21();
  virtual void v22();
  virtual void v23();
  virtual void v24();
  virtual int Get64(unsigned id);
};
struct IViewerHolder {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void* GetViewer();
};
struct IAppB {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual void v18();
  virtual void v19();
  virtual IViewerHolder* Get50();
};
struct IList18 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void Call18();
};
struct IHolder48 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void Reg7(unsigned id, const wchar_t* name, int z);
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void v16();
  virtual void v17();
  virtual IList18* Get48();
};
struct IActor {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void Fn12(int type, unsigned id, IObj* e, Vec3* tmp, unsigned flags, int z);
};
struct IObjA {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void v13();
  virtual void v14();
  virtual void v15();
  virtual void Fn16(int a, const char* s);
};
struct IMovie {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual void v8();
  virtual void Fn9();
};
struct IStreamW {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void* Get18();
};
struct IStreamB {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6();
  virtual void v7();
  virtual IStreamW* GetWriter();
};


// ---- global helpers (cdecl, bodies elsewhere)
IRootB* __cdecl GetRoot();            // 0x00b3d240
void __cdecl FUN_00b3d280();
void* __cdecl GetPlanetModelRaw();    // 0x00b3d350
IServer* __cdecl MessageServer();     // 0x0067dcc0

struct cPlanetModel {
  float GetRadiusAt(const Vec3* p);          // 0x00b7ef70 (ret 4)
  float GetWaterHeight();                    // 0x00b7e390
  void FindClosestWater(const Vec3* p, float r, Vec3* out);  // 0x00b8bb70 (ret 0xc)
  Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* p, float a, float b);  // 0x00b81780 (ret 0x10)
  bool Check(const Vec3* p);                 // 0x00b7e3e0 (ret 4)
};
cPlanetModel* __cdecl PlanetModel();  // 0x00b3d350

namespace SP {

struct cGameData;

struct cDefTable {
  unsigned Lookup(unsigned id);  // 0x00f3e8a0 (ret 4)
};
struct cApp {
  char pad[0x74];
  cDefTable* mpDefs;
};

struct cVarListSerializer {
  char mBuf[0xa14];
  cVarListSerializer(cGameData* gd, const void* table, unsigned id);  // 0x00692f90 (ret 0xc)
  void Serialize(IStreamB* s);                                       // 0x00692900 (ret 4)
};
void* __cdecl WriteUint32(void* stream, const void* p, int n, int z);  // 0x0093aa70

extern void* vtbl_cGameData0;  // 0x0145d060
extern void* vtbl_cGameData1;  // 0x0145d050
extern void* vtbl_Base0;       // 0x013eb938
extern void* vtbl_Base1;       // 0x013ec458
extern int gGameDataCount;     // 0x0167be2c
extern cApp* gApp;             // 0x016c7aa4
extern char gVarTable[];       // 0x01567e48

// cGameData: the +0x21 byte and the vtable used by the two implemented hooks.
struct RefCountBase {  // EA::RefCountVTemplate<int> part at +4 (inline ctor stores)
  void* vtbl1;
  int mRefCount;
  RefCountBase() {
    vtbl1 = &vtbl_Base1;
    mRefCount = 0;
  }
};

struct cGameData {
  void* vtbl0;     // +0x00
  RefCountBase mRC;  // +0x04
  void* mpNext;    // +0x0c
  void* mpPrev;    // +0x10
  int mIsDestroyed;  // +0x14
  u32 mID;           // +0x18
  u32 mDefinitionID;  // +0x1c
  u8 mb20;            // +0x20
  u8 mb21;            // +0x21
  u32 m24;            // +0x24
  u32 mView;          // +0x28
  IRef* mpOwner;      // +0x2c
  u32 mPoliticalID;   // +0x30

  bool WriteSerializableObjectCheck();   // 0x00b183e0
  void NotifyDirty(bool b);              // 0x00b189a0
  void VtableSlot40(int a);              // 0x00b183f0
  bool Init(void* a, int b, int c);      // 0x00b18400
  void DtorBody();                       // 0x00b184c0
  unsigned GetDefinition();              // 0x00b18530
  void SetOwner(IRef* o);                // 0x00b18550
  void Write(IStreamB* s);               // 0x00b18590
  cGameData();                           // 0x00b18660
  cGameData* ScalarDeletingDtor(u8 f);   // 0x00b186b0
};

}  // namespace SP

using SP::cGameData;

// ---------------------------------------------------------------------------
// 0x00b181d0: a bounding-volume style object: float triplets at +0x48 (begin), +0x4c (end),
// radius at +0xcc.
struct cBounds {
  char pad0[0x48];
  Vec3* mpBegin;  // +0x48
  Vec3* mpEnd;    // +0x4c
  char pad1[0xcc - 0x50];
  float mRadius;  // +0xcc
  int m_d0;       // +0xd0
  int m_d4;       // +0xd4
  void Fill();    // 0x00b172b0
};
void __cdecl BoundsFinish(cBounds* a, cBounds* b);  // 0x00b175e0
void __cdecl FillBounds(cBounds* a);                // unused placeholder

template <typename T> inline const T& MaxRef(const T& a, const T& b) { return (a < b) ? b : a; }

// @ 0x00b181d0
bool WaterClearance(cBounds* o, float* out) {
  if (o->mpBegin == o->mpEnd)
    o->Fill();
  float* p = (float*)o->mpBegin;
  float dx = p[0] - p[0x18];
  float dy = p[1] - p[0x19];
  float dz = p[2] - p[0x1a];
  o->mRadius = sqrtf_(dy * dy + (dz * dz + dx * dx)) * 0.5f;
  if (o->m_d4 == 0 && o->m_d0 == 0)
    BoundsFinish(o, o);
  float best = 0.0f;
  for (int off = 0x48; off <= 0x60; off += 0xc) {
    Vec3* v = (Vec3*)((char*)o->mpBegin + off);
    float len = sqrtf_(v->x * v->x + v->y * v->y + v->z * v->z);
    float r = PlanetModel()->GetRadiusAt(v);
    float w = PlanetModel()->GetWaterHeight();
    float d = (MaxRef(r, w) + 5.0f) - len;
    if (best < d)
      best = d;
  }
  if (out)
    *out = best;
  return best > 0.0f;
}

// ---------------------------------------------------------------------------
void __cdecl EA_Deallocate(void* p);  // 0x00f47380

struct FixedBuf {  // eastl::fixed_vector header: begin, end, capacity, allocator
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  int mPad[2];
  int mAlloc;
};
struct cQuerySvc {
  void Apply();  // 0x00b7a1d0
};
cQuerySvc* __stdcall QuerySvc(void* p, float r, void* a2, FixedBuf* d);  // 0x00b3d3c0

// @ 0x00b182f0
bool BoundsQuery(cBounds* o, void* a2) {
  if (o->mpBegin == o->mpEnd)
    o->Fill();
  float* p = (float*)o->mpBegin;
  float dx = p[0] - p[0x18];
  float dy = p[1] - p[0x19];
  float dz = p[2] - p[0x1a];
  o->mRadius = sqrtf_(dy * dy + (dz * dz + dx * dx)) * 0.5f;
  if (o->m_d4 == 0 && o->m_d0 == 0)
    BoundsFinish(o, o);
  char buf[0x400];
  FixedBuf d;
  d.mpBegin = buf;
  d.mpEnd = buf;
  d.mpCapacity = buf + 0x400;
  d.mAlloc = 0;
  QuerySvc((char*)o->mpBegin + 0x30, o->mRadius, a2, &d)->Apply();
  bool r = d.mpBegin != d.mpEnd;
  if (d.mpBegin && ((int*)d.mpBegin)[-1])
    EA_Deallocate(d.mpBegin);
  return r;
}

// ---------------------------------------------------------------------------
// @ 0x00b183e0
bool cGameData::WriteSerializableObjectCheck() {
  return mb21 == 0;
}

// @ 0x00b183f0
void cGameData::VtableSlot40(int) {
  ((int(__thiscall*)(void*))(*(void***)this)[16])(this);
}

// @ 0x00b18400
bool cGameData::Init(void* a, int, int) {
  if (a) {
    mView = ((u32*)a)[1];
    return mView != 0;
  }
  return false;
}

// @ 0x00b18490
struct RefHolder {
  u32 m0, m4, m8;
  IRef* mC;
  RefHolder* Ctor(u32 a, u32 b, IRef* o);
};
RefHolder* RefHolder::Ctor(u32 a, u32 b, IRef* o) {
  m0 = a;
  m4 = b;
  m8 = 0;
  mC = o;
  if (o)
    o->AddRef();
  return this;
}

// @ 0x00b184c0
void cGameData::DtorBody() {
  vtbl0 = &vtbl_cGameData0;
  mRC.vtbl1 = &vtbl_cGameData1;
  gGameDataCount--;
  if (mpOwner)
    mpOwner->Release();
  mRC.vtbl1 = &vtbl_Base1;
  vtbl0 = &vtbl_Base0;
}

// @ 0x00b18530
unsigned cGameData::GetDefinition() {
  if (mDefinitionID == 0xffffffff)
    return 0;
  cDefTable* t = SP::gApp->mpDefs;
  return t->Lookup(mDefinitionID);
}

// @ 0x00b18550
void cGameData::SetOwner(IRef* o) {
  IRef* old = mpOwner;
  if (o != old) {
    if (o)
      o->AddRef();
    mpOwner = o;
    if (old)
      old->Release();
  }
  if (o)
    mPoliticalID = ((cGameData*)o)->mPoliticalID;
}

// @ 0x00b18590
void cGameData::Write(IStreamB* s) {
  unsigned magic;
  IStreamW* ww = s->GetWriter();
  magic = 0x17f243b;
  void* w = ww->Get18();
  SP::WriteUint32(w, &magic, 1, 0);
  SP::cVarListSerializer ser(this, SP::gVarTable, 0x1a80d26);
  ser.Serialize(s);
}

// @ 0x00b18660
cGameData::cGameData() {
  vtbl0 = &vtbl_cGameData0;
  mRC.vtbl1 = &vtbl_cGameData1;
  mIsDestroyed = 0;
  mID = 0;
  mDefinitionID = 0xffffffff;
  mb20 = 0;
  mb21 = 0;
  m24 = 0xffffffff;
  mView = 0;
  mpOwner = 0;
  mPoliticalID = 0xffffffff;
  mpNext = 0;
  mpPrev = 0;
  gGameDataCount++;
}

// @ 0x00b186b0
cGameData* cGameData::ScalarDeletingDtor(u8 f) {
  vtbl0 = &vtbl_cGameData0;
  mRC.vtbl1 = &vtbl_cGameData1;
  gGameDataCount--;
  if (mpOwner)
    mpOwner->Release();
  mRC.vtbl1 = &vtbl_Base1;
  vtbl0 = &vtbl_Base0;
  if (f & 1)
    operator delete(this);
  return this;
}

struct cCreatureBase {
  bool Test();  // 0x00c0c0e0
};

// @ 0x00b18760
bool IsCreatureObject(IObj* o) {
  if (o) {
    IPawn* p = o->Query(0xd0036e08);
    if (p)
      return ((cCreatureBase*)p)->Test();
  }
  return false;
}

// ---------------------------------------------------------------------------
struct cTraitHolder {
  float Value();  // 0x00bfc490
};
extern char gTraitKey[];  // 0x013f94d4

// @ 0x00b188b0
u8 KindIsActive(IObj* o) {
  switch (o->GetKind()) {
    case 0xe9cb8ba:
    case 0x116d858:
    case 0xee02c7:
    case 0x1a55e4d:
    case 0x436f315:
    case 0x1007ae63:
    case 0xecade42:
    case 0xff10521: {
      cTraitHolder* t = (cTraitHolder*)o->Query((unsigned)gTraitKey);
      return (t->Value() <= 0.0f) ? 1 : 0;
    }
    case 0xd0036e08:
    case 0x4f176642: {
      char* q = (char*)o->Query(0xce9f6639);
      return q[0xb5e];
    }
  }
  return 0;
}

// @ 0x00b18960
struct InputEvent {
  u32 a, b, c, key, d;
  u8 e0, e1;
  u16 mods;
};
struct cMsgQueue {
  void Remove(void* p);   // 0x008d3b10 (ret 4)
  void Cancel(void* p);   // 0x008d41b0 (ret 4)
  void Send(int a, int b, int c);  // 0x008d36f0 (ret 0xc)
  void Post(InputEvent* ev, int n);  // 0x008d3e30 (ret 8)
  void* Find(void* a, void* b, void* c, int d, int e, int f);  // 0x008d34f0 (ret 0x18)
};
extern cMsgQueue gMsgQueue;  // 0x0167bef0
void __fastcall NotifyRemove(char* self) {
  gMsgQueue.Remove(self + 0x68);
  void* q = (self - 0xc) ? (self - 4) : 0;
  MessageServer()->Reg11(q, 0x2168a93, 0xffffd8f1);
}

// @ 0x00b189a0
void cGameData::NotifyDirty(bool b) {
  if (!b)
    ((void(__thiscall*)(void*))(*(void***)this)[7])(this);
}

// ---------------------------------------------------------------------------
// 0x00b189c0: input key handler
struct cLayoutMgr {
  bool IsWorldVisible(unsigned id);  // 0x00810760 (ret 4)
};
cLayoutMgr* __cdecl GetLayoutManager();  // 0x00805070
struct cB3d320 {
  char pad[0x28];
  u8 mFlag28;
};
cB3d320* __cdecl GetB3d320();  // 0x00b3d320
unsigned __cdecl GetCurrentGameMode();  // 0x00b5b800
struct cCreatureModeStrategy {
  bool F();  // 0x00d38880
  static cCreatureModeStrategy* Instance();  // 0x00d38840
};
struct cTribeModeStrategy {
  bool F();    // 0x00cd4490
  bool G();    // 0x00cd44a0
  static cTribeModeStrategy* Instance();  // 0x00cd40b0
};
struct cCivModeStrategy {
  bool F();    // 0x00cf7a40
  char pad[0x148];
  u8 mFlag148;
  static cCivModeStrategy* Get();  // 0x00cf74c0
};
struct cB3d410 {
  bool F();  // 0x00e36fa0
  bool G();  // 0x00e393b0
};
cB3d410* __cdecl GetB3d410();  // 0x00b3d410
struct cB3d4d0 {
  bool F();  // 0x00ac80f0
  void H();  // 0x00ad8f90
  char pad[0x2b];
  u8 mFlag2b;
  int m2c;
};
cB3d4d0* __cdecl GetB3d4d0();  // 0x00b3d4d0
struct cAppG {
  bool G();  // 0x00ef00d0
};
bool __cdecl FUN_00dd1230();
bool __cdecl FUN_00e09540();
bool __cdecl FUN_00b2f740();
struct cFlagObj {
  char pad[0x1c];
  u8 mFlag;
};
cFlagObj* __cdecl SporeGuide();     // 0x00401040
cFlagObj* __cdecl AssetBrowser();   // 0x00401030
IWinMgr* __cdecl WindowManager();   // 0x0067caa0
struct cWinObj {
  bool Test();               // 0x00812d70
  void Set(bool b);          // 0x00812d60 (ret 4)
};
struct cC10666a0 {
  bool F();  // 0x01065e20
};
cC10666a0* __cdecl GetC10666a0();  // 0x010666a0

// @ 0x00b189c0
bool __stdcall KeyDownHandler(int key, int mod) {
  cLayoutMgr* lm = GetLayoutManager();
  if (lm->IsWorldVisible(0x614de4c))
    return true;
  u8 flag28 = GetB3d320()->mFlag28;
  if (flag28)
    return true;
  bool handled;
  switch (GetCurrentGameMode()) {
    case 0x1654c01:
      handled = cCreatureModeStrategy::Instance()->F();
      break;
    case 0x1654c02:
      handled = cTribeModeStrategy::Instance()->F();
      break;
    case 0x1654c04:
      handled = cCivModeStrategy::Get()->F();
      break;
    case 0x1654c05:
      handled = GetB3d410()->F();
      break;
    case 0x1654c10:
      handled = ((cAppG*)SP::gApp)->G();
      break;
    default:
      goto after_modes;
  }
  if (handled)
    return true;
after_modes:
  if (key != 0x1b) {
    if (mod != 0)
      goto L_modnz;
    if ((key == 0x48 || key == 0xbf || key == 0x54 || key == 0x42 || key == 0x50 || key == 0x43 ||
         key == 0x4c) &&
        (FUN_00dd1230() || FUN_00e09540()))
      return true;
    if (key != 0x48 && key != 0xbf)
      goto L_27;
    goto L_c6;
  }
  if (mod == 0)
    return false;
L_modnz:
  if (mod == 1) {
    if (key != 0xbf)
      return false;
    goto L_c6;
  }
  goto L_after;
L_c6:
  if (GetCurrentGameMode() != 0x1654c00) {
    if (!SporeGuide()->mFlag) {
      MessageServer()->Post5(0x5120263, 0, 0);
      return true;
    }
    MessageServer()->Post5(0x5b9ba6c, 0, 0);
    return true;
  }
L_after:
  if (mod == 2) {
    if (key != 0x53) {
      if (key != 0x48)
        return false;
      if (GetCurrentGameMode() == 0x1654c00)
        return false;
      void* w = WindowManager()->Get4();
      cWinObj* wo = w ? (cWinObj*)((char*)w - 4) : 0;
      wo->Set(!wo->Test());
      return false;
    }
    if (GetCurrentGameMode() == 0x1654c00)
      return false;
    if (GetCurrentGameMode() == 0x1654c10)
      return false;
    if (AssetBrowser()->mFlag)
      return false;
    if (GetB3d410()->G())
      return false;
    if (GetB3d4d0()->F())
      return false;
    if (FUN_00b2f740())
      return false;
    if (GetCurrentGameMode() == 0x1654c02) {
      if (cTribeModeStrategy::Instance()->G())
        return false;
    }
    MessageServer()->Post6(0x1cd20f0, 0, 0, 0);
    return true;
  }
  if (mod != 0)
    return false;
L_27:
  if (key == 0x42) {
    if (GetCurrentGameMode() != 0x1654c00) {
      if (!AssetBrowser()->mFlag) {
        MessageServer()->Post5(0x5120264, 0, 0);
        return true;
      }
      MessageServer()->Post5(0x574f0a6, 0, 0);
      return true;
    }
  } else if (key == 0x54) {
    if (WindowManager()->Get84() == 0) {
      if (!GetB3d4d0()->F() &&
          (GetCurrentGameMode() != 0x1654c04 || !cCivModeStrategy::Get()->mFlag148)) {
        if (GetCurrentGameMode() == 0x1654c02) {
          if (cTribeModeStrategy::Instance()->G())
            return true;
        }
        if (GetCurrentGameMode() == 0x1654c05) {
          if (GetC10666a0()->F())
            return true;
        }
        MessageServer()->Post5(0x5120262, 0, 0);
      }
    }
    return true;
  }
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x00b18d50
bool __stdcall CheckSpaceGame(int) {
  GetRoot()->Get64(0xd03d8d89);
  return false;
}

// @ 0x00b18d90
void __stdcall SendMessage7(int a) {
  gMsgQueue.Send(a, -2, 7);
}

// @ 0x00b18db0
void __fastcall ClearTimers(char* self) {
  gMsgQueue.Cancel(self + 0xc0);
  gMsgQueue.Remove(self + 0xc0);
}

// @ 0x00b18dd0
IHolder48* __cdecl GetHolder();  // 0x006895b0
void CallHolder18() {
  IHolder48* h = GetHolder();
  if (h) {
    IList18* l = h->Get48();
    if (l)
      l->Call18();
  }
}

// @ 0x00b18e40
extern signed char gNibbleTable[];  // 0x0145d1c4
struct cNibbleHolder {
  char pad[0x50];
  unsigned mBits;  // +0x50
  bool HasBits();
};
bool cNibbleHolder::HasBits() {
  int sum = 0;
  unsigned v = mBits;
  while (v != 0) {
    signed char c = gNibbleTable[v & 0xf];
    sum += c;
    v >>= 4;
  }
  return (unsigned)sum > 0;
}

// @ 0x00b18e70
struct cTerrainCursor {
  IObj* GetObj();  // placeholder
};
IObj* __cdecl GetSelectedObj();  // 0x00b7c770
struct ICursor {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
  virtual void v25(); virtual void v26(); virtual void v27();
  virtual int Get70();
};
ICursor* __cdecl GetGameTerrainCursor();  // 0x00b30d70

unsigned __fastcall PawnFlags(IObj* o) {
  IPawn* pawn = o ? o->Query(0x1186577) : 0;
  unsigned flags = 0;
  if (pawn) {
    flags = (GetSelectedObj() != (IObj*)pawn ? 0x40 : 0) + 0x40;
    if (pawn->IsB())
      flags |= 1;
    else
      flags |= 2;
    if (pawn->IsA())
      flags |= 0x10;
    else
      flags |= 0x20;
  }
  if (GetGameTerrainCursor()->Get70() == 0) {
    flags |= 8;
  } else {
    flags |= 4;
  }
  return flags;
}

// @ 0x00b18ef0
void RequestAction(unsigned id, void* a2, IActor* actor) {
  int type = 10;
  if (id != 0x5ece0000 && (int)id > 0x5ece0000 && (int)id < 0x5ece0003)
    type = 11;
  IObj* e = GetRoot()->Get34();
  Vec3 tmp;
  GetRoot()->Get3c(&tmp, 0);
  actor->Fn12(type, ((unsigned*)a2)[1], e, &tmp, PawnFlags(e), 0);
}

// @ 0x00b18f70
struct cPropertyList {
  bool GetDescription(unsigned id);  // 0x006a25a0 (ret 4)
  void SetBoolProperty(unsigned id, int v);  // 0x006a17e0 (ret 8)
};
extern cPropertyList* gAppProperties;  // 0x015fd918
bool __cdecl FUN_008d3200();
bool CheckAppProperty() {
  if (!gAppProperties->GetDescription(0x2773d59))
    return FUN_008d3200();
  return false;
}

// @ 0x00b18f90
bool __fastcall CheckPawnFlags(IObj* o, int edx, u8 flags) {
  if (o) {
    IPawn* p = o->Query(0x1186577);
    if (!p)
      return true;
    if ((flags & 1) && !p->IsB())
      return false;
    if ((flags & 2) && p->IsB())
      return false;
    if ((flags & 0x10) && !p->IsA())
      return false;
    if ((flags & 0x20) && p->IsA())
      return false;
  }
  return true;
}

// @ 0x00b19000
void* __cdecl GetAppRaw();  // 0x0067dd10
extern float gDefaultPos[3];  // 0x0167bea4
struct cViewer {
  void GetCameraLocationInfo(Vec3* pos, int a, int b, int c);  // 0x007c3d30 (ret 0x10)
};
struct IAppC {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual IViewerHolder* Get50();
};
IAppC* __cdecl SPApp();  // 0x0067dd10

Vec3* PickPosition(unsigned flags, Vec3* out) {
  Vec3 pos;
  pos.x = gDefaultPos[0];
  pos.y = gDefaultPos[1];
  pos.z = gDefaultPos[2];
  cViewer* v = (cViewer*)SPApp()->Get50()->GetViewer();
  if (v)
    v->GetCameraLocationInfo(&pos, 0, 0, 0);
  if (flags & 0x100) {
    Vec3 res;
    PlanetModel()->FindClosestWater(&pos, 100.0f, &res);
    *out = res;
    return out;
  }
  if (flags & 0x200) {
    Vec3 res;
    Vec3 buf;
    int i = 0;
    do {
      res = *PlanetModel()->MakeRandomWorldPosition(&buf, &pos, 10.0f, 100.0f);
      if (i++ >= 500)
        break;
    } while (PlanetModel()->Check(&res));
    *out = res;
    return out;
  }
  PlanetModel()->MakeRandomWorldPosition(out, &pos, 10.0f, 100.0f);
  return out;
}

// @ 0x00b19180
struct Timer28 {
  u32 d[7];
  Timer28(void* a, void* fn, void* ctx, int b, int c, int e);  // 0x008d34f0 (ret 0x18)
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* p);
extern unsigned long long gStartTime;  // 0x0167c280
extern int gUseRdtsc;                  // 0x0167c290

void __fastcall RegisterInputHandler(char* self) {
  IObjA* full = (IObjA*)(self - 0xc);
  full->Fn16(-1, "ANY");
  GetHolder()->Reg7(0x2168a93, L"InputEvent", 0);
  void* q = (self - 0xc) ? (self - 4) : 0;
  MessageServer()->Reg9(q, 0x2168a93);
  *(Timer28*)(self + 0x68) = Timer28(self + 0x84, (void*)RequestAction, full, 0, 0, -2);
  *(Timer28*)(self + 0xb4) = Timer28(0, 0, 0, 1, 1000, -2);
  gMsgQueue.Cancel(self + 0x68);
  if (gStartTime == 0) {
    if (gUseRdtsc == 1) {
      gStartTime = __rdtsc();
    } else {
      long long t;
      QueryPerformanceCounter(&t);
      gStartTime = t;
    }
  }
}

// @ 0x00b19290
struct cGameTimeManager {
  int GetPauseGateCount(unsigned id);  // 0x00b320d0 (ret 4)
  void TogglePauseGate(unsigned id);   // 0x00b32280 (ret 4)
  char pad[0x48];
  u8 mPaused;
};
cGameTimeManager* __cdecl GameTimeManager();  // 0x00b3d380
struct cAvatar {
  bool F();  // 0x00ff6360
  void G();  // 0x00ff62d0
};
struct cNounManager {
  cAvatar* GetAvatar();  // 0x00b1fdb0
};
cNounManager* __cdecl SpaceGameGet();  // 0x01002bd0
IMovie* __cdecl MovieSystem();         // 0x0067cb10


struct cInputHandler : IActor {
  char pad[0x110 - 4];
  int m110;
  bool OnKey(int key, int mod);  // 0x00b19290
};
void PostEvent(cMsgQueue* q, InputEvent* ev, int n);

bool cInputHandler::OnKey(int key, int mod) {
  FUN_00b3d280();
  Vec3 tmp;
  GetRoot()->Get3c(&tmp, 0);
  switch (key) {
    case 0x1b:
      if (GetCurrentGameMode() == 0x1654c05) {
        cAvatar* av = SpaceGameGet()->GetAvatar();
        if (av && av->F())
          av->G();
        if (((cNibbleHolder*)SpaceGameGet())->HasBits())
          return true;
      }
      if (GetB3d4d0()->m2c == 1)
        return true;
      if (GetB3d4d0()->m2c == 2) {
        if (!GetB3d410()->G() && !GetB3d4d0()->mFlag2b)
          GetB3d4d0()->H();
        return true;
      }
      MovieSystem()->Fn9();
      break;
    case 0x50:
    case 0xc0:
      if (mod == 0 && m110 <= 0) {
        if (GameTimeManager()->GetPauseGateCount(0x4bf38a4) <= 0) {
          gAppProperties->SetBoolProperty(0x387d0a8, ~GameTimeManager()->mPaused & 1);
          GameTimeManager()->TogglePauseGate(0x4bf38a8);
          return true;
        }
      }
      break;
  }
  IObj* e = GetRoot()->Get34();
  Fn12(4, key, e, &tmp, PawnFlags(e), mod);
  InputEvent ev;
  ev.a = 0;
  ev.b = 0;
  ev.key = key;
  ev.e1 = 0;
  ev.e0 = 0;
  ev.mods = (u16)mod;
  gMsgQueue.Post(&ev, 1);
  return false;
}
