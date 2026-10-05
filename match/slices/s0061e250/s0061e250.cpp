// Slice s0061e250: SP::Pollen paint/upload helper objects and eastl string trim helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "../s00622f20/s00622f20.h"

extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
#pragma intrinsic(memmove)

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
// Remaining functions outlined (see partial.txt).
// ---------------------------------------------------------------------------------------------
// @ 0x0061e250
void* PollenCtor92(void* self, void* a, void* b);
void* PollenCtor92(void* self, void* a, void* b) {
  (void)a;
  (void)b;
  return self;
}

// @ 0x0061e2c0
void* PollenCtor98(void* self, void* a, void* b, void* c, void* d);
void* PollenCtor98(void* self, void* a, void* b, void* c, void* d) {
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  return self;
}

// @ 0x0061e330
void* PollenDtor54(void* self, unsigned flags);
void* PollenDtor54(void* self, unsigned flags) {
  (void)flags;
  return self;
}

// @ 0x0061e3c0
long PollenFindLastNotOf(String8* self, const char* s, unsigned int pos);
long PollenFindLastNotOf(String8* self, const char* s, unsigned int pos) {
  (void)self;
  (void)s;
  (void)pos;
  return -1;
}

// @ 0x0061e430
void PollenConvertToString8(void* out, void* wide);
void PollenConvertToString8(void* out, void* wide) {
  (void)out;
  (void)wide;
}

// @ 0x0061e4a0
void* PaintSystemCtor(void* self);
void* PaintSystemCtor(void* self) {
  return self;
}

// @ 0x0061e540
void PaintSystemDtor(void* self);
void PaintSystemDtor(void* self) {
  (void)self;
}

// @ 0x0061e5b0  (HeaderHandler::operator())
bool HeaderHandlerCall(void* self, void* a, void* b);
bool HeaderHandlerCall(void* self, void* a, void* b) {
  (void)self;
  (void)a;
  (void)b;
  return false;
}

// @ 0x0061e740
void* PollenHelper886(void* self, void* a);
void* PollenHelper886(void* self, void* a) {
  (void)a;
  return self;
}

// @ 0x0061eac0
bool PollenProcessFile(void* self, void* a);
bool PollenProcessFile(void* self, void* a) {
  (void)self;
  (void)a;
  return true;
}
}  // namespace Pollen
}  // namespace SP
