// Slice s00f25a40.  Editor "verb icon tray" / scenario serialization helpers and
// a second group of small __thiscall type predicates.  Built /O2 /MD /Gy /TP.

typedef unsigned int uint;
typedef unsigned short wchar16;
typedef unsigned int size_t;
extern "C" size_t __cdecl wcslen(const wchar_t*);

struct Vec3i { int x, y, z; };

extern "C" {
  int   sub_005f7930(void);
  void  sub_00572590(void*);
  int   sub_005f8a70(void*, void*);
  int   sub_0067dea0(void);
  int   sub_0067cb30(void);
}

// ---------------------------------------------------------------------------
// Group A: small type predicates.

struct DataObj {
  char _pad[4];
  uint f04;            // +0x04  type id
  char _pad8[0x18 - 8];
  uint f18;            // +0x18  sub type id
  char _pad1c[0x70 - 0x1c];
  void* f70;           // +0x70

  char fn25ed0();
  bool fn25ee0();
  bool fn25f20();
  bool fn25f60();
};

// @ 0x00f25ed0
char DataObj::fn25ed0() {
  return (char)(*(int*)((char*)f70 + 0x4a4) != -1);
}

// @ 0x00f25ee0
bool DataObj::fn25ee0() {
  uint t = f04;
  if (t == 0x24682294 || t == 0x476a98c7) {
    uint u = f18;
    if (u > 0x8f963dcb) {
      if (u == 0xc15695da) return false;
    } else {
      if (u == 0x8f963dcb || u == 0x1f2a25b6 || u == 0x2a5147a9) return false;
    }
  }
  return true;
}

// @ 0x00f25f20
bool DataObj::fn25f20() {
  uint t = f04;
  if (t == 0x24682294 || t == 0x476a98c7) {
    uint u = f18;
    if (u > 0xbc1041e6) {
      if (u == 0xc0b74287 || u == 0xf670aa43) return false;
    } else {
      if (u == 0xbc1041e6 || u == 0x7d433fad || u == 0x9ad7d4aa) return false;
    }
  }
  return true;
}

// @ 0x00f25f60
bool DataObj::fn25f60() {
  uint t = f04;
  if (t == 0x24682294 || t == 0x476a98c7 || t == 0x2b978c46) return false;
  return true;
}

// ---------------------------------------------------------------------------
// Helper objects used by the editor functions below.

struct PtrVec { bool Contains(void* p); };
struct CString { int GetText(); };
struct Mgr695b40 { void Add(void* p, const void* a, const wchar_t* s); };
struct Mgr6a3dd0 { void Do(); };
struct Mgrf37690 { void Do(void* p); };
struct Mgr71 { int* Find(void* a); };

extern "C" {
  int  sub_f37690(void*, void*);
  void* __stdcall sub_PropertyManager(void*);
  int  sub_f3f950(void*, void*);
  void sub_00695b40(void*, const void*, const wchar_t*);
}
extern char DAT_015aeb58;

unsigned g016c8474;
unsigned g016c8470;
unsigned g016c847c;
unsigned g016c8478;
void* g016c7aa4;

// @ 0x00f262e0
struct Tray262e0 {
  char _pad[0x2c54];
  int* begin;   // +0x2c54
  int* end;     // +0x2c58
  bool fn262e0();
};
bool Tray262e0::fn262e0() {
  PtrVec* v = (PtrVec*)sub_0067dea0();
  int* p = begin;
  int* e = end;
  while (p != e) {
    if (!v->Contains((void*)*p)) return false;
    ++p;
  }
  return true;
}

// @ 0x00f26330
struct Tray26330 {
  char _pad[0x18];
  char body[4];
  void fn26330();
};
void Tray26330::fn26330() {
  void* b = *(void**)((char*)g016c7aa4 + 0x18);
  if (b) {
    void* p = body;
    void* r = sub_PropertyManager(p);
    ((Mgr6a3dd0*)r)->Do();
    ((Mgrf37690*)b)->Do(p);
  }
}

// @ 0x00f26360
struct Tray26360 {
  char _pad[0x14];
  int f14;
  int f18;
  char _pad1c[0x24 - 0x1c];
  int f24;
  int f28;
  int fn26360();
  int fn26380();
};
int Tray26360::fn26360() {
  if (f28 != 0 && f24 != 0) return ((CString*)this)->GetText();
  return f14;
}

// @ 0x00f26380
int Tray26360::fn26380() {
  if (f28 != 0 && f24 != 0) {
    return (int)wcslen((const wchar_t*)((CString*)this)->GetText());
  }
  return (f18 - f14) >> 1;
}

// @ 0x00f264b0
float fn264b0(void* a) {
  Mgr71* m = *(Mgr71**)((char*)g016c7aa4 + 0x74);
  int i = (int)m->Find(a);
  if (i) return *(float*)(i + 0x484);
  return 0.0f;
}

// @ 0x00f26ac0
void fn26ac0(void* param) {
  int* p = ((int*(*)(void*))*(void**)((char*)param + 0x20))(param);
  if ((g016c8474 & 1) == 0) {
    g016c8474 |= 1;
    g016c8470 = *p = 0;
    return;
  }
  *p = (int)g016c8470;
}

// @ 0x00f26c60
void fn26c60(void* param) {
  int* p = ((int*(*)(void*))*(void**)((char*)param + 0x20))(param);
  if ((g016c847c & 1) == 0) {
    g016c847c |= 1;
    g016c8478 = *p = 0;
    return;
  }
  *p = (int)g016c8478;
}

// @ 0x00f26fd0
bool fn26fd0(Mgr695b40* self, int* range) {
  int* p = (int*)range[0];
  int* e = (int*)range[1];
  while (p != e) {
    if (p != (int*)-8) self->Add((char*)p + 8, &DAT_015aeb58, L"cScenarioClass");
    p = (int*)((char*)p + 0x27e8);
  }
  return true;
}

// ---------------------------------------------------------------------------
// Serialization / remaining functions (not fully reconstructed).

// @ 0x00f25a40
int fn25a40(void* a, int* out) { (void)a; if (out) *out = 0; return 1; }

// @ 0x00f25af0
char fn25af0(void* self) { (void)self; return 0; }

// @ 0x00f25d80
int fn25d80(void* a, void* b) { (void)a; (void)b; return 1; }

// @ 0x00f25f80
int fn25f80() { return 0; }

// @ 0x00f26230
void fn26230(void* self) { (void)self; }

// @ 0x00f263b0
char fn263b0(void* self, void* other) { (void)self; (void)other; return 0; }

// @ 0x00f26440
char fn26440(void* self, void* other) { (void)self; (void)other; return 0; }

// @ 0x00f264d0
void* fn264d0(void* a, int b, int c) { (void)a; (void)b; (void)c; return 0; }

// @ 0x00f26b00
void fn26b00(void* a, void* b) { (void)a; (void)b; }

// @ 0x00f26ca0
void fn26ca0(void* a, void* b) { (void)a; (void)b; }

// @ 0x00f26ef0
void fn26ef0(void* a, void* b) { (void)a; (void)b; }

// @ 0x00f27010
void fn27010(void* a, void* b) { (void)a; (void)b; }

// @ 0x00f270f0
int fn270f0(void* a, int* b) { (void)a; (void)b; return 1; }

// @ 0x00f27170
int fn27170(void* a, int b) { (void)a; (void)b; return 1; }

// @ 0x00f27200
void fn27200(void* a, void* b) { (void)a; (void)b; }

// @ 0x00f27430
char fn27430(void* a, void* b) { (void)a; (void)b; return 0; }
