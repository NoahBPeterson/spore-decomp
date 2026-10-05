// Slice s007cf310 (w2g5 slice 8).  Region: /O2 /MD /Gy /EHsc /TP /arch:SSE2.
// eastl vector/map instances, small factories, and EA::IO serialization helpers.
#include "types.h"

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
extern "C" void* __cdecl EAlloc(uint32_t, const char*, int, int, const char*, int);
extern "C" void  __cdecl EFree(void*);

// ---------------------------------------------------------------- extern callees
extern "C" void __cdecl FUN_004b5440();
extern "C" void __cdecl FUN_004b54b0(void*);
void WriteUint16(void*, const uint16_t&, int, int);   // 0x0093a9d0
void WriteUint32(void*, const uint32_t&, int, int);   // 0x0093aa70
void WriteFloat32(void*, const float&, int, int);     // 0x0093aa70
void WriteByte(void*, const uint8_t&, int);           // 0x0093a9a0  (operator<<)

// ===========================================================================
// 0x007cf310  Vec16::insert(pos,n,value)  (partial)
// ===========================================================================
struct Vec16 {
    void* mpBegin;   // +0
    void* mpEnd;     // +4
    void* mpCap;     // +8
    char  pad0c[4];
    void* mpInline;  // +0x10
    void insert(void* pos, uint32_t n, const void* value);
};
void Vec16::insert(void* pos, uint32_t n, const void* value)
{
    (void)pos; (void)n; (void)value;
}

// ===========================================================================
// 0x007cf4b0  V16::clear
// ===========================================================================
struct V16 {
    void* begin;
    void* end;
    void* cap;
    void Destruct(void* b, void* e);   // 0x007cefd0 external thiscall
    void clear();
};
void V16::clear()
{
    Destruct(begin, end);
    if (begin)
        EFree(begin);
}

// ===========================================================================
// 0x007cf4e0  Big2::dtor (partial)
// ===========================================================================
struct Big2 {
    char pad00[4];
    void* m04;
    char pad08[0x34 - 0x08];
    void* m34;
    void* m38;
    char pad3c[0x4c - 0x3c];
    void* m4c;
    void dtor();
};
void Big2::dtor()
{
    FUN_004b5440();
    void* p = m4c;
    if (p)
        EFree(p);
    if (m34)
        EFree(m34);
    if (m04)
        EFree(m04);
}

// ===========================================================================
// 0x007cf5d0  createBig
// ===========================================================================
struct Big {
    int f0, f4, f8, fc;
    char p10[0xc];
    int f1c, f20, f24;
    char p28[0xc];
    int f34, f38, f3c;
    char p40[0xc];
    int f4c, f50, f54;
    char p58[0xc];
    int f64, f68, f6c;
    char p70[8];
};
Big** __fastcall createBig(Big** out)
{
    Big* p = (Big*)EAlloc(0x78, "App", 0, 0, 0, 0);
    if (p) {
        p->f0 = 0; p->f4 = 0; p->f8 = 0; p->fc = 0;
        p->f1c = 0; p->f20 = 0; p->f24 = 0;
        p->f34 = 0; p->f38 = 0; p->f3c = 0;
        p->f4c = 0; p->f50 = 0; p->f54 = 0;
        p->f64 = 0; p->f68 = 0; p->f6c = 0;
        *out = p;
        return out;
    }
    *out = 0;
    return out;
}

// ===========================================================================
// 0x007cf630  Vec8::resize
// ===========================================================================
struct P8 { uint32_t a, b; };
struct Vec8 {
    P8* mpBegin;
    P8* mpEnd;
    P8* mpCap;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void insert(P8* pos, uint32_t n, const P8& value);   // 0x007cf030 external
    void erase(P8* first, P8* last);                     // 0x00d018d0 external
    void resize(uint32_t n);
};
void Vec8::resize(uint32_t n)
{
    if (n > size()) {
        P8 z;
        z.a = 0;
        z.b = 0;
        insert(mpEnd, n - size(), z);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// ===========================================================================
// 0x007cf690  map find-or-insert result (partial)
// ===========================================================================
struct ObjX3 { int pad[4]; };
struct MapX {
    char pad0[4];
    void* mpBegin;   // +4
    char pad8[0x14 - 8];
    bool mb14;       // +0x14
    char pad15[0x20 - 0x15];
    char* mpTree;
    ObjX3* findOrInsert(ObjX3** out, uint32_t* key);
};
extern "C" void* __cdecl FUN_00ec4ac0(void*, void*, void*, int);
extern "C" void* __cdecl FUN_007cf570(void*, void*);
ObjX3* MapX::findOrInsert(ObjX3** out, uint32_t* key)
{
    void* end = mpBegin;
    void* r = FUN_00ec4ac0(*(void**)this, end, key, mb14);
    if (r != end) {
        if (*((uint32_t*)r + 1) <= key[1] && (key[1] != *((uint32_t*)r + 1) || *(uint32_t*)r <= *key)) {
            *out = (ObjX3*)r;
            *((uint8_t*)out + 4) = 0;
            return (ObjX3*)out;
        }
    }
    void* ins = FUN_007cf570(r, key);
    *out = (ObjX3*)ins;
    *((uint8_t*)out + 4) = 1;
    return (ObjX3*)out;
}

// ===========================================================================
// 0x007cf760  map insert (partial)
// ===========================================================================
extern "C" void* __cdecl FUN_007cde30(void*, void*, void*);
extern "C" void  __cdecl FUN_007cede0(void*, void*, void*);
struct MapY {
    char pad[0x14];
    void insertPair(void* pos, void* value);
};
void MapY::insertPair(void* pos, void* value)
{
    void* p = *(void**)((char*)this + 4);
    if (p != *(void**)((char*)this + 8)) {
        *(uint32_t*)p = *((uint32_t*)p - 4);
        return;
    }
    int cap = (int)((char*)p - *(void**)this) >> 4;
    if (cap == 0) cap = 1; else cap *= 2;
    void* nb = EAlloc(cap << 4, "App", 0, 0, 0, 0);
    FUN_007cde30(*(void**)this, pos, nb);
    FUN_007cede0(*(void**)this, pos, nb);
    (void)value;
    *(void**)this = nb;
}

// ===========================================================================
// 0x007cf8d0  map slot setter (partial)
// ===========================================================================
struct MapZ {
    char pad0[8];
    uint32_t* mpBegin;    // +8
    uint32_t* mpEnd;      // +0xc
    char pad10[0x1c - 0x10];
    int m1c;
    int m20;
    bool setSlot(int handle, uint32_t* rec);
};
extern "C" void* __cdecl FUN_007cf630_dummy();
bool MapZ::setSlot(int handle, uint32_t* rec)
{
    if (handle != m1c)
        return false;
    uint32_t u = rec[0];
    int i = rec[10], a = rec[2], idx = rec[8];
    if (a != 0 && i != 0) {
        if (mpBegin == mpEnd)
            return false;
        if (i != (int)(mpEnd - mpBegin))
            return false;
        if (mpBegin[idx * 2] == 0)
            m20 = m20 + 1;
        mpBegin[idx * 2] = a;
        mpBegin[idx * 2 + 1] = u;
        return true;
    }
    if (mpBegin != mpEnd) {
        if (i != (int)(mpEnd - mpBegin))
            return false;
        if (mpBegin[idx * 2] != 0)
            m20 = m20 - 1;
        mpBegin[idx * 2] = 0;
        mpBegin[idx * 2 + 1] = 0;
    }
    return true;
}

// ===========================================================================
// 0x007cf9b0  ObjX2::clear (partial)
// ===========================================================================
struct ObjX2 {
    int f0;   // +0
    char pad[0x7c];
    void clear();
};
void __fastcall clear9b0(ObjX2* p)
{
    p->f0 = 0;
}

// ===========================================================================
// 0x007cfa90  PtrX::reset
// ===========================================================================
struct ObjX { void destroy(); };   // 0x007cf4e0 external thiscall
struct PtrX {
    ObjX* p;
    void reset();
};
void PtrX::reset()
{
    ObjX* q = p;
    if (q) {
        q->destroy();
        EFree(q);
    }
    p = 0;
}

// ===========================================================================
// 0x007cfac0  checkPtr
// ===========================================================================
bool __fastcall checkPtr(ObjX2** pp)
{
    if ((*pp)->f0 != 0)
        (*pp)->clear();
    return (*pp)->f0 == 0;
}

// ===========================================================================
// 0x007cfb40  map try-insert (partial)
// ===========================================================================
struct MapW {
    char pad0[4];
    void* mpEnd;    // +4
    char pad8[0x10 - 8];
    void* mpCap;    // +0x10
    void* tryInsert(void* pos, void* value);
};
extern "C" void __cdecl FUN_007cf760_dummy();
void* MapW::tryInsert(void* pos, void* value)
{
    void* p = mpEnd;
    int idx = (int)((char*)pos - *(char**)this) >> 4;
    if (pos == p && p != mpCap) {
        mpEnd = (char*)p + 0x10;
        *(uint32_t*)p = ((uint32_t*)value)[0];
        *((uint32_t*)p + 1) = ((uint32_t*)value)[1];
        *((uint32_t*)p + 2) = ((uint32_t*)value)[2];
        return (char*)*(void**)this + idx * 0x10;
    }
    FUN_007cf760_dummy();
    return (char*)*(void**)this + idx * 0x10;
}

// ===========================================================================
// 0x007cfbb0  InnerC::clear (partial)
// ===========================================================================
struct InnerC {
    char pad[0xa0];
    void clear();
};
extern "C" void* __cdecl FUN_007cee40(void*, void*, void*);
extern "C" void  __cdecl FUN_007cefd0(void*, void*);
extern "C" void  __cdecl FUN_006130e0(void*, void*);
extern "C" void  __cdecl FUN_00533500(void*, void*);
__declspec(noinline) void InnerC::clear()
{
    *(uint32_t*)this = 0;
}

// ===========================================================================
// 0x007cfc60  W::clear
// ===========================================================================
struct W {
    InnerC* m;
    void clear();
};
void W::clear()
{
    m->clear();
}

// ===========================================================================
// 0x007cfc70  map find-or-insert result (partial)
// ===========================================================================
extern "C" void* __cdecl FUN_007c8160(void*, void*, void*, int);
extern "C" void* __cdecl FUN_007cfb40_dummy();
struct MapV {
    char pad[0x14];
    void* findOrInsert2(void* out, void* key);
};
void* MapV::findOrInsert2(void* out, void* key)
{
    void* end = *(void**)((char*)this + 4);
    void* r = FUN_007c8160(*(void**)this, end, key, *((uint8_t*)this + 0x14));
    if (r != end) {
        if (*((uint32_t*)r + 1) <= *((uint32_t*)key + 1) &&
            (*((uint32_t*)key + 1) != *((uint32_t*)r + 1) || *(uint32_t*)r <= *(uint32_t*)key)) {
            *(void**)out = r;
            *((uint8_t*)out + 4) = 0;
            return out;
        }
    }
    void* ins = FUN_007cfb40_dummy();
    *(void**)out = ins;
    *((uint8_t*)out + 4) = 1;
    return out;
}

// ===========================================================================
// 0x007cfcd0  SP::CompileToPropertyModel (partial)
// ===========================================================================
extern "C" void* __cdecl FUN_007cfc70_dummy();
extern "C" void* __cdecl SP_PropertyManager();
void CompileToPropertyModel(int a, int* b, int* c)
{
    (void)a; (void)b; (void)c;
    FUN_007cfc70_dummy();
    SP_PropertyManager();
}

// ===========================================================================
// 0x007d00e0  cCityVisualizer::AllegianceUpdate (partial)
// ===========================================================================
struct CityViz {
    char pad[0x400];
    void allegianceUpdate(int a, int b);
};
void CityViz::allegianceUpdate(int a, int b)
{
    (void)a; (void)b;
}

// ===========================================================================
// 0x007d01d0  W2::f
// ===========================================================================
struct InnerD {
    char pad[0x40];
    void g(int, int);
};
struct W2 {
    InnerD* m;
    void f(int a, int b);
};
void W2::f(int a, int b)
{
    m->g(a, b);
}

// ===========================================================================
// 0x007d01f0  serialization
// ===========================================================================
struct IStream {
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual void Write(void*, int);   // slot 14 (0x38)
};
void* Ser1F0(IStream* s, char* p)
{
    WriteUint16(s, (uint16_t)*(uint16_t*)p, 1, 0);
    WriteFloat32(s, (float)*(float*)(p + 0x10), 1, 0);
    s->Write(p + 0x14, 0x24);
    s->Write(p + 4, 0xc);
    return s;
}

// ===========================================================================
// 0x007d0250  serialize float vector
// ===========================================================================
void* Ser250(IStream* s, int* vec)
{
    int n = (vec[1] - vec[0]) >> 2;
    WriteUint32(s, (uint32_t)n, 1, 0);
    for (uint32_t i = 0; i < (uint32_t)n; i++)
        WriteFloat32(s, (float)*(float*)(vec[0] + i * 4), 1, 0);
    return s;
}

// ===========================================================================
// 0x007d02b0  serialize pair vector
// ===========================================================================
void* Ser2B0(IStream* s, int* vec)
{
    int n = (vec[1] - vec[0]) >> 3;
    WriteUint32(s, (uint32_t)n, 1, 0);
    for (uint32_t i = 0; i < (uint32_t)n; i++) {
        int* e = (int*)(vec[0] + i * 8);
        WriteUint32(s, (uint32_t)e[0], 1, 0);
        WriteByte(s, (uint8_t)*((uint8_t*)e + 4), 1);
        WriteByte(s, (uint8_t)*((uint8_t*)e + 5), 1);
    }
    return s;
}

// ===========================================================================
// 0x007d0360  serialize object
// ===========================================================================
void Ser360(IStream* s, char* p)
{
    s->Write(p, 8);
    Ser250(s, (int*)(p + 8));
    WriteFloat32(s, (float)*(float*)(p + 0x1c), 1, 0);
    WriteUint32(s, (uint32_t)*(uint32_t*)(p + 0x24), 1, 0);
    WriteByte(s, (uint8_t)*(uint8_t*)(p + 0x28), 1);
}
