// src/game/SPEngine/SPSaveAreas.cpp -- migrated from slice(s) s006b37d0, s006b27f0, s006b18c0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPSaveAreas.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Database.h"
#include "EA/ResourceMan/DatabasePackedFile.h"
#include "EA/ResourceMan/Resource.h"
#include "SP/cPropertyList.h"
#include "SP/cString.h"
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)

// unnamed retail callees and globals (address in the comment)
extern "C" void* RBTreeIncrement(void*);        // 0x00921580
extern void  FUN_006acfe0(void*, void*);        // 0x006acfe0
extern uint32_t FUN_006b4b60(void*, void*, int, int);  // 0x006b4b60

// ---- items of slice s006b18c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct SaveAreaMap {
  uint32_t  f0;       // +0x00
  uint32_t  head;     // +0x04  (sentinel address 0x0152fdc8)
  uint32_t* root;     // +0x08  (0x0152fdcc)
  uint32_t  f3;       // +0x0c
  void find(void** out, const uint32_t* key);   // 0x00e5c780 (thiscall)
};
extern SaveAreaMap g_saveAreas;
extern "C" void* RBTreeIncrement(void*);        // 0x00921580
struct PropertyMgr4 {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12();
  virtual void Call34(void*, void*, void*);     // slot 13 (0x34)
};
extern PropertyMgr4* SP_PropertyManager();      // 0x0067de30
struct ResourceMgr4 {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual uint32_t Call20(void*, void*, void*, void*, void*);  // slot 8 (0x20)
  virtual void v9(); virtual void v10(); virtual void v11();
  virtual int Call30(void*, void*, void*);      // slot 12 (0x30)
};
extern ResourceMgr4* ResourceMan_GetManager();  // 0x0067dcd0
struct SaveObj {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8();
  virtual void Call24();                        // slot 9 (0x24)
  virtual void v10(); virtual void v11(); virtual void v12();
  virtual bool Call34(void*, void*, void*, void*, void*, void*); // slot 13
};
extern void  FUN_006acfe0(void*, void*);        // 0x006acfe0
extern uint32_t FUN_006b4b60(void*, void*, int, int);  // 0x006b4b60
struct RefVt { virtual void AddRef(); virtual void Release(); };
struct RefA { uint32_t pad0; RefVt ref; };       // polymorphic subobject at +0x4
struct RefB { virtual void AddRef(); virtual void Release(); };
struct RefPair {
  RefA* a;
  RefB* b;
  RefPair* Ctor(RefA* x, RefB* y);               // 0x6b1dc0
  void     Dtor();                               // 0x6b1e20
  RefPair* CtorCopy(const RefPair* o);           // 0x6b1e90
  RefPair* Assign(const RefPair* o);             // 0x6b1ef0
};
// ---- items of slice s006b18c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern SaveAreaMap g_saveAreas;
extern PropertyMgr4* SP_PropertyManager();      // 0x0067de30
extern ResourceMgr4* ResourceMan_GetManager();  // 0x0067dcd0

// ---- items of slice s006b27f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void EFree5(void*);                 // 0x00f47380
extern const wchar_t* GetDirFromID(uint32_t id);                 // 0x006886b0
extern void EnsureDirectoryExists(const wchar_t* dir);           // 0x00932ae0
extern void ReadExtensionMappingsFromPropFile(uint32_t group, void* db);   // 0x006b2110
extern float g_13eb95c;                                          // 0x013eb95c
extern bool CreateDirectorySave(uint32_t id, const wchar_t* a, void* b, void* c);   // 0x006b2620
extern const wchar_t kEmpty13ec468[];                            // 0x0013ec468
struct RefVt5 { virtual void AddRef(); virtual void Release(); };
struct RefA5 { uint32_t pad0; RefVt5 ref; };
struct RefB5 { virtual void AddRef(); virtual void Release(); };
struct RefPair5 {
  RefA5* a;
  RefB5* b;
  RefPair5() : a(0), b(0) {}
  RefPair5(void* pa, void* pb);               // 0x006b1dc0
  RefPair5(const RefPair5& o);                // 0x006b1e90
  ~RefPair5();                                // 0x006b1e20
  RefPair5& operator=(const RefPair5& o);     // 0x006b1ef0
};
struct SavePair {                             // eastl::pair<const unsigned, cSPSaveArea>
  uint32_t first;
  RefPair5 second;
  SavePair(const uint32_t& k, const RefPair5& v) : first(k), second(v) {}
};
struct SavePairResult { struct RBNode5* node; bool inserted; };
struct RBNode5;
struct RBNode5 {
  RBNode5* left;    // +0x00
  RBNode5* right;   // +0x04
  uint32_t m8;      // +0x08
  uint32_t mc;      // +0x0c
  uint32_t m10;     // +0x10
  RefPair5 val;     // +0x14
};
struct SaveObj5 {
  virtual void v0();
  virtual void v1();
  virtual void Call08();     // 0x08
  virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
  virtual void Call1c();     // 0x1c
};
struct TrueTag5 {};
struct SaveMap5 {
  uint32_t f0;       // +0x00
  uint32_t head;     // +0x04
  uint32_t root;     // +0x08
  uint32_t nukep;    // +0x0c
  uint32_t f10;      // +0x10
  uint32_t f14;      // +0x14
  void Nuke(RBNode5* n);   // 0x6b2aa0 (thiscall, this ignored)
  RefPair5& Index(const uint32_t& key);      // 0x6b3680 operator[]
  void DoInsertValue(SavePairResult* sret, RBNode5* hint, const SavePair& v, TrueTag5 unique);   // 0x6b3520
};
extern SaveMap5 g_m5;
struct IRef6 { virtual void AddRef(); virtual void Release(); };      // plain AddRef/Release interface
struct IRefSub { virtual void AddRef(); virtual void Release(); };    // refcount sub-object at +4 of the db objects
struct WStrA {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  void RangeInitialize(const wchar_t* p);          // 0x00579a90
  void Append(const wchar_t* b, const wchar_t* e);  // 0x00429580 (WStr::Append)
  explicit WStrA(const wchar_t* p) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; RangeInitialize(p); }
  ~WStrA() {
    if (((mpCapacity - mpBegin) & ~1) > 2 && mpBegin) {
      delete[] mpBegin;
    }
  }
};
inline const wchar_t* WStrEnd(const wchar_t* s) { const wchar_t* e = s; while (*e) ++e; return s + (e - s); }
struct DbDirFiles {                    // EA::ResourceMan::DatabaseDirectoryFiles (0x168 bytes)
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
  virtual void SetMappingFile(uint32_t group);    // 0x70
  IRefSub ref;                         // +4
  char pad[0x168 - 8];
  DbDirFiles(const wchar_t* dir, int flags);       // 0x008d7400
};
struct DbPackedFile {                  // EA::ResourceMan::DatabasePackedFile (0x388 bytes)
  virtual void v0(); virtual void v1();
  IRefSub ref;
  char pad[0x388 - 8];
  DbPackedFile(const wchar_t* path, int flags);    // 0x008d9f80
  void SetOption(int a, float b);                  // 0x008d8530
  void Open(int a);                                // 0x008d8560
};
struct DbXFile {                       // 0x5a8-byte database (0x6bdc50)
  virtual void v0(); virtual void v1();
  IRefSub ref;
  char pad[0x5a8 - 8];
  DbXFile(const wchar_t* path, int flags);         // 0x006bdc50
  void SetOption(int a, float b);                  // 0x006bc3a0
  void Open(int a);                                // 0x006bc3d0
};
struct DbService {                     // object returned by FUN_006b00a0 (db service)
  virtual void v0();
  virtual void Release();              // 0x04
  virtual void Shutdown();             // 0x08
  virtual void v3(); virtual void v4(); virtual void v5();
  virtual bool Start(int a, int b, int c);   // 0x18
  virtual void Stop();                 // 0x1c
  IRefSub ref;                         // +4
};
struct IResManager6 {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
  virtual void v18(); virtual void v19();
  virtual bool RegisterDatabase(int priority, void* db, int timeout);   // 0x50
};
extern IRef6* LRUCacheCreate(void* db, uint32_t arg);            // 0x006b0ed0
extern DbService* F_6b00a0(void* db, IRef6* cache);              // 0x006b00a0
extern IResManager6* GetManager6();                              // 0x0067dcd0
void* __cdecl operator new(size_t, const char*, int, int, int, int);   // EA::Allocator::ZoneObject::operator_new (0x926020)
void __cdecl operator delete(void* p);                                 // 0x00f47380
    void operator delete(void*); // 0x00f47380
// ---- items of slice s006b27f0 end

// ---- items of slice s006b37d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
    void CreateDirectorySave(...); // 0x006b2620
extern char g_editorMode6;         // 0x16046d8
extern char g_serverMode6;         // 0x152fbcc
extern char g_gfxMode6;            // 0x152fbcd
extern const char g_dir13ec468[];  // 0x13ec468
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
void operator delete[](void* p);   // 0x00f47380
struct IRef6_s006b_37d0 {
    virtual void v0();
    virtual void Release();
};
struct SaveObj6 { uint32_t pad0; IRef6_s006b_37d0 ref; };   // refcounted through the +4 subobject
struct SaveRef6 { SaveObj6* p; SaveRef6() : p(0) {} ~SaveRef6() { if (p) p->ref.Release(); } };
struct Ref6b { IRef6_s006b_37d0* p; Ref6b() : p(0) {} ~Ref6b() { if (p) p->Release(); } };
struct cString6 {
  cString6();   // 0x006b5060
  ~cString6();   // 0x006b5240
  void Load(uint32_t tableId, uint32_t instId, const wchar_t* dflt);   // 0x006b54b0
  const wchar_t* GetText();   // 0x006b55c0
  char data[8];
};
bool CreateDirectorySave(uint32_t root, const wchar_t* name, SaveObj6** out, uint32_t key);   // 0x006b2620
bool CreateLocationSave(uint32_t root, const wchar_t* name, SaveObj6** out, uint32_t key, uint32_t flag);   // 0x006b3430
bool CreatePackageSave(uint32_t root, const void* dir, const wchar_t* name, SaveObj6** out);   // 0x006b3240
bool CreateServerCacheSave(uint32_t root, const void* dir, const wchar_t* name, SaveObj6** out);   // 0x006b3050
bool CreateGraphicsDir(uint32_t root, const wchar_t* name, SaveObj6** out, IRef6_s006b_37d0** out2, uint32_t a, uint32_t b);   // 0x006b27f0
bool CreateGraphicsPackage(uint32_t root, const void* dir, const wchar_t* name, SaveObj6** out, IRef6_s006b_37d0** out2, uint32_t a);   // 0x006b2b30
bool CreateCachedDirectorySave(uint32_t root, const void* dir, const wchar_t* name, SaveObj6** out, IRef6_s006b_37d0** out2, uint32_t a);   // 0x006b2dc0
void RegisterSaveArea(uint32_t key, SaveObj6* o, IRef6_s006b_37d0* o2);   // 0x006b3760
uint32_t FNV1_String8(const char* s, uint32_t seed, int flag);   // 0x00932e80
struct PropDesc6 { char pad[0x118]; int flag118; };
struct PropListFn6 {
  bool GetDescription(uint32_t hash);   // 0x006a25a0
  char pad[0x3c]; PropDesc6* desc;
};
extern PropListFn6* g_appProps6;   // 0x15fd918
struct WStr6 {
  wchar_t* b; wchar_t* e; wchar_t* cap; void* alloc;
  void Init(const wchar_t* s);   // 0x00579a90
  int rfind(wchar_t c, int pos);   // 0x0041dfc0
  void push_back(wchar_t c);   // 0x004f6510
  void append(const wchar_t* s);   // 0x00599bb0
  ~WStr6() { if ((((char*)cap - (char*)b) & ~1) > 2 && b) operator delete[](b); }   // byte capacity, signed compare
};
struct Key3 { uint32_t inst, type, group; };
struct KeyRef6 { uint32_t pad[2]; uint32_t inst, type, group; };
#define V6(n) virtual void v##n();
struct ResMgr6 {
  V6(0) V6(1) V6(2) V6(3) V6(4) V6(5) V6(6) V6(7) V6(8) V6(9) V6(10) V6(11) V6(12) V6(13) V6(14) V6(15)
  V6(16) V6(17)
  virtual void* GetFormat(uint32_t type, int n);   // 0x48
  V6(19) V6(20) V6(21) V6(22) V6(23) V6(24) V6(25) V6(26) V6(27) V6(28) V6(29) V6(30) V6(31)
  virtual void SetName(void* key, const wchar_t* name);   // 0x80
  V6(33) V6(34)
  virtual const wchar_t* GetExt(uint32_t type);           // 0x8c
};
struct IStream6 {
  V6(0) V6(1)
  virtual void Release();   // 0x08
  V6(3) V6(4) V6(5) V6(6) V6(7) V6(8)
  virtual void Close();     // 0x24
};
struct Res6 {
  V6(0) V6(1) V6(2)
  virtual uint32_t GetKind();          // 0x0c
  V6(4) V6(5) V6(6) V6(7) V6(8) V6(9) V6(10) V6(11) V6(12)
  virtual bool Open(void* key, IStream6** out, int a, int b, int c, int d);   // 0x34
  V6(14) V6(15) V6(16) V6(17) V6(18)
  virtual void SetName(const wchar_t* n, uint32_t type);   // 0x4c
  V6(20) V6(21) V6(22) V6(23)
  virtual const wchar_t* GetName(uint32_t type);           // 0x60
  virtual bool GetPath(void* key, wchar_t* buf);           // 0x64
  V6(26)
  virtual uint32_t GetGroup();                             // 0x6c
};
struct Fmt6 {
  V6(0) V6(1) V6(2) V6(3) V6(4) V6(5) V6(6) V6(7) V6(8) V6(9)
  virtual bool Write(void* key, IStream6* strm, int z, uint32_t type);   // 0x28
};
ResMgr6* GetResMgr6();   // 0x0067dcd0
void FormatHex6(WStr6* s, const wchar_t* fmt, uint32_t v);   // 0x004e0850
void SPKeyFromName(void* k, const wchar_t* name, uint32_t type, uint32_t group);   // 0x0068d840
#define REL6(s) do { if (s) { out.p = 0; (s)->ref.Release(); } } while (0)
#define SAVE_DIR6(root, nm, key) \
  ok = CreateDirectorySave(root, nm, &out.p, key); s = out.p; if (ok) RegisterSaveArea(key, s, 0)
// ---- items of slice s006b37d0 end

// @ 0x006b1d50
void SP_SaveResource(void* p, uint32_t val, char flag)
{
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

// @ 0x006b1dc0
RefPair* RefPair::Ctor(RefA* x, RefB* y)
{
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

// @ 0x006b1e20
void RefPair::Dtor()
{
  if (b != 0) {
    b->Release();
  }
  if (a != 0) {
    a->ref.Release();
  }
  _ReadWriteBarrier();
}

// @ 0x006b1e90
RefPair* RefPair::CtorCopy(const RefPair* o)
{
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

// @ 0x006b1ef0
RefPair* RefPair::Assign(const RefPair* o)
{
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

// @ 0x006b1f60
namespace SP {
bool IsSaveArea(EA::ResourceMan::Database const * p)
{
  uint32_t* it = g_saveAreas.root;
  while (it != &g_saveAreas.head) {
    if (it[5] == (uint32_t)p) {
      return true;
    }
    it = (uint32_t*)RBTreeIncrement(it);
  }
  return false;
}
}  // namespace SP

// @ 0x006b1f90
void* SP_GetSaveArea(uint32_t key)
{
  uint32_t* out;
  g_saveAreas.find((void**)&out, &key);
  if (out != &g_saveAreas.head) {
    return (void*)out[5];
  }
  return 0;
}

// @ 0x006b1fc0
namespace SP {
void FlushAllSaveAreas()
{
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[6];
    if (o != 0) {
      o->Call24();
    }
  }
}
}  // namespace SP

// @ 0x006b2000
bool FUN_006b2000(void* p, char flag)
{
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

// @ 0x006b2090
bool FUN_006b2090(void* p, char flag)
{
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

// @ 0x006b2110
void ReadExtensionMappingsFromPropFile()
{}

// @ 0x006b22a0
void* SP_UpdateSaveAreas(void* p)
{
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[5];
    if (o->Call34(p, 0, (void*)1, (void*)6, (void*)1, 0)) {
      return o;
    }
  }
  return 0;
}

// @ 0x006b22f0
void* FUN_006b22f0(void* p)
{
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

// @ 0x006b2350
void SP_SomethingAllSaveAreas()
{
  for (uint32_t* it = g_saveAreas.root; it != &g_saveAreas.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    SaveObj* o = (SaveObj*)it[5];
    o->Call24();
  }
}

// @ 0x006b2400
void FUN_006b2400()
{}

// @ 0x006b2620
void FUN_006b2620()
{}

// @ 0x006b27f0
bool __cdecl SP_cAppSystem_CreateHTTPServer(uint32_t id, const wchar_t* sub, IRef6** outServer, IRef6** outCache, uint32_t cacheArg, uint32_t extraGroup)
{
    WStrA dir(GetDirFromID(id));
    dir.Append(sub, WStrEnd(sub));
    DbDirFiles* files = new("App", 0, 0, 0, 0) DbDirFiles(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    if (files == 0) {
        return false;
    }
    IRef6* cache = LRUCacheCreate(files, cacheArg);
    if (cache) {
        cache->AddRef();
    }
    if (cache == 0) {
        files->ref.Release();
        return false;
    }
    DbService* srv = F_6b00a0(files, cache);
    if (srv) {
        srv->ref.AddRef();
    }
    if (srv == 0) {
        cache->Release();
        files->ref.Release();
        return false;
    }
    srv->Release();
    ReadExtensionMappingsFromPropFile(0x1c7ac81, files);
    if (extraGroup) {
        files->SetMappingFile(extraGroup);
        ReadExtensionMappingsFromPropFile(extraGroup, files);
    }
    if (srv->Start(3, 4, 0)) {
        if (GetManager6()->RegisterDatabase(1, srv, 1000)) {
            *outServer = (IRef6*)srv;
            *outCache = cache;
            files->ref.Release();
            return true;
        }
        srv->Stop();
    }
    srv->Shutdown();
    srv->ref.Release();
    cache->Release();
    files->ref.Release();
    return false;
}

// @ 0x006b2aa0
void SaveMap5::Nuke(RBNode5* n)
{
  while (n != 0) {
    Nuke(n->left);
    RBNode5* right = n->right;
    if (n->val.b != 0) {
      n->val.b->Release();
    }
    if (n->val.a != 0) {
      n->val.a->ref.Release();
    }
    EFree5(n);
    n = right;
  }
}

// @ 0x006b2b30
bool __cdecl OpenPreCommitFile(uint32_t id, const wchar_t* sub1, const wchar_t* sub2, IRef6** outServer, IRef6** outCache, uint32_t cacheArg)
{
    WStrA dir(GetDirFromID(id));
    dir.Append(sub1, WStrEnd(sub1));
    EnsureDirectoryExists(dir.mpBegin);
    dir.Append(sub2, WStrEnd(sub2));
    DbPackedFile* files = new("App", 0, 0, 0, 0) DbPackedFile(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    files->SetOption(0x12, g_13eb95c);
    files->Open(0);
    IRef6* cache = LRUCacheCreate(files, cacheArg);
    if (cache) {
        cache->AddRef();
    }
    if (cache == 0) {
        if (files) {
            files->ref.Release();
        }
        return false;
    }
    DbService* srv = F_6b00a0(files, cache);
    if (srv) {
        srv->ref.AddRef();
    }
    if (srv) {
        srv->Release();
        if (srv->Start(3, 6, 0)) {
            if (GetManager6()->RegisterDatabase(1, srv, 1000)) {
                *outServer = (IRef6*)srv;
                *outCache = cache;
                if (files) {
                    files->ref.Release();
                }
                return true;
            }
            srv->Stop();
        }
        srv->Shutdown();
        srv->ref.Release();
    }
    cache->Release();
    if (files) {
        files->ref.Release();
    }
    return false;
}

// @ 0x006b2dc0
bool __cdecl SP_CreateCachedDirectorySave(uint32_t id, const wchar_t* sub1, const wchar_t* sub2, IRef6** outServer, IRef6** outCache, uint32_t cacheArg)
{
    WStrA dir(GetDirFromID(id));
    dir.Append(sub1, WStrEnd(sub1));
    EnsureDirectoryExists(dir.mpBegin);
    dir.Append(sub2, WStrEnd(sub2));
    DbXFile* files = new("App", 0, 0, 0, 0) DbXFile(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    files->SetOption(0x12, g_13eb95c);
    files->Open(0);
    IRef6* cache = LRUCacheCreate(files, cacheArg);
    if (cache) {
        cache->AddRef();
    }
    if (cache == 0) {
        if (files) {
            files->ref.Release();
        }
        return false;
    }
    DbService* srv = F_6b00a0(files, cache);
    if (srv) {
        srv->ref.AddRef();
    }
    if (srv) {
        srv->Release();
        if (srv->Start(3, 6, 0)) {
            if (GetManager6()->RegisterDatabase(1, srv, 1000)) {
                *outServer = (IRef6*)srv;
                *outCache = cache;
                if (files) {
                    files->ref.Release();
                }
                return true;
            }
            srv->Stop();
        }
        srv->Shutdown();
        srv->ref.Release();
    }
    cache->Release();
    if (files) {
        files->ref.Release();
    }
    return false;
}

// @ 0x006b3050
bool __cdecl cDirectoriesCheat_Execute(uint32_t id, const wchar_t* sub1, const wchar_t* sub2, IRef6** outFile)
{
    WStrA dir(GetDirFromID(id));
    dir.Append(sub1, WStrEnd(sub1));
    EnsureDirectoryExists(dir.mpBegin);
    dir.Append(sub2, WStrEnd(sub2));
    DbPackedFile* files = new("App", 0, 0, 0, 0) DbPackedFile(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    if (files) {
        files->SetOption(0x12, g_13eb95c);
        files->Open(0);
        ((IRef6*)files)->Release();
        if (((DbService*)files)->Start(3, 6, 0)) {
            if (GetManager6()->RegisterDatabase(1, files, 1000)) {
                *outFile = (IRef6*)files;
                files->ref.AddRef();
                files->ref.Release();
                return true;
            }
            ((DbService*)files)->Stop();
        }
        ((DbService*)files)->Shutdown();
    }
    if (files) {
        files->ref.Release();
    }
    return false;
}

// @ 0x006b3240
bool __cdecl SP_CreatePackageSave(uint32_t id, const wchar_t* sub1, const wchar_t* sub2, IRef6** outFile)
{
    WStrA dir(GetDirFromID(id));
    dir.Append(sub1, WStrEnd(sub1));
    EnsureDirectoryExists(dir.mpBegin);
    dir.Append(sub2, WStrEnd(sub2));
    DbXFile* files = new("App", 0, 0, 0, 0) DbXFile(dir.mpBegin, 0);
    if (files) {
        files->ref.AddRef();
    }
    if (files) {
        files->SetOption(0x12, g_13eb95c);
        files->Open(0);
        ((IRef6*)files)->Release();
        if (((DbService*)files)->Start(3, 6, 0)) {
            if (GetManager6()->RegisterDatabase(1, files, 1000)) {
                *outFile = (IRef6*)files;
                files->ref.AddRef();
                files->ref.Release();
                return true;
            }
            ((DbService*)files)->Stop();
        }
        ((DbService*)files)->Shutdown();
    }
    if (files) {
        files->ref.Release();
    }
    return false;
}

// @ 0x006b3430
bool __cdecl SP_CreateLocationSave(uint32_t id, const wchar_t* name, IRef6** out, void* extra, bool package)
{
    if (package) {
        WStrA path(name);
        path.Append(L".package", WStrEnd(L".package"));
        return cDirectoriesCheat_Execute(id, kEmpty13ec468, path.mpBegin, out);
    }
    return CreateDirectorySave(id, name, out, extra);
}

// @ 0x006b3610
void FUN_006b3610()
{
  for (uint32_t* it = (uint32_t*)g_m5.root; it != &g_m5.head;
       it = (uint32_t*)RBTreeIncrement(it)) {
    ((SaveObj5*)it[5])->Call1c();
    ((SaveObj5*)it[5])->Call08();
  }
  g_m5.Nuke((RBNode5*)g_m5.nukep);
  g_m5.head = (uint32_t)&g_m5.head;
  g_m5.root = (uint32_t)&g_m5.head;
  g_m5.nukep = 0;
  *(uint8_t*)&g_m5.f10 = 0;
  g_m5.f14 = 0;
}

// @ 0x006b3680
RefPair5& SaveMap5::Index(const uint32_t& key)
{
  RBNode5* end = (RBNode5*)&head;
  RBNode5* pRangeEnd = end;
  RBNode5* pCurrent = (RBNode5*)nukep;
  while (pCurrent) {
    if (!(pCurrent->m10 < key)) {
      pRangeEnd = pCurrent;
      pCurrent = pCurrent->right;
    } else {
      pCurrent = pCurrent->left;
    }
  }
  RBNode5* it = pRangeEnd;
  if (it == end || key < it->m10) {
    RefPair5 tmp;
    SavePair p(key, tmp);
    SavePairResult r;
    DoInsertValue(&r, it, p, TrueTag5());
    it = r.node;
  }
  return it->val;
}

// @ 0x006b3760
void __cdecl SP_RegisterSaveArea(uint32_t key, void* a, void* b)
{
  g_m5.Index(key) = RefPair5(a, b);
}

// @ 0x006b37d0
void SP_CreateDefaultSaveAreas()
{
  cString6 str;
  SaveRef6 out;
  Ref6b out2;
  SaveObj6* s;
  bool ok;

  str.Load(0x19f76d11, 0x5ca8d99, L"Pictures");
  ok = CreateDirectorySave(0xa0214b, str.GetText(), &out.p, 0x11ac196);
  s = out.p;
  if (ok) RegisterSaveArea(0x11ac196, s, 0);
  str.Load(0x19f76d11, 0x5ca8d98, L"Movies");
  REL6(s);
  ok = CreateDirectorySave(0xa0214b, str.GetText(), &out.p, 0x11ac197);
  s = out.p;
  if (ok) RegisterSaveArea(0x11ac197, s, 0);
  str.Load(0x19f76d11, 0x5ca8d9a, L"Animations");
  REL6(s);
  ok = CreateDirectorySave(0xa0214b, str.GetText(), &out.p, 0x11ac198);
  s = out.p;
  if (ok) RegisterSaveArea(0x11ac198, s, 0);
  REL6(s);
  ok = CreateDirectorySave(0xa02151, L"Games/Game0", &out.p, 0x4729a47);
  s = out.p;
  if (ok) RegisterSaveArea(0x4729a47, s, 0);
  REL6(s);
  ok = CreateDirectorySave(0xa02151, L"Preferences", &out.p, 0x11ac192);
  s = out.p;
  if (ok) RegisterSaveArea(0x11ac192, s, 0);

  if (g_editorMode6 == 0) {
    REL6(s);
    SAVE_DIR6(0xa02151, L"Creatures", 0x11ac199);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Buildings", 0x11ac19a);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Vehicles", 0x11ac19b);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Cells", 0x90368ea3);
    REL6(s);
    SAVE_DIR6(0xa02151, L"UFOs", 0x90368ea2);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Plants", 0x90368ea0);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Adventures", 0x86ca01c9);
  } else {
    REL6(s);
    ok = CreateLocationSave(0xa02151, L"EditorSaves", &out.p, 0x11ac199, 1);
    s = out.p;
    if (ok) {
      RegisterSaveArea(0x11ac199, s, 0);
      RegisterSaveArea(0x11ac19a, s, 0);
      RegisterSaveArea(0x11ac19b, s, 0);
      RegisterSaveArea(0x90368ea3, s, 0);
      RegisterSaveArea(0x90368ea2, s, 0);
      RegisterSaveArea(0x90368ea0, s, 0);
      RegisterSaveArea(0x86ca01c9, s, 0);
    }
  }

  if (g_appProps6->desc->flag118 == 0) {
    REL6(s);
    SAVE_DIR6(0xa02151, L"CityMusic", 0x500efc6);
  }

  if (g_serverMode6 == 0) {
    REL6(s);
    SAVE_DIR6(0xa02151, L"Cache", 0x11ac19c);
    REL6(s);
    SAVE_DIR6(0xa02151, L"Server", 0x11ac19d);
  } else {
    if (g_appProps6->desc->flag118 == 0) {
      REL6(s);
      ok = CreatePackageSave(0xa02151, g_dir13ec468, L"Pollination.package", &out.p);
    } else {
      REL6(s);
      ok = CreateServerCacheSave(0xa02151, g_dir13ec468, L"ServerCache.package", &out.p);
    }
    s = out.p;
    if (ok) {
      RegisterSaveArea(0x11ac19c, s, 0);
      RegisterSaveArea(0x11ac19d, s, 0);
    }
  }

  if (g_appProps6->desc->flag118 == 0) {
    REL6(s);
    ok = CreateLocationSave(0xa02151, L"Planets", &out.p, 0x31389b5, g_serverMode6);
    s = out.p;
    if (ok) RegisterSaveArea(0x31389b5, s, 0);
  }
  REL6(s);
  ok = CreateLocationSave(0xa02151, L"RigblockInfo", &out.p, 0x49a3d83, g_serverMode6);
  s = out.p;
  if (ok) RegisterSaveArea(0x49a3d83, s, 0);

  if (g_gfxMode6 == 0) {
    REL6(s);
    ok = CreateLocationSave(0xa02151, L"GraphicsCache", &out.p, 0x11ac1ac, g_serverMode6);
    if (!ok) goto done;
  } else {
    if (g_serverMode6 == 0) {
      REL6(s);
      ok = CreateGraphicsDir(0xa02151, L"GraphicsCache", &out.p, &out2.p, 0xb1e36ca3, 0x11ac1ac);
    } else if (g_appProps6->GetDescription(FNV1_String8("UseBigPackedDatabases", 0x811c9dc5, 1))) {
      REL6(s);
      ok = CreateCachedDirectorySave(0xa02151, g_dir13ec468, L"GraphicsCache.package", &out.p, &out2.p, 0xb1e36ca3);
    } else {
      REL6(s);
      ok = CreateGraphicsPackage(0xa02151, g_dir13ec468, L"GraphicsCache.package", &out.p, &out2.p, 0xb1e36ca3);
    }
    if (!ok) goto done;
  }
  RegisterSaveArea(0x11ac1ac, out.p, out2.p);
done:;
}

// @ 0x006b4010
bool SP_SaveNamedResource(KeyRef6* key, const wchar_t* name, Res6* res)
{
  if (res == 0) return false;
  ResMgr6* mgr = GetResMgr6();
  WStr6 str;
  Key3 k;
  int dot;
  k.inst = key->inst;
  k.type = key->type;
  k.group = key->group;
  str.b = str.e = str.cap = 0;
  str.Init(name);
  dot = str.rfind(L'.', -1);
  Res6* r2 = 0;
  if (res->GetKind() == 0x34728492) {
    k.group = res->GetGroup();
    r2 = res;
  }
  if (dot == -1 && r2) {
    const wchar_t* ext = r2->GetName(k.type);
    if (ext == 0) {
      ext = mgr->GetExt(k.type);
      if (ext) r2->SetName(ext, k.type);
    }
    str.push_back(L'.');
    if (ext) str.append(ext);
    else FormatHex6(&str, L"0x%08x", k.type);
  }
  SPKeyFromName(&k.inst, str.b, k.type, k.group);
  if (r2) {
    wchar_t buf[256];
    if (r2->GetPath(&k.inst, buf)) {
      if (_wcsicmp(buf, str.b) != 0) return false;
    } else {
      mgr->SetName(&k.inst, str.b);
    }
  }
  key->inst = k.inst;
  key->type = k.type;
  key->group = k.group;
  Fmt6* fmt = (Fmt6*)mgr->GetFormat(k.type, -1);
  if (fmt == 0) return false;
  IStream6* strm = 0;
  if (res->Open(&k.inst, &strm, 2, 2, 1, 0)) {
    bool r = fmt->Write(key, strm, 0, k.type);
    strm->Close();
    if (strm) strm->Release();
    return r;
  }
  if (strm) strm->Release();
  return false;
}
