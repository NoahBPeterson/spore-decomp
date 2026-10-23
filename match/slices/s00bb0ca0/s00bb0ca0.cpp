// match/slices/s00bb0ca0/s00bb0ca0.cpp
// Object file: SPStarManager/SPStarSearch.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Star-grid enumeration / star-record gather / empire resolution and the
// star-manager map (de)serializers.  Local stub structs carry the retail field
// offsets the disassembly shows; callees are external relocations.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---- globals (address in the comment) --------------------------------------
extern float g_156c638;   // 0x156c638 grid scale
extern float g_13ef54c;   // 0x13ef54c 1.1f
extern float g_1485378;   // 0x1485378 0.0f
extern float g_1465eb8;   // 0x1465eb8 FLT_MAX
extern float g_1466178;   // 0x1466178 step multiplier
extern float g_140e968;   // 0x140e968 step multiplier
extern float g_1470f1c;   // 0x1470f1c growth multiplier
extern u8    g_1689e38;   // 0x1689e38 static-init guard
extern void* g_1689e24;   // 0x1689e24 static star vector begin
extern void* g_1689e28;   // 0x1689e28 static star vector end
extern void* g_1689e2c;   // 0x1689e2c static star vector cap
extern void* g_16dda8c;   // 0x16dda8c background-sim manager
extern wchar_t gEmptyString16[];  // 0x1667bac

// ---- external callees ------------------------------------------------------
void        __stdcall FUN_00ba7100(float* pos, int* outx, int* outy); // 0xba7100
int         __cdecl FUN_00ba6bb0(void* a, void* b, void* c, void* d); // 0xba6bb0
int         __stdcall FUN_00ba6e80(int* vec, void* civ, float thr, int maxGroups); // 0xba6e80
void        __cdecl FUN_00f47380(void* p);                             // 0xf47380
void*       __cdecl FUN_00f473a0(u32 size, const char* name, int a, int b,
                                 const char* file, int line);          // 0xf473a0
int         __cdecl atexit(void (__cdecl*)(void));                     // 0x11e07ef
float       __cdecl FUN_010434c0(void* civ, void* cities);             // 0x10434c0
void*       __cdecl FUN_00b3d2a0();                                    // 0xb3d2a0
void*       __cdecl FUN_0102f810();                                    // 0x102f810
void        __cdecl FUN_0093a780(void* stream, void* out, int n, int f); // 0x93a780
void        __cdecl FUN_00babb70(void* a, int n, void* v);             // 0xbabb70
void*       __cdecl FUN_00ba95f0(void* b, void* e, void* v, u8 f);     // 0xba95f0
int         __cdecl FUN_005e9260(void* a0, void* a1, void* b0, void* b1); // 0x5e9260
void        __cdecl FUN_011e0744(void* dst, void* src, int size);      // 0x11e0744
void        __cdecl FUN_00693890(void* s);                             // 0x693890
void*       __cdecl FUN_005e9de0(void* out, void* val, unsigned a);    // 0x5e9de0
void*       __cdecl FUN_007c8b70(void* a, void* b, void* c);           // 0x7c8b70
void        __cdecl FUN_00693c70(void* s);                             // 0x693c70
void*       __cdecl FUN_0084ab40(void* a, void* b, void* c);           // 0x84ab40
void*       __cdecl FUN_00e5c780(void* tree, void* key);               // 0xe5c780

// ---- helper stubs (thiscall modelled as member functions) ------------------

// A ref-counted object whose vtable slots this TU invokes.
struct IRef {
  virtual int  AddRef();        // +0x00
  virtual void Release();       // +0x04
};

// Object that carries the star-list vector helpers.
struct RefCounted {
  int   AddRef();                       // 0x801920
  void* GetCities(void* civ);           // 0x5c65e0
  int   GetItemInstanceID();            // 0xc87040
};

// eastl vector of raw pointers (begin/end/cap).
struct EAVec {
  void* mpBegin;   // +0x00
  void* mpEnd;     // +0x04
  void* mpCap;     // +0x08
  void  Insert(void* mpEndPos, void* first, void* last, int arg);  // 0x1012030
  void  Erase(void* first, void* last);                            // 0xe25bd0
  void  DoInsertValue(void* pos, void** value);                    // 0xaea5d0
  void  GrowPush(void* pos, void** value);                         // 0x554820
  void  GrowPushW(void* pos, void** value);                        // 0x547e90
};

// A sorted container used by the gather helpers (begin/end/cap + flag).
struct StarVec {
  void* mpBegin;   // +0x00
  void* mpEnd;     // +0x04
  void* mpCap;     // +0x08
  char  pad00c[8];
  u8    mFlag;     // +0x14
  void  InsertAt(void* pos, void** value);   // 0xea9440
};

// A float vector (SpVector<float>) with an out-of-line resize.
struct FloatVec {
  float* mpBegin;
  void   Resize(int n);   // 0x4afc80
};

// Direct-call thiscall helpers reached from the (de)serializers.
struct Helper {
  void NukeSubtree(void* n);             // 0x934460
  void CopyAssign(void* a, void* b);     // 0x6a4950
  void CopyAssignW(void* a, void* b);    // 0x547e50
  void ClearVec(void* v);                // 0xb22de0
  void ClearVecW(void* v);               // 0xbae000
};

// Non-trivial 8-byte result so MSVC returns it through a hidden sret pointer.
struct NodeBool {
  void*         node;
  unsigned char second;
  NodeBool(void* n, unsigned char s) : node(n), second(s) {}
};

// A tree container with an out-of-line lower_bound (0xba95f0) and insert (0xbaf820).
struct StarTree {
  int*  mBegin;   // +0x00
  int*  mEnd;     // +0x04
  char  pad008[0xc];
  u8    mFlag;    // +0x14
  void* Insert(void* pos, void* key);    // 0xbaf820
  NodeBool FUN_00bb1560(void* key);
};

// A map node holding a wstring key and an int value.
struct WNode {
  void* mL;        // +0x00
  void* mR;        // +0x04
  void* mP;        // +0x08
  u8    mC;        // +0x0c
  char  pad[3];
  void* mpBegin;   // +0x10
  void* mpEnd;     // +0x14
  void* mpCap;     // +0x18
  int   mValue;    // +0x20
};

// The star grid manager (`this` of the grid helpers).
struct StarGrid {
  char  pad000[0xc8];
  int*  mGrid;   // +0xc8  grid base (row stride 0x500 dwords)
  int   pad0cc[0x150 / 4 - 0xc8 / 4 - 1];
  StarTree mEmpires;   // +0x150

  void FUN_00bb0ca0(float* pos, int range, char flag, EAVec* out);
  void FUN_00bb0d80(float* pos, float radius, EAVec* out);
  int  FUN_00bb0e90(float* pos, void* crit);
  void FUN_00bb1080(float* pos, void* crit, EAVec* out);
  void FUN_00bb1200(float* pos, float radius, StarVec* out);
  void* FUN_00bb1340(void* nounMgr);
};

// The criteria / query block used by the gather helpers.
struct Criteria {
  char  pad000[0x10];
  float m10;   // +0x10
  float m14;   // +0x14
  int   m18;   // +0x18
};

// ---------------------------------------------------------------------------
// @ 0x00bb0ca0  __thiscall(float* pos, int range, char flag, EAVec* out), ret 0x10
// Square scan of the star grid around `pos`; every cell is appended to `out`
// (border cells only when `flag` is set).
// ---------------------------------------------------------------------------
void StarGrid::FUN_00bb0ca0(float* pos, int range, char flag, EAVec* out) {
  int cx, cy;
  FUN_00ba7100(pos, &cx, &cy);
  int lo = -range;
  for (int x = lo; x <= range; ++x) {
    int gx = x + cx;
    if ((u32)gx > 0x3f) continue;
    int y = lo;
    int gy = y + cy;
    int idx = (gy * 0x40 + gx) * 0x14;
    for (; y <= range; ++y, ++gy) {
      if ((u32)gy <= 0x3f) {
        if (!flag || x == lo || x == range || y == lo || y == range) {
          out->Insert(out->mpEnd, &mGrid[idx], &mGrid[idx + 4], (int)flag);
        }
      }
      idx += 0x500;
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x00bb0d80  __thiscall(float* pos, float radius, EAVec* out), ret 0xc
// Rectangular region of the grid: the two corner cells of the box around `pos`
// are mapped and every cell in between is appended.
// ---------------------------------------------------------------------------
void StarGrid::FUN_00bb0d80(float* pos, float radius, EAVec* out) {
  float lo[2];
  int x0, y0, x1, y1;
  lo[0] = pos[0] - radius;
  lo[1] = pos[1] - radius;
  FUN_00ba7100(lo, &x0, &y0);
  float hi[2];
  hi[0] = pos[0] + radius;
  hi[1] = pos[1] + radius;
  FUN_00ba7100(hi, &x1, &y1);
  for (int x = x0; x <= x1; ++x) {
    if (y0 > y1) break;
    int idx = (y0 * 0x40 + x) * 0x14;
    int n = y1 - y0 + 1;
    do {
      out->Insert(out->mpEnd, &mGrid[idx], &mGrid[idx + 4], x);
      idx += 0x500;
    } while (--n);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00bb0e90  __thiscall(float* pos, Criteria* crit), ret 8
// Growing-ring star search: expand the scan radius until a candidate is found.
// ---------------------------------------------------------------------------
int StarGrid::FUN_00bb0e90(float* pos, void* crit) {
  EAVec found;
  found.mpBegin = 0;
  found.mpEnd = 0;
  found.mpCap = 0;
  FUN_00bb0ca0(pos, 1, 0, &found);

  Criteria* c = (Criteria*)crit;
  float radius = c->m10;
  if (!(radius > 0.0f)) radius = g_156c638 * g_13ef54c;
  float lo = g_156c638 * g_1466178;
  float hi = g_156c638 * g_140e968;
  char grow = 1;
  float step = lo;
  float best = g_1465eb8;
  void* bestObj = 0;
  float limit = radius;

  for (;;) {
    void** p = (void**)found.mpBegin;
    void** e = (void**)found.mpEnd;
    for (; p != e; ++p) {
      void* obj = *p;
      float score = g_1465eb8;
      if (FUN_00ba6bb0(pos, obj, crit, &score)) {
        if (score < best) { best = score; bestObj = obj; }
      }
    }
    if (bestObj != 0) break;
    if (c->m10 == 0.0f || !(limit > step)) break;
    if (grow) { step = hi * 2.0f; grow = 0; }
    else      { step = step + hi; }
    if (limit <= step) step = limit;
    found.Erase(found.mpBegin, found.mpEnd);
    FUN_00bb0d80(pos, step, &found);
  }

  // release the local star vector
  void** p = (void**)found.mpBegin;
  void** e = (void**)found.mpEnd;
  for (; p < e; ++p) {
    if (*p) ((IRef*)*p)->Release();
  }
  if (found.mpBegin && ((int*)found.mpBegin)[-1] != 0) FUN_00f47380(found.mpBegin);
  return (int)(long)bestObj;
}

// ---------------------------------------------------------------------------
// @ 0x00bb1080  SP::cStarManager::GetStarRecords(float* pos, Criteria*, EAVec* out), ret 0xc
// ---------------------------------------------------------------------------
void StarGrid::FUN_00bb1080(float* pos, void* crit, EAVec* out) {
  Criteria* c = (Criteria*)crit;
  float radius = c->m10;
  if (!(radius > 0.0f)) radius = g_156c638 * g_13ef54c;
  if (c->m14 > 0.0f) radius += c->m14;

  if ((g_1689e38 & 1) == 0) {
    g_1689e38 |= 1;
    g_1689e24 = 0;
    g_1689e28 = 0;
    g_1689e2c = 0;
    atexit((void (__cdecl*)(void))0x13c2f50);
  }
  ((EAVec*)&g_1689e24)->Erase(g_1689e24, g_1689e28);
  FUN_00bb0d80(pos, radius, (EAVec*)&g_1689e24);

  int n = (int)((char*)g_1689e28 - (char*)g_1689e24) >> 2;
  if (c->m14 > 0.0f) n = FUN_00ba6e80((int*)&g_1689e24, pos, c->m14 * c->m14, c->m18);

  for (int i = 0; i < n; ++i) {
    void* obj = ((void**)g_1689e24)[i];
    if (FUN_00ba6bb0(pos, obj, crit, 0)) {
      void* tmp = obj;
      if (obj) ((IRef*)obj)->AddRef();
      if (out->mpEnd < out->mpCap) {
        void* slot = out->mpEnd;
        out->mpEnd = (char*)out->mpEnd + 4;
        if (slot) {
          *(void**)slot = obj;
          if (obj) ((IRef*)obj)->AddRef();
        }
      } else {
        out->DoInsertValue(out->mpEnd, &tmp);
        obj = tmp;
      }
      if (obj) ((IRef*)obj)->Release();
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x00bb1200  __thiscall(float* pos, float radius, StarVec* out), ret 0xc
// Gather the grid stars in a box and keep those with enough cities.
// ---------------------------------------------------------------------------
void StarGrid::FUN_00bb1200(float* pos, float radius, StarVec* out) {
  if (!(radius > 0.0f)) radius = g_156c638 * g_13ef54c;
  float thr = radius * radius;

  EAVec found;
  found.mpBegin = 0;
  found.mpEnd = 0;
  found.mpCap = 0;
  FUN_00bb0d80(pos, radius, &found);

  void** p = (void**)found.mpBegin;
  void** e = (void**)found.mpEnd;
  for (; p != e; ++p) {
    void* obj = *p;
    int refs = ((RefCounted*)obj)->AddRef();
    if (refs <= 3) continue;
    void* cities = ((RefCounted*)obj)->GetCities(pos);
    float score = FUN_010434c0(pos, cities);
    if (score > thr) continue;

    void* slot = out->mpEnd;
    void* bb = out->mpBegin;
    void* r = FUN_00ba95f0(bb, slot, &obj, out->mFlag);
    if (r == slot) {
      if (slot == out->mpCap) { out->InsertAt(slot, &obj); continue; }
      out->mpEnd = (char*)slot + 4;
      if (slot) *(void**)slot = obj;
    } else if (obj < *(void**)r) {
      if (slot == out->mpCap) { out->InsertAt(slot, &obj); continue; }
      out->mpEnd = (char*)slot + 4;
      if (slot) *(void**)slot = obj;
    }
  }

  void** q = (void**)found.mpBegin;
  void** qe = (void**)found.mpEnd;
  for (; q < qe; ++q) if (*q) ((IRef*)*q)->Release();
  if (found.mpBegin && ((int*)found.mpBegin)[-1] != 0) FUN_00f47380(found.mpBegin);
}

// ---------------------------------------------------------------------------
// @ 0x00bb1340  __thiscall(cGameNounManager* mgr), ret 4
// Resolve (or create) the empire that owns the avatar of `mgr`.
// ---------------------------------------------------------------------------
struct NounMgr {
  int GetAvatar();                          // 0xb1fdb0
  void FUN_00a16a90(unsigned id);           // 0xa16a90
};
struct StarMgr {
  void* FUN_00baf0b0(int avatarId);         // 0xbaf0b0
  void  FUN_00baf630(int avatarId, void* mgr); // 0xbaf630
};
struct Empire {
  void FUN_00c359a0(int avatarId, int flag); // 0xc359a0
  void AddStar(void* item);                  // 0xc341a0
  void FUN_00c30c10(void* item);             // 0xc30c10
  char FUN_00c308b0();                       // 0xc308b0
  void SetSpecies(void* species);            // 0xc33690
  void FUN_00c31a60(void* x);                // 0xc31a60
};
struct Item {
  unsigned GetItemInstanceID();              // 0xc87040
  void* FUN_00bba500();                      // 0xbba500
};

void* StarGrid::FUN_00bb1340(void* nounMgr) {
  int avatar = ((NounMgr*)nounMgr)->GetAvatar();
  int avatar2 = ((NounMgr*)nounMgr)->GetAvatar();
  if (avatar2 == -1) {
    unsigned v = *(unsigned*)((char*)this + 0x1d4);
    *(unsigned*)((char*)this + 0x1d4) = v + 1;
    ((NounMgr*)nounMgr)->FUN_00a16a90(v | 0x80000000u);
    avatar = ((NounMgr*)nounMgr)->GetAvatar();
  }
  if (avatar != -1) {
    void** node = (void**)((char*)this + 0x150);
    void* hit = FUN_00e5c780(node, &avatar);
    if (*(void**)hit != (char*)this + 0x154) {
      void* emp = *(void**)(*(int*)hit + 0x14);
      if (emp) return emp;
    }
  }
  {
    void** node = (void**)((char*)this + 0x12c);
    void* hit = FUN_00e5c780(node, &avatar);
    void* item;
    if (*(void**)hit == (char*)this + 0x130 ||
        (item = *(void**)(*(int*)hit + 0x14)) == 0) {
      ((StarMgr*)this)->FUN_00baf630(avatar, nounMgr);
      item = nounMgr;
    }
    unsigned id = ((Item*)item)->GetItemInstanceID();
    char flag = (id & 3) != 0;
    StarMgr* mgr = (StarMgr*)FUN_00b3d2a0();
    Empire* emp = (Empire*)mgr->FUN_00baf0b0(avatar);
    emp->FUN_00c359a0(avatar, (int)nounMgr);
    emp->AddStar(item);
    emp->FUN_00c30c10(item);
    if (flag) {
      int* slot = (int*)((char*)g_16dda8c + 0x1c);
      int old = *slot;
      if ((void*)old != (void*)emp) {
        if (emp) ((IRef*)emp)->AddRef();
        *slot = (int)emp;
        if (old) ((IRef*)old)->Release();
      }
    }
    if (emp->FUN_00c308b0()) emp->SetSpecies(((Item*)item)->FUN_00bba500());
    void* s = FUN_0102f810();
    emp->FUN_00c31a60(s);
    return emp;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00bb14a0  __cdecl(void* writer, EAVec* vec)
// Deserialize a list of star pointers into `vec`.
// ---------------------------------------------------------------------------
void* FUN_00bb14a0(void* writer, EAVec* vec) {
  u32 count = 0;
  void* s = ((void* (__thiscall*)(void*))(*(int**)writer)[8])(writer);
  void* r = ((void* (__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093a780(r, &count, 1, 0);

  int have = (int)((char*)vec->mpEnd - (char*)vec->mpBegin) >> 2;
  if ((u32)have < count) {
    void* tmp = 0;
    FUN_00babb70(vec->mpEnd, count - have, &tmp);
  } else {
    vec->Erase((char*)vec->mpBegin + count * 4, vec->mpEnd);
  }

  for (int i = 0; i < (int)count; ++i) {
    void** slot = (void**)((char*)vec->mpBegin + i * 4);
    void* old = *slot;
    if (old) { *slot = 0; ((IRef*)old)->Release(); }
    ((void (__thiscall*)(void*, int, void**, int))(*(int**)writer)[10])(writer, 0x3e4353b, slot, 0);
  }
  return writer;
}

// ---------------------------------------------------------------------------
// @ 0x00bb1560  __thiscall(void* key) -> NodeBool, ret 8
// Map find-or-insert: return the existing node or insert a new one.
// ---------------------------------------------------------------------------
NodeBool StarTree::FUN_00bb1560(void* key) {
  void* end = mEnd;
  void* it = FUN_00ba95f0(mBegin, end, key, mFlag);
  if (it != end) {
    if (FUN_005e9260(*(void**)key, *((void**)key + 1),
                     *(void**)it, *((void**)it + 1)) >= 0) {
      return NodeBool(it, 0);
    }
  }
  void* r = Insert(it, key);
  return NodeBool(r, 1);
}

// ---------------------------------------------------------------------------
// @ 0x00bb15d0  __cdecl(void* prop, void* out, u32 type, FloatVec* vec)
// Read a property into a float vector; returns whether it was copied.
// ---------------------------------------------------------------------------
bool FUN_00bb15d0(void* prop, void* out, u32 type, FloatVec* vec) {
  if (prop != 0) {
    void* rec;
    char ok = ((char (__thiscall*)(void*, void*, void**))(*(int**)prop)[9])(prop, out, &rec);
    if (ok) {
      u16 kind = *(u16*)((char*)rec + 0x12);
      if (kind == (u16)type) {
        u16 flags = *(u16*)((char*)rec + 0x10);
        if (flags & 0x10) {
          int count;
          if (flags & 0x30) count = *(int*)((char*)rec + 8);
          else count = (kind != 0) ? 1 : 0;

          void* src;
          if (flags & 0x30) src = *(void**)rec;
          else src = (kind != 0) ? rec : 0;

          vec->Resize(count);
          FUN_011e0744(vec->mpBegin, src, count * 4);
          return 1;
        }
      }
    }
  }
  return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00bb1660  __cdecl(void* reader, void* map)
// Deserialize the star-manager's wstring->int map.
// ---------------------------------------------------------------------------
void FUN_00bb1660(void* reader, void* map) {
  char* m = (char*)map;
  ((Helper*)reader)->NukeSubtree(m);
  *(void**)(m + 8) = m + 4;
  *(void**)(m + 0xc) = 0;
  *(void**)(m + 4) = m + 4;
  m[0x10] = 0;
  *(void**)(m + 0x14) = 0;

  u32 count = 0;
  void* s = ((void* (__thiscall*)(void*))(*(int**)reader)[8])(reader);
  void* r = ((void* (__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093a780(r, &count, 1, 0);

  for (u32 i = 0; i < count; ++i) {
    void* key[3];
    key[0] = gEmptyString16;
    key[1] = gEmptyString16;
    key[2] = gEmptyString16 + 1;
    s = ((void* (__thiscall*)(void*))(*(int**)reader)[8])(reader);
    r = ((void* (__thiscall*)(void*))(*(int**)s)[6])(s);
    FUN_00693890(r);
    ((void (__thiscall*)(void*))(*(int**)reader)[7])(reader);

    s = ((void* (__thiscall*)(void*))(*(int**)reader)[8])(reader);
    r = ((void* (__thiscall*)(void*))(*(int**)s)[6])(s);
    int val = 0;
    FUN_0093a780(r, &val, 1, 0);
    ((void (__thiscall*)(void*))(*(int**)reader)[7])(reader);

    WNode node;
    node.mpBegin = key[0];
    node.mpEnd = key[1];
    node.mpCap = key[2];
    node.mValue = val;
    FUN_005e9de0(&node, &key, i);
  }
  ((void (__thiscall*)(void*))(*(int**)reader)[7])(reader);
}

// ---------------------------------------------------------------------------
// @ 0x00bb1830  __cdecl(void* reader, EAVec* vec)
// Deserialize a list of eastl strings into `vec`.
// ---------------------------------------------------------------------------
void FUN_00bb1830(void* reader, EAVec* vec) {
  char* b = (char*)vec->mpBegin;
  char* e = (char*)vec->mpEnd;
  void* tmp = FUN_007c8b70(e, e, b);
  ((Helper*)vec)->CopyAssign(tmp, vec->mpEnd);
  vec->mpEnd = (char*)vec->mpEnd + ((e - b) >> 4) * -0x10;

  u32 count = 0;
  void* s = ((void* (__thiscall*)(void*))(*(int**)reader)[8])(reader);
  void* r = ((void* (__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093a780(r, &count, 1, 0);
  ((Helper*)vec)->ClearVec(vec);

  for (u32 i = 0; i < count; ++i) {
    void* key[3];
    key[0] = gEmptyString16;
    key[1] = gEmptyString16;
    key[2] = gEmptyString16 + 1;
    s = ((void* (__thiscall*)(void*))(*(int**)reader)[8])(reader);
    r = ((void* (__thiscall*)(void*))(*(int**)s)[6])(s);
    FUN_00693c70(r);

    if ((char*)vec->mpEnd < (char*)vec->mpCap) {
      char* slot = (char*)vec->mpEnd;
      vec->mpEnd = slot + 0x10;
      if (slot) {
        *(void**)slot = 0;
        *(void**)(slot + 4) = 0;
        *(void**)(slot + 8) = 0;
        int n = (int)((char*)key[1] - (char*)key[0]) + 1;
        if (n <= 1) {
          *(void**)slot = gEmptyString16;
          *(void**)(slot + 4) = gEmptyString16;
          *(void**)(slot + 8) = gEmptyString16 + 1;
        } else {
          void* pp = FUN_00f473a0(n, "Simulator", 0, 0,
                                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                   0xd1);
          *(void**)slot = pp;
          *(void**)(slot + 4) = pp;
          *(void**)(slot + 8) = (char*)pp + n;
        }
        char* d = (char*)*(void**)slot;
        int nb = (int)((char*)key[1] - (char*)key[0]);
        FUN_011e0744(d, key[0], nb);
        *(void**)(slot + 4) = d + nb;
        *(d + nb) = 0;
      }
    } else {
      vec->GrowPush(vec->mpEnd, key);
    }

    if ((int)((char*)key[2] - (char*)key[0]) > 1 && key[0]) FUN_00f47380(key[0]);
  }
  ((void (__thiscall*)(void*))(*(int**)reader)[7])(reader);
}

// ---------------------------------------------------------------------------
// @ 0x00bb19d0  __cdecl(void* reader, EAVec* vec)
// Deserialize a list of wstrings into `vec`.
// ---------------------------------------------------------------------------
void FUN_00bb19d0(void* reader, EAVec* vec) {
  char* b = (char*)vec->mpBegin;
  char* e = (char*)vec->mpEnd;
  void* tmp = FUN_0084ab40(e, e, b);
  ((Helper*)vec)->CopyAssignW(tmp, vec->mpEnd);
  vec->mpEnd = (char*)vec->mpEnd + ((e - b) >> 4) * -0x10;

  u32 count = 0;
  void* s = ((void* (__thiscall*)(void*))(*(int**)reader)[8])(reader);
  void* r = ((void* (__thiscall*)(void*))(*(int**)s)[6])(s);
  FUN_0093a780(r, &count, 1, 0);
  ((Helper*)vec)->ClearVecW(vec);

  for (u32 i = 0; i < count; ++i) {
    void* key[3];
    key[0] = gEmptyString16;
    key[1] = gEmptyString16;
    key[2] = gEmptyString16 + 1;
    s = ((void* (__thiscall*)(void*))(*(int**)reader)[8])(reader);
    r = ((void* (__thiscall*)(void*))(*(int**)s)[6])(s);
    FUN_00693890(r);

    if ((char*)vec->mpEnd < (char*)vec->mpCap) {
      char* slot = (char*)vec->mpEnd;
      vec->mpEnd = slot + 0x10;
      if (slot) {
        *(void**)slot = 0;
        *(void**)(slot + 4) = 0;
        *(void**)(slot + 8) = 0;
        int n = (int)(((char*)key[1] - (char*)key[0]) >> 1) + 1;
        if (n <= 1) {
          *(void**)slot = gEmptyString16;
          *(void**)(slot + 4) = gEmptyString16;
          *(void**)(slot + 8) = gEmptyString16 + 1;
        } else {
          void* pp = FUN_00f473a0(n * 2, "Simulator", 0, 0,
                                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                   0xd1);
          *(void**)slot = pp;
          *(void**)(slot + 4) = pp;
          *(void**)(slot + 8) = (char*)pp + n * 2;
        }
        char* d = (char*)*(void**)slot;
        int nb = (int)((char*)key[1] - (char*)key[0]);
        FUN_011e0744(d, key[0], nb);
        *(void**)(slot + 4) = d + nb;
        *(short*)(d + nb) = 0;
      }
    } else {
      vec->GrowPushW(vec->mpEnd, key);
    }

    if ((int)((char*)key[2] - (char*)key[0]) > 2 && key[0]) FUN_00f47380(key[0]);
  }
  ((void (__thiscall*)(void*))(*(int**)reader)[7])(reader);
}
