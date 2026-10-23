// Slice s00f60630 - EA::Swarm particle-system manager (GB2-derived game object).
//
//   00f60630  FUN_00f60630   - per-frame update: advance the emission accumulator, then
//                              top the particle list up to the requested count
//   00f60810  FUN_00f60810   - destroy every particle in the list (return them to the pool)
//   00f608c0  FUN_00f608c0   - constructor (two arguments, returns this)
//   00f60d80  FUN_00f60d80   - destructor
//   00f60e60  FUN_00f60e60   - enable/disable method of the interface sub-object at +8
//
// Toolchain: VS2008 SP1 (cl 15.00) Spore game code; flags /O2 /MD /Gy /EHsc /TP.
//
// Layout (offsets are from the object base; FUN_00f60e60 runs with `this` = base + 8 and
// hands base to FUN_00f60810 as `this - 8`):
//    +0x00..+0x0c  four vtables (GB2, GmeIComponent, GmeRefCount, ...)
//    +0x14/+0x15/+0x16  bools        +0x18/+0x1c  intrusive list sentinel (head/tail)
//    +0x20  particle count           +0x24/+0x28/+0x2c  context pointers
//    +0x40/+0x50/+0x60  doubles (accumulator, rate)  +0x58 int (emit limit)
//    +0xa8..+0xbc  bounding box (min/max x/y/z)       +0x194 float (count scale)
//    +0x230 void*  optional sub-object   +0x238/+0x23c  int handles (-1 == none)
//
// The particles come from a fixed allocator at 0x016c9468 and are pooled on the free list at
// 0x016c9478 (the first dword of a node is the free-list link, +4 is the "live" prev link).
#include "types.h"

typedef uint32_t u32;

// ---------------------------------------------------------------------------------------------
// engine helpers, modelled as members of dummy structs so that `this` lands in ECX
// ---------------------------------------------------------------------------------------------
struct Allocator   { bool __thiscall AddCore(void* block, u32 size); };   // 0x016c9468 (0x926650)
struct ParticleCtx { bool __thiscall Init(void* node);                   // 0x00f5ebf0
                     bool __thiscall Emit(void* node, float dt);         // 0x00f5eb80
                     void __thiscall Kill(void* node); };                // 0x00f5f6a0
struct SpVectorRefVertex { void __thiscall Destroy(); };                 // 0x00a8c440
struct IntrusiveList     { void __thiscall Destroy(); };                 // 0x00620230
struct Matrix34          { void __thiscall Assign(const void* src); };   // 0x0041cb40

extern void __cdecl operator_delete(void* p);                            // 0x00f47380

// virtual-call shapes used through the raw vtable pointers
typedef void  (__thiscall *VFn1)(void*);
typedef void  (__thiscall *VFn2)(void*, int);
typedef void  (__thiscall *VFn2p)(void*, void*);
typedef void  (__thiscall *VFn3)(void*, int, int);
typedef void* (__thiscall *VFnR1)(void*);

// ---------------------------------------------------------------------------------------------
// fixed retail globals / constants
// ---------------------------------------------------------------------------------------------
#define DAT_016c9478 (*(void**)0x016c9478)
#define DAT_016c9434 (*(float*)0x016c9434)
#define DAT_016c9438 (*(float*)0x016c9438)
#define DAT_016c943c (*(float*)0x016c943c)
#define DAT_016c9488 (*(float*)0x016c9488)
#define DAT_016c948c (*(float*)0x016c948c)
#define DAT_016c9490 (*(float*)0x016c9490)
#define DAT_016c9494 (*(float*)0x016c9494)
#define DAT_016c9498 (*(float*)0x016c9498)
#define DAT_01485720 (*(float*)0x01485720)    // 1.0f
#define DAT_01454410 (*(double*)0x01454410)   // -1.0
#define DAT_01418f90 (*(float*)0x01418f90)
#define DAT_013f0620 (*(float*)0x013f0620)

// ---------------------------------------------------------------------------------------------
// particle node: {next/free-link, prev, a, b, x, y, z}
// ---------------------------------------------------------------------------------------------
struct Node {
    Node* next;   // +0x00  also the free-list link while pooled
    Node* prev;   // +0x04
    float a;      // +0x08
    float b;      // +0x0c
    float x;      // +0x10
    float y;      // +0x14
    float z;      // +0x18
};

// ---------------------------------------------------------------------------------------------
// the object itself
// ---------------------------------------------------------------------------------------------
struct CtxFlags {          // the flags word at ctx24 + 8
    uint32_t : 27;
    uint32_t f27 : 1;
    uint32_t : 4;
};

struct Swarm {
    void*   vtbl0;      // 0x000
    void*   vtbl1;      // 0x004
    void*   vtbl2;      // 0x008
    void*   vtbl3;      // 0x00c
    int     field_10;   // 0x010
    uint8_t b14;        // 0x014
    uint8_t b15;        // 0x015
    uint8_t b16;        // 0x016
    uint8_t pad17;      // 0x017
    Node*   head;       // 0x018  intrusive list sentinel
    Node*   tail;       // 0x01c
    int     count;      // 0x020
    void*   ctx24;      // 0x024
    void*   ctx28;      // 0x028
    void*   ctx2c;      // 0x02c
    void*   ctx30;      // 0x030
    int     i34;        // 0x034
    float   f38;        // 0x038
    int     i3c;        // 0x03c
    double  d40;        // 0x040
    uint8_t b48;        // 0x048
    uint8_t pad49[7];   // 0x049
    double  d50;        // 0x050
    int     i58;        // 0x058
    int     pad5c;      // 0x05c
    double  d60;        // 0x060
    float   f68;        // 0x068
    float   f6c;        // 0x06c
    float   f70;        // 0x070
    float   f74;        // 0x074
    int     i78;        // 0x078
    int     i7c;        // 0x07c
    int     i80;        // 0x080
    int     i84;        // 0x084
    int     i88;        // 0x088
    int     i8c;        // 0x08c
    float   f90;        // 0x090
    float   f94;        // 0x094
    float   f98;        // 0x098
    float   f9c;        // 0x09c
    float   fa0;        // 0x0a0
    float   fa4;        // 0x0a4
    float   fa8;        // 0x0a8  min x
    float   fac;        // 0x0ac  min y
    float   fb0;        // 0x0b0  min z
    float   fb4;        // 0x0b4  max x
    float   fb8;        // 0x0b8  max y
    float   fbc;        // 0x0bc  max z
    float   fc0;        // 0x0c0
    float   fc4;        // 0x0c4
    float   fc8;        // 0x0c8
    float   fcc;        // 0x0cc
    uint16_t wd0;       // 0x0d0
    uint16_t wd2;       // 0x0d2
    float   fd4;        // 0x0d4
    float   fd8;        // 0x0d8
    float   fdc;        // 0x0dc
    float   fe0;        // 0x0e0
    float   m33a[9];    // 0x0e4
    uint16_t w108;      // 0x108
    uint16_t w10a;      // 0x10a
    float   f10c;       // 0x10c
    float   f110;       // 0x110
    float   f114;       // 0x114
    float   f118;       // 0x118
    float   m33b[9];    // 0x11c
    float   f140;       // 0x140
    float   f144;       // 0x144
    float   f148;       // 0x148
    uint16_t w14c;      // 0x14c
    uint16_t w14e;      // 0x14e
    float   f150;       // 0x150
    float   f154;       // 0x154
    float   f158;       // 0x158
    float   f15c;       // 0x15c
    float   f160;       // 0x160
    float   f164;       // 0x164
    float   f168;       // 0x168
    float   f16c;       // 0x16c
    float   f170;       // 0x170
    float   f174;       // 0x174
    float   f178;       // 0x178
    float   f17c;       // 0x17c
    float   f180;       // 0x180
    float   f184;       // 0x184
    int     i188;       // 0x188
    float   f18c;       // 0x18c
    float   f190;       // 0x190
    float   f194;       // 0x194
    float   f198;       // 0x198
    float   f19c;       // 0x19c
    float   f1a0;       // 0x1a0
    float   f1a4;       // 0x1a4
    float   f1a8;       // 0x1a8
    float   f1ac;       // 0x1ac
    float   f1b0;       // 0x1b0
    void*   p1b4;       // 0x1b4
    void*   p1b8;       // 0x1b8
    void*   p1bc;       // 0x1bc
    void*   p1c0;       // 0x1c0
    uint8_t b1c4;       // 0x1c4
    uint8_t b1c5;       // 0x1c5
    uint8_t b1c6;       // 0x1c6
    uint8_t pad1c7;     // 0x1c7
    float   f1c8;       // 0x1c8
    float   f1cc;       // 0x1cc
    float   f1d0;       // 0x1d0
    float   f1d4;       // 0x1d4
    float   f1d8;       // 0x1d8
    float   f1dc;       // 0x1dc
    int     i1e0;       // 0x1e0
    int     i1e4;       // 0x1e4
    int     i1e8;       // 0x1e8
    void*   p1ec;       // 0x1ec  SpVector<RefVertex>
    void*   p1f0;       // 0x1f0
    void*   p1f4;       // 0x1f4
    uint8_t pad1f8[8];  // 0x1f8  (not initialised by the constructor)
    uint8_t b200;       // 0x200
    uint8_t pad201[3];  // 0x201
    void*   p204;       // 0x204  operator-new array (element count at -4)
    int     i208;       // 0x208
    int     i20c;       // 0x20c
    int     pad210;     // 0x210
    int     pad214;     // 0x214
    uint8_t b218;       // 0x218
    uint8_t pad219[3];  // 0x219
    void*   p21c;       // 0x21c  operator-new array (element count at -4)
    int     i220;       // 0x220
    int     i224;       // 0x224
    uint8_t pad228[8];  // 0x228  (not initialised by the constructor)
    void*   p230;       // 0x230  optional sub-object
    uint8_t b234;       // 0x234
    uint8_t pad235[3];  // 0x235
    int     i238;       // 0x238  (-1 == none)
    int     i23c;       // 0x23c  (-1 == none)
    int     pad240;     // 0x240
    uint8_t b244;       // 0x244

    void    __thiscall FUN_00f60630(float dt);          // 0x00f60630
    void    __fastcall FUN_00f60810();                  // 0x00f60810
    Swarm*  __thiscall FUN_00f608c0(void* arg2, void* arg3);  // 0x00f608c0
    void    __fastcall FUN_00f60d80();                  // 0x00f60d80
    void    __thiscall FUN_00f60e60(void* arg);         // 0x00f60e60
};

typedef char check_head[(sizeof(Swarm) >= 0x245) ? 1 : -1];

// ---------------------------------------------------------------------------------------------
// 00f60630
// ---------------------------------------------------------------------------------------------
// @ 0x00f60630
void __thiscall Swarm::FUN_00f60630(float dt)
{
    double acc = (double)dt * d60 + d50;
    d50 = acc;
    if ((double)i58 > acc)
        return;

    float f = **(float**)((uint8_t*)ctx24 + 0x64) * f194;
    int want = (int)f;
    want = ((float)want < f) ? want + 1 : want;
    want -= count;
    if (want <= 0)
        return;

    Node* sentinel = (Node*)((uint8_t*)this + 0x18);
    for (int i = want; i > 0; --i) {
        Node* node;
        for (;;) {
            node = (Node*)DAT_016c9478;
            if (node != 0) {
                DAT_016c9478 = node->next;
                node->prev = 0;
                node->next = 0;
                break;
            }
            if (!((Allocator*)0x016c9468)->AddCore(0, 0))
                break;
        }
        if (((ParticleCtx*)this)->Init(node) && ((ParticleCtx*)this)->Emit(node, dt)) {
            Node* tail = this->tail;
            node->prev = tail;
            node->next = sentinel;
            this->tail = node;
            tail->next = node;
            ++count;

            float x = node->x;
            if (fa8 > x) fa8 = x;
            if (x > fb4) fb4 = x;
            float y = node->y;
            if (fac > y) fac = y;
            if (y > fb8) fb8 = y;
            float z = node->z;
            if (fb0 > z) fb0 = z;
            if (z > fbc) fbc = z;
        } else if (p230 != 0 &&
                   (node->a >= node->b || ((CtxFlags*)((uint8_t*)ctx24 + 8))->f27)) {
            ((ParticleCtx*)this)->Kill(node);
            if (p230 != 0 && count == 0 && b15 != 0) {
                void** vt = *(void***)((uint8_t*)p230 + 8);
                ((VFn2)vt[3])((uint8_t*)p230 + 8, 0);
            }
        } else {
            node->next = (Node*)DAT_016c9478;
            DAT_016c9478 = node;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 00f60810 - destroy the whole live list
// ---------------------------------------------------------------------------------------------
// @ 0x00f60810
void __fastcall Swarm::FUN_00f60810()
{
    Node* sentinel = (Node*)((uint8_t*)this + 0x18);
    Node* node = head;
    while (node != sentinel) {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
        node->next = 0;
        node->prev = 0;
        --count;

        Node* cur = node;
        node = next;
        if (p230 != 0 &&
            (cur->a >= cur->b || ((CtxFlags*)((uint8_t*)ctx24 + 8))->f27)) {
            ((ParticleCtx*)this)->Kill(cur);
            if (p230 != 0 && count == 0 && b15 != 0) {
                void** vt = *(void***)((uint8_t*)p230 + 8);
                ((VFn2)vt[3])((uint8_t*)p230 + 8, 0);
            }
        } else {
            cur->next = (Node*)DAT_016c9478;
            DAT_016c9478 = cur;
        }
    }

    Node* rest = head;
    if (rest != sentinel) {
        do {
            Node* nx = rest->next;
            rest->prev = 0;
            rest->next = 0;
            rest = nx;
        } while (rest != sentinel);
    }
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
}

// ---------------------------------------------------------------------------------------------
// 00f608c0 - constructor
// ---------------------------------------------------------------------------------------------
// @ 0x00f608c0
Swarm* __thiscall Swarm::FUN_00f608c0(void* arg2, void* arg3)
{
    Node* sentinel = (Node*)((uint8_t*)this + 0x18);

    vtbl1 = (void*)0x140b5a0;   // ??_7GB2@@6B@
    vtbl3 = (void*)0x13ef094;   // ??_7GmeRefCount@@6B@
    field_10 = 0;
    vtbl2 = (void*)0x13f21d4;   // ??_7GmeIComponent@@6B@
    vtbl3 = (void*)0x13f2194;
    vtbl0 = (void*)0x148f0e0;
    vtbl1 = (void*)0x148f0dc;
    vtbl2 = (void*)0x148f0a0;
    vtbl3 = (void*)0x148f09c;
    b14 = 0;
    b15 = 0;
    b16 = 1;
    tail = sentinel;
    head = sentinel;
    d40 = 0.0;
    d50 = 0.0;
    ctx24 = arg2;
    ctx28 = arg2;
    d60 = DAT_01454410;
    count = 0;
    ctx30 = 0;
    i34 = 0;
    f38 = 0.0f;
    b48 = 0;
    i58 = 0;
    f68 = 0.0f;
    ctx2c = arg3;
    f6c = DAT_016c9434;
    f70 = DAT_016c9438;
    f74 = DAT_016c943c;
    i78 = 0;
    i7c = 0;
    i80 = 0;
    i84 = 0;
    i88 = 0;
    i8c = 0;
    f90 = 0.0f;
    f94 = DAT_016c9434;
    f98 = DAT_016c9438;
    f9c = DAT_016c943c;
    fa0 = 0.0f;
    fa4 = 0.0f;
    fa8 = 0.0f;
    fac = 0.0f;
    fb0 = 0.0f;
    fb4 = 0.0f;
    fb8 = 0.0f;
    fbc = 0.0f;
    fc0 = 0.0f;
    fc4 = DAT_016c9434;
    fc8 = DAT_016c9438;
    fcc = DAT_016c943c;
    wd0 = 0;
    wd2 = 0;
    fd4 = DAT_016c9434;
    fd8 = DAT_016c9438;
    fdc = DAT_016c943c;
    fe0 = DAT_01485720;
    ((Matrix34*)m33a)->Assign((const void*)0x016c9440);
    w10a = 0;
    w108 = 0;
    f10c = DAT_016c9434;
    f110 = DAT_016c9438;
    f114 = DAT_016c943c;
    f118 = DAT_01485720;
    ((Matrix34*)m33b)->Assign((const void*)0x016c9440);
    f140 = DAT_016c9434;
    f144 = DAT_016c9438;
    f148 = DAT_016c943c;
    w14c = 0;
    w14e = 0;
    f150 = DAT_016c9488;
    f154 = DAT_016c948c;
    f158 = DAT_016c9488;
    f15c = DAT_016c948c;
    f160 = DAT_016c9488;
    f164 = DAT_016c948c;
    f168 = DAT_01485720;
    f16c = DAT_01485720;
    f170 = DAT_01485720;
    f174 = DAT_01485720;
    f178 = DAT_01485720;
    f17c = DAT_016c9490;
    f180 = DAT_016c9494;
    f184 = DAT_016c9498;
    i188 = 0;
    f18c = DAT_01418f90;
    f190 = DAT_013f0620;
    f194 = DAT_01485720;
    f198 = DAT_01485720;
    f19c = DAT_01485720;
    f1a0 = DAT_01485720;
    f1a4 = DAT_01485720;
    f1a8 = DAT_016c9490;
    f1ac = DAT_016c9494;
    f1b0 = DAT_016c9498;
    p1b4 = 0;
    p1b8 = 0;
    p1bc = 0;
    p1c0 = 0;
    b1c4 = 0;
    b1c5 = 0;
    b1c6 = 0;
    f1c8 = 0.0f;
    f1cc = 0.0f;
    f1d0 = 0.0f;
    f1d4 = 0.0f;
    f1d8 = 0.0f;
    f1dc = 0.0f;
    i1e8 = 0;
    i1e0 = -1;
    i1e4 = -1;
    p1ec = 0;
    p1f0 = 0;
    p1f4 = 0;
    b200 = 0;
    p204 = 0;
    i208 = 0;
    i20c = 0;
    b218 = 0;
    p21c = 0;
    i220 = 0;
    i224 = 0;
    p230 = 0;
    i238 = -1;
    i23c = -1;
    b234 = 0;
    b244 = 0;
    return this;
}

// ---------------------------------------------------------------------------------------------
// 00f60d80 - destructor
// ---------------------------------------------------------------------------------------------
// @ 0x00f60d80
void __fastcall Swarm::FUN_00f60d80()
{
    vtbl0 = (void*)0x148f0e0;
    vtbl1 = (void*)0x148f0dc;
    vtbl2 = (void*)0x148f0a0;
    vtbl3 = (void*)0x148f09c;

    if (p230 != 0) {
        void** vt = *(void***)((uint8_t*)p230 + 8);
        ((VFn1)vt[0x38 / 4])((uint8_t*)p230 + 8);
    }

    if (p21c != 0 && *(int*)((uint8_t*)p21c - 4) != 0)
        operator_delete(p21c);
    if (p204 != 0 && *(int*)((uint8_t*)p204 - 4) != 0)
        operator_delete(p204);

    ((SpVectorRefVertex*)((uint8_t*)this + 0x1ec))->Destroy();

    if (p1c0 != 0) {
        void** vt = *(void***)p1c0;
        ((VFn1)vt[1])(p1c0);
    }
    if (p1bc != 0) {
        void** vt = *(void***)p1bc;
        ((VFn1)vt[1])(p1bc);
    }
    if (p1b8 != 0) {
        void** vt = *(void***)p1b8;
        ((VFn1)vt[1])(p1b8);
    }

    if (p1b4 != 0) {
        int* pc = (int*)((uint8_t*)p1b4 + 4);
        *pc = *pc - 1;
        if (*pc == 0) {
            *pc = 1;
            void** vt = *(void***)p1b4;
            ((VFn2)vt[0])(p1b4, 1);
        }
    }

    ((IntrusiveList*)((uint8_t*)this + 0x18))->Destroy();

    vtbl2 = (void*)0x13f21d4;
    vtbl3 = (void*)0x13ef094;
}

// ---------------------------------------------------------------------------------------------
// 00f60e60 - interface method of the sub-object at +8 (so the real object is self - 8)
// ---------------------------------------------------------------------------------------------
// @ 0x00f60e60
void __thiscall Swarm::FUN_00f60e60(void* arg)
{
    uint8_t* self = (uint8_t*)this;
    if (self[0xc] != 0) {
        void* sub = *(void**)(self + 0x228);
        if (sub != 0 && *(int*)(self + 0x18) == 0) {
            void** vt = *(void***)((uint8_t*)sub + 8);
            ((VFn2p)vt[3])((uint8_t*)sub + 8, arg);
        }

        bool off = (arg == 0);
        self[0xd] = off;
        if (!off) {
            self[0xc] = 0;
            ((Swarm*)(self - 8))->FUN_00f60810();
            if (*(int*)(self + 0x234) >= 0) {
                void* ctx = *(void**)(self + 0x28);
                void* o = ((VFnR1)(*(void***)ctx)[0x20 / 4])(ctx);
                void** vt = *(void***)o;
                ((VFn3)vt[0x24 / 4])(o, *(int*)(self + 0x234), 0);
            } else if (*(int*)(self + 0x230) >= 0) {
                void* ctx = *(void**)(self + 0x28);
                void* o = ((VFnR1)(*(void***)ctx)[0x20 / 4])(ctx);
                void** vt = *(void***)o;
                ((VFn3)vt[0x38 / 4])(o, *(int*)(self + 0x230), 0);
            }
        }
    }
}
