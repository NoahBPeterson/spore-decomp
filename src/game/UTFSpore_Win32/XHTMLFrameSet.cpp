// src/game/UTFSpore_Win32/XHTMLFrameSet.cpp -- migrated from slice(s) s00995b20, s00996f10 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/XHTMLFrameSet.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"
#include "EA/UTFWinExtras/WinXHTML.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void* FUN_009512c0(void);                                    // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void  FUN_00993390(void* self);                              // 0x993390
extern "C" void* FUN_008fe480(void);                                    // XHTML::Resource::GetResourceProvider
extern "C" void  FUN_00992e60(void* a);                                // 0x992e60 (thiscall, see casts)
extern "C" void  FUN_00992ea0(void* a);                                // 0x992ea0
extern "C" void  FUN_00997720(void);                                   // job callback
extern "C" void* WinXHTML_ctor(void* mem);                             // 0x993c10 thiscall
extern "C" void  FUN_009968f0(void);                                 // 0x9968f0
extern "C" int   FUN_00932f30(const wchar_t* s, unsigned seed, int a);   // FNV1_String16
extern "C" void* FUN_00d01260(void* a, void* b, void* c, void* d); // lower_bound (d = empty compare object by value)
extern "C" void  FUN_009970e0(void* a, void* b, void* c);               // vector<map pair>::insert
extern "C" void FUN_00996460(void* p);                                  // 0x996460 deque::clear
extern "C" int g_listNodeOffset;                        // 0x1440aec
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---- items of slice s00996f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
struct DqIter {
    char* cur; char* begin; char* end; char** arr;
    DqIter* __thiscall plus_assign(int n);                                  // 0x9964c0
    void __thiscall move_backward(DqIter* first, DqIter* last, DqIter* out);// 0x996b40
    void __thiscall move_forward(DqIter* tmp, DqIter* next, DqIter* e, DqIter* out); // 0x996ad0
};
struct JobDeque {
    void* a0; void* a4;
    DqIter b;   // +8
    DqIter e;   // +0x18
    DqIter* __thiscall erase(DqIter* out, DqIter pos);
};
struct FrameSetJobs {                   // cXHTMLFrameSet viewed from its job-cleanup method
    bool ClearJobs();
};
struct FrameMessage {                    // UTFWin message block passed to the window's +0x114 handler
    int mPad0[2];
    int mID;        // +8
    int mSource;    // +0xc
    int mPad10[2];
    int mValue;     // +0x18
    FrameMessage(int id, int source, int value) { mID = id; mSource = source; mValue = value; }
};
struct XHTMLDocument {
    void FUN_008e3600(bool flag);                                        // 0x8e3600
};
struct IWindowMsg {                      // WinXHTML's interface at +4; slot 0x114 handles a message
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void s90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual void sa4();
    virtual void sa8();
    virtual void sac();
    virtual void sb0();
    virtual void sb4();
    virtual void sb8();
    virtual void sbc();
    virtual void sc0();
    virtual void sc4();
    virtual void sc8();
    virtual void scc();
    virtual void sd0();
    virtual void sd4();
    virtual void sd8();
    virtual void sdc();
    virtual void se0();
    virtual void se4();
    virtual void se8();
    virtual void sec();
    virtual void sf0();
    virtual void sf4();
    virtual void sf8();
    virtual void sfc();
    virtual void s100();
    virtual void s104();
    virtual void s108();
    virtual void s10c();
    virtual void s110();
    virtual void HandleMessage(FrameMessage* msg);
};
struct WinXHTML {
    void* mpVtbl0;
    IWindowMsg mWindow;                   // +4
    void SetDocument(XHTMLDocument* doc);                                // 0x994b00
};
struct cXHTMLFrameSet {
    WinXHTML* GetJobInfo(void* key, bool* outFlag);
    void LoadRequestCallback(int* p);
};
struct FrameMapPair { unsigned hash; void* win; };
struct FrameMapVM {                      // vector_map<hash, WinXHTML*> part of cXHTMLFrameSet
    bool insert(void* win, const wchar_t* name);
};
struct FrameSetExt {
    bool __thiscall AddFrameEntry(void* win, const wchar_t* name); // 0x997350
};
struct FrameSet {
    void* CreateFrame(void* src);                                         // 0x9973e0
    bool HandleLocationChange(int* p, void* a3, wchar_t* name, int flag); // 0x997730
    bool FindFrames(void* root, int id);                                  // 0x9979f0
    bool Bind(int** a1, int id, int* a3);                                 // 0x997bf0
};
struct JobEntry { void* a; void* win; unsigned char flag; };
struct FixedWString96 {                 // eastl::fixed_string<wchar_t, 96> on the stack
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAllocName; wchar_t* mpPoolBegin;
    wchar_t mBuffer[96];
};
struct WString { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAlloc; };
struct PtrStack {
    void** b; void** e; void** c;
    void __thiscall DoInsertValue(void** pos, void** v);   // 0x630b30
    void push_back(void* v)
    {
        void** p = e;
        if (p < c) {
            e = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(p, &v);
        }
    }
};
extern "C" void  FUN_008e4b10(void* a, void* b);                        // 0x8e4b10
extern "C" void  FUN_008e4f00(void* a, void* b, void* c);               // 0x8e4f00
extern "C" void  FUN_00579a90(void* str, void* a, void* b, int c, int d, int e); // RangeInitialize
extern "C" void  FUN_00599bb0(void* str, void* src);                    // string operator+=
// ---- items of slice s00996f10 end

// unnamed retail callees and globals that name local stubs (address in the comment)

// ---- items of slice s00995b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __stdcall FUN_00883de0(int a, int b);
extern "C" char* __cdecl FUN_0099efa0(const char* first, const char* last, char* out);
extern "C" void* __cdecl FUN_00f473a0(uint32_t n, const char* name, int a, int b, const char* file, int line);
class JobQueue {
public:
    uint32_t f00;   // @+0x00
    uint32_t f04;   // @+0x04
    uint32_t f08;   // @+0x08
    uint32_t f0c;   // @+0x0c
    uint32_t f10;   // @+0x10
    uint32_t f14;   // @+0x14
    uint32_t f18;   // @+0x18
    uint32_t f1c;   // @+0x1c
    uint32_t f20;   // @+0x20
    uint32_t f24;   // @+0x24
    void FUN_00996640();
    void FUN_009966b0(uint32_t n);
    void FUN_009968f0(void* e);
    void Zero() { f00=0; f04=0; f08=0; f0c=0; f10=0; f14=0; f18=0; f1c=0; f20=0; f24=0; }
};
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define EASTL_NEW(n) FUN_00f473a0((n), "EASTL", 0, 0, EASTL_ALLOC_FILE, 0xd1)
class cXHTMLFrameSet_s0099_5b20 {
public:
    void*    mVftable;              // @0x00 (AddRef vtable)
    void*    mVftable2;             // @0x04
    uint32_t mField08;              // @0x08
    void*    mField0c;              // @0x0c
    uint32_t mField10;              // @0x10
    uint32_t mField14;              // @0x14
    uint32_t mField18;              // @0x18
    uint32_t mField1c;              // @0x1c
    uint8_t  mField20;              // @0x20
    uint8_t  mPad21[3];
    JobQueue mJobQueue;             // @0x24 (0x28 bytes)
    uint32_t mField4c;              // @0x4c
    uint32_t mField50;              // @0x50
    uint32_t mField54;              // @0x54
    uint32_t mField58;              // @0x58
    uint32_t mField5c;              // @0x5c
    uint32_t mField60;              // @0x60

    cXHTMLFrameSet_s0099_5b20(void* frameFactory);
    void FUN_00996280(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
    bool FUN_00996410(void* a, void* b);
    ~cXHTMLFrameSet_s0099_5b20();
    void* FUN_00996a80(uint8_t flags);
    void FUN_009968f0(uint32_t* e);
    void FUN_00996bb0(uint32_t* a, uint32_t* b);
    uint32_t GetFrame(const uint16_t* str);  // 0x00996d40 (cXHTMLFrameSet::GetFrame)
};
#define EA_DELETE_ARRAY(p) FUN_00f47380(p)
struct XDomElement;
class WinXHTML_ {
public:
    void FUN_00992e60(uint32_t v);
    void FUN_00992ea0(uint32_t v);
    void FUN_00995b20(XDomElement* fc, const uint16_t* value);
    void FUN_00995ea0(XDomElement* fc, void* out);
    bool FUN_009960b0(float x, float y, uint32_t button, uint32_t flags);
};
#define VF_s0099_5b20(p, i) (*(void**)((char*)(*(void**)(p)) + (i) * 4))
template <class T> inline const T& eastl_max(const T& a, const T& b) { return a > b ? a : b; }
struct JobIter {
    int*  mpCurrent;            // @0x00
    int*  mpBegin;              // @0x04
    int*  mpEnd;                // @0x08
    int** mpCurrentArrayPtr;    // @0x0c
    JobIter& operator+=(int n);
};
extern "C" uint32_t  __cdecl FNV1_String16(const uint16_t* s, uint32_t base, int n);
extern "C" uint32_t* __cdecl FUN_00d01260_s0099_5b20(uint32_t* begin, uint32_t* end, uint32_t* key, uint8_t compare);
struct DqIt {
    uint32_t*  mpCurrent;            // @0x00
    uint32_t*  mpBegin;              // @0x04
    uint32_t*  mpEnd;                // @0x08
    uint32_t** mpCurrentArrayPtr;    // @0x0c
};
class Vec8 {
public:
    uint32_t* mpBegin;      // @0x00
    uint32_t* mpEnd;        // @0x04
    uint32_t* mpCapacity;   // @0x08
    void insert(uint32_t* pos, uint32_t* value);
};
struct XDomElement {
    void*         mpVtbl;        // @0x00 (Node vtable)
    XDomElement*  mpNext;        // @0x04 (intrusive_list_node.mpNext)
    XDomElement*  mpPrev;        // @0x08
    uint32_t      mnType;        // @0x0c
    void*         mpDocument;    // @0x10
    XDomElement*  mpParent;      // @0x14
    XDomElement*  mpChildFirst;  // @0x18 (child-list anchor .mpNext)
    XDomElement*  mpChildLast;   // @0x1c
    uint8_t       mPad20[0x08];  // @0x20
    uint32_t      mElementType;  // @0x28
    uint8_t       mPad2c[0x18];  // @0x2c
    void*         mpFormObj;     // @0x44 (object whose vtable[3] yields IFormControlMgr)
};
// ---- items of slice s00995b20 end

// @ 0x00996280
void __thiscall cXHTMLFrameSet_s0099_5b20::FUN_00996280(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    mField54 = a;
    mField58 = b;
    mField5c = c;
    mField60 = d;
}

// @ 0x009962a0
DqIt __cdecl FUN_009962a0(DqIt first, DqIt last, DqIt result)
{
    while (first.mpCurrent != last.mpCurrent) {
        *(uint32_t*)(result.mpCurrent + 0) = *(uint32_t*)(first.mpCurrent + 0);
        *(uint32_t*)(result.mpCurrent + 1) = *(uint32_t*)(first.mpCurrent + 1);
        *(uint32_t*)(result.mpCurrent + 2) = *(uint32_t*)(first.mpCurrent + 2);
        result.mpCurrent += 3;
        if (result.mpCurrent == result.mpEnd) {
            result.mpCurrentArrayPtr += 1;
            result.mpBegin = *result.mpCurrentArrayPtr;
            result.mpEnd = result.mpBegin + 0x30;
            result.mpCurrent = result.mpBegin;
        }
        first.mpCurrent += 3;
        if (first.mpCurrent == first.mpEnd) {
            first.mpCurrentArrayPtr += 1;
            first.mpBegin = *first.mpCurrentArrayPtr;
            first.mpEnd = first.mpBegin + 0x30;
            first.mpCurrent = first.mpBegin;
        }
    }
    return result;
}

// @ 0x00996360
DqIt __cdecl FUN_00996360(DqIt first, DqIt last, DqIt result)
{
    while (first.mpCurrent != last.mpCurrent) {
        if (first.mpCurrent == first.mpBegin) {
            first.mpCurrentArrayPtr -= 1;
            first.mpBegin = *first.mpCurrentArrayPtr;
            first.mpCurrent = first.mpBegin + 0x30;
        }
        if (result.mpCurrent == result.mpBegin) {
            result.mpCurrentArrayPtr -= 1;
            result.mpBegin = *result.mpCurrentArrayPtr;
            result.mpEnd = result.mpBegin + 0x30;
            result.mpCurrent = result.mpBegin + 0x30;
        }
        first.mpCurrent -= 3;
        result.mpCurrent -= 3;
        *(uint32_t*)(result.mpCurrent + 0) = *(uint32_t*)(first.mpCurrent + 0);
        *(uint32_t*)(result.mpCurrent + 1) = *(uint32_t*)(first.mpCurrent + 1);
        *(uint32_t*)(result.mpCurrent + 2) = *(uint32_t*)(first.mpCurrent + 2);
    }
    return result;
}

// @ 0x00996410
bool __thiscall cXHTMLFrameSet_s0099_5b20::FUN_00996410(void* a, void* b)
{
    if (*(int*)((char*)b + 8) == 0x51a1a2d && a != 0) {
        void* obj = ((void*(__thiscall*)(void*, int))VF_s0099_5b20(a, 0xc / 4))(a, 0x4d044f3);
        if (obj != 0) {
            ((WinXHTML_*)obj)->FUN_00992e60(mField54);
            ((WinXHTML_*)obj)->FUN_00992ea0(mField58);
        }
    }
    return false;
}

// @ 0x009964c0
JobIter& __thiscall JobIter::operator+=(int n)
{
    int idx = (int)((char*)mpCurrent - (char*)mpBegin) / 12;
    unsigned u = (unsigned)(idx + n);
    if (u < 0x10) {
        mpCurrent = (int*)((char*)mpCurrent + n * 12);
        return *this;
    }
    int blk = (int)(u + 0x1000000) / 16 - 0x100000;
    int** newPtr = mpCurrentArrayPtr + blk;
    mpCurrentArrayPtr = newPtr;
    mpBegin = *newPtr;
    mpEnd = (int*)((char*)mpBegin + 0xc0);
    mpCurrent = (int*)((char*)mpBegin + (int)(u + (unsigned)(blk * -16)) * 12);
    return *this;
}

// @ 0x009966b0
void __thiscall JobQueue::FUN_009966b0(uint32_t n)
{
    uint32_t nCount = (n >> 4) + 1;
    uint32_t cnt = eastl_max(nCount + 2, (uint32_t)8);
    f04 = cnt;
    int* pool = (int*)EASTL_NEW(cnt * 4);
    int* p0 = pool + ((cnt - nCount) >> 1);
    int* p1 = p0 + nCount;
    f00 = (uint32_t)pool;
    for (int* p = p0; p < p1; p++)
        *p = (int)EASTL_NEW(0xc0);
    f14 = (uint32_t)p0;
    uint32_t t = *(uint32_t*)p0;
    f0c = t;
    f10 = t + 0xc0;
    f08 = f0c;
    f24 = (uint32_t)(p1 - 1);
    uint32_t t2 = *(uint32_t*)(p1 - 1);
    f1c = t2;
    f20 = t2 + 0xc0;
    f18 = f1c + (n & 0xf) * 0xc;
}

// @ 0x009968a0
__thiscall cXHTMLFrameSet_s0099_5b20::~cXHTMLFrameSet_s0099_5b20()
{
    *(uint32_t*)((char*)this + 0x00) = 0x14467bc;
    *(uint32_t*)((char*)this + 0x04) = 0x14467ac;
    ((JobQueue*)((char*)this + 0x24))->FUN_00996640();
    if (mField0c != 0)
        EA_DELETE_ARRAY(mField0c);
    *(uint32_t*)((char*)this + 0x04) = 0x13ec458;
    *(uint32_t*)((char*)this + 0x00) = 0x13eb938;
}

// @ 0x009968f0
void __thiscall JobQueue::FUN_009968f0(void* e)
{
    uint32_t v0 = *(uint32_t*)((char*)e + 0);
    uint32_t v1 = *(uint32_t*)((char*)e + 4);
    uint32_t v2 = *(uint32_t*)((char*)e + 8);
    if (((int32_t)(f24 - f00) >> 2) + 1 >= (int32_t)f04)
        FUN_00883de0(1, 1);
    uint32_t blk = (uint32_t)EASTL_NEW(0xc0);
    *(uint32_t*)(f24 + 4) = blk;
    uint32_t dst = f18;
    if (dst != 0) {
        *(uint32_t*)(dst + 0) = v0;
        *(uint32_t*)(dst + 4) = v1;
        *(uint32_t*)(dst + 8) = v2;
    }
    uint32_t old = f24;
    f24 = old + 4;
    uint32_t nb = *(uint32_t*)(old + 4);
    f1c = nb;
    f20 = f1c + 0xc0;
    f18 = f1c;
}

// @ 0x00996a80
void* __thiscall cXHTMLFrameSet_s0099_5b20::FUN_00996a80(uint8_t flags)
{
    *(uint32_t*)((char*)this + 0x00) = 0x14467bc;
    *(uint32_t*)((char*)this + 0x04) = 0x14467ac;
    ((JobQueue*)((char*)this + 0x24))->FUN_00996640();
    if (mField0c != 0)
        EA_DELETE_ARRAY(mField0c);
    *(uint32_t*)((char*)this + 0x04) = 0x13ec458;
    *(uint32_t*)((char*)this + 0x00) = 0x13eb938;
    if ((flags & 1) != 0)
        EA_DELETE_ARRAY(this);
    return this;
}

// @ 0x00996bb0
void __thiscall Vec8::insert(uint32_t* pos, uint32_t* value)
{
    uint32_t* e = mpEnd;
    if (e != mpCapacity) {
        uint32_t* v = value;
        if (v >= pos && v < e)
            v = v + 2;
        if (e != 0) {
            e[0] = e[-2];
            e[1] = e[-1];
        }
        uint32_t* cur = mpEnd;
        uint32_t* dst = mpEnd;
        while ((cur = cur - 2) != pos) {
            dst[-2] = cur[-2];
            dst[-1] = cur[-1];
            dst -= 2;
        }
        pos[0] = v[0];
        pos[1] = v[1];
        mpEnd += 2;
        return;
    }
    int count = (int)((char*)e - (char*)mpBegin) >> 3;
    uint32_t* nb;
    int newCap;
    if (count == 0) {
        newCap = 1;
    } else {
        newCap = count * 2;
    }
    if (newCap != 0)
        nb = (uint32_t*)EASTL_NEW(newCap * 8);
    else
        nb = 0;
    uint32_t* p1 = (uint32_t*)FUN_0099efa0((const char*)mpBegin, (const char*)pos, (char*)nb);
    if (p1 != 0) {
        p1[0] = ((uint32_t*)value)[0];
        p1[1] = ((uint32_t*)value)[1];
    }
    uint32_t* p2 = (uint32_t*)FUN_0099efa0((const char*)pos, (const char*)mpEnd, (char*)(p1 + 2));
    if (mpBegin != 0)
        EA_DELETE_ARRAY(mpBegin);
    mpBegin = nb;
    mpEnd = p2;
    mpCapacity = nb + newCap * 2;
}

// @ 0x00996cc0
__thiscall cXHTMLFrameSet_s0099_5b20::cXHTMLFrameSet_s0099_5b20(void* frameFactory)
{
    *(void* volatile*)((char*)this + 4) = (void*)0x13ec458;
    mField08  = 0;
    mVftable  = (void*)0x14467bc;
    mVftable2 = (void*)0x14467ac;
    mField0c  = 0;
    mField10  = 0;
    mField14  = 0;
    JobQueue* q = &mJobQueue;
    q->Zero();
    mJobQueue.FUN_009966b0(0);
    mField50 = (uint32_t)frameFactory;
    mField5c = 0x1003;
    mField60 = 0x1003;
    mField54 = 0x1002;
    mField58 = 0x1006;
}

// @ 0x00996d40
uint32_t __thiscall cXHTMLFrameSet_s0099_5b20::GetFrame(const uint16_t* str)
{
    uint32_t hash = FNV1_String16(str, 0x811c9dc5, 0);
    uint32_t* end = (uint32_t*)mField10;
    uint32_t key = hash;
    uint32_t* it = FUN_00d01260_s0099_5b20((uint32_t*)mField0c, end, &key, mField20);
    if (it != end && !(key < *it) && it != it + 2)
        return it[1];
    return 0;
}

// @ 0x00996da0
void __cdecl FUN_00996da0(const uint16_t* name, const uint16_t* value, void* params)
{
    (void)name;
    (void)value;
    (void)params;
    // incomplete
}

// @ 0x00996f10
DqIter* JobDeque::erase(DqIter* out, DqIter pos)
{
    DqIter next = pos;
    next.cur = pos.cur + 0xc;
    if (next.cur == pos.end) {
        next.arr = pos.arr + 1;
        next.begin = *next.arr;
        next.end = next.begin + 0xc0;
        next.cur = next.begin;
    }
    int idx = (int)(((pos.arr - b.arr)) * 16) + (int)((b.end - b.cur) / 0xc) + (int)((pos.cur - pos.begin) / 0xc) - 0x10;
    unsigned size = (unsigned)((((e.arr - b.arr) - 1) * 16) + (int)((e.cur - e.begin) / 0xc) + (int)((b.end - b.cur) / 0xc));
    if (idx < (int)(size >> 1)) {
        next.move_backward(&b, &pos, out);
        if (b.cur + 0xc == b.end) {
            if (b.begin)
                FUN_00f47380(b.begin);
            b.arr = b.arr + 1;
            b.begin = *b.arr;
            b.end = b.begin + 0xc0;
            b.cur = b.begin;
        } else {
            b.cur = b.cur + 0xc;
        }
    } else {
        DqIter tmp;
        pos.move_forward(&tmp, &next, &e, out);
        if (e.cur == e.begin) {
            if (e.begin)
                FUN_00f47380(e.begin);
            e.arr = e.arr - 1;
            e.begin = *e.arr;
            e.end = e.begin + 0xc0;
            e.cur = e.end - 0xc;
        } else {
            e.cur = e.cur - 0xc;
        }
    }
    DqIter t = b;
    DqIter* r = t.plus_assign(idx);
    *out = *r;
    return out;
}

// @ 0x00997140
bool FrameSetJobs::ClearJobs()
{
    char* self = (char*)this;
    char* piVar4 = (char*)FUN_008fe480();
    if (piVar4 != 0) {
        char* puVar1 = *(char**)(self + 0x3c);
        char* puVar6 = *(char**)(self + 0x2c);
        char* puVar2 = *(char**)(self + 0x34);
        char* iVar5 = *(char**)(self + 0x38);
        while (puVar6 != puVar1) {
            (*(void(__thiscall**)(char*, void*))((char*)*(void**)piVar4 + 8))(piVar4, *(void**)puVar6);
            puVar6 += 0x0c;
            if (puVar6 == puVar2) {
                puVar6 = *(char**)(iVar5 + 4);
                iVar5 += 4;
                puVar2 = puVar6 + 0xc0;
            }
        }
    }
    ((void(__thiscall*)(char*))FUN_00996460)(self + 0x24);
    char* iVar3 = *(char**)(self + 0x10);
    for (char* iVar5 = *(char**)(self + 0xc); iVar5 != iVar3; iVar5 += 8) {
        ((void(__thiscall*)(void*))FUN_00993390)(*(void**)(iVar5 + 4));
        (*(void(__thiscall**)(char*, char*))
            ((char*)*(void**)(*(int*)(iVar5 + 4) + 4) + 0x108))((char*)(*(int*)(iVar5 + 4) + 4), self);
    }
    char* end = *(char**)(self + 0x10);
    int n = (int)((end - *(char**)(self + 0xc)) >> 3);
    *(char**)(self + 0x10) = end + n * -8;
    return true;
}

// @ 0x00997210
WinXHTML* cXHTMLFrameSet::GetJobInfo(void* key, bool* outFlag)
{
    char* self = (char*)this;
    char* a = *(char**)(self + 0x2c);
    char* end = *(char**)(self + 0x3c);
    char* ebp = *(char**)(self + 0x34);
    char* esi = *(char**)(self + 0x30);
    char* edi = *(char**)(self + 0x38);
    while (a != end) {
        if (*(void**)a == key)
            break;
        a += 0x0c;
        if (a == ebp) {
            esi = *(char**)(edi + 4);
            edi += 4;
            ebp = esi + 0xc0;
            a = esi;
        }
    }
    if (a == end)
        return 0;
    WinXHTML* ret = *(WinXHTML**)(a + 4);
    *outFlag = *(bool*)(a + 8);
    DqIter found;
    found.cur = a; found.begin = esi; found.end = ebp; found.arr = (char**)edi;
    DqIter res;
    ((JobDeque*)(self + 0x24))->erase(&res, found);
    return ret;
}

// @ 0x009972a0
void cXHTMLFrameSet::LoadRequestCallback(int* p)
{
    if (*p == 4)
        return;
    bool flag;
    WinXHTML* win = GetJobInfo((void*)p[1], &flag);
    if (*p == 3) {
        FrameMessage msg(0x43b0aee, p[1], p[3]);
        win->mWindow.HandleMessage(&msg);
        return;
    }
    void* src;
    if (*p == 2 && (src = (void*)p[4]) != 0) {
        XHTMLDocument* q = (XHTMLDocument*)(*(void*(__thiscall**)(void*, int))((char*)*(void**)src + 0xc))(src, 0x2b29464);
        if (q) {
            (*(void(__thiscall**)(XHTMLDocument*))*(void**)q)(q);
            if (win) {
                q->FUN_008e3600(flag);
                win->SetDocument(q);
            }
            (*(void(__thiscall**)(XHTMLDocument*))((char*)*(void**)q + 4))(q);
        }
    }
}

// @ 0x00997350
bool FrameMapVM::insert(void* win, const wchar_t* name)
{
    char* self = (char*)this;
    FrameMapPair v;
    v.hash = (unsigned)FUN_00932f30(name, 0x811c9dc5, 0);
    v.win = win;
    char* end = *(char**)(self + 0x10);
    char* low = (char*)FUN_00d01260(*(void**)(self + 0xc), end, &v.hash, (void*)(unsigned)*(unsigned char*)(self + 0x20));
    if (low != end && *(unsigned*)low <= v.hash)
        return false;
    ((void(__thiscall*)(char*, void*, void*))FUN_009970e0)(self + 0xc, low, &v);
    char* iface = (char*)win + 4;
    (*(void(__thiscall**)(char*, char*))((char*)*(void**)iface + 0x104))(iface, self);
    return true;
}

// @ 0x009973e0
void* FrameSet::CreateFrame(void* src)
{
    char* self = (char*)this;
    char* win;
    typedef void* (__thiscall* FactoryFn)(char*);
    FactoryFn factory = *(FactoryFn*)(self + 0x50);
    if (factory == 0) {
        void* mem = FUN_009512d0(0xa8e8, 8, "XHTML/FrameSet/WinXHTML", FUN_009512c0());
        if (mem)
            win = (char*)((void*(__thiscall*)(void*))WinXHTML_ctor)(mem);
        else
            win = 0;
    } else {
        win = (char*)factory(self);
    }
    void* w2 = win + 4;
    void* slot60 = *(void**)((char*)*(void**)w2 + 0x60);
    VF(w2, 0x60, void(__thiscall*)(void*, int))(w2, VF(src, 0x34, int(__thiscall*)(void*))(src));
    VF(w2, 0xac, void(__thiscall*)(void*, int))(w2, VF(src, 0xa4, int(__thiscall*)(void*))(src));
    VF(w2, 0x50, void(__thiscall*)(void*, int))(w2, VF(src, 0x1c, int(__thiscall*)(void*))(src));
    VF(w2, 0x54, void(__thiscall*)(void*, int))(w2, VF(src, 0x20, int(__thiscall*)(void*))(src));
    (void)slot60;
    typedef unsigned (__thiscall* GetFlags)(void*);
    typedef void (__thiscall* SetFlag)(void*, int, int);
    static const struct { int mask; int shift; } bits[] = {
        {1, 0}, {2, 1}, {8, 3}, {0x10, 4}, {0x800, 0xb}, {0x400, 0xa},
        {0x40, 6}, {4, 2}, {0x80, 7}, {0x200, 9}
    };
    for (int i = 0; i < 10; i++) {
        unsigned f = VF(src, 0x28, GetFlags)(src);
        VF(w2, 0x7c, SetFlag)(w2, bits[i].mask, (f >> bits[i].shift) & 1);
    }
    const wchar_t* name = VF(src, 0x3c, const wchar_t*(__thiscall*)(void*))(src);
    ((FrameSetExt*)self)->AddFrameEntry(win, name);

    for (void* c = VF(src, 0x10c, void*(__thiscall*)(void*, void*))(src, 0); c;
         c = VF(src, 0x10c, void*(__thiscall*)(void*, void*))(src, c)) {
        if (VF(c, 0xc, void*(__thiscall*)(void*, unsigned))(c, 0xcf3df10b)) {
            VF(w2, 0x104, void(__thiscall*)(void*))(w2);
            break;
        }
    }

    int itEnd, itBeg;
    int* pe = VF(src, 0xd0, int*(__thiscall*)(void*, int*))(src, &itEnd);
    int* pb = VF(src, 0xcc, int*(__thiscall*)(void*, int*))(src, &itBeg);
    while (*pb != *pe) {
        int tmp;
        int* q = VF(src, 0xcc, int*(__thiscall*)(void*, int*))(src, &tmp);
        void* child = (void*)(*q + g_listNodeOffset);
        VF(child, 0, void(__thiscall*)(void*))(child);
        VF(src, 0xdc, void(__thiscall*)(void*, void*))(src, child);
        VF(w2, 0xd8, void(__thiscall*)(void*, void*))(w2, child);
        VF(child, 4, void(__thiscall*)(void*))(child);
        pe = VF(src, 0xd0, int*(__thiscall*)(void*, int*))(src, &itEnd);
        pb = VF(src, 0xcc, int*(__thiscall*)(void*, int*))(src, &itBeg);
    }

    void* parent = VF(src, 0x10, void*(__thiscall*)(void*))(src);
    VF(parent, 0xe0, void(__thiscall*)(void*, void*))(parent, src);
    VF(parent, 0xd8, void(__thiscall*)(void*, void*))(parent, w2);
    void* x = VF(win, 0xc, void*(__thiscall*)(void*, unsigned))(win, 0xeeee8218);
    VF(x, 0x94, void(__thiscall*)(void*))(x);
    return VF(win, 0xc, void*(__thiscall*)(void*, unsigned))(win, 0xeeee8218);
}

// @ 0x00997730
bool FrameSet::HandleLocationChange(int* p, void* a3, wchar_t* name, int flag)
{
    char* self = (char*)this;
    char* win;
    if (p != 0)
        win = (char*)VF(p, 0xc, void*(__thiscall*)(int*, unsigned))(p, 0x4d044f3);
    else
        win = 0;
    if (name != 0) {
        unsigned h = (unsigned)FUN_00932f30(name, 0x811c9dc5, 0);
        char* end = *(char**)(self + 0x10);
        char* it = (char*)FUN_00d01260(*(void**)(self + 0xc), end, &h, (void*)(unsigned)*(unsigned char*)(self + 0x20));
        if (it == end || h < *(unsigned*)it)
            it = end;
        else if (it == it + 8)
            it = end;
        if (it != end)
            win = *(char**)(it + 4);
    }
    void* prov = FUN_008fe480();
    if (win == 0 || prov == 0)
        return false;
    ((void(__thiscall*)(char*, int))FUN_00992e60)(win, *(int*)(self + 0x5c));
    ((void(__thiscall*)(char*, int))FUN_00992ea0)(win, *(int*)(self + 0x60));
    ((void(__thiscall*)(char*))FUN_00993390)(win);
    {
        char* cur = *(char**)(self + 0x2c);
        char* end = *(char**)(self + 0x3c);
        char* segEnd = *(char**)(self + 0x34);
        char** arr = *(char***)(self + 0x38);
        while (cur != end) {
            if (*(char**)(cur + 4) == win)
                VF(prov, 8, void(__thiscall*)(void*, void*))(prov, *(void**)cur);
            cur += 0xc;
            if (cur == segEnd) {
                cur = arr[1];
                arr++;
                segEnd = cur + 0xc0;
            }
        }
    }
    JobEntry je;
    je.win = win;
    je.flag = (unsigned char)flag;
    char* e = *(char**)(self + 0x3c);
    char* dq = self + 0x24;
    if (e + 0xc != *(char**)(dq + 0x20)) {
        *(char**)(dq + 0x18) = e + 0xc;
        if (e != 0)
            *(JobEntry*)e = je;
    } else {
        ((void(__thiscall*)(char*, JobEntry*))FUN_009968f0)(dq, &je);
    }
    char* cur = *(char**)(self + 0x3c);
    if (cur == *(char**)(self + 0x40))
        cur = *(char**)(*(char***)(self + 0x48) - 1) + 0xc0;
    VF(prov, 4, void(__thiscall*)(void*, char*, void*, void*, char*, int, int))(prov, cur - 0xc, a3, (void*)FUN_00997720, self, 0, flag);
    return true;
}

// @ 0x009978b0
bool EA::UTFWinExtras::cXHTMLFrameSet::HandleFormSubmit(EA::UTFWin::IWindow * p, EA::XHTML::DOM::Form * form)
{
    FixedWString96 fs;
    fs.mpBegin = fs.mBuffer;
    fs.mpEnd = fs.mBuffer;
    fs.mpCapacity = fs.mBuffer + 96;
    fs.mpPoolBegin = fs.mBuffer;
    fs.mBuffer[0] = 0;
    bool result = false;
    if (form != 0 && ((bool(__thiscall*)(void*, FixedWString96*))FUN_008e4b10)(form, &fs)
        && (fs.mpEnd - fs.mpBegin) != 0) {
        WString s;
        s.mpBegin = 0; s.mpEnd = 0; s.mpCapacity = 0;
        ((void(__thiscall*)(WString*, const wchar_t*))FUN_00579a90)(&s, fs.mpBegin);
        ((void(__thiscall*)(WString*, const void*))FUN_00599bb0)(&s, (const void*)0x1459c40);
        ((void(__thiscall*)(void*, void*, WString*))FUN_008e4f00)(form, (void*)0x996da0, &s);
        HandleLocationChange(p, s.mpBegin, 0, 0);
        if ((s.mpCapacity - s.mpBegin) > 1 && s.mpBegin)
            FUN_00f47380(s.mpBegin);
        result = true;
    }
    if ((fs.mpCapacity - fs.mpBegin) > 1 && fs.mpBegin && fs.mpBegin != fs.mpPoolBegin)
        FUN_00f47380(fs.mpBegin);
    return result;
}

// @ 0x009979f0
bool FrameSet::FindFrames(void* root, int id)
{
    char* self = (char*)this;
    if (root) {
        PtrStack st;
        st.b = 0; st.e = 0; st.c = 0;
        st.DoInsertValue(0, &root);
        while (st.b != st.e) {
            void* w = *--st.e;
            if (VF(w, 0x1c, int(__thiscall*)(void*))(w) == id)
                w = ((FrameSet*)self)->CreateFrame(w);
            int end;
            VF(w, 0xcc, void(__thiscall*)(void*, void**))(w, &root);
            VF(w, 0xd0, void(__thiscall*)(void*, int*))(w, &end);
            for (; (int)root != end; root = *(void**)root)
                st.push_back((void*)((int)root + g_listNodeOffset));
        }
        if (st.b && ((int*)st.b)[-1])
            FUN_00f47380(st.b);
    }
    return *(int*)(self + 0xc) != *(int*)(self + 0x10);
}
