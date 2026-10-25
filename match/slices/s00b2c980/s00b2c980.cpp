// s00b2c980.cpp — SP::cAppModeTerrainEditor / cSPUILayoutManager region (unnamed in PDB)
// Reconstructed from Ghidra decompiles + disassembly. EASTL container internals are
// modelled with opaque structs and helper calls mapped to the original addresses.
//
// cl (this toolchain) rejects __thiscall on free functions, so every __thiscall entry
// point is declared as a member of `S` (methods keep the FUN_ names so run_all's
// substring match still finds them); the ignored register args of the original
// disappear naturally.

#include <stddef.h>

#define ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---- thiscall helper set (addresses in the comments) ------------------------
struct E {
  void  bf40(void** v);                          // 0x00b2bf40
  void  bfe0(void* pos, unsigned n, void* val);  // 0x00b2bfe0
  void  e25bd0(void* f, void* l);                // 0x00e25bd0
  void  c260(void* root);                        // 0x00b2c260
  void  c2a0(void* a, void* b);                  // 0x00b2c2a0
  void  c300(void* pos, void* val);              // 0x00b2c300
  void  aff0(void* e);                           // 0x00b2aff0
  void  b040(void* src);                         // 0x00b2b040
  void  a6f0(void* e);                           // 0x00b2a6f0
  void  a8d0(void* a, void* b);                  // 0x00b2a8d0
  void  f002a0(void);                            // 0x00b002a0
  void  listErase(void);                         // 0x0075f3f0
  void  nukeStr(void* root);                     // 0x009a9600
  void  b02430(void* out, void* key);            // 0x00b02430
  void  c830(void* a, void* b);                  // 0x00b2c830
  void  removeNoun();                            // 0x00b225d0
  void  gonzagoCtor(void);                       // 0x00b5b960
  void  gonzagoDtor(void);                       // 0x00b5b9a0
  void  f8fa10(int a, int b);                    // 0x00f8fa10
  void  f62d80(void);                            // 0x00f62d80
  void* b74e90(void* a, void* b, void* c);       // 0x00b74e90
  void  b74ef0(void* p);                         // 0x00b74ef0
};

// ---- cdecl / stdcall runtime helpers ---------------------------------------
extern "C" void* __cdecl EastlNew(unsigned int size, const char* name, int flags, int align, const char* file, int line); // 0x00f473a0
extern "C" void  __cdecl EastlDelete(void* p);                                             // 0x00f47380
extern "C" void* __cdecl EastlNewArray(void* p, int a, int size);                          // 0x011e073e
extern "C" void  __cdecl RemoveHandler(int, int, int, int, int);                           // 0x00571db0
extern "C" void  __cdecl RBTreeErase(void* node, void* anchor);                            // 0x00921880
extern "C" void* __cdecl RBTreeIncrement(void* node);                                      // 0x00921580
extern "C" void* __cdecl PropertyManager(void);                                            // 0x0067de30
extern "C" void* __cdecl EffectsManagerPtr(void);                                          // 0x0067ddd0
extern "C" void* __cdecl GetServer(void);                                                  // 0x00883860
extern "C" void  __cdecl GetPropertyAsKeyInstance(unsigned int key, void* obj, void* out); // 0x006a12a0
extern "C" void* __stdcall NounManager(void* noun);                                        // 0x00b3d300
extern "C" void* __cdecl FUN_00b3d3c0(void);                                               // 0x00b3d3c0
extern "C" void  __cdecl FUN_00b2ba70(void* first, void* last, void* dest);                // 0x00b2ba70
extern "C" void  __cdecl FUN_00b2b830(void* dst, void* last, void* first);                 // 0x00b2b830
extern "C" void* __cdecl FUN_00b2b7c0(void* src, void* pos, void* dst);                    // 0x00b2b7c0
extern "C" void  __cdecl FUN_00b2acd0(void* src, void* pos, void* dst);                    // 0x00b2acd0
extern "C" void  __cdecl FUN_00ff3810(void* obj, float a, float b);                        // 0x00ff3810

extern "C" int g_id_1568d3c;  // 0x01568d3c
extern "C" float g_f1471064;  // 0x01471064

// ---- virtual dispatch helpers ----------------------------------------------
struct RCObj { virtual void AddRef(); virtual void Release(); };
inline void AddRef(void* o) { if (o) ((RCObj*)o)->AddRef(); }
inline void Release(void* o) { if (o) ((RCObj*)o)->Release(); }
inline void* VFn(void* o, int byteoff) { return (*(void***)o)[byteoff / 4]; }
typedef void (__thiscall *TC_vi)(void*, void*, int);
typedef void (__thiscall *TC_vpii)(void*, void*, int, void*);
typedef void (__thiscall *TC_vff)(void*, void*, float, float);
typedef void (__thiscall *TC_vpi)(void*, unsigned int, void*);
typedef char (__thiscall *TC_cpvp)(void*, void*, unsigned int, void*);

struct RBNode { RBNode* pxRight; RBNode* pxLeft; RBNode* pxParent; int mColor; };

static void CopyBytes(void* dst, const void* src, unsigned n) {
  char* d = (char*)dst; const char* s = (const char*)src;
  for (unsigned i = 0; i < n; i++) d[i] = s[i];
}

struct S {
  void  FUN_00b2c980(void* obj, char flag);
  void  FUN_00b2ca30(unsigned n);
  void** FUN_00b2ca80(void** out, void* first, void* last);
  void  FUN_00b2cc40();
  void  FUN_00b2cd90();
  void  FUN_00b2d0f0();
  void* FUN_00b2d160(void* param);
  void  FUN_00b2d250(char* pos, char* value);
  void* FUN_00b2d480();
  void  FUN_00b2d660();
  void  FUN_00b2d7c0(unsigned a, unsigned b, void* param4);
  void  FUN_00b2d870(float* pos, float radius);
  void  FUN_00b2d910(void* noun);
  void  FUN_00b2da50();
};

// ---------------------------------------------------------------------------
// @ 0x00b2c980 — intrusive list push_front of a refcounted object
// ---------------------------------------------------------------------------
void S::FUN_00b2c980(void* obj, char flag) {
  char* base = (char*)this;
  if (flag) {
    AddRef(obj);
    void** node = (void**)EastlNew(0xc, "Simulator", 0, 0, ALLOC_H, 0xd1);
    node[2] = obj;
    AddRef(obj);
    node[0] = base + 0x170;
    node[1] = *(void**)(base + 0x174);
    *(void**)(base + 0x174) = node;
    *(void**)((char*)node[1]) = node;
    Release(obj);
  } else {
    void* o = obj;
    AddRef(o);
    ((E*)(base + 0x170))->bf40(&o);
    Release(o);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2ca30 — vector<ptr>::resize(n)
// ---------------------------------------------------------------------------
void S::FUN_00b2ca30(unsigned n) {
  int* begin = *(int**)this;
  int* end = *(int**)((char*)this + 4);
  if (n > (unsigned)(end - begin)) {
    int zero = 0;
    ((E*)this)->bfe0(end, n - (unsigned)(end - begin), &zero);
  } else {
    ((E*)this)->e25bd0(begin + n, end);
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2ca80 — rbtree::erase(first,last), iterator stored in *out
// ---------------------------------------------------------------------------
void** S::FUN_00b2ca80(void** out, void* first, void* last) {
  char* base = (char*)this;
  RBNode* anchor = (RBNode*)(base + 4);
  if (first == (void*)anchor->pxLeft && last == (void*)anchor) {
    ((E*)(base + 0x1c8))->c260((void*)anchor->pxParent);
    anchor->pxParent = 0;
    *(char*)(base + 0x10) = 0;
    *(int*)(base + 0x14) = 0;
    anchor->pxLeft = anchor;
    anchor->pxRight = anchor;
    *out = anchor;
    return out;
  }
  void* cur = first;
  if (first != last) {
    do {
      *(int*)(base + 0x14) -= 1;
      void* nxt = RBTreeIncrement(cur);
      RBTreeErase(cur, anchor);
      void* v = *(void**)((char*)cur + 0x18);
      if (v) Release(v);
      EastlDelete(cur);
      cur = nxt;
    } while (cur != last);
  }
  *out = cur;
  return out;
}

// ---------------------------------------------------------------------------
// @ 0x00b2cc40 — big object destructor
// ---------------------------------------------------------------------------
void S::FUN_00b2cc40() {
  char* base = (char*)this;
  *(int*)(base + 0x00) = 0x145fdf8;
  *(int*)(base + 0x04) = 0x145fda8;
  *(int*)(base + 0x08) = 0x145fda0;
  ((E*)(base + 0x1c8))->c260(*(void**)(base + 0x1d4));
  ((E*)(base + 0x1ac))->c260(*(void**)(base + 0x1b8));
  ((E*)(base + 0x190))->nukeStr(*(void**)(base + 0x19c));
  ((E*)(base + 0x17c))->f002a0();
  ((E*)(base + 0x170))->listErase();
  ((E*)(base + 0x15c))->a8d0(*(void**)(base + 0x15c), *(void**)(base + 0x160));
  void* p = *(void**)(base + 0x15c);
  if (p && *(int*)((char*)p - 4) != 0) EastlDelete(p);
  int h = *(int*)(base + 0x140);
  if (h) {
    *(int*)(base + 0x140) = 0;
    RemoveHandler(h, *(int*)(base + 0x144), *(int*)(base + 0x148), *(int*)(base + 0x14c), *(int*)(base + 0x150));
  }
  Release(*(void**)(base + 0x40));
  Release(*(void**)(base + 0x3c));
  ((E*)(base + 4))->gonzagoDtor();
  *(int*)(base + 0x00) = 0x13eb394;
}

// ---------------------------------------------------------------------------
// @ 0x00b2cd90 — rebuild the "world layout" vector from properties
// ---------------------------------------------------------------------------
void S::FUN_00b2cd90() {
  char* base = (char*)this;
  ((E*)(base + 0x17c))->c2a0(*(void**)(base + 0x17c), *(void**)(base + 0x180));

  int vec[3] = { 0, 0, 0 };
  void* pm = PropertyManager();
  ((TC_vpi)(*(void***)pm)[0x48 / 4])(pm, (unsigned int)g_id_1568d3c, vec);
  int count = (vec[1] - vec[0]) >> 2;
  char* vbegin = (char*)vec[0];
  void* cur = 0;
  for (int i = 0; i < count; i++) {
    pm = PropertyManager();
    if (cur) {
      void* c = cur;
      cur = 0;
      ((RCObj*)c)->Release();
    }
    void* obj = *(void**)(vbegin + i * 4);
    char ok = ((TC_cpvp)(*(void***)pm)[0x2c / 4])(pm, obj, (unsigned int)g_id_1568d3c, &cur);
    if (ok) {
      unsigned char elem[0x24];
      *(void**)(elem + 0x00) = (void*)0x145fd88;
      *(void**)(elem + 0x04) = 0;
      *(void**)(elem + 0x08) = 0;
      *(void**)(elem + 0x0c) = 0;
      *(float*)(elem + 0x10) = 0.0f;
      *(float*)(elem + 0x14) = 0.0f;
      *(float*)(elem + 0x18) = 0.0f;
      *(void**)(elem + 0x1c) = 0;
      *(void**)(elem + 0x20) = 0;

      if (cur) {
        void* tmp = 0;
        if (((TC_cpvp)(*(void***)cur)[0x24 / 4])(cur, 0, 0x254cf89u, &tmp)
            && *(unsigned short*)((char*)tmp + 0x12) == 0xd) {
          void* d = (*(unsigned char*)((char*)tmp + 0x10) & 0x30) ? *(void**)tmp : tmp;
          *(float*)(elem + 0x10) = *(float*)d;
        }
        if (cur) {
          if (((TC_cpvp)(*(void***)cur)[0x24 / 4])(cur, 0, 0x254cf8fu, &tmp)
              && *(unsigned short*)((char*)tmp + 0x12) == 0xd) {
            void* d = (*(unsigned char*)((char*)tmp + 0x10) & 0x30) ? *(void**)tmp : tmp;
            *(float*)(elem + 0x14) = *(float*)d;
          }
          if (cur) {
            if (((TC_cpvp)(*(void***)cur)[0x24 / 4])(cur, 0, 0x254cf97u, &tmp)
                && *(unsigned short*)((char*)tmp + 0x12) == 0xd) {
              void* d = (*(unsigned char*)((char*)tmp + 0x10) & 0x30) ? *(void**)tmp : tmp;
              *(float*)(elem + 0x18) = *(float*)d;
            }
          }
        }
        GetPropertyAsKeyInstance(0x279a9c8u, cur, elem + 0x1c);
        if (*(int*)(elem + 0x1c) == 0x2ebcd6a6) *(int*)(elem + 0x1c) = 0;

        {
          void* tmp = 0;
          if (cur && ((TC_cpvp)(*(void***)cur)[0x24 / 4])(cur, 0, 0x37575e5u, &tmp)
              && *(unsigned short*)((char*)tmp + 0x12) == 1) {
            void* d = (*(unsigned char*)((char*)tmp + 0x10) & 0x30) ? *(void**)tmp : tmp;
            if (*(unsigned char*)d != 0) *(unsigned int*)(elem + 0x20) |= 1u;
            else *(unsigned int*)(elem + 0x20) &= ~1u;
          } else {
            *(unsigned int*)(elem + 0x20) &= ~1u;
          }
        }
        {
          void* tmp = 0;
          if (cur && ((TC_cpvp)(*(void***)cur)[0x24 / 4])(cur, 0, 0x37575ebu, &tmp)
              && *(unsigned short*)((char*)tmp + 0x12) == 1) {
            void* d = (*(unsigned char*)((char*)tmp + 0x10) & 0x30) ? *(void**)tmp : tmp;
            if (*(unsigned char*)d != 0) *(unsigned int*)(elem + 0x20) |= 2u;
            else *(unsigned int*)(elem + 0x20) &= ~2u;
          } else {
            *(unsigned int*)(elem + 0x20) &= ~2u;
          }
        }

        GetPropertyAsKeyInstance(0xf9efbbu, cur, elem + 0x04);
        if (*(int*)(elem + 0x04) == 0x2ebcd6a6) *(int*)(elem + 0x04) = 0;
        GetPropertyAsKeyInstance(0xf9efbcu, cur, elem + 0x08);
        if (*(int*)(elem + 0x08) == 0x2ebcd6a6) *(int*)(elem + 0x08) = 0;
        GetPropertyAsKeyInstance(0xf9efbdu, cur, elem + 0x0c);
        if (*(int*)(elem + 0x0c) == 0x2ebcd6a6) *(int*)(elem + 0x0c) = 0;

        char* vend = *(char**)(base + 0x180);
        char* vcap = *(char**)(base + 0x184);
        if (vend < vcap) {
          *(char**)(base + 0x180) = vend + 0x24;
          *(void**)(vend + 0x00) = *(void**)(elem + 0x00);
          *(void**)(vend + 0x20) = 0;
          *(void**)(vend + 0x04) = *(void**)(elem + 0x04);
          *(void**)(vend + 0x08) = *(void**)(elem + 0x08);
          *(void**)(vend + 0x0c) = *(void**)(elem + 0x0c);
          *(float*)(vend + 0x10) = *(float*)(elem + 0x10);
          *(float*)(vend + 0x14) = *(float*)(elem + 0x14);
          *(float*)(vend + 0x18) = *(float*)(elem + 0x18);
          *(void**)(vend + 0x1c) = *(void**)(elem + 0x1c);
          *(void**)(vend + 0x20) = *(void**)(elem + 0x20);
        } else {
          ((E*)(base + 0x17c))->c300(vend, elem);
        }
      }
    }
  }
  if (cur) ((RCObj*)cur)->Release();
  if (vec[0] && *(int*)((char*)vec[0] - 4) != 0) EastlDelete((void*)vec[0]);
}

// ---------------------------------------------------------------------------
// @ 0x00b2d0f0 — remove all nouns registered in a map, then clear containers
// ---------------------------------------------------------------------------
void S::FUN_00b2d0f0() {
  char* base = (char*)this;
  RBNode* anchor = (RBNode*)(base + 0x1cc);
  for (void* n = *(void**)(base + 0x1d0); n != (void*)anchor; n = RBTreeIncrement(n)) {
    void* noun = *(void**)((char*)n + 0x18);
    if (noun) ((E*)NounManager(noun))->removeNoun();
  }
  ((E*)(base + 0x1c8))->c260(*(void**)(base + 0x1d4));
  anchor->pxLeft = anchor;
  anchor->pxRight = anchor;
  *(int*)(base + 0x1d4) = 0;
  *(char*)(base + 0x1d8) = 0;
  *(int*)(base + 0x1dc) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b2d160 — vector::pop_back returning the removed slot
// ---------------------------------------------------------------------------
void* S::FUN_00b2d160(void* param) {
  char* base = (char*)this;
  char* end = *(char**)(base + 4);
  if ((char*)param + 0x18 < end) {
    FUN_00b2b830((char*)param + 0x18, end, param);
  }
  *(char**)(base + 4) = end - 0x18;
  char* e = *(char**)(base + 4);
  *(int*)e = -1;
  *(int*)(e + 8) = 0;
  *(int*)(e + 0xc) = 0;
  void* p = *(void**)(e + 0x10);
  if (p) {
    *(void**)(e + 0x10) = 0;
    Release(p);
  }
  void* q = *(void**)(e + 0x10);
  if (q) Release(q);
  return param;
}

// ---------------------------------------------------------------------------
// @ 0x00b2d250 — vector::insert(pos, value) (0x18-byte elements)
// ---------------------------------------------------------------------------
void S::FUN_00b2d250(char* pos, char* value) {
  char* base = (char*)this;
  char* end = *(char**)(base + 4);
  char* cap = *(char**)(base + 8);
  if (end != cap) {
    char* v = value;
    if (pos <= value && value < end) v = value + 0x18;
    if (end) ((E*)end)->aff0(end - 0x18);
    FUN_00b2ba70(pos, end - 0x18, end);
    ((E*)pos)->b040(v);
    *(char**)(base + 4) += 0x18;
    return;
  }
  char* begin = *(char**)(base + 0);
  int n = (int)((end - begin) / 0x18);
  int newcap;
  char* buf;
  if (n == 0) {
    newcap = 1;
  } else {
    newcap = n * 2;
    if (newcap == 0) { buf = 0; goto have; }
  }
  buf = (char*)EastlNew(newcap * 0x18, "Simulator", 0, 0, ALLOC_H, 0xd1);
have:
  char* p1 = (char*)FUN_00b2b7c0(begin, pos, buf);
  FUN_00b2acd0(begin, pos, buf);
  if (p1) ((E*)p1)->aff0(value);
  char* endp = *(char**)(base + 4);
  char* p2 = (char*)FUN_00b2b7c0(pos, endp, p1 + 0x18);
  FUN_00b2acd0(pos, endp, p1 + 0x18);
  if (begin && *(int*)(begin - 4) != 0) EastlDelete(begin);
  *(char**)(base + 4) = p2;
  *(char**)(base + 0) = buf;
  *(char**)(base + 8) = buf + newcap * 0x18;
}

// ---------------------------------------------------------------------------
// @ 0x00b2d480 — big object constructor
// ---------------------------------------------------------------------------
void* S::FUN_00b2d480() {
  char* base = (char*)this;
  *(void**)(base + 0x00) = (void*)0x13eb384;
  ((E*)(base + 4))->gonzagoCtor();
  *(void**)(base + 0x00) = (void*)0x145fdf8;
  *(void**)(base + 0x04) = (void*)0x145fda8;
  *(void**)(base + 0x08) = (void*)0x145fda0;

  *(void**)(base + 0x20) = 0;
  *(void**)(base + 0x28) = 0;
  *(void**)(base + 0x2c) = 0;
  *(void**)(base + 0x30) = 0;
  *(unsigned char*)(base + 0x34) = 0;
  *(void**)(base + 0x38) = 0;
  *(float*)(base + 0x24) = 0.0f;
  *(void**)(base + 0x3c) = 0;
  *(void**)(base + 0x40) = 0;

  int* p = (int*)(base + 0x44);
  p[0] = 0; p[1] = 0; p[2] = 0;
  p[7] = 0; p[8] = 0; p[9] = 0;
  p[0xe] = 0; p[0xf] = 0; p[0x10] = 0;
  p[0x15] = 0; p[0x16] = 0; p[0x17] = 0;
  p[0x1c] = 0; p[0x1d] = 0; p[0x1e] = 0;
  p[0x23] = 0; p[0x24] = 0; p[0x25] = 0;
  p[0x2a] = 0; p[0x2b] = 0; p[0x2c] = 0;
  p[0x31] = 0; p[0x32] = 0; p[0x33] = 0;
  p[0x38] = 0; p[0x39] = 0; p[0x3a] = 0;

  *(void**)(base + 0x140) = 0;
  *(void**)(base + 0x144) = 0;
  *(void**)(base + 0x148) = 0;
  *(void**)(base + 0x14c) = 0;
  *(void**)(base + 0x150) = 0;
  *(void**)(base + 0x154) = (void*)5;
  *(void**)(base + 0x158) = (void*)0xffffffff;
  *(void**)(base + 0x15c) = 0;
  *(void**)(base + 0x160) = 0;
  *(void**)(base + 0x164) = 0;

  void* list = (void*)(base + 0x170);
  *(void**)(base + 0x170) = list;
  *(void**)(base + 0x174) = list;
  *(void**)(base + 0x17c) = 0;
  *(void**)(base + 0x180) = 0;
  *(void**)(base + 0x184) = 0;

  *(void**)(base + 0x198) = 0;
  *(void**)(base + 0x19c) = 0;
  *(void**)(base + 0x1a0) = 0;
  void* t1 = (void*)(base + 0x194);
  *(void**)(base + 0x194) = t1;
  *(void**)(base + 0x198) = t1;
  *(void**)(base + 0x19c) = 0;
  *(unsigned char*)(base + 0x1a0) = 0;
  *(void**)(base + 0x1a4) = 0;

  void* t2 = (void*)(base + 0x1b0);
  *(void**)(base + 0x1b4) = 0;
  *(void**)(base + 0x1b8) = 0;
  *(void**)(base + 0x1bc) = 0;
  *(void**)(base + 0x1b0) = t2;
  *(void**)(base + 0x1b4) = t2;
  *(void**)(base + 0x1b8) = 0;
  *(unsigned char*)(base + 0x1bc) = 0;
  *(void**)(base + 0x1c0) = 0;

  void* t3 = (void*)(base + 0x1cc);
  *(void**)(base + 0x1d0) = 0;
  *(void**)(base + 0x1d4) = 0;
  *(void**)(base + 0x1d8) = 0;
  EastlNewArray(base + 0x44, 0, 0xfc);
  *(void**)(base + 0x1cc) = t3;
  *(void**)(base + 0x1d0) = t3;
  *(void**)(base + 0x1d4) = 0;
  *(unsigned char*)(base + 0x1d8) = 0;
  *(void**)(base + 0x1dc) = 0;

  return base;
}

// ---------------------------------------------------------------------------
// @ 0x00b2d660 — create sub-systems (cAppModeTerrainEditor::Activate)
// ---------------------------------------------------------------------------
void S::FUN_00b2d660() {
  char* base = (char*)this;
  void* p1 = EastlNew(0x24, "Simulator", 0, 0, 0, 0);
  if (p1) { ((E*)p1)->f8fa10(0x80, 0); *(void**)p1 = (void*)0x145fd5c; }
  else p1 = 0;
  *(void**)(base + 0x38) = p1;

  void* p2 = EastlNew(0x38, "Simulator", 0, 0, 0, 0);
  if (p2) {
    ((TC_vff)FUN_00ff3810)(p2, *(void**)(base + 0x38), 1.0f, 0.0f);
    float f = g_f1471064;
    *(void**)p2 = (void*)0x145fd2c;
    *(void**)((char*)p2 + 4) = (void*)0x145fd28;
    *(float*)((char*)p2 + 0x34) = f;
  }
  else p2 = 0;
  void* old2 = *(void**)(base + 0x3c);
  if (p2 != old2) {
    if (p2) AddRef(p2);
    *(void**)(base + 0x3c) = p2;
    if (old2) Release(old2);
  }
  {
    void* fx = EffectsManagerPtr();
    ((TC_vpii)(*(void***)fx)[0x88 / 4])(fx, (void*)0x107ae878, 0, *(void**)(base + 0x3c));
  }
  void* p3 = EastlNew(0x380, "Simulator", 0, 0, 0, 0);
  if (p3) {
    ((E*)p3)->f62d80();
    *(void**)p3 = (void*)0x145fd90;
    *(void**)((char*)p3 + 4) = (void*)0x145fd8c;
    EastlNewArray((char*)p3 + 0x2c0, 0, 0xc0);
    *(void**)((char*)p3 + 0x250) = (char*)p3 + 0x2c0;
    *(void**)((char*)p3 + 0x254) = (void*)4;
  }
  else p3 = 0;
  void* old3 = *(void**)(base + 0x40);
  if (p3 != old3) {
    if (p3) AddRef(p3);
    *(void**)(base + 0x40) = p3;
    if (old3) Release(old3);
  }
  ((S*)base)->FUN_00b2cd90();
}

// ---------------------------------------------------------------------------
// @ 0x00b2d7c0 — erase a keyed range from a map, optionally clearing nouns
// ---------------------------------------------------------------------------
void S::FUN_00b2d7c0(unsigned a, unsigned b, void* param4) {
  char* base = (char*)this;
  int all = ((a & b) == 0xffffffffu);
  void* first;
  void* last;
  if (all) {
    RBNode* anchor = (RBNode*)(base + 0x1b0);
    first = *(void**)(base + 0x1b4);
    last = anchor;
  } else {
    char tmp[8];
    unsigned pair[2];
    pair[0] = a; pair[1] = b;
    ((E*)(base + 0x1ac))->b02430(tmp, pair);
    first = *(void**)(tmp);
    last = *(void**)(tmp + 4);
  }
  void* n = first;
  while (n != last) {
    void* v = *(void**)((char*)n + 0x18);
    if (v) ((E*)this)->c830(v, param4);
    n = RBTreeIncrement(n);
  }
  ((S*)(base + 0x1ac))->FUN_00b2ca80(&param4, first, last);
  if (all) ((S*)this)->FUN_00b2d0f0();
}

// ---------------------------------------------------------------------------
// @ 0x00b2d870 — drop vector entries near a position within a radius
// ---------------------------------------------------------------------------
void S::FUN_00b2d870(float* pos, float radius) {
  char* base = (char*)this;
  char* end = *(char**)(base + 0x160);
  char* e = *(char**)(base + 0x15c);
  while (e != end) {
    void* sub = *(void**)(e + 0x10);
    if (sub) {
      void* inner = *(void**)((char*)sub + 0x34);
      float* p = (float*)((void*(__fastcall*)(void*, int))VFn(inner, 0x2c))(inner, 0);
      float dx = pos[0] - p[0];
      float dy = pos[1] - p[1];
      float dz = pos[2] - p[2];
      if (!(radius < dx * dx + dy * dy + dz * dz)) {
        ((E*)this)->a6f0(e);
        e = (char*)((S*)(base + 0x15c))->FUN_00b2d160(e);
      }
    }
    e += 0x18;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2d910 — find a vector entry by noun id and remove it
// ---------------------------------------------------------------------------
void S::FUN_00b2d910(void* noun) {
  char* base = (char*)this;
  char* listbase = base + 0x15c;
  char* end = *(char**)(base + 0x160);
  char* e = *(char**)(base + 0x15c);
  while (e != end) {
    if (*(void**)(e + 0x10) == noun) {
      void* x = FUN_00b3d3c0();
      void* r = ((E*)x)->b74e90(*(void**)(e + 8), *(void**)(e + 0xc), *(void**)(e));
      if (r) ((E*)x)->b74ef0(r);
      void* obj = *(void**)(e + 0x10);
      if (obj) {
        ((E*)NounManager(obj))->removeNoun();
        void* o = *(void**)(e + 0x10);
        if (o) { *(void**)(e + 0x10) = 0; Release(o); }
      }
      ((S*)listbase)->FUN_00b2d160(e);
      return;
    }
    e += 0x18;
  }
}

// ---------------------------------------------------------------------------
// @ 0x00b2da50 — register the message handler then activate
// ---------------------------------------------------------------------------
void S::FUN_00b2da50() {
  char* base = (char*)this;
  void* server = GetServer();
  char* handler = base - 4;
  *(void**)(base + 0x13c) = server;
  *(void**)(base + 0x140) = handler;
  *(void**)(base + 0x144) = (void*)0x145fe38;
  *(int*)(base + 0x148) = 5;
  *(int*)(base + 0x14c) = 0;
  if (server && handler) {
    for (unsigned off = 0; off < 0x14; off += 4) {
      int key = *(int*)(0x145fe38 + off);
      ((TC_vi)(*(void***)server)[9])(server, handler, key);
    }
  }
  ((S*)handler)->FUN_00b2d660();
}
