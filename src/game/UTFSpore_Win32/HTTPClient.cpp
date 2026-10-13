// src/game/UTFSpore_Win32/HTTPClient.cpp -- migrated from slice(s) s00942ff0, s00942290, s009413d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/HTTPClient.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/HTTPClient.h"
#include <intrin.h>
#include <new>

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);

// ---- items of slice s009413d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
void* __cdecl operator_new_6(unsigned int, const char*, int, int, int, int);
struct HTTPClient {
    bool AllocBuffer();
    bool FindHeader(char* name, void* out, int index);
    void SetNotificationTarget(void* target, void* ctx);
};
void* __cdecl operator_new_6(unsigned int, const char*, int, int, int, int);
// ---- items of slice s009413d0 end

// ---- items of slice s00942290 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);  // 0x00F473A0
extern "C" void __cdecl operator_delete__(void* p);                                 // 0x00F47380
void* __cdecl memmove(void*, const void*, unsigned int);                            // 0x011E0744
namespace eastl {
struct StrStub {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAllocPad;
    void assign(const char* first, const char* last);        // 0x00454CB0
    void assignRange(const char* first, const char* last);   // 0x00942E50 (this slice)
};
}
namespace eastl {
struct FixedStub {
    char data[0x100];
    void assign(const char* first, const char* last);        // 0x0060A2C0
};
}
struct URLClass {
    char data[0x90];
    void  SetURL(const char* url, int force);   // 0x0094A6A0
    void* GetAccessor();                         // 0x0097E850
};
struct UrlHolder {
    char pad0[0x30];
    URLClass mUrl;              // +0x30 .. +0xc0
    char padc0[0x20];
    eastl::FixedStub mString;   // +0xe0
    void  SetURL(const char* url);
};
// ---- items of slice s00942290 end

// ---- items of slice s00942ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int __cdecl strlen(const char* s);
void* __cdecl operator_new(unsigned int size, const char* name, int a, int b,
                           const char* file, int line);
namespace eastl {
struct StrStub_s0094_2ff0 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mnAllocPad;   // +0x0c
    char* mpSelf;       // +0x10  (points at mBuffer)
    char  mBuffer[0x40];// +0x14
    StrStub_s0094_2ff0() {}                                        // (not emitted: no default use)
    StrStub_s0094_2ff0(const StrStub_s0094_2ff0& o) {                         // SSO copy ctor
        mpSelf = mBuffer;
        mpCapacity = mBuffer + 0x40;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        *mBuffer = 0;
        assignRange(o.mpBegin, o.mpEnd);
    }
    StrStub_s0094_2ff0& operator=(const StrStub_s0094_2ff0& o) {
        if (this != &o) {
            if (mpBegin != mpEnd) {
                *mpBegin = 0;
                mpEnd = mpBegin;
            }
            assignRange(o.mpBegin, o.mpEnd);
        }
        return *this;
    }
    void assignRange(const char* first, const char* last);   // 0x00942E50 (slice 49)
    StrStub_s0094_2ff0* assign(const char* s);                          // 0x00943570
};
}
typedef eastl::StrStub_s0094_2ff0 JobString;
struct Job {
    JobString first;    // +0x00
    JobString second;   // +0x54
    Job(const Job& s);                  // 0x00943650
    Job& operator=(const Job& s);       // 0x009436B0
};
struct RefObj {
    virtual void Destroy(int flags);
    int mnRefCount;
    void AddRef() {
        _InterlockedIncrement((volatile long*)&mnRefCount);
    }
    int Release() {
        return _InterlockedDecrement((volatile long*)&mnRefCount);
    }
};
inline void ReleaseRefObj(RefObj* p) {
    if (p) {
        int rc = _InterlockedDecrement((volatile long*)&p->mnRefCount);
        if (rc == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
}
template<class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& o) {
        mpObject = o.mpObject;
        if (mpObject) ((RefObj*)mpObject)->AddRef();
    }
    __forceinline AutoRefCount& operator=(const AutoRefCount& o) {
        Assign(o.mpObject);
        return *this;
    }
    ~AutoRefCount() {
        Release();
    }
    void Release() {
        RefObj* p = (RefObj*)mpObject;
        if (p) {
            int rc = p->Release();
            if (rc == 0) {
                _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
                if (p)
                    p->Destroy(1);
            }
        }
    }
    void Assign(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) ((RefObj*)p)->AddRef();
            mpObject = p;
            if (old) {
                int rc = old->Release();
                if (rc == 0) {
                    _InterlockedExchange((volatile long*)&old->mnRefCount, 1);
                    if (old)
                        old->Destroy(1);
                }
            }
        }
    }
};
struct Cookie40 {
    int   m00, m04, m08, m0c, m10, m14, m18;   // +0x00
    AutoRefCount<RefObj> mp1c;                 // +0x1c
    bool  m20;                                 // +0x20
    AutoRefCount<RefObj> mp24;                 // +0x24
    int   m28;                                 // +0x28
    // +0x2c padding: m30 is 8-byte aligned.
    unsigned __int64 m30;                      // +0x30
    unsigned __int64 m38;                      // +0x38
    ~Cookie40();                 // 0x00942630
};
// @ 0x00942630
Cookie40::~Cookie40() {}

// @ 0x00942ce0  Cookie40 copy constructor (implicit; emitted out-of-line where used)
// @ 0x00942d70  Cookie40 copy assignment (implicit; emission forced below)
// Force out-of-line emission of the implicitly-defined copy assignment (retail 0x00942D70):
// nothing in this module TU odr-uses it, so taking its address is what makes the compiler emit it.
Cookie40& (Cookie40::* g_forceCookie40Assign)(const Cookie40&) = &Cookie40::operator=;
struct CookieNode {
    CookieNode* mpNext;   // +0x00
    CookieNode* mpPrev;   // +0x04
    Cookie40    mData;    // +0x08
    void insertBeforeSelf(const Cookie40& src);   // 0x00943600
};
struct CookieList {
    CookieNode* mpNode;   // +0x00
    void insertAtNext(const Cookie40& src);       // 0x009435B0
};
static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char kEastlName[] = "EASTL";
static inline void InsertBefore(CookieNode* at, const Cookie40& src) {
    CookieNode* node = (CookieNode*)operator_new(0x48, kEastlName, 0, 0, kEastlFile, 0xd1);
    new (&node->mData) Cookie40(src);
    node->mpNext = at;
    node->mpPrev = at->mpPrev;
    at->mpPrev->mpNext = node;
    at->mpPrev = node;
}
struct CellData {
    void* mpVtbl;     // +0
    int   mnRefCount; // +4
};
struct CellPtrVec {
    CellData** mpBegin;     // +0x00
    CellData** mpEnd;       // +0x04
    CellData** mpCapacity;  // +0x08
    void DoInsertValue(CellData**, CellData* const&);   // 0x00A80DD0
};
struct CellHolder {
    char       mPad[0x150];
    CellPtrVec mVec;        // +0x150
    bool AddCell(CellData* p);   // 0x00943D70
};
// ---- items of slice s00942ff0 end

// @ 0x00941f20
bool HTTPClient::AllocBuffer()
{
    int self = (int)this;
    if (*(char*)(self + 0xc) == 0) {
        void* p = operator_new_6(*(uint32_t*)(self + 0x144),
                                 "UTFInternet/char8_t", 0, 0, 0, 0);
        *(void**)(self + 0x140) = p;
        *(char*)(self + 0xc) = 1;
    }
    return true;
}







// @ 0x00942010
bool HTTPClientCheckTimeout(int self, int* timeout)
{
    if (*(int*)(self + 0xc) > 0) {
        __int64 now = _time64(0);
        if (*(int*)(self + 0xc) < (int)now)
            return true;
        if (*timeout > 0) {
            *(int*)(self + 0xc) = *(int*)(self + 8) + (int)now;
            *timeout = 0;
        }
    }
    return false;
}







// @ 0x00942050
bool HTTPClient::FindHeader(char* name, void* out, int index)
{
    int* self = (int*)this;
    int count = (self[1] - *self) / 0xa8;
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (_stricmp(name, *(char**)(*self + i * 0xa8)) == 0) {
            if (found == index) {
                if (out != 0)
                    *(int*)out = *(int*)(i * 0xa8 + *self + 0x54);
                return true;
            }
            found++;
        }
    }
    return false;
}







// @ 0x00942110
void HTTPClientSendCallback(int self, const char* data, int len)
{
    if (len == -1) {
        const char* p = data;
        do {
        } while (*p++ != 0);
        len = (int)(p - (data + 1));
    }
    if (*(int*)(self + 0x30) > 0) {
        (*(void(__thiscall**)(void*, const char*, int))((char*)*(void**)(self + 0x58) + 0x38))(
            *(void**)(self + 0x58), data, len);
    }
}







// @ 0x00942150
void HTTPClient::SetNotificationTarget(void* target, void* ctx)
{
    int self = (int)this;
    void* old = *(void**)(self + 0x24);
    if (old == target) {
        *(void**)(self + 0x28) = ctx;
        return;
    }
    if (old != 0) {
        typedef void (__cdecl* Fn)(void*, int, unsigned, int, int);
        ((Fn)old)(*(void**)(self + 0x28), self, 0x700af201, 0, 0);
    }
    *(void**)(self + 0x24) = target;
    *(void**)(self + 0x28) = ctx;
    if (target != 0) {
        typedef void (__cdecl* Fn)(void*, int, unsigned, int, int);
        ((Fn)target)(ctx, self, 0x700af200, 0, 0);
    }
}






// @ 0x00942e50
void eastl::StrStub::assignRange(const char* first, const char* last)
{
    if (first == last) return;
    unsigned len = (unsigned)(last - first);
    unsigned cap = (unsigned)(mpCapacity - mpBegin) - 1;
    unsigned need = (unsigned)(mpEnd - mpBegin) + len;
    if (cap < need) {
        unsigned newcap = (cap < 9) ? 8 : cap * 2;
        if (need > newcap) newcap = need;
        char* p = (char*)operator new(newcap + 1,
                     "EASTL", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                     0xd1);
        memmove(p, mpBegin, (unsigned)(mpEnd - mpBegin));
        char* dst = p + (mpEnd - mpBegin);
        memmove(dst, first, len);
        dst[len] = 0;
        if (cap > 1 && mpBegin != 0)
            operator_delete__(mpBegin);
        mpBegin = p;
        mpEnd = dst + len;
        mpCapacity = p + newcap + 1;
    } else {
        memmove(mpEnd + 1, first + 1, (unsigned)(last - (first + 1)));
        mpEnd[len] = 0;
        *mpEnd = *first;
        mpEnd += len;
    }
}





// @ 0x00942f70
void UrlHolder::SetURL(const char* url)
{
    mUrl.SetURL(url, 1);
    void* p1 = mUrl.GetAccessor();
    int v1 = *(int*)((char*)p1 + 4);
    void* p2 = mUrl.GetAccessor();
    int v2 = *(int*)p2;
    mString.assign((const char*)v2, (const char*)v1);
}




// @ 0x00943420
void __stdcall JobDestroyRange(Job* first, Job* last)
{
    for (; first < last; first = (Job*)((char*)first + 0xa8)) {
        char* b = first->second.mpBegin;
        if ((int)(first->second.mpCapacity - b) > 1 && b != 0 && b != first->second.mpSelf)
            operator_delete__(b);
        char* a = first->first.mpBegin;
        if ((int)(first->first.mpCapacity - a) > 1 && a != 0 && a != first->first.mpSelf)
            operator_delete__(a);
    }
}

// @ 0x00943480
void __fastcall ListDestroy(CookieNode* head)
{
    CookieNode* n = head->mpNext;
    while (n != head) {
        CookieNode* next = n->mpNext;
        n->mData.mp24.Release();
        n->mData.mp1c.Release();
        operator_delete__(n);
        n = next;
    }
}

// @ 0x00943500
Job* JobDestroyRangeDst(Job* first, Job* last, Job* dst)
{
    if (first != last) {
        do {
            char* b = first->second.mpBegin;
            if ((int)(first->second.mpCapacity - b) > 1 && b != 0 && b != first->second.mpSelf)
                operator_delete__(b);
            char* a = first->first.mpBegin;
            if ((int)(first->first.mpCapacity - a) > 1 && a != 0 && a != first->first.mpSelf)
                operator_delete__(a);
            first = (Job*)((char*)first + 0xa8);
            dst = (Job*)((char*)dst + 0xa8);
        } while (first != last);
    }
    return dst;
}

// @ 0x00943570
eastl::StrStub_s0094_2ff0* eastl::StrStub_s0094_2ff0::assign(const char* s)
{
    if (mpBegin != s) {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
        assignRange(s, s + strlen(s));
    }
    return this;
}

// @ 0x009435b0
void CookieList::insertAtNext(const Cookie40& src)
{
    InsertBefore(mpNode, src);
}

// @ 0x00943600
void CookieNode::insertBeforeSelf(const Cookie40& src)
{
    InsertBefore(this, src);
}

// @ 0x00943650
Job::Job(const Job& s)
: first(s.first), second(s.second) {}

// @ 0x009436b0
Job& Job::operator=(const Job& s)
{
    first = s.first;
    second = s.second;
    return *this;
}

// @ 0x009437a0
Job* CopyJob(Job* first, Job* last, Job* dst)
{
    for (; first != last; dst = (Job*)((char*)dst + 0xa8), first = (Job*)((char*)first + 0xa8))
        *dst = *first;
    return dst;
}

// @ 0x00943830
Job* CopyBackwardJob(Job* first, Job* last, Job* dst)
{
    while (last != first) {
        last = (Job*)((char*)last - 0xa8);
        dst = (Job*)((char*)dst - 0xa8);
        *dst = *last;
    }
    return dst;
}

// @ 0x00943d70
bool CellHolder::AddCell(CellData* p)
{
    if (p != 0) {
        CellData** it = mVec.mpBegin;
        if (it != mVec.mpEnd) {
            do {
                if (*it == p)
                    break;
                ++it;
            } while (it != mVec.mpEnd);
            if (it != mVec.mpEnd)
                return false;
        }
        if (mVec.mpEnd < mVec.mpCapacity) {
            CellData** pEnd = mVec.mpEnd;
            mVec.mpEnd = pEnd + 1;
            if (pEnd != 0)
                *pEnd = p;
        } else {
            mVec.DoInsertValue(mVec.mpEnd, p);
        }
        _InterlockedIncrement((volatile long*)&p->mnRefCount);
        return true;
    }
    return false;
}
