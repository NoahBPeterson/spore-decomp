// Slice s00ba2590 — Simulator species-relationship / PlayerPlanetData helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int); // 0xf473a0
void  __cdecl operator_delete__(void*);                    // 0xf47380
void* __cdecl EA_Messaging_GetServer();                    // 0x883860
void* __cdecl SP_PropertyManager();                        // 0x67de30
void  __cdecl EA_IO_WriteUint32(void*, void*, int, int);   // 0x93aa70
void  __cdecl EA_IO_ReadInt32(void*, void*, int, int);     // 0x93a780
int   __cdecl FUN_00c0b8e0(void*, void*);                  // 0xc0b8e0
bool  __cdecl FUN_00c0b780(void*);                         // 0xc0b780
bool  __cdecl FUN_00c0b7a0(void*);                         // 0xc0b7a0
void  __cdecl FUN_00ae2e40();                              // 0xae2e40
void  __cdecl FUN_00ae2ed0();                              // 0xae2ed0
void  __cdecl FUN_00695b40(void*, void*, const wchar_t*);  // 0x695b40
void  __cdecl FUN_00921440(void*, int, int, int);          // 0x921440
void  __cdecl FUN_00ba2980(int, int);                      // 0xba2980
void  __cdecl FUN_00ba29d0(int);                           // 0xba29d0
void* __cdecl FUN_00bc3e60(unsigned, int, int);            // 0xbc3e60
void  __cdecl FUN_00ac4440(void*, void*, void*);           // 0xac4440

struct CGZSub { void __thiscall Dtor(); };
struct CGZTimer { void __thiscall Dtor(); };

static inline void Release(void* p) { if (p) (*(void(__thiscall*)(void*))((*(void***)p)[1]))(p); }

extern int g_156c198;   // 0x156c198
extern int g_156c194;   // 0x156c194
extern uint32_t g_156c188, g_156c18c, g_156c190;

// ---- all thiscall entry points as methods of a thin wrapper ------------
struct W {
  void __thiscall Run_00ba2590(void* obj);
  void __thiscall Run_00ba2670(void* p);
  void __thiscall Run_00ba2750();
  void __thiscall Run_00ba2ca0(void* p2);
  char __thiscall Run_00ba2d80(void* p2);
  void __thiscall Run_00ba2f20();
  void* __thiscall Run_00ba2f90();
  void __thiscall Run_00ba3010();
  void* __thiscall Run_00ba30c0(void* out, uint32_t* key);
  void* __thiscall Run_00ba31d0(void* out, void* node, void** head);
  void __thiscall Run_00ba3310();
  void __thiscall Run_00ba3350();
  void* __thiscall Run_00ba3550(void* src);
  void* __thiscall Run_00ba3620(void* src);
  void __thiscall Run_00ba37a0();
  void __thiscall Run_00ba2e50(int lo, int hi, uint32_t* key);
};

// @ 0x00ba2590  intrusive list insert
void __thiscall W::Run_00ba2590(void* obj) {
  void* self = this;
  if (obj) (*(void(__thiscall*)(void*))((*(void***)obj)[1]))(obj);
  void* node = operator_new(0xc, "Simulator", 0, 0,
     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  void* head = (char*)self + 0x34;
  *(void**)((char*)node + 8) = obj;
  if (obj) (*(void(__thiscall*)(void*))((*(void***)obj)[1]))(obj);
  *(void**)node = head;
  *(void**)((char*)node + 4) = *(void**)((char*)head + 4);
  **(void***)((char*)head + 4) = node;
  *(void**)((char*)head + 4) = node;
  if (obj) (*(void(__thiscall*)(void*))((*(void***)obj)[2]))(obj);
  *(uint8_t*)((char*)obj + 0xe) = 1;
}

// @ 0x00ba2670
void __thiscall W::Run_00ba2670(void* p) {
  uint32_t v = 0xf2dcc8bc;
  void* io = (*(void*(__thiscall*)(void*))((*(void***)p)[0x20 / 4]))(p);
  void* wr = (*(void*(__thiscall*)(void*))((*(void***)io)[0x18 / 4]))(io);
  EA_IO_WriteUint32(wr, &v, 1, 0);
  char buf[0xa14];
  (*(void(__thiscall*)(void*, void*, int, int))((void*)0))(&buf, (char*)this - 4, 0x156c370, 0x1a80d26);
  (*(void(__thiscall*)(void*, void*))((void*)0))(&buf, p);
}

// @ 0x00ba2750
void __thiscall W::Run_00ba2750() {
  void* srv = EA_Messaging_GetServer();
  (*(void(__thiscall*)(void*, void*, int, int))((*(void***)srv)[0x2c / 4]))(srv, (char*)this - 4, 0xf62def, 0xffffd8f1);
}

// @ 0x00ba27b0
int __cdecl FUN_00ba27b0(void* a, void* b) {
  int s = FUN_00c0b8e0(a, b);
  int v;
  if (s < g_156c198) v = (s >= g_156c194) ? 1 : 0;
  else v = 2;
  if (*(int*)((char*)a + 0xb20) == *(int*)((char*)b + 0xb20)) return 6;
  if (FUN_00c0b780(a) && v >= 1) return 2;
  if (FUN_00c0b780(a)) {
    if (FUN_00c0b780(a) && v < 1) return 1;
    if (FUN_00c0b7a0(a) && v < 2) return 1;
  }
  if (FUN_00c0b780(a) && FUN_00c0b7a0(a) && v < 1) return 3;
  if (FUN_00c0b7a0(a) && FUN_00c0b780(a) && v > 1) return 3;
  return 4;
}

// @ 0x00ba28a0
struct RelCell { char pad00[0x4a8]; int f4a8; int f4ac; int f4c8; void* f4cc; void* f4d0; };
char __cdecl FUN_00ba28a0(void* mgr, int idx, void* other) {
  if (mgr == 0) return 0;
  RelCell* c = (RelCell*)((char*)*(void**)((char*)mgr + 0x70) + idx * 0x4e0);
  int state = c->f4a8;
  if (other != 0 && ((*(uint32_t*)((char*)other + 0xb58) >> 8) & 1)) state = 2;
  switch (state) {
    case 1:
      if (c->f4c8 == 0) return (c->f4ac - 1 < 1) ? 3 : 5;
      {
        int n = (int)(((char*)c->f4d0 - (char*)c->f4cc) >> 5);
        if (n > 0) {
          int32_t* p = (int32_t*)((char*)c->f4cc + 0xc);
          for (int i = 0; i < n; ++i) { if (*p == 0xb) return 3; p += 8; }
          return 5;
        }
      }
      return 5;
    case 2: return (c->f4ac != 3 || c->f4c8 != 0) ? 6 : 5;
    case 3: case 4: case 5: return 5;
    default: return 0;
  }
}

// @ 0x00ba2a80
void* __stdcall FUN_00ba2a80(void** src) {
  void* n = operator_new(0xc, "Simulator", 0, 0,
     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  if (n) {
    void* o = *src;
    *(void**)n = o;
    if (o) (*(void(__thiscall*)(void*))((*(void***)o)[0]))(o);
    *(void**)((char*)n + 4) = src[1];
  }
  *(void**)((char*)n + 8) = 0;
  return n;
}

// @ 0x00ba2af0  ReloadTuning
void __cdecl FUN_00ba2af0() {
  void* local = 0;
  void* pm = SP_PropertyManager();
  (*(bool(__thiscall*)(void*, int, int, void**))((*(void***)pm)[0x2c / 4]))(pm, 0x48f5d7cd, 0xad56080c, &local);
  if (local) Release(local);
}

// @ 0x00ba2c70
uint8_t __stdcall FUN_00ba2c70(int key, void* p) {
  if (key == 0xf62def && *(int*)((char*)p + 0x10) == (int)0xad56080c &&
      *(int*)((char*)p + 0x18) == 0x48f5d7cd)
    FUN_00ba2af0();
  return 0;
}

// @ 0x00ba2ca0
void __thiscall W::Run_00ba2ca0(void* p2) {
  uint32_t v = *(uint32_t*)((char*)p2 + 0xc);
  void* io = (*(void*(__thiscall*)(void*))((*(void***)this)[0x20 / 4]))(this);
  void* wr = (*(void*(__thiscall*)(void*))((*(void***)io)[0x18 / 4]))(io);
  EA_IO_WriteUint32(wr, &v, 1, 0);
  (*(void(__thiscall*)(void*))((*(void***)this)[0x1c / 4]))(this);
}

// @ 0x00ba2d80
char __thiscall W::Run_00ba2d80(void* p2) { (void)p2; return 1; }

// @ 0x00ba2e00
void __cdecl FUN_00ba2e00(void* arr, unsigned n) {
  unsigned i = 0;
  if (n != 0) {
    do {
      void* p = *((void**)arr + i);
      while (p != 0) {
        void* next = *(void**)((char*)p + 8);
        if (*(void**)p) Release(*(void**)p);
        operator_delete__(p);
        p = next;
      }
      *((void**)arr + i) = 0;
      ++i;
    } while (i < n);
  }
}

// @ 0x00ba2e50
void __thiscall W::Run_00ba2e50(int lo, int hi, uint32_t* key) {
  int n = (hi - lo) >> 4;
  int left = n;
  if (left > 0) {
    do {
      int mid = left >> 1;
      uint32_t* e = (uint32_t*)(mid * 0x10 + lo);
      bool less;
      if (e[0] == key[0]) less = e[2] < key[2] ? true : (e[2] == key[2] ? (e[1] < key[1]) : false);
      else less = e[0] < key[0];
      if (less) { lo = (int)e + 0x10; mid = left + (-1 - mid); }
      left = mid;
    } while (left > 0);
  }
}

// @ 0x00ba2f20
struct PPD { char pad00[0x70]; void* f68; char pad[0x24]; };
void __thiscall W::Run_00ba2f20() {
  char* s = (char*)this;
  *(void**)s = (void*)0x1465dc8;
  ((CGZTimer*)(s + 0x80))->Dtor();
  if (*(void**)(s + 0x68)) operator_delete__(*(void**)(s + 0x68));
  if (*(void**)(s + 0x50)) operator_delete__(*(void**)(s + 0x50));
  if (*(void**)(s + 0x38)) operator_delete__(*(void**)(s + 0x38));
  if (*(void**)(s + 0x20)) operator_delete__(*(void**)(s + 0x20));
  if (*(void**)(s + 0x08)) operator_delete__(*(void**)(s + 0x08));
}

// @ 0x00ba2f90
void* __thiscall W::Run_00ba2f90() {
  char* s = (char*)this;
  *(void**)s = (void*)0x1465d64;
  for (int off = 0x08; off <= 0x70; off += 0x18) {
    *(void**)(s + off) = 0; *(void**)(s + off + 4) = 0; *(void**)(s + off + 8) = 0;
  }
  *(void**)(s + 0x68) = 0; *(void**)(s + 0x6c) = 0; *(void**)(s + 0x70) = 0;
  ((CGZTimer*)(s + 0x80))->Dtor();
  uint8_t v = 0xff;
  *(uint8_t*)(s + 0xa0) = v; *(uint8_t*)(s + 0xa1) = v; *(uint8_t*)(s + 0xa2) = 0;
  return s;
}

// @ 0x00ba3010
void __thiscall W::Run_00ba3010() {
  FUN_00ba2af0();
  void* srv = EA_Messaging_GetServer();
  (*(void(__thiscall*)(void*, void*, int))((*(void***)srv)[0x20 / 4]))(srv, (char*)this - 4, 0xf62def);
}

// @ 0x00ba30c0
struct HashNode { int key[3]; char pad[0x14]; HashNode* next; };
struct HashSet { int pad0; HashNode** buckets; unsigned mask; int count; };
void* __thiscall W::Run_00ba30c0(void* out, uint32_t* key) {
  HashSet* self = (HashSet*)this;
  uint32_t h = key[0] ^ key[2];
  unsigned b = h % self->mask;
  HashNode* n = self->buckets[b];
  while (n) {
    if (n->key[0] == (int)key[0] && n->key[1] == (int)key[1] && n->key[2] == (int)key[2]) {
      *(void**)out = n; *(void**)((char*)out + 4) = &self->buckets[b]; *(char*)((char*)out + 8) = 0;
      return out;
    }
    n = n->next;
  }
  n = (HashNode*)operator_new(0x24, "Simulator", 0, 0,
     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  for (int i = 0; i < 8; ++i) n->key[i] = (int)key[i];
  n->next = self->buckets[b];
  self->buckets[b] = n;
  ++self->count;
  *(void**)out = n; *(void**)((char*)out + 4) = &self->buckets[b]; *(char*)((char*)out + 8) = 1;
  return out;
}

// @ 0x00ba31d0
void* __thiscall W::Run_00ba31d0(void* out, void* nodev, void** head) {
  HashSet* self = (HashSet*)this;
  HashNode* node = (HashNode*)nodev;
  HashNode* prev = (HashNode*)*head;
  *(void**)((char*)out + 4) = head;
  *(void**)out = node->next;
  if (prev == node) *head = node->next;
  else { HashNode* p = prev->next; while (p != node) { prev = p; p = p->next; } prev->next = p->next; }
  if (*(void**)node) Release(*(void**)node);
  operator_delete__(node);
  --self->count;
  return out;
}

// @ 0x00ba3310
void __thiscall W::Run_00ba3310() {
  char* s = (char*)this;
  FUN_00ba2980(*(int*)(s + 0x24), *(int*)(s + 0x28));
  *(int*)(s + 0x2c) = 0;
  FUN_00ba2e00(*(void**)(s + 0x44), *(unsigned*)(s + 0x48));
  *(int*)(s + 0x4c) = 0;
}

// @ 0x00ba3350
void __thiscall W::Run_00ba3350() { }

// @ 0x00ba33e0
void __cdecl FUN_00ba33e0(void* p1, void* p2) {
  FUN_00ba2980(*(int*)((char*)p2 + 4), *(int*)((char*)p2 + 8));
  *(int*)((char*)p2 + 0xc) = 0;
  uint32_t count = 0;
  void* io = (*(void*(__thiscall*)(void*))((*(void***)p1)[0x20 / 4]))(p1);
  void* rd = (*(void*(__thiscall*)(void*))((*(void***)io)[0x18 / 4]))(io);
  EA_IO_ReadInt32(rd, &count, 1, 0);
}

// @ 0x00ba3550
void* __thiscall W::Run_00ba3550(void* src) {
  if (src == this) return this;
  char* sb = *(char**)src; char* se = *((char**)src + 1);
  unsigned n = (unsigned)((se - sb) >> 4);
  char* db = *(char**)this;
  unsigned cap = (unsigned)((*((char**)this + 2) - db) >> 4);
  if (cap < n) {
    char* nb = (char*)FUN_00bc3e60(n, (int)sb, (int)se);
    if (db) operator_delete__(db);
    *(char**)this = nb; *((char**)this + 1) = nb + n * 0x10; *((char**)this + 2) = nb + n * 0x10;
    return this;
  }
  unsigned have = (unsigned)((*((char**)this + 1) - db) >> 4);
  if (have < n) { FUN_00ac4440(sb, sb + have * 0x10, db); *((char**)this + 1) = db + n * 0x10; return this; }
  FUN_00ac4440(sb, se, db);
  *((char**)this + 1) = db + n * 0x10;
  return this;
}

// @ 0x00ba3620
void* __thiscall W::Run_00ba3620(void* src) {
  if (src == this) return this;
  char* sb = *(char**)src; char* se = *((char**)src + 1);
  unsigned n = (unsigned)((se - sb) >> 3);
  char* db = *(char**)this;
  unsigned cap = (unsigned)((*((char**)this + 2) - db) >> 3);
  if (cap < n) {
    if (db) operator_delete__(db);
    char* nb = 0;
    *(char**)this = nb; *((char**)this + 1) = nb + n * 8; *((char**)this + 2) = nb + n * 8;
    return this;
  }
  unsigned have = (unsigned)((*((char**)this + 1) - db) >> 3);
  if (have < n) { FUN_00ac4440(sb, sb + have * 8, db); *((char**)this + 1) = db + n * 8; return this; }
  FUN_00ac4440(sb, se, db);
  *((char**)this + 1) = db + n * 8;
  return this;
}

// @ 0x00ba36f0
int __cdecl FUN_00ba36f0(void* buf, int end, int ret) {
  char* p = (char*)buf;
  if ((int)buf != end) {
    do {
      *(void**)(p + 0x08) = (void*)0x1465dc8;
      ((CGZTimer*)(p + 0x90))->Dtor();
      if (*(void**)(p + 0x70)) operator_delete__(*(void**)(p + 0x70));
      if (*(void**)(p + 0x58)) operator_delete__(*(void**)(p + 0x58));
      if (*(void**)(p + 0x40)) operator_delete__(*(void**)(p + 0x40));
      if (*(void**)(p + 0x28)) operator_delete__(*(void**)(p + 0x28));
      if (*(void**)(p + 0x10)) operator_delete__(*(void**)(p + 0x10));
      p += 0xb0;
    } while ((int)p != end);
  }
  return ret;
}

// @ 0x00ba37a0
void __thiscall W::Run_00ba37a0() {
  char* s = (char*)this;
  *(void**)s = (void*)0x1465dc8;
  *(void**)(s + 4) = (void*)0x1465d78;
  *(void**)(s + 8) = (void*)0x1465d70;
  FUN_00ba2e00(*(void**)(s + 0x44), *(unsigned*)(s + 0x48));
  *(int*)(s + 0x4c) = 0;
  if (*(unsigned*)(s + 0x48) > 1) operator_delete__(*(void**)(s + 0x44));
  FUN_00ba2980(*(int*)(s + 0x24), *(int*)(s + 0x28));
  *(int*)(s + 0x2c) = 0;
  if (*(unsigned*)(s + 0x28) > 1) operator_delete__(*(void**)(s + 0x24));
  ((CGZSub*)(s + 4))->Dtor();
  *(void**)s = (void*)0x1465dc8;
}
