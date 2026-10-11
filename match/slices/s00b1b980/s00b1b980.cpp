// Slice s00b1b980: the cStateMachineHost region (state-machine host + its EASTL rbtree map
// instances map<string,int>, map<int,string>, map<int, vector<Elem38>>, the class ctor/dtor and
// the transition-script setup helper).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);  // 0x00f473a0
void operator delete[](void* p);   // 0x00f47380
void operator delete(void* p);     // 0x00f47380
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" unsigned __cdecl strlen(const char*);
#pragma intrinsic(memcpy)
#pragma intrinsic(strlen)

#define EASTL_ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define SPORE_ALLOC(n) operator new((n), "Simulator", 0, 0, EASTL_ALLOC_FILE, 0xd1)

inline void* operator new(unsigned int, void* p) { return p; }
extern char gEmptyString[];  // 0x01667bac

// ------------------------------------------------------------------ basic_string<char>
struct string8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  __declspec(nothrow) string8() {
    mpBegin = gEmptyString;
    mpEnd = gEmptyString;
    mpCapacity = gEmptyString + 1;
  }
  string8(const char* b, const char* e) {
    unsigned n = (unsigned)(e - b);
    unsigned cap = n + 1;
    if (cap > 1) {
      mpBegin = (char*)SPORE_ALLOC(cap);
      mpCapacity = mpBegin + cap;
    } else {
      mpBegin = gEmptyString;
      mpCapacity = gEmptyString + 1;
    }
    mpEnd = mpBegin;
    memcpy(mpBegin, b, n);
    mpEnd = mpBegin + n;
    *mpEnd = 0;
  }
  ~string8() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin) delete[] mpBegin;
  }
  string8& assign(const char* b, const char* e);  // 0x00454cb0
};

// ------------------------------------------------------------------ Elem38 / vector
struct Elem38 {
  string8 name;
  char rest[0x38 - sizeof(string8)];
  Elem38();
  Elem38(const Elem38& o);                 // 0x00b1a0f0
  Elem38& operator=(const Elem38& o);      // 0x00b19d40
};

struct Elem38Vector {
  Elem38* mpBegin;
  Elem38* mpEnd;
  Elem38* mpCapacity;
  Elem38Vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  void Destruct(Elem38* first, Elem38* last);  // 0x00b1a190
  Elem38Vector(const Elem38Vector& x);         // 0x00b1a350
  Elem38Vector& operator=(const Elem38Vector& x);  // 0x00b1a7b0
  void DoInsertValue(Elem38* position, const Elem38& value);  // 0x00b1a900
};

// ------------------------------------------------------------------ rbtree node plumbing
struct RBNodeBase {
  RBNodeBase* mpNodeRight;   // +0
  RBNodeBase* mpNodeLeft;    // +4
  RBNodeBase* mpNodeParent;  // +8
  char mColor;               // +0xc
};

struct IntStrNode : RBNodeBase {   // map<int,string> node, size 0x24
  int first;                       // +0x10
  string8 second;                  // +0x14
};
struct StrIntNode : RBNodeBase {   // map<string,int> node, size 0x24
  string8 first;                   // +0x10
  int second;                      // +0x20
};
struct IntVecNode : RBNodeBase {   // map<int, vector<Elem38>> node, size 0x28
  int first;                       // +0x10
  Elem38Vector second;             // +0x14
};

struct Iter { RBNodeBase* mpNode; };
struct InsertResult { RBNodeBase* first; bool second; };

extern bool StringLess(const string8* a, const string8* b);       // 0x00812210 (operator<)
extern RBNodeBase* RBTreeIncrement(RBNodeBase* p);                // 0x00921580

// ---- map<int,string>
struct IntStrPair { int first; string8 second; };
struct IntStrMap {
  char pad[4];
  RBNodeBase mAnchor;  // +4
  unsigned mnSize;     // +0x14
  __declspec(noinline) string8* Index(const int& key);                    // 0x00b1ba90
  string8* operator[](const int& key) { return Index(key); }
  void DoInsert(Iter* out, IntStrNode* hint, IntStrPair* value, bool forceLeft);  // 0x00b1ad00
};
void __cdecl MakeIntStrPair(IntStrPair* out, const int* key, const string8* def);  // 0x00b209f0

// ---- map<string,int>
struct StrIntPair { const string8* first; int second; };
struct StrIntMap {
  char pad[4];
  RBNodeBase mAnchor;  // +4
  unsigned mnSize;     // +0x14
  __declspec(noinline) Iter* insert(Iter* out, RBNodeBase* hint, const void* value);  // 0x00b1b980
  __declspec(noinline) int* Index(const string8& key);                                // 0x00b1c220
  int* operator[](const string8& key) { return Index(key); }
  void DoInsertValueImpl(Iter* out, RBNodeBase* parent, const void* value, bool forceLeft);  // 0x00b1a600
  InsertResult insertSimple(const void* value, int unused);                       // 0x00b1aba0
};

// ---- map<int, vector<Elem38>>
struct IntVecPair { int first; Elem38Vector second; };
struct IntVecMap {
  char pad[4];
  RBNodeBase mAnchor;  // +4
  unsigned mnSize;     // +0x14
  __declspec(noinline) Elem38Vector* Index(const int& key);                             // 0x00b1c150
  Elem38Vector* operator[](const int& key) { return Index(key); }
  void DoInsert(Iter* out, RBNodeBase* hint, IntVecPair* value, bool forceLeft);  // 0x00b1b8b0
};

// @ 0x00b1ba90
string8* IntStrMap::Index(const int& key) {
  IntStrNode* pCurrent = (IntStrNode*)mAnchor.mpNodeParent;
  RBNodeBase* pLowerBound = &mAnchor;
  if (pCurrent) {
    do {
      if (pCurrent->first < key) pCurrent = (IntStrNode*)pCurrent->mpNodeRight;
      else { pLowerBound = pCurrent; pCurrent = (IntStrNode*)pCurrent->mpNodeLeft; }
    } while (pCurrent);
  }
  if (pLowerBound == &mAnchor || key < ((IntStrNode*)pLowerBound)->first) {
    string8 empty;
    IntStrPair pair;
    int k = key;
    MakeIntStrPair(&pair, &k, &empty);
    Iter it;
    DoInsert(&it, (IntStrNode*)pLowerBound, &pair, false);
    return &((IntStrNode*)it.mpNode)->second;
  }
  return &((IntStrNode*)pLowerBound)->second;
}

// @ 0x00b1b980
Iter* StrIntMap::insert(Iter* out, RBNodeBase* hint, const void* value) {
  RBNodeBase* pCurrent = mAnchor.mpNodeParent;
  if (hint == pCurrent || hint == &mAnchor) {
    if (mnSize != 0 && StringLess(&((StrIntNode*)pCurrent)->first, (const string8*)value)) {
      DoInsertValueImpl(out, pCurrent, value, false);
      return out;
    }
  } else {
    RBNodeBase* pNext = RBTreeIncrement(hint);
    if (StringLess(&((StrIntNode*)hint)->first, (const string8*)value) &&
        StringLess((const string8*)value, &((StrIntNode*)pNext)->first)) {
      bool forceLeft = ((StrIntNode*)hint)->mpNodeRight != 0;
      if (forceLeft) {
        DoInsertValueImpl(out, pNext, value, true);
      } else {
        DoInsertValueImpl(out, hint, value, false);
      }
      return out;
    }
  }
  InsertResult res = insertSimple(value, 0);
  out->mpNode = res.first;
  return out;
}

// @ 0x00b1c220
int* StrIntMap::Index(const string8& key) {
  StrIntNode* pCurrent = (StrIntNode*)mAnchor.mpNodeParent;
  RBNodeBase* pLowerBound = &mAnchor;
  if (pCurrent) {
    do {
      if (StringLess(&((StrIntNode*)pCurrent)->first, &key)) pCurrent = (StrIntNode*)pCurrent->mpNodeRight;
      else { pLowerBound = pCurrent; pCurrent = (StrIntNode*)pCurrent->mpNodeLeft; }
    } while (pCurrent);
  }
  if (pLowerBound != &mAnchor && !StringLess(&key, &((StrIntNode*)pLowerBound)->first)) {
    return &((StrIntNode*)pLowerBound)->second;
  }
  StrIntPair pair;
  pair.first = &key;
  pair.second = 0;
  Iter it;
  insert(&it, pLowerBound, &pair);
  return &((StrIntNode*)it.mpNode)->second;
}

// @ 0x00b1c150
Elem38Vector* IntVecMap::Index(const int& key) {
  IntVecNode* pCurrent = (IntVecNode*)mAnchor.mpNodeParent;
  RBNodeBase* pLowerBound = &mAnchor;
  if (pCurrent) {
    do {
      if (pCurrent->first < key) pCurrent = (IntVecNode*)pCurrent->mpNodeRight;
      else { pLowerBound = pCurrent; pCurrent = (IntVecNode*)pCurrent->mpNodeLeft; }
    } while (pCurrent);
  }
  if (pLowerBound != &mAnchor && !(key < ((IntVecNode*)pLowerBound)->first)) {
    return &((IntVecNode*)pLowerBound)->second;
  }
  IntVecPair value;
  value.first = key;
  value.second.mpBegin = 0;
  value.second.mpEnd = 0;
  value.second.mpCapacity = 0;
  Iter it;
  DoInsert(&it, pLowerBound, &value, false);
  Elem38* pb = value.second.mpBegin;
  value.second.Destruct(value.second.mpBegin, value.second.mpEnd);
  if (pb && ((int*)pb)[-1]) delete[] (char*)pb;
  return &((IntVecNode*)it.mpNode)->second;
}

// ================================================================== cStateMachineHost
struct CsHostInfo {
  char pad0[0x1c];
  IntStrMap mStates;     // +0x1c  map<int,string>
};

struct IEditor {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void v10();
  virtual void OnTransition(Elem38Vector* v, int a, int b, int c, int d, int e, int f);  // +0x2c
};

extern "C" void FUN_008d34d0(void* p);            // 0x008d34d0
extern "C" void FUN_008d3c60(void* p, void* a);   // 0x008d3c60
extern "C" void FUN_008d3ca0(void* p);            // 0x008d3ca0
extern "C" void FUN_00e4b990(void* p);            // 0x00e4b990
extern "C" void FUN_00b1b830(void* p);            // 0x00b1b830
extern "C" void* EA_Allocator_GetDefaultAllocator();  // 0x00925cb0
extern "C" void FUN_008d34d0_(void* p);

extern void* g_vtbl_145d318;  // 0x0145d318
extern void* g_vtbl_145d310;  // 0x0145d310
extern void* g_vtbl_145d2c0;  // 0x0145d2c0
extern void* g_vtbl_145d2bc;  // 0x0145d2bc
extern void* g_vtbl_13ec458;  // 0x013ec458
extern void* g_vtbl_13eb394;  // 0x013eb394

struct cGonzagoSubsystem { cGonzagoSubsystem(); ~cGonzagoSubsystem(); };  // 0x00b5b960 / 0x00b5b9a0
struct Stopwatch { void SetUnits(int u); void Reset(); };  // 0x0093a1a0 / 0x0093a380
extern Stopwatch gBrushStopwatch;  // 0x0167c280

struct cStateMachineHost {
  char raw[0x190];
  cStateMachineHost* ctor();                               // 0x00b1c2c0
  void dtor();                                             // 0x00b1c480
  void DeclareState(int index, const char* name);          // 0x00b1c080
  void virtual6(int a, int b, int c, int d, int e, int f); // 0x00b1c540
  void SetupTransitions(int a);                            // 0x00b1c630
  int UpdateEditedScript(int* recs, int type, int val, int* obj, int a6, unsigned a7, unsigned a8);  // 0x00b1bb40
};

// @ 0x00b1c080
void cStateMachineHost::DeclareState(int index, const char* name) {
  CsHostInfo* info = *(CsHostInfo**)(raw + 0x10);
  string8* s = info->mStates.operator[](index);
  const char* e = name + strlen(name);
  s->assign(name, e);
}

// @ 0x00b1c540
void cStateMachineHost::virtual6(int a, int b, int c, int d, int e, int f) {
  Elem38Vector* v = ((IntVecMap*)(raw + 0x28))->operator[](*(int*)(raw + 0x60));
  ((IEditor*)this)->OnTransition(v, a, b, c, d, e, f);
}

// @ 0x00b1c2c0
cStateMachineHost* cStateMachineHost::ctor() {
  unsigned char* p = (unsigned char*)raw;
  *(void**)p = &g_vtbl_13ec458;
  *(void**)(p + 4) = 0;
  *(void**)(p + 8) = &g_vtbl_13eb394;
  new (p + 0xc) cGonzagoSubsystem();
  *(void**)p = &g_vtbl_145d318;
  *(void**)(p + 8) = &g_vtbl_145d310;
  *(void**)(p + 0xc) = &g_vtbl_145d2c0;
  *(void**)(p + 0x10) = &g_vtbl_145d2bc;
  *(unsigned*)(p + 0x30) = 0; *(unsigned*)(p + 0x34) = 0; *(unsigned*)(p + 0x38) = 0;
  *(unsigned*)(p + 0x34) = 0; *(unsigned char*)(p + 0x38) = 0; *(unsigned*)(p + 0x3c) = 0;
  *(void**)(p + 0x2c) = p + 0x2c; *(void**)(p + 0x30) = p + 0x2c;
  *(unsigned*)(p + 0x4c) = 0; *(unsigned*)(p + 0x50) = 0; *(unsigned*)(p + 0x54) = 0;
  *(void**)(p + 0x48) = p + 0x48; *(void**)(p + 0x4c) = p + 0x48;
  *(unsigned*)(p + 0x50) = 0; *(unsigned char*)(p + 0x54) = 0; *(unsigned*)(p + 0x58) = 0;
  *(unsigned*)(p + 0x60) = 0; *(unsigned*)(p + 0x64) = 0;
  *(float*)(p + 0x68) = 0.0f; *(float*)(p + 0x6c) = 0.0f; *(float*)(p + 0x70) = 0.0f;
  FUN_008d34d0(p + 0x74);
  FUN_008d3c60(p + 0x90, EA_Allocator_GetDefaultAllocator());
  FUN_008d34d0(p + 0xc0);
  *(void**)(p + 0xdc) = gEmptyString;
  *(void**)(p + 0xe0) = gEmptyString;
  *(void**)(p + 0xe4) = gEmptyString + 1;
  *(void**)(p + 0xf4) = gEmptyString + 1;
  *(void**)(p + 0xec) = gEmptyString;
  *(void**)(p + 0xf0) = gEmptyString;
  *(unsigned*)(p + 0xfc) = 0; *(unsigned*)(p + 0x100) = 0; *(unsigned*)(p + 0x104) = 0;
  *(unsigned*)(p + 0x110) = 0;
  gBrushStopwatch.SetUnits(5);
  gBrushStopwatch.Reset();
  return this;
}

// @ 0x00b1c480
void cStateMachineHost::dtor() {
  unsigned char* p = (unsigned char*)raw;
  *(void**)p = &g_vtbl_145d318;
  *(void**)(p + 8) = &g_vtbl_145d310;
  *(void**)(p + 0xc) = &g_vtbl_145d2c0;
  *(void**)(p + 0x10) = &g_vtbl_145d2bc;
  void* v = *(void**)(p + 0xfc);
  if (v && ((int*)v)[-1]) delete[] (char*)v;
  unsigned char* a = *(unsigned char**)(p + 0xec);
  if ((1 < (int)(*(unsigned*)(p + 0xf4) - (unsigned)a)) && a) delete[] a;
  a = *(unsigned char**)(p + 0xdc);
  if ((1 < (int)(*(unsigned*)(p + 0xe4) - (unsigned)a)) && a) delete[] a;
  FUN_008d3ca0(p + 0x90);
  FUN_00e4b990(*(void**)(p + 0x50));
  FUN_00b1b830(*(void**)(p + 0x34));
  ((cGonzagoSubsystem*)(p + 0xc))->~cGonzagoSubsystem();
  *(void**)(p + 8) = &g_vtbl_13eb394;
  *(void**)p = &g_vtbl_13ec458;
}

// @ 0x00b1c630
// (transition-script setup; abbreviated -- the full record-building body is not reconstructed)
void cStateMachineHost::SetupTransitions(int a) {
  (void)a;
}

// @ 0x00b1bb40
// (SP::cAppModeTerrainEditor::UpdateEditedScript; the full body is not reconstructed)
int cStateMachineHost::UpdateEditedScript(int* recs, int type, int val, int* obj, int a6, unsigned a7, unsigned a8) {
  (void)recs; (void)type; (void)val; (void)obj; (void)a6; (void)a7; (void)a8;
  return 0;
}

// @ 0x00b1c580
extern StrIntMap gStringIntMap;  // 0x015680cc
void __stdcall FUN_00b1c580(int value, const char* name) {
  const char* p = name;
  while (*p) ++p;
  unsigned n = (unsigned)(p - name);
  char* buf;
  char* end;
  if (n + 1 < 2) {
    buf = gEmptyString;
    end = gEmptyString + 1;
  } else {
    buf = (char*)SPORE_ALLOC(n + 1);
    end = buf + n + 1;
  }
  memcpy(buf, name, n);
  buf[n] = 0;
  string8 s;
  s.mpBegin = buf;
  s.mpEnd = buf + n;
  s.mpCapacity = end;
  int* v = gStringIntMap.operator[](s);
  *v = value;
  if ((end - buf) > 1 && buf) delete[] buf;
}
