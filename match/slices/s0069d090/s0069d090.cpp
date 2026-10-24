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
    unsigned mElem;         // +4
    unsigned mCount;        // +8
    unsigned mFieldC;       // +0xc
    unsigned short mFlags;  // +0x10
    unsigned short mTypeId; // +0x12
    Variant() : mFlags(0), mTypeId(0) {}
    ~Variant() { if (mFlags & 4) Destruct(false); }
    Variant& operator=(const Variant&);   // 0x542b80
    void Destruct(bool);                  // 0x93db80
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
    unsigned char read(int size);
};

unsigned char C3::read(int size)
{
    char buffer[1024];
    if (size >= 0x400) {
        unsigned blocks = (unsigned)size >> 10;
        size -= blocks << 10;
        do {
            ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x34 / 4])(stream, buffer, 0x400);
        } while (--blocks);
    }
    if (size > 0) {
        ((void(__thiscall*)(void*, void*, int))(*(void***)stream)[0x34 / 4])(stream, buffer, size);
    }
    return flag;
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

// @ 0x0069d3c0
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

// @ 0x0069d4f0
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
// 0x0069d980  conditionalA
// ---------------------------------------------------------------------------
struct C980 { char pad[8]; void* p8; unsigned char flag; int conditionalA(int p); };

int C980::conditionalA(int p)
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
// 0x0069dc60  conditionalB
// ---------------------------------------------------------------------------
struct Cdc60 { char pad[4]; void* p4; char pad2[4]; unsigned char flag; int conditionalB(int a, int b); };

int Cdc60::conditionalB(int a, int b)
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

// @ 0x0069df90
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
// 0x0069d090 / 0x0069d100 / 0x0069d150  cHermiteSplineInterpolation<T>::Clear()
// Each clears three member vectors: a float vector at +0x00 and two value
// vectors at +0x14 / +0x28.  Every erase is "move [last,end) onto first, then
// mEnd -= (last - first)"; for a full-range erase the moved span is empty, so
// the memcpy/copy copies zero elements.  T=float inlines the 4-byte erase for
// all three members, T=Vector3 calls SpVector<Vector3>::erase for the value
// vectors, and T=cSPQuaternion uses the 16-byte copy_705250 helper.
// ---------------------------------------------------------------------------
extern "C" void* copy_705250(const void*, const void*, void*);  // 0x00705250

struct Quad16 { char b[16]; };

struct VecF {
    void* mBegin;   // +0x00
    void* mEnd;     // +0x04
    void* mCap;     // +0x08
    void* pad0;     // +0x0c
    void* pad1;     // +0x10
    void erase() {
        void* first = mBegin;
        void* last  = mEnd;
        memcpy(first, last, (unsigned)((char*)mEnd - (char*)last));
        mEnd = (void*)((int*)mEnd - ((int*)last - (int*)first));
    }
    void eraseQ() {
        Quad16* first = (Quad16*)mBegin;
        Quad16* last  = (Quad16*)mEnd;
        copy_705250(last, last, first);
        mEnd = (void*)((Quad16*)mEnd - (last - first));
    }
};

struct SpVector {
    void* mBegin; void* mEnd; void* mCap; void* pad0; void* pad1;
    void* erase(void* first, void* last);                 // 0x0050f740
    void eraseAll() { erase(mBegin, mEnd); }
};

struct ClrTriple {
    VecF v[3];      // +0x00, +0x14, +0x28
    void clr090();
    void clr100();
    void clr150();
};

// @ 0x0069d090
void ClrTriple::clr090()
{
    v[0].erase();
    v[1].erase();
    v[2].erase();
}

// @ 0x0069d100
void ClrTriple::clr100()
{
    v[0].erase();
    ((SpVector&)v[1]).eraseAll();
    ((SpVector&)v[2]).eraseAll();
}

// @ 0x0069d150
void ClrTriple::clr150()
{
    v[0].erase();
    v[1].eraseQ();
    v[2].eraseQ();
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

// @ 0x0069df20
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

// @ 0x0069dca0
void cObjectDatabase::dtor()
{
    vt0 = g_vtbl_14086e8;
    vt4 = g_vtbl_1408698;
    vt8 = g_vtbl_1408688;
    vt10 = g_vtbl_1408678;
    void* q = p1c;
    if (q) {
        p1c = 0;
        ((void(__thiscall*)(void*))(*(void***)q)[4 / 4])(q);
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
// Variant (de)serialisation: SP::cObjectDatabaseOStream / IStream
// ---------------------------------------------------------------------------
struct IOS;                                              // EA::IO stream (opaque)
bool __cdecl StreamWrite(IOS*, void*, int);              // 0x93a9a0
bool __cdecl WriteVariantTyped(IOS*, Variant*, int);     // 0x693390
bool __cdecl WriteUint16(IOS*, const void*, int, int);   // 0x93a9d0
bool __cdecl WriteUint32(IOS*, const void*, int, int);   // 0x93aa70

struct StreamHolder {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual IOS* GetStream();   // 0x18
};
struct Iface {
    virtual void i0(); virtual void i1(); virtual void i2();
    virtual void* Query(unsigned iid);   // 0xc
};

struct W9d0 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual bool WriteObj(void* o);      // 0x28
    StreamHolder* stream;                // +4
    char pad8[4];
    unsigned char flag;                  // +0xc
    bool writeVariant(Variant* v);
};

// @ 0x0069d9d0
bool W9d0::writeVariant(Variant* v)
{
    IOS* io;
    unsigned tmp;
    bool notVariant = v->mTypeId != 0x11;
    bool t = notVariant;
    flag = flag && (io = stream->GetStream(), StreamWrite(io, &t, 1));
    if (notVariant) {
        if (flag && (io = stream->GetStream(), WriteVariantTyped(io, v, 0))) {
            int r = 1;
            flag = r;
            return r;
        }
        int r = 0;
        flag = r;
        return r;
    }
    flag = flag && (tmp = v->mFlags, io = stream->GetStream(), WriteUint16(io, &tmp, 1, 0));
    if ((v->mFlags & 0x50) == 0) {
        if ((v->mFlags & 0x20) == 0) {
            flag = 0;
            return flag;
        }
        flag = flag && (tmp = v->mCount, io = stream->GetStream(), WriteUint32(io, &tmp, 1, 0));
        flag = flag && (tmp = v->mElem, io = stream->GetStream(), WriteUint32(io, &tmp, 1, 0));
        Iface* o = 0;
        if (v->mFlags & 0x30) o = (Iface*)v->mPtr;
        else if (v->mTypeId) o = (Iface*)v;
        void* r = o ? o->Query(0xee3f516e) : 0;
        if (flag && WriteObj(r)) {
            int one = 1;
            flag = one;
            return one;
        }
        int zero = 0;
        flag = zero;
        return zero;
    }
    flag = flag && (tmp = v->mCount, io = stream->GetStream(), WriteUint32(io, &tmp, 1, 0));
    flag = flag && (tmp = v->mElem, io = stream->GetStream(), WriteUint32(io, &tmp, 1, 0));
    Iface** arr = (Iface**)((v->mFlags & 0x30) ? v->mPtr : (v->mTypeId ? (void*)v : 0));
    unsigned i = 0;
    if (v->mCount != 0) {
        while (flag) {
            Iface* e = arr[i];
            void* r = e ? e->Query(0xee3f516e) : 0;
            flag = flag && WriteObj(r);
            i++;
            if (i >= v->mCount) return flag;
        }
    }
    return flag;
}

// ---------------------------------------------------------------------------
// 0x0069d540  SP::cObjectDatabaseIStream::ReadVariant (EH frame: temp Variant)
// ---------------------------------------------------------------------------
bool __cdecl ReadBool(IOS*, bool*);                          // 0x93ac80
bool __cdecl ReadVariantTyped(IOS*, Variant*, int);          // 0x694440
bool __cdecl ReadUint16(IOS*, void*, int, int);              // 0x93a700
bool __cdecl ReadInt32(IOS*, void*, int, int);               // 0x93a780
void* __cdecl OpNew(unsigned, const char*, int, int, int, int);  // 0xf473a0
extern char kName_PointerPtr[];                              // 0x1403974

struct R540 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual bool ReadObj(unsigned iid, void* dst, int);      // 0x28
    unsigned char flag;                                      // +4
    char pad5[7];
    StreamHolder* stream;                                    // +0xc
    bool readVariant(Variant* v);
};

// @ 0x0069d540
bool R540::readVariant(Variant* v)
{
    bool present;
    IOS* io;
    flag = flag && ReadBool(stream->GetStream(), &present);
    if (present) {
        if (flag && ReadVariantTyped(stream->GetStream(), v, 0)) {
            int r = 1;
            flag = r;
            return r;
        }
        int r = 0;
        flag = r;
        return r;
    }
    unsigned i = 0;
    if (v->mTypeId != 0) {
        Variant tmp;
        *v = tmp;
    }
    v->mTypeId = 0x11;
    flag = flag && (io = stream->GetStream(), ReadUint16(io, &v->mFlags, 1, 0));
    if ((v->mFlags & 0x50) == 0) {
        if ((v->mFlags & 0x20) == 0) {
            flag = 0;
            return flag;
        }
        flag = flag && (io = stream->GetStream(), ReadInt32(io, &v->mCount, 1, 0));
        flag = flag && (io = stream->GetStream(), ReadInt32(io, &v->mElem, 1, 0));
        if (flag && ReadObj(0xee3f516e, v, 0)) {
            int r = 1;
            flag = r;
            return r;
        }
        int r = 0;
        flag = r;
        return r;
    }
    flag = flag && (io = stream->GetStream(), ReadInt32(io, &v->mCount, 1, 0));
    flag = flag && (io = stream->GetStream(), ReadInt32(io, &v->mElem, 1, 0));
    v->mPtr = OpNew(v->mElem * v->mCount, kName_PointerPtr, 0, 0, 0, 0);
    char* arr = (char*)((v->mFlags & 0x30) ? v->mPtr : (v->mTypeId ? (void*)v : 0));
    if (v->mCount != 0) {
        while (flag) {
            bool b = ReadObj(0xee3f516e, arr, 0) != 0;
            i++;
            flag = b;
            arr += 4;
            if (i >= v->mCount) return b;
        }
    }
    return flag;
}

// ---------------------------------------------------------------------------
// 0x0069e090 / 0x0069e170 / 0x0069e260  serializer wrappers with a smart-pointer temp (EH frame)
// ---------------------------------------------------------------------------
struct Tmp8 {   // object released through vtable slot 2 (+8)
    virtual void t0(); virtual void t1(); virtual void Release();
};
struct Tmp8Ref {   // AutoRefCount-style temp: zero-initialised, released in the dtor
    Tmp8* p;
    Tmp8Ref() : p(0) {}
    ~Tmp8Ref() { if (p) p->Release(); }
};
struct PiBind {   // factory interface; slot 0x34 binds a value into the temp
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p0a(); virtual void p0b();
    virtual void p0c();
    virtual bool Bind(int a, Tmp8Ref* out, int, int, int, int);   // 0x34
};
struct Held {     // reference-counted holder target
    virtual void AddRef(); virtual void Release(); virtual void h2(); virtual void h3();
    virtual PiBind* GetBinder();   // 0x10
};
struct SmartSlot { void* p; void Attach(Tmp8Ref* src); };    // 0x5766e0 (thiscall, 1 arg)

struct S_e090 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual bool Ready();          // 0x14
    unsigned char flag;            // +4
    char pad5[7];
    SmartSlot slot;                // +0xc
    Held* p10;                     // +0x10
    bool bind(Held* p, int x);
};

// @ 0x0069e090
bool S_e090::bind(Held* p, int x)
{
    if (!Ready()) return false;
    if (p) {
        Held* old = p10;
        if (p != old) {
            p->AddRef();
            p10 = p;
            if (old) old->Release();
        }
        PiBind* b = p10->GetBinder();
        Tmp8Ref tmp;
        if (b->Bind(x, &tmp, 1, 6, 1, 0))
            slot.Attach(&tmp);
    }
    return flag = slot.p != 0;
}

struct IfaceA {   // p4 target: slot 0x18 returns an object whose slot 0x1c yields a value and slot 0x28 consumes it
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05();
    virtual struct IfaceB* Get();      // 0x18
};
struct IfaceB {
    virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03();
    virtual void b04(); virtual void b05(); virtual void b06();
    virtual int  Value();              // 0x1c
    virtual void b08(); virtual void b09();
    virtual void Put(int v, int);      // 0x28
};
struct SmartSlotA { IfaceA* p; void Attach(Tmp8Ref* src); };  // 0x5766e0 (thiscall, 1 arg)

struct S_e260 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual bool Ready();          // 0x14
    SmartSlotA slot;               // +4
    Held* p8;                      // +8
    unsigned char flag;            // +0xc
    bool bind(Held* p, int a, char b);
};

// @ 0x0069e260
bool S_e260::bind(Held* p, int a, char b)
{
    if (!Ready()) return false;
    if (p) {
        Held* old = p8;
        if (p != old) {
            p->AddRef();
            p8 = p;
            if (old) old->Release();
        }
        PiBind* bd = p8->GetBinder();
        Tmp8Ref tmp;
        if (bd->Bind(a, &tmp, 2, 4, 1, 0)) {
            slot.Attach(&tmp);
            int v;
            if (b) v = 0;
            else v = slot.p->Get()->Value();
            slot.p->Get()->Put(v, 0);
        }
    }
    return flag = slot.p != 0;
}

struct Own4 {   // owner released through slot 1 (+4), add-ref'd through slot 0
    virtual void AddRef(); virtual void Release(); virtual void o2();
    virtual void* Make(void* p);     // 0xc
};
struct Own4Ref {
    Own4* p;
    Own4Ref() : p(0) {}
    ~Own4Ref() { if (p) p->Release(); }
};
struct S_e170 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void va();
    virtual char Fetch(Own4Ref* out, int x);   // 0x2c
    char create(void* p, void** pp, int x);
};

// @ 0x0069e170
char S_e170::create(void* p, void** pp, int x)
{
    *pp = 0;
    Own4Ref tmp;
    char ok = Fetch(&tmp, x);
    if (ok) {
        if (tmp.p) {
            void* r = tmp.p->Make(p);
            if (r) {
                tmp.p->AddRef();
                *pp = r;
            }
        }
    }
    return ok;
}
