// src/game/SPGonzago/SPCinematicManager.cpp -- migrated from slice(s) s005ca070, s0057bfb0, s005718f0, s0042f160, s004292a0, s00423110, s004215f0, s0041dd90 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCinematicManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdarg.h>
#include <intrin.h>
#include <string.h>
#include "EA/Messaging/Server.h"
#include "EA/Messaging/IHandler.h"
#include <new>
#include <math.h>
#include "EA/Variant.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cEditorResource.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorSkinManager.h"
#include "SP/cSPEditorUI.h"
#include "EA/UTFWinControls/IButtonDrawable.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "SP/cSPPaletteSubCategoryUI.h"
#include "SP/cSPPaletteUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"

// ---- items of slice s0041dd90 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WStr {
    const wchar_t* mBegin;
    const wchar_t* mEnd;
    uint32_t mCap;
    WStr(const wchar_t* s, int unused);
    void Assign(const wchar_t* b, const wchar_t* e);        // 0x00423820
    int rfind(wchar_t c, uint32_t pos);
    void AppendVPrintf(const wchar_t* fmt, va_list args);   // 0x004234b0
};
// ---- items of slice s0041dd90 end

// ---- items of slice s004215f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_App_cLocaleChangeMessage[];     // 0x013eb918
extern char vtbl_UI_BehaviorMessage[];           // 0x013eb90c
extern char vtbl_SlotMessage[];                  // 0x013eb844
struct Holder {
    uint32_t pad[3];
    uint32_t mValue;
    void Apply(uint32_t a, uint32_t b);      // 0x0083c7f0
    void Set(uint32_t a, uint32_t b);
};
struct MessageHeader { uint32_t data[10]; uint32_t arg; };
struct SlotMessage {
    const void* vptr;          // +0x00
    volatile long refCount;    // +0x04
    uint32_t body[0x2c];       // +0x08 .. : 32 slots of 8 bytes; arg lives at +0x30, listener mask at +0x38

    SlotMessage* Construct(uint32_t arg);
    void Destruct();
};
// ---- items of slice s004215f0 end

// ---- items of slice s00423110 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;

    wchar_t* begin() { return mpBegin; }
    wchar_t* end() { return mpEnd; }
    wchar_t* at(int i) { return mpBegin + i; }
    unsigned size() { return (unsigned)(mpEnd - mpBegin); }
    unsigned capacity() { return (unsigned)(mpCapacity - mpBegin); }
    unsigned remaining() { return (unsigned)(mpCapacity - mpEnd); }

    WString& AppendSprintfVa(const wchar_t* fmt, va_list args);   // 0x004234b0
    WString& Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    unsigned Find(const wchar_t* s, unsigned pos, unsigned n);    // 0x00423700
    void FreeBuffer();                                            // 0x004237d0
    void AllocateSelf(const wchar_t* first, const wchar_t* last); // 0x00423820

    void reserve(unsigned n);                                      // 0x00429520
    void AllocateBuf(unsigned n);                                  // 0x00429760
    void Append(const wchar_t* first, const wchar_t* last);        // 0x00429580
    void Erase(wchar_t* first, wchar_t* last);                     // 0x0042e2f0
};
// ---- items of slice s00423110 end

// ---- items of slice s004292a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char g_EditorName[];     // "Editor"
extern const char g_AllocatorHdr[];   // ".../EASTL/include/EASTL/allocator.h"
typedef uint16_t wchar16;
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags,
                                       int align, const char* file, int line);
extern wchar16    g_EmptyWStr[];      // shared 1-char empty string storage
template <class T> static inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }
static inline wchar16* WCopy(const wchar16* first, const wchar16* last, wchar16* dest)
{
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}
static inline wchar16* WAlloc(uint32_t n)
{
    void* p = EASTL_allocator_allocate(n * 2, g_EditorName, 0, 0, g_AllocatorHdr, 0xd1);
    return (wchar16*)p;
}
static inline void Nop3() { volatile int u1, u2, u3; }
struct WStr_s0042_92a0 {
    wchar16* mBegin; wchar16* mEnd; wchar16* mCap;
    void Erase(wchar16* first, wchar16* last);
    void AppendFill(uint32_t n, wchar16 c);
    void FreeBuffer();
    void Resize(uint32_t n);
    WStr_s0042_92a0* Append(const wchar16* first, const wchar16* last);
    void AllocateSelf(uint32_t n);
};
// ---- items of slice s004292a0 end

// ---- items of slice s0042f160 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedIncrement)
struct Alloc {
    uint32_t pad;
    const char* mpName;
    Alloc& operator=(const Alloc& x)
    {
        mpName = x.mpName;
        return *this;
    }
};
struct WString_s0042_f160 {
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    Alloc mAllocator;

    WString_s0042_f160(const WString_s0042_f160& x);
    void AllocateSelf(const uint16_t* b, const uint16_t* e);  // 0x00423820
    void FreeBuffer();                                         // 0x004237d0
    void Resize(uint32_t n);                                   // 0x00429520
    void Swap(WString_s0042_f160& x);                                     // 0x0042f620
    void SetCapacity(uint32_t n);                              // 0x0042f360
    WString_s0042_f160& AssignRange(const uint16_t* b, const uint16_t* e);    // 0x0042f920
    void Assign(const uint16_t* b, const uint16_t* e);         // 0x00423650
    void EraseRange(uint16_t* b, uint16_t* e);                 // 0x0042e2f0
    void AppendRange(const uint16_t* b, const uint16_t* e);    // 0x0042f9d0
};
void* EastlAllocate(uint32_t size, const char* name, uint32_t flags, uint32_t align,
                    const char* file, int line);  // 0x00f473a0
inline void DeadHelper()
{
    uint32_t dead[3];
}
inline uint16_t* DoAllocate(uint32_t n)
{
    uint16_t* p = (uint16_t*)EastlAllocate(
        n * 2, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    return p;
}
inline uint16_t* UninitializedCopy16(const uint16_t* first, const uint16_t* last, uint16_t* dest)
{
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}
// ---- items of slice s0042f160 end

// ---- items of slice s005718f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
struct Key12 {
    uint32_t mA;
    uint32_t mB;
    uint32_t mC;
    bool operator<(const Key12& rhs) const;      // 0x5715d0
};
struct Block36 { uint32_t mData[9]; };
struct DirtyState {
    uint16_t mDirtyFlags;
    uint16_t mRevision;
    Key12 mKey;            // +0x04
    uint32_t mPad10;       // +0x10
    Block36 mBlock;        // +0x14

    void SetBlock(const Block36& b);
    void SetKey(const Key12& k);
};
struct Vec3 { float x, y, z; };
struct VecPair {
    Vec3 mA;
    Vec3 mB;
    VecPair& operator=(const VecPair& o);
};
struct OwnerHandle;
struct OwnerTarget {
    PV16 PV16 PV16 PV16 PV16 PV8 PV2 PV
    virtual void Notify(OwnerHandle* h, int arg);   // +0x16c
};
struct OwnerHandle {
    OwnerTarget* mpTarget;
    void Notify();
};
// ---- items of slice s005718f0 end

// ---- items of slice s0057bfb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
namespace eastl {
class allocator_s0057_bfb0 { public:
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, 0, 0); }
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
template <typename T> struct EmptyStr;
}
namespace eastl {
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };
}
namespace eastl {
template <typename T>
inline T* CharStringUninitializedCopy(const T* pSource, const T* pEnd, T* pDest)
{
    memcpy(pDest, pSource, (size_t)(pEnd - pSource) * sizeof(T));
    return pDest + (pEnd - pSource);
}
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0057_bfb0>
class basic_string_s0057_bfb0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    basic_string_s0057_bfb0() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string_s0057_bfb0(const basic_string_s0057_bfb0& x);
    struct CtorDoNotInitialize {};
    basic_string_s0057_bfb0(CtorDoNotInitialize, size_t n) : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(n + 1); *mpEnd = 0; }
    basic_string_s0057_bfb0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string_s0057_bfb0() { DeallocateSelf(); }

    basic_string_s0057_bfb0& operator=(const basic_string_s0057_bfb0& x);

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    T* data() { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }

    void AllocateSelf(size_t n);
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    void RangeInitialize(const T* pBegin);
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
    basic_string_s0057_bfb0& assign(const T* pBegin, const T* pEnd);
    basic_string_s0057_bfb0& append(const T* pBegin, const T* pEnd);
    int sprintf(const char* fmt, ...);
};
}
// ---- items of slice s0057bfb0 end

// ---- items of slice s005ca070 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV_s005c_a070(n) virtual void pv##n();
class cAudioSystem {
 public:
  PV_s005c_a070(0) PV_s005c_a070(1) PV_s005c_a070(2) PV_s005c_a070(3) PV_s005c_a070(4) PV_s005c_a070(5) PV_s005c_a070(6) PV_s005c_a070(7) PV_s005c_a070(8) PV_s005c_a070(9) PV_s005c_a070(10) PV_s005c_a070(11) PV_s005c_a070(12) PV_s005c_a070(13)
  virtual void SetId(int id);              // +0x38
  virtual void SetFloat(int id, float v);  // +0x3c
  virtual void SetInt(int id, int v);      // +0x40
  PV_s005c_a070(17) PV_s005c_a070(18) PV_s005c_a070(19) PV_s005c_a070(20) PV_s005c_a070(21)
  virtual void Flush();                    // +0x58
};
cAudioSystem* GetSystemAT();  // 0x00a206f0
// ---- items of slice s005ca070 end

// @ 0x0041e050
WStr* __cdecl WStr_Format(WStr* s, const wchar_t* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    s->mEnd = s->mBegin;
    s->AppendVPrintf(fmt, args);
    va_end(args);
    return s;
}

// @ 0x00421c80
SlotMessage* SlotMessage::Construct(uint32_t arg)
{
    MessageHeader* pHdr = (MessageHeader*)((char*)this + 8);
    pHdr->arg = arg;
    vptr = vtbl_App_cLocaleChangeMessage;
    vptr = vtbl_UI_BehaviorMessage;
    volatile long* pRefCount = &refCount;
    _InterlockedExchange(pRefCount, 0);
    vptr = vtbl_UI_BehaviorMessage;
    vptr = vtbl_SlotMessage;
    body[12] = 0;
    return this;
}

// @ 0x00421e80
void Holder::Set(uint32_t a, uint32_t b)
{
    mValue = b;
    Apply(a, b);
}

// @ 0x00423650
WString& WString::Assign(const wchar_t* first, const wchar_t* last)
{
    const unsigned n = (unsigned)(last - first);
    if (n <= (unsigned)(mpEnd - mpBegin)) {
        memcpy(mpBegin, first, n * 2);
        Erase(mpBegin + n, mpEnd);
    } else {
        memcpy(mpBegin, first, (mpEnd - mpBegin) * 2);
        Append(first + (mpEnd - mpBegin), last);
    }
    return *this;
}

// @ 0x00429520
void WStr_s0042_92a0::Resize(uint32_t n)
{
    uint32_t sz = mEnd - mBegin;
    if (n < sz) Erase(mBegin + n, mEnd);
    else if (n > sz) AppendFill(n - sz, 0);
}

// @ 0x00429580
WStr_s0042_92a0* WStr_s0042_92a0::Append(const wchar16* first, const wchar16* last)
{
    uint32_t nOldSize; int n; uint32_t capacity; wchar16* yfv; int k; wchar16* pNewBegin; const wchar16* tvi;
    // Local names are load-bearing: /Od frame slot order follows the symbol table.
    if (first != last) {
        nOldSize = mEnd - mBegin;
        n = last - first;
        capacity = (mCap - mBegin) - 1;
        if (nOldSize + n > capacity) {
            uint32_t nRequired = nOldSize + n;
            uint32_t nGrow = (capacity > 8) ? capacity * 2 : 8;
            k = Max(nGrow, nRequired) + 1;
            pNewBegin = WAlloc(k);
            yfv = pNewBegin;
            yfv = WCopy(mBegin, mEnd, pNewBegin);
            yfv = WCopy(first, last, yfv);
            *yfv = 0;
            Nop3();
            FreeBuffer();
            mBegin = pNewBegin; mEnd = yfv; mCap = pNewBegin + k;
        } else {
            tvi = first; ++tvi;
            WCopy(tvi, last, mEnd + 1);
            mEnd[n] = 0; *mEnd = *first; mEnd = mEnd + n;
        }
    }
    return this;
}

// @ 0x00429760
void WStr_s0042_92a0::AllocateSelf(uint32_t n)
{
    if (n > 1) {
        void* p = EASTL_allocator_allocate(n * 2, g_EditorName, 0, 0, g_AllocatorHdr, 0xd1);
        mBegin = (wchar16*)p;
        mEnd = mBegin;
        mCap = mBegin + n;
    } else {
        mBegin = g_EmptyWStr;
        mEnd = mBegin;
        mCap = mBegin + 1;
    }
}

// @ 0x0042f360
void WString_s0042_f160::SetCapacity(uint32_t n)
{
    uint32_t dead0;
    if (n == (uint32_t)-1 || n <= (uint32_t)(mpEnd - mpBegin)) {
        if (n < (uint32_t)(mpEnd - mpBegin))
            Resize(n);
        struct { uint16_t* b; uint16_t* e; uint16_t* c; } tmp = {0, 0, 0};
        ((WString_s0042_f160*)&tmp)->AllocateSelf(mpBegin, mpEnd);
        Swap(*(WString_s0042_f160*)&tmp);
        ((WString_s0042_f160*)&tmp)->FreeBuffer();
    } else {
        uint16_t* pNew;
        uint16_t* pEnd;
        {
            uint32_t dead1[3];
            pNew = DoAllocate(n);
            pEnd = pNew;
            pEnd = UninitializedCopy16(mpBegin, mpEnd, pNew);
            *pEnd = 0;
            FreeBuffer();
            mpBegin = pNew;
            mpEnd = pEnd;
            mpCapacity = pNew + n;
            DeadHelper();
        }
    }
}

// @ 0x00571d40
void DirtyState::SetKey(const Key12& k)
{
    mKey = k;
    mDirtyFlags |= 4;
    mRevision++;
}

// @ 0x00571d60
VecPair& VecPair::operator=(const VecPair& o)
{
    mB = o.mB;
    mA = o.mA;
    return *this;
}

// @ 0x00571d90
void OwnerHandle::Notify()
{
    mpTarget->Notify(this, 0);
}

// @ 0x00571db0
namespace EA {
namespace Messaging {
bool RemoveHandler(Server * server, IHandler * handler, unsigned int const * ids, unsigned int count, int priority)
{
    bool result = true;
    for (uint32_t i = 0; i < count; ++i)
        if (!server->RemoveHandler(handler, ids[i], priority))
            result = false;
    return result;
}
}
}  // namespace EA::Messaging

// @ 0x00571e60
uint64_t __cdecl GetStopwatchCycle()
{
    int64_t t;
    QueryPerformanceCounter(&t);
    return (uint64_t)t;
}

// @ 0x0057cb60
template <> eastl::basic_string_s0057_bfb0<wchar_t>& eastl::basic_string_s0057_bfb0<wchar_t>::operator=(const basic_string_s0057_bfb0<wchar_t>& x)
{
    if (&x != this)
        assign(x.mpBegin, x.mpEnd);
    return *this;
}

// @ 0x005ca880
void SetGlobalProperty(int a1, float a2)
{
  cAudioSystem* sys = GetSystemAT();
  if (sys) {
    sys->SetId(0x3cdd1a9);
    sys->SetInt(0x34753a7, a1);
    sys->SetFloat(0x34753aa, a2);
    sys->Flush();
  }
}
