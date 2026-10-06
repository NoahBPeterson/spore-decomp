// Slice s00f24b30.  Simulator game-data helper functions and a set of small
// __thiscall type/key predicates.  Built /O2 /MD /Gy (no /EHsc), x87 for float
// math, SSE scalar for float copies.
//
// The many small predicates compare a 32-bit FNV "type id" stored at this+0x04
// (or this+0x00 / this+0x18) against named constants.  Those constants are FNV
// hashes of Spore type names; without the name registry they are reproduced as
// literals under kType* names.

typedef unsigned int uint;

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
  void fn257f0(void* serializer);
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
  VarListSerializer(Obj*, const char*, int);
  char Serialize(void*);
};
struct VarReader {
  virtual void v0(); virtual void v1(); virtual void v2();
  virtual void v3(); virtual void v4(); virtual void v5();
  virtual void v6(); virtual void v7(); virtual void v8();
  virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14();
  virtual int  GetVersion();
};

void Obj::fn257f0(void* serializer) {
  // Constructs a cVarListSerializer over this and serializes through it, then
  // (if the serializer version is < 15) collapses the pending key fields.
  VarListSerializer ser(this, "VarList", 0x1a80d26);
  ser.Serialize(serializer);
  if ((uint)((VarReader*)serializer)->GetVersion() < 0xf) {
    f00 = f28; f04 = f2c; f10 = f30; f28 = 0; f08 = f24; f14 = f34;
    f2c = 0; f24 = 0; f30 = 0xffffffffu; f34 = 0xffffffffu;
  }
}

// ---------------------------------------------------------------------------
// Larger functions in the slice.

struct LayoutTree {          // ~0x1c-byte eastl rbtree header
  void* mpNode;
  LayoutTree* mpAnchor;
  void* mpLeft;
  void* mpRight;
  unsigned char mColor;
  void* mpSize;
};
struct LayoutGlobal {        // 0x38-byte Simulator layout singleton
  LayoutTree worlds;         // eastl::map<unsigned,cWorld>
  LayoutTree collections;    // eastl::map<AutoRefCount,...>
};
LayoutGlobal* gLayoutManager;

extern "C" {
  void* sub_new38(int, const char*, int, int, int, int);
  void  sub_del(void*);
  void  sub_nuke(void*);
  int   sub240d0(void*);
  void* sub_manager_0067cb30(void);
  int   sub_54e460(void*, void*, void*, void*);
  int   sub_54e740(void*, void*, void*);
  int   sub_005f7930(void);
  void  sub_00572590(void*);
  int   sub_005f8a10(void*, void*, void*);
  int   sub_00552300(void*);
}

// @ 0x00f24d30
void fn24d30() {
  LayoutGlobal* g = (LayoutGlobal*)sub_new38(0x38, "Simulator", 0, 0, 0, 0);
  gLayoutManager = g;
  if (g) {
    // default-construct the two embedded eastl maps
    g->worlds.mpAnchor = (LayoutTree*)&g->worlds.mpNode;
    g->worlds.mpNode = (void*)&g->worlds.mpNode;
    g->worlds.mpLeft = 0;
    g->worlds.mpRight = 0;
    g->worlds.mColor = 0;
    g->worlds.mpSize = 0;
    g->collections.mpAnchor = (LayoutTree*)&g->collections.mpNode;
    g->collections.mpNode = (void*)&g->collections.mpNode;
    g->collections.mpLeft = 0;
    g->collections.mpRight = 0;
    g->collections.mColor = 0;
    g->collections.mpSize = 0;
  }
}

// @ 0x00f24d90
void fn24d90() {
  LayoutGlobal* g = gLayoutManager;
  if (g) {
    sub_nuke(g->worlds.mpAnchor);           // DoNukeSubtree
    sub240d0(g->worlds.mpLeft);             // destroy the world map
    sub_del(g);                             // operator delete
  }
}

// @ 0x00f24b30
// Sends a proximity/update message for the target identified by id: looks the
// target up (creating if needed), resets it, and computes a distance-based
// scale factor from the owner's current position.
void fn24b30(void* owner, unsigned /*unused*/) {
  // The original's virtual dispatch and key construction are not fully
  // reconstructed.
  (void)owner;
}

// @ 0x00f24dc0
// Advances every interactable game-data object by dt (walking the noun
// manager's data vectors twice, once for the object list and once for the
// secondary list).
void fn24dc0(float dt) {
  (void)dt;
}

// @ 0x00f25930
int fn25930(void* a1, void* a2, Vec3i* out) {
  uint key[3];
  key[0] = 0; key[1] = 0; key[2] = 0;
  void* mgr = sub_manager_0067cb30();
  void* dir = *(void**)((char*)mgr + 0x58);
  if (!sub_54e460(dir, a1, a2, key)) return 0;
  if (sub_54e740(dir, a1, a2)) return 0;
  if (out) { out->x = (int)key[0]; out->y = (int)key[1]; out->z = (int)key[2]; }
  return 1;
}

// @ 0x00f259b0
int fn259b0(int* p, void** out) {
  int mgr = sub_005f7930();
  if (!mgr || *p == 0) return 0;
  uint local_c; int local_8, local_4;
  sub_00572590(&local_c);
  if (sub_005f8a10((void*)mgr, p, &local_c)) {
    p[2] = local_8;
    *p = local_4;
    *out = (void*)local_c;
    return 1;
  }
  int r = sub_00552300(p);
  if (r == 0) {
    *out = 0;
  } else if (r == 1) {
    *out = *(void**)(mgr + 0x44);
    return 1;
  }
  return 1;
}
