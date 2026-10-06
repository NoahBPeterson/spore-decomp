// Slice s0099afe0: EA::UTFWinTools::UTFWinToolsInternal::XmlReaderState XML reader.
// Reconstructed from the annotated disassembly; real names from the 2008 PDB where known.
#include "types.h"

extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);

// ---------------------------------------------------------------------------
// generic stubs (used by the already-matched helpers below)
// ---------------------------------------------------------------------------
struct RefObj {
  virtual void r0();
  virtual void Release();
};
struct S962100b { int* op(void*); };        // eastl hash_map<unsigned,AutoRefCount<...>>::operator[]
struct S693230 { void f(void*, unsigned); }; // hashtable bucket dealloc/copy helper
struct S620230b { void f(); };               // intrusive_list_base::~intrusive_list_base
struct S928dc0 { void f(); };                // allocator reset
struct S928cd0 { void init(int, int, int, int, int); }; // StackAllocator::StackAllocator
struct S928b00 { void init(int, int, int, int, int); }; // StackAllocator::Init
struct S928c40 { void f(void*); };

extern void FUN_f47380(void*);     // operator delete(void*)
extern "C" void* __cdecl MemSetThunk(void* p, int v, unsigned n);   // 0x011e073e

struct S99b5a0 { void f(int, int); };
struct S99b5e0 { void f(); };
struct S99b660 { S99b660* f(int, int, int, int, int); };

// ---------------------------------------------------------------------------
// types for the reader
// ---------------------------------------------------------------------------
struct XmlReaderState;
struct SerItem;

struct PropInfo {                                        // SerPropertyInfo
  char pad[0xc];
  uint16_t flags;                                        // +0xc: low 12 bits = type bits, bit 15 = variable count
  uint16_t pad2;
  uint32_t count;                                        // +0x14 fixed element count
  bool Commit(SerItem* base, SerItem* value, XmlReaderState* st);                                  // 0x0095dda0
  bool Build(SerItem* out, SerItem* base, uint32_t count, XmlReaderState* st, int flag);           // 0x0095dbd0
};
struct SerItem {
  uint32_t w[3];
  PropInfo* FindProp(SerItem* out, uint32_t id, XmlReaderState* st);                               // 0x0095dd00
};
struct ResKey { uint32_t a, b, c; };
struct HandlerItem : SerItem { uint32_t extra; };

struct INode { INode* next; INode* prev; };              // eastl::intrusive_list_node
struct IList {
  INode anchor;
  IList() { anchor.next = &anchor; anchor.prev = &anchor; }
  ~IList() {
    INode* n = anchor.next;
    while (n != &anchor) { INode* nx = n->next; n->prev = 0; n->next = 0; n = nx; }
  }
};

struct LazyReference {
  INode node;                // +0
  INode children;            // +8
  SerItem base;              // +0x10
  SerItem value;             // +0x1c
  PropInfo* prop;            // +0x28
  uint32_t* ids;             // +0x2c
  uint32_t count;            // +0x30
  char pad[4];
};

struct StackAlloc {          // EA::Allocator::StackAllocator (tail of the object)
  char pad[4];
  char* blk;                 // +4
  char* blkEnd;              // +8
  char* objBegin;            // +0xc
  char* objEnd;              // +0x10
  bool AllocateNewBlock(unsigned n);   // 0x00928ba0
  void Free(void* p);                  // 0x00928c40
  void Reset();                        // 0x00928dc0
};

struct IUnknown32 {
  virtual void AddRef();
  virtual void Release();
  virtual void v2();
  virtual IUnknown32* QueryInterface(uint32_t iid);      // +0xc
  virtual void GetInfo(void* out);                       // +0x10
};
struct ClassInfo { char pad[0x1c]; void (__cdecl* onLoaded)(void*); };
struct InfoOut { ClassInfo* info; void* ctx; uint32_t x2; uint32_t x3; };

struct IDataBinder {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual bool BindKey(SerItem* out, int typeCode, ResKey* key);   // +0x10
  virtual void Done();                                             // +0x14
  virtual bool GetHandler(uint32_t handler, SerItem* out);         // +0x18
};
struct BinderVec { IDataBinder** begin; IDataBinder** end; };

struct IReader {
  virtual void v0(); virtual void v1();
  virtual bool Open(void* stream, void* arg);            // +8
  virtual bool Next();                                   // +0xc
  virtual const void* GetPos(void* ctx);                 // +0x10
  virtual void* GetLine(const void* pos);                // +0x14 (ctx -> pos)
  const wchar_t* GetAttribute(const wchar_t* name);      // 0x00900720
  int            GetNodeType();                          // 0x00900660  (1 = element, 2 = end element)
  const wchar_t* GetName();                              // 0x00900690
  void           EndElement();                           // 0x009007b0
  uint32_t       GetErrorCode();                         // 0x00fcc210
};
extern "C" void* __cdecl FormatPos(const void* p);       // 0x0113ae10
extern "C" bool __cdecl ReadResKey(const wchar_t* s, ResKey* key);   // 0x008de0c0
extern "C" int  __cdecl ParseTypeName(const wchar_t* s);             // 0x0099a380

struct HNode { uint32_t key; void* value; HNode* next; };
struct HFind { void find(HNode** out, const uint32_t* key); };       // 0x00645ed0 (hashtable<uint,pair<uint,int>>::find)
struct HMap { char pad[4]; HNode** buckets; uint32_t nbuckets; uint32_t count; };   // +4 buckets, +8 bucket count, +0xc count
struct ObjectMapAlloc { void f(void*, unsigned); };

struct SerCollection {
  char pad[0x1c];
  HMap idMap;                                            // +0x1c
  char pad2[0x3c - 0x1c - sizeof(HMap)];
  void RemoveAll();                                      // 0x00999000
  bool Check(int n);                                     // 0x00998fb0
  void Add(IUnknown32* obj);                             // 0x00998fc0
};
struct ObjectFactory { IUnknown32* Create(uint32_t clsid, uint32_t iid, int a, int b); };   // vtbl slot 8 (+0x20)
struct FactoryMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual IUnknown32* Create(uint32_t clsid, uint32_t iid, int a, int b); };            // +0x20
FactoryMgr* GetFactoryMgr();                                                            // 0x00920090

struct HMapOps { IUnknown32** op(const uint32_t* key); };                // 0x00975d40 operator[]
struct CollMapAssign { void f(uint32_t key, IUnknown32* obj); };                         // 0x0099b5a0

struct XmlReaderState {
  const void* vptr;                                      // +0
  char allocA[0x24];                                     // +4   StackAllocator mAllocator
  char allocB[0x24];                                     // +0x28 StackAllocator mTempAllocator
  void (__cdecl* mErrorCallback)(uint32_t, void*);       // +0x4c
  void* mpCallbackContext;                               // +0x50
  uint32_t mNextTempID;                                  // +0x54
  uint32_t mResult;                                      // +0x58
  IList mLazyReferences;                                 // +0x5c
  HMap mObjectMap;                                       // +0x64 (+0x68 buckets, +0x6c bucket count, +0x70 count)
  char pad2[0x84 - 0x64 - sizeof(HMap)];
  SerCollection* mCollection;                            // +0x84
  BinderVec* mBinders;                                   // +0x88
  void* mImports;                                        // +0x8c
  void* mExports;                                        // +0x90
  IReader* mReader;                                      // +0x94

  StackAlloc* Temp() { return (StackAlloc*)((char*)this + 0x28); }
  StackAlloc* Pool() { return (StackAlloc*)((char*)this + 4); }

  void Report(uint32_t code);                                       // 0x0099a470
  bool CheckType(int typeCode, unsigned propBits);                  // 0x0099a3f0
  bool ReadObjectArray(LazyReference* ref);                         // 0x0099a4c0
  bool ReadStructArray(SerItem* val, IList* out);                   // 0x0099a7c0
  bool ReadPropertyValueArray(SerItem* val);                        // 0x0099ac80
  bool ParsePropertyValue(uint32_t v, int typeCode, const wchar_t* s); // 0x0099aa20
  void MoveChildren(IList* from, INode* to);                        // 0x0099a9d0 (thiscall on the list)

  bool Fixup(IList* list);                                          // 0x0099afe0
  LazyReference* CreateLazyReference(SerItem* base, PropInfo* prop, SerItem* value, int count); // 0x0099b110
  bool ReadProperty(SerItem* base, LazyReference** outRef);         // 0x0099b1f0
  bool ReadPropertyList(SerItem* base, IList* list);                // 0x0099b730
  IUnknown32* ReadObject(uint32_t* outId);                          // 0x0099b8a0
  bool ReadBindings();                                              // 0x0099b9e0
  bool ReadGraph();                                                 // 0x0099bac0
  uint32_t Read();                                                  // 0x0099bc00
};

// ---------------------------------------------------------------------------
// @ 0x0099b5a0  hash_map<unsigned,AutoRefCount<...>> slot assign
// ---------------------------------------------------------------------------
void S99b5a0::f(int key, int obj) {
  int* slot = ((S962100b*)this)->op(&key);
  int old = *slot;
  if (obj != old) {
    if (obj) ((RefObj*)(size_t)obj)->r0();
    *slot = obj;
    if (old) ((RefObj*)(size_t)old)->Release();
  }
}

// ---------------------------------------------------------------------------
// @ 0x0099b5e0  XmlReaderState base destructor
// ---------------------------------------------------------------------------
void S99b5e0::f() {
  char* self = (char*)this;
  char* ht = self + 0x64;
  *(int*)self = (int)0x1446c44;
  ((S693230*)ht)->f(*(void**)(ht + 4), *(unsigned*)(ht + 8));
  *(int*)(ht + 0xc) = 0;
  if (*(unsigned*)(ht + 8) > 1) FUN_f47380(*(void**)(ht + 4));
  ((S620230b*)(self + 0x5c))->f();
  ((S928dc0*)(self + 0x28))->f();
  ((S928dc0*)(self + 4))->f();
  *(int*)self = (int)0x14613b8;
}

// ---------------------------------------------------------------------------
// @ 0x0099b660  XmlReaderState::XmlReaderState
// ---------------------------------------------------------------------------
S99b660* S99b660::f(int a, int b, int c, int d, int e) {
  char* self = (char*)this;
  *(int*)self = (int)0x1446c44;
  ((S928cd0*)(self + 4))->init(0, -1, 0, 0, 0);
  ((S928cd0*)(self + 0x28))->init(0, -1, 0, 0, 0);
  *(int*)(self + 0x4c) = d;
  *(int*)(self + 0x50) = e;
  *(int*)(self + 0x54) = (int)0xef54054c;
  *(int*)(self + 0x58) = 0;
  *(int*)(self + 0x60) = (int)(self + 0x5c);
  *(int*)(self + 0x5c) = (int)(self + 0x5c);
  *(int*)(self + 0x74) = 0x3f800000;
  *(int*)(self + 0x78) = 0x40000000;
  *(int*)(self + 0x6c) = 1;
  *(int*)(self + 0x68) = (int)0x154df28;
  *(int*)(self + 0x70) = 0;
  *(int*)(self + 0x7c) = 0;
  *(int*)(self + 0x94) = a;
  *(int*)(self + 0x84) = b;
  *(int*)(self + 0x88) = c;
  *(int*)(self + 0x8c) = 0;
  *(int*)(self + 0x90) = 0;
  ((S928b00*)(self + 0x28))->init(0, 0, 0, 0, 0);
  ((S928b00*)(self + 4))->init(0, 0, 0, 0, 0);
  return this;
}

// ---------------------------------------------------------------------------
// @ 0x0099afe0  resolve the object ids of every LazyReference (recursively) and commit its value
// ---------------------------------------------------------------------------
bool XmlReaderState::Fixup(IList* list)
{
  INode* anchor = &list->anchor;
  for (INode* n = anchor->next; n != anchor; n = n->next) {
    LazyReference* lr = (LazyReference*)n;
    if (lr->children.prev != &lr->children)
      Fixup((IList*)&lr->children);
    if (lr->prop != 0) {
      uint32_t count = lr->count;
      if (count != 0) {
        uint32_t* out = (uint32_t*)lr->value.w[1];
        uint32_t i = 0;
        do {
          uint32_t key = lr->ids[i];
          void* v = 0;
          if (key != 0) {
            HNode* it;
            ((HFind*)&mObjectMap)->find(&it, &key);
            if (it == mObjectMap.buckets[mObjectMap.nbuckets]) {
              HMap* m = &mCollection->idMap;
              HNode* it2;
              ((HFind*)m)->find(&it2, &key);
              if (it2 == m->buckets[m->nbuckets])
                v = 0;
              else
                v = it2->value;
            } else {
              v = it->value;
            }
          }
          *out = (uint32_t)v;
          out++;
          i++;
        } while (i < count);
      }
      lr->prop->Commit(&lr->base, &lr->value, this);
    }
  }
  return true;
}

// ---------------------------------------------------------------------------
// @ 0x0099b110  XmlReaderState::CreateLazyReference
// ---------------------------------------------------------------------------
LazyReference* XmlReaderState::CreateLazyReference(SerItem* base, PropInfo* prop, SerItem* value, int count)
{
  StackAlloc* pool = Pool();
  LazyReference* obj;
  if ((int)(pool->blkEnd - pool->objBegin - 0x38) < 0) {
    if (pool->AllocateNewBlock(0x38))
      goto alloc_ok;
  } else {
  alloc_ok:
    char* mem = pool->objBegin;
    pool->objBegin = mem + 0x38;
    pool->objEnd = mem + 0x38;
    obj = (LazyReference*)mem;
    if (obj) {
      obj->node.prev = 0;
      obj->node.next = 0;
      obj->children.prev = &obj->children;
      obj->children.next = &obj->children;
      goto have_obj;
    }
  }
  obj = 0;
have_obj:
  obj->base = *base;
  obj->prop = prop;
  obj->value = *value;
  obj->count = count;
  if (count != 0) {
    unsigned bytes = count * 4;
    unsigned rounded = (bytes + 7) & ~7u;
    if ((int)(pool->blkEnd - pool->objBegin - rounded) < 0) {
      if (!pool->AllocateNewBlock(rounded)) {
        obj->ids = 0;
        return obj;
      }
    }
    char* mem = pool->objBegin;
    pool->objBegin = mem + rounded;
    pool->objEnd = mem + rounded;
    if (mem)
      MemSetThunk(mem, 0, bytes);
    obj->ids = (uint32_t*)mem;
  }
  return obj;
}

// ---------------------------------------------------------------------------
// @ 0x0099b1f0  XmlReaderState::ReadProperty
// ---------------------------------------------------------------------------
static inline void ReleaseTemp(StackAlloc* a, char* p)
{
  if (p > a->blk && p < a->blkEnd) { a->objBegin = p; a->objEnd = p; }
  else a->Free(p);
}

bool XmlReaderState::ReadProperty(SerItem* base, LazyReference** outRef)
{
  const wchar_t* propid = mReader->GetAttribute(L"propid");
  const wchar_t* typeStr = mReader->GetAttribute(L"type");
  const wchar_t* valueStr = mReader->GetAttribute(L"value");
  const wchar_t* countStr = mReader->GetAttribute(L"count");
  const wchar_t* keyStr = mReader->GetAttribute(L"key");
  if (propid == 0) { Report(0x2fc50003); return false; }
  int typeCode = 0;
  if (typeStr == 0 || (typeCode = ParseTypeName(typeStr)) == 0) { Report(0x2fc50004); return false; }
  SerItem prop;
  PropInfo* info = base->FindProp(&prop, wcstoul(propid, 0, 0), this);
  if (info) {
    if (!CheckType(typeCode, info->flags & 0xfff)) {
      Report(0x2fc50005);
    } else {
      uint32_t count = countStr ? wcstoul(countStr, 0, 0) : 1;
      if (!((info->flags >> 15) & 1) && count != info->count) {
        Report(0x2fc50007);
      } else {
        SerItem val;
        if (!info->Build(&val, &prop, count, this, 0)) {
          Report(3);
          return false;
        }
        if (typeCode == 0x13) {
          LazyReference* lr = CreateLazyReference(&prop, info, &val, count);
          *outRef = lr;
          if (!ReadObjectArray(lr))
            return false;
          goto done;
        }
        if (typeCode == 0x14) {
          IList list;
          if (!ReadStructArray(&val, &list))
            return false;
          if (list.anchor.prev == &list.anchor) {
            if (!info->Commit(&prop, &val, this)) {
              Report(0x2fc5000a);
              mReader->EndElement();
              return true;
            }
          } else {
            LazyReference* lr = CreateLazyReference(base, info, &val, 0);
            *outRef = lr;
            MoveChildren(&list, &lr->children);
          }
          mReader->EndElement();
          return true;
        }
        if (countStr != 0) {
          if (!ReadPropertyValueArray(&val))
            return false;
        } else if (keyStr != 0) {
          ResKey key = { 0, 0, 0 };
          if (ReadResKey(keyStr, &key)) {
            IDataBinder** it = mBinders->begin;
            for (; it != mBinders->end; ++it) {
              if ((*it)->BindKey(&val, typeCode, &key))
                goto commit;
            }
            Report(0x2fc50009);
          }
        } else if (valueStr != 0) {
          if (!ParsePropertyValue(val.w[1], typeCode, valueStr))
            return false;
        }
      commit:
        if (!info->Commit(&prop, &val, this))
          Report(0x2fc5000a);
      }
    }
  }
done:
  mReader->EndElement();
  return true;
}

// ---------------------------------------------------------------------------
// @ 0x0099b730  XmlReaderState::ReadPropertyList
// ---------------------------------------------------------------------------
bool XmlReaderState::ReadPropertyList(SerItem* base, IList* list)
{
  INode* head = &list->anchor;
  if (!mReader->Next()) {
    Report(mReader->GetErrorCode());
    return false;
  }
  for (;;) {
    int t = mReader->GetNodeType();
    if (t == 1) {
      if (wcscmp(mReader->GetName(), L"prop") != 0) {
        Report(0x2fc50001);
        return false;
      }
      char* mark = Temp()->objBegin;
      LazyReference* ref = 0;
      if (!ReadProperty(base, &ref)) {
        ReleaseTemp(Temp(), mark);
        return false;
      }
      if (ref) {
        ref->node.prev = head->prev;
        ref->node.next = head;
        head->prev = &ref->node;
        ref->node.prev->next = &ref->node;
      } else {
        ReleaseTemp(Temp(), mark);
      }
    } else {
      if (mReader->GetNodeType() == 2)
        return true;
      if (!mReader->Next()) {
        Report(mReader->GetErrorCode());
        return false;
      }
    }
  }
}

// ---------------------------------------------------------------------------
// @ 0x0099b8a0  XmlReaderState::ReadObject
// ---------------------------------------------------------------------------
IUnknown32* XmlReaderState::ReadObject(uint32_t* outId)
{
  const wchar_t* idStr = mReader->GetAttribute(L"id");
  const wchar_t* clsidStr = mReader->GetAttribute(L"clsid");
  if (clsidStr == 0) {
    Report(0x2fc50002);
    return 0;
  }
  uint32_t clsid = wcstoul(clsidStr, 0, 0);
  IUnknown32* obj = GetFactoryMgr()->Create(clsid, 0xee3f516e, 0, 0);
  if (obj == 0) {
    Report(0x2fc50002);
    return 0;
  }
  if (idStr != 0) {
    *outId = wcstoul(idStr, 0, 0);
    if (*outId != 0) {
      if (*outId + 0x10000 > 0x7fff && mCollection->Check(2))
        ((CollMapAssign*)((char*)mCollection + 0x3c))->f(*outId, obj);
      goto map_it;
    }
  } else {
    *outId = mNextTempID;
    mNextTempID++;
  map_it:
    if (*outId != 0)
      *((HMapOps*)((char*)this + 0x64))->op(outId) = obj;
  }
  obj->AddRef();
  {
    IUnknown32* iface = obj->QueryInterface(0xeec58382);
    if (iface) {
      InfoOut io;
      iface->GetInfo(&io);
      if (!ReadPropertyList((SerItem*)&io, &mLazyReferences)) {
        Report(0x2fc50002);
        return 0;
      }
    }
  }
  return obj;
}

// ---------------------------------------------------------------------------
// @ 0x0099b9e0  XmlReaderState::ReadBindings
// ---------------------------------------------------------------------------
bool XmlReaderState::ReadBindings()
{
  const wchar_t* handlerStr = mReader->GetAttribute(L"handler");
  if (handlerStr == 0) {
    Report(0x2fc50008);
    return false;
  }
  uint32_t handler = wcstoul(handlerStr, 0, 0);
  HandlerItem item;
  for (IDataBinder** it = mBinders->begin; it != mBinders->end; ++it) {
    if ((*it)->GetHandler(handler, &item))
      return ReadPropertyList(&item, &mLazyReferences);
  }
  mResult = 0x2fc50008;
  if (mErrorCallback) {
    IReader* r = mReader;
    void* line = r->GetLine(mpCallbackContext);
    const void* pos = r->GetPos(line);
    mErrorCallback(mResult, FormatPos(pos));
  }
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x0099bac0  XmlReaderState::ReadGraph
// ---------------------------------------------------------------------------
bool XmlReaderState::ReadGraph()
{
  while (mReader->Next()) {
    if (mReader->GetNodeType() == 1) {
      if (wcscmp(mReader->GetName(), L"object") == 0) {
        uint32_t id = 0;
        IUnknown32* obj = ReadObject(&id);
        if (!obj)
          return false;
        mCollection->Add(obj);
      } else {
        if (wcscmp(mReader->GetName(), L"prologue") != 0) {
          Report(0x2fc50001);
          return false;
        }
        if (!ReadBindings())
          return false;
      }
    } else {
      if (mReader->GetNodeType() == 2)
        return true;
    }
  }
  Report(mReader->GetErrorCode());
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x0099bc00  XmlReaderState::Read
// ---------------------------------------------------------------------------
uint32_t XmlReaderState::Read()
{
  bool ok = true;
  mCollection->RemoveAll();
  bool more = mReader->Next();
  while (more) {
    if (mReader->GetNodeType() == 1)
      goto found;
    more = mReader->Next();
  }
  Report(mReader->GetErrorCode());
  ok = false;
  goto cleanup;
found:
  if (wcscmp(mReader->GetName(), L"graph") == 0) {
    if (!ReadGraph()) {
      ok = false;
      goto cleanup;
    }
  } else {
    if (wcscmp(mReader->GetName(), L"object") != 0) {
      Report(0x2fc50001);
      return 0;
    }
    uint32_t id = 0;
    IUnknown32* obj = ReadObject(&id);
    if (!obj) {
      ok = false;
      goto cleanup;
    }
    mCollection->Add(obj);
  }
  Fixup(&mLazyReferences);
cleanup:
  {
    INode* anchor = &mLazyReferences.anchor;
    INode* n = anchor->next;
    while (n != anchor) { INode* nx = n->next; n->prev = 0; n->next = 0; n = nx; }
    anchor->prev = anchor;
    anchor->next = anchor;
  }
  for (IDataBinder** it = mBinders->begin; it != mBinders->end; ++it)
    (*it)->Done();
  {
    HNode* end = mObjectMap.buckets[mObjectMap.nbuckets];
    HNode** b = mObjectMap.buckets;
    HNode* n = *b;
    if (!n) {
      ++b;
      while (!(n = *b)) ++b;
    }
    HNode** bucket = b;
    while (n != end) {
      IUnknown32* u = (IUnknown32*)n->value;
      if (u) {
        IUnknown32* iface = u->QueryInterface(0xeec58382);
        if (iface) {
          InfoOut io;
          iface->GetInfo(&io);
          if (io.info->onLoaded)
            io.info->onLoaded(io.ctx);
        }
      }
      ((IUnknown32*)n->value)->Release();
      n = n->next;
      while (!n) { ++bucket; n = *bucket; }
    }
  }
  ((ObjectMapAlloc*)&mObjectMap)->f(mObjectMap.buckets, mObjectMap.nbuckets);
  mObjectMap.count = 0;
  Pool()->Reset();
  Temp()->Reset();
  return ok ? 0 : mResult;
}

// ---------------------------------------------------------------------------
// @ 0x0099be60  XmlDeserializer::Read: sniff the stream (text vs token XML), parse it
// ---------------------------------------------------------------------------
struct IStreamX {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
  virtual int  GetPosition(int mode);              // +0x24
  virtual bool SetPosition(int pos, int mode);     // +0x28
  virtual void v11();
  virtual int  Read(void* buf, int n);             // +0x30
};
struct XmlTextReader  : IReader { char body[0x88 - 4]; XmlTextReader(int);  ~XmlTextReader(); };   // 0x00900b30 / 0x00900b70
struct XmlTokenReader : IReader { char body[0xa4 - 4]; XmlTokenReader(int); ~XmlTokenReader(); };  // 0x009031a0 / 0x009031d0
struct XmlReaderStateObj : XmlReaderState {
  XmlReaderStateObj(IReader* r, SerCollection* c, BinderVec* b, void* cb, void* ctx);   // 0x0099b660
  ~XmlReaderStateObj();                                                                  // 0x0099b5e0
};

uint32_t __stdcall XmlDeserializerRead(IStreamX* stream, void* arg2, SerCollection* coll, BinderVec* binders, void* cb, void* ctx)
{
  XmlTextReader text(0);
  XmlTokenReader token(0);
  IReader* reader = &text;
  int pos = stream->GetPosition(0);
  uint32_t magic = 0xffff;
  if (stream->Read(&magic, 2) == -1)
    return 0;
  if ((uint16_t)magic == 0)
    reader = &token;
  stream->SetPosition(pos, 0);
  uint32_t result = 0;
  if (reader->Open(stream, arg2)) {
    XmlReaderStateObj st(reader, coll, binders, cb, ctx);
    result = st.Read();
  }
  return result;
}
