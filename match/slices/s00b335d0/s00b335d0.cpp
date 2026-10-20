// Slice s00b335d0 -- unnamed gameplay/front-end state class (vtable at +0,
// state field +0x84, ref-counted client +0x88, flags +0x10e/+0x10f), the
// star-database reload loop, a heap sift-up helper, and a terrain-height query.
// No dev-PDB symbols exist for this module; names are FUN_<va>.
#include "types.h"
#include <string.h>

typedef unsigned char  u8;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// Out-of-line callees (named by retail VA so the difftest resolver can bind).
// ---------------------------------------------------------------------------
void* __cdecl   FUN_00b3d340();
void* __cdecl   FUN_00b3d2a0();                       // SP::StarManager
void* __cdecl   SP_ObjectTemplateDB();
void* __cdecl   SP_PlanetModel();
void  __cdecl   Fn436ce0(float* out, int x);
void* __cdecl   Fn449c20(float* out);                 // SP::normalized_safe
float __fastcall FUN_00c887c0(int value);

struct TFn0  { void  f(); };                          // 0x00b28c20
struct TFn1  { void  f(); };                          // 0x00bb8b20
struct TFn2  { int   f(); };                          // 0x00bb9b80
struct TFn3  { void  f(int); };                       // 0x00b3d520
struct TFnH  { float f(int); };                       // 0x00f927c0
struct TFnN  { void* f(float*); };                    // 0x00f92c20

// ---------------------------------------------------------------------------
// Common object: vptr +0, state tag +0x84, owned object +0x88.
// ---------------------------------------------------------------------------
struct RefObj {
    virtual void v00();
    virtual void Release();          // slot 1 (+0x04)
};

struct StateObj {
    virtual void s00();              // +0x00
    virtual void s01();              // +0x04
    virtual void s02();              // +0x08
    virtual void s03();              // +0x0c
    virtual void s04();              // +0x10
    virtual void s05();              // +0x14
    virtual void s06();              // +0x18
    virtual void s07();              // +0x1c
    virtual void s08();              // +0x20
    virtual void s09();              // +0x24
    virtual void s10();              // +0x28
    virtual void s11();              // +0x2c
    virtual void s12();              // +0x30
    virtual void s13();              // +0x34
    virtual void s14();              // +0x38
    virtual void s15();              // +0x3c
    virtual void s16();              // +0x40
    virtual void s17();              // +0x44
    virtual void s18();              // +0x48
    virtual void s19();              // +0x4c
    virtual void s20();              // +0x50
    virtual void s21();              // +0x54
    virtual void s22();              // +0x58
    virtual void s23(int, int, int, int, int, float);  // +0x5c
    char  mPad0[0x84 - 4];
    void* mState;                    // +0x84
    RefObj* mRef;                    // +0x88
    char  mPad1[0x10e - 0x8c];
    u8    m10e;                      // +0x10e
    u8    m10f;                      // +0x10f

    void FUN_00b33ca0(int a, int b, int c);
    void FUN_00b33d00();
    void FUN_00b33d20();
    void FUN_00b33d40(void* state);
    void FUN_00b33dd0();
    u8   FUN_00b33e10(unsigned id);
};

// @ 0x00b33c30
void __cdecl FUN_00b33c30(double value, int a, int b)
{
    extern void* PTR_01569488;
    extern void FUN_008822e0(double, int, int, int, int);
    FUN_008822e0(value, a, b, (int)PTR_01569488, 0x01460564);
}

// @ 0x00b33c70
void __fastcall FUN_00b33c70(char* p)
{
    typedef void (__thiscall* Fn)(void*);
    ((Fn)(*(void**)(*(char**)(p - 8) + 0x10)))(p - 8);
}

// @ 0x00b33ca0
void StateObj::FUN_00b33ca0(int a, int b, int c)
{
    s23(a, b, c, -1, -1, 1.0f);
}

// @ 0x00b33d00
void StateObj::FUN_00b33d00()
{
    if (mState != (void*)0x1654c00) {
        typedef void (__thiscall* Fn)(void*);
        char* vt = *(char**)this;
        void* fn = *(void**)(vt + 0x14);
        mState = (void*)0x1654c08;
        ((Fn)fn)(this);
    }
}

// @ 0x00b33d20
void StateObj::FUN_00b33d20()
{
    typedef void (__thiscall* Fn)(void*);
    char* vt = *(char**)this;
    void* fn = *(void**)(vt + 0x18);
    mState = (void*)0x1654c00;
    ((Fn)fn)(this);
}

// @ 0x00b33d40
void StateObj::FUN_00b33d40(void* state)
{
    RefObj* r = mRef;
    if (r != 0) {
        mRef = 0;
        r->Release();
    }
    typedef void (__thiscall* Fn)(void*);
    switch ((int)state) {
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
    case 0x1654c06:
    case 0x1654c10:
    case 0x2ccd1d2:
        (*(Fn*)(*(char**)this + 0x14))(this);
        break;
    default:
        (*(Fn*)(*(char**)this + 0x18))(this);
        break;
    }
    mState = state;
}

// @ 0x00b33dd0
void StateObj::FUN_00b33dd0()
{
    RefObj* r = mRef;
    if (r != 0) {
        mRef = 0;
        r->Release();
    }
    if (mState != (void*)-1) {
        typedef void (__thiscall* Fn)(void*);
        (*(Fn*)(*(char**)this + 0x18))(this);
        mState = (void*)-1;
    }
}

// @ 0x00b33e10
u8 StateObj::FUN_00b33e10(unsigned id)
{
    switch (id) {
    case 0x2399be55: return m10e;
    case 0x24682294:
    case 0x476a98c7: return m10f;
    default: return 0;
    }
}

// @ 0x00b33ea0
void __cdecl FUN_00b33ea0(int* base, int start, int pos, int value)
{
    int parent = (pos - 1) >> 1;
    if (pos > start) {
        do {
            if (!(FUN_00c887c0(base[parent]) < FUN_00c887c0(value)))
                break;
            base[pos] = base[parent];
            pos = parent;
            parent = (pos - 1) >> 1;
        } while (pos > start);
    }
    base[pos] = value;
}

// ---------------------------------------------------------------------------
// 0x00b338f0 -- reload the star database and notify every registered template.
// ---------------------------------------------------------------------------
struct StarManager {
    char  mPad[0xf0];
    int*  mpBegin;                    // +0xf0
    int*  mpEnd;                      // +0xf4
};

// @ 0x00b338f0
void __cdecl FUN_00b338f0()
{
    void* a = FUN_00b3d340();
    ((TFn0*)a)->f();
    StarManager* sm = (StarManager*)FUN_00b3d2a0();
    ((TFn1*)sm)->f();
    StarManager* sm2 = (StarManager*)FUN_00b3d2a0();
    int count = (int)(sm2->mpEnd - sm2->mpBegin);
    for (int i = 0; i < count; i++) {
        int* db = (int*)SP_ObjectTemplateDB();
        int obj = sm2->mpBegin[i];
        int v = ((TFn2*)(void*)obj)->f();
        typedef void (__thiscall* Fn)(void*, int);
        (*(Fn)(*(char**)db + 0x60))(db, v);
    }
}

// ---------------------------------------------------------------------------
// 0x00b34280 -- terrain height / water height query with optional normal.
// ---------------------------------------------------------------------------
struct TerrainMap {
    char  mPad[0x34];
    float m34;                        // +0x34
    float m38;                        // +0x38
    float m3c;                        // +0x3c
};

// @ 0x00b34280
float __cdecl FUN_00b34280(int, int, int x, float* out, char useWater, char waterOnly)
{
    int pm = (int)SP_PlanetModel();
    if (pm == 0)
        return 0.0f;
    int* tm = *(int**)(pm + 0x24);
    if (tm == 0)
        return 0.0f;
    typedef void* (__thiscall* Fn)(void*);
    TerrainMap* map = (TerrainMap*)(*(Fn)(*(char**)tm + 0x0c))(tm);
    if (waterOnly)
        return map->m3c * map->m38 + map->m34;

    float h = ((TFnH*)map)->f(x);
    if (useWater) {
        float w = map->m3c * map->m38 + map->m34;
        if (w >= h) {
            h = w;
            if (out != 0) {
                float v[3];
                Fn436ce0(v, x);
                memcpy(out, v, 12);
            }
            return h;
        }
    }
    if (out != 0) {
        if (*(char*)(pm + 0xf0) != 0) {
            float v[3];
            void* r = Fn449c20(v);
            memcpy(out, r, 12);
        } else {
            float v[3];
            void* r = ((TFnN*)map)->f(v);
            memcpy(out, r, 12);
        }
    }
    return h;
}

// ---------------------------------------------------------------------------
// Large front-end state dispatchers (not reconstructed byte-exactly).
// ---------------------------------------------------------------------------
// @ 0x00b335d0
void __cdecl FUN_00b335d0(void* from, void* to)
{
    (void)from; (void)to;
}

// @ 0x00b33970
void __cdecl FUN_00b33970(void* from, void* to)
{
    (void)from; (void)to;
}

// @ 0x00b33f50
void __cdecl FUN_00b33f50(void* self, int a, int b, void* c, int d)
{
    (void)self; (void)a; (void)b; (void)c; (void)d;
}

// @ 0x00b34380
void __cdecl FUN_00b34380(int* self, float dt)
{
    (void)self; (void)dt;
}
