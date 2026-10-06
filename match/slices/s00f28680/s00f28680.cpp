// Slice s00f28680.  Scenario/building-data helpers.  Built /O2 /MD /Gy /TP.

typedef unsigned int uint;
typedef unsigned int size_t;
extern "C" size_t __cdecl wcslen(const wchar_t*);

struct Str {
  char _pad[0x10];
  int Assign(const wchar_t* p, const wchar_t* e);
};

extern "C" char A_01667bac;
extern "C" char B_01667bae;

struct CStrCtor {
  char _pad[0x14];
  void ctor();
};

struct Obj8c {
  int f00;
  CStrCtor cs;          // +0x04
  int a18, a1c, a20;    // +0x18
  int _g24;             // +0x24
  int a28, a2c;         // +0x28
  int a30, a34, a38;    // +0x30
  int _g3c;
  int a40;              // +0x40
  Obj8c* init();
};

// @ 0x00f28b30
Obj8c* Obj8c::init() {
  f00 = 0;
  cs.ctor();
  a18 = (int)&A_01667bac;
  a1c = (int)&A_01667bac;
  a20 = (int)&B_01667bae;
  a28 = 0;
  a2c = 0;
  a30 = (int)&A_01667bac;
  a34 = (int)&A_01667bac;
  a38 = (int)&B_01667bae;
  a40 = 0;
  return this;
}

struct ObjC {
  char _pad[0x14];
  Str s;                // +0x14
  int f24;              // +0x24
  ObjC* fn28c10(short* p);
};

// @ 0x00f28c10
ObjC* ObjC::fn28c10(short* p) {
  f24 = 0;
  const wchar_t* q = (const wchar_t*)p;
  while (*q) ++q;
  int len = (int)(q - (const wchar_t*)p);
  s.Assign((const wchar_t*)p, (const wchar_t*)p + len);
  return this;
}

struct ObjB {
  char _pad[0x279c];
  Str s;                // +0x279c
  int f27ac;            // +0x27ac
  void fn293b0(short* p);
};

// @ 0x00f293b0
void ObjB::fn293b0(short* p) {
  f27ac = 0;
  const wchar_t* q = (const wchar_t*)p;
  while (*q) ++q;
  int len = (int)(q - (const wchar_t*)p);
  s.Assign((const wchar_t*)p, (const wchar_t*)p + len);
}

// ---------------------------------------------------------------------------
// Not fully reconstructed.

// @ 0x00f28680
void fn28680(void* a, void* b) { (void)a; (void)b; }
// @ 0x00f28780
void fn28780(void* a, void* b) { (void)a; (void)b; }
// @ 0x00f28880
void fn28880(void* a) { (void)a; }
// @ 0x00f289d0
void fn289d0(void* a) { (void)a; }
// @ 0x00f28b80
int fn28b80(void* a, void* b) { (void)a; (void)b; return 1; }
// @ 0x00f28c50
int fn28c50(void* a, void* b) { (void)a; (void)b; return 1; }
// @ 0x00f28ce0
void fn28ce0(void* a, void* b) { (void)a; (void)b; }
// @ 0x00f28dd0  eastl::vector<SP::cBuildingData,eastl::sp_vector_allocator>::erase
void* fn28dd0(void* a, void* b, void* c) { (void)a; (void)b; (void)c; return b; }
// @ 0x00f28e40
void fn28e40(void* a) { (void)a; }
// @ 0x00f29030
void fn29030(void* a) { (void)a; }
// @ 0x00f29170
void fn29170(void* a) { (void)a; }
// @ 0x00f292c0
void fn292c0(void* a, int n, void* b) { (void)a; (void)n; (void)b; }
// @ 0x00f29330
void* fn29330(void* a, void* b, void* c) { (void)a; (void)b; (void)c; return c; }
// @ 0x00f29410
void fn29410(void* a) { (void)a; }
