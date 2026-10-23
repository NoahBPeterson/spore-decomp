// Slice s00ddb0d0 -- 0x0ddb0xx region: the simulator *manager* that owns the
// Boid/Swarm elements.  The manager is a vector<Boid*> (mpBegin/mpEnd/mpCapacity)
// plus the subsystem objects it hands out and releases; each Boid is the 0x100
// byte element built by FUN_00dd9510 (same layout as the neighbouring
// s00dd9510 slice).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (default /GS on).

#include "types.h"

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Vec4 { float x, y, z, w; };

// Timer block embedded at +0xb0 of every element; overlaps EA::Stopwatch.
namespace EA {
class Stopwatch {
public:
    unsigned __int64 mnStartTime;                // +0x00
    unsigned __int64 mnTotalElapsedTime;         // +0x08
    int mnUnits;                                 // +0x10
    float mfCoefficient;                         // +0x14
    void SetUnits(int units);                    // 0x0093a1a0
    void Restart();                              // 0x00571e80
    long long GetElapsedTimeFloat();             // 0x0093a3a0
    void SetBoolProperty();                      // 0x0093a2e0 (cDirectPropertyList alias)
};
}

// Element object (0x100 bytes).
struct Boid {
    void*  mResA;          // +0x00
    void*  mResB;          // +0x04
    void*  mEffect;        // +0x08
    Vec3   mPos;           // +0x0c
    Vec3   mV18;           // +0x18
    Vec3   mV24;           // +0x24
    Vec3   mV30;           // +0x30
    Vec3   mV3C;           // +0x3c
    Vec4   mM48[5];        // +0x48
    float  m98;            // +0x98
    float  m9C;            // +0x9c
    float  mA0;            // +0xa0
    float  mA4;            // +0xa4
    float  mA8;            // +0xa8
    int    mAC;            // +0xac
    EA::Stopwatch mTimer;  // +0xb0
    int    mC8;            // +0xc8
    int    mCC;            // +0xcc
    int    mD0;            // +0xd0
    char   mD4;            // +0xd4
    char   mD5;            // +0xd5
    char   mD6;            // +0xd6
    char   mD7;            // +0xd7
    char   mD8;            // +0xd8
    char   mD9[3];         // +0xd9
    float  mDC;            // +0xdc
    float  mE0;            // +0xe0
    float  mE4;            // +0xe4
    float  mE8;            // +0xe8
    float  mEC;            // +0xec
    float  mF0;            // +0xf0
    int    mF4;            // +0xf4 (attached creature, ref-counted)
    void*  mF8;            // +0xf8 (animation table)
    int    mFC;            // +0xfc (mode)
};

// Opaque subsystem object; call sites reach specific vtable slots, so model the
// object layout as { vftable* } and read the slot through the vftable pointer.
struct Mgr {
    void** vftable;                                  // +0x00
};

// vtable slot dispatch helpers (byte offsets from the vftable base).
template <class R> static inline R vtcall(Mgr* m, int off) {
    return ((R (__thiscall*)(Mgr*))m->vftable[off / 4])(m);
}

// Manager object owned by the slice.
struct Civ;
struct SpeciesMgr {
    int GetProfile(void* key);                       // 0x004df550 (thiscall, key)
};
struct Creature {
    int  SetValue(int p);                            // 0x00a04c80 (thiscall, 1 arg)
    int  SetFlag(char v);                            // 0x00a04ca0 (thiscall, 1 arg)
    int  AddRef();                                   // 0x00a02c30 (thiscall)
    int  Release();                                  // 0x00a05270 (thiscall)
};
struct SimMgr {
    Boid** mpBegin;        // +0x00
    Boid** mpEnd;          // +0x04
    Boid** mpCapacity;     // +0x08
    int    pad0C[2];       // +0x0c
    Mgr*   mpMgr14;        // +0x14 (Boid factory)
    Mgr*   mp18;           // +0x18
    Mgr*   mp1C;           // +0x1c
    Mgr*   mp20;           // +0x20
    char   pad24[0x14];    // +0x24
    char   mTransform38[0x38]; // +0x38 (transform copy target)
    Mgr*   mp70;           // +0x70 (model/creature manager)

    int    FUN_00ddb880(void* key);                   // 0x00ddb880
    int    FUN_00ddb9f0(Civ* civ);                    // 0x00ddb9f0
    void   FUN_00ddb0d0(Boid* e, int dtMs);           // 0x00ddb0d0
    void   FUN_00ddb600(Boid* e);                     // 0x00ddb600
    void   FUN_00ddb760();                            // 0x00ddb760
    void   FUN_00ddb790();                            // 0x00ddb790
    void   FUN_00ddbad0(void* key);                   // 0x00ddbad0
};

// ---------------------------------------------------------------------------
// Callees (addresses in comments).
// ---------------------------------------------------------------------------
extern "C" int  __cdecl FUN_00ddaa20();                           // 0x00ddaa20 (register arg)
extern "C" void __cdecl FUN_0040cd80(void* dst, void* src);       // 0x0040cd80 (0x40 byte copy)
extern "C" int  __cdecl FUN_00401090();                           // 0x00401090 GetSetting
extern "C" float __cdecl FUN_00572a10(float lo, float hi);       // 0x00572a10 RandomFloatRange
extern "C" int  __cdecl FUN_00c028b0(void* profile, int one);     // 0x00c028b0
extern "C" void* __cdecl FUN_00de7530(void* out);                 // 0x00de7530 first map element
extern "C" void* __cdecl FUN_00de56f0(void* out, void* key);      // 0x00de56f0 find by key
extern "C" void __cdecl FUN_00de9dc0(void* key);                  // 0x00de9dc0 insert by key
extern "C" void __cdecl FUN_00de74c0(void* key);                  // 0x00de74c0 erase by key
extern "C" void __cdecl FUN_00dd9130(void* out, void* in);        // 0x00dd9130 key builder
extern "C" void __cdecl FUN_00572020(int obj, int one);           // 0x00572020
extern "C" void __cdecl AudioSetListener3(int obj, float x, float y, float z); // 0x009fbc50
extern "C" void* __cdecl FUN_005b2500(void* out, const void* a, const void* b, float t); // Slerp
extern "C" void* __cdecl FUN_004a9b40(void* out, const void* q);  // QuaternionToMatrix
extern "C" void __cdecl Matrix3_Assign(void* m, const void* src); // 0x0041cb40
extern "C" void __cdecl FUN_00dde590(void* v, void* q);           // 0x00dde590
extern "C" void __cdecl FUN_00eb4420(void* v, void* q);           // 0x00eb4420 cView::UpdateTransform
extern "C" void __cdecl FUN_00dda500();                           // 0x00dda500
extern "C" int  __cdecl FUN_0067dd10();                           // 0x0067dd10 SP::App
extern "C" int  __cdecl FUN_0067dd50();                           // 0x0067dd50 (App variant)
extern "C" int  __cdecl FUN_0067dd80();                           // 0x0067dd80 SP::ModelManager
extern "C" int  __cdecl FUN_0067dd90();                           // 0x0067dd90 SP::LightingManager
extern "C" void* __cdecl FUN_00b96600(void* self, void** value);  // 0x00b96600 vector push_back
extern "C" void  __cdecl FUN_011e0744(void* dst, void* src, unsigned n); // 0x011e0744 eastl erase
extern "C" void* __cdecl FUN_00dd9510(void* mem);                 // 0x00dd9510 Boid ctor
extern "C" void* __cdecl FUN_00f473a0(unsigned size, const char* name,
                                      int a, int b, int c, int d); // 0x00f473a0 EAAllocate
extern "C" void __cdecl operator_delete__(void* p);               // 0x00f47380 operator delete
extern "C" int  __cdecl FUN_00a04c80(int self, int p);            // 0x00a04c80
extern "C" int  __cdecl FUN_00a04ca0(int self, char v);           // 0x00a04ca0
extern "C" int  __cdecl FUN_00a02c30(int self);                   // 0x00a02c30 AddRef
extern "C" int  __cdecl FUN_00a05270(int self);                   // 0x00a05270 Release
extern "C" void* __cdecl FUN_005c65e0(void* civ);                 // 0x005c65e0 GetCities
// x87 sine/cosine helpers -- the original inlines fsin/fcos, so a tiny asm
// helper is the faithful model (the result is returned in st(0)).
static float fs_sin(float x) { __asm { fld dword ptr x }; __asm { fsin }; }
static float fs_cos(float x) { __asm { fld dword ptr x }; __asm { fcos }; }
extern "C" char  g_16a0b04;                                       // 0x016a0b04

// Globals.
extern float g_16a0b0c, g_16a0b10, g_16a0b14;                     // Vec3 (0x016a0b0c)
extern float g_15a2d2c, g_15a2d30, g_15a2d34, g_15a2d38;          // Vec4 tuning (0x015a2d2c)
extern float g_16a0ba4, g_16a0ba8, g_16a0bac;                     // Vec3 axis (0x016a0ba4)
extern float g_16a1098;                                           // 0x016a1098
extern float g_16a0c3c, g_16a0c40, g_16a0c44;                     // quaternion scale (0x016a0c3c)
extern float g_15a2de4, g_15a2de8;                                // 0x015a2de4/8
extern float g_16a1018, g_16a1028;                                // RandomFloatRange args
extern int   g_16a1344;                                           // manager global (0x016a1344)
extern float g_147d2a8, g_15a2d00, g_1471064, g_13eb1bc, g_13ec480;
extern float g_13f9428, g_13f4fd0, g_1485720, g_1485378, g_14007f4;
extern float g_1473c70, g_147d24c;
extern Boid* g_16a0b90, *g_16a0b94;                               // global element vector
extern char  g_16a0b28[];                                         // 0x016a0b28 (9 dword matrix)
extern char  g_16a0c14[];                                         // 0x016a0c14 (table A)
extern char  g_16a0c28[];                                         // 0x016a0c28 (98-float table)

// ---------------------------------------------------------------------------
// @ 0x00ddb0d0
// Per-frame update of one element: advance the animation cursor, integrate
// velocity into position, rebuild the local transform matrices, push the
// transform into the attached views/effects and mirror the state word.
// ---------------------------------------------------------------------------
void SimMgr::FUN_00ddb0d0(Boid* e, int dtMs)
{
    float f = (float)dtMs;
    if (dtMs < 0)
        f += 4294967296.0f;
    f *= 0.001f;

    char ok = 1;
    if (e->mFC == 0) {
        FUN_00ddaa20();
        FUN_00ddaa20();
    }
    void** table = (void**)e->mF8;
    if (table == 0) {
        ok = 0;
    } else {
        int idx = e->mCC;
        void* node = table[idx];
        char r = ((char (__thiscall*)(void*, Boid*, float))(*(void***)node)[1])(node, e, f);
        if (r == 0) {
            ++e->mCC;
            if ((unsigned int)e->mCC < (unsigned int)((((int*)table)[1] - ((int*)table)[0]) >> 2)) {
                void* node2 = table[e->mCC];
                ((void (__thiscall*)(void*, Boid*))(*(void***)node2)[0])(node2, e);
            } else {
                ok = 0;
            }
        }
    }

    e->mV18.x += e->mV24.x * f;
    e->mV18.y += e->mV24.y * f;
    e->mV18.z += e->mV24.z * f;
    e->mPos.x += e->mV18.x * f;
    e->mPos.y += e->mV18.y * f;
    e->mPos.z += e->mV18.z * f;

    char* t = (char*)e->mResA;
    if (t != 0) {
        *(int*)(t + 0x18) = 0x3f800000;
        for (int i = 0; i < 9; ++i)
            ((int*)(t + 0x1c))[i] = ((int*)g_16a0b28)[i];
        *(float*)(t + 0x0c) = g_16a0b0c;
        *(float*)(t + 0x10) = g_16a0b10;
        *(float*)(t + 0x14) = g_16a0b14;
        *(unsigned short*)(t + 8) = 0;
        *(unsigned short*)(t + 0x0a) = 0;
        *(float*)(t + 0x0c) = e->mPos.x;
        *(float*)(t + 0x10) = e->mPos.y;
        *(unsigned short*)(t + 8) |= 4;
        *(short*)(t + 0x0a) += 1;
        *(float*)(t + 0x14) = e->mPos.z;
        if (e->m98 > g_13f9428)
            e->m98 = g_13f9428;
        *(short*)(t + 0x0a) += 1;
        *(float*)(t + 0x18) = e->m98;
        Vec4 q;
        FUN_004a9b40(&q, &e->mM48[0]);
        for (int j = 0; j < 9; ++j)
            ((int*)(t + 0x1c))[j] = ((int*)&q)[j];
        *(unsigned short*)(t + 8) |= 2;
        *(short*)(t + 0x0a) += 1;
    }

    if (e->mD4 != 0) {
        Mgr* app = (Mgr*)FUN_0067dd10();
        Mgr* a = (Mgr*)vtcall<int>(app, 0x18);
        Mgr* b = (Mgr*)vtcall<int>(a, 0x38);
        int i1 = 0, i2 = 0;
        if (b != 0) {
            i1 = vtcall<int>(b, 0x08);
            i2 = vtcall<int>(b, 0x08);
        }
        Vec4 local;
        local.x = g_1485378;
        local.y = g_16a0b0c;
        local.z = g_16a0b10;
        local.w = g_16a0b14;
        char mat[0x24];
        Matrix3_Assign(mat, g_16a0b28);
        if (i2 != 0) {
            FUN_00dde590((void*)i2, &local);
            FUN_0040cd80(t + 8, &local);
        } else if (i1 != 0) {
            FUN_00eb4420((void*)i1, &local);
            FUN_0040cd80(t + 8, &local);
        }
    }

    if (e->mResA != 0)
        FUN_0040cd80((char*)e->mResA + 8, this->mTransform38);
    if (e->mResB != 0)
        FUN_0040cd80((char*)e->mResB + 8, (char*)e->mResA + 8);
    if (e->mEffect != 0)
        ((void (__thiscall*)(Mgr*, int))((Mgr*)e->mEffect)->vftable[0x3c / 4])((Mgr*)e->mEffect, (int)((char*)e->mResA + 8));
    if (e->mD0 != 0)
        AudioSetListener3(e->mD0, e->mPos.x, e->mPos.y, e->mPos.z);
    if (e->mFC == 2) {
        int o = e->mF4;
        *(float*)(o + 4) = e->mPos.x;
        *(float*)(o + 8) = e->mPos.y;
        *(float*)(o + 0xc) = e->mPos.z;
        *(float*)(o + 0x10) = e->mM48[0].x;
        *(float*)(o + 0x14) = e->mM48[0].y;
        *(float*)(o + 0x18) = e->mM48[0].z;
        *(float*)(o + 0x1c) = e->mM48[0].w;
        *(float*)(o + 0x3c) = e->m98;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ddb480
// Re-orients one element: if the fourth matrix row points away from the
// accumulated basis (dot < 0) the row is flipped, then the orientation is
// either snapped to the timed target (past the blend window) or slerped
// towards it.
// ---------------------------------------------------------------------------
extern "C" char __stdcall FUN_00ddb480(Boid* e, int unused)
{
    char res = 1;
    float dot = ((e->mM48[3].w * e->mM48[0].w + e->mM48[3].z * e->mM48[0].z)
              + e->mM48[3].y * e->mM48[0].y)
              + e->mM48[3].x * e->mM48[0].x;
    if (dot < 0.0f) {
        float m = g_13eb1bc;
        e->mM48[3].x = e->mM48[3].x * m;
        e->mM48[3].y = e->mM48[3].y * m;
        e->mM48[3].z = e->mM48[3].z * m;
        e->mM48[3].w = e->mM48[3].w * m;
    }
    if (e->mTimer.mnStartTime != 0) {
        long long t = e->mTimer.GetElapsedTimeFloat();
        float f = ((float)t * e->mTimer.mfCoefficient) * g_13ec480;
        if (f > 1.0f) {
            ((EA::Stopwatch*)&e->mTimer)->SetBoolProperty();
            e->mM48[0].x = e->mM48[3].x;
            e->mM48[0].y = e->mM48[3].y;
            e->mM48[0].z = e->mM48[3].z;
            e->mM48[0].w = e->mM48[3].w;
            e->mC8 = 2;
            return 0;
        } else {
            Vec4 out;
            FUN_005b2500(&out, &e->mM48[4], &e->mM48[3], f);
            e->mM48[0] = out;
        }
    }
    return res;
}

// ---------------------------------------------------------------------------
// @ 0x00ddb600
// Destroy the element with the given resource pointer and erase it from the
// manager's vector.
// ---------------------------------------------------------------------------
void SimMgr::FUN_00ddb600(Boid* e)
{
    Boid** it = this->mpBegin;
    Boid** end = this->mpEnd;
    if (it == end)
        return;
    while (*it != e) {
        ++it;
        if (it == end)
            return;
    }
    Boid* b = *it;
    if (b->mF4 != 0) {
        b->mResA = 0;
        ((void (__thiscall*)(Mgr*, int))this->mp70->vftable[0x3c / 4])(this->mp70, b->mF4);
        ((Creature*)b->mF4)->Release();
        b->mF4 = 0;
    } else {
        Mgr* r = (Mgr*)b->mResA;
        void* rv = r;
        ((void (__thiscall*)(void*, int))((*(void***)rv)[0x16c / 4]))(rv, 0);
        Mgr* r2 = (Mgr*)b->mResA;
        int cnt = *(int*)((char*)r2 + 0x40);
        if (cnt > 1) {
            *(int*)((char*)r2 + 0x40) = cnt - 1;
        } else {
            unsigned f = ((*(unsigned int*)((char*)r2 + 4)) >> 31) & 1;
            ((void (__thiscall*)(Mgr*, unsigned))((*(void***)r2)[0x170 / 4]))(r2, f);
        }
    }
    if (b->mResB != 0) {
        Mgr* r = (Mgr*)b->mResB;
        void* rv = r;
        ((void (__thiscall*)(void*, int))((*(void***)rv)[0x16c / 4]))(rv, 0);
        Mgr* r2 = (Mgr*)b->mResB;
        int cnt = *(int*)((char*)r2 + 0x40);
        if (cnt > 1) {
            *(int*)((char*)r2 + 0x40) = cnt - 1;
        } else {
            unsigned f = ((*(unsigned int*)((char*)r2 + 4)) >> 31) & 1;
            ((void (__thiscall*)(Mgr*, unsigned))((*(void***)r2)[0x170 / 4]))(r2, f);
        }
    }
    if (b->mEffect != 0) {
        Mgr* ef = (Mgr*)b->mEffect;
        ((void (__thiscall*)(Mgr*, int))((*(void***)ef)[0xc / 4]))(ef, 0);
        ((void (__thiscall*)(Mgr*))((*(void***)ef)[0x4 / 4]))(ef);
    }
    if (b->mD0 != 0)
        FUN_00572020(b->mD0, 1);
    if (b->mResA != 0)
        operator_delete__(b);
    Boid** next = it + 1;
    if (next < this->mpEnd) {
        unsigned n = (unsigned)((char*)this->mpEnd - (char*)next);
        FUN_011e0744(it, next, n);
    }
    this->mpEnd -= 1;
}

// ---------------------------------------------------------------------------
// @ 0x00ddb760
// ---------------------------------------------------------------------------
void SimMgr::FUN_00ddb760()
{
    Boid** it = this->mpBegin;
    while (it != this->mpEnd) {
        this->FUN_00ddb600(*it);
        it = this->mpBegin;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ddb790
// Destroy every element, drop the model libraries and release the subsystem
// objects the manager owns.
// ---------------------------------------------------------------------------
void SimMgr::FUN_00ddb790()
{
    Boid** it = this->mpBegin;
    while (it != this->mpEnd) {
        this->FUN_00ddb600(*it);
        it = this->mpBegin;
    }
    Mgr* app = (Mgr*)FUN_0067dd50();
    ((void (__thiscall*)(Mgr*, int))app->vftable[0x50 / 4])(app, 20);
    Mgr* mm = (Mgr*)FUN_0067dd80();
    ((void (__thiscall*)(Mgr*, int))mm->vftable[0x18 / 4])(mm, 0x7b6877e);
    ((void (__thiscall*)(Mgr*, int))mm->vftable[0x18 / 4])(mm, 0x7d23d13);
    ((void (__thiscall*)(Mgr*, int))mm->vftable[0x18 / 4])(mm, 0x7d23d14);
    ((void (__thiscall*)(Mgr*, int))mm->vftable[0x18 / 4])(mm, 0x7d23d15);
    if (this->mp18 != 0) {
        Mgr* m = this->mp18;
        this->mp18 = 0;
        ((void (__thiscall*)(Mgr*))m->vftable[0x4 / 4])(m);
    }
    if (this->mp1C != 0) {
        Mgr* m = this->mp1C;
        this->mp1C = 0;
        ((void (__thiscall*)(Mgr*))m->vftable[0x4 / 4])(m);
    }
    Mgr* lm = (Mgr*)FUN_0067dd90();
    ((void (__thiscall*)(Mgr*, int))lm->vftable[0x20 / 4])(lm, 0x7b6877f);
    if (this->mp20 != 0) {
        Mgr* m = this->mp20;
        this->mp20 = 0;
        ((void (__thiscall*)(Mgr*))m->vftable[0x4 / 4])(m);
    }
    if (this->mpMgr14 != 0) {
        Mgr* m = this->mpMgr14;
        this->mpMgr14 = 0;
        ((void (__thiscall*)(Mgr*))m->vftable[0x4 / 4])(m);
    }
    ((void (__thiscall*)(Mgr*))this->mp70->vftable[0x20 / 4])(this->mp70);
    if (this->mp70 != 0) {
        Mgr* m = this->mp70;
        this->mp70 = 0;
        ((void (__thiscall*)(Mgr*))m->vftable[0x4 / 4])(m);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ddb880
// Create a Simulator element from a resource key and register it.
// ---------------------------------------------------------------------------
int SimMgr::FUN_00ddb880(void* key)
{
    if (g_16a0b90 == g_16a0b94)
        return 0;
    if (*(int*)key == 0)
        return 0;

    int creature = ((int (__thiscall*)(Mgr*, void*, int, void*, void*, int))
                    this->mp70->vftable[0x30 / 4])(this->mp70, key, 2, &g_16a0b0c, &g_15a2d2c, 1);
    if (creature == 0)
        return 0;
    ((void (__thiscall*)(Mgr*, int, int, int))this->mp70->vftable[0x40 / 4])(this->mp70, creature, 2, 1);
    *(float*)(creature + 0x3c) = 0.0f;

    int setting = FUN_00401090();
    int profile = ((SpeciesMgr*)setting)->GetProfile(key);
    if (profile != 0) {
        int c = FUN_00c028b0((void*)profile, 1);
        ((Creature*)creature)->SetValue(c);
    }
    ((Creature*)creature)->SetFlag(1);
    ((Creature*)creature)->AddRef();

    Boid* b = (Boid*)FUN_00f473a0(0x100, "Simulator", 0, 0, 0, 0);
    if (b == 0)
        b = 0;
    else
        b = (Boid*)FUN_00dd9510(b);

    b->mF4 = creature;
    b->mF8 = g_16a0c14;
    b->mFC = 2;
    b->m98 = 0.0f;
    b->mA8 = g_16a1098;
    b->mE4 = FUN_00572a10(g_1473c70, g_147d24c);
    b->mTimer.SetUnits(5);
    b->mTimer.Restart();

    Boid** slot = this->mpEnd;
    if (slot < this->mpCapacity) {
        this->mpEnd = slot + 1;
        if (slot != 0)
            *slot = b;
    } else {
        FUN_00b96600(this, (void**)&b);
    }
    return (int)b;
}

// Opaque civilization record reached through vtable-free thiscall methods.
struct Civ {
    int   GetKey();                                  // 0x00bb9b80
    Vec3* GetCities();                               // 0x005c65e0
};

// ---------------------------------------------------------------------------
// @ 0x00ddb9f0
// Create an element for a civ at its first city, nudged by a scaled axis.
// ---------------------------------------------------------------------------
int SimMgr::FUN_00ddb9f0(Civ* civ)
{
    int key = civ->GetKey();
    Boid* b = (Boid*)this->FUN_00ddb880((void*)key);
    if (b != 0) {
        float k = g_14007f4;
        float dx = g_16a0ba4 * k;
        float dy = g_16a0ba8 * k;
        float dz = g_16a0bac * k;
        Vec3* city = civ->GetCities();
        b->mPos.x = dx + city->x;
        b->mPos.y = dy + city->y;
        b->mPos.z = dz + city->z;
        int o = b->mF4;
        *(float*)(o + 4) = b->mPos.x;
        *(float*)(o + 8) = b->mPos.y;
        *(float*)(o + 0xc) = b->mPos.z;
        void* v = (void*)b->mF4;
        ((void (__thiscall*)(void*, int, int))((*(void***)v)[1]))(v, 0x2481de5, 0);
        b->mD8 = 1;
        FUN_00dda500();
    }
    return (int)b;
}

// ---------------------------------------------------------------------------
// @ 0x00ddbad0
// Create (or revive) an element from a three-word key: look the key up in the
// manager's map, then build a fully-initialised element around it.
// ---------------------------------------------------------------------------
void SimMgr::FUN_00ddbad0(void* key)
{
    int k0 = ((int*)key)[0];
    int k1 = ((int*)key)[1];
    int k2 = ((int*)key)[2];
    g_16a0b04 = 0;
    float local_44 = 0.0f;
    int local_40 = 0;
    int local_3c = 0;

    if (k0 == 0) {
        char stackBuf[12];
        stackBuf[0] = 0; stackBuf[1] = 0; stackBuf[2] = 0;
        ((int*)stackBuf)[0] = 0;
        ((int*)stackBuf)[1] = 0;
        ((int*)stackBuf)[2] = 0;
        // read the first element of the map at g_16a1344 + 0x3c
        int* elem = (int*)FUN_00de7530(stackBuf);
        local_44 = *(float*)(elem + 0);
        local_40 = elem[1];
        local_3c = elem[2];
        if (elem[-1] != 0)
            operator_delete__(elem);
    } else {
        int kk[3];
        kk[0] = k0; kk[1] = k1; kk[2] = k2;
        FUN_00de9dc0(kk);
        int out[3];
        int* elem = (int*)FUN_00de56f0(out, kk);
        local_44 = *(float*)(elem + 0);
        local_40 = elem[1];
        local_3c = elem[2];
    }

    int a0 = 0, a1 = 0, a2 = 0, b0 = 0, b1 = 0, b2 = 0;
    (void)a0; (void)a1; (void)a2; (void)b0; (void)b1; (void)b2;
    float out44 = local_44;
    int out40 = local_40;
    int out3c = local_3c;
    FUN_00dd9130(&out40, 0);
    (void)out44;

    Mgr* factory = this->mpMgr14;
    int e = ((int (__thiscall*)(Mgr*, int, int, int))((*(void***)factory)[3]))(factory, out40, out3c, 0);
    if (e == 0) {
        FUN_00de74c0(&out40);
        g_16a0b04 = 1;
    } else {
        ++*(int*)(e + 0x40);
        Boid* b = (Boid*)FUN_00f473a0(0x100, "Simulator", 0, 0, 0, 0);
        if (b == 0)
            b = 0;
        else
            b = (Boid*)FUN_00dd9510(b);
        b->mResA = (void*)e;
        b->mFC = 0;

        Mgr* f2 = this->mpMgr14;
        void* e2 = (void*)((int (__thiscall*)(Mgr*, int, int, int))((*(void***)f2)[3]))(f2, out40, out3c, 0);
        b->mResB = e2;
        ++*(int*)((char*)e2 + 0x40);
        b->mTimer.SetUnits(5);
        b->mC8 = 0;
        b->mD5 = 0;
        b->mCC = 0;
        b->mF8 = g_16a0c28;
        float a = g_15a2d00 * g_1471064;
        b->mE8 = g_16a0ba4;
        b->mEC = g_16a0ba8;
        b->mF0 = g_16a0bac;
        b->mD6 = 0;
        b->mD7 = 0;
        b->mD0 = 0;
        b->mV18.x = g_16a0b0c;
        b->mV18.y = g_16a0b10;
        b->mV18.z = g_16a0b14;
        b->mV24.x = g_16a0b0c;
        b->mV24.y = g_16a0b10;
        b->mV24.z = g_16a0b14;

        float sa = 0.0f, sb = 0.0f, sc = 0.0f;
        float sw = 0.0f, sx = 0.0f, sy = 0.0f;
        (void)sa; (void)sb; (void)sc; (void)sw; (void)sx; (void)sy;
        float s = a;
        float sn = fs_sin(s);
        float cs = fs_cos(s);
        b->mM48[0].x = sn * g_16a0c3c;
        b->mM48[0].y = sn * g_16a0c40;
        b->mM48[0].z = sn * g_16a0c44;
        b->mM48[0].w = cs;
        b->mPos.x = 0.0f;
        b->mPos.y = 0.0f;
        b->mPos.z = -0.0073242188f;
        b->mV30.x = 0.0f;
        b->mV30.y = 0.0f;
        b->mV30.z = -0.0073242188f;
        b->mV3C.x = 0.0f;
        b->mV3C.y = g_15a2de8;
        b->mV3C.z = 0.0f;
        float rnd = g_16a1018;
        b->mDC = rnd;
        b->mE4 = g_15a2de4;
        b->mA8 = g_15a2de4;
        b->m98 = g_15a2de4;
        (void)rnd;

        ((void (__thiscall*)(void*, Boid*))(*(void***)g_16a0c28)[0])((void*)g_16a0c28, b);

        Boid** slot = this->mpEnd;
        if (slot < this->mpCapacity) {
            this->mpEnd = slot + 1;
            if (slot != 0)
                *slot = b;
        } else {
            FUN_00b96600(this, (void**)&b);
        }
    }
}
