#include "types.h"
#include <wchar.h>
#include <new>

#define VFN(o,off) (*(void***)(o))[(off)/4]

extern "C" void FUN_0067e070(int x);   // 0x67e070
extern "C" void FUN_00883780();        // 0x883780
extern "C" void* GetManager();         // 0x67dcd0

// @ 0x00695c30
extern "C" bool __fastcall FUN_00695c30(void* self)
{
    if (*(char*)((char*)self + 8) != 0)
    {
        void* p = *(void**)((char*)self + 0x4c);
        if (p != 0)
            ((void(__thiscall*)(void*, int))VFN(p, 0))(p, 1);
        *(void**)((char*)self + 0x4c) = 0;
        FUN_0067e070(0);
        FUN_00883780();
    }
    *(char*)((char*)self + 8) = 0;
    return true;
}

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

struct Ctl {
    char pad0[4];
    void* head;      // +4
    bool check(void* arg);
    void addThing(void* a, void* b);
};

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

// =====================================================================
// @ 0x00695450  run a (partial) sort over a 0x3c-record array
// =====================================================================
struct Elem { unsigned int m0; unsigned int mId; unsigned int m2[13]; };
extern "C" void operator_delete_arr(void* p);                       // 0xf47380
extern "C" void FUN_006950b0(Elem* first, Elem* last, bool cmp);   // 0x6950b0

struct Sorter {
    void* run(char* first);
};

void* Sorter::run(char* first)
{
    char* p = first;
    char* old;
    do
    {
        old = p;
        p += 0x3c;
        if (*(int*)(old + 0x24) == 0) break;
    } while (*(int*)(old + 0x28) != 0);
    bool flag = false;
    FUN_006950b0((Elem*)first, (Elem*)p, flag);
    return this;
}

// =====================================================================
// @ 0x00695490  reserve (vector of 0x60-byte objects)
// =====================================================================
extern "C" void* EASTL_alloc6(unsigned sz, const char* name, int a, int b, const char* file, int line); // 0xf473a0
extern "C" void  FUN_00694320(char* first, char* last, char* dst);   // 0x694320
extern "C" char* FUN_00694e00(char* first, char* last, char* out);  // 0x694e00

struct Vec60 {
    char* begin; char* end; char* cap;
    void reserve(unsigned int n);
};

void Vec60::reserve(unsigned int n)
{
    if ((unsigned)((end - begin) / 0x60) < n)
    {
        char* p;
        if (n == 0)
            p = 0;
        else
            p = (char*)EASTL_alloc6(n * 0x60, "App", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        char* oldbegin = begin;
        char* oldend = end;
        FUN_00694320(oldbegin, oldend, p);
        FUN_00694e00(oldbegin, oldend, p);
        if (oldbegin != 0 && *(int*)(oldbegin - 4) != 0)
            operator_delete_arr(oldbegin);
        begin = p;
        end = ((end - oldbegin) / 0x60) * 0x60 + p;
        cap = n * 0x60 + p;
    }
}

// =====================================================================
// @ 0x00695e00  allocate and construct a 0xc node (EH)
// =====================================================================
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

// =====================================================================
// @ 0x00695e80  destroy a content-validation summarizer object
// =====================================================================
extern "C" void* g_vtbl_a[];
extern "C" void* g_vtbl_b[];

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

// =====================================================================
// @ 0x00695f00  destroy the object's intrusive list + reset
// =====================================================================
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

// =====================================================================
// destroy all pooled sub-vectors (see FUN_00695fa0 below)
// =====================================================================
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

// =====================================================================
// Serializer / text-report bodies (EH heavy, /O2 /GS-).
extern char gEmptyString[];                     // @ 0x1667bac
typedef unsigned int size_t;
// =====================================================================
namespace eastl {
inline size_t CharStrlen(const char* p)
{
    const char* pCurrent = p;
    while (*pCurrent++) {}
    return (size_t)(pCurrent - p - 1);
}
struct allocator {
    void deallocate(void* p, size_t) { delete[] (char*)p; }
};
struct basic_string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;
    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
    ~basic_string() { DeallocateSelf(); }
    void AllocateSelf() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(char* p, size_t n) { if (p) mAllocator.deallocate(p, n); }
    basic_string& assign(const char* pBegin, const char* pEnd);          // @ 0x454cb0
    basic_string& assign(const char* p)
    {
        return assign(p, p + CharStrlen(p));
    }
};
}

namespace SP {
struct cDataSerializerGeneric {
    const char* mpStaticFieldName;      // +0x00
    unsigned int mId;                   // +0x04
    unsigned int mData[4];              // +0x08
    void* mpBinderContext;              // +0x18
    void* mpSetDefaultValueFunc;        // +0x1c
    void* (*mpDataBinderFunc)(cDataSerializerGeneric*);   // +0x20
    void* mpReadFunc;                   // +0x24
    void* mpWriteFunc;                  // +0x28
    void* mpReadStringFunc;             // +0x2c
    void (*mpWriteStringFunc)(eastl::basic_string*, void*);   // +0x30
    void (*mpWriteWideFunc)(void*, void*);   // +0x34
    void* mpPad38;                      // +0x38
};
struct cDataSerializationInfo {
    unsigned int mId;                   // +0x0
    unsigned int mDataSize;             // +0x4
    bool mbSerialized;                  // +0x8
    void* mpBinderContext;              // +0xc
    cDataSerializerGeneric* mpSerializer;   // +0x10
};
}

void* DefaultDataBinder(SP::cDataSerializerGeneric*);   // 0x011874d0
struct FieldEntryBase : SP::cDataSerializerGeneric {
    FieldEntryBase()
    {
        mpStaticFieldName = "field_name";
        mId = 0xffffffff;
        mData[0] = 0;
        mpBinderContext = 0;
        mpSetDefaultValueFunc = 0;
        mpDataBinderFunc = (void* (*)(SP::cDataSerializerGeneric*))DefaultDataBinder;
        mpReadFunc = 0; mpWriteFunc = 0; mpReadStringFunc = 0; mpWriteStringFunc = 0;
        mpWriteWideFunc = 0; mpPad38 = 0;
    }
};
struct FieldEntry : FieldEntryBase {
    void* mpObject;                     // +0x3c
    eastl::basic_string mName;          // +0x40
    eastl::basic_string mValue;         // +0x50
};

struct FieldVec {
    FieldEntry* mpBegin; FieldEntry* mpEnd; FieldEntry* mpCapacity;
    void reserve(unsigned n);                       // 0x00695490 (thiscall)
    void push_back(const FieldEntry& e);            // 0x006956f0 (thiscall, ret 4)
};
extern "C" char g_bTextFlag;                        // 0x01600c5c

struct WStrTmp {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; eastl::allocator mAllocator;
    WStrTmp() {}
    ~WStrTmp()
    {
        if ((int)(((unsigned)((char*)mpCapacity - (char*)mpBegin)) & 0xfffffffeu) > 2 && mpBegin)
            mAllocator.deallocate(mpBegin, 0);
    }
};
struct CharString : eastl::basic_string {
    CharString& sprintf(const char* fmt, ...);      // 0x00472fe0 (cdecl, this pushed)
};
WStrTmp ConvertToString16(const eastl::basic_string& s);       // 0x0093c6d0 (cdecl, sret first)
struct WStrTmpVec { void push_back(const WStrTmp& s); };          // 0x00553f10 (thiscall, ret 4)
struct SubA { void Reserve(int n); };                       // 0x006b58c0 (thiscall, ret 4)
struct SubB { void Reserve(int n); };                       // 0x006953b0 (thiscall, ret 4)

struct FieldReport {
    char pad0[4];
    SubA mFields;                       // +0x04
    char pad1[0x5c - 0x04 - 1];
    SubB mTexts;                        // +0x5c
};

namespace SP {
struct cVarListSerializer {
    cDataSerializationInfo mDataSerializationInfos[128];   // +0x0
    int mSerializableVarCount;                              // +0xa00
    int mSerializedVarCount;                                // +0xa04
    unsigned int mSignature;                                // +0xa08
    void* mpObject;                                         // +0xa0c
    cDataSerializerGeneric* mpSerializerList;               // +0xa10
    cVarListSerializer(void* object, cDataSerializerGeneric* serializerList, unsigned int signature);   // 0x00692880 (thiscall, ret 0xc)
    int GetFields(FieldVec& out);
    int Execute(FieldReport* report);
};
}

void* DefaultDataBinder(SP::cDataSerializerGeneric*);   // 0x011874d0

struct Obj60 {
    char d[0x60];
    Obj60(const Obj60& o);                                          // 0x006940d0 (thiscall, ret 4)
    Obj60& operator=(const Obj60& o);                               // 0x006941c0 (thiscall, ret 4)
};
Obj60* UninitCopy60(Obj60* first, Obj60* last, Obj60* dst);         // 0x00694320 (cdecl)
Obj60* UninitFill60(Obj60* first, Obj60* last, Obj60* dst);         // 0x00694e00 (cdecl)
void   CopyBackward60(Obj60* first, Obj60* last, Obj60* dstEnd);    // 0x006943b0 (cdecl)

struct Vec60b {
    Obj60* mpBegin; Obj60* mpEnd; Obj60* mpCapacity;
    Obj60* DoAllocate(unsigned n)
    {
        return n ? (Obj60*)EASTL_alloc6(n * 0x60, "App", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    }
    void DoInsertValue(Obj60* position, const Obj60& value);
};


void* EASTL_alloc(size_t sz, const char* name, int a, int b, const char* file, int line);  // 0xf473a0

struct WStr {                                       // eastl::basic_string<wchar_t> (16 bytes)
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; eastl::allocator mAllocator;
    WStr() { mpBegin = (wchar_t*)gEmptyString; mpEnd = mpBegin; mpCapacity = (wchar_t*)(gEmptyString + 2); }
    ~WStr()
    {
        if ((int)(((unsigned)((char*)mpCapacity - (char*)mpBegin)) & 0xfffffffeu) > 2 && mpBegin)
            mAllocator.deallocate(mpBegin, 0);
    }
    WStr& sprintf(const wchar_t* fmt, ...);         // 0x0041e050 (cdecl, this pushed)
    WStr& assign(const wchar_t* b, const wchar_t* e);   // 0x00423650 (thiscall, ret 8)
    WStr& operator=(const WStr& x)
    {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
};
struct cWString {                                   // RangeInitialize-constructed copy
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity;
    cWString(const wchar_t* s) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(s); }
    ~cWString()
    {
        if ((int)(((unsigned)((char*)mpCapacity - (char*)mpBegin)) & 0xfffffffeu) > 2 && mpBegin)
            delete[] (char*)mpBegin;
    }
    void RangeInitialize(const wchar_t* s);         // 0x00579a90 (thiscall, ret 4)
};
WStr WStrConcat(const cWString& a, const WStr& b);   // 0x00688f00 (cdecl, sret first)

struct Node;
struct NodePtrVec {                                 // eastl::vector<T*>
    Node** mpBegin; Node** mpEnd; Node** mpCapacity;
    void DoInsertValue(Node** pos, Node*& value);    // 0x00690b80 (thiscall, ret 8)
    void push_back(Node* const& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Node*(value);
        else
            DoInsertValue(mpEnd, (Node*&)value);
    }
};
struct Parent;
struct ParentPtrVec {
    Parent** mpBegin; Parent** mpEnd; Parent** mpCapacity;
    void DoInsertValue(Parent** pos, Parent*& value);    // 0x00690b80 (thiscall, ret 8)
    void push_back(Parent* const& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) Parent*(value);
        else
            DoInsertValue(mpEnd, (Parent*&)value);
    }
};

struct Node {                                       // 0x74 bytes
    char pad0[0x18];
    ParentPtrVec mParents;                          // +0x18
    char pad1[0x2c - 0x24];
    WStr mName;                                     // +0x2c
    WStr mOpenTag;                                  // +0x3c
    WStr mCloseTag;                                 // +0x4c
    char pad2[0x74 - 0x5c];
    Node* init(unsigned key);                       // 0x00694e60 (thiscall, ret 4)
};

struct Parent {
    char pad0[4];
    NodePtrVec mChildren;                           // +0x04
    Node* GetOrCreate(unsigned key, const wchar_t* name);
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};

struct HashIter {
    void* mpNode; void** mpBucket;
    bool operator==(const HashIter& x) const { return mpNode == x.mpNode; }
};
struct HashPair { unsigned first; Node* second; };
struct HashResult { HashIter mIter; bool mbInserted; };
struct NodeTable {
    void* pad0;
    void** mpBucketArray;                           // +4
    unsigned mnBucketCount;                         // +8
    HashIter end() const { HashIter i; i.mpNode = mpBucketArray[mnBucketCount]; i.mpBucket = mpBucketArray + mnBucketCount; return i; }
    HashIter find(const unsigned& key) const;       // 0x00645ed0 (thiscall, ret 8)
    HashResult insert(const HashPair& value, bool b);   // 0x007c3990 (thiscall, ret 0xc)
};
extern NodeTable gNodeTable;                        // 0x0152d69c


// @ 0x00695550
void Vec60b::DoInsertValue(Obj60* position, const Obj60& value)
{
    if (mpEnd != mpCapacity) {
        const Obj60* pValue = &value;
        if ((&value >= position) && (&value < mpEnd))
            ++pValue;
        ::new(mpEnd) Obj60(*(mpEnd - 1));
        CopyBackward60(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? 2 * nPrevSize : 1;
        Obj60* const pNewData = DoAllocate(nNewSize);
        Obj60* pNewPosition = UninitCopy60(mpBegin, position, pNewData);
        UninitFill60(mpBegin, position, pNewData);
        ::new(pNewPosition) Obj60(value);
        Obj60* pNewEnd = UninitCopy60(position, mpEnd, pNewPosition + 1);
        UninitFill60(position, mpEnd, pNewPosition + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete_arr(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00695960
int SP::cVarListSerializer::GetFields(FieldVec& out)
{
    out.reserve(mSerializableVarCount);
    for (int i = 0; i < mSerializableVarCount; ++i) {
        cDataSerializationInfo& info = mDataSerializationInfos[i];
        cDataSerializerGeneric* ser = info.mpSerializer;
        if (ser->mpBinderContext == 0)
            ser->mpBinderContext = mpObject;
        FieldEntry entry;
        entry.mName.assign(ser->mpStaticFieldName);
        entry.mpObject = mpObject;
        *static_cast<cDataSerializerGeneric*>(&entry) = *ser;
        if (ser->mpWriteStringFunc && ser->mpDataBinderFunc)
            ser->mpWriteStringFunc(&entry.mValue, ser->mpDataBinderFunc(ser));
        ser->mpBinderContext = info.mpBinderContext;
        out.push_back(entry);
    }
    return mSerializableVarCount;
}

// @ 0x00695770
int SP::cVarListSerializer::Execute(FieldReport* report)
{
    if (g_bTextFlag)
        report->mTexts.Reserve(mSerializableVarCount);
    report->mFields.Reserve(mSerializableVarCount);
    for (int i = 0; i < mSerializableVarCount; ++i) {
        cDataSerializationInfo& info = mDataSerializationInfos[i];
        cDataSerializerGeneric* ser = info.mpSerializer;
        if (ser->mpBinderContext == 0)
            ser->mpBinderContext = mpObject;
        if (ser->mpWriteWideFunc && ser->mpDataBinderFunc)
            ser->mpWriteWideFunc(report, ser->mpDataBinderFunc(ser));
        if (g_bTextFlag) {
            const char* name = ser->mpStaticFieldName;
            CharString value;
            if (ser->mpWriteStringFunc && ser->mpDataBinderFunc) {
                ser->mpWriteStringFunc(&value, ser->mpDataBinderFunc(ser));
                if (value.mpBegin != value.mpEnd) {
                    CharString tagged;
                    tagged.sprintf("<%s>%s</%s>", name, value.mpBegin, name);
                    ((WStrTmpVec*)&report->mTexts)->push_back(ConvertToString16(tagged));
                }
            }
        }
        ser->mpBinderContext = info.mpBinderContext;
    }
    return mSerializableVarCount;
}

// @ 0x00695140
Node* Parent::GetOrCreate(unsigned key, const wchar_t* name)
{
    HashIter it = gNodeTable.find(key);
    Node* node;
    if (it == gNodeTable.end()) {
        Node* mem = (Node*)EASTL_alloc(0x74, "Simulator", 0, 0, 0, 0);
        node = mem ? mem->init(key) : 0;
        WStr suffix;
        suffix.sprintf(L" @ 0x%08x", key);
        {
            cWString full(name);
            node->mName = WStrConcat(full, suffix);
        }
        mChildren.push_back(node);
        node->mParents.push_back(this);
        HashPair pair; pair.first = key; pair.second = node;
        gNodeTable.insert(pair, false);
        if (g_bTextFlag) {
            node->mOpenTag.sprintf(L"<%s>", name);
            node->mCloseTag.sprintf(L"</%s>", name);
        }
    } else {
        node = ((HashPair*)it.mpNode)->second;
        mChildren.push_back(node);
        node->mParents.push_back(this);
    }
    return node;
}


// =====================================================================
// @ 0x00695b40  link a child node into this writer (create+execute if new)
// =====================================================================
bool Parent::AddChild(unsigned obj, const void* desc, const wchar_t* name)
{
    HashIter it = gNodeTable.find(obj);
    if (it == gNodeTable.end()) {
        Node* node = GetOrCreate(obj, name);
        SP::cVarListSerializer local((void*)obj, (SP::cDataSerializerGeneric*)desc, 0x1a80d26);
        return local.Execute((FieldReport*)node) != 0;
    }
    HashPair* entry = (HashPair*)it.mpNode;
    mChildren.push_back(entry->second);
    Node* node = entry->second;
    node->mParents.push_back(this);
    return true;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
