// Slice s00b8e180: Editor::cPropertyList (GmeEditorResBase-derived) — default ctor,
// destructor, member helpers and serialization (MSVC 2008 SP1, /O2).
//
//  0x00b8e180  cPropertyList()                        (default ctor)
//  0x00b8e3f0  assign a wide-string member from a range
//  0x00b8e590  typed-value to-string + key lookup compare
//  0x00b8e760  purge rule entries with empty key containers
//  0x00b8e7d0  erase the entry whose key matches
//  0x00b8e830  erase the whole rule vector
//  0x00b8e860  ~cPropertyList()
//  0x00b8eaa0  Serialize(stream)
//  0x00b8ef40  vector assign (pointer vector)
//  0x00b8f030  operator=(const cPropertyList&)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned undefined4;
typedef unsigned uint;

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

// ---------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------
void __cdecl operator_delete(void* p);                                        // 0x00f47380
void* __cdecl operator_new(unsigned size, const char* name, int a, int b,
                           const char* file, int line);                       // 0x00f473a0
void* __cdecl VectorInsert(void* dst, void* src, unsigned n);                 // 0x011e0744
struct RuleObj {
    void Destroy();                                                        // 0x00ff2e30
};
// 0x00ff2e30 (__thiscall, this in ecx)
#define ObjDtor(o) ((RuleObj*)(o))->Destroy()

// generic eastl vector {begin,end,cap}
struct PtrVec {
    void* begin;   // +0
    void* end;     // +4
    void* cap;     // +8
    // 0x00b968b0 (__thiscall): grow to hold n elements; returns the new buffer.
    void* allocateToFit(unsigned n, void* srcBegin, void* srcEnd);
    // 0x00b8ef40 (__thiscall): copy assignment.
    PtrVec* assignSlow(const PtrVec& o);
    // 0x00fea240 (__thiscall, two stack args): erase a range.
    void eraseRange(void* b, void* e);                                         // 0x00fea240
};
// 0x00fea240 reached with just (begin,end) on the stack and no this.
// 0x006609a0 (__thiscall, one stack arg)
#define KeyVecAssign(d, s) ((PtrVec*)(d))->assignSlow(*(const PtrVec*)(s))
// 0x0050d4e0 (__thiscall, one stack arg)
#define FloatVecAssign(d, s) ((PtrVec*)(d))->assignSlow(*(const PtrVec*)(s))
// 0x00b8e420 (__thiscall, one stack arg)
#define RuleVecAssign(d, s) ((PtrVec*)(d))->assignSlow(*(const PtrVec*)(s))
// 0x00b8ef40 (this TU)
#define PtrVecAssign(d, s) ((PtrVec*)(d))->assignSlow(*(const PtrVec*)(s))

// --- Serialize helpers (0x00b8eaa0) ---------------------------------------
extern void* g_PlanetAttrs;         // 0x0156b758
extern void* g_SomeWStr;            // 0x0151ac94 (L"..." global)
extern unsigned char g_flag15d8b4c; // 0x015d8b4c

// 0x00f473a0 (__cdecl, 6 args): allocate with a debug name.
void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b,
                         int c, int d);                                       // 0x00f473a0
// 0x0093a780 (__cdecl): EA::IO::ReadInt32(stream, dst, count, unused).
void __cdecl ReadInt32(void* s, unsigned* dst, unsigned n, int z);            // 0x0093a780

// 0x00b96600 (__thiscall, one stack arg): push a pointer onto vector<Ptr>.
struct PushVec {
    void* begin;   // +0
    void* end;     // +4
    void* cap;     // +8
    void pushBack(void** v);                                                  // 0x00b96600
};
// 0x00acb810: push a 0x2c-byte Rule by value (this in ecx, two stack args)
void __stdcall RuleVecPush(void* self, void* dst, void* src);                 // 0x00acb810

#define PushPtrBack(pv, p)  ((PushVec*)(pv))->pushBack((void**)(p))
#define PushRuleBack(pv, d, s) RuleVecPush(pv, d, s)

// 0x00692f90: construct a cVarListSerializer.
void* __cdecl VarListConstruct(void* self, void* global, unsigned id);        // 0x00692f90
// 0x00693e10: serialize the variable list (this in ecx, one stack arg).
char __stdcall VarListSerialize(void* self, void* stream);                    // 0x00693e10

// 0x004010a0: build a 16-bit string from a literal id.
void __cdecl WStrFromLit(void* dst, int lit);                                 // 0x004010a0
// 0x005ecf80: resolve the literal to a wide string.
void* __stdcall WStrResolve(void* from, int lit);                             // 0x005ecf80
// object ctors / deserializers used by Serialize
struct CtorObj {
    void Ctor();          // 0x00ff3440 (cCivData)
    void CtorTribe();     // 0x00ff0700 (cTribeData)
};
#define CIV_CTOR(p)   ((CtorObj*)(p))->Ctor()
#define TRIBE_CTOR(p) ((CtorObj*)(p))->CtorTribe()

// deserializers (each: this in ecx, stream on the stack)
struct Deser {
    bool From(void* s);   // 0x00ff2e80 (cCivData)
    bool TribeFrom(void* s); // 0x00ff0590 (cTribeData operator>>)
    bool CommodityFrom(void* s); // 0x00bfe2d0 (cCommodityNodeData)
    bool RuleFrom(void* s);      // 0x00bc3230 (Rule)
};
#define CIV_FROM(p, s)  ((Deser*)(p))->From(s)
#define TRIBE_FROM(p, s) ((Deser*)(p))->TribeFrom(s)
#define COMM_FROM(p, s) ((Deser*)(p))->CommodityFrom(s)
#define RULE_FROM(p, s) ((Deser*)(p))->RuleFrom(s)

// eastl::basic_string<wchar_t>::assign(first,last): object arrives in ecx.
void __stdcall WString_Assign(const void* b, const void* e);                  // 0x00423650

// cTypedValueToStringT<unsigned char>::Write(self, value)
void __stdcall TypedValueWrite(void* self, int value);                        // 0x00694f60
// EA::ConvertToString16Impl(dst, src, len)
void __cdecl ConvertToString16Impl(void* dst, const char* src, unsigned len); // 0x0093c5a0
// EA::ConvertToString16(dst, src)
void* __cdecl ConvertToString16(void* dst, const void* src);                  // 0x0093c6d0
// eastl::basic_string<wchar_t> ctor(self, other)
void __stdcall WStrCtor(void* self, void* other);                             // 0x0056e2d0

struct Vec4 {
    void** mpBegin;   // +0
    void** mpEnd;     // +4
    void** mpCap;     // +8
};

// range of 0x2c-byte rules
struct Rule {
    uint32_t w[0x2c / 4];
};

struct RuleVec : Vec4 {
    void erase() { Vec4::mpEnd = mpBegin; }
};

extern const char kAllocFile[];

// GmeEditorResBase: only the vtable pointer matters here.
struct GmeEditorResBase {
    void* mvtbl;                       // +0: 0x14655a0 then 0x13eb938 on destruction
};

struct cPropertyList : GmeEditorResBase {
    uint32_t m04;                      // +0x04  (interlocked)
    uint32_t m08, m0c, m10, m14;       // +0x08
    uint32_t m18, m1c, m20;            // +0x18 wide-string range (begin/end/cap)
    uint32_t m24;                      // +0x24
    int32_t  m28;                      // +0x28
    uint32_t m2c;                      // +0x2c
    uint8_t  m30[0x98 - 0x30];         // +0x30
    uint8_t  m98;                      // +0x98
    uint8_t  m99[0x9c - 0x99];         // +0x99
    float    m9cf;                     // +0x9c
    float    ma0f;                     // +0xa0
    float    ma4f;                     // +0xa4
    float    ma8;                      // +0xa8
    uint8_t  mac, mad;                 // +0xac
    float    mb0, mb4, mb8;            // +0xb0
    Vec4     mbc;                      // +0xbc
    uint32_t mC8[2];                   // +0xc8
    Vec4     md0;                      // +0xd0
    uint32_t mDC[2];                   // +0xdc
    Vec4     me4;                      // +0xe4
    uint32_t mF0[2];                   // +0xf0
    Vec4     mf8;                      // +0xf8
    uint32_t m104[3];                  // +0x104
    Vec4     m110;                     // +0x110
    uint32_t m11C[2];                  // +0x11c
    uint32_t m124;                     // +0x124
    float    m128, m12c;               // +0x128
    uint8_t  m130;                     // +0x130
    Vec4     m134;                     // +0x134
    uint32_t m140[2];                  // +0x140
    Vec4     m148;                     // +0x148
    uint32_t m154[2];                  // +0x154
    Vec4     m15c;                     // +0x15c
    uint32_t m168[2];                  // +0x168
    Vec4     m170;                     // +0x170
    uint32_t m17C[2];                  // +0x17c
    uint32_t m184;                     // +0x184
    uint32_t m188, m18c, m190;         // +0x188
    uint32_t m194;                     // +0x194
    uint32_t m198, m19c, m1a0;         // +0x198
    uint32_t m1a4, m1a8, m1ac;         // +0x1a4

    void Ctor();
    void Dtor();
    cPropertyList& operator=(const cPropertyList& o);
    cPropertyList& AssignCopy(const cPropertyList& o);
    bool Serialize(void* stream);
    void AssignRange(const Vec4& r);
    void PurgeEmptyRules();
    void EraseRule(int key);
    void EraseAllRules();
};

// ---------------------------------------------------------------------------
// @ 0x00b8e180
// ---------------------------------------------------------------------------
void cPropertyList::Ctor()
{
    undefined4* p = (undefined4*)this;
    p[0] = (undefined4)0x013ebcdc;       // PropBaseA22 vtable
    _InterlockedExchange((volatile long*)(p + 1), 0);
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[0] = (undefined4)0x014655a0;       // Editor::cPropertyList vtable
    p[8] = (undefined4)0x01667bae;
    p[6] = (undefined4)0x01667bac;       // eastl::gEmptyString16
    p[7] = (undefined4)0x01667bac;
    p[0xb] = 0;
    p[10] = 0xffffffff;
    *((uint8_t*)p + 0x30) = 1;
    *((uint8_t*)p + 0x98) = 1;
    *((float*)p + 0x27) = *(const float*)0x0156b730;
    *((float*)p + 0x28) = *(const float*)0x0156b734;
    *((float*)p + 0x29) = *(const float*)0x0156b738;
    *((float*)p + 0x2a) = *(const float*)0x01485720;
    *((float*)p + 0x2c) = *(const float*)0x013eb1bc;
    *((float*)p + 0x2d) = *((float*)p + 0x2c);
    *((float*)p + 0x2e) = *((float*)p + 0x2c);
    *((uint8_t*)p + 0xac) = 0xff;
    *((uint8_t*)p + 0xad) = 0xff;
    p[0x2f] = 0; p[0x30] = 0; p[0x31] = 0;
    p[0x34] = 0; p[0x35] = 0; p[0x36] = 0;
    p[0x39] = 0; p[0x3a] = 0; p[0x3b] = 0;
    p[0x3e] = 0; p[0x3f] = 0; p[0x40] = 0;
    p[0x44] = 0; p[0x45] = 0; p[0x46] = 0;
    p[0x49] = 0; p[0x4a] = 0; p[0x4b] = 0;
    *((uint8_t*)p + 0x130) = 0;
    p[0x4d] = 0; p[0x4e] = 0; p[0x4f] = 0;
    p[0x52] = 0; p[0x53] = 0; p[0x54] = 0;
    p[0x57] = 0; p[0x58] = 0; p[0x59] = 0;
    p[0x5c] = 0; p[0x5d] = 0; p[0x5e] = 0;
    p[0x61] = 0xffffffff;
    p[0x62] = 0; p[99] = 0; p[100] = 0; p[0x65] = 0;
    p[0x66] = *(const uint32_t*)0x016882ac;
    p[0x67] = *(const uint32_t*)0x016882b0;
    p[0x68] = *(const uint32_t*)0x016882b4;
    p[0x69] = 0; p[0x6a] = 0; p[0x6b] = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00b8e3f0
// ---------------------------------------------------------------------------
void cPropertyList::AssignRange(const Vec4& r)
{
    int* a = (int*)this;
    if (r.mpBegin != r.mpEnd && (a[0x2c / 4] & 1) == 0 && (const int*)&r != a + 6)
        WString_Assign(r.mpBegin, r.mpEnd);
}

// ---------------------------------------------------------------------------
// @ 0x00b8e590
// ---------------------------------------------------------------------------
// Typed-value to string, then match against the entry key.
struct TypedMatcher {
    bool Match(int num, int type, int value);
};
bool TypedMatcher::Match(int num, int type, int value)
{
    int* self = (int*)this;
    void* gEmpty = (void*)0x01667bac;
    void* begin = gEmpty, *end = gEmpty, *cap = (void*)0x01667bad;
    bool result = true;

    TypedValueWrite(&begin, type);
    if (begin == end)
        goto cleanup;

    {
        void* name[3];
        bool isNull = (num == 0);
        if (isNull) {
            name[0] = gEmpty; name[1] = gEmpty; name[2] = (void*)0x01667bae;
        } else {
            ConvertToString16(name, (const void*)num);
        }
        void* nb = name[0], *ne = name[1];
        WStrCtor(&begin, name);
        if (isNull) {
            if (((((int)ne - (int)nb) & 0xfffffffe) > 2) && nb != 0)
                operator_delete(nb);
        } else {
            int b = ((int*)name)[0], e = ((int*)name)[2];
            if (((((e - b) & 0xfffffffe) > 2)) && b != 0)
                operator_delete((void*)b);
        }
    }

    {
        void* k[3];
        ConvertToString16(k, &begin);
        int k0 = ((int*)k)[0], k1 = ((int*)k)[1];
        int v = value;
        bool matched = false;
        if (k0 == k1) {
            if (((char(__thiscall**)(int*, int))(*self))[0](self, v) != 0) {
                if (((char(__thiscall**)(int*, int))(*self))[3](self, k0) == 0)
                    goto after;
                matched = true;
            }
        } else {
            char c = ((char(__thiscall**)(int*, int))(*self))[0](self, k0);
            if (g_flag15d8b4c == 0) {
                if (c != 0) {
                    if (((char(__thiscall**)(int*, int))(*self))[3](self, k0) == 0)
                        goto after;
                    matched = true;
                }
            } else if (c != 0) {
                if (((char(__thiscall**)(int*, const char*, int))(*self))[2]
                        (self, "type", v) == 0)
                    goto after;
                if (((char(__thiscall**)(int*, int))(*self))[3](self, k0) == 0)
                    goto after;
                matched = true;
            }
        }
after:
        if (k0 == k1) {
            if (matched) {
                if (((char(__thiscall**)(int*, int))(*self))[1](self, v) == 0)
                    result = false;
            } else {
                result = false;
            }
        } else {
            v = k0;
            if (matched) {
                if (((char(__thiscall**)(int*, int))(*self))[1](self, v) == 0)
                    result = false;
            } else {
                result = false;
            }
        }
        {
            int b = k[0] ? ((int*)k)[0] : 0;
            int e = ((int*)k)[2];
            if (((((e - b) & 0xfffffffe) > 2)) && b != 0)
                operator_delete((void*)b);
        }
    }

cleanup:
    if (((((int)cap - (int)begin) & 0xfffffffe) > 2) && begin != 0)
        operator_delete(begin);
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00b8e760
// ---------------------------------------------------------------------------
void cPropertyList::PurgeEmptyRules()
{
    int* a = (int*)this;
    int* dst = (int*)a[0x15c / 4];
    if (dst == (int*)a[0x160 / 4])
        return;
    int* src = dst + 1;
    do {
        int* o = (int*)*dst;
        if (((o[0x40 / 4] - o[0x3c / 4]) & 0xfffffffc) == 0) {
            if (o != 0) {
                ObjDtor(o);
                operator_delete(o);
            }
            if (src < (int*)a[0x160 / 4])
                VectorInsert(dst, src, (unsigned)((int)a[0x160 / 4] - (int)src));
            a[0x160 / 4] -= 4;
        } else {
            dst++;
            src++;
        }
    } while (dst != (int*)a[0x160 / 4]);
}

// ---------------------------------------------------------------------------
// @ 0x00b8e7d0
// ---------------------------------------------------------------------------
void cPropertyList::EraseRule(int key)
{
    int* a = (int*)this;
    Rule* p = (Rule*)a[0x134 / 4];
    Rule* end = (Rule*)a[0x138 / 4];
    for (; p != end; p++)
        if (*(int*)p == key)
            break;
    if (p == end)
        return;
    Rule* q = p + 1;
    if (q < end) {
        do {
            *p = *q;
            p++;
            q++;
        } while (q != end);
    }
    a[0x138 / 4] -= 0x2c;
}

// ---------------------------------------------------------------------------
// @ 0x00b8e830
// ---------------------------------------------------------------------------
void cPropertyList::EraseAllRules()
{
    PtrVec* v = (PtrVec*)this;
    v->eraseRange(v->begin, v->end);
}

// ---------------------------------------------------------------------------
// @ 0x00b8e860
// ---------------------------------------------------------------------------
struct LayoutElem {
    void SetSerializer();                                                  // 0x00c2e4e0
};
// 0x00c2e4e0 (__thiscall, this in ecx)
#define ElemDtor(p) ((LayoutElem*)(p))->SetSerializer()

// free a vector<ptr> whose elements were allocated with a 4-byte header:
// drop the shrunk range, then release the buffer if its refcount is 0.
void cPropertyList::Dtor()
{
    int* a = (int*)this;
    mvtbl = (void*)0x014655a0;
    // +0x170: vector of LayoutElem*
    {
        int n = (a[0x174 / 4] - a[0x170 / 4]) >> 2;
        for (int i = 0; i < n; i++) {
            int v = ((int*)a[0x170 / 4])[i];
            if (v != 0) { ElemDtor(v); operator_delete((void*)v); }
        }
        int end = a[0x174 / 4], beg = a[0x170 / 4];
        VectorInsert((void*)beg, (void*)end, 0);
        a[0x174 / 4] = end + ((end - beg) >> 2) * -4;
    }
    // +0x15c: vector of RuleObj*
    {
        int n = (a[0x160 / 4] - a[0x15c / 4]) >> 2;
        for (int i = 0; i < n; i++) {
            int v = ((int*)a[0x15c / 4])[i];
            if (v != 0) { ObjDtor(v); operator_delete((void*)v); }
        }
        int end = a[0x160 / 4], beg = a[0x15c / 4];
        VectorInsert((void*)beg, (void*)end, 0);
        a[0x160 / 4] = end + ((end - beg) >> 2) * -4;
    }
    // +0xe4: vector of raw pointers
    {
        int n = (a[0xe8 / 4] - a[0xe4 / 4]) >> 2;
        for (int i = 0; i < n; i++)
            operator_delete((void*)((int*)a[0xe4 / 4])[i]);
        int end = a[0xe8 / 4], beg = a[0xe4 / 4];
        VectorInsert((void*)beg, (void*)end, 0);
        a[0xe8 / 4] = end + ((end - beg) >> 2) * -4;
    }
#define FREE_OWNED(off) { int v = a[(off) / 4]; \
        if (v != 0 && *(int*)(v - 4) != 0) operator_delete((void*)v); }
    FREE_OWNED(0x170) FREE_OWNED(0x15c) FREE_OWNED(0x148) FREE_OWNED(0x134)
    FREE_OWNED(0x110) FREE_OWNED(0xf8)  FREE_OWNED(0xe4)  FREE_OWNED(0xd0)
    FREE_OWNED(0xbc)
#undef FREE_OWNED
    {
        int b = a[0x18 / 4], e = a[0x20 / 4];
        if ((((e - b) & 0xfffffffe) > 2) && b != 0)
            operator_delete((void*)b);
    }
    mvtbl = (void*)0x013eb938;   // GmeEditorResBase vtable
}

// ---------------------------------------------------------------------------
// @ 0x00b8ef40
// ---------------------------------------------------------------------------
PtrVec* PtrVec::assignSlow(const PtrVec& o)
{
    if (&o == this)
        return this;
    int n = (int)((char*)o.end - (char*)o.begin) >> 2;
    if ((unsigned)((int)((char*)cap - (char*)begin) >> 2) < (unsigned)n) {
        void* p = allocateToFit((unsigned)n, o.begin, o.end);
        if (begin != 0 && *(int*)((int)begin - 4) != 0)
            operator_delete(begin);
        begin = p;
        cap = (void*)((int)p + n * 4);
        end = (void*)((int)p + n * 4);
        return this;
    }
    unsigned have = (unsigned)((int)((char*)end - (char*)begin) >> 2);
    if (have < (unsigned)n) {
        VectorInsert(begin, o.begin, have * 4);
        void* src = (void*)((int)o.begin + ((int)((char*)end - (char*)begin) >> 2) * 4);
        VectorInsert(end, src, (unsigned)((int)((char*)o.end - (int)src)));
        end = (void*)((int)begin + n * 4);
        return this;
    }
    VectorInsert(begin, o.begin, (unsigned)((int)((char*)o.end - (int)o.begin)));
    end = (void*)((int)begin + n * 4);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00b8f030
// ---------------------------------------------------------------------------
cPropertyList& cPropertyList::AssignCopy(const cPropertyList& o)
{
    int* a = (int*)this;
    const int* b = (const int*)&o;
    if ((void*)((int)b + 0x18) != (void*)(a + 6))
        WString_Assign((const void*)b[0x18 / 4], (const void*)b[0x1c / 4]);
    a[0x28 / 4] = b[0x28 / 4];
    a[0x2c / 4] = b[0x2c / 4];
    {
        const int* s = b + 0x30 / 4;
        int* d = a + 0x30 / 4;
        for (int i = 0x1a; i != 0; i--)
            *d++ = *s++;
    }
    *(uint8_t*)((int)a + 0x98) = *(const uint8_t*)((int)b + 0x98);
    a[0x9c / 4] = b[0x9c / 4];
    a[0xa0 / 4] = b[0xa0 / 4];
    a[0xa4 / 4] = b[0xa4 / 4];
    a[0xa8 / 4] = b[0xa8 / 4];
    *(uint8_t*)((int)a + 0xac) = *(const uint8_t*)((int)b + 0xac);
    *(uint8_t*)((int)a + 0xad) = *(const uint8_t*)((int)b + 0xad);
    a[0xb0 / 4] = b[0xb0 / 4];
    a[0xb4 / 4] = b[0xb4 / 4];
    a[0xb8 / 4] = b[0xb8 / 4];
    KeyVecAssign((int)a + 0xbc, (int)b + 0xbc);
    KeyVecAssign((int)a + 0xd0, (int)b + 0xd0);
    PtrVecAssign((int)a + 0xe4, (int)b + 0xe4);
    FloatVecAssign((int)a + 0xf8, (int)b + 0xf8);
    a[0x10c / 4] = b[0x10c / 4];
    FloatVecAssign((int)a + 0x110, (int)b + 0x110);
    a[0x124 / 4] = b[0x124 / 4];
    a[0x128 / 4] = b[0x128 / 4];
    a[0x12c / 4] = b[0x12c / 4];
    *(uint8_t*)((int)a + 0x130) = *(const uint8_t*)((int)b + 0x130);
    RuleVecAssign((int)a + 0x134, (int)b + 0x134);
    FloatVecAssign((int)a + 0x148, (int)b + 0x148);
    PtrVecAssign((int)a + 0x15c, (int)b + 0x15c);
    PtrVecAssign((int)a + 0x170, (int)b + 0x170);
    a[0x184 / 4] = b[0x184 / 4];
    a[0x194 / 4] = b[0x194 / 4];
    a[0x198 / 4] = b[0x198 / 4];
    a[0x19c / 4] = b[0x19c / 4];
    a[0x1a0 / 4] = b[0x1a0 / 4];
    {
        const int* s = b + 0x1a4 / 4;
        int* d = a + 0x1a4 / 4;
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
    }
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x00b8eaa0
// ---------------------------------------------------------------------------
struct ISerialStream {
    virtual void vt00(); virtual void vt04(); virtual void vt08(); virtual void vt0c();
    virtual void vt10(); virtual void vt14(); virtual void vt18(); virtual void vt1c();
    virtual void* GetSerializer();            // slot +0x20 -> index 8
};
struct ISerializer {
    virtual void vt00(); virtual void vt04(); virtual void vt08(); virtual void vt0c();
    virtual void vt10(); virtual void vt14();
    virtual void* GetReader();                // slot +0x18 -> index 6
};

static void* Reader(ISerialStream* s)
{
    ISerializer* ser = (ISerializer*)s->GetSerializer();
    return ser->GetReader();
}

bool cPropertyList::Serialize(void* stream)
{
    int* a = (int*)this;
    ISerialStream* s = (ISerialStream*)stream;
    unsigned count;

    // --- civ data (0x50-byte cCivData*) ---
    ReadInt32(Reader(s), &count, 1, 0);
    {
        int* ve = a + 0x15c / 4;                 // {begin,end,cap}
        VectorInsert((void*)ve[0], (void*)ve[1], 0);
        ve[1] += (((ve[1] - ve[0]) >> 2) * -4);
    }
    for (unsigned i = 0; i < count; i++) {
        void* o = EAAllocate(0x50, "Simulator/cCivData", 0, 0, 0, 0);
        void* v = o ? (CIV_CTOR(o), o) : 0;
        CIV_FROM(v, s);
        int* ve = a + 0x15c / 4;
        if (ve[1] < ve[2]) {
            int* slot = (int*)ve[1];
            ve[1] += 4;
            if (slot) *slot = (int)v;
        } else {
            PushPtrBack(ve, &v);
        }
    }

    // --- tribe data (0x18-byte cTribeData*) ---
    ReadInt32(Reader(s), &count, 1, 0);
    {
        int* ve = a + 0x170 / 4;
        VectorInsert((void*)ve[0], (void*)ve[1], 0);
        ve[1] += (((ve[1] - ve[0]) >> 2) * -4);
    }
    for (unsigned i = 0; i < count; i++) {
        void* o = EAAllocate(0x18, "Simulator/cTribeData", 0, 0, 0, 0);
        void* v = o ? (TRIBE_CTOR(o), o) : 0;
        TRIBE_FROM(v, s);
        int* ve = a + 0x170 / 4;
        if (ve[1] < ve[2]) {
            int* slot = (int*)ve[1];
            ve[1] += 4;
            if (slot) *slot = (int)v;
        } else {
            PushPtrBack(ve, &v);
        }
    }

    // --- rules (0x2c-byte) ---
    ReadInt32(Reader(s), &count, 1, 0);
    PtrVec* rv = (PtrVec*)(a + 0x134 / 4);
    rv->eraseRange(rv->begin, rv->end);
    for (unsigned i = 0; i < count; i++) {
        unsigned char rule[0x2c];
        unsigned* r = (unsigned*)rule;
        r[0] = 0; r[1] = 0; r[2] = 0; r[3] = 0;
        *(unsigned short*)(rule + 0x10) = 0;
        rule[0x12] = 1;
        RULE_FROM(rule, s);
        int* ve = a + 0x138 / 4;
        if (ve[1] < ve[2]) {
            unsigned* slot = (unsigned*)ve[1];
            ve[1] += 0x2c;
            if (slot) {
                for (int k = 0; k < 0xb; k++) slot[k] = r[k];
            }
        } else {
            PushRuleBack(ve, (void*)ve[1], rule);
        }
    }

    // --- commodity node data (8-byte) ---
    ReadInt32(Reader(s), &count, 1, 0);
    {
        int* ve = a + 0xe4 / 4;
        VectorInsert((void*)ve[0], (void*)ve[1], 0);
        ve[1] += (((ve[1] - ve[0]) >> 2) * -4);
    }
    for (unsigned i = 0; i < count; i++) {
        void* o = EAAllocate(8, "Simulator/cCommodityNodeData", 0, 0, 0, 0);
        if (o) { ((unsigned*)o)[0] = 0xffffffff; ((unsigned*)o)[1] = 0xffffffff; }
        COMM_FROM(o, s);
        int* ve = a + 0xe4 / 4;
        if (ve[1] < ve[2]) {
            int* slot = (int*)ve[1];
            ve[1] += 4;
            if (slot) *slot = (int)o;
        } else {
            PushPtrBack(ve, &o);
        }
    }

    // --- variable list ---
    {
        void* vls = VarListConstruct(0, g_PlanetAttrs, 0x1a80d26);
        char ok = VarListSerialize(vls, s);
        // compare the stored name against the global wstring, update if it matches
        {
            unsigned char tmp[0x30];
            WStrFromLit(tmp, 0x7e1310a);
            int* p = (int*)WStrResolve(tmp, 0x7e1310a);
            if (p[0] != p[1] && (*(unsigned char*)((int)a + 0x2c) & 1) == 0
                && p != a + 6)
                WString_Assign((void*)p[0], (void*)p[1]);
            int b = ((int*)tmp)[0], e = ((int*)tmp)[4];
            if ((((e - b) & 0xfffffffe) > 2) && b != 0)
                operator_delete((void*)b);
        }
        return ok != 0;
    }
}
