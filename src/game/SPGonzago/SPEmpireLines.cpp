#include "game/types.h"
#include <stddef.h>
#include <math.h>

void* AllocateBlocks(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void FreeArray(void* p);                                                                          // 0x00f47380
void* GetPlayerEmpire();                          // 0x01021300
void GetPlayerEmpireID();                               // 0x01021090
struct IUniverseCtx { bool FUN_010449e0(); };
IUniverseCtx* __stdcall FUN_01046fc0(int which);          // 0x01046fc0
struct cViewer {
    cViewer* FUN_007c3f70();                            // 0x007c3f70
    bool Init(bool flag);                               // 0x007c4dd0
    void FUN_007c3ba0();                                // 0x007c3ba0
    void FUN_007c4000();                                // 0x007c4000
};
struct ViewerHolder {
    void* mpUnk0;     // +0x00
    void* mpViewer;   // +0x04
};

typedef unsigned char      u8;
typedef unsigned int       u32;
typedef signed int         i32;
#define MOPS(p) ((COps*)(p))
static inline void** vtbl(const void* p) { return *(void***)p; }
void* FUN_01046fc0();                                  // 0x01046fc0
void* FUN_01021300();                                  // 0x01021300
void* MaterialManager();                               // 0x0067dd70
i32   __cdecl   FUN_006dde90(int n, void** out, void* a, void* b); // 0x006dde90
void  __cdecl   FUN_006ddee0();                        // 0x006ddee0
void  __cdecl   FUN_006ddef0(void* mesh);              // 0x006ddef0
void  __cdecl   FUN_006dde30(int a, int b, void* mat); // 0x006dde30
struct COps
{
    u8  FUN_00bb9c00();                    // 0x00bb9c00
    u8  FUN_00c31c50();                    // 0x00c31c50
    u8  FUN_00c31bc0();                    // 0x00c31bc0
    u8  FUN_01044bf0(void* civ);           // 0x01044bf0
    u8  FUN_010449e0(u32 arg);             // 0x010449e0
    void FUN_00c32cd0(float* out);         // 0x00c32cd0
    void FUN_007c3d30(float* a, float* b, int c, int d); // 0x007c3d30
    void* FUN_00c308d0();                  // 0x00c308d0
    void* FUN_00bef6c0();                  // 0x00bef6c0
    float* FUN_005c65e0();                 // 0x005c65e0
};
class cEmpireLayer
{
public:
    u8    pad0[0x04];                  // +0x00
    void* mpViewer;                    // +0x04

    void DrawEmpire(void* empire, void* mesh);
};
struct QuadVert
{
    float x, y, z;        // +0x00
    u32   color;          // +0x0c
    float uv0[2];         // +0x10
    float uv1[2];         // +0x18
    float uv2[2];         // +0x20
};

// ---- items of slice s00feb120 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned __int64   u64;
#define MOPS_s00fe_b120(p) ((COps_s00fe_b120*)(p))
void* FUN_00ffbe50();                                  // 0x00ffbe50
void* __stdcall FUN_00b3d3f0(void* avatar);            // 0x00b3d3f0
void* __stdcall FUN_00b3d2a0(void* arg);               // 0x00b3d2a0
void* __stdcall FUN_01021230(void* box, void* vec);    // 0x01021230
i32   __cdecl   atexit(void (*fn)(void));              // 0x011e07ef
u32*  __cdecl   FUN_00555a20(u32* begin, u32* end, u32* value, u8 flag); // 0x00555a20
void* __cdecl   memcpy(void* d, const void* s, unsigned int n);    // 0x011e0744
u32   FUN_01021090();                                  // 0x01021090
struct COps_s00fe_b120
{
    u8  FUN_00bb9c00();                    // 0x00bb9c00
    void* FUN_00bfc5f0();                  // 0x00bfc5f0
    u8  FUN_00fe4180();                    // 0x00fe4180
    u8  FUN_00c31c50();                    // 0x00c31c50
    u8  FUN_00c31bc0();                    // 0x00c31bc0
    u8  FUN_00e18c70();                    // 0x00e18c70
    u8  FUN_00feba90();                    // 0x00feba90
    u8  FUN_007c4fd0();                    // 0x007c4fd0
    u8  FUN_01044bf0(void* civ);           // 0x01044bf0
    u8  FUN_010449e0(u32 arg);             // 0x010449e0
    i32  FUN_00dd5d80(u32 a, u32 b);       // 0x00dd5d80
    void FUN_00dd6d10(u32 a, u32 b);       // 0x00dd6d10
    void FUN_00695b40(void* a, void* b, void* c); // 0x00695b40
    void FUN_00c47d80();                   // 0x00c47d80
    void FUN_00c32cd0(float* out);         // 0x00c32cd0
    void FUN_007c3d30(float* a, float* b, int c, int d); // 0x007c3d30
    void FUN_007c3c10();                   // 0x007c3c10
    void FUN_007c50b0(void* src, u8 a, u8 b); // 0x007c50b0
    void FUN_005481d0(u32* pos, u32* value);  // 0x005481d0
    void FUN_00bc3110();                   // 0x00bc3110
    void FUN_00bb1080();                   // 0x00bb1080
    void FUN_00e25bd0(void* begin, void* end); // 0x00e25bd0
    u32  FUN_00b1fdb0();                   // 0x00b1fdb0
    u32  FUN_00ba9370();                   // 0x00ba9370
    i32  FUN_00c317a0();                   // 0x00c317a0
    void* FUN_00c308d0();                  // 0x00c308d0
    void* FUN_00bef6c0();                  // 0x00bef6c0
    void* FUN_00c8b360();                  // 0x00c8b360
    float* FUN_005c65e0();                 // 0x005c65e0
    float FUN_00ffbfd0();                  // 0x00ffbfd0
    double FUN_009360d0();                 // 0x009360d0
    u64  FUN_00bc3190();                   // 0x00bc3190
};
void FUN_013ca260(void);                   // 0x013ca260
void FUN_013ca240(void);                   // 0x013ca240
class cEmpireLayer_s00fe_b120
{
public:
    u8    pad0[0x04];                  // +0x00
    void* mpViewer;                    // +0x04

    void DrawEmpire(void* empire, void* mesh);  // 0x00feb510 (cEmpireLayer::DrawEmpire)
    void DrawLayer(void* arg1, u32 layer, u32* viewer, void* mesh);
};
struct SpaceQuery
{
    u32   a;
    u32   b;
    u32   c;
    float d;
    float e;
    float f;
    u32   g;
};
// ---- items of slice s00feb120 end

// @ 0x00feb060
void __fastcall FUN_00feb060(ViewerHolder* self)
{
    // cViewer is sizeof 0x174 (SP::cViewer), allocated from the "Simulator" pool.
    void* mem = AllocateBlocks(0x174, "Simulator", 0, 0, 0, 0);
    cViewer* viewer;
    if (mem)
        viewer = ((cViewer*)mem)->FUN_007c3f70();
    else
        viewer = 0;
    self->mpViewer = viewer;
    viewer->Init(false);
}

// @ 0x00feb0b0
bool __stdcall FUN_00feb0b0(uint32_t empireID)
{
    GetPlayerEmpireID();
    if (((IUniverseCtx*)FUN_01046fc0(1))->FUN_010449e0())
        return true;
    if (((IUniverseCtx*)FUN_01046fc0(0))->FUN_010449e0()) {
        if (empireID == (uint32_t)(size_t)GetPlayerEmpire())
            return true;
    }
    return false;
}

// @ 0x00feb0f0
void __fastcall FUN_00feb0f0(ViewerHolder* self)
{
    if (self->mpViewer) {
        ((cViewer*)self->mpViewer)->FUN_007c3ba0();
        void* viewer = self->mpViewer;
        if (viewer) {
            ((cViewer*)viewer)->FUN_007c4000();
            FreeArray(viewer);
        }
    }
}

// @ 0x00feb120
void FUN_00feb120(void* mesh, void* civA, void* civB, float* dir, float t, u8 flags)
{
    float* pa = MOPS_s00fe_b120(civA)->FUN_005c65e0();
    float* pb = MOPS_s00fe_b120(civB)->FUN_005c65e0();

    float dx = pb[0] - pa[0];
    float dy = pb[1] - pa[1];
    float dz = pb[2] - pa[2];
    float length = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));

    u8 flagA = 0;
    if (MOPS_s00fe_b120(FUN_01046fc0())->FUN_01044bf0(civA) != 0)
    {
        if (flags == 0 && MOPS_s00fe_b120(civA)->FUN_00bb9c00() == 0 &&
            *(u8*)FUN_01046fc0() == 0)
            flagA = 0;
        else
            flagA = 0xff;
    }

    u8 flagB = 0;
    if (MOPS_s00fe_b120(FUN_01046fc0())->FUN_01044bf0(civB) != 0)
    {
        if (flags == 0 && MOPS_s00fe_b120(civB)->FUN_00bb9c00() == 0 &&
            *(u8*)FUN_01046fc0() == 0)
            flagB = 0;
        else
            flagB = 0xff;
    }

    if (flagA != 0 || flagB != 0)
    {
        float* verts = 0;
        float scratch[4];

        if (FUN_006dde90(4, (void**)&verts, scratch, mesh) != 0)
        {
            float ex = pb[0] - pa[0];
            float ey = pb[1] - pa[1];
            float ez = pb[2] - pa[2];
            float inv = 1.0f / (float)sqrt((double)(ey * ey + (ez * ez + ex * ex)) + 1e-08);
            inv = 1.0f / (float)sqrt((double)((ey * ey + (ez * ez + ex * ex))) + 1e-08);

            float offX = ((ez * inv) * dir[1] - (ey * inv) * dir[2]) * 0.3f;
            float offY = ((inv * ex) * dir[2] - (ez * inv) * dir[0]) * 0.3f;
            float offZ = ((ey * inv) * dir[0] - (inv * ex) * dir[1]) * 0.3f;

            QuadVert* v = (QuadVert*)verts;

            v[0].x = offX + pa[0];
            v[0].y = offY + pa[1];
            v[0].z = offZ + pa[2];

            v[1].x = offX + pb[0];
            v[1].y = offY + pb[1];
            v[1].z = offZ + pb[2];

            v[2].x = pb[0] - offX;
            v[2].y = pb[1] - offY;
            v[2].z = pb[2] - offZ;

            v[3].x = pa[0] - offX;
            v[3].y = pa[1] - offY;
            v[3].z = pa[2] - offZ;

            u32 colorA = ((u32)flagA << 24) | 0xffffff;
            u32 colorB = ((u32)flagB << 24) | 0xffffff;

            v[0].color = colorA;
            v[1].color = colorB;
            v[2].color = colorB;
            v[3].color = colorA;

            v[0].uv0[0] = 0.0f;
            v[0].uv0[1] = 0.0f;
            v[0].uv1[0] = t;
            v[0].uv1[1] = length;
            v[0].uv2[0] = 0.0f;
            v[0].uv2[1] = 0.0f;

            v[1].uv0[0] = 1.0f;
            v[1].uv0[1] = 0.0f;
            v[1].uv1[0] = t;
            v[1].uv1[1] = length;
            v[1].uv2[0] = 0.0f;
            v[1].uv2[1] = 0.0f;

            v[2].uv0[0] = 1.0f;
            v[2].uv0[1] = 1.0f;
            v[2].uv1[0] = t;
            v[2].uv1[1] = length;
            v[2].uv2[0] = 0.0f;
            v[2].uv2[1] = 0.0f;

            v[3].uv0[0] = 0.0f;
            v[3].uv0[1] = 1.0f;
            v[3].uv1[0] = t;
            v[3].uv1[1] = length;
            v[3].uv2[0] = 0.0f;
            v[3].uv2[1] = 0.0f;
        }
        FUN_006ddee0();
    }
}

// @ 0x00feb510
void cEmpireLayer_s00fe_b120::DrawEmpire(void* empire, void* mesh)
{
    void** stars = (void**)MOPS_s00fe_b120(empire)->FUN_00c308d0();
    void** other = (void**)MOPS_s00fe_b120(empire)->FUN_00bef6c0();
    i32 count = ((char*)stars[1] - (char*)stars[0]) >> 2;
    bool drew = false;

    if (MOPS_s00fe_b120(empire)->FUN_00c31c50() != 0)
        return;

    float posA[3];
    float posB[3];
    float dir[3];
    posA[0] = *(float*)0x16dac14;
    posA[1] = *(float*)0x16dac18;
    posA[2] = *(float*)0x16dac1c;
    posB[0] = *(float*)0x16dac14;
    posB[1] = *(float*)0x16dac18;
    posB[2] = *(float*)0x16dac1c;
    if (mpViewer != 0)
        MOPS_s00fe_b120(mpViewer)->FUN_007c3d30(posA, posB, 0, 0);

    double len2 = (double)posB[2] * posB[2] +
                  ((double)posB[1] * posB[1] + (double)posB[0] * posB[0]);
    float inv = (float)(1.0 / sqrt(len2 + 1e-08));
    dir[0] = inv * posB[0];
    dir[1] = inv * posB[1];
    dir[2] = inv * posB[2];

    void* playerEmpire = FUN_01021300();
    u8 colorEnabled = MOPS_s00fe_b120(playerEmpire)->FUN_00c31bc0();

    void* mat = (*(void* (__thiscall**)(u32, void*))((char*)vtbl(MaterialManager()) + 0x28))(0x71f30f82, empire);

    for (i32 i = 0; i < count; i++)
    {
        i32 a = ((i32*)stars[0])[i];
        i32 b = ((i32*)other[0])[i];
        if (a == 0 || b == 0 || a == b)
            continue;

        if (MOPS_s00fe_b120((void*)a)->FUN_00bb9c00() == 0 &&
            MOPS_s00fe_b120((void*)b)->FUN_00bb9c00() == 0 &&
            *(u8*)FUN_01046fc0() == 0 &&
            colorEnabled == 0)
            continue;

        if (!drew)
        {
            float color[3];
            MOPS_s00fe_b120(empire)->FUN_00c32cd0(color);
            *(u32*)0x16f9528 = *(u32*)0x16f9528 | 0x10;
            *(float*)0x16f96a8 = color[0];
            *(float*)0x16f96ac = color[1];
            *(float*)0x16f96b0 = color[2];
            *(float*)0x16f96b4 = *(float*)0x1485720;
            FUN_006dde30(3, 10, mat);
            drew = true;
        }

        FUN_00feb120(empire, (void*)a, (void*)b, dir,
                     (float)i / (float)count, colorEnabled);
    }

    if (drew)
        FUN_006ddef0(mesh);
}

// @ 0x00feb770
void cEmpireLayer_s00fe_b120::DrawLayer(void* arg1, u32 layer, u32* viewer, void* mesh)
{
    if (layer != 0x17)
        return;

    MOPS_s00fe_b120(mpViewer)->FUN_007c50b0((void*)*viewer, 0, 0);
    if (!MOPS_s00fe_b120(mpViewer)->FUN_007c4fd0())
        return;

    u32* guard = (u32*)0x16dac10;
    if ((*guard & 1) == 0)
    {
        *guard = *guard | 1;
        *(u32*)0x16dabfc = 0;
        *(u32*)0x16dac00 = 0;
        *(u32*)0x16dac04 = 0;
        atexit(FUN_013ca260);
    }

    SpaceQuery box;
    box.a = 0x1fff;
    box.b = 0x20;
    box.c = 0;
    box.d = 0.0f;
    box.e = *(float*)0x13eb1bc;
    box.f = *(float*)0x13eb1bc;
    box.g = 0;
    box.e = MOPS_s00fe_b120(FUN_00ffbe50())->FUN_00ffbfd0();

    MOPS_s00fe_b120((void*)0x16dabfc)->FUN_00e25bd0((void*)*(u32*)0x16dac00,
                                         (void*)*(u32*)0x16dabfc);

    void* rec = FUN_01021230(&box, (void*)0x16dabfc);
    void* r2 = MOPS_s00fe_b120(rec)->FUN_00c8b360();
    void* sm = FUN_00b3d2a0(r2);
    MOPS_s00fe_b120(sm)->FUN_00bb1080();

    if ((*guard & 2) == 0)
    {
        *guard = *guard | 2;
        *(u32*)0x16dabe4 = 0;
        *(u32*)0x16dabe8 = 0;
        *(u32*)0x16dabec = 0;
        atexit(FUN_013ca240);
    }

    u32* avBegin = *(u32**)0x16dabe4;
    u32* avEnd = *(u32**)0x16dabe8;
    memcpy(avBegin, avEnd, 0);

    i32 starCount = ((i32)*(u32*)0x16dac00 - (i32)*(u32*)0x16dabfc) >> 2;
    *(u32**)0x16dabe8 = avBegin;

    for (i32 i = 0; i < starCount; i++)
    {
        void* entry = *(void**)(*(u32*)0x16dabfc + i * 4);
        u32 avatar = MOPS_s00fe_b120(entry)->FUN_00b1fdb0();
        u8 flag = *(u8*)0x16dabf8;

        u32* pos = FUN_00555a20(*(u32**)0x16dabe4, *(u32**)0x16dabe8, &avatar, flag);
        if (pos == *(u32**)0x16dabe8)
        {
            if (pos == *(u32**)0x16dabec)
            {
                MOPS_s00fe_b120((void*)0x16dabe4)->FUN_005481d0(pos, &avatar);
            }
            else
            {
                *(u32**)0x16dabe8 = pos + 1;
                *pos = avatar;
            }
        }
        else if (avatar < *pos)
        {
            MOPS_s00fe_b120((void*)0x16dabe4)->FUN_005481d0(pos, &avatar);
        }
    }

    i32 n = ((i32)*(u32*)0x16dabe8 - (i32)*(u32*)0x16dabe4) >> 2;
    for (i32 i = 0; i < n; i++)
    {
        u32 id = (*(u32**)0x16dabe4)[i];
        void* star = FUN_00b3d2a0((void*)id);
        void* emp = (void*)MOPS_s00fe_b120(star)->FUN_00ba9370();

        FUN_01021090();

        bool draw = false;
        if (MOPS_s00fe_b120(FUN_01046fc0())->FUN_010449e0(1) != 0)
            draw = true;
        else if (MOPS_s00fe_b120(FUN_01046fc0())->FUN_010449e0(id) != 0 &&
                 FUN_01021300() == emp)
            draw = true;

        if (draw)
        {
            if (MOPS_s00fe_b120(FUN_00b3d3f0((void*)id))->FUN_00e18c70() == 0)
                DrawEmpire(emp, mesh);
        }
    }

    MOPS_s00fe_b120(mpViewer)->FUN_007c3c10();
}
