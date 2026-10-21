// s00b2b8a0.cpp — unnamed class in the 0x00b2a000..0x00b2d900 region (same object as
// match/slices/s00b2c980). Nearly all entry points are __thiscall; cl rejects __thiscall on
// free functions, so the ones that use ECX are declared as members of a local stub class `S`
// (methods keep the FUN_ names so run_all's substring match still finds them). The helpers
// that only take stack arguments stay free functions with their real convention.
//
// Element types (from the disassembly):
//   * vector element of 0x24 bytes: { +0 vtable, +4..+0x20 data }  (copied by 0x00b2a3b0)
//   * eastl map/list node: { +0 next, +4 prev, +8 value }

#include <stddef.h>

#define ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---- helpers (defined in other slices / the binary) ------------------------
extern "C" void* __cdecl EastlNewArray(void* p, int fill, int size);            // 0x011e073e
extern "C" void* __cdecl EastlNew(unsigned size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EastlDelete(void* p);                                  // 0x00f47380
extern "C" void* __cdecl RBTreeIncrement(void* node);                           // 0x00921580
extern "C" void* __stdcall NounManager(void* noun);                             // 0x00b3d300
extern "C" void  __stdcall FUN_00f62ea0(int a, int b);                          // 0x00f62ea0
extern "C" void  __stdcall FUN_010210e0(void* p);                               // 0x010210e0
extern "C" void* __cdecl FUN_01021260(void);                                    // 0x01021260
extern "C" void* __cdecl FUN_008414c0(void);                                    // 0x008414c0
extern "C" void* __cdecl FUN_0067de30(void);                                    // 0x0067de30  (PropertyManager)
extern "C" void* __cdecl FUN_00f62b70(void* out);                               // 0x00f62b70
extern "C" void* __cdecl FUN_00f48aa0(void);                                    // 0x00f48aa0
extern "C" void  __cdecl FUN_00b2b720(void* tree, void* out, void* parent, void* key, int b); // 0x00b2b720 (ECX=tree)
extern "C" void* __cdecl FUN_00b2a3b0(void* dst, void* first, void* last);      // 0x00b2a3b0
extern "C" void  __cdecl FUN_00b2a400(void* dst, void* first, void* last);      // 0x00b2a400
extern "C" void  __cdecl FUN_00b2ac90(char* dst, unsigned n, void* val);        // 0x00b2ac90
extern "C" char* __cdecl FUN_00b2ad40(char* first, char* last, char* dst);      // 0x00b2ad40
extern "C" void  __cdecl FUN_00829110(void* at, void* dst, void* src, void* end); // 0x00829110
extern "C" void  __cdecl FUN_00affd00(char* first, char* last, char* dst);      // 0x00affd00
extern "C" void  __cdecl FUN_00ea0350(void* first, void* last, void* at);       // 0x00ea0350
extern "C" void  __cdecl FUN_00ac97a0(void* first, void* last, void* dst);      // 0x00ac97a0
extern "C" void* __cdecl FUN_00b2b090(void);                                    // 0x00b2b090
extern "C" void  __cdecl FUN_00b2ada0(void* first, int, int idx);               // 0x00b2ada0
extern "C" void  __cdecl FUN_00b2af00(void* a, void* b);                        // 0x00b2af00
extern "C" void  __cdecl FUN_00b2c150(void* first, void* last, float x, float y, float z); // 0x00b2c150
extern "C" void  __cdecl FUN_00b2c1c0(void* first, void* last, float x, float y, float z); // 0x00b2c1c0
extern "C" void  __cdecl FUN_00b2b6d0(void* out, void* key);                    // 0x00b2b6d0
extern "C" void  __cdecl FUN_00b2bf90(void* self, void* out, void* key, void* b); // 0x00b2bf90
extern "C" void  __cdecl FUN_00b3d420(void* key);                               // 0x00b3d420
extern "C" void  __cdecl FUN_00b2a460(void* elem);                              // 0x00b2a460
extern "C" void  __cdecl FUN_00b2a110(void);                                    // 0x00b2a110
extern "C" void  __cdecl FUN_00b2b150(void* dst, void* src);                    // 0x00b2b150
extern "C" void  __cdecl FUN_00b2b8a0(void* first, int, int idx, int, void* val, float x, float y, float z); // 0x00b2b8a0
extern "C" void* __cdecl FUN_00b90410(void* key);                                // 0x00b90410
extern "C" void  __cdecl FUN_00b225d0(void* mgr, void* noun);                    // 0x00b225d0

extern "C" int g_1568cf0;                     // 0x01568cf0
extern "C" const char g_167e0a0;              // 0x0167e0a0

// ---- remote stub classes ---------------------------------------------------
struct Vtbl { void* slots[32]; };
struct Obj {                       // refcounted object: vtable slot 0 = AddRef, slot 1 = Release
  void** vptr;
  void** raw() { return vptr; }
  void addref() { ((void(__thiscall*)(Obj*))vptr[0])(this); }
  void release() { ((void(__thiscall*)(Obj*))vptr[1])(this); }
  float* pos() { return ((float*(__thiscall*)(char*))vptr[11])((char*)this + 0x34); } // vfn +0x2c
};

struct DistInfo;                                  // 0x00b2bbe0 target object
struct TypeInfo;                                  // cTerrainDistributeInfo data at +0x10

struct Grid {                                     // cDistGrid-like, object at S+0x40
  char pad0[0x10];
  Obj*  obj;                                      // +0x10
  char pad1[0x38];
  int   cnt;                                      // +0x48
  char pad2[0x210];
  int   flags;                                    // +0x258
};

// property-manager object returned by 0x0067de30
struct PropMgr {
  char pad[0x2c];
  void __thiscall call2c(void* a, unsigned b, void** out) { ((void(__thiscall*)(void*, void*, unsigned, void**))(*(void***)((char*)this + 0x2c)))((char*)this + 0x2c, a, b, out); }
};

// species object returned by 0x00b90410
struct Species {
  void* vt;
  void* prop() { return ((void*(__thiscall*)(Species*))((void**)vt)[6])(this); }        // vfn +0x18
  int __thiscall id_() { return ((int(__thiscall*)(Species*))((void**)vt)[6])(this); }
  char pad0[0x7c];
  int  a7c;                                      // +0x7c
  int  a80;                                      // +0x80
  int  a84;                                      // +0x84
  int  a88;                                      // +0x88
};

struct Sub {                                       // subobject at S+0x34
  void* vt;
  void call38(const char* s) { ((void(__thiscall*)(Sub*, const char*))((void**)vt)[14])(this, s); }  // vfn +0x38
  void* getac() { return ((void*(__thiscall*)(Sub*))((void**)vt)[43])(this); }                       // vfn +0xac
};

struct SpeciesMgr {                                // cPlantSpeciesManager, ECX = return of 0x00b3d420
  Species* __thiscall GetSpeciesFromID(void* id) {
    return ((Species*(__thiscall*)(SpeciesMgr*, void*))0x00b90410)(this, id); // 0x00b90410
  }
};

// ---- the unnamed class -----------------------------------------------------
struct S {
  char pad0[0xc];
  void** vecBegin;                                // +0x0c
  void** vecEnd;                                  // +0x10
  void** vecCap;                                  // +0x14
  char   buf[0x100];                              // +0x20 inline buffer for the +0x0c vector
  int    f120;                                    // +0x120
  int    f124;                                    // +0x124
  char   pad1[0xb7];                              // +0x128 .. 0x1c7
  void*  treeRoot;                                // +0x1c8

  void FUN_00b2bb90();                            // 0x00b2bb90
  void FUN_00b2bbe0();                            // 0x00b2bbe0
  void FUN_00b2bf10(char);                        // 0x00b2bf10
  void FUN_00b2bf40(void* key);                   // 0x00b2bf40
  void FUN_00b2bf90(void* out, void* key, void* b); // 0x00b2bf90
  void FUN_00b2bfe0(void* pos, unsigned n, void* val); // 0x00b2bfe0
  void FUN_00b2c2a0(void* a, void* b);            // 0x00b2c2a0
  void FUN_00b2c300(void* pos, void* val);        // 0x00b2c300
  void FUN_00b2c830(void* a, int b);              // 0x00b2c830
};

struct Big {                                       // the 0x00b2c830 object (derived region of S)
  void*  vt;                                       // +0x00
  char   pad0[0x30];
  void*  subVt;                                    // +0x34 (subobject)
  char   pad1[0x6d];
  char   fa5;                                      // +0xa5
  char   fa9;                                      // +0xa9
  char   pad2[0x5e];                               // +0xaa .. 0x107
  int    f108;                                     // +0x108
  long long f110;                                  // +0x110
  char   pad3[0x50];                               // +0x118 .. 0x167
  void*  treeRoot;                                 // +0x1c8? (not used here)
  char   pad4[0x6c];                               // +0x1cc .. 0x237
  unsigned char f238;                              // +0x238
};

// pair<long long,int> used as the rb-tree key
struct Key {
  long long lo;                                    // +0
  int       hi;                                    // +8
};

// node = { ptr link; Key key; ... } with key at +0x10/+0x14
struct Node {
  Node* link;                                      // +0x00
  char  pad0[8];
  int   keyLo;                                     // +0x10
  int   keyHi;                                     // +0x14
};

static inline void iadd(long long* p) { *p = *p + 1; }

// ===========================================================================
// 0x00b2b8a0 — sift-down (heap) pass over a vector of Obj* with a float target
// ===========================================================================
// @ 0x00b2b8a0
void __cdecl FUN_00b2b8a0(Obj** first, int, int hole, int, Obj* val, float x, float y, float z)
{
  int n = hole * 2 + 2;
  while (n < *((int*)first - 1)) {
    Obj* a = first[n];
    Obj* b = first[n - 1];
    float* pa = a->pos();
    float db = (x - pa[0]) * (x - pa[0]) + (y - pa[1]) * (y - pa[1]) + (z - pa[2]) * (z - pa[2]);
    float* pb = b->pos();
    float da = (x - pb[0]) * (x - pb[0]) + (y - pb[1]) * (y - pb[1]) + (z - pb[2]) * (z - pb[2]);
    if (da < db) n = n - 1;
    Obj* up = first[n];
    Obj* dn = first[hole];
    if (up != dn) {
      if (up) up->addref();
      first[hole] = up;
      if (dn) dn->release();
    }
    hole = n;
    n = hole * 2 + 2;
  }
  if (n == *((int*)first - 1)) {
    Obj* up = first[n - 1];
    Obj* dn = first[hole];
    if (up != dn) {
      if (up) up->addref();
      first[hole] = up;
      if (dn) dn->release();
    }
    hole = n - 1;
  }
  if (val) val->addref();
  FUN_00b2ada0(first, 0, hole);
  if (val) val->release();
}

// ===========================================================================
// 0x00b2ba70 — copy_backward over 0x18-byte elements (last -> first, dest end)
// ===========================================================================
// @ 0x00b2ba70
extern "C" void* __cdecl FUN_00b2ba70(void* dst, void* first, void* last)
{
  char* d = (char*)dst;
  char* l = (char*)last;
  if (first == last)
    return d;
  do {
    l -= 0x18;
    d -= 0x18;
    *(void**)d = *(void**)l;
    Obj* nb = *(Obj**)(l + 0x10);
    Obj* ob = *(Obj**)(d + 0x10);
    if (nb != ob) {
      if (nb) nb->addref();
      *(Obj**)(d + 0x10) = nb;
      if (ob) ob->release();
    }
    *(void**)(d + 8) = *(void**)(l + 8);
    *(void**)(d + 0xc) = *(void**)(l + 0xc);
  } while (l != first);
  return d;
}

// ===========================================================================
// @ 0x00b2bb90
// @ 0x00b2c230
// ===========================================================================
// @ 0x00b2bb90
void S::FUN_00b2bb90()
{
  FUN_00b2b090();
  vecBegin = 0;
  vecEnd = 0;
  vecCap = 0;
  f120 = 0;
  f124 = 0;
  void** it = vecBegin;
  void** e = vecEnd;
  while (it < e) {
    Obj* o = (Obj*)*it;
    if (o) o->release();
    ++it;
  }
}

// ===========================================================================
// 0x00b2bbe0 — SP::cTerrainDistributeInfo::SetInfoFromProps
// ===========================================================================
// @ 0x00b2bbe0
void S::FUN_00b2bbe0()
{
  char* self = (char*)this;
  void* planet = FUN_01021260();                     // cSPLivingUniverse::GetActivePlanet
  if (!planet)
    return;
  if (!FUN_008414c0())
    return;
  char* grid0 = *(char**)((char*)planet + 0x13c);
  unsigned int* g = (unsigned int*)grid0;
  EastlNewArray((void*)(self + 0x44), 0, 0xfc);
  char* grid = (char*)g;
  int count = (int)((*(int*)(grid + 0xc0) - *(int*)(grid + 0xbc)) / 0xc);
  int used[3];
  used[0] = 0; used[1] = 0; used[2] = 0;
  int filled = 0;
  if (count > 0) {
    int off = 0;
    do {
      if (off >= 0x6c)
        break;
      char* entry = (char*)(*(int*)(grid + 0xbc) + off);
      FUN_00b3d420(entry);
      Species* sp = (Species*)FUN_00b90410(entry);
      unsigned h = (unsigned)sp->id_();
      int bucket = 0;
      if (h == 0x029c388a) bucket = 1;
      else if (h == 0x3a8be428) bucket = 0;
      else if (h == 0x6d60a1cc) bucket = 2;
      int n = used[bucket];
      int* cntp = &used[bucket];
      if (n < 3) {
        int e = n + bucket * 3;
        char* dst = self + 0x44 + e * 0x1c;
        *(int*)(dst + 0x00) = *(int*)(entry + 0);
        *(int*)(dst + 0x04) = *(int*)(entry + 4);
        *(int*)(dst + 0x08) = *(int*)(entry + 8);
        *(int*)(dst + 0x0c) = sp->a7c;
        *(int*)(self + 0x44 + (e + 3) * 0x1c) = sp->a80;
        *(int*)(dst + 0x14) = sp->a84;
        *(int*)(dst + 0x18) = sp->a88;
        *cntp = n + 1;
      }
      off += 0xc;
      ++filled;
    } while (filled < count);
  }
  char flag = 0;
  char* info = self + 0x44;
  int r = 0;
  do {
    int c = 0;
    do {
      int gg = *(int*)(self + 0x40);
      Obj* prev = *(Obj**)(r + 0x10 + gg);
      int saved = *(int*)(r + gg + 0x48);
      if (prev) prev->addref();
      if (*(int*)info == 0) {
        int g2 = *(int*)(self + 0x40);
        char* tmp = 0;
        FUN_00f62b70(&tmp);
        FUN_00b2b150((void*)(r + 0x10 + g2), tmp);
        if (tmp) ((Obj*)tmp)->release();
      } else {
        char* src = info;
        FUN_00b3d420(src);
        Species* sp = (Species*)FUN_00b90410(src);
        void* out = 0;
        char* pm = (char*)FUN_0067de30();           // PropertyManager
        void* prop = sp->prop();
        unsigned k = *(unsigned*)((char*)prop + 8);
        void* vis = sp->prop();
        ((PropMgr*)pm)->call2c(vis, (k & 0xffff62ffu) | 0x6200u, &out);
        FUN_00f62ea0(filled, (int)out);
        if (out) ((Obj*)out)->release();
      }
      *(int*)(r + 0x48 + *(int*)(self + 0x40)) = saved;
      if (*(Obj**)(r + 0x10 + *(int*)(self + 0x40)) != prev) {
        int* q = (int*)(r + 0x48 + *(int*)(self + 0x40));
        *q = *q + 1;
        flag = 1;
      }
      if (prev) prev->release();
      info += 0x1c;
      ++c;
      r += 0x40;
    } while (c < 3);
    filled += 3;
  } while (r <= 0x180);
  if (*(int*)(self + 0x40) != 0) {
    FUN_00b2a110();
    if (flag)
      *(int*)(*(int*)(self + 0x40) + 0x258) += 1;
    void* ts = FUN_00f48aa0();
    if (ts) {
      void* ts2 = FUN_00f48aa0();
      ((void(__thiscall*)(void*, void*))((void**)(*(void**)ts2))[9])(ts2, *(void**)(self + 0x40));
    }
  }
}

// ===========================================================================
// 0x00b2bf10
// ===========================================================================
// @ 0x00b2bf10
void S::FUN_00b2bf10(char force)
{
  void* p = FUN_01021260();
  if (p && force == 0)
    FUN_010210e0(p);
  FUN_00b2bbe0();
}

// @ 0x00b2c230
void* __cdecl FUN_00b2c230(void* self)
{
  S* p = (S*)self;
  p->vecBegin = 0;
  p->vecEnd = 0;
  p->vecCap = 0;
  p->vecEnd = (void**)p->buf;
  p->vecBegin = (void**)p->buf;
  p->vecCap = (void**)(p->buf + 0x100);
  p->f120 = 0;
  p->f124 = 0;
  return self;
}

// ===========================================================================
// 0x00b2bf40
// ===========================================================================
// @ 0x00b2bf40
void S::FUN_00b2bf40(void* key)
{
  void** list = (void**)this;                 // sentinel at +0
  void* cur = *list;
  if (cur == list)
    return;
  do {
    void* nxt = *(void**)cur;
    if (*(void**)((char*)cur + 8) == *(void**)key) {
      char* node = (char*)nxt;
      char* prev = *(char**)(node + 4);
      char* next = *(char**)(node + 0);
      *(void**)prev = next;
      *(void**)(next + 4) = prev;
      Obj* o = *(Obj**)(node + 8);
      if (o) o->release();
      EastlDelete(node);
    }
    cur = nxt;
  } while (cur != list);
}

// ===========================================================================
// 0x00b2bf90 — rb-tree lower_bound then node insert
// ===========================================================================
// @ 0x00b2bf90
void S::FUN_00b2bf90(void* out, void* key, void* b)
{
  void** rootp = (void**)((char*)this + 0xc);
  void* root = *rootp;
  void* parent = (char*)this + 4;
  if (root) {
    Node* n = (Node*)root;
    unsigned khi = *(unsigned*)((char*)key + 4);
    unsigned klo = *(unsigned*)key;
    do {
      parent = n;
      if (khi < (unsigned)n->keyHi || (khi == (unsigned)n->keyHi && klo < (unsigned)n->keyLo))
        n = (Node*)n->link;
      else
        n = *(Node**)((char*)n + 4);
    } while (n);
  }
  FUN_00b2b720(this, out, parent, key, 0);
}

// ===========================================================================
// 0x00b2bfe0 — vector<0x24-byte>::insert(pos, n, val)
// ===========================================================================
// @ 0x00b2bfe0
void S::FUN_00b2bfe0(void* pos, unsigned n, void* val)
{
  char* self = (char*)this;
  char* begin = *(char**)self;
  char* end = *(char**)(self + 4);
  unsigned have = (unsigned)((end - begin) >> 2) / 9;
  if (n <= have)
    goto insert_into_capacity;
  {
    unsigned total = (unsigned)((end - begin) >> 2) / 9;
    unsigned cap = total * 2;
    if (total == 0) cap = 1;
    unsigned need = total + n;
    if (cap <= need) cap = need;
    size_t off = (char*)pos - begin;
    char* ne = (char*)EastlNewArray(0, (int)(size_t)begin, (int)off);
    ne = ne + (off & ~3u);
    FUN_00b2ac90(ne, n, val);
    char* tail = *(char**)(self + 4);
    FUN_00b2ac90(ne + n * 4, (unsigned)(tail - (char*)pos) >> 2, pos);
    *(void**)self = 0;
    *(char**)(self + 4) = ne + n * 4 + ((unsigned)(tail - (char*)pos) >> 2) * 4;
    *(char**)(self + 8) = ne + cap * 4;
    return;
  }
insert_into_capacity:
  if (n == 0)
    return;
  Obj* v = *(Obj**)val;
  if (v) v->addref();
  char* me = *(char**)(self + 4);
  unsigned tail = (unsigned)((me - (char*)pos) >> 2) / 9;
  if (n < tail) {
    char* split = me - n * 0x24;
    FUN_00829110(&n, split, me, me);
    *(char**)(self + 4) = *(char**)(self + 4) + n * 0x24;
    FUN_00ac97a0(pos, split, me);
    FUN_00ea0350(pos, (char*)pos + n * 0x24, &v);
  } else {
    FUN_00b2ac90(me, n - tail, &v);
    *(char**)(self + 4) = *(char**)(self + 4) + (n - tail) * 0x24;
    char* ne = *(char**)(self + 4);
    FUN_00829110(&pos, pos, me, ne);
    *(char**)(self + 4) = *(char**)(self + 4) + tail * 0x24;
    FUN_00ea0350(pos, me, &v);
  }
  if (v) v->release();
}

// ===========================================================================
// 0x00b2c2a0 — erase range [a,b) of 0x24-byte elements
// ===========================================================================
// @ 0x00b2c2a0
void S::FUN_00b2c2a0(void* a, void* b)
{
  char* self = (char*)this;
  char* pos = (char*)FUN_00b2a3b0(b, *(void**)(self + 4), a);
  char* e = *(char**)(self + 4);
  for (; pos < e; pos += 0x24) {
    Obj* v = *(Obj**)pos;
    ((void(__thiscall*)(Obj*, int))v->vptr[0])(v, 0);
  }
  long long d = (long long)((char*)b - (char*)a);
  *(char**)(self + 4) = *(char**)(self + 4) + (int)(d / 0x24) * 0x24;
}

// ===========================================================================
// 0x00b2c300 — vector<0x24-byte>::insert(pos, val)
// ===========================================================================
// @ 0x00b2c300
void S::FUN_00b2c300(void* pos, void* val)
{
  char* self = (char*)this;
  char* end = *(char**)(self + 4);
  char* cap = *(char**)(self + 8);
  char* begin = *(char**)self;
  if (end != cap) {
    char* v = (char*)val;
    if ((char*)pos <= v && v < end)
      v += 0x24;
    if (end) FUN_00b2a460(end - 0x24);
    FUN_00b2a400(pos, end - 0x24, end);
    *(void**)((char*)pos + 4) = *(void**)(v + 4);
    *(void**)((char*)pos + 8) = *(void**)(v + 8);
    *(void**)((char*)pos + 0xc) = *(void**)(v + 0xc);
    *(float*)((char*)pos + 0x10) = *(float*)(v + 0x10);
    *(float*)((char*)pos + 0x14) = *(float*)(v + 0x14);
    *(float*)((char*)pos + 0x18) = *(float*)(v + 0x18);
    *(void**)((char*)pos + 0x1c) = *(void**)(v + 0x1c);
    *(void**)((char*)pos + 0x20) = *(void**)(v + 0x20);
    *(char**)(self + 4) = *(char**)(self + 4) + 0x24;
    return;
  }
  int cnt = (int)((end - begin) / 0x24);
  int newCap;
  if (cnt != 0)
    newCap = cnt * 2;
  else
    newCap = 1;
  char* nb = 0;
  if (newCap != 0)
    nb = (char*)EastlNew(newCap * 0x24, "Simulator", 0, 0, ALLOC_H, 0xd1);
  char* p = FUN_00b2ad40(begin, (char*)pos, nb);
  FUN_00affd00(begin, (char*)pos, nb);
  if (p) FUN_00b2a460(val);
  char* q = FUN_00b2ad40((char*)pos, *(char**)(self + 4), p + 0x24);
  FUN_00affd00((char*)pos, *(char**)(self + 4), p + 0x24);
  if (begin && *(int*)(begin - 4) != 0)
    EastlDelete(begin);
  *(void**)(self + 4) = q;
  *(void**)self = nb;
  *(char**)(self + 8) = nb + newCap * 0x24;
}

// ===========================================================================
// 0x00b2c470 — partition by distance (hoare-style, both ends)
// ===========================================================================
// @ 0x00b2c470
extern "C" char* __cdecl FUN_00b2c470(Obj** first, Obj** last, Obj* owner, float x, float y, float z)
{
  char* lo = (char*)first;
  while (1) {
    while (1) {
      float* pa = (*(Obj**)lo)->pos();
      float db = (x - pa[0]) * (x - pa[0]) + (y - pa[1]) * (y - pa[1]) + (z - pa[2]) * (z - pa[2]);
      float* pb = owner->pos();
      float da = (x - pb[0]) * (x - pb[0]) + (y - pb[1]) * (y - pb[1]) + (z - pb[2]) * (z - pb[2]);
      if (da <= db) break;
      lo += 4;
    }
    char* hi = (char*)last;
    do {
      hi -= 4;
      Obj* cand = *(Obj**)hi;
      float* pc = owner->pos();
      float dc = (x - pc[0]) * (x - pc[0]) + (y - pc[1]) * (y - pc[1]) + (z - pc[2]) * (z - pc[2]);
      float* pd = cand->pos();
      float dd = (x - pd[0]) * (x - pd[0]) + (y - pd[1]) * (y - pd[1]) + (z - pd[2]) * (z - pd[2]);
      if (dd >= dc) break;
    } while (1);
    last = (Obj**)hi;
    if (lo >= hi) break;
    FUN_00b2af00(lo, hi);
    lo += 4;
  }
  if (owner) owner->release();
  return lo;
}

// ===========================================================================
// 0x00b2c640 — quickselect-ish partition then settle
// ===========================================================================
// @ 0x00b2c640
extern "C" void __cdecl FUN_00b2c640(Obj** first, Obj** last, Obj* owner, float x, float y, float z)
{
  char* a4 = (char*)first;
  char* a5 = (char*)last;
  Obj* a3 = owner;
  FUN_00b2c150(first, last, x, y, z);
  for (char* it = a5; it < a5; ) { }
  for (char* it = a4 + 4; it < a5; it += 4) {
    Obj* el = *(Obj**)it;
    Obj* beg = *(Obj**)a4;
    float* pe = el->pos();
    float de = (x - pe[0]) * (x - pe[0]) + (y - pe[1]) * (y - pe[1]) + (z - pe[2]) * (z - pe[2]);
    float* pb = beg->pos();
    float db = (x - pb[0]) * (x - pb[0]) + (y - pb[1]) * (y - pb[1]) + (z - pb[2]) * (z - pb[2]);
    if (db < de) {
      Obj* o = el;
      if (o) o->addref();
      Obj* old = *(Obj**)it;
      if (old != o) {
        if (old) old->addref();
        *(Obj**)it = old;
        if (o) o->release();
      }
      if (o) o->release();
      FUN_00b2b8a0(first, 0, (int)(it - a4) >> 2, 0, beg, x, y, z);
    }
  }
  FUN_00b2c1c0(first, last, x, y, z);
  if (a3) a3->release();
}

// ===========================================================================
// 0x00b2c830
// ===========================================================================
// @ 0x00b2c830
void S::FUN_00b2c830(void* a, int b)
{
  Big* self = (Big*)this;
  long long k = self->f110;
  Key ky;
  ky.lo = k;
  ky.hi = (int)(k >> 32);
  char out[8];
  FUN_00b2b6d0(out, &ky);
  void* it = *(void**)out;
  void* last = *(void**)(out + 4);
  int n = 0;
  while (it != last) {
    it = RBTreeIncrement(it);
    ++n;
  }
  if (n < g_1568cf0) {
    if (b != 0 || !(self->f238 & 1) || self->f108 == 0) {
      Sub* sub = (Sub*)((char*)self + 0x34);
      self->fa5 = 1;
      self->fa9 = 0;
      sub->call38(&g_167e0a0);
      if (sub->getac()) {
        unsigned* c = (unsigned*)((char*)sub->getac() + 4);
        *c &= ~1u;
        void* t = sub->getac();
        void** vt = *(void***)t;
        ((void(__thiscall*)(void*, int))vt[0x16c / 4])(t, 0);
      }
      void** vt = *(void***)self;
      ((void(__thiscall*)(void*))vt[0]) (self);
      long long k3 = self->f110;
      char key2[8];
      *(void**)key2 = self;
      ((void(__thiscall*)(void*))vt[0]) (self);
      ((void(__thiscall*)(void*, void*, void*, void*))0x00b2bf90)
          ((void*)((char*)this + 0x1c8), out, key2, &k3);
      ((void(__thiscall*)(void*))vt[1]) (self);
      ((void(__thiscall*)(void*))vt[1]) (self);
      return;
    }
  } else {
    void* nm = NounManager(self);
    ((void(__thiscall*)(void*, void*))0x00b225d0)(nm, self);
  }
}
