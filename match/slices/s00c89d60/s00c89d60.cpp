// Slice s00c89d60: SP::cSpatialObject view/effect helpers.
// Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast
#include "types.h"

struct cSPVector3 { float x, y, z; };
struct cSPBoundingBox { cSPVector3 mMin; cSPVector3 mMax; };
struct Matrix33 { float m[9]; };

// Effect element stored in the +0xc0 vector (stride 0x3c).
struct EffectElem {
    int   id;              // +0x00
    char  pad04[0x10 - 0x4];
    char  b10;             // +0x10
    char  pad11[0x14 - 0x11];
    float f14;             // +0x14
    char  pad18[0x38 - 0x18];
    int*  p38;             // +0x38 (effect interface)
};

struct Spatial {
    void** vt;                       // +0x00
    char   pad04[0x9c - 0x4];
    int*   p9c;                      // +0x9c (refcounted)
    int*   pa0;                      // +0xa0
    char   padA4[0xc0 - 0xa4];
    EffectElem* vecBegin;            // +0xc0
    EffectElem* vecEnd;              // +0xc4
    EffectElem* vecCap;              // +0xc8
    int    padCc;

    float* GetExtents() {
        typedef float* (__thiscall* Fn)(Spatial*);
        return ((Fn)vt[0x68 / 4])(this);
    }
};

void __cdecl FUN_00b3d240();
char __cdecl FUN_00b33e10(float x);
int* __cdecl FUN_00401010();
void __cdecl FUN_00478db0(unsigned int v);
void __cdecl FUN_00c895f0(void* p);
void __cdecl FUN_00c88ba0(void* p);
void __cdecl FUN_00c88570(int a, int b, int c);
int  __cdecl FUN_00c88cd0(int a, int b, int c);
void __cdecl FUN_00c88c30(int a);
void __cdecl FUN_00c88d50(int a, int b, int c);
void __cdecl LocalToWorldTransform(Spatial* s, void* m);
void __cdecl cSPBoundingBox_Transform(cSPBoundingBox* b, void* m);
void __cdecl Matrix33_ctor(Matrix33* m, const float* src);
void __cdecl Opaque();

// The +0xc0..+0xc8 vector element operations declared cdecl to force call relocations.
void* __cdecl eastl_erase_effect(int a, int b, int c);           // 0xc8a890 support
void  __cdecl FUN_00c88d90(void* p);

// ===========================================================================
// @ 0x00c89d60
// ===========================================================================
void __fastcall F89d60(Spatial* s)
{
    if (s->vecBegin != s->vecEnd) {
        Opaque();
    }
}

// ===========================================================================
// @ 0x00c8a020  find effect by id, set +0x14
// ===========================================================================
void __fastcall F8a020(Spatial* s, int unused, int id, float val)
{
    EffectElem* p = s->vecBegin;
    if (p == s->vecEnd)
        return;
    while (p->id != id) {
        p += 1;                       // +0x3c bytes via struct stride
        if (p == s->vecEnd)
            return;
    }
    p->f14 = val;
    if (p->p38 != 0) {
        void** vt = *(void***)p->p38;
        ((void(__thiscall*)(int*, void*))vt[0x20 / 4])((int*)0, (void*)0);
        ((void(__thiscall*)(int*, void*))vt[0x18 / 4])((int*)0, (void*)0);
    }
}

// ===========================================================================
// @ 0x00c8a110  find effect by id, set byte +0x10
// ===========================================================================
void __fastcall F8a110(Spatial* s, int unused, int id, char val)
{
    EffectElem* p = s->vecBegin;
    if (p == s->vecEnd)
        return;
    while (p->id != id) {
        p += 1;
        if (p == s->vecEnd)
            return;
    }
    p->b10 = val;
    if (p->p38 != 0) {
        void** vt = *(void***)p->p38;
        ((void(__thiscall*)(int*, void*))vt[0x20 / 4])((int*)0, (void*)0);
        ((void(__thiscall*)(int*, void*))vt[0x18 / 4])((int*)0, (void*)0);
    }
}

// ===========================================================================
// @ 0x00c8a200
// ===========================================================================
void __fastcall F8a200(Spatial* s, int unused, int id, int val)
{
    EffectElem* p = s->vecBegin;
    if (p == s->vecEnd)
        return;
    while (p->id != id) {
        p += 1;
        if (p == s->vecEnd)
            return;
    }
    Opaque();
}

// ===========================================================================
// @ 0x00c8a420  destructor: reset vtable, release +0xa0, release +0x9c
// ===========================================================================
void __fastcall F8a420(Spatial* s)
{
    s->vt = 0;
    FUN_00c895f0((char*)s + 0xc0);
    if (s->pa0 != 0) {
        void** vt = *(void***)s->pa0;
        ((void(__thiscall*)(int*))vt[4 / 4])(s->pa0);
    }
    int* p = s->p9c;
    if (p != 0) {
        int refs = p[0x10];
        if (refs > 1) { p[0x10] = refs - 1; return; }
        void** vt = *(void***)p;
        ((void(__thiscall*)(int*, unsigned int))vt[0x170 / 4])(p, (unsigned int)p[1] >> 31);
    }
}

// ===========================================================================
// @ 0x00c8a480
// ===========================================================================
void __cdecl F8a480(char* p)
{
    (void)p;
    Opaque();
}

// ===========================================================================
// @ 0x00c8a4a0  SP::cSpatialObject::GetWorldExtents
// ===========================================================================
cSPBoundingBox* __fastcall GetWorldExtents(Spatial* s, int, cSPBoundingBox* box)
{
    float* f = s->GetExtents();
    box->mMin.x = f[0];
    box->mMin.y = f[1];
    box->mMin.z = f[2];
    box->mMax.x = f[3];
    box->mMax.y = f[4];
    box->mMax.z = f[5];
    Matrix33 m;
    Matrix33_ctor(&m, 0);
    LocalToWorldTransform(s, &m);
    cSPBoundingBox_Transform(box, &m);
    return box;
}

// ===========================================================================
// @ 0x00c8a550  SP::cSpatialObject::LoadModel
// ===========================================================================
unsigned int __fastcall LoadModel(Spatial* s, void*, int* model)
{
    (void)model;
    Opaque();
    return 0;
}

// ===========================================================================
// @ 0x00c8a890  eastl::vector<tEffectInfo>::erase
// ===========================================================================
EffectElem* __fastcall EraseEffect(Spatial* s, int, EffectElem* first, EffectElem* last)
{
    EffectElem* p = first;
    while (p != last) { p->p38 = 0; ++p; }
    return first;
}

// ===========================================================================
// @ 0x00c8a910
// ===========================================================================
void __fastcall F8a910(Spatial* s, int, unsigned int a, unsigned int b)
{
    (void)a; (void)b;
    Opaque();
}
