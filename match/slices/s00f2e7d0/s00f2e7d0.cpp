// Slice s00f2e7d0 -- Simulator scenario object region, part 2 (bfs2 slice 11).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

void* __cdecl EA_Alloc(size_t, const char*, int, int, const char*, int);  // 0x00F473A0
void  __cdecl EA_Delete(void*);                                           // 0x00F47380
void  __cdecl MoveA(void*, void*, void*);
void  __cdecl MoveB(void*, void*, void*);
void* __cdecl operator new(size_t, const char*, int, int, int, int);

struct CString { char pad[0x14]; void ctor(); };  // 0x006B5060
extern wchar_t g_emptyW[];
extern wchar_t g_emptyW2[];

// ---------------------------------------------------------------- 0x27e8 element / vector
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

// ---------------------------------------------------------------- 0x534 element / vector
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

// @ 0x00F2F050 (insert for 0x534 element, same shape as 0x4e0 insert)
E534* V534::Insert(E534* position, const E534& value)
{
    if (mpEnd != mpCapacity) {
        E534* pValue = (E534*)&value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        if (mpEnd)
            *(E534*)mpEnd = *(mpEnd - 1);
        for (E534* p = mpEnd - 1; p > position; --p)
            *p = *(p - 1);
        *position = *pValue;
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
        E534* pNewData = nNewSize ? (E534*)EA_Alloc(nNewSize * 0x534, "Simulator", 0, 0,
                                                    "allocator.h", 0xd1) : 0;
        MoveA(mpBegin, position, pNewData);
        MoveB(mpBegin, position, pNewData);
        MoveA(position, mpEnd, pNewData + nPrevSize + 1);
        MoveB(position, mpEnd, pNewData + nPrevSize + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            EA_Delete(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize + 1;
        mpCapacity = pNewData + nNewSize;
    }
    return position;
}

// ---------------------------------------------------------------- 0x238 element / vector
struct E238 { char pad[0x238]; };
struct V238 {
    E238* mpBegin; E238* mpEnd; E238* mpCapacity;
    void set_capacity(unsigned n);
    E238* Insert(E238* position, const E238& value);
    void Clear();
    void PushConst();
    void AssignAt(void* value);
};

// @ 0x00F2ECD0
void V238::Clear()
{
    E238* b = mpBegin;
    E238* e = mpEnd;
    MoveA(e, e, b);
    MoveB(e, e, b);
    mpEnd += ((mpEnd - mpBegin) / 0x238) * 0x238;
    *(int*)((char*)this + 0x14) = 0x3fffffff;
    *(int*)((char*)this + 0x18) = 0x3fffffff;
}

// @ 0x00F2EB30
void V238::PushConst()
{
    if (mpEnd < mpCapacity) {
        E238* p = mpEnd++;
        if (p)
            *(int*)p = 0x80000000;
    } else {
        E238 local;
        *(int*)&local = 0x80000000;
        Insert(mpEnd, local);
        *(int*)&local = 0;
    }
}

// ---------------------------------------------------------------- deserialize helpers
extern void* __cdecl ReadInt32(void* stream, void* out, int n, int flag);  // 0x0093A780
void* __cdecl GetStream(void* obj);   // vtable[6] accessor

// @ 0x00F2ED20 -- assign element by index
void V238::AssignAt(void* value)
{
    int idx = *(int*)((char*)this + 0x18);
    if (idx != 0x3fffffff) {
        E238* p = mpBegin + idx;
        *(int*)((char*)this + 0x18) = p->pad[0] & 0x3fffffff;
        *(int*)p &= 0x7fffffff;
    }
    (void)value;
}

// ---------------------------------------------------------------- 0x2cb0 property list ctor
struct PropertyListBase { void ctor(); };  // 0x006A1C40

struct PropertyList2CB0 {
    unsigned char mData[0x2cb0];
    void ctor();   // 0x00F2E7D0
};

// @ 0x00F2E7D0
void PropertyList2CB0::ctor()
{
    unsigned char* b = mData;
    (*(void**)b) = 0;
    ((PropertyListBase*)(b + 0x18))->ctor();
    *(float*)(b + 0x50) = -1.0f;
    *(float*)(b + 0x54) = 0.5f;
    *(float*)(b + 0x58) = 0.5f;
    b[0x5c] = 0; *(float*)(b+0x60) = 0.0f; b[0x64] = 0;
    *(int*)(b+0x78) = 0x20790816;
    ((CString*)(b+0x7c))->ctor();
    *(wchar_t**)(b+0x90) = g_emptyW;
    *(wchar_t**)(b+0x94) = g_emptyW;
    *(wchar_t**)(b+0x98) = g_emptyW2;
    *(int*)(b+0x9c) = 0; *(int*)(b+0xa0) = 0;
    *(wchar_t**)(b+0xa8) = g_emptyW;
    *(wchar_t**)(b+0xac) = g_emptyW;
    *(wchar_t**)(b+0xb0) = g_emptyW2;
    ((CString*)(b+0xb8))->ctor();
    *(wchar_t**)(b+0xcc) = g_emptyW;
    *(wchar_t**)(b+0xd0) = g_emptyW;
    *(wchar_t**)(b+0xd4) = g_emptyW2;
    *(int*)(b+0xdc) = 0; *(int*)(b+0xe0) = 0;
    *(wchar_t**)(b+0xe4) = g_emptyW;
    *(wchar_t**)(b+0xe8) = g_emptyW;
    *(wchar_t**)(b+0xec) = g_emptyW2;
    ((CString*)(b+0xf4))->ctor();
    *(wchar_t**)(b+0x108) = g_emptyW;
    *(wchar_t**)(b+0x10c) = g_emptyW;
    *(wchar_t**)(b+0x110) = g_emptyW2;
    *(int*)(b+0x118) = 0; *(int*)(b+0x11c) = 0;
    *(wchar_t**)(b+0x120) = g_emptyW;
    *(wchar_t**)(b+0x124) = g_emptyW;
    *(wchar_t**)(b+0x128) = g_emptyW2;
    *(int*)(b+0x130) = 0; *(int*)(b+0x134) = 0;
    *(int*)(b+0x138) = 0; *(int*)(b+0x13c) = 0;
    b[0x14c] = 0;
    *(int*)(b+0x140) = -1; *(int*)(b+0x144) = -1; *(int*)(b+0x148) = -1;
    *(float*)(b+0x150) = 0.0f; *(float*)(b+0x154) = 0.0f; *(float*)(b+0x158) = 0.0f;
    *(float*)(b+0x15c) = 0.0f; *(float*)(b+0x160) = 0.0f; *(float*)(b+0x164) = 0.0f;
    *(float*)(b+0x168) = 0.0f;
    b[0x174] = 0; b[0x175] = 0;
    *(float*)(b+0x16c) = 1.0f; *(float*)(b+0x170) = 1.0f;
    *(int*)(b+0x18c) = 0;
    *(void**)(b+0x178) = b + 0x190;
    *(void**)(b+0x17c) = b + 0x190;
    *(void**)(b+0x180) = b + 0x190 + 0xa8;
    *(int*)(b+0x238) = 0;
    *(int*)(b+0x250) = 0;
    *(void**)(b+0x23c) = b + 0x254;
    *(void**)(b+0x240) = b + 0x254;
    *(void**)(b+0x244) = b + 0x254 + 0x29a0;
    *(int*)(b+0x2bf4) = 0; *(int*)(b+0x2bf8) = 0; *(int*)(b+0x2bfc) = 0;
    *(int*)(b+0x2c0c) = 0x400;
    *(int*)(b+0x2c10) = 0; *(int*)(b+0x2c14) = 0; *(int*)(b+0x2c18) = 0;
    *(int*)(b+0x2c24) = 0x3fffffff; *(int*)(b+0x2c28) = 0x3fffffff;
    b[0x2c2c] = 0; b[0x2c2d] = 1;
    *(int*)(b+0x2ca0) = 0; *(int*)(b+0x2ca4) = 0;
    *(int*)(b+0x2ca8) = 0x11;
    ((V238*)(b+0x2ca0))->set_capacity(0x400);
}

// @ 0x00F2EB80
struct PL {
    PL();
    virtual void AddRef();
    virtual void Release();
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
    PL* obj = new ("Simulator",0,0,0,0) PL();
    if (obj)
        obj->AddRef();
    if (arg0 != 0) {
        if (!o9(arg0, obj, arg2, arg3)) {
            if (obj)
                obj->Release();
            return 0;
        }
    }
    *out = obj;
    return 1;
}

// ---------------------------------------------------------------- deserialize loops (stubs)
void Serialize27e8(V27e8* v, void* owner) { (void)v; (void)owner; }   // @ 0x00F2F6C0
void Serialize27e0_vec(void* v, void* owner) { (void)v; (void)owner; } // @ 0x00F2F5E0
void Serialize238(V238* v, void* owner) { (void)v; (void)owner; }      // @ 0x00F2F1B0
void Serialize534(V534* v, void* owner) { (void)v; (void)owner; }      // @ 0x00F2F4F0
void Erase27e0(void* first, void* last) { (void)first; (void)last; }   // @ 0x00F2F2E0
void Erase27e8(void* first, void* last) { (void)first; (void)last; }   // @ 0x00F2F340
