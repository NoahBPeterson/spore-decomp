// Slice s00995b20 — EA::UTFWinExtras WinXHTML / cXHTMLFrameSet and EASTL helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef int            int32_t;

// 0x00f473a0 — debug-named operator new: (size, name, 0, 0, file, line)
extern "C" void* __cdecl FUN_00f473a0(uint32_t n, const char* name, int a, int b, const char* file, int line);
// 0x00f47380 — operator delete[]
extern "C" void  __cdecl FUN_00f47380(void* p);

// ===========================================================================
// cXHTMLFrameSet — layout (only what this slice touches)
// ===========================================================================

// 0x00996640 — eastl::deque<...JobEntry...,16>::~deque
// 0x009966b0 — eastl::deque<...JobEntry...,16>::deque(n)
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

// 0x00883de0 — deque growth assert/throw helper: (1,1) __stdcall (cleans args)
extern "C" void __stdcall FUN_00883de0(int a, int b);

// the inline allocator debug path string passed to FUN_00f473a0
#define EASTL_ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

#define EASTL_NEW(n) FUN_00f473a0((n), "EASTL", 0, 0, EASTL_ALLOC_FILE, 0xd1)

class cXHTMLFrameSet {
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

    cXHTMLFrameSet(void* frameFactory);
    void FUN_00996280(uint32_t a, uint32_t b, uint32_t c, uint32_t d);
    bool FUN_00996410(void* a, void* b);
    ~cXHTMLFrameSet();
    void* FUN_00996a80(uint8_t flags);
    void FUN_009968f0(uint32_t* e);
    void FUN_00996bb0(uint32_t* a, uint32_t* b);
    uint32_t GetFrame(const uint16_t* str);
};

// @ 0x00996cc0 — EA::UTFWinExtras::cXHTMLFrameSet::cXHTMLFrameSet
__thiscall cXHTMLFrameSet::cXHTMLFrameSet(void* frameFactory) {
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

#define EA_DELETE_ARRAY(p) FUN_00f47380(p)

// 0x00996460 — eastl::deque<SP::cStarRecord_*,eastl::allocator,64>::clear
class StarDeque {
public:
    uint8_t mPad00[8];
    void*   mBegin;      // @0x08
    void*   mField0c;    // @0x0c
    void*   mField10;    // @0x10
    void*   mItBegin;    // @0x14  (iterator array ptr)
    void*   mEnd;        // @0x18
    void*   mpPool;      // @0x1c  (current block)
    void*   mField20;    // @0x20
    void*   mItEnd;      // @0x24
    void clear();
};

// @ 0x00996460
void __thiscall StarDeque::clear() {
    if (mItBegin != mItEnd && mpPool != 0)
        EA_DELETE_ARRAY(mpPool);
    void** p = (void**)((char*)mItBegin + 4);
    if (p < (void**)mItEnd) {
        do {
            if (*p != 0)
                EA_DELETE_ARRAY(*p);
            p++;
        } while (p < (void**)mItEnd);
    }
    mEnd    = mBegin;
    mpPool  = mField0c;
    mField20 = mField10;
    mItEnd  = mItBegin;
}

// @ 0x009968a0 — EA::UTFWinExtras::cXHTMLFrameSet::~cXHTMLFrameSet
__thiscall cXHTMLFrameSet::~cXHTMLFrameSet() {
    *(uint32_t*)((char*)this + 0x00) = 0x14467bc;
    *(uint32_t*)((char*)this + 0x04) = 0x14467ac;
    ((JobQueue*)((char*)this + 0x24))->FUN_00996640();
    if (mField0c != 0)
        EA_DELETE_ARRAY(mField0c);
    *(uint32_t*)((char*)this + 0x04) = 0x13ec458;
    *(uint32_t*)((char*)this + 0x00) = 0x13eb938;
}

// @ 0x00996a80 — cXHTMLFrameSet::`scalar deleting dtor'
void* __thiscall cXHTMLFrameSet::FUN_00996a80(uint8_t flags) {
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

// @ 0x00996280
void __thiscall cXHTMLFrameSet::FUN_00996280(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    mField54 = a;
    mField58 = b;
    mField5c = c;
    mField60 = d;
}

// 0x00992e60 / 0x00992ea0 — WinXHTML setters used by FUN_00996410
struct XDomElement;
class WinXHTML_ {
public:
    void FUN_00992e60(uint32_t v);
    void FUN_00992ea0(uint32_t v);
    void FUN_00995b20(XDomElement* fc, const uint16_t* value);
    void FUN_00995ea0(XDomElement* fc, void* out);
    bool FUN_009960b0(float x, float y, uint32_t button, uint32_t flags);
};

// Define them after cXHTMLFrameSet so the member pointer type is known; they are
// declared here as exported symbols only.

#define VF(p, i) (*(void**)((char*)(*(void**)(p)) + (i) * 4))

// @ 0x00996410
bool __thiscall cXHTMLFrameSet::FUN_00996410(void* a, void* b) {
    if (*(int*)((char*)b + 8) == 0x51a1a2d && a != 0) {
        void* obj = ((void*(__thiscall*)(void*, int))VF(a, 0xc / 4))(a, 0x4d044f3);
        if (obj != 0) {
            ((WinXHTML_*)obj)->FUN_00992e60(mField54);
            ((WinXHTML_*)obj)->FUN_00992ea0(mField58);
        }
    }
    return false;
}

// ===========================================================================
// JobQueue — eastl::deque<JobEntry, allocator, 16> inline operations
// JobEntry is a 12-byte {u32,u32,u32} record.
// ===========================================================================

// @ 0x009968f0 — eastl::deque<JobEntry,...>::push_back(const JobEntry&)
void __thiscall JobQueue::FUN_009968f0(void* e) {
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

// @ 0x009966b0 — eastl::deque<JobEntry,...>::deque(n) (initial block allocation)
template <class T> inline const T& eastl_max(const T& a, const T& b) { return a > b ? a : b; }

void __thiscall JobQueue::FUN_009966b0(uint32_t n) {
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

// ===========================================================================
// eastl::DequeIterator<JobEntry,...,16>
// ===========================================================================
struct JobIter {
    int*  mpCurrent;            // @0x00
    int*  mpBegin;              // @0x04
    int*  mpEnd;                // @0x08
    int** mpCurrentArrayPtr;    // @0x0c
    JobIter& operator+=(int n);
};

// @ 0x009964c0
JobIter& __thiscall JobIter::operator+=(int n) {
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

// ===========================================================================
// Frame map (eastl::map<unsigned, WinXHTML_*>) lookup helper for GetFrame
// ===========================================================================
extern "C" uint32_t  __cdecl FNV1_String16(const uint16_t* s, uint32_t base, int n);
extern "C" uint32_t* __cdecl FUN_00d01260(uint32_t* begin, uint32_t* end, uint32_t* key, uint8_t compare);

// @ 0x00996d40 — cXHTMLFrameSet::GetFrame(string)
uint32_t __thiscall cXHTMLFrameSet::GetFrame(const uint16_t* str) {
    uint32_t hash = FNV1_String16(str, 0x811c9dc5, 0);
    uint32_t* end = (uint32_t*)mField10;
    uint32_t key = hash;
    uint32_t* it = FUN_00d01260((uint32_t*)mField0c, end, &key, mField20);
    if (it != end && !(key < *it) && it != it + 2)
        return it[1];
    return 0;
}

// ===========================================================================
// eastl::deque<JobEntry, allocator, 16> range copy helpers (free functions)
// JobEntry element is 12 bytes; block holds 0x10 entries (0xc0 bytes).
// ===========================================================================
struct DqIt {
    uint32_t*  mpCurrent;            // @0x00
    uint32_t*  mpBegin;              // @0x04
    uint32_t*  mpEnd;                // @0x08
    uint32_t** mpCurrentArrayPtr;    // @0x0c
};

// @ 0x009962a0 — eastl::deque<JobEntry,allocator,16>::copy(first, last, result)
DqIt __cdecl FUN_009962a0(DqIt first, DqIt last, DqIt result) {
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

// @ 0x00996360 — eastl::deque<JobEntry,allocator,16>::copy_backward(first, last, result)
DqIt __cdecl FUN_00996360(DqIt first, DqIt last, DqIt result) {
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

// ===========================================================================
// eastl::vector<8-byte element> insert(iterator, const value&)
// vector layout: mpBegin @0, mpEnd @4, mpCapacity @8.
// ===========================================================================
extern "C" char* __cdecl FUN_0099efa0(const char* first, const char* last, char* out);

class Vec8 {
public:
    uint32_t* mpBegin;      // @0x00
    uint32_t* mpEnd;        // @0x04
    uint32_t* mpCapacity;   // @0x08
    void insert(uint32_t* pos, uint32_t* value);
};

// @ 0x00996bb0
void __thiscall Vec8::insert(uint32_t* pos, uint32_t* value) {
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

// ===========================================================================
// XHTML DOM element — opaque layout (only the fields this slice's DOM methods
// reach; the full Element definition lives in another TU).
// ===========================================================================
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

typedef void* (__thiscall* XDomQueryFn)(void*, uint32_t);

// @ 0x00995b20 — EA::UTFWinExtras::WinXHTML::SetFormControlValue(FormControl*, wchar_t const*)
// [PARTIAL] Guards and the Element-type dispatch are reconstructed; the per-type
// value handling (Input / Select / Textarea, the vtable calls and DOM walks) is
// not reconstructed — it needs the full DOM Element/FormControl layout.
void __thiscall WinXHTML_::FUN_00995b20(XDomElement* fc, const uint16_t* value) {
    if (fc == 0)
        return;
    void* formObj = fc->mpFormObj;
    if (formObj == 0)
        return;
    void* mgr = ((XDomQueryFn)(*(void***)formObj)[3])(formObj, 0xeeee8218);
    if (mgr == 0)
        return;
    uint32_t type = fc->mElementType;  // 23 = Input, 24 = Select, 26 = Textarea
    (void)type;
    (void)value;
    // incomplete
}

// @ 0x00995ea0 — EA::UTFWinExtras::WinXHTML::GetFormControlValue(FormControl*, eastl::basic_string<wchar_t,allocator>&)
// [PARTIAL] Guards are reconstructed; the Input (checkbox/radio) attribute read
// and the Select option resolution are not reconstructed.
void __thiscall WinXHTML_::FUN_00995ea0(XDomElement* fc, void* out) {
    if (fc == 0)
        return;
    void* formObj = fc->mpFormObj;
    if (formObj == 0)
        return;
    void* mgr = ((XDomQueryFn)(*(void***)formObj)[3])(formObj, 0xeeee8218);
    if (mgr == 0)
        return;
    (void)out;
    // incomplete
}

// @ 0x009960b0 — EA::UTFWinExtras::WinXHTML::OnMouseUp(float, float, uint32_t, uint32_t)
// [PARTIAL] Signature and ABI only; the layout/page hit-test reasoning is not
// reconstructed (needs the 0xa8c0-byte WinXHTML layout).
bool __thiscall WinXHTML_::FUN_009960b0(float x, float y, uint32_t button, uint32_t flags) {
    (void)x;
    (void)y;
    (void)button;
    (void)flags;
    // incomplete
    return false;
}

// @ 0x00996da0 — EA::UTFWinExtras::cXHTMLFrameSet::FormParamCallback(wchar_t const*, wchar_t const*, void*)
// [PARTIAL] Signature only; the URL-encoding / string-append logic is not
// reconstructed (needs the eastl string globals 0x014467d8 / 0x014467dc).
void __cdecl FUN_00996da0(const uint16_t* name, const uint16_t* value, void* params) {
    (void)name;
    (void)value;
    (void)params;
    // incomplete
}
