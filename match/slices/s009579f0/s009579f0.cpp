// Slice s009579f0 -- EA::UTFWin UI image table + WindowMgr display/message plumbing.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include <intrin.h>
#include <xmmintrin.h>

typedef unsigned int   uint;
typedef unsigned char  uchar;

// ---- raw offset accessors ----
#define B(p)     ((char*)(p))
#define I8(p,o)  (*(char*)((char*)(p)+(o)))
#define U8(p,o)  (*(unsigned char*)((char*)(p)+(o)))
#define U16(p,o) (*(unsigned short*)((char*)(p)+(o)))
#define I32(p,o) (*(int*)((char*)(p)+(o)))
#define U32(p,o) (*(unsigned*)((char*)(p)+(o)))
#define PTR(p,o) (*(void**)((char*)(p)+(o)))
#define F32(p,o) (*(float*)((char*)(p)+(o)))

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedIncrement, _InterlockedExchange)

void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);  // 0x00F473A0
void  __cdecl operator_delete__(void*) throw();                                     // 0x00F47380

int  __cdecl EA_atexit(void*);                       // 0x011E07EF atexit
void* __cdecl memcpy_impl(void*, const void*, unsigned);  // 0x011E0744

// ---- thiscall / fastcall externals ----
struct Ext {
    void* ctor(int, int);                                    // 0x009222A0 Mutex::Mutex
    int   Lock(const void*);                                 // 0x009221B0 Mutex::Lock
    void  tp3(float* out, const float* in);                  // 0x0095EEB0 TransformPoint3
    void  tp4(float* out, const float* in);                  // 0x0095F1C0 TransformPoint4
    void  bb80(void*);                                       // 0x0095BB80
    void  bd60(void*, void*);                                // 0x0095BD60
    void  Splice1(void*);                                    // 0x0099A9D0 XmlReaderState::Splice
    void  ba90(void*);                                       // 0x0095BA90
    void* ba70(void*);                                       // 0x0095BA70
    void  ea0();                                             // 0x00961AE0
    void  r2db_dtor();                                       // 0x00952F80 Renderable2DBuilder::~Renderable2DBuilder
    void  iba0();                                            // 0x00951BA0
};
int __fastcall Mutex_Unlock(void*);                          // 0x00922270

// ---- virtual-object view (offsets 0x00..0x7c) ----
struct VTab {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c(int);
    virtual void  v10(int, int);
    virtual void  v14();
    virtual void  v18(int, int, void*);
    virtual void  v1c();
    virtual char  v20(void*);
    virtual void  v24();
    virtual void  v28();
    virtual void  v2c();
    virtual void  v30();
    virtual void  v34();
    virtual void  v38();
    virtual void  v3c();
    virtual void  v40();
    virtual void  v44();
    virtual void  v48();
    virtual void  v4c();
    virtual void  v50();
    virtual void  v54();
    virtual void  v58(int, int);
    virtual void  v5c();
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual void  v6c();
    virtual void  v70();
    virtual char  v74(void*, int);
    virtual void  v78(void*, int);
    virtual void  v7c();
};

// single-slot view (offset 0x18 = index 6) for the 2-arg shape
struct VS6 {
    virtual void  a0(); virtual void  a1(); virtual void  a2();
    virtual void  a3(); virtual void  a4(); virtual void  a5();
    virtual char  f(void*, void*);
};

// ---- UI::Image (0x2c bytes) ----
struct UIImage {
    void* vtbl;                  // +0x00
    void* p1;                    // +0x04
    int   f8;                    // +0x08
    float f0c, f10, f14, f18;    // +0x0c
    int   f1c, f20, f24, f28;    // +0x1c
    UIImage* Image(void* obj, int a, int b, float c, float d, float e, float f, int h); // 0x009579F0
};

struct SimpleVec { void DoInsertValue(unsigned* pos, const unsigned& v); };  // 0x004558A0

// ---- image-table manager ----
struct ImageTable {
    char      _m[0x30];
    unsigned* begin;             // +0x30
    unsigned* end;               // +0x34
    unsigned* cap;               // +0x38
    void Add(void* obj, uchar k);    // 0x00957BB0
};

// ---- WindowMgr / window plumbing (thiscall + stack args) ----
// tag at +8 (the original writes [esp+0x10] and passes esp+8): lead[0x10] put it at +0x10 and the
// APC handler read garbage (hybrid crash at 0x959bd7, 2026-10-12)
struct APCData { char lead[8]; int tag; int p2; void* p3; };

struct W {
    void     PostAPC(int a, void* b);            // 0x00957D40
    void     d90(void* a);                       // 0x00957D90
    char*    db0(int idx);                       // 0x00957DB0
    unsigned dd0(void* target);                  // 0x00957DD0
    char*    e70(int idx);                       // 0x00957E70
    void     e90(int idx, void* arg);            // 0x00957E90
    void     ed0(unsigned mask, char set);       // 0x00957ED0
    void     ff0(void* obj);                     // 0x00957FF0
    void     x070(float* pt);                    // 0x00958070
    void     x0b0(void* target);                 // 0x009580B0
    void     x0e0(char* node);                   // 0x009580E0
    char     x500(void* obj, int a);             // 0x00958500
    void     ComputeClip(float* out, void* node);// 0x00958150
    void     Plot(int param);                    // 0x009586F0
    void     m7d0(char* node);                   // 0x009587D0
    void     m820(char* node);                   // 0x00958820
    void     m860(char* node);                   // 0x00958860
    void     m8c0(char* node);                   // 0x009588C0
    void     DispatchMsgToWindow(int p2, char* p3, int p4); // 0x009589F0
};

// ---- free functions (0-stack-arg thiscall == __fastcall(void*)) ----
char  __fastcall Fn00957c40(void* self);     // 0x00957C40
void  __fastcall Fn00957fa0(void* self);     // 0x00957FA0
void  __fastcall Fn00958110(void* self);     // 0x00958110
void  __cdecl    Fn00958570(void* a, int* b, int* c);   // 0x00958570
void  __fastcall DumpDisplayList(void* self);            // 0x00958640
char  __cdecl    Fn00958920(int* self, void* p2, char* p3, char p4, unsigned p5); // 0x00958920
void* __cdecl    GetGlobalImageTable();                  // 0x00957B00
void* __fastcall Fn00957f50(void* self);                 // 0x00957F50
void  __cdecl    ProcessPendingTextures();               // 0x00957D30

// ===========================================================================
// @ 0x009579F0  UI::Image::Image
// ===========================================================================
UIImage* UIImage::Image(void* obj, int a, int b, float c, float d, float e, float f, int h)
{
    vtbl = (void*)0x144064c;
    _InterlockedExchange((volatile long*)&f28, 0);
    p1 = obj;
    if (obj) ((VTab*)obj)->v00();
    f0c = c;
    f10 = d;
    f14 = e;
    f1c = a;
    f20 = b;
    f24 = h;
    f18 = f;
    return this;
}

// ===========================================================================
// @ 0x00957A60  Fn00957a60
// ===========================================================================
void** __cdecl Fn00957a60(int a, int b)
{
    unsigned* g = (unsigned*)0x166b138;
    if ((*g & 1) == 0) {
        *g |= 1;
        *(int*)0x154edfc = a;
        *(int*)0x154ee00 = b;
        *(int*)0x154ee04 = 0;
    }
    return (void**)0x154edf0;
}

// ===========================================================================
// @ 0x00957AA0  Fn00957aa0
// ===========================================================================
UIImage* __fastcall Fn00957aa0(UIImage* self)
{
    self->vtbl = (void*)0x144064c;
    _InterlockedExchange((volatile long*)&self->f28, 0);
    self->p1 = 0;
    return self;
}

// ===========================================================================
// @ 0x00957AC0  Fn00957ac0
// ===========================================================================
void* __stdcall Fn00957ac0(int a, int b)
{
    UIImage* p = (UIImage*)operator new(0x2c, "UTFWin/Image", 0, 0, 0, 0);
    if (p) {
        p->vtbl = (void*)0x144064c;
        _InterlockedExchange((volatile long*)&p->f28, 0);
        p->p1 = 0;
        return p;
    }
    return 0;
}

// ===========================================================================
// @ 0x00957B00  EA::UTFWin::GetGlobalImageTable
// ===========================================================================
void* __cdecl GetGlobalImageTable()
{
    void* r = *(void**)0x166b130;
    if (r == 0) {
        if ((*(unsigned*)0x166b188 & 1) == 0) {
            *(unsigned*)0x166b188 |= 1;
            ((Ext*)0x166b140)->ctor(0, 1);
            *(int*)0x166b170 = 0;
            *(int*)0x166b174 = 0;
            *(int*)0x166b178 = 0;
            EA_atexit((void*)0x13c1110);
        }
        r = (void*)0x166b140;
        *(void**)0x166b130 = r;
    }
    return r;
}

// ===========================================================================
// @ 0x00957BB0  ImageTable::Add
// ===========================================================================
void ImageTable::Add(void* obj, uchar k)
{
    ((Ext*)this)->Lock((const void*)0x14405d0);
    unsigned v = (unsigned)obj + (unsigned)k;
    unsigned* end = this->end;
    if (end < this->cap) {
        this->end = end + 1;
        if (end) *end = v;
    } else {
        ((SimpleVec*)((char*)this + 0x30))->DoInsertValue(end, v);
    }
    ((VTab*)obj)->v00();
    Mutex_Unlock(this);
}

// ===========================================================================
// @ 0x00957C20  Fn00957c20
// ===========================================================================
void __cdecl Fn00957c20(int a, int b)
{
    ((ImageTable*)GetGlobalImageTable())->Add((void*)a, (uchar)b);
}

// ===========================================================================
// @ 0x00957C40  Fn00957c40
// ===========================================================================
char __fastcall Fn00957c40(void* self)
{
    ((Ext*)self)->Lock((const void*)0x14405d0);
    int* src = *(int**)(B(self) + 0x30);
    int* end = *(int**)(B(self) + 0x34);
    char result = 0;
    if (src != end) {
        result = 1;
        *(int**)(B(self) + 0x34) = src;
    }
    Mutex_Unlock(self);
    return result;
}

// ===========================================================================
// @ 0x00957D30  EA::UTFWin::ProcessPendingTextures
// ===========================================================================
void __cdecl ProcessPendingTextures()
{
    Fn00957c40(GetGlobalImageTable());
}

// ===========================================================================
// @ 0x00957D40  EA::UTFWin::WindowMgr::PostAPC
// ===========================================================================
void W::PostAPC(int a, void* b)
{
    APCData d;
    d.tag = 0x74d2e9;
    if (b) ((VTab*)b)->v00();
    d.p2 = a;
    d.p3 = b;
    ((VTab*)this)->v18(0, 0, &d);
}

// ===========================================================================
// @ 0x00957D90  Fn00957d90
// ===========================================================================
void W::d90(void* a)
{
    ((VTab*)this)->v18(0, 0, a);
}

// ===========================================================================
// @ 0x00957DB0  Fn00957db0
// ===========================================================================
char* W::db0(int idx)
{
    char* p = (char*)PTR(this, 0x68c + idx * 0x28);
    if (p) return p + 4;
    return 0;
}

// ===========================================================================
// @ 0x00957DD0  Fn00957dd0
// ===========================================================================
unsigned W::dd0(void* target)
{
    unsigned result = 0;
    unsigned bit = 1;
    char* p = B(this) + 0x6b4;
    int n = 2;
    do {
        for (int k = 0; k < 5; k++) {
            void* f = *(void**)(p + k * 0x28 - 0x28);
            void* v = f ? (char*)f + 4 : 0;
            if (v == target) result |= bit;
            bit += bit;
        }
        p += 0xc8;
    } while (--n);
    return result;
}

// ===========================================================================
// @ 0x00957E70  Fn00957e70
// ===========================================================================
char* W::e70(int idx)
{
    char* p = (char*)PTR(this, 0x694 + idx * 0x28);
    if (p) return p + 4;
    return 0;
}

// ===========================================================================
// @ 0x00957E90  Fn00957e90
// ===========================================================================
void W::e90(int idx, void* arg)
{
    void* stored = PTR(this, 0x694 + idx * 0x28);
    void* v = arg ? (char*)arg - 4 : 0;
    if (stored == v) {
        ((VTab*)this)->v58(idx, 0);
    }
}

// ===========================================================================
// @ 0x00957ED0  Fn00957ed0
// ===========================================================================
void W::ed0(unsigned mask, char set)
{
    U32(this, 0xd0) = U32(this, 0xd0) & ~mask;
    if (set) U32(this, 0xd0) = U32(this, 0xd0) | mask;
}

// ===========================================================================
// @ 0x00957F50  EA::UTFWin::WindowMgr::GetMainWindow
// ===========================================================================
void* __fastcall Fn00957f50(void* self)
{
    void* p = PTR(self, 4);
    if (p) return (char*)p + 4;
    return 0;
}

// ===========================================================================
// @ 0x00957FA0  Fn00957fa0
// ===========================================================================
void __fastcall Fn00957fa0(void* self)
{
    void* n = PTR(self, 0x6b4);
    if (n != 0) {
        int v;
        do {
            v = I32(n, 0xa8);
            if (v != 0) break;
            n = PTR(n, 0x38);
        } while (n != 0);
        if (I32(self, 0xc4) != v) {
            I32(self, 0xc4) = v;
            void* o = PTR(self, 0xb8);
            if (o) ((VTab*)o)->v0c(v);
        }
    }
}

// ===========================================================================
// @ 0x00957FF0  Fn00957ff0
// ===========================================================================
void W::ff0(void* obj)
{
    void* old = PTR(this, 0xb8);
    if (obj != old) {
        if (obj) ((VTab*)obj)->v00();
        PTR(this, 0xb8) = obj;
        if (old) ((VTab*)old)->v04();
    }
    if (obj && I32(this, 0xc4) != 0) {
        ((VTab*)PTR(this, 0xb8))->v0c(I32(this, 0xc4));
    }
}

// ===========================================================================
// @ 0x00958070  Fn00958070
// ===========================================================================
void W::x070(float* pt)
{
    void* o = PTR(this, 0xb8);
    if (o) {
        int a = _mm_cvtss_si32(_mm_load_ss(&pt[0]));
        int b = _mm_cvtss_si32(_mm_load_ss(&pt[1]));
        ((VTab*)o)->v10(a, b);
    }
}

// ===========================================================================
// @ 0x009580B0  Fn009580b0
// ===========================================================================
void W::x0b0(void* target)
{
    void* n = PTR(this, 0x6b4);
    if (n != 0) {
        do {
            if (n == target) { Fn00957fa0(this); return; }
            n = *(void**)((char*)n + 0x38);
        } while (n != 0);
    }
}

// ===========================================================================
// @ 0x009580E0  Fn009580e0
// ===========================================================================
void W::x0e0(char* node)
{
    if (I32(node, 0x24) == 0 && I8(this, 0x25) == 0) {
        int edx = I32(this, 0x1c);
        char* base = B(this) + 0x18;
        node += 0x20;
        *(int*)(node + 4) = edx;
        *(char**)node = base;
        *(char**)(base + 4) = node;
        char* c = *(char**)(node + 4);
        *(char**)c = node;
    }
}

// ===========================================================================
// @ 0x00958110  Fn00958110
// ===========================================================================
void __fastcall Fn00958110(void* self)
{
    if (I8(self, 0x25) != 0) return;
    char* H = B(self) + 0x18;
    I8(self, 0x25) = 1;
    while (*(char**)(H + 4) != H) {
        char* edx = *(char**)(H + 4);
        char* edi = *(char**)(edx + 4);
        char* esi = *(char**)(B(self) + 0x1c);
        *(char**)edi = H;
        edi = *(char**)(H + 4);
        edi = *(char**)(edi + 4);
        *(char**)(H + 4) = edi;
        if (edx != H) {
            *(void**)(edx + 4) = 0;
            *(void**)edx = 0;
        }
        *(void**)(esi + 4) = 0;
    }
}

// ===========================================================================
// @ 0x00958150  WM::ComputeClip
// ===========================================================================
void W::ComputeClip(float* out, void* node)
{
    float xmin = -10000.0f, ymin = -10000.0f, xmax = 10000.0f, ymax = 10000.0f;
    for (; node != 0; node = PTR(node, 0x38)) {
        if ((U32(node, 0x2c) & 0x400) != 0) {
            float w = F32(node, 0x90) - F32(node, 0x88);
            float h = F32(node, 0x94) - F32(node, 0x8c);
            float pxmin, pymin, pxmax, pymax;
            if (w == 0.0f || h == 0.0f) {
                pxmin = pymin = pxmax = pymax = 0.0f;
            } else {
                void* M = B(node) + 0x14c;
                if (I32(node, 0x18c) < 2) {
                    float i[4] = {0, 0, 0, 0}, o[4];
                    ((Ext*)M)->tp3(o, i);
                    float i2[4] = {w, h, 0, 0}, o2[4];
                    ((Ext*)M)->tp3(o2, i2);
                    pxmin = o[0] < o2[0] ? o[0] : o2[0];
                    pymin = o[1] < o2[1] ? o[1] : o2[1];
                    pxmax = o[0] > o2[0] ? o[0] : o2[0];
                    pymax = o[1] > o2[1] ? o[1] : o2[1];
                } else {
                    float p[4] = {0, 0, 0, 0}, a[4], b[4], c[4], d[4];
                    ((Ext*)M)->tp4(a, p);
                    p[0] = w; p[1] = h; p[2] = 0; p[3] = 0; ((Ext*)M)->tp4(b, p);
                    p[0] = w; p[1] = 0; ((Ext*)M)->tp4(c, p);
                    p[0] = 0; p[1] = h; ((Ext*)M)->tp4(d, p);
                    pxmin = a[0]; if (b[0] < pxmin) pxmin = b[0]; if (c[0] < pxmin) pxmin = c[0]; if (d[0] < pxmin) pxmin = d[0];
                    pymin = a[1]; if (b[1] < pymin) pymin = b[1]; if (c[1] < pymin) pymin = c[1]; if (d[1] < pymin) pymin = d[1];
                    pxmax = a[0]; if (b[0] > pxmax) pxmax = b[0]; if (c[0] > pxmax) pxmax = c[0]; if (d[0] > pxmax) pxmax = d[0];
                    pymax = a[1]; if (b[1] > pymax) pymax = b[1]; if (c[1] > pymax) pymax = c[1]; if (d[1] > pymax) pymax = d[1];
                }
            }
            if (xmax <= pxmin || pxmax <= xmin || ymax <= pymin || pymax <= ymin) {
                xmin = 0; ymin = 0; xmax = 0; ymax = 0;
            } else {
                if (xmin < pxmin) xmin = pxmin;
                if (ymin < pymin) ymin = pymin;
                if (pxmax < xmax) xmax = pxmax;
                if (pymax < ymax) ymax = pymax;
            }
        }
        if ((U8(node, 0x30) & 2) == 0) break;
    }
    out[0] = xmin;
    out[1] = ymin;
    out[2] = xmax;
    out[3] = ymax;
}

// ===========================================================================
// @ 0x00958500  Fn00958500
// ===========================================================================
char W::x500(void* obj, int a)
{
    char result = 0;
    if (obj) ((VTab*)obj)->v00();
    void* saved = PTR(this, 0x688);
    PTR(this, 0x688) = 0;
    if (obj) {
        if (((VTab*)this)->v74(obj, a)) {
            ((VTab*)this)->v78(obj, 0);
            result = 1;
        }
    }
    PTR(this, 0x688) = saved;
    if (obj) ((VTab*)obj)->v04();
    return result;
}

// ===========================================================================
// @ 0x00958570  Fn00958570
// ===========================================================================
void __cdecl Fn00958570(void* pa, int* b, int* c)
{
    int param_1 = (int)pa;
    int zero = 0;
    while ((int*)b[1] != b) {
        int* piVar1 = (int*)*b;
        *(int**)(*piVar1 + 4) = b;
        *b = *(int*)*b;
        if (piVar1 != b) {
            piVar1[1] = zero;
            *piVar1 = zero;
        }
        int* piVar2 = (int*)piVar1[2];
        int iVar3;
        if (piVar1[7] == zero && piVar1[5] == zero) {
            iVar3 = *piVar2;
            if (iVar3 != param_1 && *(unsigned short*)(piVar2 + 4) < *(unsigned short*)(iVar3 + 0x12)) {
                *(unsigned short*)(iVar3 + 0x12) = *(unsigned short*)(piVar2 + 4);
            }
            int* piVar4 = (int*)piVar2[1];
            iVar3 = *piVar2;
            *piVar4 = iVar3;
            *(int**)(iVar3 + 4) = piVar4;
            *piVar2 = zero;
            piVar2[1] = zero;
            piVar2[1] = c[1];
            *piVar2 = (int)c;
            c[1] = (int)piVar2;
            *(int**)piVar2[1] = piVar2;
            piVar1[1] = c[1];
            *piVar1 = (int)c;
            c[1] = (int)piVar1;
            *(int**)piVar1[1] = piVar1;
        } else {
            *(char*)((int)piVar1 + 0xd) = *(char*)((int)piVar2 + 0xd);
            piVar1[2] = piVar2[2];
            *(char*)((int)piVar2 + 0xd) = (char)zero;
            int* puVar5 = (int*)piVar2[1];
            piVar2[1] = (int)piVar1;
            *puVar5 = (int)piVar1;
            piVar1[1] = (int)puVar5;
            *piVar1 = (int)piVar2;
            if (c != piVar2) {
                iVar3 = *piVar2;
                piVar1 = (int*)piVar2[1];
                *(int**)(iVar3 + 4) = piVar1;
                *piVar1 = iVar3;
                puVar5 = (int*)c[1];
                *puVar5 = (int)piVar2;
                c[1] = (int)piVar2;
                piVar2[1] = (int)puVar5;
                *piVar2 = (int)c;
            }
        }
    }
}

// ===========================================================================
// @ 0x00958640  EA::UTFWin::`anonymous_namespace'::DumpDisplayList
// ===========================================================================
void __fastcall DumpDisplayList(void* self)
{
    if (I8(self, 0x58) == 0) return;
    I8(self, 0x58) = 0;
    if (I8(self, 0x59) != 0) {
        Fn00958570(B(self) + 0xa0, (int*)(B(self) + 0x5c), (int*)(B(self) + 0x64));
        return;
    }
    char* piVar1 = B(self) + 0x5c;
    ((Ext*)(B(self) + 0xa0))->Splice1(piVar1);
    for (char* puVar2 = *(char**)(B(self) + 0xa0); puVar2 != B(self) + 0xa0; puVar2 = *(char**)puVar2) {
        if (*(void**)(puVar2 + 8) != 0 && *(char*)(puVar2 + 0xc) == 0) {
            ((Ext*)(*(char**)(puVar2 + 8) + 0x18))->ba90(puVar2 + 0x18);
        }
        *(void**)(puVar2 + 8) = 0;
        *(char*)(puVar2 + 0xd) = 1;
        *(char*)(puVar2 + 0xc) = 0;
    }
    char* piVar3 = *(char**)(piVar1 + 0);
    if (piVar3 != piVar1) {
        char* piVar4 = *(char**)(B(self) + 0x68);
        char* piVar5 = *(char**)(B(self) + 0x60);
        *(char**)piVar4 = piVar3;
        *(char**)(piVar3 + 4) = piVar4;
        *(char**)piVar5 = B(self) + 0x64;
        *(char**)(B(self) + 0x68) = piVar5;
        *(char**)piVar1 = piVar1;
        *(char**)(B(self) + 0x60) = piVar1;
    }
}

// ===========================================================================
// @ 0x009586F0  EA::UTFWin::WindowMgr::Plot
// ===========================================================================
void W::Plot(int param)
{
    char local[0x3c34];
    ((Ext*)(local + 0xc))->bb80(local + 0xc);
    ((Ext*)(B(this) + 0x28))->Lock((const void*)0x1440688);
    ProcessPendingTextures();
    DumpDisplayList(this);
    Mutex_Unlock(B(this) + 0x28);
    ((Ext*)(B(this) + 0x70))->Lock((const void*)0x1440688);
    ((Ext*)(local + 0x10))->bd60(B(this) + 0xa0, (void*)param);
    Mutex_Unlock(B(this) + 0x70);
    ((Ext*)(local + 0x84))->r2db_dtor();
    ((Ext*)(local + 0x60))->iba0();
}

// ===========================================================================
// @ 0x00958780  EA::UTFWin::WindowMgr::DebugDumpDisplayList
// ===========================================================================
void __fastcall DebugDumpDisplayList(void* self)
{
    ((Ext*)(B(self) + 0x28))->Lock((const void*)0x1440688);
    char pending = I8(self, 0x58);
    if (pending == 0) {
        Mutex_Unlock(B(self) + 0x28);
        return;
    }
    ((Ext*)(B(self) + 0x70))->Lock((const void*)0x1440688);
    DumpDisplayList(self);
    Mutex_Unlock(B(self) + 0x70);
    Mutex_Unlock(B(self) + 0x28);
}

// ===========================================================================
// @ 0x009587D0  Fn009587d0
// ===========================================================================
void W::m7d0(char* node)
{
    void** piVar2 = (void**)(*(char**)(B(this) + 0x20));
    if ((char*)piVar2 == node + 0x18) {
        I8(this, 0x24) = 1;
        void** piVar1 = (void**)piVar2[1];
        void*  iVar3 = *piVar2;
        *piVar1 = iVar3;
        *(void**)((char*)iVar3 + 4) = piVar1;
        *piVar2 = 0;
        piVar2[1] = 0;
        *(void**)(B(this) + 0x20) = iVar3;
        *(void**)(node + 0x1c) = 0;
        return;
    }
    void* a = *(void**)(node + 0x1c);
    void* c = *(void**)(node + 0x18);
    *(void**)a = c;
    *(void**)((char*)c + 4) = a;
    *(void**)(node + 0x18) = 0;
    *(void**)(node + 0x1c) = 0;
    *(void**)(node + 0x1c) = 0;
}

// ===========================================================================
// @ 0x00958820  Fn00958820
// ===========================================================================
void W::m820(char* node)
{
    if ((U8(node, 0x30) & 0x14) == 0) {
        U8(node, 0x30) = U8(node, 0x30) | 0x10;
        if (I32(node, 0x78) == 0) {
            Fn00958110(this);
            return;
        }
        char* base = B(this) + 8;
        void** p = (void**)(node + 0x10);
        void* t = *(void**)(base + 4);
        p[1] = t;
        *p = base;
        *(void**)(base + 4) = p;
        void** c = (void**)p[1];
        *c = p;
    }
}

// ===========================================================================
// @ 0x00958860  Fn00958860
// ===========================================================================
void W::m860(char* node)
{
    if ((U8(node, 0x30) & 0x40) == 0) {
        if (I32(node, 0x78) != 0 && I32(node, 0x24) == 0 && I8(this, 0x25) == 0) {
            char* base = B(this) + 0x18;
            void** p = (void**)(node + 0x20);
            void* t = *(void**)(base + 4);
            p[1] = t;
            *p = base;
            *(void**)(base + 4) = p;
            void** c = (void**)p[1];
            *c = p;
        }
        char* iVar2 = *(char**)(node + 0x38);
        U8(node, 0x30) = U8(node, 0x30) | 0x40;
        for (; iVar2 != 0; iVar2 = *(char**)(iVar2 + 0x38)) {
            if (I8(iVar2, 0x30) < 0) break;
            U8(iVar2, 0x30) = U8(iVar2, 0x30) | 0x80;
        }
    }
}

// ===========================================================================
// @ 0x009588C0  Fn009588c0
// ===========================================================================
void W::m8c0(char* node)
{
    if ((U8(node, 0x30) & 0x20) == 0) {
        if (I32(node, 0x78) != 0 && I32(node, 0x24) == 0 && I8(this, 0x25) == 0) {
            char* base = B(this) + 0x18;
            void** p = (void**)(node + 0x20);
            void* t = *(void**)(base + 4);
            p[1] = t;
            *p = base;
            *(void**)(base + 4) = p;
            void** c = (void**)p[1];
            *c = p;
        }
        char* iVar2 = *(char**)(node + 0x38);
        U8(node, 0x30) = U8(node, 0x30) | 0x20;
        for (; iVar2 != 0; iVar2 = *(char**)(iVar2 + 0x38)) {
            if (I8(iVar2, 0x30) < 0) break;
            U8(iVar2, 0x30) = U8(iVar2, 0x30) | 0x80;
        }
    }
}

// ===========================================================================
// @ 0x00958920  Fn00958920
// ===========================================================================
char __cdecl Fn00958920(int* self, void* p2, char* p3, char p4, unsigned p5)
{
    char cVar4 = 0;
    ((VTab*)self)->v00();
    self[0x1d] = self[0x1d] + 1;
    int* piVar1 = *(int**)(p3 + 0xc);
    for (;;) {
        if (piVar1 == self + 0x19) {
            self[0x1d] = self[0x1d] - 1;
            if (self[0x1d] == 0) ((Ext*)self)->ea0();
            if (p4 == 0 && cVar4 == 0) {
                cVar4 = ((VTab*)self)->v20(p2);
            }
            ((VTab*)self)->v04();
            return cVar4;
        }
        piVar1 = (int*)piVar1[2];
        if (piVar1) ((VTab*)piVar1)->v00();
        unsigned uVar2 = *(unsigned*)(*(int*)(p3 + 0xc) + 0xc);
        *(int*)(p3 + 0xc) = **(int**)(p3 + 0xc);
        if (((p5 & uVar2) != 0) && ((char)((VS6*)piVar1)->f((void*)(self + 1), p2) != 0)) {
            cVar4 = 1;
            if (piVar1) ((VTab*)piVar1)->v04();
            self[0x1d] = self[0x1d] - 1;
            if (self[0x1d] == 0) ((Ext*)self)->ea0();
            if (p4 == 0 && cVar4 == 0) {
                cVar4 = ((VTab*)self)->v20(p2);
            }
            ((VTab*)self)->v04();
            return cVar4;
        }
        if (piVar1) ((VTab*)piVar1)->v04();
        piVar1 = *(int**)(p3 + 0xc);
    }
}

// ===========================================================================
// @ 0x009589F0  EA::UTFWin::WindowMgr::DispatchMsgToWindow
// ===========================================================================
struct MsgNode {
    void* f0;
    void* f4;
    int   fc;
    int   f8;
    char  f10;
};

void W::DispatchMsgToWindow(int p2, char* p3, int p4)
{
    void* uVar1 = ((Ext*)this)->ba70(*(void**)(p3 + 8));
    MsgNode local;
    local.f8 = I32(p2, 100);
    local.f0 = PTR(this, 0x688);
    local.fc = p2;
    local.f10 = (char)p4;
    if (local.f0 != 0 && I32(local.f0, 8) == p2 && I8(local.f0, 0x10) == local.f10) {
        local.f8 = I32(local.f0, 0xc);
    }
    PTR(this, 0x688) = &local;
    Fn00958920((int*)p2, p3, (char*)&local, local.f10, (unsigned)uVar1);
    PTR(this, 0x688) = local.f0;
}
