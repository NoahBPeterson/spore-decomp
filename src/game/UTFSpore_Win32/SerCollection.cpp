// src/game/UTFSpore_Win32/SerCollection.cpp -- migrated from slice(s) s00999110, s00997f50 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/SerCollection.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Thread/Mutex.h"
#include "EA/UTFWinTools/RWTextureFactory.h"
#include "EA/UTFWinTools/SerCollection.h"
#include "EA/UTFWinTools/SerScope.h"
#include "EA/ResourceMan/Key.h"
#include "EA/UTFWinTools/ISerAutoUpdate.h"
#include "EA/ResourceMan/KeyFilter.h"
#include "EA/UTFWinTools/SerializationService.h"
#include "EA/Allocator/StackAllocator.h"
#include <intrin.h>
#include <string.h>
#include <new>

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void FUN_011e0744_(void* a, void* b, int c);
extern void* g_SerCollection_vftable[];       // 0x1446abc
extern void* g_hashEmptyBucketArray[];        // 0x154df28 (eastl gpEmptyBucketArray)
extern const wchar_t g_emptyWString[];        // 0x13fe144
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---- items of slice s00997f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_011e0744_(void* a, void* b, int c);
extern void* g_SerCollection_vftable[];       // 0x1446abc
extern void* g_hashEmptyBucketArray[];        // 0x154df28 (eastl gpEmptyBucketArray)
extern const wchar_t g_emptyWString[];        // 0x13fe144
struct WString16b {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    void FUN_00579a90(const wchar_t* s);      // basic_string<wchar_t>::RangeInitialize, thiscall
};
struct SerRehashPolicy {                       // eastl::prime_rehash_policy
    float    mfMaxLoadFactor;
    float    mfGrowthFactor;
    unsigned mnNextResize;
    SerRehashPolicy() : mfMaxLoadFactor(1.0f), mfGrowthFactor(2.0f), mnNextResize(0) {}
};
struct SerHashtable {                         // eastl::hashtable<uint, AutoRefCount<...>> (0x20 bytes)
    int             mHashObj;                 // +0 (empty functor slot)
    void**          mpBucketArray;            // +4
    unsigned        mnBucketCount;            // +8
    unsigned        mnElementCount;           // +0xc
    SerRehashPolicy mRehashPolicy;            // +0x10
    int             mAllocator;               // +0x1c
    SerHashtable() : mnBucketCount(0), mnElementCount(0) { reset_lose_memory(); }
    void reset_lose_memory() {
        mnBucketCount = 1;
        mpBucketArray = g_hashEmptyBucketArray;
        mnElementCount = 0;
        mRehashPolicy.mnNextResize = 0;
    }
};
struct SerPtrVector {                         // eastl::vector<T*> (0x10 bytes)
    void** mpBegin; void** mpEnd; void** mpCapacity; int mAllocator;
    SerPtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};
struct SerWString : WString16b {
    SerWString() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; FUN_00579a90(g_emptyWString); }
};
struct SerKey {
    unsigned mInstance, mType, mGroup;
    SerKey() : mInstance(0), mType(0), mGroup(0) {}
};
struct SerCollection {
    void**       mpVtbl;                      // +0
    void*        mService;                    // +4
    void*        mAutoUpdate;                 // +8
    SerKey       mKey;                        // +0xc
    unsigned     mSerFlags;                   // +0x18
    SerHashtable mImports;                    // +0x1c
    SerHashtable mExports;                    // +0x3c
    SerPtrVector mList;                       // +0x5c
    int          mPad6c;                      // +0x6c
    SerWString   mName;                       // +0x70
    SerCollection();
};
// ---- items of slice s00997f50 end

// ---- items of slice s00999110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  operator_delete(void*) throw();   // 0x00f47380
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk, returns dst
extern void* FUN_008de1a0();                                             // service-manager singleton accessor
extern wchar_t g_emptyWStr[2];     // 0x1667bac (empty string literal storage)
extern void __fastcall FUN_00999050_(char*) throw();       // SerCollection::ClearObjects helper (0x999050)
extern void __fastcall FUN_00999000_(char*) throw();       // SerCollection::RemoveAll (0x999000)
#pragma intrinsic(_InterlockedExchange)
typedef unsigned int uint;
struct PluginVecRaw { void FUN_004b5440(); };   // eastl::vector<T*> dtor body, thiscall
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
struct Key { uint mInstance; uint mType; uint mGroup; };
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
struct SSPluginVec {        // eastl::vector<IUnknown32*> (refcounted plugins)
  void** mpBegin;
  void** mpEnd;
  void** mpCap;
  char   mAlloc[8];
  SSPluginVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
  ~SSPluginVec() { ((PluginVecRaw*)this)->FUN_004b5440(); }
};
struct SSBinderVec {        // vector of binders; buffer freed only when its header word is set
  void** mpBegin;
  void** mpEnd;
  void** mpCap;
  char   mAlloc[8];
  SSBinderVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
  ~SSBinderVec() {
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator_delete(mpBegin);
  }
};
struct SerializationService {
  virtual ~SerializationService();
  SSPluginVec mPlugins;     // +0x04 (begin/end/cap + 8-byte allocator)
  SSBinderVec mBinders;     // +0x18
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
  void   AddPlugin(IUnknown32* obj);
  void   RemovePlugin(IUnknown32* obj);
  void   ClearAll();
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
struct SpVecDtor {
  void __thiscall Destroy();   // 0x007a41a0
};
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
struct SerCollection_s0099_9110 : IListener {
  SerializationService* mService;   // +0x04
  ISvcAutoUpdate*       mAutoUpdate;// +0x08
  Key                   mKey;       // +0x0c
  uint                  mSerFlags;  // +0x18
  SerScope              mImports;   // +0x1c
  SerScope              mExports;   // +0x3c
  SpVec                 mObjects;   // +0x5c
  char                  pad6c[4];   // +0x6c
  WStrRaw               mName;      // +0x70
  ~SerCollection_s0099_9110();
  void Shutdown();  // 0x009991e0 (SerCollection::Shutdown)
  bool Reload();  // 0x00999250 (SerCollection::Reload)
};
// ---- items of slice s00999110 end

// @ 0x00999000
void __fastcall SerCollection_RemoveAll(char* self)
{
    char* end = *(char**)(self + 0x60);
    for (char* p = *(char**)(self + 0x5c); p != end; p += 4) {
        void* o = *(void**)p;
        (*(void(__thiscall**)(void*))((char*)*(void**)o + 4))(o);
    }
    char* a = *(char**)(self + 0x5c);
    char* b = *(char**)(self + 0x60);
    FUN_011e0744_(a, b, (int)b - (int)b);
    int n = (int)(b - a) >> 2;
    n = -n;
    n = n + n;
    n = n + n;
    *(int*)(self + 0x60) = (int)b + n;
}

// @ 0x00999050
void __fastcall FUN_00999050(char* self)
{
    char* au = *(char**)(self + 8);
    if (au) {
        (*(void(__thiscall**)(char*, char*, char*))((char*)*(void**)au + 0x14))(au, self + 0xc, self);
        *(unsigned*)(self + 8) = 0;
    }
    (*(void(__thiscall**)(char*))((char*)*(void**)self + 0x10))(self);
    SerCollection_RemoveAll(self);
}

// @ 0x00999080
SerCollection::SerCollection()
: mpVtbl(g_SerCollection_vftable), mService(0), mAutoUpdate(0), mSerFlags(0)
{
}

// @ 0x00999110
SerCollection_s0099_9110::~SerCollection_s0099_9110()
{
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
void SerCollection_s0099_9110::Shutdown()
{
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
bool SerCollection_s0099_9110::Reload()
{
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
