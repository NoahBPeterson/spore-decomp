// src/game/SPEngine/SPLocaleManager.cpp -- migrated from slice(s) s00696c80, s006960f0, s00695140 by tools/migrate/rewrite.py
// Object file: SPEngine/SPLocaleManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* GetManager();         // 0x67dcd0
#include <wchar.h>
#include "EA/Allocator/ICoreAllocator.h"
#include <intrin.h>
#include "EA/Thread/Mutex.h"
#include "EA/Trace/Server.h"
#include <string.h>
#include <new>
#include "EA/CommandLine.h"

// ---- items of slice s00695140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void operator_delete_arr(void* p);                       // 0xf47380
extern "C" void* g_vtbl_a[];
extern "C" void* g_vtbl_b[];
#define VFN(o,off) (*(void***)(o))[(off)/4]
struct Ctl {
    char pad0[4];
    void* head;      // +4
    bool check(void* arg);
    void addThing(void* a, void* b);
};
static void destroy30(char* p, char* end)
{
    while (p < end)
    {
        char* d = *(char**)(p + 4);
        if (((*(int*)(p + 0xc) - (int)d) & 0xfffffffe) > 2 && d != 0)
            operator_delete_arr(d);
        p += 0x30;
    }
}
// ---- items of slice s00695140 end

// ---- items of slice s006960f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cLocaleManager;
}
extern wchar_t gEmptyString16[2];   // 0x1667bac — eastl empty wide-string sentinel
extern wchar_t gPathSep[];          // 0x13fa488 — L"\\"
void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void* p);
namespace eastl {
class allocator_s0069_60f0 { public:
  void deallocate(void* p) { ::operator delete(p); }
  void* allocate(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
    return ::operator new(n, pName, flags, debugFlags, file, line);
  }
};
}
namespace eastl {
struct FixedStringBase {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator_s0069_60f0 mOverflowAllocator;
  void* mpPoolBegin;

  FixedStringBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  FixedStringBase(void* pool) : mpBegin(0), mpEnd(0), mpCapacity(0) { mpPoolBegin = pool; }
  FixedStringBase& append(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x68cc10

  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
  // (cap - begin) cleared of its low bit, compared signed, then the begin / pool-begin identity.
  void DeallocateSelf() {
    if (((((int)((char*)mpCapacity - (char*)mpBegin)) & ~1) > 2) && mpBegin != 0 &&
        mpBegin != mpPoolBegin) {
      mOverflowAllocator.deallocate(mpBegin);
    }
  }
  ~FixedStringBase() { DeallocateSelf(); }
};
}
namespace eastl {
inline size_t CharStrlenW(const wchar_t* p) {
  const wchar_t* q = p;
  while (*q) ++q;
  return (size_t)(q - p);
}
}
namespace eastl {
struct FixedString16 : FixedStringBase {
  union {
    wchar_t mArray[1];
    char mBuffer[32];
  };

  FixedString16(const wchar_t* p);
  FixedString16(const FixedString16& x);
  FixedString16& operator=(const FixedString16& x);
};
}
namespace eastl {
struct WStr {
  wchar_t* mpBegin;      // +0
  wchar_t* mpEnd;        // +4
  wchar_t* mpCapacity;   // +8

  WStr& assign(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x423650
  WStr& Append(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x429580
  ~WStr() {
    if (((((int)((char*)mpCapacity - (char*)mpBegin)) & ~1) > 2) && mpBegin != 0)
      ::operator delete(mpBegin);
  }
};
}
namespace EA {
struct AtomicInt {
  int mValue;
  AtomicInt() { _InterlockedExchange((long*)&mValue, 0); }
};
}
namespace EA {
template <typename T>
class RefCountVTemplate_s0069_60f0 { public:
  virtual ~RefCountVTemplate_s0069_60f0() {}
  T mRefCount;
  RefCountVTemplate_s0069_60f0() : mRefCount() {}
};
}
namespace EA {
namespace Messaging {
class IMessageRC_s0069_60f0 { public:
  virtual ~IMessageRC_s0069_60f0() {}
};  // namespace Messaging
}
}
namespace EA {
namespace Allocator {
class ICoreAllocator_s0069_60f0 {
 public:
  static ICoreAllocator_s0069_60f0* GetDefaultAllocator();               // 0x925cb0
  virtual void* v00();
  virtual void* v04();
  virtual void* Allocate(size_t n, int flags, void* tag);     // vtable +0x08
  virtual void  Free(void* p, size_t n);                      // vtable +0x0c
};  // namespace Allocator
}
}
namespace EA {
namespace Locale {
void Init();                                                  // 0x883730
}
}
namespace EA {
namespace Locale {
int GetLocaleInfoString(int a, int b, wchar_t* out, int n, const void* locale);  // 0x880910
}
}
namespace EA {
namespace IO {
class Directory { public:
  static bool Exists(const wchar_t* path);                    // 0x9322b0
};  // namespace IO
}
}
namespace App {
using eastl::FixedString16;
}
namespace App {
class cLocaleChangeMessage : public EA::Messaging::IMessageRC_s0069_60f0, public EA::RefCountVTemplate_s0069_60f0<EA::AtomicInt> {
 public:
  FixedString16 mLocaleId;  // +0xc
  cLocaleChangeMessage(const FixedString16& id);
};
}
namespace SP {
using eastl::FixedString16;
}
namespace SP {
struct List16 {
  void* mNext;
  void* mPrev;
  EA::Allocator::ICoreAllocator_s0069_60f0* mAlloc;
  void* mZero;
};
}
namespace SP {
struct LocaleNode {
  LocaleNode* mNext;
  LocaleNode* mPrev;
  void* mValue;
};
}
namespace SP {
struct LocalePair { const wchar_t* mName; const wchar_t* mCode; };
}
namespace SP {
extern LocalePair g_localeTable[24];   // 0x152d6c8
}
namespace SP {
int LocaleCommonPrefix(const wchar_t* a, const wchar_t* b);  // 0x695c70
}
namespace SP {
bool FUN_0087fd10(int* a, int* b, char c);                   // 0x87fd10
}
namespace SP {
void* GetManager();                                          // 0x67dcd0 (resource manager)
}
namespace SP {
bool GetDirString(unsigned hash, void* out, int dflt);       // 0x688830
}
namespace SP {
class cLocaleManager : public EA::RefCountVTemplate_s0069_60f0<int> {
 public:
  bool mbInit;             // +8
  bool field9;             // +9
  bool fieldA;             // +0xa
  char padB;               // +0xb
  int fieldC;              // +0xc
  int field10;             // +0x10
  int field14;             // +0x14
  FixedString16 mLocaleId;  // +0x18
  void* mpStringManager;   // +0x4c
  List16 mList50;          // +0x50
  List16 mList60;          // +0x60

  cLocaleManager();

  // vtable 0x1403d34: +0 dtor, +4 AddRef, +8 Release, +0xc GetReferenceCount, +0x10 SetLocale,
  // +0x14 helper, +0x18 SetFromMatch, +0x1c FindMatchingLocale.
  virtual void* AddRef() { return 0; }                                   // vtable +0x04
  virtual void* Release() { return 0; }                                  // vtable +0x08
  virtual int GetReferenceCount() { return 0; }                          // vtable +0x0c
  virtual bool ApplyLocaleId(const FixedString16& id) { return mbInit; } // vtable +0x10
  virtual void* LocaleHelper() { return 0; }                             // vtable +0x14
  virtual bool SetFromMatch(const eastl::WStr& id);                      // vtable +0x18
  virtual const wchar_t* FindMatchingLocale();                           // vtable +0x1c

  bool Init(void* pCommandLine, void* pUnknown);                         // 0x6964c0
  bool GetDefaultLanguage(const FixedString16& locale);                  // 0x696a60
};
}
namespace SP {
class LocaleBroadcastBase {
 public:
  virtual ~LocaleBroadcastBase() {}
};
}
namespace SP {
class LocaleBroadcastMessage : public LocaleBroadcastBase {
 public:
  List16* mList;    // +4
};
}
namespace SP {
struct ILocaleBroadcastTarget {
virtual void* v00();
virtual void* v04();
virtual void* v08();
virtual void* v0c();
virtual void* v10();
virtual void* v14();
virtual void* v18();
virtual void* v1c();
virtual void* v20();
virtual void* v24();
virtual void* v28();
virtual void* v2c();
  virtual void* v30();
  virtual int   Dispatch(void* list, LocaleBroadcastMessage* msg);   // +0x34
};
}
// ---- items of slice s006960f0 end

// @ 0x00695c70
extern "C" int FUN_00695c70(const wchar_t* a, const wchar_t* b)
{
    int i = 0;
    if (a[0] != 0)
    {
        do
        {
            if (b[i] == 0)
                break;
            if ((wint_t)towlower(a[i]) != (wint_t)towlower(b[i]))
                break;
            ++i;
        } while (a[i] != 0);
    }
    return i;
}

// @ 0x00695cd0
extern "C" int __fastcall FUN_00695cd0(void* self)
{
    if (*(void**)((char*)self + 0x4c) != 0)
        return ((int(__thiscall*)(void*))VFN(*(void**)((char*)self + 0x4c), 0x10))
                   (*(void**)((char*)self + 0x4c));
    return 0;
}

// @ 0x00695cf0
extern "C" int FUN_00695cf0(void** p)
{
    void* o = *p;
    if (o == 0)
        return 0;
    void* t = *(void**)((char*)o + 4);
    void* self = (char*)o + 4;
    return ((int(__thiscall*)(void*, int))*(void**)((char*)t + 0xc))(self, 0x226a25b);
}

// @ 0x00695d10
void Ctl::addThing(void* a, void* b)
{
    void* m = GetManager();
    bool ok = ((bool(__thiscall*)(void*, void*, void*, int, int, int, int))VFN(m, 0xc))
                  (m, a, b, 0, 0, 0, 0);
    if (!ok)
    {
        char* end = (char*)this + 0x60;
        void* n = *(void**)((char*)this + 0x60);
        while (n != end && !ok)
        {
            m = GetManager();
            ok = ((bool(__thiscall*)(void*, void*, void*, int, void*, int, int))VFN(m, 0xc))
                     (m, a, b, 0, *(void**)((char*)n + 8), 0, 0);
            n = *(void**)n;
        }
    }
}

// @ 0x00695d70
bool Ctl::check(void* arg)
{
    void* h = head;
    void* n = *(void**)h;
    if (n != h)
    {
        do
        {
            void* obj = *(void**)((char*)n + 8);
            if (((bool(__thiscall*)(void*, void*, int, int, int, int, int))VFN(obj, 0x34))
                    (obj, arg, 0, 1, 6, 1, 0))
                return true;
            n = *(void**)n;
        } while (n != head);
    }
    return false;
}

// @ 0x00695dc0
extern "C" void __fastcall FUN_00695dc0(void* self)
{
    void* n = *(void**)self;
    while (n != self)
    {
        void* cur = n;
        void* obj = *(void**)((char*)cur + 8);
        n = *(void**)n;
        if (obj != 0)
        {
            void* t = *(void**)((char*)obj + 4);
            ((void(__thiscall*)(void*))*(void**)((char*)t + 4))((char*)obj + 4);
        }
        void* mgr = *(void**)((char*)self + 8);
        ((void(__thiscall*)(void*, void*, int))VFN(mgr, 0xc))(mgr, cur, 0xc);
    }
}

// @ 0x00695e00
extern "C" int __fastcall FUN_00695e00(void* self)
{
    void* alloc = *(void**)((char*)self + 8);
    void* arg   = *(void**)((char*)self + 0xc);
    int node = ((int(__thiscall*)(void*, int, int, void*))VFN(alloc, 8))(alloc, 0xc, 0, arg);
    int* p = (int*)(node + 8);
    if (p != 0)
    {
        int v = *(int*)arg;
        *p = v;
        if (v != 0)
            ((void(__thiscall*)(void*))*(void**)(v + 4))(p);
    }
    return node;
}

// @ 0x00695e80
extern "C" void __fastcall FUN_00695e80(void* self)
{
    *(void**)self = g_vtbl_a;
    FUN_00695dc0((char*)self + 0x60);
    FUN_00695dc0((char*)self + 0x50);
    char* p = *(char**)((char*)self + 0x18);
    int d = (int)(*(char**)((char*)self + 0x20) - p) & 0xfffffffe;
    if (d > 2 && p != 0 && p != *(char**)((char*)self + 0x28))
        operator_delete_arr(p);
    *(void**)self = g_vtbl_b;
}

// @ 0x00695f00
extern "C" void __fastcall FUN_00695f00(void* self)
{
    char* head = (char*)self + 0x60;
    while (*(void**)head != head)
    {
        char* n = *(char**)head;
        char* obj = *(char**)(n + 8);
        if (obj != 0)
        {
            void* t = *(void**)(obj + 4);
            void* fn = *(void**)((char*)t + 0xc);
            void* r = (void*)((int(__thiscall*)(void*, int))fn)(obj + 4, 0x226a25b);
            if (r != 0)
            {
                if (((int(__thiscall*)(void*))VFN(r, 0x4c))(r) != 0)
                {
                    ((void(__thiscall*)(void*))VFN(r, 0x1c))(r);
                    ((void(__thiscall*)(void*))VFN(r, 8))(r);
                }
            }
        }
        char* nn = *(char**)head;
        *(void**)(*(void**)(nn + 4)) = *(void**)nn;
        *(void**)((char*)(*(void**)nn) + 4) = *(void**)(nn + 4);
        if (*(void**)(nn + 8) != 0)
            ((void(__thiscall*)(void*))*(void**)((char*)(*(void**)(nn + 8)) + 4))(*(void**)(nn + 8));
        void* mgr = *(void**)((char*)self + 0x68);
        ((void(__thiscall*)(void*, void*, int))VFN(mgr, 0xc))(mgr, nn, 0xc);
    }
    char* l = (char*)self + 0x50;
    FUN_00695dc0(l);
    *(void**)l = l;
    *(void**)((char*)self + 0x54) = l;
}

// @ 0x00695fa0
extern "C" void __fastcall FUN_00695fa0(void* self)
{
    char* b = (char*)self;
    if (*(char**)(b + 0x14) == *(char**)(b + 0x24))
    {
        char* p = *(char**)(b + 8);
        char* e = *(char**)(b + 0x18);
        destroy30(p, e);
    }
    else
    {
        destroy30(*(char**)(b + 8), *(char**)(b + 0x10));
        destroy30(*(char**)(b + 0x1c), *(char**)(b + 0x18));
        void* p = *(void**)(b + 0x1c);
        if (p != 0)
        {
            void* mgr = *(void**)(b + 0x28);
            ((void(__thiscall*)(void*, void*, int))VFN(mgr, 0xc))(mgr, p, 0xc0);
        }
    }
    char** pp = (char**)(*(char**)(b + 0x14) + 4);
    char** pe = *(char***)(b + 0x24);
    while (pp < pe)
    {
        char* v = *pp;
        destroy30(v, v + 0xc0);
        if (*pp != 0)
        {
            void* mgr = *(void**)(b + 0x28);
            ((void(__thiscall*)(void*, void*, int))VFN(mgr, 0xc))(mgr, *pp, 0xc0);
        }
        ++pp;
    }
    *(void**)(b + 0x18) = *(void**)(b + 8);
    *(void**)(b + 0x1c) = *(void**)(b + 0xc);
    *(void**)(b + 0x20) = *(void**)(b + 0x10);
    *(void**)(b + 0x24) = *(void**)(b + 0x14);
}

// @ 0x006960f0
namespace SP {
int __stdcall BroadcastLocaleChange(const wchar_t* name, List16* list)
{
  (void)name;
  if (GetManager() == 0) return 0;

  List16 head;
  head.mAlloc = EA::Allocator::ICoreAllocator_s0069_60f0::GetDefaultAllocator();
  head.mZero = 0;
  head.mNext = &head;
  head.mPrev = &head;
  for (LocaleNode* n = (LocaleNode*)list->mNext; n != (LocaleNode*)list; n = n->mNext) {
    LocaleNode* node = (LocaleNode*)head.mAlloc->Allocate(0xc, 0, head.mZero);
    node->mValue = n->mValue;
    node->mNext = (LocaleNode*)&head;
    node->mPrev = (LocaleNode*)head.mPrev;
    ((LocaleNode*)head.mPrev)->mNext = node;
    head.mPrev = node;
  }

  int result;
  {
    LocaleBroadcastMessage msg;
    msg.mList = &head;
    result = ((ILocaleBroadcastTarget*)GetManager())->Dispatch(list, &msg);
  }
  for (LocaleNode* n = (LocaleNode*)head.mNext; n != (LocaleNode*)&head; ) {
    LocaleNode* next = n->mNext;
    head.mAlloc->Free(n, 0xc);
    n = next;
  }
  return result;
}
}  // namespace SP

// @ 0x00696230
namespace eastl {
FixedString16::FixedString16(const FixedString16& x)
: FixedStringBase(mBuffer) {
  mpBegin = mpEnd = mArray;
  mpCapacity = mpBegin + 16;
  *mpBegin = 0;
  append(x.mpBegin, x.mpEnd);
}
}  // namespace eastl

// @ 0x006962a0
namespace eastl {
FixedString16::FixedString16(const wchar_t* p)
: FixedStringBase(mBuffer) {
  mpBegin = mpEnd = mArray;
  mpCapacity = mpBegin + 16;
  *mpBegin = 0;
  append(p, p + CharStrlenW(p));
}
}  // namespace eastl

// @ 0x00696320
namespace eastl {
FixedString16& FixedString16::operator=(const FixedString16& x)
{
  if (this != &x) {
    clear();
    append(x.mpBegin, x.mpEnd);
  }
  return *this;
}
}  // namespace eastl

// @ 0x00696350
namespace App {
cLocaleChangeMessage::cLocaleChangeMessage(const FixedString16& id)
: mLocaleId(id) {}
}  // namespace App

// @ 0x00696420
namespace SP {
cLocaleManager::cLocaleManager()
: mbInit(false), field9(false), fieldA(false), fieldC(0), field10(2), field14(2),
      mLocaleId(L"**-**") {
  mpStringManager = 0;
  mList50.mAlloc = EA::Allocator::ICoreAllocator_s0069_60f0::GetDefaultAllocator();
  mList50.mZero = 0;
  mList50.mNext = &mList50;
  mList50.mPrev = &mList50;
  mList60.mAlloc = EA::Allocator::ICoreAllocator_s0069_60f0::GetDefaultAllocator();
  mList60.mZero = 0;
  mList60.mNext = &mList60;
  mList60.mPrev = &mList60;
}
}  // namespace SP

// @ 0x006964c0
namespace SP {
bool cLocaleManager::Init(void* pCommandLine, void* pUnknown)
{
  (void)pCommandLine;
  (void)pUnknown;
  return mbInit;
}
}  // namespace SP

// @ 0x006968f0
namespace SP {
bool cLocaleManager::SetFromMatch(const eastl::WStr& id)
{
  int best = 0;
  int bestScore = 0;
  for (int i = 0; i < 24; ++i) {
    int score = LocaleCommonPrefix(id.mpBegin, g_localeTable[i].mName);
    if (score > bestScore) {
      best = i;
      bestScore = score;
    }
  }
  FixedString16 code(g_localeTable[best].mCode);
  return ApplyLocaleId(code);
}
}  // namespace SP

// @ 0x006969b0
namespace SP {
const wchar_t* cLocaleManager::FindMatchingLocale()
{
  for (int i = 0; i < 24; ++i) {
    bool matched;
    {
      FixedString16 code(g_localeTable[i].mCode);
      matched = FUN_0087fd10((int*)&mLocaleId, (int*)&code, 1);
    }
    if (matched) return g_localeTable[i].mName;
  }
  return 0;
}
}  // namespace SP

// @ 0x00696a60
namespace SP {
bool cLocaleManager::GetDefaultLanguage(const FixedString16& locale)
{
  bool matched;
  {
    FixedString16 tmp(L"en-us");
    matched = FUN_0087fd10((int*)&locale, (int*)&tmp, 1);
  }
  if (matched) return true;

  eastl::WStr path;
  path.mpBegin = path.mpEnd = gEmptyString16;
  path.mpCapacity = gEmptyString16 + 1;
  if (!GetDirString(0x6cbed3a, &path, 0)) {
    if (!GetDirString(0x45962cc, &path, 0)) return false;
  }

  eastl::WStr lang;
  lang.mpBegin = lang.mpEnd = gEmptyString16;
  lang.mpCapacity = gEmptyString16 + 1;

  wchar_t buf[0x80];
  if (EA::Locale::GetLocaleInfoString(2, 0, buf, 0x80, &locale) <= 0) return false;

  lang.assign(buf, buf + eastl::CharStrlenW(buf));
  path.Append(lang.mpBegin, lang.mpEnd);
  path.Append(gPathSep, gPathSep + eastl::CharStrlenW(gPathSep));
  return EA::IO::Directory::Exists(path.mpBegin);
}
}  // namespace SP

// @ 0x00697710
namespace SP {
bool cLocaleManagerSetLocale(void* self, void* arg)
{
  (void)self;
  (void)arg;
  return true;
}
}  // namespace SP
