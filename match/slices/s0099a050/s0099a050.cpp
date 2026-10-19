// Slice s0099a050 - EA::UTFWinTools / EA::StringMan XML reader helpers
// (0x99a050..0x99ac80, 11 functions).
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (UTFWin region, see s0096c6f0).

#include "types.h"
#include <wchar.h>

// The original inlines the two-wchar compare loop at every site.
#pragma intrinsic(wcscmp)

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

// A resource key: three 32-bit words.
struct Key {
    uint32_t mInstance;    // +0x00
    uint32_t mType;        // +0x04
    uint32_t mGroup;       // +0x08
};

// The element description handed to the binder callbacks.
struct SerItem {
    uint32_t w[3];
};

struct IList;
struct ILoadSrc;

struct SerItem;

// IDedataBinder -- receives the parsed key/type triples.
struct IDataBinder {
    virtual void bv0();  // +0x00
    virtual void bv4();  // +0x04
    virtual void bv8();  // +0x08
    virtual void bvc();  // +0x0c
    virtual bool BindKey(SerItem* out, int typeCode, Key* key);   // +0x10
};

// EA::XML::XmlReader -- the cursor interface shared by reader implementations.
struct XmlReader {
    virtual void v00();                                    // +0x00
    virtual void v04();                                    // +0x04
    virtual void v08();                                    // +0x08
    virtual bool Next();                                   // +0x0c  0x9013e0
    virtual const void* GetPos(void* ctx);                 // +0x10
    virtual void* GetLine(const void* pos);                // +0x14
    const wchar_t* GetAttribute(const wchar_t* name);      // 0x900720
    int            GetNodeType();                          // 0x900660
    const wchar_t* GetName();                              // 0x900690
    void           EndElement();                           // 0x9007b0
    uint32_t       GetErrorCode();                         // 0xfcc210
    int            FUN_00900680();                         // 0x900680
    const wchar_t* FUN_009008f0();                         // 0x9008f0
    const wchar_t* ReadString(void* alloc, void* pOut);    // 0x900800
};

// EA::XML::XmlTextReader -- the concrete reader, used as a stack object.
struct XmlTextReader {
    char mData[0x88];
    XmlTextReader(void* alloc);                            // 0x900b30
    ~XmlTextReader();                                      // 0x900b70
    bool Next();                                           // 0x9013e0
    void Begin(void* stream, int flags);                   // 0x901440
    const wchar_t* GetAttribute(const wchar_t* name);      // 0x900720
    int            GetNodeType();                          // 0x900660
    const wchar_t* GetName();                              // 0x900690
    void           EndElement();                           // 0x9007b0
    uint32_t       GetErrorCode();                         // 0xfcc210
    const wchar_t* ReadString(void* alloc, void* pOut);    // 0x900800
};

// ILoadSrc -- what the load callback receives.
struct ILoadSrc {
    virtual void lv0(); virtual void lv1(); virtual void lv2(); virtual void lv3();
    virtual unsigned GetOffset();   // +0x10
    virtual unsigned GetBase();     // +0x14
};

// EA::Allocator::StackAlloc (the StringTableXml allocator at +0x4c).
struct StackAllocBookmark {
    void*  m00;
    char*  m04;
    void*  m08;
};

struct StackAlloc064 {
    uint32_t m00;                          // +0x00
    char*    mpEnd;                        // +0x04
    char*    mpCap;                        // +0x08
    char*    mpBegin;                      // +0x0c
    char*    mpCur;                        // +0x10
    char     pad14[0x0c];                  // +0x14
    StackAllocBookmark* mpCurrentBlock;    // +0x20
    void FUN_0082aa70();                                        // 0x82aa70
    void FUN_0082aa50(int param_2);                             // 0x82aa50
    void AllocateNewBlock(StackAllocBookmark* b);               // 0x82b0d0
    void Reset(void* p);                                        // 0x928c40
};

// EASTL vector of pointers (StringTableXml::mStrings at +0x38).
struct StrVec064 {
    void** mpBegin;    // +0x00
    void** mpEnd;      // +0x04
    void** mpCap;      // +0x08
    char   pad0c[8];   // +0x0c
    void resize(unsigned n);   // 0x999fb0
};

// EA::StringMan::StringTableXml (only the members read here).
struct StringTableXml064 {
    char       pad00[0x08];
    Key        mKey;               // +0x08
    char       pad14[0x08];
    wchar_t*   mpTableName;        // +0x1c
    char       pad20[0x18];
    StrVec064  mStrings;           // +0x38
    StackAlloc064 mAllocator;      // +0x4c
    wchar_t* StrDup(const wchar_t* s);   // 0x999b20
};

struct BinderVec {
    IDataBinder** mpBegin;   // +0x00
    IDataBinder** mpEnd;     // +0x04
    IDataBinder** mpCap;     // +0x08
};

// EA::UTFWinTools::UTFWinToolsInternal::XmlReaderState
struct XmlReaderState {
    // 0x99a920
    void Allocate(void* param_2, void* param_3);
    // 0x99a940
    void* StrDup(const wchar_t* s);
    // 0x99a470
    void  ReportResult(void* param_2);
    // 0x99a9d0
    void  Splice(void* param_2);

    bool ReadObjectArray(int param_2);                                  // 0x99a4c0
    bool ReadStructArray(int* param_2, unsigned param_3);               // 0x99a7c0
    bool ParsePropertyValue(double* param_2, unsigned param_3, wchar_t* param_4);  // 0x99aa20
    bool ReadPropertyValueArray(void* param_2);                         // 0x99ac80

    // 0x99b730  ReadPropertyList(SerItem*, IList*)
    bool ReadPropertyList(SerItem* param_2, IList* param_3);
    // 0x99b8a0  ReadObject(unsigned*)
    void* ReadObject(unsigned* param_2);

    // The reader cursor pointer lives at +0x94.
    XmlReader* Reader() { return *(XmlReader**)((char*)this + 0x94); }
};

} // namespace UTFWinToolsInternal
} // namespace UTFWinTools
} // namespace EA

namespace EA {
namespace StringMan {

struct FactoryStringTableXml_s0099_a050 {
    char     pad00[0x08];
    void*    mpCallback;      // +0x08
    uint32_t mArg;            // +0x0c
    bool ReadResource(int param_2, int* param_3, unsigned param_4, int param_5);  // 0x99a050
    // 0x999bc0  LoadCallbackHolder::Invoke
    void Invoke(EA::UTFWinTools::UTFWinToolsInternal::ILoadSrc* src, unsigned extra);
};

} // namespace StringMan
} // namespace EA

namespace EA {
namespace ResourceMan {
// 0x8de0c0  EA::ResourceMan::ReadKey(const wchar_t*, Key&)
bool ReadKey(const wchar_t* name, EA::UTFWinTools::UTFWinToolsInternal::Key& key);
} // namespace ResourceMan
} // namespace EA

namespace EA {
namespace UTFWinTools {
namespace UTFWinToolsInternal {

// 0x11e0744  eastl::vector<...>::DoInsertValue
extern "C" void* __cdecl InsertValue_011e0744(void* dst, void* end, unsigned value);

// 0x99a380  name-table lookup (binary search over the sorted wide-string name table)
unsigned FUN_0099a380(const wchar_t* key);

// 0x99a3f0  type-kind predicate
bool __fastcall FUN_0099a3f0(unsigned param_1, unsigned param_2);

// msvcr90 helpers.  These are real imports of the analysis image (no VA annotation:
// resolve maps them through the import table / symbol database).
extern "C" int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
extern "C" long          __cdecl wcstol(const wchar_t*, wchar_t**, int);
extern "C" double        __cdecl wcstod(const wchar_t*, wchar_t**);
extern "C" int           __cdecl swscanf(const wchar_t*, const wchar_t*, ...);
// 0x92d6d0 / 0x92d710  in-image 64-bit string converters.
extern "C" __int64       __cdecl StrtoI6416(const wchar_t*, wchar_t**, int);
extern "C" unsigned __int64 __cdecl StrtoU6416(const wchar_t*, wchar_t**, int);
} // namespace UTFWinToolsInternal
} // namespace UTFWinTools
} // namespace EA

namespace EA {
namespace UTFWinTools {
namespace UTFWinToolsInternal {

// ---------------------------------------------------------------------------
// 0x0099a470  XmlReaderState / ReportResult
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
// 0x0099a920  XmlReaderState / Allocate
// ---------------------------------------------------------------------------
// @ 0x0099a920
void XmlReaderState::Allocate(void* param_2, void* param_3)
{
    ((StackAllocator*)((char*)this + 0x28))->MallocAligned(param_2, param_3, 0, 1);
}

// ---------------------------------------------------------------------------
// 0x0099a940  XmlReaderState / StrDup
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
// 0x0099a3f0  type-kind predicate
//
// Native ABI: the two operands arrive in ECX and EAX.  The closest C++
// spelling is the 2-operand __fastcall form (ECX/EDX); the second operand
// therefore lands in EDX instead of EAX.  Written for semantics, not bytes.
// ---------------------------------------------------------------------------
// @ 0x0099a3f0
bool __fastcall FUN_0099a3f0(unsigned param_1, unsigned param_2)
{
    if (param_1 > 0x3ff)
        return param_1 == param_2;
    if (param_1 >= 0x3fd)
        return param_2 == 0x13;
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
    default:
        return param_1 == param_2;
    }
}

} // namespace UTFWinToolsInternal
} // namespace UTFWinTools
} // namespace EA

namespace EA {
namespace UTFWinTools {
namespace UTFWinToolsInternal {

// ---------------------------------------------------------------------------
// 0x0099a7c0  XmlReaderState::ReadStructArray
// ---------------------------------------------------------------------------
// @ 0x0099a7c0
bool XmlReaderState::ReadStructArray(int* param_2, unsigned param_3)
{
    unsigned n        = 0;
    int      stride   = param_2[1];
    int      elemSize = *(int*)(param_2[0] + 8);
    if (!Reader()->Next())
        goto failTail;
    while (true) {
        if (Reader()->GetNodeType() == 1) {
            if (wcscmp(Reader()->GetName(), L"struct") != 0) {
                ReportResult((void*)0x2fc50001);
                return 0;
            }
            if (n >= (unsigned)param_2[2]) {
                ReportResult((void*)0x2fc50007);
                return 0;
            }
            SerItem item;
            item.w[1] = (uint32_t)stride;
            item.w[0] = (uint32_t)param_2[0];
            item.w[2] = 1;
            if (!ReadPropertyList(&item, (IList*)param_3))
                return 0;
            stride += elemSize;
            ++n;
        } else if (Reader()->GetNodeType() == 2) {
            if (n == (unsigned)param_2[2])
                return 1;
            ReportResult((void*)0x2fc50007);
            return 0;
        }
        if (!Reader()->Next())
            break;
    }
failTail:
    ReportResult((void*)Reader()->GetErrorCode());
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0099aa20  XmlReaderState::ParsePropertyValue
// ---------------------------------------------------------------------------
// @ 0x0099aa20
bool XmlReaderState::ParsePropertyValue(double* param_2, unsigned param_3, wchar_t* param_4)
{
    switch (param_3) {
    case 2:
        *(bool*)param_2 = (_wcsicmp(param_4, L"true") == 0);
        return 1;
    case 3:
        *(char*)param_2 = (char)wcstol(param_4, 0, 0);
        return 1;
    case 4:
        *(short*)param_2 = (short)wcstol(param_4, 0, 0);
        return 1;
    case 5:
        *(uint32_t*)param_2 = (uint32_t)wcstol(param_4, 0, 0);
        return 1;
    case 6:
        *(long long*)param_2 = (long long)StrtoI6416(param_4, 0, 0);
        return 1;
    case 7:
        *(char*)param_2 = (char)wcstoul(param_4, 0, 0);
        return 1;
    case 8:
        *(short*)param_2 = (short)wcstoul(param_4, 0, 0);
        return 1;
    case 9:
        *(uint32_t*)param_2 = (uint32_t)wcstoul(param_4, 0, 0);
        return 1;
    case 10:
        *(unsigned long long*)param_2 = (unsigned long long)StrtoU6416(param_4, 0, 0);
        return 1;
    case 11:
        *(float*)param_2 = (float)wcstod(param_4, 0);
        return 1;
    case 12:
        *param_2 = wcstod(param_4, 0);
        return 1;
    case 13:
    case 18:
        *(void**)param_2 = StrDup(param_4);
        return 1;
    case 14: {
        int n = swscanf(param_4, L"%d,%d,%d,%d", (char*)param_2, (char*)param_2 + 4,
                            (char*)param_2 + 8, (char*)param_2 + 12);
        if (n != 4) {
            *(void**)((char*)this + 0x58) = (void*)0x2fc50006;
            return 0;
        }
        return 1;
    }
    case 15: {
        int n = swscanf(param_4, L"%d,%d", (char*)param_2, (char*)param_2 + 4);
        if (n != 2) {
            *(void**)((char*)this + 0x58) = (void*)0x2fc50006;
            return 0;
        }
        return 1;
    }
    case 16: {
        int n = swscanf(param_4, L"%g,%g,%g,%g", (char*)param_2, (char*)param_2 + 4,
                            (char*)param_2 + 8, (char*)param_2 + 12);
        if (n != 4) {
            *(void**)((char*)this + 0x58) = (void*)0x2fc50006;
            return 0;
        }
        return 1;
    }
    case 17: {
        int n = swscanf(param_4, L"%g,%g", (char*)param_2, (char*)param_2 + 4);
        if (n != 2) {
            *(void**)((char*)this + 0x58) = (void*)0x2fc50006;
            return 0;
        }
        return 1;
    }
    case 19:
    case 20:
        *(void**)((char*)this + 0x58) = (void*)0x2fc50006;
        return 0;
    default:
        return 0;
    }
}

// ---------------------------------------------------------------------------
// 0x0099a4c0  XmlReaderState::ReadObjectArray
// ---------------------------------------------------------------------------
// @ 0x0099a4c0
bool XmlReaderState::ReadObjectArray(int param_2)
{
    unsigned* const ids = *(unsigned**)((char*)(uintptr_t)param_2 + 0x2c);
    const unsigned  count = *(unsigned*)((char*)(uintptr_t)param_2 + 0x30);
    XmlReader* r = *(XmlReader**)((char*)this + 0x94);

    const wchar_t* valAttr = r->GetAttribute(L"value");
    if (count == 1 && valAttr != 0) {
        if (wcscmp(valAttr, L"null") == 0)
            return 1;
        unsigned v = wcstoul(valAttr, 0, 0);
        if (v != 0)
            *ids = v;
        return 1;
    }

    unsigned n = 0;
    if (!r->Next())
        goto failTail;
    for (;;) {
        r = *(XmlReader**)((char*)this + 0x94);
        if (r->GetNodeType() == 1) {
            if (wcscmp(r->GetName(), L"value") != 0)
                goto objectPath;

            const wchar_t* typeAttr = r->GetAttribute(L"type");
            const wchar_t* va       = r->GetAttribute(L"value");
            const wchar_t* keyAttr  = r->GetAttribute(L"key");

            if (n >= count) {
                ReportResult((void*)0x2fc50007);
                return 0;
            }
            if (wcscmp(typeAttr, L"object") != 0) {
                ReportResult((void*)0x2fc50005);
                return 0;
            }
            if (keyAttr != 0) {
                ids[n] = 0;
                r->EndElement();
                ++n;
            } else {
                if (va == 0) {
                    va = r->FUN_009008f0();
                    if (va == 0) {
                        ReportResult((void*)0x2fc50006);
                        return 0;
                    }
                }
                unsigned v = wcstoul(va, 0, 0);
                if (v != 0)
                    ids[n] = v;
                r->EndElement();
                ++n;
            }
        } else {
            if (r->GetNodeType() == 2) {
                if (n == count)
                    return 1;
                ReportResult((void*)0x2fc50007);
                return 0;
            }
        }
    next:
        r = *(XmlReader**)((char*)this + 0x94);
        if (!r->Next())
            break;
        continue;

    objectPath:
        if (wcscmp(r->GetName(), L"object") != 0) {
            ReportResult((void*)0x2fc50001);
            return 0;
        }
        {
            unsigned localId = 0;
            if (ReadObject(&localId) == 0)
                return 0;
            if (localId != 0)
                ids[n] = localId;
            ++n;
        }
        goto next;
    }

failTail:
    ReportResult((void*)(*(XmlReader**)((char*)this + 0x94))->GetErrorCode());
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0099ac80  XmlReaderState::ReadPropertyValueArray
// ---------------------------------------------------------------------------
// @ 0x0099ac80
bool XmlReaderState::ReadPropertyValueArray(void* param_2)
{
    uint32_t* const p    = (uint32_t*)param_2;
    const unsigned short typeCode = *(unsigned short*)(uintptr_t)p[0];
    const int  elemSize  = *(int*)((char*)(uintptr_t)p[0] + 8);
    const unsigned count = p[2];

    SerItem item;
    item.w[0] = p[0];
    item.w[1] = p[1];
    item.w[2] = 1;

    XmlReader* r = *(XmlReader**)((char*)this + 0x94);
    unsigned idx = 0;
    int iVar6 = r->FUN_00900680();
    if (!r->Next())
        goto failTail;

    for (;;) {
        r = *(XmlReader**)((char*)this + 0x94);
        if (r->GetNodeType() == 1) {
            if (wcscmp(r->GetName(), L"value") != 0) {
                *(void**)((char*)this + 0x58) = (void*)0x2fc50001;
                goto reportTail;
            }
            const wchar_t* va      = r->GetAttribute(L"value");
            const wchar_t* typeAttr = r->GetAttribute(L"type");
            const wchar_t* keyAttr = r->GetAttribute(L"key");

            if (idx >= count) {
                *(void**)((char*)this + 0x58) = (void*)0x2fc50007;
                goto reportTail;
            }
            unsigned t = 0;
            if (typeAttr != 0) {
                t = FUN_0099a380(typeAttr);
                if (t == 0) {
                    ReportResult((void*)0x2fc50004);
                    return 0;
                }
                if (!FUN_0099a3f0(t, typeCode)) {
                    ReportResult((void*)0x2fc50005);
                    r->EndElement();
                    return 1;
                }
            }
            if (keyAttr != 0) {
                Key key;
                key.mInstance = 0;
                key.mType = 0;
                key.mGroup = 0;
                if (EA::ResourceMan::ReadKey(keyAttr, key)) {
                    BinderVec* b = *(BinderVec**)((char*)this + 0x88);
                    IDataBinder** it = b->mpBegin;
                    if (it != b->mpEnd) {
                        for (;;) {
                            if ((*it)->BindKey(&item, (int)t, &key))
                                goto advance;
                            ReportResult((void*)0x2fc50009);
                            ++it;
                            if (it == (*(BinderVec**)((char*)this + 0x88))->mpEnd)
                                break;
                        }
                    }
                }
            } else {
                const wchar_t* s = va;
                if (s == 0) {
                    s = r->FUN_009008f0();
                    if (s == 0)
                        s = L"";
                }
                if (!ParsePropertyValue((double*)(uintptr_t)item.w[1], typeCode, (wchar_t*)s)) {
                    ReportResult(*(void**)((char*)this + 0x58));
                    r->EndElement();
                    return 1;
                }
            }
        advance:
            item.w[1] += (uint32_t)elemSize;
            ++idx;
        } else if (r->GetNodeType() == 2) {
            if (r->FUN_00900680() == iVar6) {
                if (idx == count)
                    return 1;
                ReportResult((void*)0x2fc50007);
                return 0;
            }
        }

        r = *(XmlReader**)((char*)this + 0x94);
        if (!r->Next())
            break;
    }

failTail:
    *(void**)((char*)this + 0x58) =
        (void*)(*(XmlReader**)((char*)this + 0x94))->GetErrorCode();
reportTail:
    ReportResult(*(void**)((char*)this + 0x58));
    return 0;
}

} // namespace UTFWinToolsInternal
} // namespace UTFWinTools
} // namespace EA

// ---------------------------------------------------------------------------
// 0x0099a050  EA::StringMan::FactoryStringTableXml_s0099_a050::ReadResource
// ---------------------------------------------------------------------------
// @ 0x0099a050
bool EA::StringMan::FactoryStringTableXml_s0099_a050::ReadResource(
        int param_2, int* param_3, unsigned param_4, int param_5)
{
    (void)param_4;
    using namespace EA::UTFWinTools::UTFWinToolsInternal;

    if (param_5 != -1 && param_5 != (int)0xcf6c21b8)
        return false;
    if (param_3 == 0)
        return false;

    StringTableXml064* st = (StringTableXml064*)
        (*(void*(__thiscall**)(void*, unsigned))(*param_3 + 0x0c))(
            (void*)param_3, 0xcf6c2b18u);
    if (st == 0)
        return false;

    void** vt = *(void***)(uintptr_t)param_2;
    unsigned* pk = (unsigned*)((void*(__thiscall*)(void*))vt[4])((void*)(uintptr_t)param_2);
    st->mKey.mInstance = pk[0];
    st->mKey.mType     = pk[1];
    st->mKey.mGroup    = pk[2];

    void* stream = ((void*(__thiscall*)(void*))vt[6])((void*)(uintptr_t)param_2);

    XmlTextReader reader((void*)0);
    reader.Begin(stream, 0);

    // Release the allocator's current block back to the stack allocator.
    StackAllocBookmark* blk = *(StackAllocBookmark**)((char*)st + 0x6c);
    if (blk != 0) {
        int   pc = (int)(uintptr_t)blk->m04;
        void* pd = blk->m00;
        void* pe = blk->m08;
        *(void**)((char*)st + 0x6c) = pd;
        if (pc > *(int*)((char*)st + 0x50) && pc < *(int*)((char*)st + 0x54)) {
            *(int*)((char*)st + 0x58) = pc;
            *(int*)((char*)st + 0x5c) = pc;
        } else {
            st->mAllocator.Reset((void*)pc);
        }
        *(void**)((char*)st + 0x5c) = pe;
    }
    st->mAllocator.AllocateNewBlock((StackAllocBookmark*)0);

    StrVec064* strings = (StrVec064*)((char*)st + 0x38);
    void**      _Dst   = strings->mpBegin;
    void**      _End   = strings->mpEnd;
    InsertValue_011e0744(_Dst, _End, 0);
    *(void***)((char*)st + 0x3c) =
        (void**)((char*)_End + (-(((int)((char*)_End - (char*)_Dst)) >> 2) * 4));

    if (!reader.Next()) {
        Invoke((EA::UTFWinTools::UTFWinToolsInternal::ILoadSrc*)&reader,
               reader.GetErrorCode());
        return false;
    }
    while (reader.GetNodeType() != 1)
        ;
    if (wcscmp(reader.GetName(), L"StringTable") != 0)
        return false;

    const wchar_t* nameAttr = reader.GetAttribute(L"name");
    if (nameAttr != 0) {
        st->mAllocator.FUN_0082aa70();
        st->mAllocator.FUN_0082aa50(0);
        st->mpTableName = st->StrDup(nameAttr);
        st->mAllocator.AllocateNewBlock((StackAllocBookmark*)0);
    }

    unsigned idx = 0;
    if (!reader.Next()) {
        Invoke((EA::UTFWinTools::UTFWinToolsInternal::ILoadSrc*)&reader,
               reader.GetErrorCode());
        return false;
    }
    for (;;) {
        if (reader.GetNodeType() == 1) {
            if (wcscmp(reader.GetName(), L"String") != 0) {
                Invoke((EA::UTFWinTools::UTFWinToolsInternal::ILoadSrc*)&reader, 0x4002);
                return false;
            }
            const wchar_t* idxAttr = reader.GetAttribute(L"index");
            if (idxAttr != 0)
                idx = (unsigned)wcstoul(idxAttr, 0, 0);
            unsigned len = (unsigned)(((char*)strings->mpEnd - (char*)strings->mpBegin) >> 2);
            if (idx + 1 > len)
                strings->resize(idx + 1);
            void* local = 0;
            const wchar_t* s = reader.ReadString((void*)((char*)st + 0x4c), &local);
            if (strings->mpBegin[idx] != 0) {
                Invoke((EA::UTFWinTools::UTFWinToolsInternal::ILoadSrc*)&reader, 0x4003);
                return false;
            }
            strings->mpBegin[idx] = (void*)s;
            if (reader.GetNodeType() != 2) {
                do {
                    reader.EndElement();
                } while (reader.GetNodeType() != 2);
            }
            if (!reader.Next()) {
                Invoke((EA::UTFWinTools::UTFWinToolsInternal::ILoadSrc*)&reader,
                       reader.GetErrorCode());
                return false;
            }
        } else {
            if (reader.GetNodeType() == 2)
                return true;
            if (!reader.Next()) {
                Invoke((EA::UTFWinTools::UTFWinToolsInternal::ILoadSrc*)&reader,
                       reader.GetErrorCode());
                return false;
            }
        }
    }
}
