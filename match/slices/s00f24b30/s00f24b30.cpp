// Slice s00f24b30.  Simulator game-data helper functions and a set of small
// __thiscall type/key predicates.  Built /O2 /MD /Gy (no /EHsc), x87 for float
// math, SSE scalar for float copies.
//
// The many small predicates compare a 32-bit FNV "type id" stored at this+0x04
// (or this+0x00 / this+0x18) against named constants.  Those constants are FNV
// hashes of Spore type names; without the name registry they are reproduced as
// literals under kType* names.

#include <math.h>
#pragma intrinsic(sqrt)

typedef unsigned int uint;

struct Vec3 { float x, y, z; };

struct Vec3i { int x, y, z; };

struct Obj;

extern "C" {
  int   sub_eece20(void*);          // noun/type id of an object
  int   sub_eecf10(void*);          // noun/type id of an object (variant)
  int   sub_eeca60(void*, void*);   // writes a key struct at arg0
  void* sub_f21bb0(void*, void*);   // fills a Vector3 at arg0, returns it
  void* sub_f24200(void);
  int   sub_b3d300(void);           // SP::NounManager
  int   sub_0067cb30(void);
  int   sub_005f7930(void);
  void* sub_new(int, const char*, int, int, int, int);
  void  sub_delete(void*);
}

// A generic 32-bit key / type id.
enum : uint {
  kType24682294 = 0x24682294,
  kType2B978C46 = 0x2b978c46,
  kType476A98C7 = 0x476a98c7,
  kType2399BE55 = 0x2399be55,
  kType90C48D09 = 0x90c48d09,
  kType3144B430 = 0x3144b430,
  kTypeB1B104   = 0xb1b104,
  kType2F7D0004 = 0x2f7d0004,
  kType65928944 = 0x65928944,
  kTypeCF56099A = 0xcf56099a,
  kTypeB10E526F = 0xb10e526f,
  kTypeD37C1045 = 0xd37c1045,
  kTypeE34E8A60 = 0xe34e8a60,
  kType5B3D1D0D = 0x5b3d1d0d,
  kType6031C03A = 0x6031c03a,
  kType7998CE71 = 0x7998ce71,
  kTypeE137FF08 = 0xe137ff08,
};

struct Obj {
  uint f00, f04, f08, f0c, f10, f14, f18;
  unsigned char b1c; unsigned char _p1[3];
  unsigned char b20; unsigned char _p2[3];
  uint f24, f28, f2c, f30, f34;
  uint _g38[4];
  uint f48, f4c, f50, f54, f58;
  char _g5c[0x4a8 - 0x5c];
  uint f4a8, f4ac, f4b0, f4b4, f4b8, f4bc, f4c0, f4c4;

  int  fn25080(Obj* o);
  void fn25110(Vec3i* out, bool* flag);
  void fn25160(Vec3i* o);
  void fn25190(Vec3i* out, bool* flag);
  Vec3i* fn251f0(Vec3i* o);
  Vec3i* fn25240(Vec3i* o, bool* flag);

  int  fn252c0();
  int  fn252f0();
  bool fn25330();
  bool fn25360();
  bool fn25370();
  char fn253e0();
  char fn253f0();
  char fn25420();
  bool fn25430();
  bool fn25470();
  bool fn25490();
  bool fn254d0();
  int  fn25530();
  bool fn25560();
  bool fn25580();
  bool fn255d0();
  bool fn25600();
  bool fn25640();
  bool fn25670();
  int  fn25680();
  bool fn256a0();
  bool fn256e0();
  bool fn25720();
  bool fn25730();
  int  fn25750();
  Obj* fn257b0();

  // complex
  char fn257f0(void* serializer);
};

// @ 0x00f25050  __stdcall
int __stdcall fn25050(void* buf, uint n) {
  if (buf) {
    if (n < 3) return 0;
    *(uint*)buf = 0x366a930d;
    ((uint*)buf)[1] = 0x191c3c61;
    ((uint*)buf)[2] = 0xe22261b7;
  }
  return 3;
}

// @ 0x00f25080
int Obj::fn25080(Obj* o) {
  if (f4a8 == o->f4a8 && f4ac == o->f4ac && f4b0 == o->f4b0 &&
      f4b4 == o->f4b4 && f4b8 == o->f4b8 && f4bc == o->f4bc &&
      f4c0 == o->f4c0 && f4c4 == o->f4c4)
    return 0;
  return 1;
}

// @ 0x00f25110
void Obj::fn25110(Vec3i* out, bool* flag) {
  *flag = (f24 == 1);
  out->x = 0; out->y = 0; out->z = 0;
  if (f24 == 2) {
    out->x = (int)f28; out->y = (int)f2c; out->z = (int)f30;
  } else {
    out->x = (int)f00; out->y = (int)f04; out->z = (int)f08;
  }
}

// @ 0x00f25160
void Obj::fn25160(Vec3i* o) {
  o->x = (int)f00; o->y = (int)f04; o->z = (int)f08;
  if ((uint)o->y == kTypeB1B104) o->z = (int)kType65928944;
  o->y = (int)kType2F7D0004;
}

// @ 0x00f25190
void Obj::fn25190(Vec3i* out, bool* flag) {
  *flag = (f24 == 1);
  out->x = 0; out->y = 0; out->z = 0;
  if (f24 == 2) {
    out->x = (int)f28; out->y = (int)f2c; out->z = (int)f30;
  } else {
    out->x = (int)f00; out->y = (int)f04; out->z = (int)f08;
  }
  if ((uint)out->y == kTypeB1B104) out->z = (int)kType65928944;
  out->y = (int)kType2F7D0004;
}

// @ 0x00f251f0
Vec3i* Obj::fn251f0(Vec3i* o) {
  o->x = 0; o->y = 0; o->z = 0;
  Vec3i tmp;
  Vec3i* r = (Vec3i*)sub_f21bb0(&tmp, this);
  *o = *r;
  if ((uint)o->y == kTypeB1B104) o->z = (int)kType65928944;
  o->y = (int)kType2F7D0004;
  return o;
}

// @ 0x00f25240
Vec3i* Obj::fn25240(Vec3i* o, bool* flag) {
  *flag = (f48 == 1);
  o->x = 0; o->y = 0; o->z = 0;
  if (f48 == 2) {
    o->x = (int)f50; o->y = (int)f54; o->z = (int)f58;
  } else {
    Vec3i tmp;
    Vec3i* r = (Vec3i*)sub_f21bb0(&tmp, this);
    *o = *r;
  }
  if ((uint)o->y == kTypeB1B104) o->z = (int)kType65928944;
  o->y = (int)kType2F7D0004;
  return o;
}

// @ 0x00f252c0
int Obj::fn252c0() {
  if (sub_eece20(this) == (int)kTypeCF56099A)
    return (f00 != kType3144B430) * 2 + 1;
  return 0;
}

// @ 0x00f252f0
int Obj::fn252f0() {
  uint t = f00;
  if (t == kType90C48D09) return 1;
  if (t == 0x4117bf2c || t == 0x7d14bb49 || t == 0x8e83d305 ||
      t == 0x34fb4ab0 || t == 0x21329a37) return 3;
  return 0;
}

// @ 0x00f25330
bool Obj::fn25330() {
  bool r = false;
  switch (f04) {
    case 0x2b978c46: case 0x2399be55: case 0x24682294: case 0x476a98c7:
      r = true; break;
  }
  return r;
}

// @ 0x00f25360
bool Obj::fn25360() {
  bool r = false;
  if (f04 == kType2B978C46) r = true;
  return r;
}

// @ 0x00f25370
bool Obj::fn25370() {
  bool r = false;
  switch (f04) {
    case 0x2b978c46: case 0x2399be55: case 0x24682294: case 0x476a98c7:
      r = true; break;
  }
  if (!r) {
    switch (f00) {
      case 0xa0ebd95a: case 0x48b8e425: case 0x812057c5: case 0x93512140:
      case 0xc7c9cc8d: case 0xd41f216b: case 0xf70ab170:
        r = true; break;
    }
  }
  return r;
}

// @ 0x00f253e0
char Obj::fn253e0() {
  return (char)(f00 == kType90C48D09);
}

// @ 0x00f253f0
char Obj::fn253f0() {
  if (f04 != kTypeB1B104) return 0;
  uint local[3];
  sub_eeca60(local, this);
  return local[1] == 0xf0000001;
}

// @ 0x00f25420
char Obj::fn25420() {
  return (char)(f00 == kType3144B430);
}

// @ 0x00f25430
bool Obj::fn25430() {
  uint t = f00;
  if (t == 0xc7c9cc8d || t == 0x48b8e425 || t == 0xd41f216b ||
      t == 0xa0ebd95a || t == 0x812057c5 || t == 0xf70ab170)
    return true;
  return false;
}

// @ 0x00f25470
bool Obj::fn25470() {
  bool r = false;
  uint t = f04;
  if (t == kType24682294 || t == kType2B978C46 || t == kType476A98C7)
    r = true;
  return r;
}

// @ 0x00f25490
bool Obj::fn25490() {
  bool r = false;
  switch (sub_eece20(this)) {
    case (int)0xe34e8a60: case (int)0xb10e526f: case (int)0xcf56099a:
    case (int)0xd37c1045: case (int)0x5b3d1d0d: case (int)0x6031c03a:
      r = true; break;
  }
  return r;
}

// @ 0x00f254d0
bool Obj::fn254d0() {
  if (sub_eecf10(this) == 0x0b7e477a) return true;
  uint t = f00;
  if (t == 0xc7c9cc8d || t == 0x48b8e425 || t == 0xd41f216b ||
      t == 0x812057c5 || t == 0xff562b48 || t == 0x35e79d51 ||
      t == 0x293fc645 || t == 0x979592bc || t == 0xfd7178fb)
    return true;
  return false;
}

// @ 0x00f25530
int Obj::fn25530() {
  uint t = f04;
  if (t == kType24682294 || t == kType2B978C46 || t == kType476A98C7) goto R;
  if (fn254d0()) goto R;
  return 0;
R:
  return 1;
}

// @ 0x00f25560
bool Obj::fn25560() {
  int t = sub_eece20(this);
  if (t == (int)kTypeE137FF08 || t == (int)kType7998CE71) return false;
  return true;
}

// @ 0x00f25580
bool Obj::fn25580() {
  int v = sub_eece20(this);
  if (v > (int)0x6031c03a) {
    if (v == (int)0x7998ce71) return true;
    return false;
  }
  if (v == (int)0x6031c03a) return sub_eecf10(this) == 0x167b1f54;
  if (v == (int)0xb10e526f) return true;
  if (v == (int)0xcf56099a) return fn254d0() == false;
  return false;
}

// @ 0x00f255d0
bool Obj::fn255d0() {
  int t = sub_eece20(this);
  switch (t) {
    case (int)kTypeE34E8A60:
    case (int)kTypeD37C1045:
    case (int)kTypeE137FF08:
    case (int)kType5B3D1D0D:
      return false;
  }
  return true;
}

// @ 0x00f25600
bool Obj::fn25600() {
  if (f00 == kType90C48D09) return false;
  if (f04 == kTypeB1B104) {
    int t = sub_eecf10(this);
    return t != (int)0x8b8556d8 && t != (int)0x8adff558;
  }
  return true;
}

// @ 0x00f25640
bool Obj::fn25640() {
  if (f04 == kTypeB1B104) {
    int t = sub_eecf10(this);
    return t != (int)0x8b8556d8 && t != (int)0x8adff558;
  }
  return true;
}

// @ 0x00f25670
bool Obj::fn25670() {
  return f04 == kType2B978C46;
}

// @ 0x00f25680
int Obj::fn25680() {
  uint t = f04;
  if (t == kType24682294 || t == kType476A98C7) return 1;
  return 0;
}

// @ 0x00f256a0
bool Obj::fn256a0() {
  uint t = f04;
  if (t == 0x24682294 || t == 0x476a98c7) {
    uint u = f18;
    if (u <= 0xbc1041e6) {
      if (u == 0xbc1041e6 || u == 0x7d433fad || u == 0x9ad7d4aa) return true;
    } else {
      if (u == 0xc0b74287 || u == 0xf670aa43) return true;
    }
  }
  return false;
}

// @ 0x00f256e0
bool Obj::fn256e0() {
  uint t = f04;
  if (t == 0x24682294 || t == 0x476a98c7) {
    uint u = f18;
    if (u <= 0x441cd3e6) {
      if (u == 0x441cd3e6 || u == 0x1a4e0708 || u == 0x2090a11b) return true;
    } else {
      if (u == 0x449c040f || u == 0x98e03c0d) return true;
    }
  }
  return false;
}

// @ 0x00f25720
bool Obj::fn25720() {
  return f04 == kType2399BE55;
}

// @ 0x00f25730
bool Obj::fn25730() {
  return sub_eece20(this) == (int)kTypeCF56099A;
}

// @ 0x00f25750
int Obj::fn25750() {
  switch (sub_eece20(this)) {
    case (int)kTypeE34E8A60: return 5;
    case (int)kTypeB10E526F: return 7;
    case (int)kTypeCF56099A: return 10;
    case (int)kTypeD37C1045: return 6;
    case (int)kType5B3D1D0D: return 6;
    case (int)kType6031C03A: return 8;
  }
  return -1;
}

// @ 0x00f257b0
Obj* Obj::fn257b0() {
  f00 = 0; f04 = 0; f08 = 0; f0c = 0;
  f10 = 0xffffffffu; f14 = 0xffffffffu; f18 = 0xffffffffu;
  b1c = 0; b20 = 0;
  f24 = 0; f28 = 0; f2c = 0;
  f30 = 0xffffffffu; f34 = 0xffffffffu;
  return this;
}

// @ 0x00f257f0
struct VarListSerializer {
  unsigned mData[0xa14 / 4];                    // +0x0000
  VarListSerializer(Obj*, const char*, int);    // 0x00692f90
  char Serialize(void*);                        // 0x00693e10
};
struct VarReader {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual void v3(); virtual void v4(); virtual void v5();
  virtual void v6(); virtual void v7(); virtual void v8();
  virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14();
  virtual int  GetVersion();
};

char Obj::fn257f0(void* serializer) {
  // Constructs a cVarListSerializer over this and serializes through it, then
  // (if the serializer version is < 15) collapses the pending key fields.
  VarListSerializer ser(this, (const char*)0x15aed38, 0x1a80d26);
  char r = ser.Serialize(serializer);
  if ((uint)((VarReader*)serializer)->GetVersion() < 0xf) {
    f00 = f24; f04 = f28; f08 = f2c; f10 = f30; f14 = f34;
    f24 = 0; f28 = 0; f2c = 0; f30 = 0xffffffffu; f34 = 0xffffffffu;
  }
  return r;
}

// ---------------------------------------------------------------------------
// Larger functions in the slice.

struct LayoutTree {          // 0x1c-byte Simulator event-tree header
  void*  mpUnused00;         // +0x00
  void*  mpNext;             // +0x04  self-referential list head
  void*  mpPrev;             // +0x08
  void*  mpRoot;             // +0x0c  tree root (nuked / destroyed)
  unsigned char mColor;      // +0x10
  unsigned char mPad11[3];   // +0x11
  void*  mpSize;             // +0x14
  unsigned mPad18;           // +0x18
  void DoNukeSubtree(void* pNode);   // 0x009a9600
  void Destroy(void* pNode);         // 0x00f240d0
};
struct LayoutGlobal {        // 0x38-byte Simulator layout singleton
  LayoutTree worlds;         // +0x00
  LayoutTree collections;    // +0x1c
};
#define gLayoutManager (*(LayoutGlobal**)0x016c8318)   /* 0x016c8318 */

void* FUN_00f473a0(unsigned size, const char* name, int a, int b,
                   const char* file, int line);      // 0x00f473a0
void  FUN_00f47380(void* p);                         // 0x00f47380

extern "C" {
  void* sub_manager_0067cb30(void);
  int   sub_005f7930(void);
  int   sub_00552300(void*);
}

struct AssetDir {                                       // SP::Pollen::cAssetDirectory
  bool GetLocalKey(void* a1, void* a2, void* pKey);     // 0x0054e460
  bool IsPending(void* a1, void* a2);                   // 0x0054e740
};
struct UintArray {                                      // 3-dword key array
  unsigned m00;                                         // +0x00
  int      m04;                                         // +0x04
  int      m08;                                         // +0x08
  UintArray* Self();                                    // 0x00572590
};
struct AssetManager {
  unsigned  mPad00[0x16];                               // +0x00
  AssetDir* mpDirectory;                                // +0x58
};
struct AssetThing {                                     // object returned by 0x005f7930
  unsigned mPad00[0x11];                                // +0x00
  void*    mpValue;                                     // +0x44
  bool GetKey(void* p, UintArray* pKey);                // 0x005f8a10
};

// @ 0x00f24d30
void fn24d30() {
  LayoutGlobal* g = (LayoutGlobal*)FUN_00f473a0(0x38, "Simulator", 0, 0, 0, 0);
  if (g) {
    // default-construct the two embedded event-tree headers
    g->worlds.mpNext = (void*)&g->worlds.mpNext;
    g->worlds.mpPrev = (void*)&g->worlds.mpNext;
    g->worlds.mpRoot = 0;
    g->worlds.mColor = 0;
    g->worlds.mpSize = 0;
    g->collections.mpNext = (void*)&g->collections.mpNext;
    g->collections.mpPrev = (void*)&g->collections.mpNext;
    g->collections.mpRoot = 0;
    g->collections.mColor = 0;
    g->collections.mpSize = 0;
  }
  gLayoutManager = g;
}

// @ 0x00f24d90
void fn24d90() {
  LayoutGlobal* g = gLayoutManager;
  if (g) {
    LayoutTree& c = g->collections;
    c.DoNukeSubtree(c.mpRoot);                             // free the world tree
    LayoutTree& w = g->worlds;
    w.Destroy(w.mpRoot);                                   // destroy the collection tree
    FUN_00f47380(g);
  }
}

// --- types used by 0x00f24b30 -------------------------------------------------
#ifndef PV
#define PV(n) virtual void pv##n();
#endif

// The object reached through root->GetComponent(0x8367427): slot +0x04 yields a
// boolean-ish sub object, slot +0x08 yields something with a position.
struct InnerCheck {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual char Check();                        // +0x2c
};
struct PosProvider {
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual float* GetPos();                     // +0x2c
};
struct EffectComp {
  PV(0)                                        // +0x00
  virtual InnerCheck*    GetInner();           // +0x04
  virtual PosProvider*   GetPosProvider();     // +0x08
  unsigned mKind;                              // +0x04  dispatch kind (6/0xa/0xd/0xf)
};
struct EffectRoot {
  PV(0) PV(1) PV(2)
  virtual EffectComp* GetComponent(unsigned id);   // +0x0c
};
struct EffectOwner {                           // result of FUN_00ae6740
  PV(0) PV(1)
  virtual PosProvider* GetPosProvider();       // +0x08
  PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  unsigned mPad04[9];                          // +0x04
  void* mpSlot28;                              // +0x28
};

void* FUN_00ae6740(void* p);                              // 0x00ae6740
void* FUN_00f20240(void* pSlot);                          // 0x00f20240
void  FUN_00f24ae0(int* a1, int a2, float a3);            // 0x00f24ae0

// Shared float constants the original reads straight out of .rdata.
extern float g_1485720;   // 0x01485720  1.0f
extern float g_148c3b8;   // 0x0148c3b8  0.111110926f
extern float g_1471064;   // 0x01471064  0.5f
extern float g_1488874;   // 0x01488874  0.1f

// @ 0x00f24b30
// Sends an update to the effect component of root, for the given dispatch mode:
// the component's kind selects the only handled class of effects, whose scale is
// derived from the distance between the component's position and the owner's.
void fn24b30(EffectRoot* root, unsigned mode) {
  if (!root) return;
  EffectComp* comp = root->GetComponent(0x8367427);
  if (!comp || comp->mKind == 0) return;
  if (comp->GetInner()->Check()) return;
  switch (comp->mKind) {
    case 6: case 10: case 13: case 15: {
      EffectOwner* o = (EffectOwner*)FUN_00ae6740(root);
      void* selected;
      if (mode == 0x13) selected = o->mpSlot28;
      else              selected = 0;
      void* rec = FUN_00f20240(&o->mpSlot28);
      float scale = 0.0f;
      if (rec) {
        unsigned t = *(unsigned*)((char*)rec + 4);
        if (t == 0xf || t == 6 || t == 0xa || t == 0xd) {
          Vec3 p1 = *(Vec3*)comp->GetPosProvider()->GetPos();
          Vec3* p2 = (Vec3*)o->GetPosProvider()->GetPos();
          Vec3 delta;
          delta.z = p2->z - p1.z;
          delta.x = p2->x - p1.x;
          delta.y = p2->y - p1.y;
          double d = sqrt((double)delta.z * delta.z + (double)delta.x * delta.x
                          + (double)delta.y * delta.y);
          d = (d - g_1485720) * g_148c3b8;
          float v = (float)d;
          if (v < 0.0f) v = 0.0f;
          if (v > g_1485720) v = g_1485720;
          scale = (float)((double)v * g_1471064 + g_1488874);
        }
      }
      FUN_00f24ae0((int*)comp, (int)selected, scale);
      break;
    }
    default:
      break;
  }
}

// --- types used by 0x00f24dc0 -------------------------------------------------
struct GameDataList {                  // Simulator::tGameDataVectorT header
  void*  mPad00;                       // +0x00
  void** mpBegin;                      // +0x04
  void** mpEnd;                        // +0x08
  void*  mPad0c;                       // +0x0c
  void*  mAllocator;                   // +0x10
};
struct RefObj {                        // ref-counted game object base
  virtual void AddRef();               // +0x00
  virtual void Release();              // +0x04
};
struct PtrVector {                     // eastl::vector<T*> header
  void** mpBegin;                      // +0x00
  void** mpEnd;                        // +0x04
  void** mpCap;                        // +0x08
  PtrVector* Reserve(unsigned n, void* allocator);   // 0x00b93c60
};
struct GameDataMgr {                   // SP::cGameNounManager
  GameDataList* GetGameDataVector(unsigned a, unsigned b, unsigned c, unsigned d,
                                  unsigned e);       // 0x00b21340
};
void  FUN_00829110(void*** out, void** first, void** last, void** dest,
                   int index);                       // 0x00829110
void* FUN_00f20ef0(int* p, float dt);                // 0x00f20ef0
void* FUN_00f243c0(int* p, float dt);                // 0x00f243c0

#define SIM_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// @ 0x00f24dc0
// Advances every interactable game-data object by dt: snapshots both of the noun
// manager's game-data vectors, dispatches each element on its kind (6 = update,
// 9 = secondary update, 0xd = timer advance) and releases the snapshots.
void fn24dc0(float dt) {
  sub_f24200();
  GameDataMgr* mgr = (GameDataMgr*)sub_b3d300();
  GameDataList* list = mgr->GetGameDataVector(0xcd7d10, 0xd3d420, 0xc5fc70, 0xb1e500,
                                              0x18c88e4);
  int n = (int)((char*)list->mpEnd - (char*)list->mpBegin) >> 2;
  PtrVector tmp;
  tmp.Reserve((unsigned)n, &list->mAllocator);
  void** out = tmp.mpBegin;
  FUN_00829110(&out, list->mpBegin, list->mpEnd, tmp.mpBegin, 0);
  int count = (int)((char*)out - (char*)tmp.mpBegin) >> 2;
  void** base = tmp.mpBegin;
  for (int i = 0; i < count; ++i) {
    if (((InnerCheck*)base[i])->Check() == 1) continue;
    char* p = base[i] ? (char*)base[i] + 0x34 : 0;
    int kind = *(int*)(p + 4);
    if (kind == 6) { FUN_00f20ef0((int*)p, dt); continue; }
    if (kind == 9) { FUN_00f243c0((int*)p, dt); continue; }
    if (kind == 0xd && *(char*)(p + 0x30) != 0) *(float*)(p + 0x34) += dt;
  }

  mgr = (GameDataMgr*)sub_b3d300();
  GameDataList* list2 = mgr->GetGameDataVector(0xcd7d10, 0xd3d420, 0xd3d440, 0xb1e500,
                                               0x3a2511e);
  int n2 = (int)((char*)list2->mpEnd - (char*)list2->mpBegin) >> 2;
  void** buf = 0;
  if (n2 != 0) {
    buf = (void**)FUN_00f473a0((unsigned)n2 * 4, "Simulator", 0, 0, SIM_ALLOC_FILE, 0xd1);
  }
  void** out2 = 0;
  FUN_00829110(&out2, list2->mpBegin, list2->mpEnd, buf, 0);
  int count2 = (int)((char*)out2 - (char*)buf) >> 2;
  void** base2 = buf;
  for (int i = 0; i < count2; ++i) {
    if (((InnerCheck*)base2[i])->Check() == 1) continue;
    char* p = base2[i] ? (char*)base2[i] + 0x130 : 0;
    int kind = *(int*)(p + 4);
    if (kind == 6) { FUN_00f20ef0((int*)p, dt); continue; }
    if (kind == 9) { FUN_00f243c0((int*)p, dt); continue; }
    if (kind == 0xd && *(char*)(p + 0x30) != 0) *(float*)(p + 0x34) += dt;
  }

  for (void** p = buf; p < out2; ++p) {
    if (*p) ((RefObj*)*p)->Release();
  }
  if (buf && ((int*)buf)[-1] != 0) FUN_00f47380(buf);
  for (void** p = tmp.mpBegin; p < tmp.mpCap; ++p) {
    if (*p) ((RefObj*)*p)->Release();
  }
  if (tmp.mpBegin && ((int*)tmp.mpBegin)[-1] != 0) FUN_00f47380(tmp.mpBegin);
}

// @ 0x00f25930
bool fn25930(void* a1, void* a2, Vec3i* out) {
  int key[3];
  key[0] = 0; key[1] = 0; key[2] = 0;
  AssetManager* mgr = (AssetManager*)sub_manager_0067cb30();
  AssetDir* dir = mgr->mpDirectory;
  if (dir->GetLocalKey(a1, a2, key)) {
    if (!dir->IsPending(a1, a2)) {
      if (out) { out->x = key[0]; out->y = key[1]; out->z = key[2]; }
      return true;
    }
  }
  return false;
}

// @ 0x00f259b0// @ 0x00f259b0
bool fn259b0(int* p, void** out) {
  AssetThing* mgr = (AssetThing*)sub_005f7930();
  if (mgr && *p != 0) {
    UintArray key;
    key.Self();
    if (mgr->GetKey(p, &key)) {
      p[2] = key.m04;
      *p = key.m08;
      *out = (void*)key.m00;
      return true;
    }
    switch (sub_00552300(p)) {
      case 0:
        *out = 0;
        break;
      case 1:
        *out = mgr->mpValue;
        return true;
    }
    return true;
  }
  return false;
}
