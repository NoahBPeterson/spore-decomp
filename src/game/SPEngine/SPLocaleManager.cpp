// src/game/SPEngine/SPLocaleManager.cpp -- migrated from slice(s) s00696c80, s006960f0, s00695140 by tools/migrate/rewrite.py
// Object file: SPEngine/SPLocaleManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/ZoneObject.h"

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
extern wchar_t gEmptyString16[2];   // 0x1667bac � eastl empty wide-string sentinel
extern wchar_t gPathSep[];          // 0x13fa488 � L"\\"
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
  ~cLocaleChangeMessage() throw();   // implicitly virtual; ??_G at 0x006963d0 inlines it
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

// Retail Database has the canonical ZoneObject / IUnknown32 base layout.
// The query consumes a full-width ID; the generated InterfaceId enum currently
// lists only its sentinels, so this local interface keeps the native ID domain.
namespace LocaleDatabaseRetail {
struct IUnknown32 {
    virtual int AddRef();
    virtual int Release();
    virtual ~IUnknown32();
    virtual void* AsInterface(uint32_t typeID);
};
struct Database : EA::Allocator::ZoneObject, IUnknown32 {
    int mRefCount;
};
}

// @ 0x00695cf0
extern "C" void* FUN_00695cf0(LocaleDatabaseRetail::Database** p)
{
    LocaleDatabaseRetail::Database* database = *p;
    if (database != 0)
        return static_cast<LocaleDatabaseRetail::IUnknown32*>(database)->AsInterface(0x0226a25b);
    return 0;
}

struct LocaleResourceManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual bool GetResource(void* key, void* resource, int flags, void* database, int, int); // +0x0c
};

// @ 0x00695d10
void Ctl::addThing(void* a, void* b)
{
    LocaleResourceManager* __restrict manager = (LocaleResourceManager*)GetManager();
    bool ok = manager->GetResource(a, b, 0, 0, 0, 0);
    if (!ok) {
        char* end = (char*)this + 0x60;
        void* n = *(void**)((char*)this + 0x60);
        while (n != end && !ok) {
            LocaleResourceManager* __restrict current = (LocaleResourceManager*)GetManager();
            void* database = *(void**)((char*)n + 8);
            ok = current->GetResource(a, b, 0, database, 0, 0);
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
{    void* n = *(void**)self;
    while (n != self)
    {
        void* cur = n;
        n = *(void**)n;
        void* obj = *(void**)((char*)cur + 8);
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

// Destructor's view of cLocaleManager: same layout, with the member destructors retail runs.
struct LocaleNodeListD {
    void* mNext;
    void* mPrev;
    void* mAlloc;
    void* mZero;
    LocaleNodeListD(void* alloc);
    ~LocaleNodeListD();
};
struct LocaleNodeListF {
    void* mNext;
    void* mPrev;
    void* mAlloc;
    void* mZero;
    LocaleNodeListF(void* alloc);
    ~LocaleNodeListF();
};
void __fastcall ClearLocaleNodeList(void* list);  // 0x695dc0
inline LocaleNodeListF::LocaleNodeListF(void* alloc)
{
    mAlloc = alloc;
    mZero = 0;
    mNext = this;
    mPrev = this;
}
inline LocaleNodeListF::~LocaleNodeListF() { ClearLocaleNodeList(this); }
inline LocaleNodeListD::~LocaleNodeListD() { ClearLocaleNodeList(this); }

class LocaleManagerDtorView : public EA::RefCountVTemplate_s0069_60f0<int> {
public:
    bool mbInit;
    bool field9;
    bool fieldA;
    char padB;
    int fieldC;
    int field10;
    int field14;
    eastl::FixedString16 mLocaleId;
    void* mpStringManager;
    LocaleNodeListF mList50;
    LocaleNodeListD mList60;
    LocaleManagerDtorView();
    virtual ~LocaleManagerDtorView();
};

inline LocaleNodeListD::LocaleNodeListD(void* alloc)
{
    mZero = 0;
    mAlloc = alloc;
    mNext = this;
    mPrev = this;
}

// @ 0x00695e80
LocaleManagerDtorView::~LocaleManagerDtorView()
{
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

// 0x006963d0 (byte-exact lifted version: match/slices/s006963d0/s006963d0.cpp)
namespace App {
cLocaleChangeMessage::~cLocaleChangeMessage()
{}
}  // namespace App

// @ 0x00696420
LocaleManagerDtorView::LocaleManagerDtorView()
: mbInit(false), field9(false), fieldA(false), fieldC(0), field10(2), field14(2),
      mLocaleId(L"**-**"), mpStringManager(0),
      mList50(EA::Allocator::ICoreAllocator_s0069_60f0::GetDefaultAllocator()),
      mList60(EA::Allocator::ICoreAllocator_s0069_60f0::GetDefaultAllocator())
{
}

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

// ---- items of slice s00696c80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
void __cdecl operator delete(void*, const char*, int, int, int, int);
namespace SP {
void* MessageServer();                          // 0x67dcc0
}
namespace SP {
namespace LocaleLoad {
struct Node { Node* next; Node* prev; void* value; };   // 0xc-byte list node
}
}
namespace SP {
namespace LocaleLoad {
struct Head { Node* next; Node* prev; };                 // list sentinel
}
}
namespace SP {
namespace LocaleLoad {
struct WStr_s0069_6c80 { wchar_t* mBegin; wchar_t* mEnd; wchar_t* mCap; void* mAlloc; };
}
}
namespace SP {
namespace LocaleLoad {
struct KeyList { Node* next; Node* prev; void* alloc; unsigned size; };
}
}
namespace SP {
namespace LocaleLoad {
void* GetDefaultAllocator();                             // 0x00925cb0
}
}
namespace SP {
namespace LocaleLoad {
int GetLocaleInfoString(int, int, wchar_t*, int, const WStr_s0069_6c80*);   // 0x00880910
}
}
namespace SP {
namespace LocaleLoad {
unsigned FNV1_String16(const wchar_t*, unsigned, bool);  // 0x00932f30
}
}
namespace SP {
struct KeyItem {
virtual void* k00();
virtual void* k04();
virtual void* k08();
virtual void* k0c();
virtual void* k10();
virtual void* k14();
virtual void* k18();
virtual void* k1c();
virtual void* k20();
virtual void* k24();
virtual void* k28();
virtual void* k2c();
    virtual void* k30();                                  // +0x30 record count
virtual void* k34();
virtual void* k38();
virtual void* k3c();
virtual void* k40();
virtual void* k44();
virtual void* k48();
virtual void* k4c();
    virtual void* k50();
    virtual void* k54(void* out);                          // +0x54
};
}
namespace SP {
struct ILocaleMgr {
virtual void* m00();
virtual void* m04();
virtual void* m08();
virtual void* m0c();
virtual void* m10();
virtual void* m14();
virtual void* m18();
virtual void* m1c();
virtual void* m20();
virtual void* m24();
virtual void* m28();
virtual void* m2c();
virtual void* m30();
virtual void* m34();
virtual void* m38();
virtual void* m3c();
virtual void* m40();
virtual void* m44();
virtual void* m48();
virtual void* m4c();
virtual void* m50();
virtual void* m54(KeyItem* item, void* ctx);
virtual void* m58();
virtual void* m5c(void* list, int flag);
};
}
namespace SP {
struct DatabasePackedFile {
virtual void* d00();
virtual void* d04();
virtual void* d08();
virtual void* d0c();
virtual void* d10();
virtual void* d14();
virtual void* d18(int a, int b, int c);
virtual void* d1c();
virtual void* d20();
virtual void* d24();
virtual void* d28();
    virtual void* d2c(void* path);                          // +0x2c
    void* Ctor(int, int);                                   // 0x696230-like; ctor at 0x696150
};
}
namespace SP {
struct CObj0c { virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c(); };
}
namespace SP {
struct CObj14 { virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
                virtual void s10(); virtual void s14(unsigned v); };
}
namespace SP {
struct CMsgSrv { virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
                 virtual void s10(); virtual void s14(); virtual void s18(unsigned m, void* p, int a, int b); };
}
namespace SP {
struct CLocaleChangeMessage {
  char pad[0x40];
  CLocaleChangeMessage(void* src);  // 0x696350
};
}
namespace SP {
namespace eastl_s6c {
struct WStr16 {
  wchar_t* mBegin;       // +0x00
  wchar_t* mEnd;         // +0x04
  wchar_t* mCap;         // +0x08
  wchar_t* mAlloc;       // +0x0c
  wchar_t* mInline;      // +0x10
  wchar_t  mBuffer[16];  // +0x14
  void __thiscall Ctor(const WStr16& src);      // 0x696230
  WStr16* __thiscall Assign(const void* src);   // 0x696320
};  // namespace eastl
}
}
namespace SP {
namespace SP_EA {
namespace Locale {
bool IsLocaleAvailable(int* locale);          // 0x87f5e0
}
}
}
namespace SP {
namespace SP_EA {
namespace Locale {
bool SetLocale(void* locale, int a, int b);   // 0x882b30
}
}
}
namespace SP {
namespace SP_EA {
namespace ResourceMan {
bool GetRecordName(const void* key, wchar_t* out);   // 0x8d68c0
}
}
}
namespace SP {
unsigned __cdecl FUN_0087fd10_s0069_6c80(int* a, int* b, char c);   // 0x87fd10
}
namespace SP {
void* __cdecl FUN_008d5f40();                            // 0x8d5f40
}
namespace SP {
void __cdecl opdel(void* p);                             // 0xf47380
}
namespace SP {
bool OpenPackageRecord(int idx, void* item, void** out, int ctx, bool flag);  // 0x00686d90
}
namespace SP {
void* BuildPackageNode(void* value);                     // 0x00695e00 (list-node alloc)
}
namespace SP {
void OpenPackageDB(void);                                // 0x00695fa0
}
namespace SP {
void ReadPackageDir(const wchar_t* pattern, void* out, int a, int b, int c);  // 0x0092ef40
}
namespace SP {
void WideStrAppend(void* dst, const wchar_t* s);         // 0x0042f9d0 (WideFixedBuf::append)
}
namespace SP {
void DequeDestroy();                                     // 0x005f96c0
}
namespace SP {
void DequeInit(int n);                                   // 0x005f8840
}
namespace SP {
DatabasePackedFile* NewDatabasePackedFile(const wchar_t* path, void* alloc);  // 0x008d9f80
}
namespace SP {
struct IMgr {
virtual void* s00();
virtual void* s04();
virtual void* s08();
  virtual bool  s0c(void* rec, void** out, int, int, int, int);   // +0x0c
virtual void* s10();
virtual void* s14();
  virtual void* s18(void* rec, void* out, int, int, int);         // +0x18
virtual void* s1c();
virtual void* s20();
virtual void* s24();
virtual void* s28();
virtual void* s2c();
virtual void* s30();
virtual void* s34();
virtual void* s38();
virtual void* s3c();
virtual void* s40();
virtual void* s44();
virtual void* s48();
  virtual void* s4c();
  virtual void* s50(int, void* item, void* ctx);                  // +0x50
};
}
namespace SP {
struct IAlloc {
virtual void* s00();
virtual void* s04();
virtual void* s08();
  virtual void* s0c(void* node, unsigned sz);                     // +0x0c
};
}
namespace SP {
struct IItem {
virtual void* s00();
virtual void* s04();
virtual void* s08();
virtual void* s0c();
  virtual void* s10();                                            // +0x10
};
}
namespace SP {
struct ISub {
  virtual void* s00();
  virtual void* s04();                                            // +0x04
  virtual void* s08();
  virtual void* s0c(void* arg);                                   // +0x0c
};
}
namespace SP {
class cLocaleManager_s0069_6c80 {
 public:
virtual void* v00();
virtual void* v04();
virtual void* v08();
virtual void* v0c();
virtual void* v10();
virtual void* v14();
virtual void* v18();
virtual void* v1c();
  virtual void* v20();                          // +0x20
  char pad_04[8];                               // +0x04..+0x0c
  void* mField0c;                               // +0x0c
  char pad10[4];
  void* mField14;                               // +0x14
  eastl_s6c::WStr16 mField18;                       // +0x18 (0x34 bytes)
  void* mField4c;                               // +0x4c
  LocaleLoad::Head mHeadA;                      // +0x50 (flag clear)
  void* mAlloc;                                 // +0x58
  char pad5c[4];                                // +0x5c..+0x60
  LocaleLoad::Head mHeadB;                      // +0x60 (flag set)
  void* GetDefaultLanguage();                   // 0x696a60
  void BuildRecordList(void* list, void* head); // 0x6960f0
  bool Load(const LocaleLoad::WStr_s0069_6c80* locale, bool bFlag);
  void BroadcastLocaleChange(unsigned int arg); // 0x697650
};
}
// ---- items of slice s00696c80 end

// @ 0x00695c70


// @ 0x00696c80
namespace SP {
bool cLocaleManager_s0069_6c80::Load(const LocaleLoad::WStr_s0069_6c80* locale, bool bFlag)
{
  using namespace LocaleLoad;
  bool result = false;
  wchar_t buf[0x80];
  Head* head = bFlag ? &mHeadB : &mHeadA;
  WStr_s0069_6c80 path = {0, 0, 0, 0};
  (void)GetDirString(0x045962cc, &path, 0);

  void* mgr = GetManager();
  int n = GetLocaleInfoString(2, 0, buf, 0x80, locale);
  if (n > 0) {
    unsigned hash = FNV1_String16(locale->mBegin, 0x811c9dc5, true);
    (void)hash;

    // Key list: manager vtable +0x5c fills it; then for every key node, the manager's vtable
    // +0x54 builds the record set (returning a count), and per record we open the package
    // record and splice a fresh node into the target head (flag ? mHeadB : mHeadA).
    KeyList keys = {0, 0, GetDefaultAllocator(), 0};
    keys.next = keys.prev = reinterpret_cast<Node*>(&keys);
    ((ILocaleMgr*)mgr)->m5c(&keys, 0);
    for (Node* k = keys.next; k != reinterpret_cast<Node*>(&keys); k = k->next) {
      KeyItem* item = (KeyItem*)k->value;
      int ctx = 0;
      void* ctxIn = 0;
      ((ILocaleMgr*)mgr)->m54(item, &ctxIn);
      int count = (int)(uintptr_t)item->k30();
      (void)ctx;
      for (int i = 0; i < count; ++i) {
        void* value = 0;
        bool ok = OpenPackageRecord(i, item, &value, (int)(uintptr_t)&ctxIn, !bFlag);
        if (ok) {
          void* node = BuildPackageNode(&value);
          // node->next = head->next; node->prev = head; splice before head
          *(void**)node = head->next;
          *(void**)((char*)node + 4) = *(void**)((char*)head + 4);
          *(void**)head->next = node;
          *(void**)((char*)head + 4) = node;
        }
        // value's owning sub-object is released by OpenPackageRecord on failure.
      }
      if (item) (*(void(__thiscall**)(void*))((char*)*(void**)item + 0x04))(item);
    }
    (void)head;
  }

  // Second pass: the locale directory ("*.package"). When the directory property exists, scan,
  // build/open a DatabasePackedFile per entry and hook its records into the manager.
  if (GetDirString(0x06cbed3a, &path, 0)) {
    void* alloc = GetDefaultAllocator();
    (void)OpenPackageDB();
    // The eastl fixed-deque of directory entries (0x30 bytes each) is initialised then filled
    // by the *.package scan; each entry name is appended to `path`, a DatabasePackedFile is
    // constructed and opened, and its records are attached to the manager.
    DequeInit(4);
    struct DirEntry { void* name0; void* name1; char pad[0x28]; };
    DirEntry* begin = 0; DirEntry* end = 0; (void)begin; (void)end;
    ReadPackageDir(L"*.package", &begin, 2, 0x100000, 0);
    for (DirEntry* e = begin; e != end; e = (DirEntry*)((char*)e + 0x30)) {
      (void)WideStrAppend(&path, (const wchar_t*)/*e->name*/ 0);
      DatabasePackedFile* db = NewDatabasePackedFile((const wchar_t*)&path, alloc);
      if (db) {
        db->d2c(&path);                       // set the package path
        if (db->d18(1, 6, 0)) {               // open
          void* node = BuildPackageNode(db);  // node->value = db
          (void)node;
        }
      }
    }
    DequeDestroy();
    (void)head;
    result = true;
  }
  if (!result) {
    // No directory: recurse once with the default flag to refresh the lists.
    (void)GetDirString(0x045962cc, &path, 0);
    (void)FUN_0087fd10_s0069_6c80((int*)&path, (int*)locale, 1);
    WStr_s0069_6c80 def = {0, 0, 0, 0};
    this->Load(&def, true);
  }
  return result;
}
}  // namespace SP

// @ 0x00697650
namespace SP {
void cLocaleManager_s0069_6c80::BroadcastLocaleChange(unsigned int arg)
{
  if (v20() != 0) {
    ((CObj14*)v20())->s14(arg);
  }
  if (mField4c != 0) ((CObj0c*)mField4c)->s0c();
  void* server = MessageServer();
  if (server != 0) {
    void* msg = new ("App/cLocaleChangeMessage", 0, 0, 0, 0) CLocaleChangeMessage((void*)&mField18);
    ((CMsgSrv*)server)->s18(0x2800a7f, msg, 0, 0);
  }
}
}  // namespace SP