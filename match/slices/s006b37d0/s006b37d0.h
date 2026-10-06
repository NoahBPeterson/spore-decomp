#pragma once
// Stub declarations for slice s006b37d0 (SP default save areas).
#include "types.h"

// object with a counter at +0x40 (0x6b42f0).
struct Counter40 {
  uint32_t pad[0x10];
  uint32_t m40;
  bool Inc();
};

// secondary-vtable object referenced through a pointer slot (0x6b4390).
struct SecBase6 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual uint32_t Call0c(uint32_t);
};
struct ObjSec6 { uint32_t pad0; SecBase6 sec; };

// job holder at 0x01604b48 with an EA mutex.
struct Mutex6 { Mutex6(int, int); ~Mutex6(); };
struct Job6 { void GetStatus(); };
struct JobPtr6 { void* p; JobPtr6() : p(0) {} ~JobPtr6(); };
struct JobHolder6 {
  JobPtr6 job;      // +0x00
  uint32_t pad;     // +0x04
  Mutex6 mutex;     // +0x08
  JobHolder6();
  ~JobHolder6();
};
extern JobHolder6 g_jobHolder6;   // 0x01604b48
extern uint32_t  g_1604b80;
inline void* operator new(uint32_t, void* p) { return p; }

// ---- save-area setup (0x6b37d0) ----
struct IRef6 { virtual void v0(); virtual void Release(); };
struct SaveObj6 { uint32_t pad0; IRef6 ref; };   // refcounted through the +4 subobject
struct SaveRef6 { SaveObj6* p; SaveRef6() : p(0) {} ~SaveRef6() { if (p) p->ref.Release(); } };
struct Ref6b { IRef6* p; Ref6b() : p(0) {} ~Ref6b() { if (p) p->Release(); } };
struct cString6 {
  cString6();
  ~cString6();
  void Load(uint32_t tableId, uint32_t instId, const wchar_t* dflt);
  const wchar_t* GetText();
  char data[8];
};
bool CreateDirectorySave(uint32_t root, const wchar_t* name, SaveObj6** out, uint32_t key);
bool CreateLocationSave(uint32_t root, const wchar_t* name, SaveObj6** out, uint32_t key, uint32_t flag);
bool CreatePackageSave(uint32_t root, const void* dir, const wchar_t* name, SaveObj6** out);
bool CreateServerCacheSave(uint32_t root, const void* dir, const wchar_t* name, SaveObj6** out);
bool CreateGraphicsDir(uint32_t root, const wchar_t* name, SaveObj6** out, IRef6** out2, uint32_t a, uint32_t b);
bool CreateGraphicsPackage(uint32_t root, const void* dir, const wchar_t* name, SaveObj6** out, IRef6** out2, uint32_t a);
bool CreateCachedDirectorySave(uint32_t root, const void* dir, const wchar_t* name, SaveObj6** out, IRef6** out2, uint32_t a);
void RegisterSaveArea(uint32_t key, SaveObj6* o, IRef6* o2);
uint32_t FNV1_String8(const char* s, uint32_t seed, int flag);
struct PropDesc6 { char pad[0x118]; int flag118; };
struct PropList6 { char pad[0x3c]; PropDesc6* desc; };
struct PropListFn6 { bool GetDescription(uint32_t hash); char pad[0x3c]; PropDesc6* desc; };
extern PropListFn6* g_appProps6;   // 0x15fd918
extern char g_editorMode6;         // 0x16046d8
extern char g_serverMode6;         // 0x152fbcc
extern char g_gfxMode6;            // 0x152fbcd
extern const char g_dir13ec468[];  // 0x13ec468

// ---- save-named-resource (0x6b4010) ----
struct WStr6 {
  wchar_t* b; wchar_t* e; wchar_t* cap; void* alloc;
  void Init(const wchar_t* s);
  int rfind(wchar_t c, int pos);
  void push_back(wchar_t c);
  void append(const wchar_t* s);
  ~WStr6() { if (((cap - b) & ~1) > 2 && b) operator delete[](b); }
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
ResMgr6* GetResMgr6();
void FormatHex6(WStr6* s, const wchar_t* fmt, uint32_t v);
void SPKeyFromName(void* k, const wchar_t* name, uint32_t type, uint32_t group);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);

// ---- editor-resource job (0x6b4400..0x6b4610) ----
struct IRefC { virtual void v0(); virtual void Release(); };
struct SvcBase6 {
  V6(0) V6(1) V6(2) V6(3) V6(4) V6(5) V6(6) V6(7) V6(8) V6(9) V6(10) V6(11) V6(12) V6(13) V6(14) V6(15)
  V6(16) V6(17)
  virtual uint32_t Detach();   // 0x48
};
struct SvcA6 : SvcBase6 {
  bool Check(void* key, uint32_t size);
  bool Pack(void* data, uint32_t size, uint32_t* pOut, uint32_t* pLen, uint16_t* pFlag);
  bool Unpack(void* key, uint32_t a, uint32_t b, uint32_t size, uint32_t flag);
};
struct SvcB6 : SvcBase6 {
  bool Check(void* key, uint32_t size);
  bool Pack(void* data, uint32_t size, uint32_t* pOut, uint32_t* pLen, uint16_t* pFlag);
  bool Unpack(void* key, uint32_t a, uint32_t b, uint32_t size, uint32_t flag);
};
struct Alloc6 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual void Free(void* p, uint32_t n); };
struct AllocHolder6 { Alloc6* GetAllocator(); };
struct Provider6 {   // object at +4 of a SvcProvider
  virtual void v0(); virtual void Release();
  virtual void v2();
  virtual void* Query(uint32_t id);   // 0x0c
};
struct ProvObj6 { uint32_t pad; Provider6 sec; };
struct ProvPtr6 {
  ProvObj6* p;
  ~ProvPtr6() { if (p) p->sec.Release(); }
};
struct Stream6 {
  ~Stream6();
  void* GetData();
  void Attach(int a, int b);
  void SetData(uint32_t p, uint32_t n, int a, int b, uint32_t c);
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
  virtual void Flush();    // 0x18
  virtual uint32_t Size(); // 0x1c
  char d[0x24];
};
struct IRefPtr6 { IRefC* p; ~IRefPtr6() { if (p) p->Release(); } };
struct JobCtx6 { void Done(int n); };
struct BG6 { virtual void bg0(); virtual ~BG6() {} };
struct ER6 { virtual void er0(); virtual ~ER6() {} };
struct Job6B : ER6, BG6 {
  uint32_t pad8;
  IRefPtr6 m0c;
  uint32_t m10;
  uint32_t m14;
  uint32_t pad18;
  ProvPtr6 m1c;
  Stream6 strm;
  uint32_t m48, m4c, m50;
  uint16_t m54;
  ~Job6B();
  bool Prepare(JobCtx6* c);
  bool Finish(JobCtx6* c);
};
