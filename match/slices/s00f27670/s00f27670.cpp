// Slice s00f27670.  Editor/Simulator scenario helpers.  Built
// /O2 /MD /Gy /TP /arch:SSE (scalar SSE used for float clears).

typedef unsigned int uint;
typedef unsigned int size_t;
extern "C" {
  int  sub_eece20(void*);
  void* sub_00572590(void*);
  void* __cdecl FUN_00f473a0(unsigned size, const char* name, int a, int b, int c, int d);
  void  __cdecl FUN_00f47380(void* p);
  void  __cdecl FUN_00720200(void* a, void* b, void* c);
  void  __cdecl FUN_00f25ea0(void* a, void* b, void* c);
}
struct CBase { void dtor(); };  // 0x006b5240 base destructor
extern "C" size_t __cdecl wcslen(const wchar_t*);

struct CS {
  char _pad[0x14];
  int f14;
  int f18;
  char _pad1c[0x24 - 0x1c];
  int f24;
  int f28;
  int GetText();
};

struct StrObj {
  uint f00;
  char _pad4[0x14 - 4];
  int f14;
  int f18;
  char _pad1c[0x24 - 0x1c];
  int f24;
  int f28;
  int fn277f0();
  bool fn278b0();
};

// @ 0x00f278b0
bool StrObj::fn278b0() {
  bool r = false;
  if (sub_eece20(this) == (int)0xcf56099a) {
    uint t = f00;
    if (t == 0x90c48d09 || t == 0x3144b430) r = true;
    else if (fn277f0()) r = true;
  }
  return r;
}

struct Elem { char _pad4[4]; CS s; char _tail[0x40 - sizeof(CS)]; };
// sizeof(Elem) == 0x44

// @ 0x00f278f0
bool fn278f0(int* range) {
  if ((range[1] - range[0]) / 0x44 == 0) return false;
  for (int i = 0; i < (range[1] - range[0]) / 0x44; ++i) {
    Elem* e = (Elem*)(range[0] + i * 0x44);
    int len;
    if (e->s.f28 != 0 && e->s.f24 != 0)
      len = (int)wcslen((const wchar_t*)e->s.GetText());
    else
      len = (e->s.f18 - e->s.f14) >> 1;
    if (len != 0) return true;
  }
  return false;
}

struct Zeroed {
  float f00, f04, f08, f0c, f10, f14, f18;
  int i1c, i20, i24;
  int _pad28, _pad2c;
  int i30;
  Zeroed* fn280b0();
};

// @ 0x00f280b0
Zeroed* Zeroed::fn280b0() {
  f00 = 0.0f; f04 = 0.0f; f08 = 0.0f; f0c = 0.0f;
  f10 = 0.0f; f14 = 0.0f; f18 = 0.0f;
  i1c = 0; i20 = 0; i24 = 0; i30 = 0;
  return this;
}

// @ 0x00f27fc0  lower_bound over 0x18-stride records
int fn27fc0(int begin, int end, uint* key) {
  int n = (end - begin) / 0x18;
  while (n > 0) {
    int half = n >> 1;
    uint* mid = (uint*)(begin + half * 0x18);
    bool less;
    if (*mid != key[0])
      less = *mid < key[0];
    else if (mid[2] != key[2])
      less = mid[2] < key[2];
    else
      less = mid[1] < key[1];
    if (less) {
      begin = (int)(mid + 6);
      n = n + (-1 - half);
    } else {
      n = half;
    }
  }
  return begin;
}

// ---------------------------------------------------------------------------
// Not fully reconstructed.

// @ 0x00f27670
bool fn27670(void* a) { (void)a; return false; }
// @ 0x00f27730
bool fn27730(void* a) { (void)a; return false; }
// @ 0x00f277f0
int StrObj::fn277f0() { return 0; }
// @ 0x00f27990
void fn27990(void* a) { (void)a; }
// @ 0x00f27d80
void fn27d80(void* a) { (void)a; }
// @ 0x00f27e00
void fn27e00(void* a) { (void)a; }
// @ 0x00f27ee0
void fn27ee0(void* a, void* b) { (void)a; (void)b; }
struct CStr {
  char  _pad00[0x14];  // 0x00..0x13
  char* mBegin1;       // +0x14
  char* mCap1;         // +0x18
  char* mEnd1;         // +0x1c
  char  _pad20[0x0c];  // 0x20..0x2b
  char* mBegin2;       // +0x2c
  char* mCap2;         // +0x30
  char* mEnd2;         // +0x34
  ~CStr();
};
// @ 0x00f280f0
CStr::~CStr()
{
  if (((((int)(mEnd2 - mBegin2)) & ~1) > 2) && mBegin2) FUN_00f47380(mBegin2);
  if (((((int)(mEnd1 - mBegin1)) & ~1) > 2) && mBegin1) FUN_00f47380(mBegin1);
  ((CBase*)this)->dtor();
}
struct Vec18 {
  char* begin;   // +0x00
  char* end;     // +0x04
  char* cap;     // +0x08
  void reserve(unsigned n);
};
// @ 0x00f28140
void Vec18::reserve(unsigned n)
{
  unsigned capCount = (unsigned)((cap - begin) / 0x18);
  if (n > capCount) {
    char* p;
    if (n)
      p = (char*)FUN_00f473a0(n * 0x18, (const char*)0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
    else
      p = 0;
    FUN_00720200(begin, end, p);
    if (begin)
      FUN_00f47380(begin);
    unsigned count = (unsigned)((end - begin) / 0x18);
    begin = p;
    end = p + count * 0x18;
    cap = p + n * 0x18;
  }
}
struct AllocHdr { int mOwner; };  // 4-byte allocation header before the element buffer

struct Vec38 {
  char* begin;   // +0x00
  char* end;     // +0x04
  char* cap;     // +0x08
  void reserve(unsigned n);
};
// @ 0x00f28280
void Vec38::reserve(unsigned n)
{
  unsigned capCount = (unsigned)((cap - begin) / 0x38);
  if (n > capCount) {
    char* p;
    if (n)
      p = (char*)FUN_00f473a0(n * 0x38, (const char*)0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
    else
      p = 0;
    FUN_00f25ea0(begin, end, p);
    if (begin && ((AllocHdr*)begin)[-1].mOwner != 0)
      FUN_00f47380(begin);
    unsigned count = (unsigned)((end - begin) / 0x38);
    begin = p;
    end = p + count * 0x38;
    cap = p + n * 0x38;
  }
}
// @ 0x00f28380
char fn28380(void* a, int b, int c) { (void)a; (void)b; (void)c; return 1; }
// @ 0x00f28480
char fn28480(void* a, int b, int c) { (void)a; (void)b; (void)c; return 1; }
// @ 0x00f28580
char fn28580(void* a, int b, int c) { (void)a; (void)b; (void)c; return 1; }
