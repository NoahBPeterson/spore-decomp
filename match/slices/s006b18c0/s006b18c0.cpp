// Slice s006b18c0: SP save-area subsystem and App::LRUCache manager methods.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS-.
#include "s006b18c0.h"
#include <intrin.h>
#include <wchar.h>
#pragma intrinsic(_ReadWriteBarrier)

struct EaHeader { uint32_t mRefCount; };            // 4 bytes in front of every EA allocation
static inline void FreeOwned(void* p) {
  if (p != 0 && ((EaHeader*)p)[-1].mRefCount != 0) EAFree(p);
}

// @ 0x6b1d40
void SetSaveAreaFlag(uint8_t b) {
  g_16046d8 = b;
}

// @ 0x6b1f60
bool SP_IsSaveArea(void* p) {
  uint32_t* it = g_saveAreas.root;
  while (it != &g_saveAreas.head) {
    if (it[5] == (uint32_t)p) {
      return true;
    }
    it = (uint32_t*)RBTreeIncrement(it);
  }
  return false;
}

// @ 0x6b1f90
void* SP_GetSaveArea(uint32_t key) {
  uint32_t* out;
  g_saveAreas.find((void**)&out, &key);
  if (out != &g_saveAreas.head) {
    return (void*)out[5];
  }
  return 0;
}

// @ 0x6b1fc0
void SP_FlushAllSaveAreas() {
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[6];
    if (o != 0) {
      o->Call24();
    }
  }
}

// @ 0x6b2350
void SP_SomethingAllSaveAreas() {
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[5];
    o->Call24();
  }
}

// @ 0x6b1d50
void SP_SaveResource(void* p, uint32_t val, char flag) {
  if (*(uint32_t*)((uint32_t)p + 0xc) == 0xb1b104) {
    PropertyMgr4* pm = SP_PropertyManager();
    pm->Call34(p, *(void**)((uint32_t)p + 8), *(void**)((uint32_t)p + 0x10));
  } else {
    FUN_006acfe0((void*)((uint32_t)p + 8), p);
  }
  if (flag != 0) {
    FUN_006b4b60(p, (void*)val, 0, 0);
    return;
  }
  ResourceMgr4* rm = ResourceMan_GetManager();
  rm->Call20(p, 0, (void*)val, 0, 0);
}

// @ 0x6b2000
bool FUN_006b2000(void* p, char flag) {
  uint32_t key = 0x11ac19c;
  uint32_t* out;
  g_saveAreas.find((void**)&out, &key);
  if (out == &g_saveAreas.head) {
    return false;
  }
  SaveObj* o = (SaveObj*)out[5];
  if (o == 0) {
    return false;
  }
  FUN_006acfe0((void*)((uint32_t)p + 8), p);
  if (flag != 0) {
    return FUN_006b4b60(p, o, 0, 0) != 0;
  }
  ResourceMgr4* rm = ResourceMan_GetManager();
  return rm->Call20(p, 0, o, 0, 0) != 0;
}

// @ 0x6b2090
bool FUN_006b2090(void* p, char flag) {
  uint32_t key = 0x11ac1ac;
  uint32_t* out;
  g_saveAreas.find((void**)&out, &key);
  if (out == &g_saveAreas.head) {
    return false;
  }
  SaveObj* o = (SaveObj*)out[5];
  if (o == 0) {
    return false;
  }
  if (flag != 0) {
    return FUN_006b4b60(p, o, 0, 0) != 0;
  }
  ResourceMgr4* rm = ResourceMan_GetManager();
  return rm->Call20(p, 0, o, 0, 0) != 0;
}

// @ 0x6b22a0
void* SP_UpdateSaveAreas(void* p) {
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[5];
    if (o->Call34(p, 0, (void*)1, (void*)6, (void*)1, 0)) {
      return o;
    }
  }
  return 0;
}

// @ 0x6b22f0
void* FUN_006b22f0(void* p) {
  ResourceMgr4* rm = ResourceMan_GetManager();
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[5];
    if (rm->Call30(p, 0, o) != 0) {
      return o;
    }
  }
  return 0;
}

// @ 0x6b1dc0
RefPair* RefPair::Ctor(RefA* x, RefB* y) {
  a = x;
  if (x != 0) {
    x->ref.AddRef();
  }
  b = y;
  if (y != 0) {
    y->AddRef();
  }
  return this;
}

// @ 0x6b1e20
void RefPair::Dtor() {
  if (b != 0) {
    b->Release();
  }
  if (a != 0) {
    a->ref.Release();
  }
  _ReadWriteBarrier();
}

// @ 0x6b1e90
RefPair* RefPair::CtorCopy(const RefPair* o) {
  a = o->a;
  if (a != 0) {
    a->ref.AddRef();
  }
  b = o->b;
  if (b != 0) {
    b->AddRef();
  }
  return this;
}

// @ 0x6b1ef0
RefPair* RefPair::Assign(const RefPair* o) {
  if (o->a != a) {
    if (o->a != 0) {
      o->a->ref.AddRef();
    }
    RefA* old = a;
    a = o->a;
    if (old != 0) {
      old->ref.Release();
    }
  }
  if (o->b != b) {
    if (o->b != 0) {
      o->b->AddRef();
    }
    RefB* old = b;
    b = o->b;
    if (old != 0) {
      old->Release();
    }
  }
  return this;
}

// @ 0x6b18c0
void CacheMgr::Notify(CacheEvent* ev) {
  uint32_t* p = (uint32_t*)ev + 1;
  Key8 key;
  key.lo = p[0];
  key.hi = (p[2] & 0xc0000000u) == 0x40000000u ? (p[2] & 0xc0ff0000u) : 0;
  AreaMapNode* node;
  map.find((void**)&node, &key);
  ListNode* it = &list;
  if (node != (AreaMapNode*)&map.head) {
    it = (ListNode*)node->mpValue;
  }
  if (ev->op == 0) {
    if (it != &list) {
      Touch(it);
    }
    return;
  }
  if (ev->op == 1) {
    if (it == &list) {
      ListNode* added;
      it = *(ListNode**)InsertKey((void**)&added, key.lo, key.hi);
    } else {
      Touch(it);
    }
    AreaRec* area = it == &list ? 0 : it->mpValue;
    m40 += area->AddFromEvent((int*)p, ev->extra);
    return;
  }
  if (ev->op == 2 && it != &list) {
    m40 += it->mpValue->AddFromStream((int*)p);
  }
}

// @ 0x6b19e0
void CacheMgr::ReleaseArea(ListNode* it) {
  AreaRec* area;
  if (it == &list) {
    area = 0;
  } else {
    area = it->mpValue;
  }
  Key8 key;
  key.hi = area->m04;
  key.lo = area->m00;
  m40 -= area->SizeTaken(m0c);
  AreaMapNode* node;
  map.find((void**)&node, &key);
  if (node != (AreaMapNode*)&map.head) {
    --map.size;
    RBTreeIncrement(node);
    RBTreeErase(node, &map.head);
    EAFree(node);
  }
  ListNode* p = it->mpNext->mpPrev;
  p->mpPrev->mpNext = p->mpNext;
  p->mpNext->mpPrev = p->mpPrev;
  EAFree(p);
  FreeOwned(area->mpBuf);
  EAFree(area);
  mb15 = 1;
}

// @ 0x6b1ab0
void CacheMgr::Destructor() {
  vt0 = (uint32_t)&gVtblCacheMgrA;
  vt1 = (uint32_t)&gVtblCacheMgrB;
  if (mb14 != 0) {
    Shutdown();
  }
  sub.Free();
  if (job != 0) {
    job->Release();
  }
  if (stream != 0) {
    ((StreamVt*)stream)->Release();
  }
  ListNode* it = list.mpNext;
  while (it != &list) {
    ListNode* next = it->mpNext;
    EAFree(it);
    it = next;
  }
  map.Clear(map.m0c);
  if (mpOwner != 0) {
    ((OwnerObj*)mpOwner)->ref.Release();
  }
  vt0 = (uint32_t)&gVtblCacheMgrBaseA;
  vt1 = (uint32_t)&gVtblCacheMgrBaseB;
}

// @ 0x6b1b80
void CacheMgr::Update() {
  CacheEvent ev;
  ev.lo = 0;
  ev.m08 = 0;
  ev.hi = 0;
  if (sub.Poll(&ev)) {
    do {
      Notify(&ev);
    } while (sub.Poll(&ev));
  }
  int limit = g_pDirectPropertyList->GetIntProperty(m10);
  mLimit = __allmul(limit, limit >> 31, 0x100000, 0);
  if (mLimit != 0) {
    do {
      if (m40 <= mLimit) {
        break;
      }
      if (list.mpNext == &list) {
        m40 = 0;
      } else {
        ListNode* it = list.mpNext;
        if (it->mpValue->CanRelease(m0c)) {
          Touch(it);
          break;
        }
        ReleaseArea(it);
      }
    } while (mLimit != 0);
  }
  Tracer* tracer = FUN_0068f4d0();
  tracer->Enter();
  try {
    if (job != 0) {
      int status = job->ContinueJob();
      if ((unsigned)(status - 7) <= 1) {
        Job* j = job;
        if (j != 0) {
          job = 0;
          j->Release();
        }
      }
    }
    if (--m50 == 0) {
      m50 = 9000;
      if (mb15 != 0 && job == 0) {
        Job** slot = &job;
        Tracer* t2 = FUN_0068f4d0();
        Job* j = job;
        if (j != 0) {
          job = 0;
          j->Release();
        }
        if (t2->CheckJob(slot)) {
          StartJob();
          Job* nj = job;
          nj->mpFunc = (void*)&gJobFunc;
          nj->mpOwner = this;
          job->m18 = 4;
          job->GetStatus();
          mb15 = 0;
        }
      }
    }
  } catch (...) {
  }
  tracer->Exit();
}

// ---- extension-mapping import (property file reader) ----
struct Variant {
  void*    mpData;      // +0x00 array payload
  uint32_t m04;         // +0x04
  uint32_t m08;         // +0x08 array length in 0x10-byte units
  uint32_t m0c;         // +0x0c
  uint16_t m10;         // +0x10 type flags (0x30 = external array)
  uint16_t m12;         // +0x12 inline count/flag
  uint32_t m14;         // +0x14
};
struct ExtEntry {                             // 0x20-byte map entry inside the variant array
  const wchar_t* mpBegin;   // +0x00
  const wchar_t* mpEnd;     // +0x04
  uint32_t m08;             // +0x08
  uint32_t m0c;             // +0x0c
  uint32_t mValue;          // +0x10
  uint32_t m14;             // +0x14
  uint32_t m18;             // +0x18
  uint32_t m1c;             // +0x1c
};
struct IConfigFile {
  virtual void s00(); virtual void Release();                    // +0x04
  virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14();
  virtual void s18();
  virtual bool HasSection(uint32_t key);                         // +0x1c
  virtual void s20(); virtual void s24();
  virtual Variant* GetVariant(uint32_t key);                     // +0x28
};
struct IExtMapSink {
  virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
  virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
  virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
  virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
  virtual void s40(); virtual void s44(); virtual void s48();
  virtual void AddMapping(uint32_t value, unsigned long number);  // +0x4c
  virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
  virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
  virtual void SetKey(uint32_t key);                             // +0x70
};
struct IPropMgrOpen {
  virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
  virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
  virtual void s20(); virtual void s24(); virtual void s28();
  virtual bool Open(void* source, uint32_t section, IConfigFile** out);   // +0x2c
};
extern "C" void* VariantTypeTraits_Key_GetTPTR(Variant* v);      // 0x00454b10

// @ 0x6b2110
void ReadExtensionMappingsFromPropFile(uint32_t propKey, IExtMapSink* sink) {
  IConfigFile* file = 0;
  IPropMgrOpen* pm = (IPropMgrOpen*)SP_PropertyManager();
  if (pm != 0) {
    IConfigFile* old = file;
    if (old != 0) {
      file = 0;
      old->Release();
    }
    if (pm->Open((void*)propKey, 0x1c7ac81, &file)) {
      if (file->HasSection(0x4334f33)) {
        Variant* v = file->GetVariant(0x4334f33);
        uint32_t count;
        ExtEntry* begin;
        if ((v->m10 & 0x30) != 0) {
          count = v->m08;
        } else {
          count = 0;
          if (v->m12 != 0) {
            count = 1;
          }
        }
        count &= 0xfffffffeu;
        if ((v->m10 & 0x30) != 0) {
          begin = (ExtEntry*)v->mpData;
        } else {
          begin = v->m12 != 0 ? (ExtEntry*)v : 0;
        }
        ExtEntry* last = (ExtEntry*)((char*)begin + count * 0x10);
        for (ExtEntry* it = begin; it < last; ++it) {
          const wchar_t* s = it->mpBegin;
          const wchar_t* e = it->mpEnd;
          wchar_t* endptr;
          unsigned long number = wcstoul(s, &endptr, 16);
          if (endptr - s == e - s) {
            sink->AddMapping(it->mValue, number);
          }
        }
      }
      if (file->HasSection(0x4334f34)) {
        Variant* v = file->GetVariant(0x4334f34);
        uint32_t* key = (uint32_t*)VariantTypeTraits_Key_GetTPTR(v);
        Key12 copy;
        copy.a = key[0];
        copy.b = key[1];
        sink->SetKey(key[2]);
      }
    }
  }
  if (file != 0) {
    file->Release();
  }
}

// ---- 12-byte element vector returned by the save-area object's collect slot ----
struct Elem12 { uint32_t a, b, c; };
struct Vec12 { Elem12* mpBegin; Elem12* mpEnd; Elem12* mpCap; };

// save-area object: slot +0x24 idle, +0x30 collect, +0x34 query, +0x40 element dtor
struct SaveAreaObj {
  virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
  virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
  virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
  virtual void Collect(Vec12* out, void* unused);   // +0x30
  virtual void s34(); virtual void s38(); virtual void s3c();
  virtual void DestroyElem(Elem12* it);            // +0x40
};


// @ 0x6b2400
void FUN_006b2400(uint32_t key) {
  uint32_t* out;
  g_saveAreas.find((void**)&out, &key);
  if (out == &g_saveAreas.head) {
    return;
  }
  SaveAreaObj* o = (SaveAreaObj*)out[5];
  if (o == 0) {
    return;
  }
  Vec12 v;
  v.mpBegin = 0;
  v.mpEnd = 0;
  v.mpCap = 0;
  try {
    o->Collect(&v, 0);
    for (Elem12* it = v.mpBegin; it != v.mpEnd; ++it) {
      o->DestroyElem(it);
    }
  } catch (...) {
    FreeOwned(v.mpBegin);
    throw;
  }
  FreeOwned(v.mpBegin);
}

// ---- directory save object created by SP::CreateDirectorySave ----
struct WString {                             // eastl::wstring (0xc bytes)
  wchar_t* mpBegin;   // +0x00
  wchar_t* mpEnd;     // +0x04
  wchar_t* mpCap;     // +0x08
  WString(const wchar_t* s);                 // 0x00579a90 range_initialize
  void Append(const wchar_t* first, const wchar_t* last);   // 0x00429580
};

struct DatabaseDirectoryFiles {
  virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
  virtual void s10(); virtual void s14(); virtual void s18();
  virtual bool Configure(int a, int b, int c);   // +0x18
  virtual void Shutdown();                       // +0x1c
  virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
  virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
  virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
  virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
  virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
  virtual void SetSink(void* sink);              // +0x70
  OwnerRef ref;                                  // +0x04 refcounted handle
};

extern "C" const wchar_t* GetDirFromID(uint32_t id);                    // 0x006886b0
extern "C" void* ZoneObject_new(int size, const char* area, int a, int b, int c, int d);  // 0x00926020
extern "C" DatabaseDirectoryFiles* DatabaseDirectoryFiles_Ctor(DatabaseDirectoryFiles*, const wchar_t*, void*);  // 0x008d7400

// @ 0x6b2620
bool FUN_006b2620(uint32_t dirId, const wchar_t* name, DatabaseDirectoryFiles** out,
                  uint32_t, uint32_t, IExtMapSink* sink) {
  const wchar_t* dir = GetDirFromID(dirId);
  WString path(dir);
  const wchar_t* end = name;
  while (*end != 0) {
    ++end;
  }
  path.Append(name, end);
  void* mem = ZoneObject_new(0x168, "App", 0, 0, 0, 0);
  DatabaseDirectoryFiles* pFiles;
  if (mem != 0) {
    pFiles = DatabaseDirectoryFiles_Ctor((DatabaseDirectoryFiles*)mem, path.mpBegin, 0);
  } else {
    pFiles = 0;
  }
  if (pFiles != 0) {
    pFiles->ref.AddRef();
  }
  if (pFiles == 0) {
    goto cleanup;
  }
  pFiles->s04();
  ReadExtensionMappingsFromPropFile(0x1c7ac81, (IExtMapSink*)pFiles);
  if (sink != 0) {
    pFiles->SetSink(sink);
    ReadExtensionMappingsFromPropFile((uint32_t)sink, (IExtMapSink*)pFiles);
  }
  if (pFiles->Configure(3, 4, 0)) {
    ResourceMgr4* rm = ResourceMan_GetManager();
    if (rm->Call50(1, pFiles, 1000)) {
      *out = pFiles;
      pFiles->ref.AddRef();
      pFiles->ref.Release();
      if ((((uint32_t)((char*)path.mpEnd - (char*)path.mpBegin)) & 0xfffffffeu) > 2 && path.mpBegin != 0) {
        EAFree(path.mpBegin);
      }
      return true;
    }
    pFiles->Shutdown();
  }
  pFiles->s08();
cleanup:
  if (pFiles != 0) {
    pFiles->ref.Release();
  }
  if ((((uint32_t)((char*)path.mpEnd - (char*)path.mpBegin)) & 0xfffffffeu) > 2 && path.mpBegin != 0) {
    EAFree(path.mpBegin);
  }
  return false;
}
