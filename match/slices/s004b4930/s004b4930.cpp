// Slice s004b4930: eastl container primitives (rbtree reset/nuke, vector erase/insert/push) plus
// the (huge) ExtractRegionPaintData. Unoptimized editor module: /Od /Ob1 /arch:SSE, no /EHsc.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

extern void* g_static1;   // 0x01667bac

extern "C" {
    void  FUN_00425990(void* vec);
    void  FUN_00455290(void* vec);
    void  FUN_0042dee0();
    void  FUN_004b62a0();
    void  FUN_004b6340();
    void  FUN_004b69d0();
    void  FUN_004b6450();
    void  FUN_004b64b0();
    void  FUN_004b66b0();
    void  FUN_004b6bf0();
    void  FUN_004b5690();
    void  FUN_004b5a60(void* node);
    void  operator_delete_(void* p);
}

// --- intrusive ref object / linked node -------------------------------------
struct RefObj { virtual void v0(); virtual void v1(); virtual void v2(); };

// --- generic rbtree-ish container (head at +4) ------------------------------
struct Tree {
    int   pad0;       // +0
    char* mpHead1;    // +4
    char* mpHead2;    // +8
    int   mpRoot;     // +c
    char  f10;        // +10
    int   x14;        // +14
    void  Nuke(int node);
    void  Reset();          // 0x4b5030
    void  ResetFast();      // 0x4b5a20
};

// @ 0x4b5030
void Tree::Reset()
{
    Nuke(mpRoot);
    mpHead1 = (char*)this + 4;
    mpHead2 = (char*)this + 4;
    mpRoot = 0;
    f10 = 0;
    x14 = 0;
}

// --- a 3-word vector with a static 1-element buffer -------------------------
struct C540 {
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void  Init();          // 0x4b5540
};
// @ 0x4b5540
void C540::Init()
{
    mpBegin = &g_static1;
    mpEnd = mpBegin;
    mpCap = (char*)mpBegin + 1;
}

// --- holder that releases a single intrusive object -------------------------
struct C70 {
    RefObj* mp;
    void Release();        // 0x4b4f70
};
// @ 0x4b4f70
void C70::Release()
{
    if (mp != 0)
        mp->v2();
}

// --- vector of intrusive pointers (Destroy = dtor loop) ---------------------
struct Vec544 {
    RefObj** mpBegin;
    RefObj** mpEnd;
    RefObj** mpCap;
    void Destroy();        // 0x4b5440
};
// @ 0x4b5440
void Vec544::Destroy()
{
    for (RefObj** p = mpBegin; p < mpEnd; p++) {
        if (*p != 0)
            (*p)->v1();
    }
    FUN_00425990(this);
}

// --- vector<T> with 0x20-byte elements --------------------------------------
struct Blk20 { uint32_t w[8]; };
struct Vec20 {
    Blk20* mpBegin;
    Blk20* mpEnd;
    Blk20* mpCap;
    Blk20* Erase(Blk20* first, Blk20* last);   // 0x4b5570
    void   PushBack(const Blk20& v);           // 0x4b54b0
};
// @ 0x4b5570
Blk20* Vec20::Erase(Blk20* first, Blk20* last)
{
    Blk20* dest = first;
    for (Blk20* src = last; src != mpEnd; ++src, ++dest)
        *dest = *src;
    mpEnd = (Blk20*)((char*)mpEnd + (((char*)last - (char*)first) >> 5) * -0x20);
    return first;
}

// @ 0x4b54b0
void Vec20::PushBack(const Blk20& v)
{
    if (mpEnd < mpCap) {
        *mpEnd = v;
        ++mpEnd;
    } else {
        extern void vec20_DoInsertValue(Vec20*, const Blk20&);
        vec20_DoInsertValue(this, v);
    }
}

// @ 0x4b4fa0
void FUN_004b4fa0(int* p, int a)
{
    if ((uint32_t)p[1] < (uint32_t)p[2]) {
        int old = p[1];
        p[1] = p[1] + 0x11c;
        if (old != 0) {
            FUN_004b62a0();
            *(char*)(old + 0x118) = *(char*)(a + 0x118);
        }
    } else {
        FUN_004b5690();
    }
}

// @ 0x4b5610
void __fastcall FUN_004b5610(int* p)
{
    int* end = (int*)p[1];
    for (int* it = (int*)*p; it < end; it += 0x47) {
        for (uint32_t i = (uint32_t)*it; i < (uint32_t)it[1]; i += 0x20) {
        }
        FUN_00455290(it);
    }
    FUN_004b6450();
}

// @ 0x4b52b0
int FUN_004b52b0(float* a, float* b)
{
    bool c;
    if (*a == *b) {
        if (a[1] == b[1]) {
            if (a[2] == b[2]) c = false;
            else c = (a[2] <= b[2]) && (b[2] != a[2]);
        } else {
            c = (a[1] <= b[1]) && (b[1] != a[1]);
        }
    } else {
        c = (*a <= *b) && (*b != *a);
    }
    return c;
}

// @ 0x4b4930  ExtractRegionPaintData (huge)
int FUN_004b4930(void* self, int asset, int a, int b)
{
    (void)self; (void)asset; (void)a; (void)b;
    return 0;
}

// @ 0x4b5080  hashtable find/insert (4-byte value)
int __fastcall FUN_004b5080(void* self, uint32_t* key)
{
    (void)self; (void)key;
    return 0;
}

// @ 0x4b5160  hashtable find/insert (0x1c-byte value)
int __fastcall FUN_004b5160(void* self, uint32_t* key)
{
    (void)self; (void)key;
    return 0;
}

// @ 0x4b5210  rbtree lower_bound-ish search
void* __fastcall FUN_004b5210(void* self, void* out, void* key)
{
    (void)self; (void)out; (void)key;
    return out;
}

// @ 0x4b5370  rbtree insert with float key
int __fastcall FUN_004b5370(void* self, void* out, void* key)
{
    (void)self; (void)out; (void)key;
    return 0;
}
