// Slice s0080a700: cSPUIImageAtlasMap / UI layout records.
// Copy/construct/assign helpers are byte-exact; the larger AtlasMap and layout routines are
// only partially reconstructed.
#include "types.h"

struct Ref {
    virtual void AddRef();     // +0
    virtual void Release();    // +4
};
extern char Rec_vtable[];
// EA's block free (the retail deleting destructors call it directly).
void __cdecl free_block(void* p);          // 0x00f47380

// ================= 0x0080a9d0: copy a 0x28-byte record into this
struct Big {
    int a, b, c, d, e;
    float f0, f1;
    int g, h, i;
    Big* Assign(const Big* src);
};
Big* Big::Assign(const Big* src)
{
    a = src->a; b = src->b; c = src->c; d = src->d; e = src->e;
    f0 = src->f0; f1 = src->f1;
    g = src->g; h = src->h; i = src->i;
    return this;
}

// ================= 0x0080aa20 / 0x0080aa90: window scale from a subobject at +0x20c
extern float g_const_13ef548;

struct Sub {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual Sub* Fn10();                        // +0x10 (index 4)
    virtual void v5(); virtual void v6();
    virtual void Fn1c(int x);                   // +0x1c (index 7)
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual float* Fn38();                      // +0x38 (index 14)
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void v27(); virtual void v28();
    virtual void Fn74(float a, float b);        // +0x74 (index 29)
};

// @ 0x0080aa20
bool FUN_0080aa20(void* p)
{
    Sub* s = (Sub*)((char*)p + 0x20c);
    Sub* w = s->Fn10();
    float* r = w->Fn38();
    w->Fn74(g_const_13ef548, r[3] - r[1]);
    s->Fn1c(0);
    s->Fn1c(1);
    return true;
}

struct Win2 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33();
    virtual void Fn88(int x);                   // +0x88 (index 34)
};

// @ 0x0080aa90
bool FUN_0080aa90(void* p)
{
    Sub* s = (Sub*)((char*)p + 0x20c);
    Sub* w = s->Fn10();
    float* r = w->Fn38();
    w->Fn74(g_const_13ef548, r[3] - r[1]);
    Win2* o = (Win2*)p;
    o->Fn88(0);
    o->Fn88(1);
    return true;
}

// ================= 0x0080ae70: destroy a range of 0x34-byte objects
struct E34 {
    virtual void Fn(int v);
    char pad[0x30];
};
void __stdcall dtorRange(E34* a, E34* b)
{
    for (; a < b; ++a)
        a->Fn(0);
}

// ================= 0x0080af20: ctor from a 0x28 record + external AutoRef
struct Src28 { int a, b, c, d, e; float f0, f1; int g, h, i; };
struct RecA {
    void* vtbl;                 // +0
    int a, b, c, d, e;          // +4..+0x14
    float f0, f1;               // +0x18, +0x1c
    int g, h, i;                // +0x20,+0x24,+0x28
    Ref* r;                     // +0x2c
    int tail;                   // +0x30
    RecA* Ctor(const Src28* src, Ref* r2);
    RecA* DeletingDtor(unsigned int flags);
};
RecA* RecA::Ctor(const Src28* src, Ref* r2)
{
    vtbl = (void*)Rec_vtable;
    a = src->a; b = src->b; c = src->c; d = src->d; e = src->e;
    f0 = src->f0; f1 = src->f1;
    g = src->g; h = src->h; i = src->i;
    r = r2;
    if (r) r->AddRef();
    tail = src->d;
    return this;
}

// ================= 0x0080af90: copy-construct a 0x34-byte record
struct Rec {
    void* vtbl;                // +0
    int a, b, c, d, e;         // +4..+0x14
    float f0, f1;              // +0x18, +0x1c
    int g, h, i;               // +0x20,+0x24,+0x28
    Ref* r;                    // +0x2c
    int tail;                  // +0x30
    Rec* Ctor(const Rec* src);
};
Rec* Rec::Ctor(const Rec* src)
{
    vtbl = (void*)Rec_vtable;
    a = src->a; b = src->b; c = src->c; d = src->d; e = src->e;
    f0 = src->f0; f1 = src->f1;
    g = src->g; h = src->h; i = src->i;
    r = src->r;
    if (r) r->AddRef();
    tail = src->tail;
    return this;
}

// ================= 0x0080b240: assignment of a 0x34-byte record
struct AutoRef2 {
    Ref* p;
    AutoRef2& operator=(Ref* x) {
        Ref* old = p;
        if (x != old) {
            if (x) x->AddRef();
            p = x;
            if (old) old->Release();
        }
        return *this;
    }
};
struct W40 { int x[10]; };
struct RecC {
    void* vtbl;          // +0
    W40 w;               // +4..+0x2b
    AutoRef2 r;          // +0x2c
    int tail;            // +0x30
    RecC& operator=(const RecC& src);
};
RecC& RecC::operator=(const RecC& src)
{
    w = src.w;
    r = src.r.p;
    tail = src.tail;
    return *this;
}

// ================= 0x0080b2d0 / 0x0080b340: range copy (complete, non-byte-exact)
// @ 0x0080b340
RecC* copyFwd(void* unused, RecC* begin, RecC* end, RecC* dst)
{
    (void)unused;
    if (begin == end)
        return dst;
    do {
        *dst = *begin;
        ++begin;
        ++dst;
    } while (begin != end);
    return dst;
}

// @ 0x0080b2d0
RecC* copyBack(void* unused, RecC* begin, RecC* end, RecC* dst)
{
    (void)unused;
    if (end == begin)
        return dst;
    do {
        --end;
        --dst;
        *dst = *end;
    } while (end != begin);
    return dst;
}

// ================= 0x0080b3b0: deleting destructor of a 0x34-byte record
// Rewrites the record's table, clears and releases the reference-counted owner
// at +0x2c twice (the second read is dead, exactly as retail leaves it), then
// frees the block when the low flag bit marks a deleting call.
// @ 0x0080b3b0
RecA* RecA::DeletingDtor(unsigned int flags)
{
    vtbl = (void*)0x01417cac;
    Ref* owner = r;
    if (owner != 0) {
        r = 0;
        owner->Release();
    }
    owner = r;
    if (owner != 0)
        owner->Release();
    if ((flags & 1) != 0)
        free_block(this);
    return this;
}

// ================= 0x0080b400: validate the atlas layout entries
// Walks the 0x34-byte entry array at +0x1c4 and reports whether some entry whose
// owner exposes a non-empty title (or that has no title flag at all) also lacks
// the +0x30 bit 8 marker.
struct AtlasOwner {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14();
    virtual const unsigned short* Title();     // +0x3c (index 15)
};
struct AtlasEntry {
    void* mpVtable;                 // +0x00
    char pad04[0x28];
    AtlasOwner* mpOwner;            // +0x2c
    unsigned int mFlags;            // +0x30
};
struct AtlasState {
    char pad00[0x1c4];
    AtlasEntry* mpBegin;            // +0x1c4
    AtlasEntry* mpEnd;              // +0x1c8
    char pad1cc[0x41c - 0x1cc];
    unsigned char mReady;           // +0x41c

    bool Validate();
};

// @ 0x0080b400
bool AtlasState::Validate()
{
    if (mReady == 0)
        return false;
    for (unsigned int i = 0; i < (unsigned int)(((char*)mpEnd - (char*)mpBegin) / 0x34); i++) {
        AtlasEntry* e = mpBegin + i;
        bool checkFlags = false;
        if (e->mpOwner != 0) {
            if (((e->mFlags >> 10) & 1) != 0) {
                const unsigned short* s = e->mpOwner->Title();
                if (s != 0) {
                    const unsigned short* q = s;
                    while (*q != 0)
                        ++q;
                    if ((int)(q - s) >= 1)
                        checkFlags = true;
                }
            } else {
                checkFlags = true;
            }
        }
        if (checkFlags && ((e->mFlags >> 8) & 1) == 0)
            return true;
    }
    return false;
}

// ================= 0x0080b170: resolve the layout subobjects and drive a resize
// Looks up two message handlers on the actor, backs off the 0x20c subobject
// header, and dispatches to the scale setters (plain) or to the float-taking
// routines (when the mode byte is set).
struct ActorFind {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void* Find(int id);                 // +0x0c (index 3)
};
unsigned int FUN_0080ab00_dispatch(void* sub, float a, float b, float c);   // 0x0080ab00
unsigned int FUN_0080acb0_dispatch(void* sub, float a, float b, float c);   // 0x0080acb0

// @ 0x0080b170
unsigned int __stdcall FUN_0080b170(void* actor, char mode, float a, float b, float c)
{
    char* sub1 = 0;
    if (actor != 0) {
        char* w = (char*)((ActorFind*)actor)->Find(0xf15f4bd);
        if (w != 0)
            sub1 = w - 0x20c;           // subobject header sits 0x20c before the window
    }
    char* sub2 = 0;
    if (actor != 0) {
        char* w = (char*)((ActorFind*)actor)->Find(0x8ed27e7a);
        if (w != 0)
            sub2 = w - 0x20c;
    }
    if (mode == 0) {
        if (sub1 != 0)
            return FUN_0080aa20(sub1);
        if (sub2 != 0)
            return FUN_0080aa90(sub2);
    } else {
        if (sub1 != 0)
            return FUN_0080ab00_dispatch(sub1, a, b, c);
        if (sub2 != 0)
            return FUN_0080acb0_dispatch(sub2, a, b, c);
    }
    return 1;
}

// ================= remaining (partial)
// @ 0x0080a700
void cSPUIImageAtlasMap_Init() { /* atlas map load; not reconstructed */ }
// @ 0x0080ab00
void FUN_0080ab00() { /* not reconstructed */ }
// @ 0x0080acb0
void FUN_0080acb0() { /* not reconstructed */ }
// @ 0x0080b000
void FUN_0080b000() { /* not reconstructed */ }
// @ 0x0080b3b0
void FUN_0080b3b0() { /* deleting destructor of a 0x34 record; not reconstructed */ }

// @ 0x0080b4d0
void FUN_0080b4d0() { /* not reconstructed */ }
