// src/game/UTFSpore_Win32/SerializationService.cpp -- migrated from slice(s) s00999110 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/SerializationService.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinTools/SerializationService.h"
#include "EA/UTFWinTools/ISerAutoUpdate.h"
#include "EA/ResourceMan/Key.h"
#include "EA/ResourceMan/KeyFilter.h"
#include "EA/UTFWinTools/SerCollection.h"
#include "EA/UTFWinTools/SerScope.h"
#include "EA/Allocator/StackAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete(void*) throw();   // 0x00f47380
extern void** FUN_00b6f4f0(void*, void*, void*, void*);
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk, returns dst
#include <intrin.h>
#include <string.h>
#include <new>
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s00999110 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
extern "C" void  operator_delete(void*) throw();   // 0x00f47380
extern void** FUN_00b6f4f0(void*, void*, void*, void*);
struct PluginVecRaw { void FUN_004b5440(); };   // eastl::vector<T*> dtor body, thiscall
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
extern "C" void* FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy thunk, returns dst
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
struct RcVecIns {                    // eastl::vector<AutoRefCount<T>, sp_vector_allocator>
  void __thiscall DoInsertValue(void** pos, IUnknown32** v);   // 0x004b6000
};
// ---- items of slice s00999110 end

// @ 0x009994a0
uint SerializationService::Read(uint a, uint b, uint c, uint d)
{
  (void)d;
  void* p = VF(this, 0x10, void*(__thiscall*)(void*, uint))(this, 0xafc46457);
  if (p != 0)
    return VF(p, 0x10, uint(__thiscall*)(void*, uint, uint, uint, void*, void*, void*))
      (p, a, b, c, &mBinders.mpBegin, mErrorCallback, mpCallbackContext);
  return 0x4fc40001;
}

// @ 0x009994f0
void* SerializationService::GetReader(void* arg)
{
  void* result = 0;
  void** it = mPlugins.mpBegin;
  void** end = mPlugins.mpEnd;
  if (it != end) {
    do {
      if (result) break;
      result = ((IUnknown32*)*it)->Cast((uint)arg);
      ++it;
    } while (it != end);
  }
  return result;
}

// @ 0x00999550
SerializationService::~SerializationService()
{
}

// @ 0x00999590
void SerializationService::AddPlugin(IUnknown32* obj)
{
  IUnknown32* tmp = obj;                       // AutoRefCount temporary
  if (tmp) tmp->AddRef();
  void** p = mPlugins.mpEnd;
  if (p < mPlugins.mpCap) {
    mPlugins.mpEnd = p + 1;
    if (p) {
      *p = tmp;                                // AutoRefCount copy-construct
      if (tmp) tmp->AddRef();
    }
  } else {
    ((RcVecIns*)&mPlugins.mpBegin)->DoInsertValue(p, &tmp);
  }
  if (tmp) tmp->Release();
  if (obj) {
    void* casted = obj->Cast(0x4fc56322);
    if (casted)
      ((SpVec*)&mBinders.mpBegin)->push_back(casted);
  }
}

// @ 0x00999640
void SerializationService::RemovePlugin(IUnknown32* obj)
{
  RcVec* plugins = (RcVec*)&mPlugins.mpBegin;
  SpVec* binders = (SpVec*)&mBinders.mpBegin;
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

// @ 0x00999720
void SerializationService::ClearAll()
{
  ((SpVec*)&mBinders.mpBegin)->clear_all();
  RcVec* plugins = (RcVec*)&mPlugins.mpBegin;
  plugins->erase(plugins->b, plugins->e);
}
