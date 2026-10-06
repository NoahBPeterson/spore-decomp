// Slice s00e61000 -- SP::cCellMode / cell-stage helpers (cell game update + transforms).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- external data (addresses are masked relocations)
extern float  g_16b3dd0;
extern float  g_1485720;
extern float  g_13eb1bc;
extern float  g_1485548;
extern float  g_15a7c28;
extern float  g_15a7c2c;
extern float  g_15a7c30;
extern float  g_16b3c54;
extern float  g_16b3c58;
extern float  g_16b3c5c;
extern float  g_16b3c28;
extern float  g_16b3c2c;
extern float  g_16b3c30;
extern float  g_14851ec;
extern float  g_13eb8b0;
extern char   g_15a7c40[];
extern char   g_16b3c60[];
extern char   g_16b3dac[];
extern char   g_1667bac[];
extern char   g_1667bae[];
extern int    g_16b4430;
extern int    g_16b442c;

// ---------------------------------------------------------------- external callees
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int);  // 0x00f473a0
void  __cdecl EA_Free(void*);                                             // 0x00f47380
int   __cdecl FNVHash(const char*, unsigned, int);                        // 0x00932e80
int   __cdecl CreateEffectSafe(int, int, int, int);                       // 0x00628450
void  __cdecl Matrix3FromFacingAndUp(void*, const float*, const void*);   // 0x0069b440
void  __cdecl Vector3_Normalize(float*, const float*);                    // 0x00436ce0
void  __cdecl sCellSetPosition(void*, const float*);                      // 0x00e5e590
float __cdecl rand01(float, float);                                       // 0x00572a10
int   __cdecl f5c9d0(void);                                               // 0x00e5c9d0
void  __cdecl f83910(void*, int, int, int);                               // 0x00e83910
void  __cdecl f828c0(void);                                               // 0x00e828c0
void  __cdecl f82be0(unsigned, int);                                      // 0x00e82be0
int*  __cdecl f4ce60(void*);                                              // 0x00e4ce60
int*  __cdecl f4ce40(void*);                                              // 0x00e4ce40
int*  __cdecl f823a0(void*, void*);                                       // 0x00e823a0
int   __cdecl f82970(void);                                               // 0x00e82970
void  __cdecl f82920(void*);                                              // 0x00e82920
void  __cdecl f82ce0(void*);                                              // 0x00e82ce0
void  __cdecl f91ff50(void*);                                             // 0x0091ff50
void  __cdecl f4fcd0(void*);                                              // 0x00e4fcd0
void* __cdecl memset_stub(void*, int, unsigned);                          // 0x011e073e
void  __cdecl f84150(int, int, void*);                                    // 0x00e84150
void* __cdecl f5cae0(void);                                               // 0x00e5cae0
void* __cdecl f453b20(void*, const void*, float);                         // 0x00453b20
void  __fastcall f697960(void*);                                          // 0x00697960
void  __fastcall f6b5060(void*);                                          // 0x006b5060
void  __fastcall f6b5240(void*);                                          // 0x006b5240
void  __fastcall fC2e4e0(void*);                                          // 0x00c2e4e0
void  __fastcall f743b50(void*);                                          // 0x00743b50
void  __fastcall f82130(void*);                                           // 0x00e82130
void* __cdecl EA_Free2(void*);                                            // (unused)

// ---------------------------------------------------------------- class stubs
struct IRefCounted {
    virtual int AddRef();
    virtual int Release();
};

struct Matrix33 {
    float x[3];
    float y[3];
    float z[3];
    Matrix33& operator=(const Matrix33&);   // 0x0041cb40 (out of line)
};

struct cSPTransform {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    float          mTranslation[3];     // +0x04
    float          mScale;              // +0x10
    Matrix33       mRotation;           // +0x14
    cSPTransform()
    {
        mFlags = 0;
        mModificationCount = 0;
        mTranslation[0] = g_16b3c28;
        mTranslation[1] = g_16b3c2c;
        mTranslation[2] = g_16b3c30;
        mScale = g_1485720;
        mRotation = *(const Matrix33*)g_16b3dac;
    }
    cSPTransform(const cSPTransform& o)
    {
        mFlags = o.mFlags;
        mModificationCount = o.mModificationCount;
        mTranslation[0] = o.mTranslation[0];
        mTranslation[1] = o.mTranslation[1];
        mTranslation[2] = o.mTranslation[2];
        mScale = o.mScale;
        mRotation = o.mRotation;
    }
    cSPTransform& operator=(const cSPTransform&);   // 0x00537dc0 (out of line)
};

struct RefPtr {
    void* mp;
    RefPtr() : mp(0) {}
    RefPtr(const RefPtr& o) : mp(o.mp) { if (mp) ((IRefCounted*)mp)->AddRef(); }
    RefPtr& operator=(const RefPtr& o) {
        void* nn = o.mp;
        void* old = mp;
        if (nn != old) {
            if (nn) ((IRefCounted*)nn)->AddRef();
            mp = nn;
            if (old) ((IRefCounted*)old)->Release();
        }
        return *this;
    }
    ~RefPtr() { if (mp) ((IRefCounted*)mp)->Release(); }
};

// 0x74-byte transform pair + refptr
struct CellXform {
    cSPTransform mBase;     // +0x00
    cSPTransform mChild;    // +0x38
    RefPtr       mPtr;      // +0x70
};
CellXform* CopyCellFwd(CellXform* first, CellXform* last, CellXform* result);
CellXform* CopyCellBwd(CellXform* first, CellXform* last, CellXform* result);

// 0x48-byte small record with a rotation
struct SmallRec {
    char    f00;            // +0x00
    int     f04;            // +0x04
    float   f08;            // +0x08
    float   f0c;            // +0x0c
    float   f10;            // +0x10
    Matrix33 rot;           // +0x14
    float   f38;            // +0x38
    float   f3c;            // +0x3c
    float   f40;            // +0x40
    float   f44;            // +0x44
    SmallRec(const SmallRec&);
};
SmallRec::SmallRec(const SmallRec& o)
{
    f00 = o.f00;
    f04 = o.f04;
    f08 = o.f08;
    f0c = o.f0c;
    f10 = o.f10;
    rot = o.rot;
    f38 = o.f38;
    f3c = o.f3c;
    f40 = o.f40;
    f44 = o.f44;
}

struct CollPair {
    int  first;
    char second[0x28];
};

// ---------------------------------------------------------------- cell globals
struct CellObj5190;
struct Invoker1c { int Call(); };
struct VObj {
    virtual void v0();
    virtual void v1();                  // +0x04
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11(void*, int);       // +0x2c
};
struct IRegistrar {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void Register(void*, void*, const char*);   // +0x20
};
struct Sub10 { char pad[0xc]; };
struct CellObj5190 {
    char            pad0[0xc];
    int             field_0c;        // +0x0c
    Sub10           sub10;           // +0x10
    Invoker1c*      field_1c;        // +0x1c
    int             field_20;        // +0x20
    int             field_24;        // +0x24
    int             field_28;        // +0x28
    int             field_2c;        // +0x2c
    char            pad30[0xb4];
    int             field_e4;        // +0xe4
    bool            field_e8;        // +0xe8
};

struct cCellGame {
    char            pad0[0x40fc];
    unsigned int    midPlayerCell;   // +0x40fc
    char            pad4100[0x1c];
    int             field_411c;      // +0x411c
    char            pad4120[0x1044]; // 0x4120 .. 0x5164
    int             field_5164;      // +0x5164
    char            field_5168;      // +0x5168
    char            pad5169[0x27];
    CellObj5190*    field_5190;      // +0x5190
    char            pad5194[0x46];
    char            field_51da;      // +0x51da
};

struct cCellGfx {
    char            pad0[0x161bc];
    unsigned int    field_161bc;     // +0x161bc
    char            pad161c0[0x8];
    unsigned int    field_161c8;     // +0x161c8
};

struct Vec3 { float x, y, z; };
struct WorldObj { char pad[0x48]; Vec3 a; Vec3 b; Vec3 c; };

extern cCellGame*   gspCellGame;     // 0x016b3c04
extern cCellGfx*    gspCellGfx;      // 0x016b3c08
extern WorldObj*    g_16b3c0c;       // 0x016b3c0c
extern char         g_016b3c00;      // 0x016b3c00

void FUN_00e611b0(void);
void FUN_00e61b90(int, int, int, int);

// ================================================================ 0x00e61140
void FUN_00e61140(void)
{
    int a = gspCellGame->field_5190->field_1c->Call();
    int d = a - gspCellGame->field_5190->field_2c + 0x32;
    int b = f5c9d0();
    f83910(&gspCellGame->field_5190->sub10, d, b, gspCellGame->field_5164);
    f828c0();
    gspCellGame->field_5168 = 1;
}

// ================================================================ 0x00e61320
bool FUN_00e61320(int param)
{
    cCellGame* g = gspCellGame;
    if (g->field_5190->field_0c == 0)
        return false;
    switch (param) {
    case 0:
        FUN_00e611b0();
        break;
    case 1:
        g->field_5190->field_e8 = (g->field_5190->field_e8 == 0);
        return true;
    }
    return true;
}

// ================================================================ 0x00e61510
void FUN_00e61510(int* param)
{
    VObj** slot = (VObj**)&gspCellGame->field_5190;
    VObj* old = *slot;
    g_016b3c00 = 1;
    if (old != 0) {
        *slot = 0;
        old->v1();
    }
    ((VObj*)param)->v11(slot, 0);
}

// ================================================================ 0x00e616c0  RegisterAppMode_cCellMode
void* operator new(unsigned, const char*, int, int, const char*, int);
struct B1 { virtual void b1(); };
struct B2 { virtual void b2(); };
struct AppModeC : B1, B2 {
    virtual void d();
    int x;
};
void RegisterAppMode_cCellMode(IRegistrar* self)
{
    AppModeC* m = new ("App", 0, 0, 0, 0) AppModeC();
    self->Register(m, (void*)0x1654c00, "Game_Cell");
}

// ================================================================ 0x00e618c0
CellXform* CopyCellFwd(CellXform* first, CellXform* last, CellXform* result)
{
    while (first != last) {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

// ================================================================ 0x00e61930
CellXform* CopyCellBwd(CellXform* first, CellXform* last, CellXform* result)
{
    while (last != first) {
        --last;
        --result;
        *result = *last;
    }
    return result;
}

// ================================================================ force-emission helpers
// (these exist only so the compiler emits the implicit special members under test)
__declspec(noinline) CellXform* ForceCopyCellXform(const CellXform& x)
{
    return new CellXform(x);
}
__declspec(noinline) CellXform* ForceNewCellXform()
{
    return new CellXform();
}
#pragma auto_inline(off)
__declspec(noinline) SmallRec* ForceCopySmall(const SmallRec& x)
{
    return new SmallRec(x);
}
#pragma auto_inline(on)

CollPair* lower_bound(CollPair* first, CollPair* last, const int* value)
{
    int n = (int)((last - first));
    while (n > 0) {
        int i = n >> 1;
        CollPair* p = first + i;
        if (p->first < *value) {
            first = p + 1;
            n -= i + 1;
        } else {
            n = i;
        }
    }
    return first;
}

// ================================================================ 0x00e61050
struct IEffect {
    virtual int AddRef();       // +0x00
    virtual int Release();      // +0x04
    virtual int v2(int);        // +0x08
    virtual int v3(int);        // +0x0c
    virtual int v4();           // +0x10
    virtual int v5();           // +0x14
    virtual int v6(void*);      // +0x18
};

void FUN_00e61050(int p1, IEffect** p2, int p3, int p4, int p5, char flag)
{
    if (flag) {
        if (*p2 == 0) {
            int h = FNVHash("cell_hostileNPC_growl", 0x811c9dc5, 1);
            CreateEffectSafe(p1, h, 0, (int)p2);
            (*p2)->v2(0);
        }
        cSPTransform x;
        f84150(p4, p5, &x);
        (*p2)->v6(&x);
        return;
    }
    if (*p2 != 0) {
        (*p2)->v3(0);
        (*p2)->Release();
        *p2 = 0;
    }
}

// ================================================================ 0x00e611b0
struct Pool { void* Find(int); };

void FUN_00e611b0(void)
{
    char h[8];
    f743b50(h);
    int* pi = f4ce60(h);
    if (gspCellGame->field_5190->field_e4 < *pi) {
        if (!(g_16b4430 & 1)) {
            g_16b4430 |= 1;
            g_16b442c = FNVHash("clg-notenoughnanites", 0x811c9dc5, 1);
        }
        f82be0(g_16b442c, 1);
        f82130(h + 4);
        return;
    }
    char* e = (char*)((Pool*)((char*)gspCellGame + 0x1c))->Find(gspCellGame->field_411c);
    if (e != 0) {
        float lc = *(float*)(e + 0x4c);
        float l8 = *(float*)(e + 0x50);
        float l4 = *(float*)(e + 0x54);
        float l0 = (float)pi[1];
        lc = rand01(-1.0f, 1.0f) * l0 + lc;
        l8 = rand01(-1.0f, 1.0f) * l0 + l8;
        float v[3];
        v[0] = lc; v[1] = l8; v[2] = l4;
        sCellSetPosition(e, v);
        g_16b3c0c->a.x = lc; g_16b3c0c->a.y = l8; g_16b3c0c->a.z = l4;
        g_16b3c0c->b.x = lc; g_16b3c0c->b.y = l8; g_16b3c0c->b.z = l4;
        g_16b3c0c->c.x = lc; g_16b3c0c->c.y = l8; g_16b3c0c->c.z = l4;
        gspCellGame->field_5190->field_e4 = gspCellGame->field_5190->field_e4 - *pi;
    }
    f82130(h + 4);
}

// ================================================================ 0x00e61370
void FUN_00e61370(float* out, cSPTransform* p, float s)
{
    Matrix33 tmp;
    Matrix33 m;
    m = *(Matrix33*)f453b20(&tmp, g_15a7c40, g_16b3dd0 * s);
    float f0 = (m.x[0] * g_15a7c28 + m.y[0] * g_15a7c2c + m.z[0] * g_15a7c30) * g_1485548;
    float f1 = (m.x[1] * g_15a7c28 + m.y[1] * g_15a7c2c + m.z[1] * g_15a7c30) * g_1485548;
    float f2 = (m.x[2] * g_15a7c28 + m.y[2] * g_15a7c2c + m.z[2] * g_15a7c30) * g_1485548;
    out[0] = f0; out[1] = f1; out[2] = f2;
    if (p->mFlags & 2) {
        out[0] = p->mRotation.x[0] * f0 + p->mRotation.y[0] * f1 + p->mRotation.z[0] * f2;
        out[1] = p->mRotation.x[1] * f0 + p->mRotation.y[1] * f1 + p->mRotation.z[1] * f2;
        out[2] = p->mRotation.x[2] * f0 + p->mRotation.y[2] * f1 + p->mRotation.z[2] * f2;
    }
    float sc = p->mScale;
    out[0] = sc * out[0] + p->mTranslation[0];
    out[1] = sc * out[1] + p->mTranslation[1];
    out[2] = out[2] * sc + p->mTranslation[2];
}

// ================================================================ 0x00e61550 / 0x00e61a50
struct CellAbility : B1, B2 {
    int  f08;
    int  f0c;
    int  f10, f14, f18;
    int  f1c, f20, f24, f28;
    int  f2c;
    int  f30;
    char o34[0x68 - 0x34];
    char b68, b69;
    int  f6c, f70, f74;
    char o78[0x80 - 0x78];
    int  f7c;
    char buf80[0x60];
    char b_e0, b_e1, b_e2;
    char pad_e3;
    int  f_e4;
    char b_e8, b_e9;
    char pad_ea[0xec - 0xea];
    CellAbility()
    {
        f10 = 0;
        f7c = 1;
        b_e2 = 1;
        f14 = 0; f18 = 0;
        b68 = 0;
        f1c = 0; f20 = 0; f24 = 0; f28 = 0;
        b69 = 0;
        f70 = 0; f6c = 0;
        f_e4 = 0;
        b_e8 = 0;
        f74 = 0;
        b_e0 = 0; b_e1 = 0;
        f30 = 10;
        f2c = 0;
        f91ff50(o78);
        f4fcd0(o34);
        memset_stub(buf80, 0, 0x60);
        gspCellGame->field_51da = 0;
        b_e9 = 0;
    }
};

CellAbility* FUN_00e61550()
{
    return new ("Simulator", 0, 0, 0, 0) CellAbility();
}

struct SaveGameObj : B1, B2 {
    int f08;
    int pad0c;
    int f10, f14, f18;
    char pad1c[0xec - 0x1c];
    SaveGameObj()
    {
        f08 = 0;
        f10 = 0; f14 = 0; f18 = 0;
    }
};

// 0x00e61a50
void* __stdcall CreateInstance_SaveGame(void*, void*)
{
    return new ("SP_Simulator/CellSaveGame/COM", 0, 0, 0, 0) SaveGameObj();
}

// ================================================================ 0x00e61630
CellAbility* FUN_00e61630()
{
    CellAbility* a = FUN_00e61550();
    char h[8];
    f743b50(h);
    int* r = f4ce40(h);
    a->f0c = *r;
    a->f7c = f82970();
    switch (a->f0c) {
    case 0:
    case 2: {
        float v[3];
        f82920(v);
        a->f10 = v[0]; a->f14 = v[1]; a->f18 = v[2];
        break;
    }
    case 1:
        f82ce0(&a->f10);
        break;
    }
    f82130(h + 4);
    return a;
}

// ================================================================ 0x00e61aa0 / 0x00e61b00
struct Obj9c { void Init(); void Destroy(); };
struct CStrObj { void Init(); void Destroy(); };

struct BigMode {
    char        pad0[0x90];
    int         h90;        // +0x90
    int         h94;        // +0x94
    int         h98;        // +0x98
    char        o9c[0x910 - 0x9c];
    const void* s910;       // +0x910
    const void* s914;       // +0x914
    const void* s918;       // +0x918
    int         pad91c;     // +0x91c
    char        str920[0x1c];
    BigMode();
    ~BigMode();
};

BigMode::BigMode()
{
    f697960(this);
    h90 = 0;
    h94 = 0;
    Obj9c* o = (Obj9c*)o9c;
    h98 = 0;
    o->Init();
    s910 = g_1667bac;
    s914 = g_1667bac;
    s918 = g_1667bae;
    ((CStrObj*)str920)->Init();
}

BigMode::~BigMode()
{
    ((CStrObj*)str920)->Destroy();
    int a = *(int*)((char*)this + 0x910);
    unsigned int c = (*(int*)((char*)this + 0x918) - a) & 0xfffffffeu;
    if ((int)c > 2 && a != 0)
        EA_Free((void*)a);
    ((Obj9c*)o9c)->Destroy();
    if (*(void**)((char*)this + 0x98) != 0)
        (*(IEffect**)((char*)this + 0x98))->Release();
    {
        char* rc = *(char**)((char*)this + 0x94);
        if (rc != 0) {
            int n = *(int*)(rc + 4) - 1;
            *(int*)(rc + 4) = n;
            if (n == 0) {
                *(int*)(rc + 4) = 1;
                (*(void(__thiscall**)(char*, int))rc)(rc, 1);
            }
        }
    }
    if (*(void**)((char*)this + 0x90) != 0)
        (*(void(__thiscall**)(char*))((*(char***)((char*)this + 0x90))[2]))(*(char**)((char*)this + 0x90));
}

// ================================================================ 0x00e61b90
void FUN_00e61b90(int obj, int p2, int flag, int facing)
{
    int* src = (int*)p2;
    int effId = (flag == 0) ? (int)gspCellGfx->field_161c8 : (int)gspCellGfx->field_161bc;
    IEffect* eff = 0;
    CreateEffectSafe(effId, *src, 0, (int)&eff);
    float* pos = (float*)obj;
    if (pos == 0) {
        if (eff) eff->v2(0);
        return;
    }
    float dir[3];
    if (facing == 0) {
        Vec3* v = (Vec3*)f5cae0();
        dir[0] = v->x; dir[1] = v->y; dir[2] = v->z;
    } else {
        float* f = (float*)facing;
        float dx = f[0] - pos[0];
        float dy = f[1] - pos[1];
        float dz = f[2] - pos[2];
        if (dz * dz + dx * dx + dy * dy <= g_14851ec) {
            Vec3* v = (Vec3*)f5cae0();
            dir[0] = v->x; dir[1] = v->y; dir[2] = v->z;
        } else {
            float tmp[3]; tmp[0] = dx; tmp[1] = dy; tmp[2] = dz;
            Vector3_Normalize(dir, tmp);
        }
    }
    cSPTransform xf;
    *(float*)((char*)&xf + 0x14) = pos[0];
    *(float*)((char*)&xf + 0x18) = pos[1];
    *(float*)((char*)&xf + 0x1c) = pos[2];
    xf.mFlags |= 4;
    xf.mModificationCount++;
    float nd[3]; nd[0] = -dir[0]; nd[1] = -dir[1]; nd[2] = -dir[2];
    Matrix33 m;
    Matrix3FromFacingAndUp(&m, nd, g_15a7c40);
    xf.mRotation = m;
    xf.mFlags |= 2;
    xf.mModificationCount++;
    if (eff) {
        eff->v6(&xf);
        eff->v2(0);
    }
    if (facing != 0) {
        void** vt = *(void***)p2;
        typedef void (__thiscall *F11)(void*, int, int, int);
        ((F11)vt[0x10 / 4])((void*)p2, 9, facing, 1);
    }
    if (p2 != 0) {
        void** vt = *(void***)p2;
        typedef void (__thiscall *F1)(void*);
        ((F1)vt[1])((void*)p2);
    }
}

// ================================================================ 0x00e61d90
void FUN_00e61d90(int self, char* arg1, int idx)
{
    char h1[4], h2[4];
    f743b50(h1);
    int* pi = f823a0((void*)*(unsigned*)(self + 0x108), h1);
    f743b50(h2);
    int* arr = f823a0((void*)(unsigned)*pi, h2);
    if (arr[idx] != 0) {
        int flag = (*(int*)(self + 0x35c) != (int)gspCellGame->midPlayerCell) ? 1 : 0;
        FUN_00e61b90(self + 0x4c, (int)(arg1 + 0x4c), flag, 0);
    }
    f82130(h2);
    f82130(h1);
}


