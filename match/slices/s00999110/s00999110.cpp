// Slice s00999110 (bfs4 #35): EA::UTFWinTools::SerCollection / UI::SerializationService
// and EA::StringMan StringTable / StringTableXml resource machinery.
// Default flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <new>
void* __cdecl operator new(size_t, const char*, int, int, int, int);
#pragma intrinsic(_InterlockedExchange)

typedef unsigned int uint;
typedef wchar_t wchar16;

// ===========================================================================
// generic declarations
// ===========================================================================
extern "C" void  operator_delete(void*) throw();
extern "C" void* operator_new(unsigned int, const char*, int, int, const char*, int);


extern void FUN_004b6000(void*, void*, void*);
extern void FUN_00a80dd0(void*, void*);
extern void FUN_00e25bd0(void*, void*);
extern void** FUN_00b6f4f0(void*, void*, void*, void*);
extern void FUN_00620230(void*);
extern void FUN_00928ba0(void*, uint);
extern void FUN_00a16a20(void*);
extern void FUN_00a23ef0(void*, void*);
extern void FUN_004b5440(void*);
extern void FUN_00928dc0(void*);

#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk, returns dst
extern void* FUN_008de1a0();                                             // service-manager singleton accessor

struct Key { uint mInstance; uint mType; uint mGroup; };

struct AtomicInt {
  volatile long mValue;
  AtomicInt() { _InterlockedExchange(&mValue, 0); }
};

// generic COM-ish object; slot 3 ([+0xc]) is Cast(uint type)
struct IUnknown32 {
  virtual void AddRef();
  virtual void Release();
  virtual void v08();
  virtual void* Cast(uint type);
  virtual void v10();
  virtual void v14();
  virtual void v18();
  virtual void v1c();
  virtual void v20();
  virtual void v24();
  virtual void v28();
  virtual void v2c();
};

// EA::Allocator::StackAllocator
struct StackAllocator {
  uint   mnDefaultBlockSize;         // +0x00
  void*  mpCurrentBlock;             // +0x04
  char*  mpCurrentBlockEnd;          // +0x08
  char*  mpCurrentObjectBegin;       // +0x0c
  char*  mpCurrentObjectEnd;         // +0x10
  void*  mpCoreAllocationFunction;   // +0x14
  void*  mpCoreFreeFunction;         // +0x18
  void*  mpCoreFunctionContext;      // +0x1c
  void*  mpTopBookmark;              // +0x20
  StackAllocator(int, int, int, int, int) throw();
  ~StackAllocator() { Reset(); }
  void __thiscall Reset() throw();                 // 0x928dc0
  void   Init(int, int, int, int, int) throw();
  bool   AllocateNewBlock(uint) throw();
  void* AllocInline(uint size) {
    if ((int)(mpCurrentBlockEnd - mpCurrentObjectBegin) - (int)size < 0) {
      if (!AllocateNewBlock(size)) return 0;
    }
    char* p = mpCurrentObjectBegin;
    mpCurrentObjectBegin = p + size;
    mpCurrentObjectEnd = p + size;
    return p;
  }
};

// EA::ResourceMan::Resource + intrusive_list_node
struct ResourceBase {
  virtual ~ResourceBase();
  volatile long mRefCount;   // +0x04
  Key mKey;                  // +0x08
  ResourceBase() {
    _InterlockedExchange(&mRefCount, 0);
    mKey.mInstance = 0; mKey.mType = 0; mKey.mGroup = 0;
  }
};
struct IntrusiveNode {
  void* mpNext;   // maps to StringTable+0x14
  void* mpPrev;   // maps to StringTable+0x18
  IntrusiveNode() { mpPrev = 0; mpNext = 0; }
};

struct StringTable : ResourceBase, IntrusiveNode {
  wchar_t* mpTableName;   // +0x1c
  Key mFirstKey;          // +0x20
  Key mLastKey;           // +0x2c
  __declspec(noinline) StringTable();
  ~StringTable();                                   // out of line at 0xa16a20
};

struct PtrVector {
  IUnknown32** mpBegin;   // +0x00
  IUnknown32** mpEnd;     // +0x04
  IUnknown32** mpCap;     // +0x08
  char alloc[4];          // +0x0c
  void resize(uint) throw();
};

struct StrVec {
  IUnknown32** mpStringBegin;  // +0x38
  IUnknown32** mpStringEnd;    // +0x3c
  IUnknown32** mpStringCap;    // +0x40
  char padString[8];           // +0x44
  StrVec() : mpStringBegin(0), mpStringEnd(0), mpStringCap(0) {}
  ~StrVec() { if (mpStringBegin != 0 && *(int*)((char*)mpStringBegin - 4) != 0) operator_delete(mpStringBegin); }
};

struct StringTableXml : StringTable {
  StrVec mStrings;
  StackAllocator mAllocator;   // +0x4c
  StringTableXml(const Key& k, const wchar_t* name);
  ~StringTableXml();
  wchar_t* StrDup(const wchar_t* src);
  void SetString(uint index, const wchar_t* str);
};

// ===========================================================================
// EA::UTFWinTools::SerializationService
// ===========================================================================
struct SerializationService {
  virtual ~SerializationService();
  void** mpPluginsBegin;    // +0x04
  void** mpPluginsEnd;      // +0x08
  void** mpPluginsCap;      // +0x0c
  char   pad10[8];          // +0x10
  void** mpBindersBegin;    // +0x18
  void** mpBindersEnd;      // +0x1c
  void** mpBindersCap;      // +0x20
  char   pad24[8];          // +0x24
  void*  mErrorCallback;    // +0x2c
  void*  mpCallbackContext; // +0x30
  SerializationService();
  __declspec(noinline) void Callback(uint code) {
    if (mErrorCallback)
      ((void (__cdecl*)(uint, int, int, int, void*))mErrorCallback)
        (code, 0, 0, 0, mpCallbackContext);
  }
  void*  GetReader(void* arg);
  uint   Read(uint a, uint b, uint c, uint d);
  void   RemovePlugin(IUnknown32* obj);
  void   ClearAll();
};

struct RcVec {                       // eastl::vector<AutoRefCount<..>, sp_vector_allocator>
  void** b; void** e; void** c; char alloc[4];
  void __thiscall erase(void** first, void** last);   // 0xe25bd0
};
struct SpVec {                       // eastl::vector<T*, sp_vector_allocator>
  void** b; void** e; void** c; char alloc[4];
  void __thiscall DoInsertValue(void** pos, void** v);   // 0xa80dd0
  void __thiscall swap(SpVec* o);                        // 0x811a20
  void __thiscall insert_n(void** pos, uint n, void** value);   // 0x999dd0
  void push_back(void* v) {
    void** p = e;
    if (p < c) { e = p + 1; if (p) *p = v; }
    else DoInsertValue(p, &v);
  }
  void clear_all() {
    void** last = e; void** first = b;
    FUN_011e0744(first, last, (uint)((char*)e - (char*)last));
    e = e - (last - first);
  }
};

// @ 0x009994a0  SerializationService::Read
uint SerializationService::Read(uint a, uint b, uint c, uint d) {
  (void)d;
  void* p = VF(this, 0x10, void*(__thiscall*)(void*, uint))(this, 0xafc46457);
  if (p != 0)
    return VF(p, 0x10, uint(__thiscall*)(void*, uint, uint, uint, void*, void*, void*))
      (p, a, b, c, &mpBindersBegin, mErrorCallback, mpCallbackContext);
  return 0x4fc40001;
}

// @ 0x009994f0  SerializationService::GetReader
void* SerializationService::GetReader(void* arg) {
  void* result = 0;
  void** it = mpPluginsBegin;
  void** end = mpPluginsEnd;
  if (it != end) {
    do {
      if (result) break;
      result = ((IUnknown32*)*it)->Cast((uint)arg);
      ++it;
    } while (it != end);
  }
  return result;
}

// @ 0x00999520
SerializationService::SerializationService()
  : mpPluginsBegin(0), mpPluginsEnd(0), mpPluginsCap(0),
    mpBindersBegin(0), mpBindersEnd(0), mpBindersCap(0),
    mErrorCallback(0), mpCallbackContext(0) {}

// @ 0x00999550  SerializationService::_virtual_dtor
SerializationService::~SerializationService() {
  void* p = mpBindersBegin;
  if (p != 0 && *(int*)((char*)p - 4) != 0) operator_delete(p);
  FUN_004b5440(&mpPluginsBegin);
}

// @ 0x00999590  SerializationService::func04h  (add plugin, bind object)
void FUN_00999590(SerializationService* self, IUnknown32* obj) {
  if (obj) obj->AddRef();
  if (self->mpPluginsEnd < self->mpPluginsCap) {
    *self->mpPluginsEnd++ = obj;
  } else {
    FUN_004b6000(&self->mpPluginsBegin, self->mpPluginsEnd, &obj);
  }
  if (obj) obj->Release();
  if (obj) {
    IUnknown32* casted = (IUnknown32*)obj->Cast(0x4fc56322);
    if (casted) {
      if (self->mpBindersEnd < self->mpBindersCap) *self->mpBindersEnd++ = casted;
      else FUN_00a80dd0(self->mpBindersEnd, &casted);
    }
  }
}

// @ 0x00999640  SerializationService::RemovePlugin
void SerializationService::RemovePlugin(IUnknown32* obj) {
  RcVec* plugins = (RcVec*)&mpPluginsBegin;
  SpVec* binders = (SpVec*)&mpBindersBegin;
  void** it = plugins->b;
  void** end = plugins->e;
  for (; it != end; ++it) {
    if (*it == obj) {
      if (it != end)
        it = FUN_00b6f4f0(it + 1, end, it, &obj);
      break;
    }
  }
  if (it != plugins->e) {
    plugins->erase(it, plugins->e);
    binders->clear_all();
    void** e2 = plugins->e;
    for (void** q = plugins->b; q != e2; ++q) {
      IUnknown32* p = (IUnknown32*)*q;
      if (p) {
        void* c = p->Cast(0x4fc56322);
        if (c)
          binders->push_back(c);
      }
    }
  }
}

// @ 0x00999720  SerializationService::ClearAll  (clear binders + plugins)
void SerializationService::ClearAll() {
  ((SpVec*)&mpBindersBegin)->clear_all();
  RcVec* plugins = (RcVec*)&mpPluginsBegin;
  plugins->erase(plugins->b, plugins->e);
}

// ===========================================================================
// UTFWin serialization service (UI variant) -- placeholder complete-ish body
// ===========================================================================
struct UISerializationService {
  virtual ~UISerializationService();
  void** mpPluginsBegin;    // +0x04
  void** mpPluginsEnd;      // +0x08
  void** mpPluginsCap;      // +0x0c
  char   pad10[8];          // +0x10
  void** mpBindersBegin;    // +0x18
  void** mpBindersEnd;      // +0x1c
  void** mpBindersCap;      // +0x20
  char   pad24[8];          // +0x24
  void*  mErrorCallback;    // +0x2c
  void*  mpCallbackContext; // +0x30
};

// ===========================================================================
// UI::StringMan
// ===========================================================================
struct IntrusiveListHead { void* mpNext; void* mpPrev; };

struct UIStringMan {
  virtual ~UIStringMan();
  int    mField04;         // +0x04
  void*  mpArg;            // +0x08
  IntrusiveListHead mList; // +0x0c
  UIStringMan(void* arg);
};
UIStringMan::UIStringMan(void* arg)
  : mpArg(arg), mField04(0) {
  mList.mpPrev = &mList;
  mList.mpNext = &mList;
}

// @ 0x00999790  intrusive-list teardown helper (this in ecx; list at +0xc)
void FUN_00999790(void* self) {
  IntrusiveListHead* head = (IntrusiveListHead*)((char*)self + 0xc);
  while (head->mpNext != head) {
    char* node = (char*)head->mpNext;
    char* obj = node - 0x14;
    ((IntrusiveListHead*)node)->mpPrev = head;
    head->mpNext = *(void**)node;
    if (node != (char*)head) {
      ((IntrusiveListHead*)node)->mpPrev = 0;
      *(void**)node = 0;
    }
    ((IUnknown32*)obj)->Release();
  }
}

// @ 0x00999850
UIStringMan::~UIStringMan() {
  FUN_00999790(this);
  FUN_00620230(&mList);
}

// @ 0x00999890
struct S99890Finder { char c[4]; unsigned* __thiscall find(void* tmp, unsigned* key); };   // 0xa23ef0
struct S99890 {
  char pad0[4];             // +0x00
  S99890Finder finder;      // +0x04
  unsigned** mpArray;       // +0x08
  uint mIndex;              // +0x0c
  bool f(unsigned* key);
};
bool S99890::f(unsigned* key) {
  S99890Finder* fp = &finder;
  unsigned* elem = mpArray[mIndex];
  unsigned tmp[2];
  unsigned* found = fp->find(tmp, key + 1);
  return *found != (unsigned)elem;
}

// @ 0x009997e0
StringTable::StringTable() {
  mpTableName = 0;
  mFirstKey.mInstance = 0; mFirstKey.mType = 0; mFirstKey.mGroup = 0;
  mLastKey.mInstance = 0; mLastKey.mType = 0; mLastKey.mGroup = 0;
}

// @ 0x009998d0  EA::StringMan::StringTableFilter deleting dtor
struct KeyFilter { virtual ~KeyFilter() {} };
struct HashSetU32 {                 // eastl::hash_set<uint> (nodes of 8 bytes)
  char alloc[4];
  void** mpBucketArray;             // +0x04 (in filter)
  uint  mnBucketCount;
  uint  mnElementCount;
  float mfMaxLoad, mfGrowth;
  uint  mnNextResize;
  void __thiscall DoFreeNodes(void** array, uint count) throw();         // 0x6b6570
  void* __thiscall DoInsertValue(void* out, const uint* v, char flag);   // 0x6758a0
  __forceinline ~HashSetU32() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1) operator_delete(mpBucketArray);
  }
};
struct StringTableFilter : KeyFilter {
  HashSetU32 mTypes;   // +0x04
  __forceinline ~StringTableFilter() {}
  StringTableFilter() {
    mTypes.mnBucketCount = 1;
    mTypes.mpBucketArray = (void**)0x154df28;
    mTypes.mnElementCount = 0;
    mTypes.mfMaxLoad = 1.0f;
    mTypes.mfGrowth = 2.0f;
    mTypes.mnNextResize = 0;
  }
};

// @ 0x009998d0 (scalar deleting dtor of StringTableFilter is emitted from the vtable)
static void* g_filterVtableAnchor() { return new StringTableFilter; }

struct IAlloc { virtual void v0(); virtual void v4(); virtual void v8(); virtual void Free(void* p, uint n); };
struct ListNode { ListNode* next; ListNode* prev; };
struct ListNodeObj : ListNode { IUnknown32* obj; };
struct RMgr {
  void* v0;
  char padx[0x4c];
};
extern void* FUN_00925cb0();     // ICoreAllocator::GetDefaultAllocator

// @ 0x00999930  EA::StringMan::Manager::Open
struct StringManMgr {
  int mRefCount;      // +4
  void* mpManager;    // +8
  void Open();
};
void StringManMgr::Open() {
  ListNode list1;
  list1.next = &list1; list1.prev = &list1;
  StringTableFilter filter;
  VF(mpManager, 0x4c, void(__thiscall*)(void*, ListNode*, int))(mpManager, &list1, -1);
  for (ListNode* n = list1.next; n != &list1; n = n->next) {
    IUnknown32* o = ((ListNodeObj*)n)->obj;
    if (VF(o, 0x18, int(__thiscall*)(void*))(o) == (int)0x8f6ad1c8) {
      uint types[16];
      uint cnt = VF(o, 0x2c, uint(__thiscall*)(void*, uint*, uint))(o, types, 0x10);
      for (uint i = 0; i < cnt; i++) {
        uint v = types[i];
        char flag = 0;
        char out[8];
        filter.mTypes.DoInsertValue(out, &v, flag);
      }
    }
  }
  struct { ListNode head; IAlloc* alloc; uint count; } list2;
  list2.head.next = &list2.head; list2.head.prev = &list2.head;
  list2.alloc = (IAlloc*)FUN_00925cb0();
  list2.count = 0;
  VF(mpManager, 0x5c, void(__thiscall*)(void*, ListNode*, int))(mpManager, &list2.head, 0);
  for (ListNode* w = list2.head.next; w != &list2.head; w = w->next) { }
  for (ListNode* n = list2.head.next; n != &list2.head; ) {
    ListNode* nx = n->next;
    list2.alloc->Free(n, 0xc);
    n = nx;
  }
  for (ListNode* n = list1.next; n != &list1; ) {
    ListNode* nx = n->next;
    operator_delete(n);
    n = nx;
  }
}

// @ 0x00999b20  StringTableXml::StrDup
wchar_t* StringTableXml::StrDup(const wchar_t* src) {
  if (src == 0) return 0;
  const wchar_t* p = src;
  do { } while (*p++);
  uint bytes = ((uint)(p - (src + 1)) * 2 + 9) & 0xfffffff8;
  void* obj = mAllocator.AllocInline(bytes);
  if (obj == 0) return 0;
  wchar_t* d = (wchar_t*)obj;
  while ((*d++ = *src++) != 0) {}
  return (wchar_t*)obj;
}

// @ 0x00999ba0  FactoryStringTableXml::GetSupportedTypes
int __stdcall FUN_00999ba0(uint* types, uint count) {
  if (count > 0) *types = 0xcf6c21b8;
  return 1;
}

// @ 0x00999ba0  FactoryStringTableXml::GetSupportedTypes
// @ 0x00999bc0  factory load callback
struct FactoryBase {
  virtual ~FactoryBase();
  FactoryBase() { _InterlockedExchange(&mRefCount, 0); }
  volatile long mRefCount;  // +0x04
};
struct ILoadSrc {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual uint GetOffset(uint);   // +0x10 (caller-cleans in the original; not reproducible)
  virtual uint GetBase(uint);     // +0x14 (caller-cleans in the original; not reproducible)
};
struct LoadCallbackHolder {
  char pad[8];
  void* mpCallback;   // +0x08
  uint  mArg;         // +0x0c
  void Invoke(ILoadSrc* src, uint extra);
};
void LoadCallbackHolder::Invoke(ILoadSrc* src, uint extra) {
  if (mpCallback != 0) {
    uint base = src->GetBase(mArg);
    uint off = src->GetOffset(base);
    ((void (__cdecl*)(uint, uint))mpCallback)(extra, off);
  }
}

// @ 0x00999c20  FactoryStringTableXml::FactoryStringTableXml
struct FactoryStringTableXml : FactoryBase {
  void* mErrorCallback;    // +0x08
  void* mpCallbackContext; // +0x0c
  FactoryStringTableXml();
};
FactoryStringTableXml::FactoryStringTableXml() { mErrorCallback = 0; mpCallbackContext = 0; }

// @ 0x00999c50  StringTableXml::StringTableXml
StringTableXml::StringTableXml(const Key& k, const wchar_t* name)
  : mAllocator(0, -1, 0, 0, 0) {
  mFirstKey.mInstance = k.mInstance;
  mFirstKey.mType = k.mType;
  mFirstKey.mGroup = k.mGroup;
  mFirstKey.mType = 0x4f72d78a;
  mAllocator.Init(0, 0, 0, 0, 0);
  mpTableName = StrDup(name);
  mAllocator.AllocateNewBlock(0);
}

// @ 0x00999ce0  StringTableXml deleting dtor
StringTableXml::~StringTableXml() {
  mAllocator.Reset();
}

// @ 0x00999d30  FactoryStringTableXml::CreateResource
struct FactoryStringTableXml2 : FactoryBase {
  void* mErrorCallback;    // +0x08
  void* mpCallbackContext; // +0x0c
  bool CreateResource(void* src, void** out, const wchar_t* name, uint a4);
};
bool FactoryStringTableXml2::CreateResource(void* src, void** out, const wchar_t* name, uint a4) {
  StringTableXml* t = new("UTFWin/StringTableXml", 0, 0, 0, 0)
    StringTableXml(*VF(src, 0x10, Key*(__thiscall*)(void*))(src), name);
  VF(t, 0, void(__thiscall*)(void*))(t);
  char ok = VF(this, 0x24, char(__thiscall*)(void*, void*, void*, const wchar_t*, uint))(this, src, t, name, a4);
  if (ok) {
    t->mLastKey = t->mFirstKey;
    t->mLastKey.mInstance += (uint)(t->mStrings.mpStringEnd - t->mStrings.mpStringBegin);
    *out = t;
    return true;
  }
  VF(t, 4, void(__thiscall*)(void*))(t);
  return false;
}

// @ 0x00999dd0  eastl::vector<T*,sp_vector_allocator>::insert(position, n, value)
void SpVec::insert_n(void** position, uint n, void** value) {
  if ((uint)(c - e) >= n) {
    if (n > 0) {
      void* temp = *value;
      void** oldEnd = e;
      uint nExtra = (uint)(oldEnd - position);
      if (n < nExtra) {
        void** first = oldEnd - n;
        FUN_011e0744(oldEnd, first, (uint)((char*)oldEnd - (char*)first));
        e = e + n;
        memmove((char*)oldEnd - ((char*)first - (char*)position), position, (uint)((char*)first - (char*)position));
        void** stop = position + n;
        if (position != stop) {
          do { *position++ = temp; } while (position != stop);
        }
      } else {
        uint k = n - nExtra;
        void** q = oldEnd;
        for (uint i = k; i != 0; i--)
          *q++ = temp;
        e = e + k;
        FUN_011e0744(e, position, (uint)((char*)oldEnd - (char*)position));
        e = e + nExtra;
        if (position != oldEnd) {
          do { *position++ = temp; } while (position != oldEnd);
        }
      }
    }
  } else {
    uint oldSize = (uint)(e - b);
    uint grow = oldSize * 2;
    if (oldSize == 0)
      grow = 1;
    uint newCap = oldSize + n;
    if (newCap < grow)
      newCap = grow;
    void** nb = 0;
    if (newCap != 0)
      nb = (void**)operator_new(newCap * 4, "EASTL", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    uint pre = (uint)((char*)position - (char*)b);
    void** d = (void**)FUN_011e0744(nb, b, pre);
    d = (void**)((char*)d + (pre >> 2) * 4);
    void* temp = *value;
    void** f = d;
    for (uint i = n; i != 0; i--)
      *f++ = temp;
    d = d + n;
    uint post = (uint)((char*)e - (char*)position);
    void** r = (void**)FUN_011e0744(d, position, post);
    void** newEnd = (void**)((char*)r + (post >> 2) * 4);
    if (b != 0 && ((int*)b)[-1] != 0)
      operator_delete(b);
    b = nb;
    e = newEnd;
    c = nb + newCap;
  }
}

// @ 0x0099a010  StringTableXml::SetString
void StringTableXml::SetString(uint index, const wchar_t* str) {
  if ((uint)(mStrings.mpStringEnd - mStrings.mpStringBegin) < index + 1)
    ((PtrVector*)&mStrings.mpStringBegin)->resize(index + 1);
  wchar_t** dst = (wchar_t**)(mStrings.mpStringBegin + index);
  *dst = StrDup(str);
}

// ===========================================================================
// EA::UTFWinTools::SerCollection
// ===========================================================================
struct SerScope {                 // eastl::hashtable member (alloc, buckets, count, elems, policy)
  char  alloc[4];
  void** mpBucketArray;   // +0x04
  uint  mnBucketCount;    // +0x08
  uint  mnElementCount;   // +0x0c
  float mfMaxLoad, mfGrowth;
  uint  mnNextResize;
  char  pad[4];
  void __thiscall DoFreeNodes(void** array, uint count) throw();   // 0x961d60
  void clear() { DoFreeNodes(mpBucketArray, mnBucketCount); mnElementCount = 0; }
  void destroy() {
    clear();
    if (mnBucketCount > 1) operator_delete(mpBucketArray);
  }
};

struct WStrRaw { wchar_t* b; wchar_t* e; wchar_t* c; };

struct IListener {
  virtual void AddRef();
  virtual void Release();
  virtual void v08();
  virtual void OnReload();
  virtual void ClearObjects() throw();
  virtual void v14();
};

extern wchar_t g_emptyWStr[2];     // 0x1667bac (empty string literal storage)
struct SpVecDtor { void __thiscall Destroy(); };   // 0x7a41a0
extern void __fastcall FUN_00999050_(char*) throw();       // SerCollection::ClearObjects helper (0x999050)
extern void __fastcall FUN_00999000_(char*) throw();       // SerCollection::RemoveAll (0x999000)
struct WStrOps {
  void __thiscall DeallocateSelf();     // 0x933960
  void __thiscall Assign(void* other);  // 0x57cb60
};

struct ISvcAutoUpdate {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void Register(Key* k, void* listener) throw();    // +0x10
  virtual void Unregister(Key* k, void* listener) throw();  // +0x14
};

struct IClearSlot {
  virtual void s0() throw() = 0; virtual void s1() throw() = 0; virtual void s2() throw() = 0; virtual void s3() throw() = 0;
  virtual void Clear() throw() = 0;     // +0x10
};

struct SerCollection : IListener {
  SerializationService* mService;   // +0x04
  ISvcAutoUpdate*       mAutoUpdate;// +0x08
  Key                   mKey;       // +0x0c
  uint                  mSerFlags;  // +0x18
  SerScope              mImports;   // +0x1c
  SerScope              mExports;   // +0x3c
  SpVec                 mObjects;   // +0x5c
  char                  pad6c[4];   // +0x6c
  WStrRaw               mName;      // +0x70
  ~SerCollection();
  void Shutdown();
  bool Reload();
};

// @ 0x00999110
SerCollection::~SerCollection() {
  if (mAutoUpdate != 0) {
    mAutoUpdate->Unregister(&mKey, this);
    mAutoUpdate = 0;
  }
  ((IClearSlot*)(void*)this)->Clear();
  FUN_00999000_((char*)this);
  if (((int)((char*)mName.c - (char*)mName.b) & -2) > 2 && mName.b != 0)
    operator_delete(mName.b);
  if (mObjects.b != 0 && ((int*)mObjects.b)[-1] != 0)
    operator_delete(mObjects.b);
  mExports.destroy();
  mImports.destroy();
}

// @ 0x009991e0
void SerCollection::Shutdown() {
  if (mAutoUpdate != 0) {
    mAutoUpdate->Unregister(&mKey, this);
    mAutoUpdate = 0;
  }
  VF(this, 0x10, void(__thiscall*)(void*))(this);
  FUN_00999000_((char*)this);
  mImports.clear();
  mExports.clear();
}

// @ 0x00999250
bool SerCollection::Reload() {
  if (mService != 0) {
    SpVec vec;
    vec.b = 0; vec.e = 0; vec.c = 0;
    mObjects.swap(&vec);
    void* mgr = FUN_008de1a0();
    if (mgr == 0)
      mService->Callback(0x4fbd0001);
    void* src = VF(mgr, 0x58, void*(__thiscall*)(void*, Key*))(mgr, &mKey);
    if (src == 0) {
      mService->Callback(0x4fbd0002);
    } else {
      void* stream = 0;
      char ok = VF(src, 0x34, char(__thiscall*)(void*, Key*, void**, int, int, int, int))(src, &mKey, &stream, 1, 6, 1, 0);
      if (ok == 0) {
        mService->Callback(0x4fbd0003);
      } else {
        void* reader = VF(stream, 0x18, void*(__thiscall*)(void*))(stream);
        if (reader == 0) {
          mService->Callback(0x4fbd0004);
          VF(stream, 0x24, void(__thiscall*)(void*))(stream);
        } else {
          WStrRaw str;
          str.b = g_emptyWStr;
          str.e = g_emptyWStr;
          str.c = g_emptyWStr + 1;
          VF(mgr, 0x7c, void(__thiscall*)(void*, Key*, WStrRaw*))(mgr, &mKey, &str);
          if (str.b != str.e)
            ((WStrOps*)&mName)->Assign(&str);
          int r = VF(mService, 0x18, int(__thiscall*)(void*, void*, wchar_t*, void*, uint))(mService, reader, mName.b, this, mSerFlags);
          if (r == 0) {
            VF(stream, 0x24, void(__thiscall*)(void*))(stream);
            mObjects.swap(&vec);
            FUN_00999050_((char*)this);
            mObjects.swap(&vec);
            OnReload();
            if (mSerFlags & 1) {
              mAutoUpdate = VF(mService, 0x10, ISvcAutoUpdate*(__thiscall*)(void*, uint))(mService, 0x2fbf2058);
              if (mAutoUpdate != 0)
                mAutoUpdate->Register(&mKey, this);
            }
            ((WStrOps*)&str)->DeallocateSelf();
            if (stream != 0)
              VF(stream, 8, void(__thiscall*)(void*))(stream);
            ((SpVecDtor*)&vec)->Destroy();
            return true;
          }
          ((WStrOps*)&str)->DeallocateSelf();
          VF(stream, 0x24, void(__thiscall*)(void*))(stream);
        }
        if (stream != 0)
          VF(stream, 8, void(__thiscall*)(void*))(stream);
      }
    }
    if (vec.b != 0 && ((int*)vec.b)[-1] != 0)
      operator_delete(vec.b);
  }
  return false;
}
