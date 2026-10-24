// Slice s00c7e1c0: cCubeSim cube-face helpers / terraform check (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
#include "types.h"
#include <math.h>

struct CS;

extern float    g_01694c08;
extern uint32_t g_01694c0c;
extern float    g_01579a08;
extern uint32_t g_01579a10, g_01579a14;

// ---- callees (addresses resolved/masked by chk) -----------------------------
void*   MessageServer_0067dcc0();
void*   SpaceGameGet_01002bd0();
void*   GetSetting9_00401090();
void*   GetUniverseContext_01021080();
void*   GetActivePlanet_01021260();
void*   TerraformingManager_00b3d430();
void*   FUN_01049a10();
void*   GetMissionManager_00feb9f0();
int     WrapCubeFace_00684ca0(int, int*, int*, int*, int, int);
float*  FUN_00684c50_00(float*, int, int*);
void    ReadInt32_0093a780(void*, void*, int, int);
int     ResourceMan_opne_005f78f0(int*, int*);
void    RemoveHandler_00571db0(void*, void*, void*, void*, void*);
void*   operator_new_array_011e073e(void*, int, int);
void __stdcall vector_ctor_iterator_00401930(void*, unsigned, int, void*);
float   GetTerraformRadius_00fc1fa0(int);

// thiscall-like (ecx = object, no stack args)
void     __fastcall FUN_00bc3170_00(void*);
void     __fastcall cSPTimer_Start_00bc30f0(void*);
void     __fastcall cSPTimer_Restart_00bc3130(void*);
bool     __fastcall FUN_00c70a70_00(void*);
float    __fastcall FUN_00c71d30_00(void*);
bool     __fastcall cSPTimer_IsRunning_00feba90(void*);
uint64_t __fastcall cSPTimer_GetElapsedTime_00bc3190(void*);
float    __fastcall cTerraformTuning_GetFloraBullseyeRadius_01049c90(void*);
uint32_t __fastcall cSPMission_GetMissionID_01030e10(void*);
void*    __fastcall cSPMission_GetTargetPlanet_00970b30(void*);
void*    __fastcall cSPMissionManager_GetMissionList_00fedd50(void*);

// helpers needing a "this" in ecx plus stack args (dummy-struct methods)
struct SimGame     { void* f5180(int); };
struct CubeMapObj  { void FUN_00c70aa0(float); };
struct SpeciesMgr  { void* GetProfile(int* key); };
struct TerraMgrObj { int F670(int); bool FUN_00bbe370(int); };
struct Ser {
    uint8_t buf[0xa14];
    void ctor(void*, void*, int);   // 0x692f90
    char Serialize(void*);          // 0x692900
    char Read(void*);               // 0x693e10
};

struct CubeCell {                       // 0x54 bytes
    uint32_t pad00[8];                  // 0x00
    uint8_t  m1F9C;                     // 0x20  (absolute 0x1f9c in cell #0x5f)
    uint8_t  pad21[0x33];               // 0x21..0x53
    void FUN_00c7dfe0(void* s);         // 0xc7dfe0
    void FUN_00c7e0a0(void* s);         // 0xc7e0a0
};
struct CubeElem {                       // 0x54 bytes (face grid element, ctor)
    uint32_t m00;                       // 0x00
    uint32_t mVec0[0x30 / 4];           // 0x04
    uint32_t mVec1[0x20 / 4];           // 0x34
};

struct CS {
    union {
        struct {
            uint32_t pad00[0x18 / 4];   // 0x00
            void*    mp18;              // 0x18
            uint32_t pad1C[4];          // 0x1c
            void*    mp2C;              // 0x2c
            uint32_t pad30;             // 0x30
            void*    mp34;              // 0x34
            void*    mp38;              // 0x38
            void*    mp3C;              // 0x3c
            void*    mp40;              // 0x40
            void*    mp44;              // 0x44
            void*    mp48;              // 0x48
            void*    mp4C;              // 0x4c
            CubeCell mCells[0x60];      // 0x50
            uint32_t pad1FD0;           // 0x1fd0
            float    m1FD4;             // 0x1fd4
            float    m1FD8;             // 0x1fd8
            uint32_t pad1FDC[5];        // 0x1fdc
            uint8_t  timer1FF0[0x20];   // 0x1ff0
            uint8_t  timer2010[0x20];   // 0x2010
            uint8_t  m2030;             // 0x2030
            uint8_t  m2031;             // 0x2031
            uint8_t  pad2032[6];        // 0x2032
            uint8_t  timer2038[0x28];   // 0x2038
        } h;
        CubeElem mElems[0x60];          // 0x00 (overlaps h)
    };

    void*     ctor_00c7ea70();
    void      FUN_00c7ead0(int* out);
    void      FUN_00c7e280(void* a);
    void      FUN_00c7e2f0(char b);
    void      FUN_00c7e5d0(int a2, int a3, int a4, int a5, void* cb, int a7, int a8);
    void      FUN_00c7e780(int a2, void* cb, int a4, int a5);
    bool      FUN_00c7e8f0(void* s);
    bool      FUN_00c7e950(void* s);
    bool      FUN_00c7e9b0(int msg, int unk);
    CubeElem* FUN_00c7eaf0(float* p);
    void      FUN_00c7ecb0();
    void      FUN_00c7ed00(int* a, int* b);
    bool      FUN_00c7ee50();
};

// ================================================================ definitions

// @ 0x00c7e1c0
bool __stdcall FUN_00c7e1c0(int* a, int* b)
{
    b[0] = a[0]; b[1] = a[1]; b[2] = a[2]; b[0] -= 1;
    b[3] = a[0]; b[4] = a[1]; b[5] = a[2]; b[3] += 1;
    b[6] = a[0]; b[7] = a[1]; b[8] = a[2]; b[7] -= 1;
    b[9] = a[0]; b[10] = a[1]; b[11] = a[2]; b[10] += 1;
    if (a[0] > 0 && a[0] < 3 && a[1] > 0 && a[1] < 3) return false;
    int* p = b + 2;
    for (int i = 4; i != 0; --i, p += 3) {
        int t = *p;
        WrapCubeFace_00684ca0(4, &t, p - 2, p - 1, 0, 0);
        *p = t;
    }
    return true;
}

// @ 0x00c7e280
void CS::FUN_00c7e280(void* a)
{
    h.mp4C = a;
    FUN_00bc3170_00(h.timer1FF0);
    FUN_00bc3170_00(h.timer2010);
    cSPTimer_Start_00bc30f0(h.timer2010);
    void* hTarget = (void*)&h.mp34;
    void* ms = MessageServer_0067dcc0();
    h.mp38 = ms;
    h.mp3C = hTarget;
    h.mp40 = (void*)0x1473354;
    h.mp44 = (void*)1;
    h.mp48 = 0;
    if (ms != 0 && hTarget != 0) {
        ((void(__thiscall*)(void*, void*, uint32_t))(*(void***)ms)[0x24 / 4])(ms, hTarget, 0x44448ed);
    }
}

// @ 0x00c7e2f0
void CS::FUN_00c7e2f0(char b)
{
    h.m2030 = (uint8_t)b;
    h.m2031 = 0;
    if (b != 0) cSPTimer_Restart_00bc3130(h.timer2038);
    else { h.m1FD4 = 0.0f; h.m1FD8 = 0.0f; }
    if (h.mp4C != 0) {
        if (!FUN_00c70a70_00(h.mp4C))
            ((CubeMapObj*)h.mp4C)->FUN_00c70aa0(FUN_00c71d30_00(h.mp4C));
    }
    ((SimGame*)SpaceGameGet_01002bd0())->f5180((int)(b == 0));
}

// @ 0x00c7e370
int __stdcall FUN_00c7e370(int a1, int* key, int p3, int p4, int p5, int p6, int p7)
{
    (void)a1;
    void* prof = ((SpeciesMgr*)GetSetting9_00401090())->GetProfile(key);
    if (prof == 0) return 0;
    if (*(int*)((char*)prof + 0x608) == 0) {
        if (*(int*)((char*)prof + 0x60c) != 0) {
            int* q = (int*)(p4 + 0x10);
            for (int i = 0; i < 3; ++i, q += 4) {
                if (*(int*)(p3 + 0x10 + i * 0x10) != 0) return 1;
                if (q[0] != 0) return 1;
                if (*(int*)(p6 + 0x10 + i * 0x10) != 0) return 1;
                if (*(int*)(p7 + 0x10 + i * 0x10) != 0) return 1;
                if (*(int*)(p5 + 0x10 + i * 0x10) != 0) return 1;
            }
        }
    } else {
        if (*(int*)(p3 + 0x40) != 0) {
            if (*(int*)(p3 + 0x34) != key[0] || *(int*)(p3 + 0x38) != key[1] ||
                *(int*)(p3 + 0x3c) != key[2]) return 1;
        }
        if (*(int*)(p4 + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(p4 + 0x34), key)) return 1;
        if (*(int*)(p6 + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(p6 + 0x34), key)) return 1;
        if (*(int*)(p7 + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(p7 + 0x34), key)) return 1;
        if (*(int*)(p5 + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(p5 + 0x34), key)) return 1;
    }
    return 0;
}

// @ 0x00c7e490
void __stdcall FUN_00c7e490(int a1, int a2, int p, int a4, char* e)
{
    (void)a1; (void)a2; (void)a4;
    int* pi = (int*)p;
    int* ei = (int*)e;
    if (*e != 0) {
        if (pi[1] == ei[1] && pi[2] == ei[2] && pi[3] == ei[3]) pi[4] = 0;
        if (pi[5] == ei[1] && pi[6] == ei[2] && pi[7] == ei[3]) pi[8] = 0;
        if (pi[9] == ei[1] && pi[10] == ei[2] && pi[11] == ei[3]) pi[12] = 0;
    } else {
        if (pi[0xd] == ei[1] && pi[0xe] == ei[2] && pi[0xf] == ei[3]) pi[0x10] = 0;
        if (pi[0x11] == ei[1] && pi[0x12] == ei[2] && pi[0x13] == ei[3]) pi[0x14] = 0;
    }
}

// @ 0x00c7e530
void __stdcall FUN_00c7e530(int a, int b, int p, int d, int* e)
{
    (void)a; (void)b; (void)d;
    if (*(int*)(p + 0x34) == e[0] && *(int*)(p + 0x38) == e[1] && *(int*)(p + 0x3c) == e[2]) {
        *(int*)(p + 0x34) = e[3]; *(int*)(p + 0x38) = e[4]; *(int*)(p + 0x3c) = e[5];
    }
    if (*(int*)(p + 0x44) == e[0] && *(int*)(p + 0x48) == e[1] && *(int*)(p + 0x4c) == e[2]) {
        *(int*)(p + 0x44) = e[3]; *(int*)(p + 0x48) = e[4]; *(int*)(p + 0x4c) = e[5];
    }
}

// @ 0x00c7e5d0
void CS::FUN_00c7e5d0(int a2, int a3, int a4, int a5, void* cb, int a7, int a8)
{
    (void)a7; (void)a8;
    int i1 = a3, i2 = a4, i3 = a5;

    int local_2c = i2 + 1;
    int p4 = i1, p5 = i3;
    WrapCubeFace_00684ca0(4, &p4, &local_2c, &p5, 0, 0);
    CubeCell* local_10 = &h.mCells[local_2c + (p5 + p4 * 4) * 4];

    int p3 = i2 - 1; p4 = i1; p5 = i3;
    WrapCubeFace_00684ca0(4, &p4, &p3, &p5, 0, 0);
    CubeCell* local_c = &h.mCells[p3 + (p5 + p4 * 4) * 4];

    p5 = i3 + 1; p3 = i2; p4 = i1;
    WrapCubeFace_00684ca0(4, &p4, &p3, &p5, 0, 0);
    CubeCell* local_8 = &h.mCells[p3 + (p5 + p4 * 4) * 4];

    p5 = i3 - 1; p3 = i2; p4 = i1;
    WrapCubeFace_00684ca0(4, &p4, &p3, &p5, 0, 0);
    CubeCell* local_4 = &h.mCells[p3 + (p5 + p4 * 4) * 4];

    (void)local_10; (void)local_c; (void)local_8; (void)local_4;

    int coord[3];
    coord[0] = i2; coord[1] = i3; coord[2] = i1;
    float local_1c[3];
    float* res = FUN_00684c50_00(local_1c, 4, coord);
    ((void(__thiscall*)(void*, int, void*))cb)((char*)this + a7, a2, (void*)res);
}

// @ 0x00c7e780
void CS::FUN_00c7e780(int a2, void* cb, int a4, int a5)
{
    CubeCell* base = &h.mCells[5];          // this + 0x1f4
    for (int i4 = 0; i4 < 6; ++i4) {
        int n30 = 1;
        CubeCell* i3 = base;
        do {
            CubeCell* i1 = i3;
            int i5 = 1;
            do {
                i1 = i3;
                int coord[3];
                coord[0] = i5; coord[1] = n30; coord[2] = i4;
                float out[3];
                float* res = FUN_00684c50_00(out, 4, coord);
                ((void(__thiscall*)(void*, int, void*))cb)((char*)this + a4, a2, (void*)res);
                ++i5;
                i3 = i1 + 1;
            } while (i5 < 3);
            ++n30;
            i3 = i1 + 3;                    // iVar1 + 0xfc
        } while (n30 < 3);
        int k = 1;
        do {
            FUN_00c7e5d0(a2, i4, 0, k, cb, a4, a5);
            FUN_00c7e5d0(a2, i4, 3, k, cb, a4, a5);
            ++k;
        } while (k < 3);
        k = 0;
        do {
            FUN_00c7e5d0(a2, i4, k, 0, cb, a4, a5);
            FUN_00c7e5d0(a2, i4, k, 3, cb, a4, a5);
            ++k;
        } while (k < 4);
        base += 0x540 / 0x54;               // +16 cells
    }
}

// @ 0x00c7e8f0
bool CS::FUN_00c7e8f0(void* s)
{
    for (int i = 0x60; i != 0; --i)
        h.mCells[0x60 - i].FUN_00c7dfe0(s);
    Ser ser;
    ser.ctor(this, (void*)0x1579cd0, 0x1a80d26);
    return ser.Serialize(s) != 0;
}

// @ 0x00c7e950
bool CS::FUN_00c7e950(void* s)
{
    for (int i = 0x60; i != 0; --i)
        h.mCells[0x60 - i].FUN_00c7e0a0(s);
    Ser ser;
    ser.ctor(this, (void*)0x1579cd0, 0x1a80d26);
    return ser.Read(s) != 0;
}

// @ 0x00c7e9b0
bool CS::FUN_00c7e9b0(int msg, int unk)
{
    (void)unk;
    if (msg != 0x44448ed) return false;
    if (GetUniverseContext_01021080() == 0) {
        if (h.mp18 == GetActivePlanet_01021260())
            h.mCells[0x5f].m1F9C = 1;
    }
    return true;
}

// @ 0x00c7e9f0
bool __cdecl FUN_00c7e9f0(void* io, void** out)
{
    void* a = ((void*(__thiscall*)(void*))(*(void***)io)[0x20 / 4])(io);
    void* b = ((void*(__thiscall*)(void*))(*(void***)a)[0x18 / 4])(a);
    int x;
    ReadInt32_0093a780(b, &x, 1, 0);
    *out = (void*)x;
    return true;
}

// @ 0x00c7ea30
void __cdecl FUN_00c7ea30(int* a, int* b, int* out)
{
    while (a != b) {
        if (out != 0) { out[0] = a[0]; out[1] = a[1]; out[2] = a[2]; out[3] = a[3]; }
        a += 4;
        out += 4;
    }
}

// @ 0x00c7ea70
void* CS::ctor_00c7ea70()
{
    CubeElem* p = mElems;
    int n = 0x5f;
    do {
        p->m00 = 0;
        vector_ctor_iterator_00401930(&p->mVec0, 0x10, 3, (void*)0xfaed90);
        vector_ctor_iterator_00401930(&p->mVec1, 0x10, 2, (void*)0xfaed90);
        p += 1;
    } while (--n >= 0);
    operator_new_array_011e073e(this, 0, 0x1f80);
    return this;
}

// @ 0x00c7ead0
void CS::FUN_00c7ead0(int* out)
{
    out[2] = 0; out[0] = 0; out[1] = 0; out[3] = (int)this;
}

// @ 0x00c7eaf0
CubeElem* CS::FUN_00c7eaf0(float* p)
{
    float x = p[0];
    volatile float ax = (float)fabs((double)x);
    float y = p[1];
    volatile float ay = (float)fabs((double)y);
    float z = p[2];
    volatile float az = (float)fabs((double)z);
    int i7, i8, i9;
    if (az < ax || az < ay) {
        if (ay < ax) {
            float t = y / x;
            t = (t + 1.0f) * 2.0f;
            i7 = (int)t;
            t = z / ax;
            t = (t + 1.0f) * 2.0f;
            i8 = (int)t;
            i9 = (x < 0.0f) ? 3 : 2;
        } else {
            float t = z / y;
            t = (t + 1.0f) * 2.0f;
            i7 = (int)t;
            t = x / ay;
            t = (t + 1.0f) * 2.0f;
            i8 = (int)t;
            i9 = (y < 0.0f) ? 5 : 4;
        }
    } else {
        float t = x / z;
        t = (t + 1.0f) * 2.0f;
        i7 = (int)t;
        t = y / az;
        t = (t + 1.0f) * 2.0f;
        i8 = (int)t;
        i9 = (z < 0.0f) ? 1 : 0;
    }
    if (i7 == 4) i7 = 3;
    if (i8 == 4) i8 = 3;
    return &mElems[i7 + (i8 + i9 * 4) * 4];
}

// @ 0x00c7ecb0
void CS::FUN_00c7ecb0()
{
    void* p = h.mp38;
    if (p != 0) {
        void* a2 = h.mp3C;
        void* a3 = h.mp40;
        void* a4 = h.mp44;
        void* a5 = h.mp48;
        h.mp38 = 0;
        RemoveHandler_00571db0(p, a2, a3, a4, a5);
    }
    h.mp4C = (void*)0;
    if (h.mp2C != (void*)0) {
        void* q = h.mp2C;
        h.mp2C = (void*)0;
        ((void(__thiscall*)(void*))(*(void***)q)[1])(q);
    }
}

// @ 0x00c7ed00
void CS::FUN_00c7ed00(int* a, int* b)
{
    int local[6];
    local[0] = a[0]; local[1] = a[1]; local[2] = a[2];
    local[3] = b[0]; local[4] = b[1]; local[5] = b[2];
    FUN_00c7e780(0, (void*)FUN_00c7e530, 0, (int)local);
}

// @ 0x00c7ed50
void __stdcall FUN_00c7ed50(int a1, int a2, int p, int a4, int* e)
{
    (void)a1; (void)a2; (void)a4;
    int n0 = (e[1] - e[0]) / 0xc;
    int n1 = (e[0xb] - e[0xa]) / 0xc;
    for (int k = 0; k < 3; ++k) {
        int* q = (int*)(p + 4 + k * 0x10);
        for (int i = 0; i < n0; ++i) {
            int* r = (int*)(e[0] + i * 0xc);
            if (q[0] == r[0] && q[1] == r[1] && q[2] == r[2]) {
                int* s = (int*)(e[5] + i * 0xc);
                q[0] = s[0]; q[1] = s[1]; q[2] = s[2];
            }
        }
    }
    for (int k = 0; k < 2; ++k) {
        int* q = (int*)(p + 0x34 + k * 0x10);
        for (int i = 0; i < n1; ++i) {
            int* r = (int*)(e[0xa] + i * 0xc);
            if (q[0] == r[0] && q[1] == r[1] && q[2] == r[2]) {
                int* s = (int*)(e[0xf] + i * 0xc);
                q[0] = s[0]; q[1] = s[1]; q[2] = s[2];
            }
        }
    }
}

// @ 0x00c7ee50
bool CS::FUN_00c7ee50()
{
    if (h.m2031 == 0) {
        if (cSPTimer_IsRunning_00feba90(h.timer2038)) {
            uint64_t t = cSPTimer_GetElapsedTime_00bc3190(h.timer2038);
            uint64_t limit = ((uint64_t)g_01579a14 << 32) | g_01579a10;
            if (t > limit) h.m2031 = 1;
        }
        return false;
    }

    float flora = cTerraformTuning_GetFloraBullseyeRadius_01049c90(FUN_01049a10());
    if ((g_01694c0c & 1) == 0) {
        float half = flora * 0.5f;
        float cap = 0.02f;
        g_01694c0c |= 1;
        g_01694c08 = (cap <= half) ? cap : half;
    }

    int obj = *(int*)((char*)h.mp4C + 0x13c);
    float radius = (float)((TerraMgrObj*)TerraformingManager_00b3d430())->F670(obj);

    if (radius == 0.0f) {
        float bx = *(float*)((char*)obj + 0xb0);
        if (fabsf(bx) < g_01694c08 || fabsf(bx - 1.0f) < g_01694c08) {
            if (g_01694c08 <= fabsf(*(float*)((char*)obj + 0xb4)) &&
                g_01694c08 <= fabsf(*(float*)((char*)obj + 0xb4) - 1.0f))
                return false;
            return true;
        }
    } else {
        if (((TerraMgrObj*)TerraformingManager_00b3d430())->FUN_00bbe370(obj)) {
            void* vec = cSPMissionManager_GetMissionList_00fedd50(GetMissionManager_00feb9f0());
            int* it = *(int**)vec;
            int* end = ((int**)vec)[1];
            for (; it != end; ++it) {
                void* mission = (void*)*it;
                if (mission == 0) continue;
                if (cSPMission_GetMissionID_01030e10(mission) != 0x311cc10f) continue;
                if (cSPMission_GetTargetPlanet_00970b30(mission) == h.mp4C) return false;
            }
            float gr = GetTerraformRadius_00fc1fa0(*(int*)&radius);
            float dx = *(float*)((char*)obj + 0xb0) - 0.5f;
            float dy = *(float*)((char*)obj + 0xb4) - 0.5f;
            if (fabsf((float)sqrt((double)(dx * dx + dy * dy)) - (gr - flora)) < g_01694c08 &&
                fabsf(h.m1FD4) < g_01579a08 &&
                fabsf(h.m1FD8) < g_01579a08)
                return true;
            return false;
        }
    }
    return false;
}