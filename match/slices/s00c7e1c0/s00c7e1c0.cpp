// Slice s00c7e1c0: cCubeSim cube-face helpers / terraform check (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
// NOTE: several functions are partial reconstructions (see partial.txt).
#include "types.h"
#include <math.h>

struct CS;
extern float g_01694c08;
extern uint32_t g_01694c0c;
extern float g_01579a08;
extern uint32_t g_01579a10, g_01579a14;

struct CS {
    char pad_00[0x2c];
    void* mp2C;                    // +0x2c
    char pad_30[0x38 - 0x30];
    void* mp38;                    // +0x38
    void* mp3C;                    // +0x3c
    void* mp40;                    // +0x40
    void* mp44;                    // +0x44
    void* mp48;                    // +0x48
    void* mp4C;                    // +0x4c
    char pad_50[0x1fd4 - 0x50];
    float m1FD4;                   // +0x1fd4
    float m1FD8;                   // +0x1fd8
    char pad_1fdc[0x2030 - 0x1fdc];
    uint8_t m2030;                 // +0x2030
    uint8_t m2031;                 // +0x2031
    char pad_2032[0x2038 - 0x2032];
    char timer2038[0x20];          // +0x2038
    void* ctor_00c7ea70();
    void FUN_00c7ead0(int* out);
};

void   FUN_00c7e1c0_00();
void   WrapCubeFace_00684ca0(int a, void* b, void* c, void* d, int e, int f);
void   FUN_00684c50_00();
void   FUN_00bc3170_00(void* p);
void   cSPTimer_Start_00bc30f0(void* p);
void   cSPTimer_Restart_00bc3130(void* p);
void   cSPTimer_dtor_00bc3170(void* p);
bool   FUN_00c70a70_00(void* p);
float  FUN_00c71d30_00(void* p);
void   FUN_00c70aa0_00(void* p, float f);
void*  SpaceGameGet_01002bd0(int a);
void   FUN_01005180_00(int a);
void*  GetSetting9_00401090();
void*  GetProfile_004df550(void* mgr, int* key);
int    ResourceMan_opne_005f78f0(void* a, int* b);
void   FUN_00c7dfe0_00(void* p, void* s);
void   FUN_00c7e0a0_00(void* p, void* s);
void   cVarListSerializer_ctor_00692f90(void* p, void* a, void* b, int c);
bool   cVarListSerializer_Serialize_00693e10(void* p, void* s);
bool   cVarListSerializer_Serialize_00692900(void* p, void* s);
void*  GetUniverseContext_01021080();
void*  GetActivePlanet_01021260();
void   ReadInt32_0093a780(int a, void* out, int n, int b);
void   vector_ctor_iterator_00401930();
void*  operator_new_array_011e073e(int a, int b, int c);
void   RemoveHandler_00571db0(void* a, void* b, void* c, void* d, void* e);
void*  TerraformingManager_00b3d430(void* p);
void*  TerraformingManager_F670_00bbc670(void* p);
bool   FUN_00bbe370_00(void* p);
void*  FUN_01049a10();
float  cTerraformTuning_GetFloraBullseyeRadius_01049c90(void* t);
void   FUN_01049a10_00();
void*  GetMissionManager_00feb9f0();
void*  cSPMissionManager_GetMissionList_00fedd50(void* m);
uint32_t cSPMission_GetMissionID_01030e10(void* m);
void*  cSPMission_GetTargetPlanet_00970b30(void* m);
float  GetTerraformRadius_00fc1fa0(void* p);
bool   cSPTimer_IsRunning_00feba90(void* p);
uint64_t cSPTimer_GetElapsedTime_00bc3190(void* p);

struct Mission { uint32_t GetMissionID_01030e10(); void* GetTargetPlanet_00970b30(); };

// ================================================================ definitions

// @ 0x00c7e1c0
int __cdecl FUN_00c7e1c0(int* a, int* b)
{
    b[0] = a[0]; b[1] = a[1]; b[2] = a[2]; b[0] -= 1;
    b[3] = a[0]; b[4] = a[1]; b[5] = a[2]; b[3] += 1;
    b[6] = a[0]; b[7] = a[1]; b[8] = a[2]; b[7] -= 1;
    b[9] = a[0]; b[10] = a[1]; b[11] = a[2]; b[10] += 1;
    if (a[0] > 0 && a[0] < 3 && a[1] > 0 && a[1] < 3) return 0;
    int* p = b + 2;
    for (int i = 4; i != 0; --i, p += 3) {
        int t = *p;
        WrapCubeFace_00684ca0(4, &t, p - 2, p - 1, 0, 0);
        *p = t;
    }
    return 1;
}

// @ 0x00c7e280
void __cdecl FUN_00c7e280(CS* self, void* a)
{
    self->mp4C = a;
    FUN_00bc3170_00((char*)self + 0x1ff0);
    FUN_00bc3170_00((char*)self + 0x2010);
    cSPTimer_Start_00bc30f0((char*)self + 0x2010);
    void* h = (char*)self + 0x34;
    void* ms = (void*)0;
    (void)ms;
    self->mp38 = ms;
    self->mp3C = h;
    self->mp40 = (void*)0x1473354;
    self->mp44 = (void*)1;
    self->mp48 = 0;
    if (self->mp38 != 0 && h != 0) {
        ((void(__thiscall*)(void*, void*, uint32_t))(*(void***)self->mp38)[0x24 / 4])(
            self->mp38, h, 0x44448ed);
    }
}

// @ 0x00c7e2f0
void __cdecl FUN_00c7e2f0(CS* self, char b)
{
    self->m2030 = b;
    self->m2031 = 0;
    if (b != 0) cSPTimer_Restart_00bc3130((char*)self + 0x2038);
    else { self->m1FD4 = 0.0f; self->m1FD8 = 0.0f; }
    if (self->mp4C != 0) {
        if (!FUN_00c70a70_00(self->mp4C))
            FUN_00c70aa0_00(self->mp4C, FUN_00c71d30_00(self->mp4C));
    }
    int x = (b == 0);
    SpaceGameGet_01002bd0(x);
    FUN_01005180_00(x);
}

// @ 0x00c7e370
int __cdecl FUN_00c7e370(int a, int* key, int c, int* d, int e, int f, int g)
{
    (void)a;
    if (GetProfile_004df550(GetSetting9_00401090(), key) != 0) {
        // five resource comparisons; partial
        if (d[0x10] != 0 && ResourceMan_opne_005f78f0(d + 0xd, key)) return 1;
        if (*(int*)(f + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(f + 0x34), key)) return 1;
        if (*(int*)(g + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(g + 0x34), key)) return 1;
        if (*(int*)(e + 0x40) != 0 && ResourceMan_opne_005f78f0((int*)(e + 0x34), key)) return 1;
    }
    (void)c;
    return 0;
}

// @ 0x00c7e490
void __cdecl FUN_00c7e490(int a, int b, int p, int d, char* e)
{
    (void)a; (void)b; (void)d;
    if (*e == 0) {
        if (*(int*)(p + 0x34) == *(int*)(e + 4) && *(int*)(p + 0x38) == *(int*)(e + 8) &&
            *(int*)(p + 0x3c) == *(int*)(e + 0xc)) *(int*)(p + 0x40) = 0;
        if (*(int*)(p + 0x44) == *(int*)(e + 4) && *(int*)(p + 0x48) == *(int*)(e + 8) &&
            *(int*)(p + 0x4c) == *(int*)(e + 0xc)) *(int*)(p + 0x50) = 0;
    } else {
        if (*(int*)(p + 4) == *(int*)(e + 4) && *(int*)(p + 8) == *(int*)(e + 8) &&
            *(int*)(p + 0xc) == *(int*)(e + 0xc)) *(int*)(p + 0x10) = 0;
        if (*(int*)(p + 0x14) == *(int*)(e + 4) && *(int*)(p + 0x18) == *(int*)(e + 8) &&
            *(int*)(p + 0x1c) == *(int*)(e + 0xc)) *(int*)(p + 0x20) = 0;
        if (*(int*)(p + 0x24) == *(int*)(e + 4) && *(int*)(p + 0x28) == *(int*)(e + 8) &&
            *(int*)(p + 0x2c) == *(int*)(e + 0xc)) *(int*)(p + 0x30) = 0;
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
void __cdecl FUN_00c7e5d0(CS* self, int a, int b, int c, int d, void* cb, int e, int f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    // cube-face neighbour callback walk; partial
    (void)((void*(*)(void*, int))cb)(self, 0);
}

// @ 0x00c7e780
void __cdecl FUN_00c7e780(CS* self, int a, void* cb, int d, int e)
{
    (void)self; (void)a; (void)cb; (void)d; (void)e;
}

// @ 0x00c7e8f0
bool __cdecl FUN_00c7e8f0(CS* self, void* s)
{
    for (int i = 0x60; i != 0; --i) FUN_00c7dfe0_00((char*)self + 0x50, s);
    cVarListSerializer_ctor_00692f90((char*)self + 0xa14, self, (void*)0x1579cd0, 0x1a80d26);
    return cVarListSerializer_Serialize_00693e10((char*)self + 0xa14, s);
}

// @ 0x00c7e950
bool __cdecl FUN_00c7e950(CS* self, void* s)
{
    for (int i = 0x60; i != 0; --i) FUN_00c7e0a0_00((char*)self + 0x50, s);
    cVarListSerializer_ctor_00692f90((char*)self + 0xa14, self, (void*)0x1579cd0, 0x1a80d26);
    return cVarListSerializer_Serialize_00693e10((char*)self + 0xa14, s);
}

// @ 0x00c7e9b0
bool __cdecl FUN_00c7e9b0(CS* self, int msg)
{
    if (msg != 0x44448ed) return false;
    if (GetUniverseContext_01021080() == 0) {
        if (*(int*)((char*)self + 0x18) == (int)GetActivePlanet_01021260())
            *(uint8_t*)((char*)self + 0x1f9c) = 1;
    }
    return true;
}

// @ 0x00c7e9f0
bool __cdecl FUN_00c7e9f0(void* io, void** out)
{
    int* pi = (int*)(*(void*(__thiscall*)(void*))(*(void***)io)[0x20 / 4])(io);
    int x = 0;
    ReadInt32_0093a780((int)(*(void*(__thiscall*)(void*))(*(void***)pi)[0x18 / 4])(pi), &x, 1, 0);
    *out = (void*)x;
    return true;
}

// @ 0x00c7ea30
void __cdecl FUN_00c7ea30(int* a, int* b, int* out)
{
    for (; a != b; a += 4) {
        if (out != 0) { out[0]=a[0]; out[1]=a[1]; out[2]=a[2]; out[3]=a[3]; }
        out += 4;
    }
}

// @ 0x00c7ea70
void* CS::ctor_00c7ea70()
{
    char* esi = (char*)this + 0x34;
    for (int i = 0x5f; i >= 0; --i, esi += 0x54) {
        *(int*)(esi - 0x34) = 0;
        vector_ctor_iterator_00401930();
        vector_ctor_iterator_00401930();
    }
    operator_new_array_011e073e((int)this, 0, 0x1f80);
    return this;
}

// @ 0x00c7ead0
void CS::FUN_00c7ead0(int* out)
{
    out[2] = 0; out[0] = 0; out[1] = 0; out[3] = (int)this;
}

// @ 0x00c7eaf0
int __cdecl FUN_00c7eaf0(CS* self, float* p)
{
    (void)self;
    float x = p[0], y = p[1], z = p[2];
    float ax = fabsf(x), ay = fabsf(y), az = fabsf(z);
    int i7, i8, i9;
    if (az < ax || az < ay) {
        if (ay < ax) {
            i7 = (int)((y / x + 1.0f) * 2.0f);
            i8 = (int)((z / ax + 1.0f) * 2.0f);
            i9 = (x < 0.0f) ? 3 : 2;
        } else {
            i7 = (int)((z / y + 1.0f) * 2.0f);
            i8 = (int)((x / ay + 1.0f) * 2.0f);
            i9 = (y < 0.0f) ? 5 : 4;
        }
    } else {
        i7 = (int)((x / z + 1.0f) * 2.0f);
        i8 = (int)((y / az + 1.0f) * 2.0f);
        i9 = (z < 0.0f) ? 1 : 0;
    }
    if (i7 == 4) i7 = 3;
    if (i8 == 4) i8 = 3;
    return (i7 + (i8 + i9 * 4) * 4) * 0x54;
}

// @ 0x00c7ecb0
void __cdecl FUN_00c7ecb0(CS* self)
{
    if (self->mp38 != 0) {
        void* h = self->mp38;
        self->mp38 = 0;
        RemoveHandler_00571db0(h, self->mp3C, self->mp40, self->mp44, self->mp48);
    }
    self->mp4C = 0;
    if (self->mp2C != 0) {
        void* p = self->mp2C;
        self->mp2C = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    }
}

// @ 0x00c7ed00
void __cdecl FUN_00c7ed00(int* a, int* b)
{
    int local[6];
    local[0]=a[0]; local[1]=a[1]; local[2]=a[2];
    local[3]=b[0]; local[4]=b[1]; local[5]=b[2];
    FUN_00c7e780((CS*)0, 0, (void*)FUN_00c7e530, 0, (int)local);
}

// @ 0x00c7ed50
void __cdecl FUN_00c7ed50(int a, int b, int p, int d, int* e)
{
    (void)a; (void)b; (void)d;
    int n0 = (e[1] - e[0]) / 0xc;
    int n1 = (e[0xb] - e[0xa]) / 0xc;
    int* q = (int*)(p + 4);
    for (int k = 3; k != 0; --k, q += 4) {
        for (int i = 0; i < n0; ++i) {
            int* r = (int*)(e[0] + i * 0xc);
            if (q[0] == r[0] && q[1] == r[1] && q[2] == r[2]) {
                int* s = (int*)(e[5] + i * 0xc);
                q[0]=s[0]; q[1]=s[1]; q[2]=s[2];
            }
        }
    }
    q = (int*)(p + 0x34);
    for (int k = 2; k != 0; --k, q += 4) {
        for (int i = 0; i < n1; ++i) {
            int* r = (int*)(e[0xa] + i * 0xc);
            if (q[0] == r[0] && q[1] == r[1] && q[2] == r[2]) {
                int* s = (int*)(e[0xf] + i * 0xc);
                q[0]=s[0]; q[1]=s[1]; q[2]=s[2];
            }
        }
    }
}

// @ 0x00c7ee50
bool __cdecl FUN_00c7ee50(CS* self)
{
    if (self->m2031 == 0) {
        if (cSPTimer_IsRunning_00feba90((char*)self + 0x2038)) {
            uint64_t t = cSPTimer_GetElapsedTime_00bc3190((char*)self + 0x2038);
            if ((uint64_t)(((uint64_t)g_01579a14 << 32) | g_01579a10) < t) self->m2031 = 1;
        }
        return false;
    }
    return false;
}
