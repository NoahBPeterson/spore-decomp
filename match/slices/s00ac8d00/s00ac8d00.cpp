// Slice s00ac8d00 - Spore gameplay: tribe/city helpers, EASTL range/copy helpers,
// cLocomotionRequest ctor, locomotion tuning loader.  (no PDB names)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int   uint32;
typedef unsigned short uint16;
typedef unsigned char  byte;

// ---------------------------------------------------------------------------
struct RCObj {                       // refcounted, vtable slot0 AddRef, slot1 Release
    virtual void AddRef();
    virtual void Release();
};
extern "C" void WriteUint32(void* stream, void* pValue, int one, int zero);  // 0x93aa70
extern "C" void operator_delete(void* p);                                    // 0xf47380
struct Pair {                        // 0xc-byte element (vtable, byte, refcounted ptr)
    void* mpVtbl;                    // +0x00  (0x145a158)
    byte  mb4;                       // +0x04
    char  pad5[3];
    RCObj* mp8;                      // +0x08
};
struct CGVis { void SetCity(int c); };
struct CGSub { void FUN_00d57a60(void* v); };
struct CGSub2 { void FUN_00d61880(); };
struct CCity { void* GetCivilization(int a); };

// "tribe world" owner object with +0xa4, +0x20/+0x24 (sphere vector), +0xbc
struct CT {
    char  pad0[0x20];
    float* mpSphereBegin;     // +0x20
    float* mpSphereEnd;       // +0x24
    char  pad1[0xa4 - 0x28];
    void* mpA4;               // +0xa4
    char  pad2[0xbc - 0xa8];
    void* mpBC;               // +0xbc
    void  FUN_00ac8d00(int city, int a);
    void  FUN_00ac8d40(int a);
    bool  FUN_00ac8d60(int a);
    bool  FUN_00ac8d80(float* p);
    bool  FUN_00ac8df0(float* p);
    void  FUN_00ac8e90();
};

// ===========================================================================
// @ 0x00ac8d00
// ===========================================================================
void CT::FUN_00ac8d00(int city, int a)
{
    void* g = mpA4;
    if (g && *(int*)((char*)g + 0xaf0) == city) {
        void* u = ((CCity*)city)->GetCivilization(a);
        ((CGSub*)g)->FUN_00d57a60(u);
    }
}

// ===========================================================================
// @ 0x00ac8d40
// ===========================================================================
void CT::FUN_00ac8d40(int a)
{
    void* g = mpA4;
    if (g && *(int*)((char*)g + 0xaf0) == a) {
        ((CGSub2*)g)->FUN_00d61880();
    }
}

// ===========================================================================
// @ 0x00ac8d60
// ===========================================================================
bool CT::FUN_00ac8d60(int a)
{
    int r = 0;
    if (mpA4) {
        r = *(int*)((char*)mpA4 + 0xaf0);
        if (r == a) return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00ac8d80
// ===========================================================================
bool CT::FUN_00ac8d80(float* p)
{
    float* pf = mpSphereBegin;
    float* end = mpSphereEnd;
    if (pf != end) {
        float x = p[0], y = p[1], z = p[2];
        do {
            float dx = x - pf[0];
            float dy = y - pf[1];
            float dz = z - pf[2];
            float sum = dx * dx + dy * dy + dz * dz;
            if (pf[4] > sum) return false;
            pf += 5;
        } while (pf != end);
    }
    return true;
}

// ===========================================================================
// @ 0x00ac8df0
// ===========================================================================
bool CT::FUN_00ac8df0(float* p)
{
    float* pf = mpSphereBegin;
    float* end = mpSphereEnd;
    if (pf != end) {
        float x = p[0], y = p[1], z = p[2];
        do {
            float dx = x - pf[0];
            float dy = y - pf[1];
            float dz = z - pf[2];
            float sum = dx * dx + dy * dy + dz * dz;
            if (pf[3] >= sum) return true;
            pf += 5;
        } while (pf != end);
    }
    return false;
}

// ===========================================================================
// @ 0x00ac8e90
// ===========================================================================
void CT::FUN_00ac8e90()
{
    int saved = *(int*)((char*)mpA4 + 0xaf0);
    ((CGVis*)mpA4)->SetCity(0);
    ((CGVis*)mpA4)->SetCity(saved);
}

// ===========================================================================
// @ 0x00ac8f00
// ===========================================================================
extern "C" void* FUN_006bb5d0(void);                          // 0x6bb5d0
struct CSC { void FUN_00695b40(void* a, void* b, const wchar_t* c); };  // 0x695b40
extern int DAT_0164dc58;

void* FUN_00ac8f00(void* out, int* p, int a, int p4, int p5)
{
    if (p) {
        char ok = (*(char (__thiscall*)(void*, int, void**))((char*)*(void**)p + 0x24))(p, a, (void**)&p);
        if (ok) {
            short t = *(short*)((char*)p + 0x12);
            if (t != 0x30 && t != 0x10) {
                void* q = FUN_006bb5d0();
                *(int*)out = *(int*)q;
                ((int*)out)[1] = ((int*)q)[1];
                return out;
            }
            if (*(byte*)((char*)p + 0x10) & 0x30) {
                void* q = (void*)*(int*)p;
                *(int*)out = *(int*)q;
                ((int*)out)[1] = ((int*)q)[1];
                return out;
            }
            void* q = (void*)(-(int)(t != 0) & (int)p);
            *(int*)out = *(int*)q;
            ((int*)out)[1] = ((int*)q)[1];
            return out;
        }
    }
    *(int*)out = p4;
    ((int*)out)[1] = p5;
    return out;
}

// ===========================================================================
// @ 0x00ac8fa0
// ===========================================================================
int FUN_00ac8fa0(int* p, int a, int b)
{
    if (p) {
        char ok = (*(char (__thiscall*)(void*, int, void**))((char*)*(void**)p + 0x24))(p, a, (void**)&p);
        if (ok) {
            short t = *(short*)((char*)p + 0x12);
            if (t != 10 && t != 0x10) {
                return DAT_0164dc58;
            }
            if (*(byte*)((char*)p + 0x10) & 0x30) {
                return *(int*)*(int*)p;
            }
            return *(int*)(-(int)(t != 0) & (int)p);
        }
    }
    return b;
}

// ===========================================================================
// @ 0x00ac9040
// ===========================================================================
struct CEachElem { int a; char pad[0x1c]; };   // stride 0x20
extern "C" void SP_cVarListSerializer_ctor(void* self, void* a, void* b, int c);  // 0x692f90
extern "C" char SP_cVarListSerializer_Serialize(void* self, void* p);              // 0x692900

void FUN_00ac9040(int* self, int* arr)
{
    int count = (arr[1] - arr[0]) >> 5;
    int* q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
    WriteUint32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &count, 1, 0);
    int* end = (int*)arr[1];
    for (int* it = (int*)arr[0]; it != end; it += 8) {
        int v = *it;
        q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
        WriteUint32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &v, 1, 0);
        (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
        char srl[0xa14];
        SP_cVarListSerializer_ctor(srl, it + 1, (void*)0x1566000, 0x1a80d26);
        SP_cVarListSerializer_Serialize(srl, self);
        (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
    }
    (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
}

// ===========================================================================
// @ 0x00ac9110
// ===========================================================================
extern "C" void FUN_00695b40(void* a, void* b, const wchar_t* c);   // 0x695b40
bool FUN_00ac9110(void* a, int* arr)
{
    int end = arr[1];
    for (int it = arr[0]; it != end; it += 0x20) {
        if (it != -4) {
            ((CSC*)a)->FUN_00695b40((void*)(it + 4), (void*)0x1566000, L"cCastInfo");
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00ac9150
// ===========================================================================
void FUN_00ac9150(int* self, int* arr)
{
    int count = (arr[1] - arr[0]) / 0xc;
    int* q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
    WriteUint32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &count, 1, 0);
    int* end = (int*)arr[1];
    for (int* it = (int*)arr[0]; it != end; it += 3) {
        (*(void (__thiscall*)(int*, int*))((char*)*(void**)it + 4))(it, self);
    }
    (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
}

// ===========================================================================
// ===========================================================================
struct S28 {
    int   a;          // +0x00
    float b;          // +0x04
    float c;          // +0x08
    float d;          // +0x0c
    short e;          // +0x10
    byte  f;          // +0x12
    char  pad13;      // +0x13
    float g;          // +0x14
    int   h;          // +0x18
    int   i;          // +0x1c
    int   j;          // +0x20
    int   k;          // +0x24
    byte  l;          // +0x28
    void assign(const S28* s);
    void* FUN_00ac9200(S28* s);
};
void S28::assign(const S28* s)
{
    a = s->a;
    b = s->b;
    c = s->c;
    d = s->d;
    e = s->e;
    f = s->f;
    g = s->g;
    h = s->h;
    i = s->i;
    j = s->j;
    k = s->k;
    l = s->l;
}
// @ 0x00ac9200
void* S28::FUN_00ac9200(S28* s)
{
    assign(s);
    return this;
}

// ===========================================================================
// @ 0x00ac93c0
// ===========================================================================
extern "C" char FUN_00ac0730(void* a, void* b);               // 0xac0730
void FUN_00ac93c0(int base, int start, int idx, int* value)
{
    int i = idx;
    while (start < i) {
        int parent = (i - 1) >> 1;
        void* b;
        if (value == 0) b = 0;
        else b = (char*)value + 0x120;
        int e = *(int*)(base + parent * 4);
        void* a;
        if (e == 0) a = 0;
        else a = (char*)e + 0x120;
        if (!FUN_00ac0730(a, b)) break;
        RCObj* pv = *(RCObj**)(base + parent * 4);
        RCObj* pi = *(RCObj**)(base + i * 4);
        if (pv != pi) {
            if (pv) pv->AddRef();
            *(RCObj**)(base + i * 4) = pv;
            if (pi) pi->Release();
        }
        i = parent;
    }
    RCObj* pv = *(RCObj**)(base + i * 4);
    if (value != (int*)pv) {
        if (value) ((RCObj*)value)->AddRef();
        *(int**)(base + i * 4) = value;
        if (pv) pv->Release();
    }
    if (value) ((RCObj*)value)->Release();
}

// ===========================================================================
// @ 0x00ac9480
// ===========================================================================
struct RefPtr {
    RCObj* mp;
    RefPtr* assign(RefPtr* src);
};
RefPtr* RefPtr::assign(RefPtr* src)
{
    RCObj* p = src->mp;
    RCObj* old = mp;
    if (p != old) {
        if (p) p->AddRef();
        mp = p;
        if (old) old->Release();
    }
    return this;
}

// ===========================================================================
// @ 0x00ac94c0
// ===========================================================================
void* FUN_00ac94c0(void** out, Pair* src, Pair* end, void* base)
{
    *out = base;
    for (; src != end; src = (Pair*)((char*)src + 0xc)) {
        Pair* d = (Pair*)*out;
        if (d) {
            d->mpVtbl = (void*)0x145a158;
            d->mb4 = src->mb4;
            RCObj* p = (RCObj*)src->mp8;
            d->mp8 = p;
            if (p) p->AddRef();
        }
        *out = (char*)*out + 0xc;
    }
    return out;
}

// ===========================================================================
// @ 0x00ac9510
// ===========================================================================
void FUN_00ac9510(char* d, char* end, char* s)
{
    for (; d != end; d += 0xc) {
        d[4] = s[4];
        RCObj* p = *(RCObj**)(s + 8);
        RCObj* old = *(RCObj**)(d + 8);
        if (p != old) {
            if (p) p->AddRef();
            *(RCObj**)(d + 8) = p;
            if (old) old->Release();
        }
    }
}

// ===========================================================================
// @ 0x00ac9560
// ===========================================================================
void FUN_00ac9560(char* d, int n, char* s)
{
    for (; n != 0; --n) {
        if (d) {
            *(void**)d = (void*)0x145a158;
            d[4] = s[4];
            RCObj* p = *(RCObj**)(s + 8);
            *(RCObj**)(d + 8) = p;
            if (p) p->AddRef();
        }
        d += 0xc;
    }
}

// ===========================================================================
// @ 0x00ac95a0
// ===========================================================================
char* FUN_00ac95a0(char* s, char* end, char* d)
{
    if (s == end) return d;
    do {
        if (d) {
            *(void**)d = (void*)0x145a158;
            d[4] = s[4];
            RCObj* p = *(RCObj**)(s + 8);
            *(RCObj**)(d + 8) = p;
            if (p) p->AddRef();
        }
        s += 0xc;
        d += 0xc;
    } while (s != end);
    return d;
}

// ===========================================================================
// @ 0x00ac95f0
// ===========================================================================
void** FUN_00ac95f0(void** out, RCObj*** src, RCObj*** end, void* base)
{
    *out = base;
    for (; src != end; ++src) {
        RCObj** d = (RCObj**)*out;
        if (d) {
            RCObj* p = (RCObj*)*src;
            *d = p;
            if (p) p->AddRef();
        }
        *out = (char*)*out + 4;
    }
    return out;
}

// ===========================================================================
// @ 0x00ac9630
// ===========================================================================
void FUN_00ac9630(RCObj** p, RCObj** end, RCObj*** src)
{
    for (; p != end; ++p) {
        RCObj* s = (RCObj*)*src;
        RCObj* old = *p;
        if (s != old) {
            if (s) s->AddRef();
            *p = s;
            if (old) old->Release();
        }
    }
}

// ===========================================================================
// @ 0x00ac9680
// ===========================================================================
void FUN_00ac9680(RCObj** p, int n, RCObj*** src)
{
    for (; n != 0; --n) {
        if (p) {
            RCObj* s = (RCObj*)*src;
            *p = s;
            if (s) s->AddRef();
        }
        ++p;
    }
}

// ===========================================================================
// @ 0x00ac96b0
// ===========================================================================
struct S2c { char data[0x2c]; };
char* FUN_00ac96b0(char* p, char* end, char* d)
{
    if (p != end) {
        do {
            if (d) {
                S2c* s = (S2c*)p;
                S2c* t = (S2c*)d;
                *(int*)t = *(int*)s;
                *(float*)((char*)t + 4) = *(float*)((char*)s + 4);
                *(float*)((char*)t + 8) = *(float*)((char*)s + 8);
                *(float*)((char*)t + 0xc) = *(float*)((char*)s + 0xc);
                *(short*)((char*)t + 0x10) = *(short*)((char*)s + 0x10);
                *(byte*)((char*)t + 0x12) = *(byte*)((char*)s + 0x12);
                *(float*)((char*)t + 0x14) = *(float*)((char*)s + 0x14);
                *(int*)((char*)t + 0x18) = *(int*)((char*)s + 0x18);
                *(int*)((char*)t + 0x1c) = *(int*)((char*)s + 0x1c);
                *(int*)((char*)t + 0x20) = *(int*)((char*)s + 0x20);
                *(int*)((char*)t + 0x24) = *(int*)((char*)s + 0x24);
                *(byte*)((char*)t + 0x28) = *(byte*)((char*)s + 0x28);
            }
            p += 0x2c;
            d += 0x2c;
        } while (p != end);
        return d;
    }
    return d;
}

// ===========================================================================
// @ 0x00ac9740
// ===========================================================================
char* FUN_00ac9740(char* p, char* end, char* d)
{
    if (p == end) return d;
    do {
        d[4] = p[4];
        RCObj* s = *(RCObj**)(p + 8);
        RCObj* old = *(RCObj**)(d + 8);
        if (s != old) {
            if (s) s->AddRef();
            *(RCObj**)(d + 8) = s;
            if (old) old->Release();
        }
        p += 0xc;
        d += 0xc;
    } while (p != end);
    return d;
}

// ===========================================================================
// @ 0x00ac97a0
// ===========================================================================
RCObj** FUN_00ac97a0(RCObj** last, RCObj** first, RCObj** d)
{
    if (first == last) return d;
    do {
        RCObj* s = *(RCObj**)(first - 1);
        RCObj* old = d[-1];
        --first;
        --d;
        if (s != old) {
            if (s) s->AddRef();
            *d = s;
            if (old) old->Release();
        }
    } while (first != last);
    return d;
}

// ===========================================================================
// @ 0x00ac97f0
// ===========================================================================
char* FUN_00ac97f0(char* p, char* end, char* d)
{
    if (p == end) return d;
    do {
        char v = p[-8];
        p -= 0xc;
        d -= 0xc;
        d[4] = v;
        RCObj* s = *(RCObj**)(p + 8);
        RCObj* old = *(RCObj**)(d + 8);
        if (s != old) {
            if (s) s->AddRef();
            *(RCObj**)(d + 8) = s;
            if (old) old->Release();
        }
    } while (p != end);
    return d;
}

// ===========================================================================
// @ 0x00ac9850
// ===========================================================================
extern float DAT_0167a390, DAT_0167a394, DAT_0167a398;
struct cLocomotionRequest {
    char data[0x74];
    cLocomotionRequest();
};
cLocomotionRequest::cLocomotionRequest()
{
    *(int*)this = 0;
    *(int*)((char*)this + 4) = 0;
    *(int*)((char*)this + 8) = 0;
    *(float*)((char*)this + 0x14) = DAT_0167a390;
    *(float*)((char*)this + 0x18) = DAT_0167a394;
    *(float*)((char*)this + 0x1c) = DAT_0167a398;
    *(float*)((char*)this + 0x20) = 1.0f;
    *(int*)((char*)this + 0x24) = 0;
    *(byte*)((char*)this + 0x4c) = 0;
    *(float*)((char*)this + 0x50) = 0.0f;
    *(float*)((char*)this + 0x54) = 0.0f;
    *(float*)((char*)this + 0x58) = 0.0f;
    *(float*)((char*)this + 0x60) = 2.0f;
    *(float*)((char*)this + 0x64) = 0.9f;
    *(int*)((char*)this + 0x5c) = 0;
    *(float*)((char*)this + 0x68) = 3.402823466e38f;
    *(float*)((char*)this + 0x6c) = 0.0f;
    *(int*)((char*)this + 0x70) = 0;
}

// ===========================================================================
// ===========================================================================
extern byte  DAT_01565cfc;
extern int   DAT_01565ce0, DAT_01565ce4, DAT_01565ce8;
extern int   DAT_01565cec, DAT_01565cf0, DAT_01565cf8;
extern int   DAT_01565d54, DAT_01565d58, DAT_01565d5c, DAT_01565d60;
extern int   DAT_01565d00, DAT_01565d04, DAT_01565d08;
extern int   DAT_015d9c6c, DAT_015d9c68;

static int FUN_00ac98e0_readfloat(int* p, int id, int def)
{
    int v;
    if (!p) return def;
    if (!(*(char (__thiscall*)(void*, int, void**))((char*)*(void**)p + 0x24))(p, id, (void**)&p)) return def;
    short t = *(short*)((char*)p + 0x12);
    if (t != 0xd && t != 0x10) { v = DAT_015d9c6c; return v; }
    if (*(byte*)((char*)p + 0x10) & 0x30) return *(int*)*(int*)p;
    return *(int*)(-(int)(t != 0) & (int)p);
}

// @ 0x00ac98e0
void FUN_00ac98e0(int* p)
{
    DAT_01565cfc = 1;
    DAT_01565ce0 = FUN_00ac98e0_readfloat(p, 0x54ba6b0, 0x40a00000);
    DAT_01565ce4 = FUN_00ac98e0_readfloat(p, 0x4ff9582, 0x41200000);
    DAT_01565ce8 = FUN_00ac98e0_readfloat(p, 0x4ffccf5, 0x41f00000);
    {
        float a = 0.5f;
        int out[2];
        FUN_00ac8f00(out, p, 0x5008313, 0, *(int*)&a);
        DAT_01565d54 = out[0];
        DAT_01565d58 = out[1];
    }
    DAT_01565cec = FUN_00ac98e0_readfloat(p, 0x5008412, 0x42c80000);
    {
        int v;
        if (!p) v = 5;
        else if (!(*(char (__thiscall*)(void*, int, void**))((char*)*(void**)p + 0x24))(p, 0x500849f, (void**)&p)) v = 5;
        else {
            short t = *(short*)((char*)p + 0x12);
            if (t != 10 && t != 0x10) v = DAT_0164dc58;
            else if (*(byte*)((char*)p + 0x10) & 0x30) v = *(int*)*(int*)p;
            else v = *(int*)(-(int)(t != 0) & (int)p);
        }
        DAT_01565cf0 = v;
    }
    DAT_01565cf8 = FUN_00ac98e0_readfloat(p, 0x508af89, 0x41f00000);
    {
        float a = 100.0f, b = 150.0f;
        int out[2];
        FUN_00ac8f00(out, p, 0x509beb7, *(int*)&a, *(int*)&b);
        DAT_01565d5c = out[0];
        DAT_01565d60 = out[1];
    }
    {
        int v;
        if (!p) v = 100;
        else if (!(*(char (__thiscall*)(void*, int, void**))((char*)*(void**)p + 0x24))(p, 0x5c8390d, (void**)&p)) v = 100;
        else {
            short t = *(short*)((char*)p + 0x12);
            if (t != 9 && t != 0x10) v = DAT_015d9c68;
            else if (*(byte*)((char*)p + 0x10) & 0x30) v = *(int*)*(int*)p;
            else v = *(int*)(-(int)(t != 0) & (int)p);
        }
        DAT_01565d00 = v;
    }
    {
        int v;
        if (!p) v = 10;
        else if (!(*(char (__thiscall*)(void*, int, void**))((char*)*(void**)p + 0x24))(p, 0x68dc104, (void**)&p)) v = 10;
        else {
            short t = *(short*)((char*)p + 0x12);
            if (t != 9 && t != 0x10) v = DAT_015d9c68;
            else if (*(byte*)((char*)p + 0x10) & 0x30) v = *(int*)*(int*)p;
            else v = *(int*)(-(int)(t != 0) & (int)p);
        }
        DAT_01565d04 = v;
    }
    {
        int v;
        if (!p) v = 4;
        else if (!(*(char (__thiscall*)(void*, int, void**))((char*)*(void**)p + 0x24))(p, 0x511f4a9, (void**)&p)) v = 4;
        else {
            short t = *(short*)((char*)p + 0x12);
            if (t != 10 && t != 0x10) v = DAT_0164dc58;
            else if (*(byte*)((char*)p + 0x10) & 0x30) v = *(int*)*(int*)p;
            else v = *(int*)(-(int)(t != 0) & (int)p);
        }
        DAT_01565d08 = v;
    }
}

// ===========================================================================
// @ 0x00ac9d90
// ===========================================================================
struct CAnim2 { void Release(); };
struct Vec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void FUN_00ac9d90();
};
void Vec::FUN_00ac9d90()
{
    for (void** p = mpBegin; p < mpEnd; ++p) {
        if (*p) ((CAnim2*)*p)->Release();
    }
    void* base = mpBegin;
    if (base && *(int*)((char*)base - 4) != 0) {
        operator_delete(base);
    }
}

// ===========================================================================
// @ 0x00ac9dd0
// ===========================================================================
extern "C" void FUN_00ac9310(int a, int b, bool c);            // 0xac9310
void FUN_00ac9dd0(int a, int b)
{
    FUN_00ac9310(a, b, false);
}

// ===========================================================================
// @ 0x00ac9df0
// ===========================================================================
void FUN_00ac9df0(int* self, int* p)
{
    int v = *(int*)((char*)p + 0xc);
    int* q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
    WriteUint32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &v, 1, 0);
    int* root = *(int**)((char*)p + 4);
    int* node = (int*)*root;
    int* slot = root;
    if (!node) {
        slot = root + 1;
        while (*slot == 0) ++slot;
        node = (int*)*slot;
    }
    int* end = (int*)root[*(int*)((char*)p + 8)];
    while (node != end) {
        q = (int*)(*(void* (__thiscall*)(int*))((char*)*(void**)self + 0x20))(self);
        int nv = *node;
        WriteUint32((void*)(*(void* (__thiscall*)(int*))((char*)*(void**)q + 0x18))(q), &nv, 1, 0);
        (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
        char srl[0xa14];
        SP_cVarListSerializer_ctor(srl, node + 1, (void*)0x15661a8, 0x1a80d26);
        SP_cVarListSerializer_Serialize(srl, self);
        (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
        node = (int*)node[0x1a];
        while (!node) {
            node = (int*)slot[1];
            ++slot;
        }
    }
    (*(void (__thiscall*)(int*))((char*)*(void**)self + 0x1c))(self);
}

// ===========================================================================
// @ 0x00ac9ef0
// ===========================================================================
bool FUN_00ac9ef0(void* a, int* p)
{
    int* root = *(int**)((char*)p + 4);
    int node = *root;
    int* slot = root;
    if (!node) {
        slot = root + 1;
        while (*slot == 0) ++slot;
        node = *slot;
    }
    int end = root[*(int*)((char*)p + 8)];
    while (node != end) {
        if (node + 4 != 0) {
            ((CSC*)a)->FUN_00695b40((void*)(node + 4), (void*)0x15661a8, L"tAnimalStage");
        }
        node = *(int*)(node + 0x68);
        while (!node) {
            node = slot[1];
            ++slot;
        }
    }
    return 1;
}
