#pragma once
// Stub declarations for slice s006b27f0 (SP save-area registration).
#include "types.h"

// AutoRefCount pair value (cSPSaveArea) - same shape as slice 4's RefPair.
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

// eastl rbtree node holding a RefPair5 value at +0x14.
struct RBNode5;
struct RBNode5 {
  RBNode5* left;    // +0x00
  RBNode5* right;   // +0x04
  uint32_t m8;      // +0x08
  uint32_t mc;      // +0x0c
  uint32_t m10;     // +0x10
  RefPair5 val;     // +0x14
};

// object stored per save area (vtable slots 0x08 and 0x1c used here).
struct SaveObj5 {
  virtual void v0();
  virtual void v1();
  virtual void Call08();     // 0x08
  virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
  virtual void Call1c();     // 0x1c
};

// eastl::true_type: empty tag argument (1 byte; the caller leaves the slot's upper bytes as garbage).
struct TrueTag5 {};

// global save-area map (base 0x0152fdc4).
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

extern "C" void* RBTreeIncrement(void*);   // 0x00921580
extern void EFree5(void*);                 // 0x00f47380

// ---- save-file creation helpers (0x6b27f0 .. 0x6b3760) ---------------------------------------
struct IRef6 { virtual void AddRef(); virtual void Release(); };      // plain AddRef/Release interface
struct IRefSub { virtual void AddRef(); virtual void Release(); };    // refcount sub-object at +4 of the db objects

// eastl::basic_string<wchar_t, eastl::allocator> (no SSO): begin/end/capacity.
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

extern const wchar_t* GetDirFromID(uint32_t id);                 // 0x006886b0
extern void EnsureDirectoryExists(const wchar_t* dir);           // 0x00932ae0
extern IRef6* LRUCacheCreate(void* db, uint32_t arg);            // 0x006b0ed0
extern DbService* F_6b00a0(void* db, IRef6* cache);              // 0x006b00a0
extern void ReadExtensionMappingsFromPropFile(uint32_t group, void* db);   // 0x006b2110
extern IResManager6* GetManager6();                              // 0x0067dcd0
extern float g_13eb95c;                                          // 0x013eb95c
extern bool CreateDirectorySave(uint32_t id, const wchar_t* a, void* b, void* c);   // 0x006b2620
extern const wchar_t kEmpty13ec468[];                            // 0x0013ec468
