// Slice s0061d240: SP::Pollen asset-feed/edit-feed transactions plus eastl string/search
// helpers. Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "../s00622f20/s00622f20.h"

extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
#pragma intrinsic(memmove)

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};

// ---- eastl::basic_string<char>::erase(position, n) ------------------------------------------
struct String8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  void* mAllocator;
  String8* erase(unsigned int position, unsigned int n);
};

// @ 0x0061e200
String8* String8::erase(unsigned int position, unsigned int n) {
  unsigned int nRemaining = (unsigned int)(mpEnd - mpBegin) - position;
  if (n > nRemaining) n = nRemaining;
  char* pDst = mpBegin + position;
  char* pSrc = pDst + n;
  if (pDst != pSrc) {
    memmove(pDst, pSrc, (mpEnd - pSrc) + 1);
    mpEnd = (char*)mpEnd + (pDst - pSrc);
  }
  return this;
}

// ---- ref-counted reference wrapper (eastl::intrusive_ptr-like ctor) -------------------------
struct IRefObject {
  virtual int slot0();    // +0
  virtual int AddRef();   // +4
  virtual int Release();  // +8
};
struct RefObject {
  IRefObject* mpObject;
  RefObject(IRefObject* p);
};

// @ 0x0061df40
RefObject::RefObject(IRefObject* p) : mpObject(p) {
  if (p) p->AddRef();
}

// ---- critical-section guarded bool getter ---------------------------------------------------
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void*);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void*);
struct GuardedFlag {
  char pad0[0x48];
  uint32_t mCriticalSection[6];  // +0x48 (CRITICAL_SECTION, 0x18 bytes)
  char pad1[0x68 - 0x60];
  bool mbFlag;  // +0x68
  bool Get() const;
};

// @ 0x0061e180
bool GuardedFlag::Get() const {
  EnterCriticalSection((void*)mCriticalSection);
  bool b = mbFlag;
  LeaveCriticalSection((void*)mCriticalSection);
  return b;
}

// ---- small wrapper --------------------------------------------------------------------------
int SubHelper(int a, int b, int c, int d);  // 0x0093abd0

// @ 0x0061dea0
int PollenWrapper(int a, int b) {
  SubHelper(a, b, -1, 0);
  return a;
}

// ---- eastl search helpers -------------------------------------------------------------------
// @ 0x0061df60
const char* FindFirstNotOf(const char* first1, const char* last1, const char* first2,
                           const char* last2) {
  for (; first1 != last1; ++first1) {
    const char* it = first2;
    for (; it != last2; ++it) {
      if (*first1 == *it) break;
    }
    if (it == last2) return first1;
  }
  return last1;
}

// @ 0x0061dfa0
const char* FindLastNotOf(const char* last1, const char* first1, const char* first2,
                          const char* last2) {
  while (last1 != first1) {
    --last1;
    const char* it = first2;
    for (; it != last2; ++it) {
      if (*last1 == *it) break;
    }
    if (it == last2) return last1;
  }
  return first1;
}

// ---------------------------------------------------------------------------------------------
// Remaining functions outlined (see partial.txt).
// ---------------------------------------------------------------------------------------------
class cHandshakeTransaction : public cITransaction {
 public:
  uint8_t pad[0x70 - 0x8];
  bool HandleResult(int code, void* result, void* queue);
};

// @ 0x0061de00
bool cHandshakeTransaction::HandleResult(int code, void* result, void* queue) {
  (void)code;
  (void)result;
  (void)queue;
  return false;
}

// @ 0x0061d240
void* AssetHelper288(void* self, void* a);
void* AssetHelper288(void* self, void* a) {
  (void)a;
  return self;
}

// @ 0x0061d380
bool GetAssetFeedConstructRequest(void* self, void* ppRequest);
bool GetAssetFeedConstructRequest(void* self, void* ppRequest) {
  (void)self;
  (void)ppRequest;
  return false;
}

// @ 0x0061d960
bool EditFeedConstructRequest(void* self, void* ppRequest);
bool EditFeedConstructRequest(void* self, void* ppRequest) {
  (void)self;
  (void)ppRequest;
  return false;
}

// @ 0x0061dfe0
void PollenNotifyHelper(void* self);
void PollenNotifyHelper(void* self) {
  (void)self;
}

// @ 0x0061e040
void* PollenHelper311(void* self, void* a, void* b);
void* PollenHelper311(void* self, void* a, void* b) {
  (void)a;
  (void)b;
  return self;
}

// @ 0x0061e1a0
void* PollenCtor78(void* self, void* a, void* b);
void* PollenCtor78(void* self, void* a, void* b) {
  (void)a;
  (void)b;
  return self;
}
}  // namespace Pollen
}  // namespace SP
