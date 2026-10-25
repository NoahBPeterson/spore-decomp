// Slice s00b1b980: the cStateMachineHost region (state-machine host + its EASTL rbtree map
// instances map<string,int>, map<int,string>, map<int, vector<Elem38>>, the class ctor/dtor and
// the transition-script setup helper).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE (SetupTransitions is scored with /EHs-c- so its body has the
// original's bare, EH-free prologue; the other functions compile identically under both)
#include "types.h"
#include <intrin.h>

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
// The engine's string is 16 bytes: begin / end / capacity plus an unused 4th slot (the original's
// pair<string,int> puts the int at +0x10 and its copy ctor never touches +0xc).
struct string8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  unsigned int mUnused0c;
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
// One 0x38-byte transition-script record.  The engine's strings only use the first 0xc bytes, so the
// string member occupies 16 bytes and the payload starts at +0x10.
struct Elem38 {
  string8 name;              // +0x00  always "transition"
  int field10;               // +0x10
  int state;                 // +0x14  the state the record belongs to
  int value18;               // +0x18  6 / 8 / the edited-script id
  int value1c;               // +0x1c  0 / 1 / -1 / the edited-script id
  int value20;               // +0x20  -1
  unsigned char flag24;      // +0x24
  int value28;               // +0x28  6 / 8 / 10 / 11
  int field2c;               // +0x2c
  int field30;               // +0x30
  int field34;               // +0x34
  Elem38() {}
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
  // eastl::vector<Elem38>::push_back, inlined by the original
  void push_back(const Elem38& value) {
    if (mpEnd < mpCapacity) {
      Elem38* p = mpEnd;
      mpEnd = p + 1;
      if (p) new (p) Elem38(value);
    } else {
      DoInsertValue(mpEnd, value);
    }
  }
  // explicit teardown (the slice's Elem38Vector has no destructor; other reconstructed callers run
  // Destruct/free themselves, so the vector type stays destructor-free)
  void Destroy() {
    for (Elem38* p = mpBegin; p != mpEnd; ++p) p->~Elem38();
    if (mpBegin && ((int*)mpBegin)[-1]) delete[] (char*)mpBegin;
  }
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
// pair<int,string> constructor: copies the default string into the pair's second member
struct String4 { __declspec(noinline) void* ctor(void* key, void* def); };  // 0x00b209f0
struct IntStrMap {
  char pad[4];
  RBNodeBase mAnchor;  // +4
  unsigned mnSize;     // +0x14
  char mAllocator[4];  // +0x18  stateless eastl::allocator (never written)
  __declspec(noinline) string8* Index(const int& key);                    // 0x00b1ba90
  string8* operator[](const int& key) { return Index(key); }
  // 0x00b1ad00; the trailing slot is an unused flag argument that the original fills with the
  // caller's (dead) key-pointer stack slot, so callers pass that value through
  void DoInsert(Iter* out, IntStrNode* hint, IntStrPair* value, unsigned int unusedFlag);
  void Free(RBNodeBase* node);                                            // 0x00e4b990
  void destroy() { Free(mAnchor.mpNodeParent); }
  // inlined eastl::rbtree::reset(): only the anchor's links/colour and the size
  void Reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  // inlined eastl::rbtree::rbtree(allocator): mAnchor() value-init, then reset()
  void Construct() {
    mAnchor = RBNodeBase();
    Reset();
  }
  void clear() {
    destroy();
    Reset();
  }
};


// ---- map<string,int>
// The pair is laid out like the original's: the key string at +0 (so a pair* doubles as a
// string*), the mapped int at +0x10.
struct StrIntPair {
  string8 first;
  int second;
  StrIntPair(const string8& key) : first(key.mpBegin, key.mpEnd), second(0) {}
};
struct StrIntMap {
  char pad[4];
  RBNodeBase mAnchor;  // +4
  unsigned mnSize;     // +0x14
  void LowerBound(RBNodeBase** out, const string8* key);                              // 0x00b19cb0
  __declspec(noinline) Iter* insert(Iter* out, RBNodeBase* hint, const void* value,
                                    bool forceLeft);                                  // 0x00b1b980
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
  char mAllocator[4];  // +0x18  stateless eastl::allocator (never written)
  __declspec(noinline) Elem38Vector* Index(const int& key);                             // 0x00b1c150
  Elem38Vector* operator[](const int& key) { return Index(key); }
  // 0x00b1b8b0; the trailing slot is unused and carries the caller's (dead) key-pointer value
  void DoInsert(Iter* out, RBNodeBase* hint, IntVecPair* value, unsigned int unusedFlag);
  void Free(RBNodeBase* node);                                            // 0x00b1b830
  void destroy() { Free(mAnchor.mpNodeParent); }
  // inlined eastl::rbtree::reset(): only the anchor's links/colour and the size
  void Reset() {
    mAnchor.mpNodeRight = &mAnchor;
    mAnchor.mpNodeLeft = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor = 0;
    mnSize = 0;
  }
  // inlined eastl::rbtree::rbtree(allocator): mAnchor() value-init, then reset()
  void Construct() {
    mAnchor = RBNodeBase();
    Reset();
  }
  void clear() {
    destroy();
    Reset();
  }
};

// @ 0x00b1ba90
string8* IntStrMap::Index(const int& key) {
  IntStrNode* pCurrent = (IntStrNode*)mAnchor.mpNodeParent;
  RBNodeBase* pLowerBound = &mAnchor;
  if (pCurrent) {
    do {
      // the original orders the keys as unsigned (`jb`/`jae`)
      if ((unsigned)pCurrent->first < (unsigned)key) pCurrent = (IntStrNode*)pCurrent->mpNodeRight;
      else { pLowerBound = pCurrent; pCurrent = (IntStrNode*)pCurrent->mpNodeLeft; }
    } while (pCurrent);
  }
  if (pLowerBound == &mAnchor || (unsigned)key < (unsigned)((IntStrNode*)pLowerBound)->first) {
    string8 empty;
    IntStrPair pair;
    ((String4*)&pair)->ctor((void*)&key, &empty);
    Iter it;
    // the unused flag rides in the key's dead stack slot: only its low byte is cleared
    DoInsert(&it, (IntStrNode*)pLowerBound, &pair, (unsigned int)&key & ~0xFFu);
    return &((IntStrNode*)it.mpNode)->second;
  }
  return &((IntStrNode*)pLowerBound)->second;
}

// @ 0x00b1b980
Iter* StrIntMap::insert(Iter* out, RBNodeBase* hint, const void* value, bool forceLeft) {
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
  // the tree search lives in the shared lower_bound helper (0x00b19cb0), which compares with the
  // length-first string ordering
  RBNodeBase* pLowerBound;
  LowerBound(&pLowerBound, &key);
  if (pLowerBound != &mAnchor && !StringLess(&key, &((StrIntNode*)pLowerBound)->first)) {
    return &((StrIntNode*)pLowerBound)->second;
  }
  StrIntPair value(key);
  Iter it;
  insert(&it, pLowerBound, &value, false);
  return &((StrIntNode*)it.mpNode)->second;
}

// @ 0x00b1c150
Elem38Vector* IntVecMap::Index(const int& key) {
  IntVecNode* pCurrent = (IntVecNode*)mAnchor.mpNodeParent;
  RBNodeBase* pLowerBound = &mAnchor;
  if (pCurrent) {
    do {
      // the original orders the keys as unsigned (`jb`/`jae`)
      if ((unsigned)pCurrent->first < (unsigned)key) pCurrent = (IntVecNode*)pCurrent->mpNodeRight;
      else { pLowerBound = pCurrent; pCurrent = (IntVecNode*)pCurrent->mpNodeLeft; }
    } while (pCurrent);
  }
  if (pLowerBound != &mAnchor && (unsigned)((IntVecNode*)pLowerBound)->first <= (unsigned)key) {
    return &((IntVecNode*)pLowerBound)->second;
  }
  // value_type(key, mapped_type()): the zeroed mapped_type() is copy-constructed into the pair
  Elem38Vector empty;
  IntVecPair value;
  value.first = key;
  new (&value.second) Elem38Vector(empty);   // 0x00b1a350
  Iter it;
  DoInsert(&it, pLowerBound, &value, (unsigned int)&key & ~0xFFu);
  Elem38* pb = value.second.mpBegin;
  value.second.Destruct(value.second.mpBegin, value.second.mpEnd);
  if (pb && ((int*)pb)[-1]) delete[] (char*)pb;
  empty.Destruct(empty.mpBegin, empty.mpEnd);
  return &((IntVecNode*)it.mpNode)->second;
}

// ---- the two state maps sit next to each other: the dtor addresses the string map as
//      (&mVecMap)+0x1c, so model them as one sub-object the teardown takes a reference to
struct StateMaps {
  IntVecMap vec;   // +0x00
  IntStrMap str;   // +0x1c
};

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

extern "C" void* EA_Allocator_GetDefaultAllocator();  // 0x00925cb0

extern void* g_vtbl_145d318;  // 0x0145d318
extern void* g_vtbl_145d310;  // 0x0145d310
extern void* g_vtbl_145d2c0;  // 0x0145d2c0
extern void* g_vtbl_145d2bc;  // 0x0145d2bc
extern void* g_vtbl_13ec458;  // 0x013ec458
extern void* g_vtbl_13eb394;  // 0x013eb394

struct cGonzagoSubsystem {
  void* mpVftable;
  cGonzagoSubsystem();                     // 0x00b5b960
  ~cGonzagoSubsystem();                    // 0x00b5b9a0
};
// Inlined construction sites of the sub-object go through this ecx-call form (the original has no
// placement-new null test).
extern void __fastcall cGonzagoSubsystem_ctor(cGonzagoSubsystem* self);  // 0x00b5b960

// A 0x1c-byte framework sub-object whose ctor is 0x008d34d0.
struct FrameworkObject1c {
  char mData[0x1c];
  void ctor();                             // 0x008d34d0
};

// One entry of the edited-script list at +0x90; only the second word is read here.
struct TransitionConfig {
  int field0;
  int value;
};

// The list at +0x90 (size 0x30).
struct TransitionConfigList {
  char mData[0x30];
  void ctor(void* allocator);              // 0x008d3c60
  void dtor();                             // 0x008d3ca0
  int GetCount();                          // 0x008d3ac0
  TransitionConfig* GetItem(int index);    // 0x008d3ad0
};

// A refcount-header vector with trivial elements (only its allocation is released on teardown).
struct PodVector {
  void* mpBegin;
  void* mpEnd;
  void* mpCapacity;
};

// Win32 performance counter plumbing used by the inlined EA::Stopwatch start.
union LARGE_INTEGER {
  struct { unsigned int LowPart; int HighPart; } u;
  __int64 QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* count);
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)

struct Stopwatch {
  unsigned __int64 mnStartTime;        // +0x00
  unsigned __int64 mnTotalElapsedTime; // +0x08
  int mnUnits;                         // +0x10
  float mfCoefficient;                 // +0x14
  void SetUnits(int units);            // 0x0093a1a0
  void SetElapsedCycles(__int64 cycles);  // 0x0093a380
  void Start() {
    if (!mnStartTime) {
      if (mnUnits == 1) {
        mnStartTime = __rdtsc();
      } else {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        mnStartTime = now.QuadPart;
      }
    }
  }
};
extern Stopwatch gBrushStopwatch;  // 0x0167c280

struct cStateMachineHost {
  void** mpVftable;                    // +0x00
  void* mpField04;                     // +0x04
  void** mpVftable08;                  // +0x08
  cGonzagoSubsystem mGonzago;          // +0x0c
  void* mpSharedState;                 // +0x10  the shared info object DeclareState walks
  char mPad14[0x14];                   // +0x14
  StateMaps mMaps;                     // +0x28  map<int, vector<Elem38>>, map<int, string>
  int mStateId;                        // +0x60
  int mField64;                        // +0x64
  float mFloat68;                      // +0x68
  float mFloat6c;                      // +0x6c
  float mFloat70;                      // +0x70
  FrameworkObject1c mObject74;         // +0x74
  TransitionConfigList mConfigs;       // +0x90
  FrameworkObject1c mObjectC0;         // +0xc0
  string8 mStringDC;                   // +0xdc
  string8 mStringEC;                   // +0xec
  PodVector mPodVector;                // +0xfc
  char mPad108[8];                     // +0x108
  int mField110;                       // +0x110
  char mPad114[0x7c];                  // +0x114

  cStateMachineHost* ctor();                               // 0x00b1c2c0
  void dtor();                                             // 0x00b1c480
  void DeclareState(int index, const char* name);          // 0x00b1c080
  void virtual6(int a, int b, int c, int d, int e, int f); // 0x00b1c540
  void SetupTransitions(int a);                            // 0x00b1c630
};

typedef char cStateMachineHost_size_check[sizeof(cStateMachineHost) == 0x190 ? 1 : -1];

// @ 0x00b1c080
void cStateMachineHost::DeclareState(int index, const char* name) {
  CsHostInfo* info = (CsHostInfo*)mpSharedState;
  string8* s = info->mStates.operator[](index);
  const char* e = name + strlen(name);
  s->assign(name, e);
}

// @ 0x00b1c540
void cStateMachineHost::virtual6(int a, int b, int c, int d, int e, int f) {
  Elem38Vector* v = mMaps.vec.operator[](mStateId);
  ((IEditor*)this)->OnTransition(v, a, b, c, d, e, f);
}

// @ 0x00b1c2c0
cStateMachineHost* cStateMachineHost::ctor() {
  mpVftable = &g_vtbl_13ec458;
  mpField04 = 0;
  mpVftable08 = &g_vtbl_13eb394;
  cGonzagoSubsystem_ctor(&mGonzago);
  mpVftable = &g_vtbl_145d318;
  mpVftable08 = &g_vtbl_145d310;
  mGonzago.mpVftable = &g_vtbl_145d2c0;
  mpSharedState = &g_vtbl_145d2bc;
  mMaps.vec.Construct();
  mMaps.str.Construct();
  mStateId = 0;
  mField64 = 0;
  mFloat68 = 0.0f;
  mFloat6c = 0.0f;
  mFloat70 = 0.0f;
  mObject74.ctor();
  mConfigs.ctor(EA_Allocator_GetDefaultAllocator());
  mObjectC0.ctor();
  mStringDC.mpBegin = gEmptyString;
  mStringDC.mpEnd = gEmptyString;
  mStringDC.mpCapacity = gEmptyString + 1;
  mStringEC.mpCapacity = gEmptyString + 1;
  mStringEC.mpBegin = gEmptyString;
  mStringEC.mpEnd = gEmptyString;
  mPodVector.mpBegin = 0;
  mPodVector.mpEnd = 0;
  mPodVector.mpCapacity = 0;
  mField110 = 0;
  gBrushStopwatch.SetUnits(5);
  gBrushStopwatch.SetElapsedCycles(0);
  gBrushStopwatch.Start();
  return this;
}

// @ 0x00b1c480
void cStateMachineHost::dtor() {
  cGonzagoSubsystem* gonzago = &mGonzago;
  mpVftable = &g_vtbl_145d318;
  mpVftable08 = &g_vtbl_145d310;
  gonzago->mpVftable = &g_vtbl_145d2c0;
  mpSharedState = &g_vtbl_145d2bc;
  void* v = mPodVector.mpBegin;
  if (v && ((int*)v)[-1]) delete[] (char*)v;
  unsigned char* a = (unsigned char*)mStringEC.mpBegin;
  if ((1 < (int)(mStringEC.mpCapacity - mStringEC.mpBegin)) && a) delete[] a;
  a = (unsigned char*)mStringDC.mpBegin;
  if ((1 < (int)(mStringDC.mpCapacity - mStringDC.mpBegin)) && a) delete[] a;
  mConfigs.dtor();
  StateMaps& maps = mMaps;
  maps.str.destroy();
  maps.vec.destroy();
  gonzago->~cGonzagoSubsystem();
  mpVftable08 = &g_vtbl_13eb394;
  mpVftable = &g_vtbl_13ec458;
}

// @ 0x00b1c630
void cStateMachineHost::SetupTransitions(int a) {
  Elem38 t;
  t.name.assign("transition", "");
  t.state = a;
  t.field10 = 0;
  t.value20 = -1;
  t.flag24 = 0;
  t.field2c = 0;
  t.field30 = 0;
  t.field34 = 0;
  t.value1c = 0;

  Elem38Vector v;
  t.value18 = 6;
  t.value28 = 6;
  v.push_back(t);
  t.value18 = 8;
  t.value28 = 8;
  t.value1c = 1;
  v.push_back(t);
  t.value1c = -1;
  v.push_back(t);

  int count = mConfigs.GetCount();
  for (int i = 0; i < count; ++i) {
    int value = mConfigs.GetItem(i)->value;
    t.value18 = value;
    t.value1c = value;
    t.value28 = 10;
    v.push_back(t);
    t.value28 = 11;
    v.push_back(t);
  }

  mMaps.str.clear();
  mMaps.vec.clear();
  mMaps.str.operator[](0)->assign("TriggerNeutral", "");
  mMaps.vec.operator[](0)->operator=(v);

  // ~vector<Elem38>: destroy each record's name buffer, then release the array block
  for (Elem38* p = v.mpBegin; p != v.mpEnd; ++p) {
    if ((p->name.mpCapacity - p->name.mpBegin) > 1 && p->name.mpBegin)
      delete[] p->name.mpBegin;
  }
  if (v.mpBegin && ((int*)v.mpBegin)[-1]) delete[] (char*)v.mpBegin;
}

// ================================================================== the edited-script updater
// The updater walks the host's pending property-edit records, applies the first one that matches the
// requested (type, flags, mask, value, object) tuple through the script property services, and moves
// the host to the record's target state id.

extern unsigned char g_0167be90;   // 0x0167be90: nonzero while the updater runs
extern int g_0167be8c;             // 0x0167be8c: the record that was applied
extern float g_013f5c8c;           // 0x013f5c8c: seconds per tick (1/120)
extern int g_015d1160;             // 0x015d1160: fallback for a non-integer property value
extern void* FUN_006895b0();       // 0x006895b0: script property services singleton

namespace eastl {
struct sp_vector_allocator;
template <class T, class A> struct vector {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  void DoInsertValue(T* position, const T& value);   // 0x004558a0
};
}

namespace EA {
struct Variant {                    // 16-byte inline payload followed by the flag/type words
  unsigned int value0;              // +0x00 inline int, or a pointer when mFlags & 0x30
  unsigned int value1;              // +0x04
  unsigned int value2;              // +0x08
  unsigned int value3;              // +0x0c
  unsigned short mFlags;            // +0x10
  unsigned short mTypeId;           // +0x12
  bool Construct(unsigned short type, unsigned short flags, const void* src, unsigned int width,
                 unsigned int isAtomic);           // 0x0093dd80
  void Destruct(char bFree);                       // 0x0093db80
};
}

struct IPropertyTarget {            // what a record's object id is resolved against
  virtual void v0();
  virtual void v4();
  virtual void v8();
  virtual int v0c(int objectId);    // +0x0c nonzero when the object exists
};

struct PropBag {                    // a property bag handed out by the services
  virtual void v0();
  virtual void v4();                                        // +0x04 release
  virtual void v8();
  virtual void vc();
  virtual void v10();
  virtual void v14(int keep);                               // +0x14 commit
  virtual void v18(int id);
  virtual const EA::Variant* GetProp(int id);               // +0x1c
  virtual void SetProp(int id, const EA::Variant* value);   // +0x20
};

struct ScriptServices {             // the services singleton (0x006895b0)
  virtual void v0();
  virtual void v4();
  virtual void v8();
  virtual void vc();
  virtual void v10();
  virtual void v14();
  virtual void v18(PropBag** out);                          // +0x18 hand out a bag
  virtual void v1c();
  virtual void v20();
  virtual void v24();
  virtual void v28();
  virtual void v2c();
  virtual void v30();
  virtual void v34();
  virtual void v38();
  virtual void v3c();
  virtual void v40();
  virtual void v44();
  virtual void v48();
  virtual void v4c();
  virtual void v50();
  virtual void v54(int a, PropBag* b, PropBag* c);          // +0x54 apply the edit
};

struct EditRecord {                 // one pending property edit, 0x38 bytes
  uint32_t pad00[4];                // +0x00
  int32_t mField10;                 // +0x10
  int32_t mField14;                 // +0x14
  int32_t mValue18;                 // +0x18
  int32_t mLimit1c;                 // +0x1c (-1: no value restriction)
  int32_t mObjectId20;              // +0x20 (-1: no object restriction)
  unsigned char mKeep24;            // +0x24 keep the current state id on the id stack
  unsigned char pad25[3];           // +0x25
  int32_t mType28;                  // +0x28
  uint32_t mFlags2c;                // +0x2c
  uint32_t mMask30;                 // +0x30
  uint32_t mTime34;                 // +0x34
};

struct EditRecordVector {           // eastl vector of records
  EditRecord* mpBegin;
  EditRecord* mpEnd;
  EditRecord* mpCapacity;
};

struct cScriptHost {                // the state-machine host as the script updater sees it
  uint32_t pad00[17];               // +0x00
  IntStrMap mStateNames;            // +0x44 state id -> name
  uint32_t pad5c;                   // +0x5c
  int32_t mCurrentId;               // +0x60
  int32_t mPreviousId;              // +0x64
  uint32_t pad68[2];                // +0x68
  float mTime;                      // +0x70
  uint32_t pad74[34];               // +0x74
  eastl::vector<unsigned int, eastl::sp_vector_allocator> mIdStack;   // +0xfc
  bool UpdateEditedScript(EditRecordVector* recs, int type, int val, IPropertyTarget* obj,
                          const int* vec3, unsigned mask, unsigned flags);
};

// @ 0x00b1bb40
bool cScriptHost::UpdateEditedScript(EditRecordVector* recs, int type, int val, IPropertyTarget* obj,
                                     const int* vec3, unsigned mask, unsigned flags) {
  g_0167be90 = 1;
  int count = (int)((char*)recs->mpEnd - (char*)recs->mpBegin) / 0x38;
  if (count == 0) {
    g_0167be90 = 0;
    return false;
  }
  // pick the first record that matches the requested edit
  EditRecord* rec;
  unsigned int i = 0;
  for (;;) {
    rec = recs->mpBegin + i;
    bool match = type == rec->mType28 &&
                 (((flags | 0x40) & rec->mFlags2c) == rec->mFlags2c || rec->mFlags2c == 0x3ff) &&
                 (rec->mMask30 & mask) == rec->mMask30 &&
                 !((rec->mFlags2c & 0x40) && (flags & 0x40));
    if (rec->mObjectId20 != -1) {
      // the object lookup runs whether or not the rest of the record matched
      bool found = obj ? obj->v0c(rec->mObjectId20) != 0 : rec->mObjectId20 == 0;
      match = match && found;
    }
    if (match && (rec->mLimit1c == -1 || val == rec->mLimit1c)) break;
    ++i;
    if (i >= (unsigned int)count) {   // the original scans with an unsigned index
      g_0167be90 = 0;
      return false;
    }
  }

  if (rec->mTime34) mTime = (float)rec->mTime34;
  int value18 = rec->mValue18;
  if (rec->mType28 == 9 && value18 == -1) value18 = val;
  int pending = 0;
  if (rec->mType28 == 10 || rec->mType28 == 11) pending = rec->mType28;
  float fvec[3] = {0.0f, 0.0f, 0.0f};
  if (rec->mType28 == 8) {
    float ticks = (float)val;                 // seconds: the value in ticks scaled to the frame time
    fvec[2] = ticks * g_013f5c8c;
  }

  ScriptServices* services = (ScriptServices*)FUN_006895b0();
  PropBag* primary;
  services->v18(&primary);
  EA::Variant v;
  v.mFlags = 0;
  v.mTypeId = 0;
  v.Construct(0x11, 0x29, obj, 4, 1);      // the edited object itself
  primary->SetProp(0, &v);
  if (v.mFlags & 4) v.Destruct(false);

  v.value0 = (unsigned)value18;            // the record's value
  v.mFlags = 0;
  v.mTypeId = 0xa;
  primary->SetProp(1, &v);
  if (v.mFlags & 4) v.Destruct(false);

  v.value0 = (unsigned)pending;            // the pending state / event
  v.mFlags = 0;
  v.mTypeId = 0xa;
  primary->SetProp(2, &v);
  if (v.mFlags & 4) v.Destruct(false);

  v.value0 = (unsigned)vec3[0];            // the target position
  v.value1 = (unsigned)vec3[1];
  v.value2 = (unsigned)vec3[2];
  v.mFlags = 0;
  v.mTypeId = 0x31;
  primary->SetProp(3, &v);
  if (v.mFlags & 4) v.Destruct(false);

  memcpy(&v.value0, fvec, sizeof(fvec));   // the extra vector
  v.mFlags = 0;
  v.mTypeId = 0x31;
  primary->SetProp(4, &v);
  if (v.mFlags & 4) v.Destruct(false);

  PropBag* secondary;
  services->v18(&secondary);
  v.value0 = 0;
  v.mFlags = 0;
  v.mTypeId = 9;
  secondary->SetProp(0, &v);
  if (v.mFlags & 4) v.Destruct(false);

  services->v54(rec->mField14, primary, secondary);

  // the applied edit reports the state id to switch to
  const EA::Variant* r = secondary->GetProp(0);
  int mode;
  if (!r) {
    mode = 0;
  } else if (r->mTypeId == 9 || r->mTypeId == 0x10) {
    mode = (r->mFlags & 0x30) ? *(const int*)(unsigned)r->value0 : (int)r->value0;
  } else {
    mode = g_015d1160;
  }

  primary->v14(0);
  secondary->v14(0);
  primary->v4();
  secondary->v4();

  int value = mCurrentId;
  if (mode == 1) {
    // drop the whole id stack (the original clears it through a zero-length copy)
    volatile unsigned nothing = 0;
    memcpy(mIdStack.mpBegin, mIdStack.mpEnd, nothing);
    mIdStack.mpEnd = mIdStack.mpBegin;
    value = mPreviousId;
  } else if (mode == 0) {
    if (rec->mField10 == -3) {
      value = (int)*--mIdStack.mpEnd;
    } else if (rec->mField10 != -2) {
      value = rec->mField10;
    }
  }

  if (mCurrentId != value) {
    if (rec->mKeep24) {
      if (mIdStack.mpEnd >= mIdStack.mpCapacity) {
        mIdStack.DoInsertValue(mIdStack.mpEnd, (const unsigned int&)mCurrentId);
      } else {
        unsigned int* slot = mIdStack.mpEnd++;
        if (slot) *slot = (unsigned int)mCurrentId;
      }
    }
    // name of the state being left: copied once, then released (nothing reads the copy)
    string8* s = mStateNames.Index(mCurrentId);
    unsigned int n = (unsigned int)(s->mpEnd - s->mpBegin);
    char* buf;
    char* cap;
    if (n + 1 > 1) {
      buf = (char*)SPORE_ALLOC(n + 1);
      cap = buf + n + 1;
    } else {
      buf = gEmptyString;
      cap = gEmptyString + 1;
    }
    memcpy(buf, s->mpBegin, n);
    buf[n] = 0;
    mCurrentId = value;
    if (cap - buf > 1 && buf) delete[] buf;
  }
  g_0167be8c = (int)rec;
  g_0167be90 = 0;
  return true;
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
  // `s`'s destructor releases `buf` (only when the capacity was allocated, not the shared empty
  // string), which is exactly where the original frees it -- a manual free would double-free.
}
