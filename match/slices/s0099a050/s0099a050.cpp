// Slice s0099a050 - EA::UTFWinTools / EA::StringMan XML reader helpers
// (0x99a050..0x99ac80, 11 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region, see s0096c6f0).
//
// The five large XML-reader entry points (ReadResource 0x99a050, ReadObjectArray 0x99a4c0,
// ReadStructArray 0x99a7c0, ParsePropertyValue 0x99aa20, ReadPropertyValueArray 0x99ac80)
// walk the EASTL vector/hash structures and the XmlReader cursor; only faithful fragments are
// reconstructed here (see partial.txt).  The small comparison/allocator/list helpers are
// byte-exact.

#include "types.h"
#include <wchar.h>

namespace EA {
namespace UTFWinTools {
namespace UTFWinToolsInternal {

// ---------------------------------------------------------------------------
// Shared helper types.
// ---------------------------------------------------------------------------

// EA::Allocator::StackAllocator -- only the two entry points used here.
struct StackAllocator {
    void* MallocAligned(void* a, void* b, int zero, int one);  // 0x928d40
    bool  AllocateNewBlock(int size);                          // 0x928ba0
};

// Object referenced through XmlReaderState+0x94.
struct XmlObj094 {
    virtual void pv00(); virtual void pv01(); virtual void pv02(); virtual void pv03();
    virtual void* v10(void* a);          // +0x10
    virtual void* v14(void* a);          // +0x14
    void* FUN_0113ae10(void* r);         // 0x113ae10
};

struct XmlReaderState {
    // 0x99a920
    void Allocate(void* param_2, void* param_3);
    // 0x99a940
    void* StrDup(const wchar_t* s);
    // 0x99a470
    void  ReportResult(void* param_2);
    // 0x99a9d0
    void  Splice(void* param_2);
    // large entry points (partial)
    unsigned ReadObjectArray(int param_2);                                  // 0x99a4c0
    unsigned ReadStructArray(int* param_2, unsigned param_3);               // 0x99a7c0
    unsigned ParsePropertyValue(double* param_2, unsigned param_3, wchar_t* param_4);  // 0x99aa20
    unsigned ReadPropertyValueArray(void* param_2);                         // 0x99ac80
};

} // namespace UTFWinToolsInternal
} // namespace UTFWinTools
} // namespace EA

namespace EA {
namespace StringMan {

struct FactoryStringTableXml {
    bool ReadResource(int param_2, int* param_3, unsigned param_4, int param_5);  // 0x99a050
};

} // namespace StringMan
} // namespace EA

namespace EA {
namespace UTFWinTools {
namespace UTFWinToolsInternal {

// ---------------------------------------------------------------------------
// 0x0099a920  XmlReaderState::Allocate
// ---------------------------------------------------------------------------
// @ 0x0099a920
void XmlReaderState::Allocate(void* param_2, void* param_3)
{
    ((StackAllocator*)((char*)this + 0x28))->MallocAligned(param_2, param_3, 0, 1);
}

// ---------------------------------------------------------------------------
// 0x0099a940  XmlReaderState::StrDup
// ---------------------------------------------------------------------------
// @ 0x0099a940
void* XmlReaderState::StrDup(const wchar_t* s)
{
    const wchar_t* p = s;
    const wchar_t* q = s + 1;
    while (*p++) {
    }
    int n = (int)(p - q);
    unsigned size = ((unsigned)(n * 2 + 9)) & 0xfffffff8u;

    char* base = (char*)this + 4;
    if ((int)(*(int*)((char*)this + 0x0c) - (int)size - *(int*)(base + 0x0c)) < 0) {
        if (!((StackAllocator*)base)->AllocateNewBlock((int)size))
            return 0;
    }
    char* dst = *(char**)(base + 0x0c);
    char* newEnd = dst + size;
    *(char**)(base + 0x0c) = newEnd;
    *(char**)(base + 0x10) = newEnd;

    const wchar_t* r = s;
    wchar_t* out = (wchar_t*)dst;
    wchar_t c;
    do {
        c = *r++;
        *out++ = c;
    } while (c != 0);
    return dst;
}

// ---------------------------------------------------------------------------
// 0x0099a470  XmlReaderState / XmlReader::ReportResult
// ---------------------------------------------------------------------------
// @ 0x0099a470
void XmlReaderState::ReportResult(void* param_2)
{
    *(void**)((char*)this + 0x58) = param_2;
    if (*(void**)((char*)this + 0x4c) != 0) {
        XmlObj094* p = *(XmlObj094**)((char*)this + 0x94);
        void* r = p->v14(*(void**)((char*)this + 0x50));
        r = p->v10(r);
        r = (*(XmlObj094**)((char*)this + 0x94))->FUN_0113ae10(r);
        void* f = *(void**)((char*)this + 0x4c);
        ((void(__cdecl*)(void*, void*))f)(*(void**)((char*)this + 0x58), r);
    }
}

// ---------------------------------------------------------------------------
// 0x0099a9d0  XmlReaderState / intrusive list Splice
// ---------------------------------------------------------------------------
// @ 0x0099a9d0
void XmlReaderState::Splice(void* param_2)
{
    void** a = (void**)this;
    void** b = (void**)param_2;
    void* iVar1 = a[0];
    void* iVar2 = a[1];
    a[0] = b[0];
    a[1] = b[1];
    b[1] = iVar2;
    b[0] = iVar1;
    if (a[0] == (void*)b) {
        a[1] = (void*)a;
        a[0] = (void*)a;
    } else {
        *(void**)a[1] = (void*)a;
        *(void**)((char*)a[0] + 4) = (void*)a;
    }
    if (b[0] == (void*)a) {
        b[1] = (void*)b;
        b[0] = (void*)b;
        return;
    }
    *(void**)b[1] = (void*)b;
    *(void**)((char*)b[0] + 4) = (void*)b;
}

// ---------------------------------------------------------------------------
// 0x0099a3f0  wide-string / enum kind predicate
// ---------------------------------------------------------------------------
// @ 0x0099a3f0
bool __fastcall FUN_0099a3f0(unsigned param_1, unsigned param_2)
{
    switch (param_1) {
    case 3:
    case 7:
        return param_2 == 3 || param_2 == 7;
    case 4:
    case 8:
        return param_2 == 4 || param_2 == 8;
    case 5:
    case 9:
        return param_2 == 5 || param_2 == 9;
    case 0x3fd:
    case 0x3fe:
    case 0x3ff:
        return param_2 == 0x13;
    default:
        return param_1 == param_2;
    }
}

// ---------------------------------------------------------------------------
// 0x0099a380  static name-table lookup (binary search over wide-string keys)
// ---------------------------------------------------------------------------
namespace {
struct NameEntry {
    const wchar_t* name;
    int value;
};
const NameEntry* const kNameTable = (const NameEntry*)0x15503d0;
} // namespace

// @ 0x0099a380
unsigned FUN_0099a380(const wchar_t* key)
{
    int hi = 0x16;
    int lo;
    lo = 0;
    do {
        int mid = (hi + lo) / 2;
        int c = wcscmp(key, kNameTable[mid].name);
        if (c == 0)
            return (unsigned)kNameTable[mid].value;
        if (c < 0)
            hi = mid;
        else
            lo = mid + 1;
    } while (hi > lo);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0099a4c0  XmlReaderState::ReadObjectArray  (partial)
// ---------------------------------------------------------------------------
// @ 0x0099a4c0
unsigned XmlReaderState::ReadObjectArray(int)
{
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0099a7c0  XmlReaderState::ReadStructArray  (partial)
// ---------------------------------------------------------------------------
// @ 0x0099a7c0
unsigned XmlReaderState::ReadStructArray(int*, unsigned)
{
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0099aa20  XmlReaderState::ParsePropertyValue  (partial)
// ---------------------------------------------------------------------------
// @ 0x0099aa20
unsigned XmlReaderState::ParsePropertyValue(double*, unsigned, wchar_t*)
{
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0099ac80  XmlReaderState::ReadPropertyValueArray  (partial)
// ---------------------------------------------------------------------------
// @ 0x0099ac80
unsigned XmlReaderState::ReadPropertyValueArray(void*)
{
    return 0;
}

} // namespace UTFWinToolsInternal
} // namespace UTFWinTools
} // namespace EA

// ---------------------------------------------------------------------------
// 0x0099a050  EA::StringMan::FactoryStringTableXml::ReadResource  (partial)
// ---------------------------------------------------------------------------
// @ 0x0099a050
bool EA::StringMan::FactoryStringTableXml::ReadResource(int, int*, unsigned, int)
{
    return 0;
}
