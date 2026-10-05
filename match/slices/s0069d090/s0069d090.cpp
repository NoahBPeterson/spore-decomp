// Batch w1g5 slices s0069d090..s0069e3a0 (part 1): SP::cObjectDatabase / serializer helpers.
// Region is /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <intrin.h>

typedef void* VP;
typedef void** VTP;

// Vtable-bearing globals referenced by address (relocations are masked).
extern char g_vtbl_1408550[];
extern char g_vtbl_1408598[];
extern char g_vtbl_14085dc[];
extern char g_vtbl_140862c[];
extern char g_vtbl_1408668[];
extern char g_vtbl_14085f0[];
extern char g_vtbl_13eb938[];
extern char g_vtbl_13effb8[];
extern char g_vtbl_14086e8[];
extern char g_vtbl_1408698[];
extern char g_vtbl_1408688[];
extern char g_vtbl_1408678[];
extern char g_vtbl_13ec458[];

// EA::Variant (0x14 bytes) as seen by the serializers.
struct Variant {
    void* mPtr;             // +0
    int   mField4;          // +4
    int   mCount;           // +8
    int   mFieldC;          // +0xc
    unsigned short mFlags;  // +0x10
    unsigned short mTypeId; // +0x12
};

extern "C" void* memcpy(void*, const void*, unsigned int);

// ---------------------------------------------------------------------------
// 0x0069d1c0  two-vptr initialiser
// ---------------------------------------------------------------------------
struct C1 { char pad[4]; void init(); };

void C1::init()
{
    *(VP*)((char*)this + 4) = g_vtbl_13eb938;
    *(VP*)((char*)this) = g_vtbl_13effb8;
}

// ---------------------------------------------------------------------------
// 0x0069d1d0 / 0x0069d280  flag-reset stubs (ret 8)
// ---------------------------------------------------------------------------
struct C2a { char pad[4]; unsigned char flag; bool f(int, int); };
struct C2b { char pad[0xc]; unsigned char flag; bool g(int, int); };

bool C2a::f(int, int) { flag = 0; return false; }
bool C2b::g(int, int) { flag = 0; return false; }

// ---------------------------------------------------------------------------
// 0x0069d210  read a blob in 1KB chunks through a virtual stream
// ---------------------------------------------------------------------------
struct C3 {
    char pad[8];
    void* stream;       // +8
    unsigned char flag; // +0xc
    bool read(int size);
};

bool C3::read(int size)
{
    char buffer[1024];
    if (size >= 0x400) {
        int blocks = size >> 10;
        size -= blocks << 10;
        do {
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x34 / 4])(stream, buffer, 0x400);
        } while (--blocks);
    }
    if (size > 0) {
        ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x34 / 4])(stream, buffer, size);
    }
    return flag != 0;
}

// ---------------------------------------------------------------------------
// 0x0069d2c0  CloseIStream(serializable)
// ---------------------------------------------------------------------------
extern "C" void __stdcall FUN_0069d2c0(void* p);
void __stdcall FUN_0069d2c0(void* p)
{
    ((void(__thiscall*)(void*))(*(void***)p)[0x14 / 4])(p);
}

// ---------------------------------------------------------------------------
// 0x0069d2f0  clamp a percentage into [0,100] and keep the maximum
// ---------------------------------------------------------------------------
struct C5 { char pad[0x20]; float mfProgress; void setProgress(float v); };

void C5::setProgress(float v)
{
    if (v < 0.0f)
        v = 0.0f;
    else if (v > 100.0f)
        v = 100.0f;
    if (v > mfProgress)
        mfProgress = v;
}

// ---------------------------------------------------------------------------
// 0x0069d360  interface query (IID 0xee3f516e)
// ---------------------------------------------------------------------------
struct C6 { VP asInterface(int iid); };

VP C6::asInterface(int iid)
{
    if (iid != (int)0xee3f516e)
        return 0;
    return ((char*)this - 4) ? this : 0;
}

// ---------------------------------------------------------------------------
// 0x0069d3c0  refcount release on +4 with a deleteSelf callback at -4
// ---------------------------------------------------------------------------
struct C7 { int Release(); };

int C7::Release()
{
    long* p = (long*)((char*)this + 4);
    long n = _InterlockedExchangeAdd(p, -1);
    --n;
    if (n == 0) {
        _InterlockedExchange(p, 1);
        void* owner = (void*)((char*)this - 4);
        if (owner)
            ((void(__thiscall*)(void*, int))(*(void***)owner)[0])(owner, 1);
    }
    return (int)n;
}

// ---------------------------------------------------------------------------
// 0x0069d3f0  Database::GetRefCount (atomic read at +8)
// ---------------------------------------------------------------------------
struct C8 { int GetRefCount(); };

int C8::GetRefCount()
{
    return (int)_InterlockedExchangeAdd((long*)((char*)this + 8), 0);
}

// ---------------------------------------------------------------------------
// 0x0069d480 / 0x0069d4d0 / 0x0069d4f0  two-refcount holder
// ---------------------------------------------------------------------------
struct Holder {
    char pad[4];
    unsigned char flag;     // +4
    char pad2[7];
    void* p0c;              // +0xc
    void* p10;              // +0x10
    bool reset();
    bool valid();
    void conditional(int, int);
};

bool Holder::reset()
{
    if (p10 && p0c)
        ((void(__thiscall*)(void*))(*(void***)p0c)[0x24 / 4])(p0c);
    void* q = p0c;
    if (q) {
        p0c = 0;
        ((void(__thiscall*)(void*))(*(void***)q)[8 / 4])(q);
    }
    void* r = p10;
    if (r) {
        p10 = 0;
        ((void(__thiscall*)(void*))(*(void***)r)[4 / 4])(r);
    }
    return flag = true;
}

bool Holder::valid()
{
    return p0c != 0 && p10 != 0;
}

void Holder::conditional(int a, int b)
{
    void* o = p10;
    void* pi = ((void*(__thiscall*)(void*))(*(void***)o)[0x14 / 4])(o);
    if (flag) {
        void* self = (this == (Holder*)8) ? 0 : this;
        char c = ((char(__thiscall*)(void*, void*, int, int))(*(void***)pi)[0x24 / 4])(pi, self, a, b);
        if (c) {
            flag = 1;
            return;
        }
    }
    flag = 0;
}

// ---------------------------------------------------------------------------
// 0x0069d830  conditional compare-write
// ---------------------------------------------------------------------------
struct C830 { char pad[4]; unsigned char flag; char pad2[7]; void* p0c; void f(int a, int b); };

void C830::f(int a, int b)
{
    void* pi = ((void*(__thiscall*)(void*))(*(void***)p0c)[0x18 / 4])(p0c);
    int r = ((int(__thiscall*)(void*, int, int))(*(void***)pi)[0x30 / 4])(pi, a, b);
    flag = (unsigned char)(r == b);
}

// ---------------------------------------------------------------------------
// 0x0069d8e0 / 0x0069d930  two-refcount holder variant
// ---------------------------------------------------------------------------
struct Holder8 {
    char pad[4];
    void* p4;               // +4
    void* p8;               // +8
    unsigned char flag;     // +0xc
    bool reset();
    bool valid();
};

bool Holder8::reset()
{
    if (p8 && p4)
        ((void(__thiscall*)(void*))(*(void***)p4)[0x24 / 4])(p4);
    void* q = p4;
    if (q) {
        p4 = 0;
        ((void(__thiscall*)(void*))(*(void***)q)[8 / 4])(q);
    }
    void* r = p8;
    if (r) {
        p8 = 0;
        ((void(__thiscall*)(void*))(*(void***)r)[4 / 4])(r);
    }
    return flag = true;
}

bool Holder8::valid()
{
    return p4 != 0 && p8 != 0;
}

// ---------------------------------------------------------------------------
// 0x0069d950  write one serialized object through the vtable
// ---------------------------------------------------------------------------
struct C950 { void emit(void*); };

void C950::emit(void* p)
{
    void* u = 0;
    if (p)
        u = ((void*(__thiscall*)(void*, int))(*(void***)p)[0xc / 4])(p, 0x179c807);
    ((void(__thiscall*)(void*, void*))(*(void***)this)[0x2c / 4])(this, u);
}

// ---------------------------------------------------------------------------
// 0x0069d980  conditional write helper
// ---------------------------------------------------------------------------
struct C980 { char pad[8]; void* p8; unsigned char flag; int f(int p); };

int C980::f(int p)
{
    if (flag) {
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p8)[0x14 / 4])(p8);
        void* self = (this == (C980*)8) ? 0 : this;
        char c = ((char(__thiscall*)(void*, void*, int))(*(void***)pi)[0x20 / 4])(pi, self, p);
        if (c)
            return flag = 1;
    }
    int r = 0;
    flag = r;
    return r;
}

// ---------------------------------------------------------------------------
// 0x0069dc60  conditional two-arg write helper
// ---------------------------------------------------------------------------
struct Cdc60 { char pad[4]; void* p4; char pad2[4]; unsigned char flag; int f(int a, int b); };

int Cdc60::f(int a, int b)
{
    if (flag) {
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p4)[0x18 / 4])(p4);
        char c = ((char(__thiscall*)(void*, int, int))(*(void***)pi)[0x38 / 4])(pi, a, b);
        if (c)
            return flag = 1;
    }
    int r = 0;
    flag = r;
    return r;
}

// ---------------------------------------------------------------------------
// 0x0069ddc0 / 0x0069dea0  tail-call getters
// ---------------------------------------------------------------------------
struct Cddc0 { char pad[0x14]; void* p14; int get(); };

int Cddc0::get()
{
    void* o = p14;
    if (o)
        return ((int(__thiscall*)(void*))(*(void***)o)[0x20 / 4])(o);
    return 0;
}

struct Cdea0 { char pad[0x1c]; void* p1c; char get(); };

char Cdea0::get()
{
    void* o = p1c;
    if (o)
        return ((char(__thiscall*)(void*))(*(void***)o)[0x1c / 4])(o);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x0069ded0  flush + two releases
// ---------------------------------------------------------------------------
struct Cded0 { char pad[0x14]; void* p14; void* p18; char flush(); };

char Cded0::flush()
{
    ((void(__thiscall*)(void*))(*(void***)this)[0x1c / 4])(this);
    void* q = p18;
    if (q) {
        p18 = 0;
        ((void(__thiscall*)(void*))(*(void***)q)[4 / 4])(q);
    }
    char r = ((char(__thiscall*)(void*))(*(void***)p14)[8 / 4])(p14);
    void* s = p14;
    if (s) {
        p14 = 0;
        void* s4 = (char*)s + 4;
        ((void(__thiscall*)(void*))(*(void***)s4)[4 / 4])(s4);
    }
    return r;
}

// ---------------------------------------------------------------------------
// 0x0069df90  two virtual predicates
// ---------------------------------------------------------------------------
struct Cdf90 { char pad[0x14]; void* p14; void* p18; bool ok(); };

bool Cdf90::ok()
{
    bool c1 = ((char(__thiscall*)(void*))(*(void***)p18)[0x14 / 4])(p18) != 0;
    if (!((char(__thiscall*)(void*))(*(void***)p14)[0x1c / 4])(p14))
        return false;
    return c1;
}

// ---------------------------------------------------------------------------
// 0x0069dfc0  bind a serializable
// ---------------------------------------------------------------------------
struct Cdfc0 { char pad[0x48]; void* p48; bool bind(void* p, int unused); };

bool Cdfc0::bind(void* p, int)
{
    if (p) {
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p)[0x10 / 4])(p);
        int r = ((int(__thiscall*)(void*))(*(void***)pi)[0x20 / 4])(pi);
        if (r) {
            void* old = p48;
            if (p != old) {
                ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
                p48 = p;
                if (old)
                    ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
            }
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x0069e040 / 0x0069e210  small object initialisers
// ---------------------------------------------------------------------------
struct C_e040 {
    VP p0; VP p4; VP p8;
    unsigned char flag; char pad0[3];
    VP p10; VP p14; VP p18;
    C_e040* ctor();
};

C_e040* C_e040::ctor()
{
    p4 = 0;
    p8 = g_vtbl_1408550;
    _ReadWriteBarrier();
    p0 = g_vtbl_14085dc;
    p8 = g_vtbl_1408598;
    flag = 1;
    p10 = 0;
    p14 = 0;
    p18 = 0;
    return this;
}

struct C_e210 {
    VP p0; VP p4; VP p8; VP p0c; VP p10;
    unsigned char flag; char pad0[3];
    C_e210* ctor();
};

C_e210* C_e210::ctor()
{
    p4 = 0;
    p8 = g_vtbl_14085f0;
    _ReadWriteBarrier();
    p0 = g_vtbl_1408668;
    p8 = g_vtbl_140862c;
    p0c = 0;
    p10 = 0;
    flag = 1;
    return this;
}

// ===========================================================================
// Part 2: container-clear helpers and the larger serializer/EH methods.
// These are behaviourally complete or summarised as noted in partial.txt /
// nonmatching.txt (none of them reproduce the original bytes).
// ===========================================================================

// ---------------------------------------------------------------------------
// 0x0069d090 / 0x0069d100 / 0x0069d150  "clear three vectors" instantiations
// ---------------------------------------------------------------------------
struct ClrTriple {
    VP b0, e0, pad0[3];
    VP b1, e1, pad1[3];
    VP b2, e2;
    void clr090();
    void clr100();
    void clr150();
};

void ClrTriple::clr090()
{
    VP b = b0, e = e0;
    memcpy(b, e, (unsigned)((char*)e - (char*)e));
    e0 = (VP)((char*)e - ((char*)e - (char*)b));
    b = b1; e = e1;
    memcpy(b, e, (unsigned)((char*)e - (char*)e));
    e1 = (VP)((char*)e - ((char*)e - (char*)b));
    b = b2; e = e2;
    memcpy(b, e, (unsigned)((char*)e - (char*)e));
    e2 = (VP)((char*)e - ((char*)e - (char*)b));
}

extern "C" void do_copy_key(void*, void*);
extern "C" void do_copy_runinfo(void*, void*);

void ClrTriple::clr100()
{
    VP b = b0, e = e0;
    memcpy(b, e, (unsigned)((char*)e - (char*)e));
    e0 = (VP)((char*)e - ((char*)e - (char*)b));
    do_copy_key(b1, e1);
    do_copy_key(b2, e2);
}

void ClrTriple::clr150()
{
    VP b = b0, e = e0;
    memcpy(b, e, (unsigned)((char*)e - (char*)e));
    e0 = (VP)((char*)e - ((char*)e - (char*)b));
    do_copy_runinfo(b1, e1);
    do_copy_runinfo(b2, e2);
}

// ---------------------------------------------------------------------------
// 0x0069df20  guard + begin/commit
// ---------------------------------------------------------------------------
struct Cdf20 {
    char pad[4];
    void* p4;               // +4
    char pad2[0x10];
    void* p18;              // +0x18
    void* p1c;              // +0x1c
    float f20;              // +0x20
    bool begin(char flag);
};

bool Cdf20::begin(char flag)
{
    f20 = 0.0f;
    char mode = (char)((flag == 0) + 1);
    char c1 = ((char(__thiscall*)(void*, int, int, int))(*(void***)p18)[0x18 / 4])(p18, mode, 4, 0);
    if (c1) {
        if (((char(__thiscall*)(void*, void*, int))(*(void***)p1c)[0x10 / 4])(p1c, this, mode))
            return true;
    }
    if (((int(__thiscall*)(void*))(*(void***)p4)[0x20 / 4])(p4))
        ((void(__thiscall*)(void*))(*(void***)p4)[0x1c / 4])(p4);
    return false;
}

// ---------------------------------------------------------------------------
// 0x0069dca0  SP::cObjectDatabase::~cObjectDatabase
// ---------------------------------------------------------------------------
struct cObjectDatabase {
    VP vt0; VP vt4; VP vt8; VP pad_c; VP vt10; VP pad14; void* p18; void* p1c; float f20;
    void dtor();
};

void cObjectDatabase::dtor()
{
    vt0 = g_vtbl_14086e8;
    vt4 = g_vtbl_1408698;
    vt8 = g_vtbl_1408688;
    vt10 = g_vtbl_1408678;
    if (p1c) {
        p1c = 0;
        ((void(__thiscall*)(void*))(*(void***)p1c)[4 / 4])(p1c);
    }
    if (p1c) {
        ((void(__thiscall*)(void*))(*(void***)p1c)[4 / 4])(p1c);
    }
    if (p18) {
        void* b = (char*)p18 + 4;
        ((void(__thiscall*)(void*))(*(void***)b)[4 / 4])(b);
    }
    vt10 = g_vtbl_13ec458;
    vt8 = g_vtbl_13eb938;
    vt4 = g_vtbl_13effb8;
    vt0 = g_vtbl_13eb938;
}

// ---------------------------------------------------------------------------
// 0x0069df20 left over: variant / IO helpers (external, relocations masked)
// ---------------------------------------------------------------------------
extern "C" char FUN_0093ac80(void*);
extern "C" char FUN_0093a700(void*, void*, int, int);
extern "C" char IO_ReadInt32(void*, void*, int, int);
extern "C" char IO_WriteUint16(void*, void*, int, int);
extern "C" char IO_WriteUint32(void*, void*, int, int);
extern "C" char IO_operator_shl(void*, void*, int);
extern "C" void* EAAllocate(unsigned, const char*, int, int, int, int);
extern "C" void Variant_assign(Variant*, Variant*);
extern "C" void Variant_destruct(Variant*, int);
extern "C" char WriteTypedVariant(void*);
extern "C" char WriteUnknownVariant(void*);
extern "C" void FUN_005766e0(void*);

static unsigned operator_new_count(Variant* v);

// ---------------------------------------------------------------------------
// 0x0069d540  read a Variant (best-effort transcription of the original flow)
// ---------------------------------------------------------------------------
struct R540 {
    VP vt0; unsigned char flag; char pad[7]; void* stream;
    bool readVariant(Variant* v);
    void fail();
};

void R540::fail() { flag = 0; }

bool R540::readVariant(Variant* v)
{
    char present = 0;
    bool ok = flag != 0;
    if (ok) {
        void* p = ((void*(__thiscall*)(void*, char*))(*(void***)stream)[0x18 / 4])(stream, &present);
        ok = FUN_0093ac80(p) != 0;
    }
    flag = (unsigned char)ok;
    if (present != 0) {
        if (ok) {
            void* p = ((void*(__thiscall*)(void*, Variant*, int))(*(void***)stream)[0x18 / 4])(stream, v, 0);
            if (WriteUnknownVariant(p)) { flag = 1; return true; }
        }
        flag = 0;
        return false;
    }
    if (v->mTypeId != 0) {
        Variant tmp;
        Variant_assign(v, &tmp);
        Variant_destruct(&tmp, 0);
    }
    v->mTypeId = 0x11;
    if (flag) {
        void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
        ok = FUN_0093a700(p, &v->mFlags, 1, 0) != 0;
    } else ok = false;
    flag = (unsigned char)ok;
    if ((v->mFlags & 0x50) == 0) {
        if ((v->mFlags & 0x20) == 0) {
            flag = 0;
            return false;
        }
        if (ok) {
            void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
            ok = IO_ReadInt32(p, &v->mCount, 1, 0) != 0;
        } else ok = false;
        flag = (unsigned char)ok;
        if (ok) {
            void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
            ok = IO_ReadInt32(p, &v->mFieldC, 1, 0) != 0;
        } else ok = false;
        flag = (unsigned char)ok;
        if (ok && ((char(__thiscall*)(void*, int, Variant*, int))(*(void***)this)[0x28 / 4])(this, (int)0xee3f516e, v, 0)) {
            flag = 1;
            return true;
        }
        flag = 0;
        return false;
    }
    if (ok) {
        void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
        ok = IO_ReadInt32(p, &v->mCount, 1, 0) != 0;
    } else ok = false;
    flag = (unsigned char)ok;
    if (ok) {
        void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
        ok = IO_ReadInt32(p, &v->mFieldC, 1, 0) != 0;
    } else ok = false;
    flag = (unsigned char)ok;
    unsigned count = operator_new_count(v);
    v->mPtr = (void*)count;
    return ok;
}

// placeholder used above
static unsigned operator_new_count(Variant* v)
{
    void* p = EAAllocate((unsigned)(v->mCount * v->mFieldC), "App/PropertyList/Variant/PointerPtr", 0, 0, 0, 0);
    return (unsigned)(unsigned long)p;
}

// ---------------------------------------------------------------------------
// 0x0069d9d0  write a Variant (summarised)
// ---------------------------------------------------------------------------
struct W9d0 {
    VP vt0; void* stream; unsigned char flag;
    bool writeVariant(Variant* v);
};

bool W9d0::writeVariant(Variant* v)
{
    bool notVariant = v->mTypeId != 0x11;
    bool ok = flag != 0;
    if (ok) {
        void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
        ok = IO_operator_shl(p, &notVariant, 1) != 0;
    }
    flag = (unsigned char)ok;
    if (notVariant) {
        if (ok) {
            void* p = ((void*(__thiscall*)(void*, Variant*, int))(*(void***)stream)[0x18 / 4])(stream, v, 0);
            if (WriteTypedVariant(p)) { flag = 1; return true; }
        }
        flag = 0;
        return false;
    }
    if (ok) {
        unsigned short f = v->mFlags;
        void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
        ok = IO_WriteUint16(p, &f, 1, 0) != 0;
    } else ok = false;
    flag = (unsigned char)ok;
    if (ok) {
        void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
        ok = IO_WriteUint32(p, &v->mCount, 1, 0) != 0;
    } else ok = false;
    flag = (unsigned char)ok;
    if (ok) {
        void* p = ((void*(__thiscall*)(void*))(*(void***)stream)[0x18 / 4])(stream);
        ok = IO_WriteUint32(p, &v->mField4, 1, 0) != 0;
    } else ok = false;
    flag = (unsigned char)ok;
    return ok;
}

// ---------------------------------------------------------------------------
// 0x0069e090 / 0x0069e170 / 0x0069e260  serializer EH wrappers (summarised)
// ---------------------------------------------------------------------------
struct S_e090 {
    VP vt0; unsigned char flag; char pad[7]; void* p0c; void* p10;
    void bind(void* p, int x);
};
void S_e090::bind(void* p, int)
{
    if (!((char(__thiscall*)(void*))(*(void***)this)[0x14 / 4])(this))
        return;
    if (p) {
        void* old = p10;
        if (p != old) {
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            p10 = p;
            if (old) ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
        }
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p10)[0x10 / 4])(p10);
        void* tmp = 0;
        if (((char(__thiscall*)(void*, int, void**, int, int, int, int))(*(void***)pi)[0x34 / 4])(pi, 0, &tmp, 1, 6, 1, 0))
            FUN_005766e0(&tmp);
        if (tmp) ((void(__thiscall*)(void*))(*(void***)tmp)[8 / 4])(tmp);
    }
    flag = (unsigned char)(p0c != 0);
}

struct S_e170 {
    char pad0[0x14]; void* p14;
    char create(void* p, void** pp, int x);
};
char S_e170::create(void* p, void** pp, int x)
{
    *pp = 0;
    void* tmp = 0;
    char ok = ((char(__thiscall*)(void*, void**, int))(*(void***)this)[0x2c / 4])(this, &tmp, x);
    if (ok && p) {
        int r = ((int(__thiscall*)(void*, void*))(*(void***)p)[0xc / 4])(p, tmp);
        if (r) {
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            *pp = (void*)r;
        }
    }
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
    return ok;
}

struct S_e260 {
    VP vt0; void* p4; void* p8; unsigned char flag;
    void bind(void* p, int a, int b);
};
void S_e260::bind(void* p, int a, int b)
{
    if (!((char(__thiscall*)(void*))(*(void***)this)[0x14 / 4])(this))
        return;
    if (p) {
        void* old = p8;
        if (p != old) {
            ((void(__thiscall*)(void*))(*(void***)p)[0])(p);
            p8 = p;
            if (old) ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
        }
        void* pi = ((void*(__thiscall*)(void*))(*(void***)p8)[0x10 / 4])(p8);
        void* tmp = 0;
        if (((char(__thiscall*)(void*, int, void**, int, int, int, int))(*(void***)pi)[0x34 / 4])(pi, a, &tmp, 2, 4, 1, 0)) {
            FUN_005766e0(&tmp);
            int v = (b == 0) ? 0 : ((int(__thiscall*)(void*))(*(void***)(void*)p4)[0x1c / 4])(p4);
            pi = ((void*(__thiscall*)(void*))(*(void***)p4)[0x18 / 4])(p4);
            ((void(__thiscall*)(void*, int, int))(*(void***)pi)[0x28 / 4])(pi, v, 0);
        }
        if (tmp) ((void(__thiscall*)(void*))(*(void***)tmp)[8 / 4])(tmp);
    }
    flag = (unsigned char)(p4 != 0);
}
