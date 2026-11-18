// Slice s00cd7d90 -- SP::cTribeModeStrategy destructor.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc)
#include "types.h"

// The strategy is polymorphic (five vtable pointers at +0x00..+0x10); the
// destructor resets them, releases the refcounted members one by one and then
// rewrites the base-class vtables.  It is spelled out explicitly because the
// retail member layout keeps raw pointers rather than owning types.

// ------------------------------------------------------------------ engine bits
extern char VT_1477668[];
extern char VT_1477648[];
extern char VT_1477640[];
extern char VT_14775f0[];
extern char VT_14775e8[];
extern char VT_13eb938[];
extern char VT_13eb394[];

// 0x00f47380 -- free a single block
void __cdecl operator_delete_00f47380(void* p);

// 0x00571db0 -- unregister a UI handler and release its context block
void __cdecl FUN_00571db0(void* a, void* b, void* c, void* d, void* e);

// Release through a vtable slot: slot 1 ([vtbl+4]) and slot 2 ([vtbl+8]).
inline void Release1(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[1])(p);
}
inline void Release2(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[2])(p);
}

// 0x00b638b0 -- tour timer / timer2 destructor
struct cGonzagoTimer {
    uint32_t m[8];                      // 0x20 bytes
    void dtor_00b638b0();
};

// 0x00cd57d0 -- subsystem helper stored at +0x40
struct Obj40 {
    uint32_t m[6];
    void dtor_00cd57d0();
};

// 0x00ae6970 -- helper stored at +0x94
struct Obj94 {
    uint32_t m[5];
    void dtor_00ae6970();
};

// 0x00b5b9a0 -- base subobject destructor beginning at +0x0c
struct Obj0c {
    uint32_t m[0x34 / 4];
    void dtor_00b5b9a0();
};

// The allocator-backed string/vector living at +0xa8: begin at +4, capacity at
// +8, size at +0xc, a pool free list at +0x1c, the pool range at +0x24..+0x28
// and the inline buffer pointer at +0x30.
struct PoolContainer {
    uint32_t m00;                       // +0x00
    void*    mpBegin;                   // +0x04
    uint32_t mCapacity;                 // +0x08
    uint32_t mSize;                     // +0x0c
    uint32_t mPad10[3];                 // +0x10..+0x1b
    void*    mpFreeList;                // +0x1c
    uint32_t mPad20;                    // +0x20
    void*    mpPoolBegin;               // +0x24
    void*    mpPoolEnd;                 // +0x28
    uint32_t mPad2c;                    // +0x2c
    void*    mpInline;                  // +0x30
    uint32_t mPad34[0xbc / 4];          // +0x34..+0xef

    void DestroyRange_00a1b6c0(void* first, uint32_t capacity);
};

struct Vector2c {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void DestroyRange_01023030(void* first, void* last);
};

struct Vector304 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void DestroyRange_00cd6fd0(void* first, void* last);
};

// ------------------------------------------------------------------ strategy
struct cTribeModeStrategy {
    void*    mpVtbl0;                   // +0x00
    void*    mpVtbl1;                   // +0x04
    void*    mpVtbl2;                   // +0x08
    void*    mpVtbl3;                   // +0x0c
    void*    mpVtbl4;                   // +0x10
    uint32_t m14[6];                    // +0x14..+0x2b
    Vector2c mVec2c;                    // +0x2c
    uint32_t m38[2];                    // +0x38..+0x3f
    Obj40    mObj40;                    // +0x40..+0x57
    cGonzagoTimer mTimer;               // +0x58..+0x77
    uint32_t m78;                       // +0x78
    void*    mp7c;                      // +0x7c
    uint32_t m80[5];                    // +0x80..+0x93
    Obj94    mObj94;                    // +0x94..+0xa7
    PoolContainer mContA8;              // +0xa8..+0x197
    uint8_t  mb198;                     // +0x198
    uint8_t  m199[3];                   // +0x199..+0x19b
    void*    mp19c;                     // +0x19c
    float    m1a0;                      // +0x1a0
    uint8_t  mb1a4;                     // +0x1a4
    uint8_t  m1a5[3];                   // +0x1a5..+0x1a7
    cGonzagoTimer mTimer2;              // +0x1a8..+0x1c7
    void*    mp1c8;                     // +0x1c8
    void*    mp1cc;                     // +0x1cc
    void*    mp1d0;                     // +0x1d0
    void*    mp1d4;                     // +0x1d4
    void*    mp1d8;                     // +0x1d8
    void*    mp1dc;                     // +0x1dc
    uint32_t m1e0[0x48 / 4];            // +0x1e0..+0x227
    uint8_t  mb228;                     // +0x228
    uint8_t  m229[3];                   // +0x229..+0x22b
    uint32_t m22c;                      // +0x22c
    uint32_t m230;                      // +0x230
    uint32_t m234;                      // +0x234
    uint32_t m238;                      // +0x238
    uint32_t m23c;                      // +0x23c
    void*    mp240;                     // +0x240
    uint32_t m244;                      // +0x244
    uint32_t m248;                      // +0x248
    uint32_t m24c;                      // +0x24c
    void*    mp250;                     // +0x250
    void*    mp254;                     // +0x254
    void*    ma258[20];                 // +0x258..+0x2a7
    void*    ma2a8[20];                 // +0x2a8..+0x2f7
    void*    mp2f8;                     // +0x2f8
    uint32_t m2fc;                      // +0x2fc
    uint32_t m300;                      // +0x300 (untouched by the destructor)
    Vector304 mVec304;                  // +0x304..+0x30f
    uint32_t m310[0x21];                // +0x310..+0x393
    void*    mp394;                     // +0x394
    void*    mp398;                     // +0x398
    void* volatile mp39c;               // +0x39c
    uint8_t  mb3a0;                     // +0x3a0
    uint8_t  m3a1;                      // +0x3a1
    uint8_t  m3a2;                      // +0x3a2
    uint8_t  mb3a3;                     // +0x3a3

    ~cTribeModeStrategy();
};

// @ 0x00cd7d90
cTribeModeStrategy::~cTribeModeStrategy()
{
    // volatile prologue stores: the retail destructor writes all five vtables
    // before it starts loading members (a plain store pair lets cl sink the
    // later base-vtable stores below them)
    *(void* volatile*)&mpVtbl0 = (void*)VT_1477668;
    *(void* volatile*)&mpVtbl1 = (void*)VT_1477648;
    *(void* volatile*)&mpVtbl2 = (void*)VT_1477640;
    *(void* volatile*)&mpVtbl3 = (void*)VT_14775f0;
    *(void* volatile*)&mpVtbl4 = (void*)VT_14775e8;

    void* first = mp39c;
    if (first) Release1(first);
    if (mp398) Release1(mp398);
    if (mp394) Release2(mp394);

    // record vector at +0x304: destroy the elements, then release its storage
    mVec304.DestroyRange_00cd6fd0(mVec304.mpBegin, mVec304.mpEnd);
    {
        void* p = mVec304.mpBegin;
        if (p && ((uint32_t*)p)[-1] != 0)
            operator_delete_00f47380(p);
    }

    // the two twenty-slot arrays of refcounted pointers; the second one starts
    // exactly where the first ends (+0x2a8), so both walks begin one past their
    // array and pre-decrement
    void** pEnd = ma2a8 + 20;
    if (mp2f8) Release2(mp2f8);
    for (int i = 19; i >= 0; --i) {
        --pEnd;
        if (*pEnd) Release1(*pEnd);
    }
    void** qEnd = ma258 + 20;
    for (int i = 19; i >= 0; --i) {
        --qEnd;
        if (*qEnd) Release1(*qEnd);
    }

    if (mp254) Release1(mp254);
    if (mp250) Release1(mp250);

    if (mp240) {
        void* sub = (char*)mp240 + 0x3c;
        Release1(sub);
    }

    if (mp1cc) {
        void* h = mp1cc;
        mp1cc = 0;
        FUN_00571db0(h, mp1d0, mp1d4, mp1d8, mp1dc);
    }

    if (mp1c8) Release2(mp1c8);

    mTimer2.dtor_00b638b0();

    if (mp19c) Release1(mp19c);

    // allocator-backed container at +0xa8
    PoolContainer* container = &mContA8;
    container->DestroyRange_00a1b6c0(container->mpBegin, container->mCapacity);
    {
        void* p = container->mpBegin;
        container->mSize = 0;
        if (container->mCapacity > 1 && p != container->mpInline) {
            if ((uint32_t)p < (uint32_t)container->mpPoolBegin || (uint32_t)p >= (uint32_t)container->mpPoolEnd) {
                operator_delete_00f47380(p);
            } else {
                *(void**)p = container->mpFreeList;
                container->mpFreeList = p;
            }
        }
    }

    mObj94.dtor_00ae6970();

    if (mp7c) operator_delete_00f47380(mp7c);

    mTimer.dtor_00b638b0();

    mObj40.dtor_00cd57d0();

    // vector at +0x2c
    mVec2c.DestroyRange_01023030(mVec2c.mpBegin, mVec2c.mpEnd);
    {
        void* p = mVec2c.mpBegin;
        if (p && ((uint32_t*)p)[-1] != 0)
            operator_delete_00f47380(p);
    }

    ((Obj0c*)((char*)this + 0x0c))->dtor_00b5b9a0();

    mpVtbl2 = VT_13eb394;
    mpVtbl1 = VT_13eb938;
    mpVtbl0 = VT_13eb938;
}
