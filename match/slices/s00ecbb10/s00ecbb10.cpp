// Slice s00ecbb10 -- Sporepedia card data / asset helpers.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------
// Out-of-line callees.
// ---------------------------------------------------------------------------
void  __fastcall FUN_00641810(void* self);          // base reset/notify (ecx=this)
void  __fastcall FUN_005ed650(void* self);          // cSPPaletteItemRollover::Destroy
void* __fastcall FUN_0080ba10(void* self);          // returns new object in eax
void* __cdecl    FUN_00f473a0(unsigned size, const char* name, int a, int b, int c, int d);

struct VObj {
    virtual void slot0(int);
    virtual void slot1();
};

struct VObj0 {
    virtual void vt0();
};

// Open container with a 4-byte gap at +8: further members spill
// (pun: same layout, different member granularity).
struct Gap24 { char a[8]; int x; };
struct Amb {
    virtual void slot0(int);
    virtual void slot1();
    Gap24 g;
    int   y;
};

struct S80 {
    char pad0[0x80];
    int  m80;
    int  m84;
};

struct S920 {
    int   m00, m04, m08;
    union {
        int   m0c;
        struct { short m0c_lo, m0e; };
    };
    int   m10;
    float m14, m18;
    int   m1c, m20, m24;
};
struct S_c8 {
    char  pad0[0xc8];
    VObj* mC8;
};

// @ 0x00ecc530
void __fastcall FUN_00ecc530(S80* s)
{
    if (s->m80 == s->m84)
        FUN_00641810(s);
}

// ---------------------------------------------------------------------------
// Vtables / globals used by the container class.
// ---------------------------------------------------------------------------
extern void* vtbl_ecb_b0;    // 0x14893b0
extern void* vtbl_ecb_9c;    // 0x148939c
extern void* vtbl_ecb_8c;    // 0x148938c
extern void* vtbl_ec6_48;    // 0x1462748
extern void* vtbl_ec6_38;    // 0x1462738

void  __fastcall FUN_00642190(void* self);
void  __fastcall FUN_00641e10(void* self);
struct TC_93db80 { void Destruct(int unlink); };
struct TC_93dd80 { unsigned char Construct(unsigned short a, unsigned short b, const void* c, unsigned d, unsigned e); };
void* __fastcall Property_GetBool_0(void* prop);
void* __fastcall Property_GetInt_0(void* prop);
void  __fastcall FUN_00eed920(void* v);
void* __cdecl    FUN_0067de30();
void* __cdecl    FUN_006a0ae0(void* a, void* b, void* c);
void* __cdecl    FUN_00806230(void* a, void* b, int c, int d, int e);
void  __cdecl    FUN_00da1f10(int a, int b, int c);
struct TC_da1f10 { void FUN(int a, int b, int c); };
void  __cdecl    operator_delete(void* p);
void* __cdecl    FUN_00645ed0(void* retbuf, void* key);
// Member-function wrappers so the call is emitted with `this` in ecx and
// the remaining argument on the stack (ret 4 shape).
struct TC_680 { void* FUN_00ecc680(void* src); };
struct TC_780 { void* FUN_00ecc780(void* src); };

extern unsigned short eastl_gEmptyString16[];
extern unsigned short eastl_gEmptyString16_end[];

struct EastlStr16 {
    unsigned short* begin;
    unsigned short* end;
    unsigned short* cap;
};

struct CCard {
    char pad0[0x78];
    char m78;
    char pad78[3];
    int  m7c;
    EastlStr16 s80;   // +0x80
};

struct TC_620 { void* FUN_00ecc620(int flags); };

// @ 0x00ecc620
void* TC_620::FUN_00ecc620(int flags)
{
    CCard* s = (CCard*)this;
    *(void**)s = &vtbl_ecb_b0;
    *(void**)((char*)s + 0x10) = &vtbl_ecb_9c;
    *(void**)((char*)s + 0x14) = &vtbl_ecb_8c;
    unsigned short* b = s->s80.begin;
    if ((((int)((char*)s->s80.cap - (char*)b)) & -2) > 2 && b != 0) {
        operator_delete(b);
    }
    FUN_00642190(s);
    if (flags & 1) {
        operator_delete(s);
    }
    return s;
}

// @ 0x00ecc680
void* TC_680::FUN_00ecc680(void* src)
{
    void* self = this;
    char* s = (char*)self;
    char* d = (char*)src;
    *(void**)s = (void*)0x1403758;
    *(int*)(s + 4) = *(int*)(d + 4);
    *(int*)(s + 8) = *(int*)(d + 8);
    *(int*)(s + 0xc) = *(int*)(d + 0xc);
    *(void**)(s + 0x10) = (void*)0x13f1ab0;
    *(void**)(s + 0x14) = (void*)0x13ec458;
    *(int*)(s + 0x18) = 0;
    *(void**)s = (void*)0x13ff648;
    *(void**)(s + 0x10) = (void*)0x1462748;
    *(void**)(s + 0x14) = (void*)0x1462738;
    VObj0* p;
    p = *(VObj0**)(d + 0x1c);
    *(void**)(s + 0x1c) = p;
    if (p) p->vt0();
    VObj0* q;
    q = *(VObj0**)(d + 0x20);
    *(void**)(s + 0x20) = q;
    if (q) q->vt0();
    *(char*)(s + 0x24) = *(char*)(d + 0x24);
    *(char*)(s + 0x25) = *(char*)(d + 0x25);
    *(char*)(s + 0x26) = *(char*)(d + 0x26);
    *(int*)(s + 0x28) = *(int*)(d + 0x28);
    *(int*)(s + 0x2c) = *(int*)(d + 0x2c);
    *(int*)(s + 0x30) = *(int*)(d + 0x30);
    *(int*)(s + 0x34) = *(int*)(d + 0x34);
    *(int*)(s + 0x38) = *(int*)(d + 0x38);
    VObj0* r;
    r = *(VObj0**)(d + 0x3c);
    *(void**)(s + 0x3c) = r;
    if (r) r->vt0();
    char* v = s + 0x40;
    char* e = v + 0x18;
    *(void**)(v + 0x10) = e;
    *(void**)(v + 4) = e;
    *(void**)v = e;
    e += 0x14;
    *(void**)(v + 8) = e;
    ((TC_da1f10*)(s + 0x40))->FUN(*(int*)(d + 0x40), *(int*)(d + 0x44), (int)d);
    *(int*)(s + 0x6c) = *(int*)(d + 0x6c);
    VObj0* t;
    t = *(VObj0**)(d + 0x70);
    *(void**)(s + 0x70) = t;
    if (t) t->vt0();
    VObj0* u;
    u = *(VObj0**)(d + 0x74);
    *(void**)(s + 0x74) = u;
    if (u) u->vt0();
    return self;
}

// @ 0x00ecc780
void* TC_780::FUN_00ecc780(void* src)
{
    CCard* s = (CCard*)this;
    ((TC_680*)this)->FUN_00ecc680(src);
    s->m78 = 0;
    *(int*)((char*)s + 0x7c) = 0;
    *(void**)s = &vtbl_ecb_b0;
    *(void**)((char*)s + 0x10) = &vtbl_ecb_9c;
    *(void**)((char*)s + 0x14) = &vtbl_ecb_8c;
    s->s80.begin = eastl_gEmptyString16;
    s->s80.end = eastl_gEmptyString16;
    s->s80.cap = eastl_gEmptyString16_end;
    return s;}

struct TC_8b0 { void* FUN_00ecc8b0(unsigned short* str); };

// @ 0x00ecc8b0
void* TC_8b0::FUN_00ecc8b0(unsigned short* str)
{
    char* s = (char*)this;
    if (*(unsigned char*)(s + 0x10) & 4)
        ((TC_93db80*)s)->Destruct(1);
    if (str != 0) {
        unsigned short* q = str;
        unsigned short* base = q + 1;
        short c;
        do { c = (short)*q; q++; } while (c != 0);
        int n = ((int)((char*)q - (char*)base)) >> 1;
        ((TC_93dd80*)s)->Construct(3, 0x18, str, 2, n + 1);
        return s;
    }
    ((TC_93dd80*)s)->Construct(3, 0x20, 0, 2, 1);
    return s;
}

struct Iter { int* node; int pad; };
struct TC_645ed0 { Iter* find(Iter* out, int* key); };

// @ 0x00ecc100
int __cdecl FUN_00ecc100(int key)
{
    Iter it;
    Iter* r = ((TC_645ed0*)0x15abdd4)->find(&it, &key);
    int* node = *(int**)r;
    if (node != *(int**)(*(char**)0x15abdd8 + *(int*)0x15abddc * 4))
        return node[1];
    return 0;
}

// @ 0x00ecc920
void __fastcall FUN_00ecc920(S920* s)
{
    s->m00 = 0;
    s->m04 = 0;
    s->m08 = 0;
    s->m0c = 0;
    s->m0e = 0;
    s->m10 = 0;
    s->m14 = 0.0f;
    s->m18 = 0.0f;
    s->m1c = 0xfffff;
    s->m20 = -1;
    s->m24 = -1;
}

// @ 0x00ecc840
bool __fastcall FUN_00ecc840(S_c8* s)
{
    void* p = FUN_00f473a0(0x5394, (const char*)0x13f6b3c, 0, 0, 0, 0);
    s->mC8 = (VObj*)(p != 0 ? FUN_0080ba10(p) : 0);
    return 1;
}

// @ 0x00ecc880
bool __fastcall FUN_00ecc880(S_c8* s)
{
    VObj* p = s->mC8;
    if (p != 0) {
        p->slot0(1);
        s->mC8 = 0;
    }
    FUN_005ed650(s);
    return 1;
}

// @ 0x00ecc7d0
void* __cdecl FUN_00ecc7d0(void* a1)
{
    if (a1 != 0) {
        char* o = (char*)a1 + 0x10;
        void** vt = *(void***)o;
        void* tgt = vt[3];
        void* r = (*(void* (__thiscall*)(void*, int))tgt)(o, 0x13d55dc8);
        if (r != 0) {
            void* mem = FUN_00f473a0(0x90, "Sporepedia/AssetData/cSPScenarioCaptainAssetData", 0, 0, 0, 0);
            void* obj = (mem != 0) ? ((TC_780*)mem)->FUN_00ecc780(r) : 0;
            (*(void(__thiscall**)(void*))(*(char**)obj + 0x50))(obj);
            return obj;
        }
    }
    return 0;
}

// @ 0x00ecc550
void __fastcall FUN_00ecc550(void* self)
{
    char* s = (char*)self;
    FUN_00641e10(self);
    char* p = *(char**)(s + 0x20);
    if (p == 0)
        return;
    void** vt = *(void***)p;
    (*(void(__thiscall**)(char*))vt[0])(p);
    int* out = 0;
    unsigned char ok = (*(unsigned char(__thiscall*)(char*, int, int**))(vt + 9))(p, 0xec2942cd, &out);
    if (ok && *(short*)((char*)out + 0x12) == 1) {
        char* b = (char*)Property_GetBool_0(out);
        if (*b) {
            *(unsigned char*)(s + 0x78) = 1;
            void* r = (*(void*(__thiscall*)(char*, char*))(*(char**)s + 0x40))(s, s + 0x80);
            FUN_00eed920(r);
        }
    }
    ok = (*(unsigned char(__thiscall*)(char*, int, int**))(vt + 9))(p, 0x5888ef41, &out);
    if (ok && *(short*)((char*)out + 0x12) == 9) {
        int* v = (int*)Property_GetInt_0(out);
        *(int*)(s + 0x7c) = *v;
    }
    (*(void(__thiscall**)(char*))(*((char**)p) + 1))(p);
}

// Stubs for the large functions (see nonmatching.txt).
// @ 0x00ecbb10
void __fastcall FUN_00ecbb10(void* self)
{
}

// @ 0x00ecc140
void __fastcall FUN_00ecc140(void* self)
{
}

// @ 0x00ecc960
void* __cdecl FUN_00ecc960(void** out)
{
    *out = 0;
    void* tmp = 0;
    char* pm = (char*)FUN_0067de30();
    if (tmp != 0) {
        char* t = (char*)tmp;
        tmp = 0;
        (*(void(__thiscall**)(char*))(*(char**)t + 4))(t);
    }
    unsigned char ok = (*(unsigned char(__thiscall*)(char*, int, int, void**))(*(char**)pm + 0x2c))(
        pm, *(int*)0x15abed8, *(int*)0x15abee0, &tmp);
    if (ok) {
        if (tmp == 0)
            goto cleanup;
        int a = 0, b = 0;
        if (FUN_006a0ae0(&a, &b, tmp)) {
            int n = a;
            if ((unsigned)b > (unsigned)n)
                goto cleanup;
            char* pv = (char*)*out;
            if (pv != 0) {
                *out = 0;
                (*(void(__thiscall**)(char*))(*(char**)pv + 4))(pv);
            }
            FUN_00806230((char*)&a, 0, -1, -1, 0);
        }
    }
cleanup:
    if (tmp != 0)
        (*(void(__thiscall**)(char*))(*(char**)tmp + 4))((char*)tmp);
    return *out;
}

// @ 0x00ecca30
void* __cdecl FUN_00ecca30()
{
    void* tmp = 0;
    char* pm = (char*)FUN_0067de30();
    if (tmp != 0) {
        char* t = (char*)tmp;
        tmp = 0;
        (*(void(__thiscall**)(char*))(*(char**)t + 4))(t);
    }
    unsigned char ok = (*(unsigned char(__thiscall*)(char*, int, int, void**))(*(char**)pm + 0x2c))(
        pm, *(int*)0x15abed8, *(int*)0x15abee0, &tmp);
    if (ok) {
        if (tmp == 0)
            goto cleanup;
        int a = 0, b = 0;
        if (FUN_006a0ae0(&a, &b, tmp)) {
            int n = b;
            if (a <= n)
                goto cleanup;
            char* v = *(char**)((char*)&a + (n + n * 2) * 0);
            (void)v;
        }
    }
cleanup:
    if (tmp != 0)
        (*(void(__thiscall**)(char*))(*(char**)tmp + 4))((char*)tmp);
    return 0;
}
