// Slice s00f2e7d0 -- Simulator scenario object region, part 2 (bfs2 slice 11).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"

// ---------------------------------------------------------------------------
// Allocation / raw-range helpers (VAs in comments; call targets are relocations
// masked by the matcher).
void* __cdecl EA_Alloc(size_t, const char*, int, int, const char*, int);  // 0x00F473A0
void  __cdecl EA_Delete(void*);                                           // 0x00F47380
void  __cdecl MoveA(void*, void*, void*);
void  __cdecl MoveB(void*, void*, void*);
void* __cdecl operator new(size_t, const char*, int, int, int, int);

extern "C" void H_dfcc40();   // 0x00DFCC40 temp destroy (0x238 element)
extern "C" void H_dfce40();   // 0x00DFCE40 temp destroy (0x534 element)
extern "C" void H_dfce90();   // 0x00DFCE90 temp destroy (0x27e0/0x27e8 element)
extern "C" void H_dfd300();   // 0x00DFD300 range destroy (this+2 args)
extern "C" void H_dfe9a0();   // 0x00DFE9A0 move/copy range -> returns new end
extern "C" void H_dfb850();   // 0x00DFB850 string assign
extern "C" void H_dfdff0();   // 0x00DFDFE0 element payload copy (this+1 arg)
extern "C" void H_dff130();   // 0x00DFF130 element copy-construct (this+1 arg)
extern "C" void H_dff1a0();   // 0x00DFF1A0 element copy-construct (0x27e0)
extern "C" void H_dff2b0();   // 0x00DFF2B0 move range (3 args cdecl)
extern "C" void H_dfee80();   // 0x00DFEE80 element reset
extern "C" void H_f2aac0();   // 0x00F2AAC0 element construct
extern "C" void H_f2d010();   // 0x00F2D010 destroy range (3 args cdecl)
extern "C" void H_f2d260();   // 0x00F2D260 element construct (0x27e0)
extern "C" void H_f2d330();   // 0x00F2D330 element construct (0x534)
extern "C" void H_f2d7e0();   // 0x00F2D7E0 element read (this+1 arg)
extern "C" void H_f2e230();   // 0x00F2E230 Vec238::set_capacity
extern "C" void H_f2e5d0();   // 0x00F2E5D0 Vec238::Insert(pos,value)
extern "C" void H_f2e750();   // 0x00F2E750 copy range (3 args cdecl)
extern "C" void H_f2ee50();   // 0x00F2EE50 Vec27e0::set_capacity
extern "C" void H_f2efe0();   // 0x00F2EFE0 Vec534::clear
extern "C" void H_f2f3a0();   // 0x00F2F3A0 Vec27e0 insert
extern "C" void H_f27430();   // 0x00F27430 element deserialize (this+1 arg)
extern "C" void H_ed29b0();   // 0x00ED29B0 lower_bound
extern "C" void H_ed3740();   // 0x00ED3740 insert
extern "C" bool H_93a780();   // 0x0093A780 ReadInt32
extern "C" void H_692f90();   // 0x00692F90 cVarListSerializer ctor
extern "C" void H_693e10();   // 0x00693E10 cVarListSerializer serialize
extern "C" void H_6a1c40();   // 0x006A1C40 cPropertyList ctor

typedef void (__thiscall *TC0)(void*);
typedef void (__thiscall *TC1)(void*, void*);
typedef void (__thiscall *TC2)(void*, void*, void*);
typedef void (__thiscall *TC1i)(void*, unsigned);

extern "C" long _InterlockedExchange(volatile long*, long);

static void FreeBlock(void* p)
{
    if (p && *(int*)((char*)p - 4)) EA_Delete(p);
}

// ---------------------------------------------------------------------------
// Small cString header used by the 0x2cb0 ctor.
struct CString { char pad[0x14]; void ctor(); };         // 0x006B5060
struct PropBase { void ctor(); };                        // 0x006A1C40
extern wchar_t g_emptyW[];
extern wchar_t g_emptyW2[];

// ---------------------------------------------------------------------------
// VObj: owner/stream object; only the vtable slots the targets use are named.
struct VObj {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18();
    virtual VObj* V18();                 // +0x18
    virtual void V1c();                  // +0x1c
    virtual VObj* V20();                 // +0x20
};

// ---------------------------------------------------------------------------
// ---------------------------------------------------------------- 0x27e8
struct E27e8 { char pad[0x27e8]; };
struct V27e8 {
    E27e8* mpBegin; E27e8* mpEnd; E27e8* mpCapacity;
    void set_capacity(unsigned n);
};

// @ 0x00F2EC10
void V27e8::set_capacity(unsigned n)
{
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        E27e8* pNewData = n ? (E27e8*)EA_Alloc(n * 0x27e8, "Simulator", 0, 0,
                                               "allocator.h", 0xd1) : 0;
        E27e8* pOldEnd = mpEnd;
        E27e8* pOldBegin = mpBegin;
        MoveA(pOldBegin, pOldEnd, pNewData);
        MoveB(pOldBegin, pOldEnd, pNewData);
        if (mpBegin)
            EA_Delete(mpBegin);
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = pNewData + n;
    }
}

// ---------------------------------------------------------------- 0x534
struct E534 { char pad[0x534]; };
struct V534 {
    E534* mpBegin; E534* mpEnd; E534* mpCapacity;
    void set_capacity(unsigned n);
    E534* Insert(E534* position, const E534& value);
};

// @ 0x00F2EF10
void V534::set_capacity(unsigned n)
{
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        E534* pNewData = n ? (E534*)EA_Alloc(n * 0x534, "Simulator", 0, 0,
                                             "allocator.h", 0xd1) : 0;
        E534* pOldEnd = mpEnd;
        E534* pOldBegin = mpBegin;
        MoveA(pOldBegin, pOldEnd, pNewData);
        MoveB(pOldBegin, pOldEnd, pNewData);
        if (mpBegin && ((int*)mpBegin)[-1])
            EA_Delete(mpBegin);
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = pNewData + n;
    }
}

// @ 0x00F2F050  V534::Insert
E534* V534::Insert(E534* position, const E534& value)
{
    if (mpEnd != mpCapacity) {
        E534* pValue = (E534*)&value;
        if (pValue >= position && pValue < mpEnd) ++pValue;
        if (mpEnd) ((TC1)H_dff130)(mpEnd, (E534*)mpEnd - 1);
        for (E534* p = mpEnd - 1; p > position; --p)
            ((TC1)H_dff130)(p, p - 1);
        ((TC1)H_dff130)(position, pValue);
        ++mpEnd;
        return position;
    }
    unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
    unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
    E534* pNewData = nNewSize ? (E534*)EA_Alloc(nNewSize * 0x534, "Simulator", 0, 0,
                                                "allocator.h", 0xd1) : 0;
    void* p1 = ((void*(__cdecl*)(void*, void*, void*))H_f2e750)(mpBegin, position, pNewData);
    ((void(__cdecl*)(void*, void*, void*))H_f2d010)(mpBegin, position, pNewData);
    if (p1) ((TC1)H_dff130)(p1, (void*)&value);
    E534* p2 = (E534*)((void*(__cdecl*)(void*, void*, void*))H_f2e750)(position, mpEnd, (char*)p1 + 0x534);
    ((void(__cdecl*)(void*, void*, void*))H_f2d010)(position, mpEnd, (char*)p1 + 0x534);
    if (mpBegin && ((int*)mpBegin)[-1]) EA_Delete(mpBegin);
    mpBegin = pNewData;
    mpEnd = p2;
    mpCapacity = pNewData + nNewSize;
    return position;
}

// ---------------------------------------------------------------- 0x238
struct E238 { int flags; char pad[0x234]; };
struct V238 {
    E238* mpBegin; E238* mpEnd; E238* mpCapacity;
    int f0c; int f10;
    int f14; int f18;
    void Clear();                       // 0x00F2ECD0
    void PushConst();                   // 0x00F2EB30
    int  AssignAt(void* value);         // 0x00F2ED20
};

// @ 0x00F2ECD0
void V238::Clear()
{
    E238* b = mpBegin;
    E238* e = mpEnd;
    void* p = ((void*(__cdecl*)(void*, void*, void*))H_dfe9a0)(e, e, b);
    ((TC2)H_dfd300)(this, p, mpEnd);
    mpEnd = (E238*)((char*)mpEnd + ((int)((char*)e - (char*)b) / 0x238) * 0x238);
    *(int*)((char*)this + 0x14) = 0x3fffffff;
    *(int*)((char*)this + 0x18) = 0x3fffffff;
}

// @ 0x00F2EB30
void V238::PushConst()
{
    if (mpEnd < mpCapacity) {
        E238* p = mpEnd++;
        if (p) p->flags = 0x80000000;
    } else {
        char tmp[0x238];
        *(int*)tmp = 0x80000000;
        ((void(__stdcall*)(void*, void*))H_f2e5d0)(mpEnd, tmp);
        ((TC0)H_dfcc40)(tmp);
    }
}

// @ 0x00F2ED20
int V238::AssignAt(void* value)
{
    int idx = *(int*)((char*)this + 0x18);
    int ret = idx;
    if (idx != 0x3fffffff) {
        E238* el = (E238*)((char*)mpBegin + idx * 0x238);
        *(int*)((char*)this + 0x18) = el->flags & 0x3fffffff;
        el->flags &= 0x7fffffff;
        void* dst = (char*)el + 4;
        if (dst) ((TC1)H_dfdff0)(dst, value);
    } else {
        char tmp[0x234];
        ((TC1)H_dfdff0)(tmp, value);
        ret = (int)((char*)mpEnd - (char*)mpBegin) / 0x238;
        PushConst();
        if (ret != 0) {
            E238* prev = (E238*)((char*)mpBegin + ret * 0x238 - 0x238);
            prev->flags &= 0xbfffffff;
        }
        E238* el = (E238*)((char*)mpBegin + ret * 0x238);
        el->flags |= 0x40000000;
        el->flags &= 0x7fffffff;
        void* dst = (char*)el + 4;
        if (dst) ((TC1)H_dfdff0)(dst, tmp + 4);
        FreeBlock(*(void**)tmp);
        ((void(__cdecl*)(void*, void*))H_dfb850)(tmp, *(void**)(tmp + 4));
        FreeBlock(*(void**)tmp);
    }
    if (*(unsigned*)((char*)this + 0x14) > (unsigned)ret)
        *(int*)((char*)this + 0x14) = ret;
    return ret;
}

// ---------------------------------------------------------------- 0x27e0
struct E27e0 { char pad[0x27e0]; };
struct V27e0 { E27e0* mpBegin; E27e0* mpEnd; E27e0* mpCapacity; };

// @ 0x00F2F2E0
int __fastcall V27e0_Erase(V27e0* self, int edx, E27e0* first, E27e0* last)
{
    E27e0* p = (E27e0*)((void*(__cdecl*)(void*, void*, void*))H_dff2b0)(last, self->mpEnd, first);
    E27e0* e = self->mpEnd;
    while (p < e) {
        ((TC0)H_dfce90)(p);
        p = (E27e0*)((char*)p + 0x27e0);
    }
    self->mpEnd = (E27e0*)((char*)self->mpEnd +
                           (((char*)last - (char*)first) / 0x27e0) * 0x27e0);
    return (int)first;
}

// @ 0x00F2F340
int __fastcall V27e8_Erase(V27e8* self, int edx, E27e8* first, E27e8* last)
{
    E27e8* p = (E27e8*)((void*(__cdecl*)(void*, void*, void*))H_dff2b0)(last, self->mpEnd, first);
    E27e8* e = self->mpEnd;
    while (p < e) {
        ((TC0)H_dfce90)((char*)p + 8);
        p = (E27e8*)((char*)p + 0x27e8);
    }
    self->mpEnd = (E27e8*)((char*)self->mpEnd +
                           (((char*)last - (char*)first) / 0x27e8) * 0x27e8);
    return (int)first;
}

// ---------------------------------------------------------------- 0x2cb0 ctor
struct PropertyList2CB0 { void ctor(); };

static void InitStr(CString* c, wchar_t* e1, wchar_t* e2)
{
    c->ctor();
    *(wchar_t**)((char*)c + 0x14) = e1;
    *(wchar_t**)((char*)c + 0x18) = e1;
    *(wchar_t**)((char*)c + 0x1c) = e2;
    *(int*)((char*)c + 0x24) = 0;
    *(int*)((char*)c + 0x28) = 0;
    *(wchar_t**)((char*)c + 0x2c) = e1;
    *(wchar_t**)((char*)c + 0x30) = e1;
    *(wchar_t**)((char*)c + 0x34) = e2;
}

// @ 0x00F2E7D0
void PropertyList2CB0::ctor()
{
    unsigned char* b = (unsigned char*)this;
    wchar_t* e1 = g_emptyW;
    wchar_t* e2 = g_emptyW2;
    *(unsigned*)b = 0x13ebcdc;
    _InterlockedExchange((volatile long*)(b + 4), 0);
    *(int*)(b + 8) = 0;
    *(int*)(b + 0x0c) = 0;
    *(int*)(b + 0x10) = 0;
    *(int*)(b + 0x14) = 0;
    *(unsigned*)b = 0x148c6c4;
    ((PropBase*)(b + 0x18))->ctor();
    *(float*)(b + 0x50) = -1.0f;
    *(float*)(b + 0x54) = 0.5f;
    *(float*)(b + 0x58) = 0.5f;
    b[0x5c] = 0;
    *(float*)(b + 0x60) = 0.0f;
    b[0x64] = 0;
    *(int*)(b + 0x78) = 0x20790816;
    InitStr((CString*)(b + 0x7c), e1, e2);
    InitStr((CString*)(b + 0xb8), e1, e2);
    InitStr((CString*)(b + 0xf4), e1, e2);
    *(int*)(b + 0x130) = 0;
    *(int*)(b + 0x134) = 0;
    *(int*)(b + 0x138) = 0;
    *(int*)(b + 0x13c) = 0;
    b[0x14c] = 0;
    *(int*)(b + 0x140) = -1;
    *(int*)(b + 0x144) = -1;
    *(int*)(b + 0x148) = -1;
    *(float*)(b + 0x150) = *(float*)0x016c8418;
    *(float*)(b + 0x154) = *(float*)0x016c841c;
    *(float*)(b + 0x158) = *(float*)0x016c8420;
    *(float*)(b + 0x15c) = *(float*)0x015ada9c;
    *(float*)(b + 0x160) = *(float*)0x015adaa0;
    *(float*)(b + 0x164) = *(float*)0x015adaa4;
    *(float*)(b + 0x168) = *(float*)0x015adaa8;
    b[0x174] = 0;
    b[0x175] = 0;
    *(float*)(b + 0x16c) = *(float*)0x01485720;
    *(float*)(b + 0x170) = *(float*)0x01485720;
    *(void**)(b + 0x178) = b + 0x190;
    *(void**)(b + 0x17c) = b + 0x190;
    *(void**)(b + 0x180) = b + 0x190 + 0xa8;
    *(int*)(b + 0x18c) = 0;
    *(int*)(b + 0x238) = 0;
    *(int*)(b + 0x250) = 0;
    *(void**)(b + 0x23c) = b + 0x254;
    *(void**)(b + 0x240) = b + 0x254;
    *(void**)(b + 0x244) = b + 0x254 + 0x29a0;
    *(int*)(b + 0x2bf4) = 0;
    *(int*)(b + 0x2bf8) = 0;
    *(int*)(b + 0x2bfc) = 0;
    *(int*)(b + 0x2c0c) = 0x400;
    *(int*)(b + 0x2c10) = 0;
    *(int*)(b + 0x2c14) = 0;
    *(int*)(b + 0x2c18) = 0;
    *(int*)(b + 0x2c24) = 0x3fffffff;
    *(int*)(b + 0x2c28) = 0x3fffffff;
    b[0x2c2c] = 0;
    b[0x2c2d] = 1;
    *(float*)(b + 0x2c30) = *(float*)0x016c8418;
    *(float*)(b + 0x2c34) = *(float*)0x016c841c;
    *(float*)(b + 0x2c38) = *(float*)0x016c8420;
    *(float*)(b + 0x2c3c) = *(float*)0x015ada9c;
    *(float*)(b + 0x2c40) = *(float*)0x015adaa0;
    *(float*)(b + 0x2c44) = *(float*)0x015adaa4;
    *(float*)(b + 0x2c48) = *(float*)0x015adaa8;
    *(float*)(b + 0x2c4c) = 0.0f;
    *(int*)(b + 0x2c50) = 0;
    *(int*)(b + 0x2c54) = 0;
    *(int*)(b + 0x2c58) = 0;
    *(int*)(b + 0x2c5c) = 0;
    *(int*)(b + 0x2c6c) = 0;
    *(int*)(b + 0x2c70) = 0;
    *(int*)(b + 0x2c74) = 0;
    *(int*)(b + 0x2c80) = 0;
    *(int*)(b + 0x2c84) = 0;
    *(int*)(b + 0x2c88) = 0;
    *(int*)(b + 0x2c94) = 0;
    *(int*)(b + 0x2c98) = 0;
    *(int*)(b + 0x2c9c) = 0;
    *(int*)(b + 0x2ca0) = -1;
    *(int*)(b + 0x2ca4) = -1;
    *(int*)(b + 0x2ca8) = 0x11;
    ((TC1i)H_f2e230)((void*)(b + 0x2c10), 0x400);
}

// @ 0x00F2EB80
struct PL {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct Owner {
    virtual void o0(); virtual void o1(); virtual void o2(); virtual void o3();
    virtual void o4(); virtual void o5(); virtual void o6(); virtual void o7();
    virtual void o8();
    virtual unsigned char o9(int arg0, PL* obj, int arg2, int arg3);
    unsigned char Create(int arg0, PL** out, int arg2, int arg3);
};

unsigned char Owner::Create(int arg0, PL** out, int arg2, int arg3)
{
    PL* obj = (PL*)((void*(__cdecl*)(unsigned, const char*, int, int, int, int))EA_Alloc)
                   (0x2cb0, "Simulator", 0, 0, 0, 0);
    if (obj) {
        ((TC0)H_6a1c40)(obj);
        obj->v0();
    }
    if (arg0 != 0) {
        if (!o9(arg0, obj, arg2, arg3)) {
            if (obj) obj->v1();
            return 0;
        }
    }
    *out = obj;
    return 1;
}

// @ 0x00F2F1B0  V238 deserialize loop
void FUN_00f2f1b0(VObj* owner, V238* vec)
{
    vec->Clear();
    unsigned count = 0;
    VObj* s = owner->V20();
    ((bool(__cdecl*)(void*, void*, int, int))H_93a780)(s->V18(), &count, 1, 0);
    ((TC1i)H_f2e230)(vec, count);
    for (unsigned i = 0; i < count; ++i) {
        char tmp[0x234];
        ((TC0)H_f2aac0)(tmp);
        ((TC1)H_f2d7e0)(tmp, owner);
        vec->AssignAt(tmp);
        char* rb = *(char**)(tmp + 0x30);
        char* re = *(char**)(tmp + 0x34);
        if (rb < re) {
            int n = (int)(re - rb - 1) / 0x34 + 1;
            for (char* p = rb + 0x1c; n--; p += 0x34) FreeBlock(*(void**)p);
        }
        FreeBlock(rb);
    }
    owner->V1c();
}

// @ 0x00F2F4F0  V534 deserialize loop
void FUN_00f2f4f0(VObj* owner, V534* vec)
{
    ((TC2)H_f2efe0)(vec, vec->mpBegin, vec->mpEnd);
    unsigned count = 0;
    VObj* s = owner->V20();
    ((bool(__cdecl*)(void*, void*, int, int))H_93a780)(s->V18(), &count, 1, 0);
    vec->set_capacity(count);
    for (unsigned i = 0; i < count; ++i) {
        char tmp[0x534];
        ((TC0)H_f2d330)(tmp);
        ((TC1)H_692f90)(tmp + 0x14, 0);
        ((TC1)H_693e10)(tmp, owner);
        E534* end = vec->mpEnd;
        if (end < vec->mpCapacity) {
            vec->mpEnd = (E534*)((char*)end + 0x534);
            if (end) ((TC1)H_dff130)(end, tmp);
        } else {
            vec->Insert(end, *(E534*)tmp);
        }
        ((TC0)H_dfce40)(tmp);
    }
    owner->V1c();
}

// @ 0x00F2F5E0  V27e0 deserialize loop
void FUN_00f2f5e0(VObj* owner, V27e0* vec)
{
    V27e0_Erase(vec, 0, vec->mpBegin, vec->mpEnd);
    unsigned count = 0;
    VObj* s = owner->V20();
    ((bool(__cdecl*)(void*, void*, int, int))H_93a780)(s->V18(), &count, 1, 0);
    ((TC1i)H_f2ee50)(vec, count);
    for (unsigned i = 0; i < count; ++i) {
        char tmp[0x27e0];
        ((TC0)H_f2d260)(tmp);
        ((TC1)H_f27430)(tmp, owner);
        E27e0* end = vec->mpEnd;
        if (end < vec->mpCapacity) {
            vec->mpEnd = (E27e0*)((char*)end + 0x27e0);
            if (end) ((TC1)H_dff1a0)(end, tmp);
        } else {
            ((TC2)H_f2f3a0)(vec, end, tmp);
        }
        ((TC0)H_dfce90)(tmp);
    }
    owner->V1c();
}

// @ 0x00F2F6C0  V27e8 deserialize loop (keyed container)
void FUN_00f2f6c0(VObj* owner, V27e8* vec)
{
    V27e8_Erase(vec, 0, vec->mpBegin, vec->mpEnd);
    unsigned count = 0;
    VObj* s = owner->V20();
    ((bool(__cdecl*)(void*, void*, int, int))H_93a780)(s->V18(), &count, 1, 0);
    vec->set_capacity(count);
    for (unsigned i = 0; i < count; ++i) {
        char tmp[0x27e8];
        ((TC0)H_f2d260)(tmp);
        int key = 0;
        VObj* s2 = owner->V20();
        ((bool(__cdecl*)(void*, void*, int, int))H_93a780)(s2->V18(), &key, 1, 0);
        owner->V1c();
        ((TC1)H_f27430)(tmp, owner);
        owner->V1c();
        *(int*)(tmp + 0x20) = key;
        ((TC2)H_dff1a0)((char*)tmp, (char*)tmp, (char*)tmp + 4);
        char* end = (char*)vec->mpEnd;
        char* pos = (char*)((void*(__cdecl*)(void*, void*, void*, int))H_ed29b0)
                              (vec->mpBegin, end, tmp + 0x20, *(unsigned char*)((char*)vec + 0x14));
        bool inserted;
        if (pos == end || *(int*)(tmp + 0x20) < *(int*)pos) {
            ((void(__cdecl*)(void*, void*))H_ed3740)(pos, tmp + 0x20);
            inserted = true;
        } else {
            inserted = false;
        }
        ((TC0)H_dfce90)(tmp + 4);
        if (!inserted) ((TC0)H_dfee80)(tmp + 4);
        ((TC0)H_dfce90)(tmp);
    }
    owner->V1c();
}
