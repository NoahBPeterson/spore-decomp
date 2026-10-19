// Slice s0061e250: SP::Pollen paint/upload helper objects and eastl string trim helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "../s00622f20/s00622f20.h"

extern "C" unsigned int __cdecl strlen(const char*);
extern "C" unsigned int __cdecl wcslen(const wchar_t*);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
#pragma intrinsic(memmove)
#pragma intrinsic(strlen, wcslen)

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void*);
extern "C" __declspec(dllimport) void* __cdecl memcpy(void*, const void*, unsigned int);

// ---- data / vtable symbols referenced by constructors and destructors ----
extern "C" char V_13f1ab0[];
extern "C" char V_13ef094[];
extern "C" char V_13fcaa8[];
extern "C" char V_13fcaa4[];
extern "C" char V_13fcab8[];
extern "C" char V_13fcabc[];
extern "C" char V_13fcac4[];
extern "C" char V_13eb394[];
extern "C" char V_13eb938[];
extern wchar_t gEmptyStringW[];  // 0x01667bac

// opaque thiscall callees
extern "C" void F_93c440(void* dst, const wchar_t* first, int last);  // cdecl, 3 args

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<char> trim helpers (find_first_not_of / find_last_not_of + erase)
// ---------------------------------------------------------------------------------------------
struct String8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  void* mAllocator;
  String8* TrimLeft();
  String8* TrimRight();
  unsigned int find_last_not_of(const char* p, unsigned int position, unsigned int n) const;
  unsigned int find_last_not_of(const char* p, unsigned int position) const;
};

const char* FindFirstNotOf(const char* first1, const char* last1, const char* first2,
                           const char* last2);
const char* FindLastNotOf(const char* last1, const char* first1, const char* first2,
                          const char* last2);

// @ 0x0061eba0
String8* String8::TrimLeft() {
  char ws[3];
  ws[0] = ' ';
  ws[1] = '\t';
  ws[2] = 0;
  const char* wsEnd = ws;
  while (*wsEnd) ++wsEnd;
  const char* const p = FindFirstNotOf(mpBegin, mpEnd, ws, wsEnd);
  const unsigned int n = (p == mpEnd) ? 0xffffffffu : (unsigned int)(p - mpBegin);
  char* pDst = mpBegin;
  char* pSrc = pDst + n;
  if (pDst != pSrc) {
    memmove(pDst, pSrc, (mpEnd - pSrc) + 1);
    mpEnd = (char*)mpEnd + (pDst - pSrc);
  }
  return this;
}

// @ 0x0061ec30
String8* String8::TrimRight() {
  const char* const ws = " \t";
  const char* const p = FindLastNotOf(mpEnd, mpBegin, ws, ws + 2);
  const unsigned int n = (p == mpBegin) ? 0xffffffffu : (unsigned int)(p - mpBegin + 1);
  char* pDst = mpBegin + n;
  if (mpBegin != pDst) {
    memmove(mpBegin, pDst, (mpEnd - pDst) + 1);
    mpEnd = (char*)mpEnd + (mpBegin - pDst);
  }
  return this;
}

// ---------------------------------------------------------------------------------------------
// find_last_not_of(p, position) — the 3-argument overload inlined.
// ---------------------------------------------------------------------------------------------
// @ 0x0061e3c0
unsigned int String8::find_last_not_of(const char* p, unsigned int position) const {
  const unsigned int n = (unsigned int)strlen(p);
  char* const begin = mpBegin;
  const unsigned int len = (unsigned int)(mpEnd - begin);
  if (len == 0) return 0xffffffffu;
  const unsigned int lenMinus1 = len - 1;
  const unsigned int& pos = position < lenMinus1 ? position : lenMinus1;
  const char* const r = FindLastNotOf(begin + pos + 1, begin, p, p + n);
  if (r == begin) return 0xffffffffu;
  return (unsigned int)(r - begin) - 1;
}

// ---------------------------------------------------------------------------------------------
// MI transaction/event objects (two vtable pointers, atomic refcount, DateTime + Variant).
// ---------------------------------------------------------------------------------------------
struct BaseA {
  virtual void a0();
  virtual void a1();
};
struct BaseB {
  virtual void b0();
  virtual void b1();
};
struct RCInit {
  volatile long mRefCount;  // +0x08
  RCInit() { _InterlockedExchange(&mRefCount, 0); }
};
struct D18 {
  char pad[8];
  D18(int v);
};
struct D20 {
  char pad0[0x10];
  unsigned short mType;
  unsigned short mType2;
  void SetValue(const void* src);
  void Destroy(int);
  D20(const void* b) : mType(0), mType2(0) { SetValue(b); }
};

struct O96 : BaseA, BaseB, RCInit {
  void* m0c;  // +0x0c
  int m10;    // +0x10
  int m14;    // +0x14
  D18 m18;    // +0x18
  D20 m20;    // +0x20
  O96(void* a, const void* b);
  O96(void* a, int b, int c, const void* d);
  O96* DeletingDtor(unsigned int flags);
  virtual void a0();
};

// @ 0x0061e250
O96::O96(void* a, const void* b) : m0c(a), m10(0), m14(0), m18(1), m20(b) {}

// @ 0x0061e2c0
O96::O96(void* a, int b, int c, const void* d) : m0c(a), m10(b), m14(c), m18(1), m20(d) {}

// @ 0x0061e330
O96* O96::DeletingDtor(unsigned int flags) {
  D20& v20 = m20;
  if (v20.mType & 4) v20.Destroy(0);
  *(void**)((char*)this + 4) = V_13ef094;
  *(void**)this = V_13eb938;
  if (flags & 1) EASTL_allocator_deallocate(this);
  return this;
}

// ---------------------------------------------------------------------------------------------
// EA::ConvertToString8(out, wide)
// ---------------------------------------------------------------------------------------------
struct String8Tmp {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  void* mAllocator;
};

// @ 0x0061e430
void ConvertToString8(void* out, const wchar_t* wide) {
  const unsigned int n = (unsigned int)wcslen(wide);
  String8Tmp tmp;
  F_93c440(&tmp, wide + n - 0x10, -1);
  memcpy(out, tmp.mpBegin, (unsigned int)(tmp.mpEnd - tmp.mpBegin));
  if ((tmp.mpCapacity - tmp.mpBegin) > 1) {
    if (tmp.mpBegin) EASTL_allocator_deallocate(tmp.mpBegin);
  }
}

// ---------------------------------------------------------------------------------------------
// SP::Skinner::PaintSystem (two vtable pointers, critical section, refcounted members).
// ---------------------------------------------------------------------------------------------
struct PBase0 {
  void Ctor7(int a, int b, int c, int d, int e, int f, int g);
  ~PBase0();
};
struct PBase38 {
  void Ctor3(void* a, void* b, int c);
};
struct IRel8 {
  virtual void v0();
  virtual void v1();
  virtual int Release();
};

// Interface used by the Pollen file-processing object (m3c): buffer fetch at vtbl +0x44.
struct IBuf {
  virtual void s00();  virtual void s01();  virtual void s02();  virtual void s03();
  virtual void s04();  virtual void s05();  virtual void s06();  virtual void s07();
  virtual void s08();  virtual void s09();  virtual void s10();  virtual void s11();
  virtual void s12();  virtual void s13();  virtual void s14();  virtual void s15();
  virtual void s16();
  virtual unsigned int GetText(wchar_t* buf, unsigned int count);  // vtbl +0x44
};

// The argument object passed to ProcessFile; member at +8 exposes a lookup at vtbl +0xc.
struct IArg8 {
  virtual void a0();  virtual void a1();  virtual void a2();
  virtual void* Lookup(unsigned int id);  // vtbl +0x0c
};
struct FileArg {
  void* m0;
  void* m4;
  IArg8* m8;
};

extern "C" void F_931fd0(void* p);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);

struct PaintSystem {
  void* mVt;                    // +0x00
  char pad04[0x20];             // +0x04..0x23
  int m24, m28, m2c, m30, m34;  // +0x24
  void* mVt2;                   // +0x38
  IRel8* m3c;                   // +0x3c
  IRel8* m40;                   // +0x40
  char pad44[4];                // +0x44
  uint32_t mCS[6];              // +0x48 (CRITICAL_SECTION)
  char pad60[8];                // +0x60
  bool m68, m69;                // +0x68
  char pad6a[2];
  int m6c;                      // +0x6c
  wchar_t* m70a;                // +0x70
  wchar_t* m70b;                // +0x74
  wchar_t* m70c;                // +0x78
  void* m70d;                   // +0x7c
  PaintSystem* Ctor();
  void Dtor();
  bool ProcessFile(FileArg* arg);   // 0x0061eac0
  bool F_61e040(void* out, int flag);  // 0x0061e040
  bool Helper886(FileArg* arg);     // 0x0061e740
};

// @ 0x0061e4a0
PaintSystem* PaintSystem::Ctor() {
  ((PBase0*)this)->Ctor7(0, 0, 0x12c, 0x3e8, 2, 0, 0);
  m28 = 0;
  m2c = 0;
  m30 = 0;
  mVt = V_13fcab8;
  m34 = -1;
  m24 = 0;
  ((PBase38*)this)->Ctor3((void*)0xed1cf0, this, 0);
  mVt2 = V_13eb394;
  mVt = V_13fcac4;
  mVt2 = V_13fcabc;
  m3c = 0;
  m40 = 0;
  InitializeCriticalSection(&mCS);
  m68 = 0;
  m69 = 0;
  m6c = 0x8000;
  m70a = gEmptyStringW;
  m70b = m70a;
  m70c = m70a + 1;
  return this;
}

// @ 0x0061e540
void PaintSystem::Dtor() {
  volatile void** const vt = (volatile void**)this;
  vt[0] = V_13fcac4;
  ((volatile void**)this)[0x0e] = V_13fcabc;
  if ((m70c - m70a) > 1) {
    if (m70a) EASTL_allocator_deallocate(m70a);
  }
  DeleteCriticalSection(&mCS);
  if (m40) m40->Release();
  if (m3c) m3c->Release();
  vt[0x0e] = V_13eb394;
  ((PBase0*)this)->~PBase0();
}

// ---------------------------------------------------------------------------------------------
// Remaining functions outlined (see partial.txt).
// ---------------------------------------------------------------------------------------------
// @ 0x0061e5b0  (HeaderHandler::operator())
bool HeaderHandlerCall(void* self, void* a, void* b);
bool HeaderHandlerCall(void* self, void* a, void* b) {
  (void)self;
  (void)a;
  (void)b;
  return false;
}

// @ 0x0061e740
bool PaintSystem::Helper886(FileArg* arg) {
  (void)arg;
  return true;
}

// ---------------------------------------------------------------------------------------------
// PollenProcessFile — compare the current text buffer against a freshly fetched one.
// ---------------------------------------------------------------------------------------------
// @ 0x0061eac0
bool PaintSystem::ProcessFile(FileArg* arg) {
  if (arg->m8) {
    void* p = arg->m8->Lookup(0x60419efu);
    if (p) F_931fd0((char*)p + 0xc);
  }
  if (!m69) {
    wchar_t cur[0x104];
    if (F_61e040(cur, 1)) {
      wchar_t next[0x104];
      const unsigned int n = ((IBuf*)m3c)->GetText(next, 0x104u);
      if (n > 0) {
        const wchar_t* a = next;
        const wchar_t* b = cur;
        while (*a && *a == *b) {
          ++a;
          ++b;
        }
        if (*a != *b) {
          return Helper886(arg);
        }
      }
    }
  }
  void* const cs = mCS;
  EnterCriticalSection(cs);
  m68 = 0;
  LeaveCriticalSection(cs);
  return true;
}
}  // namespace Pollen
}  // namespace SP
