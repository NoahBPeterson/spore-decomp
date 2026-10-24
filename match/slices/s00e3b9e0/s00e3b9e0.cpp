// Slice s00e3b9e0 (batch gold1) — SP UI hint/overlay subsystem (unnamed).
// Module "Spore" (VS2008 SP1). Compiled /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast.
// These functions are all members of one UI manager object; no symbols exist for the class,
// so member access is expressed as raw offsets from `this`.

#include "types.h"
#include <math.h>

typedef unsigned int u32;

// ---- globals (addresses in comments; relocations are masked in byte diffs) ----
extern "C" {
    unsigned int  g_16acc84;                          // 0x016acc84  one-time-init bitmask
    float         g_16acc7c, g_16acc80;               // 0x016acc7c
    float         g_16acc74, g_16acc78;               // 0x016acc74
    float         g_16acc6c, g_16acc70;               // 0x016acc6c
    float         g_16acc64, g_16acc68;               // 0x016acc64
    unsigned int  DAT_016acd90, DAT_016acda0, DAT_016acdb0, DAT_016acdc0, DAT_016acdd0;
    int           DAT_016acf2c;                       // 0x016acf2c
    float         DAT_016acecc;                       // 0x016acecc
    float         DAT_016acde0;                       // 0x016acde0
    float         DAT_016acf0c;                       // 0x016acf0c
    float         DAT_015a5890;                       // 0x015a5890
    unsigned int  g_15a5984[12];                      // 0x015a5984..0x015a59b3 (mode colours)
    unsigned int  PTR_PTR_015a59b4;                   // 0x015a59b4
    unsigned int  DAT_01481d84[8];                    // 0x01481d84  id->value table
    unsigned int  DAT_013f6b3c;                       // 0x013f6b3c
    unsigned int  DAT_013eb90c;                       // 0x013eb90c  vtable
    unsigned int  DAT_013eb844;                       // 0x013eb844  vtable
}

// ---- callees ----
struct U3 { u32 x, y, z; };                                 // 12-byte uint triple (by value)
struct V3 { float x, y, z; };                               // 12-byte float triple (by value)
struct Vector2 { float x, y; };                             // 8-byte fpu pair
struct cSPHintMgr                                          // object returned by the argless getter
{
    void FUN_0067aaf0(U3 col, void* p, int a, V3 v, int b, int c);  // 0x0067aaf0 (__thiscall, ret 0x28)
};
int   SP_GetCurrentGameMode();                              // 0x00b5b800
void* FUN_0067caf0();                                       // 0x0067caf0 (argless getter; args belong to FUN_0067aaf0)
void  FUN_00677360(int);                                    // 0x00677360
void* FUN_00e3a730(unsigned int, int);                      // 0x00e3a730
int   FUN_00e36f50(unsigned int);                           // 0x00e36f50
float* FUN_00e3a000(void*, Vector2*, Vector2*, Vector2*, Vector2*, float); // 0x00e3a000
float* FUN_00e3a570(void*, float, float, Vector2*, float, Vector2*, float, float); // 0x00e3a570
void* SP_WindowManager();                                   // 0x0067caa0
void* SP_MessageServer();                                   // 0x0067dcc0
void  FUN_0067caa0();                                       // n/a
void* FUN_00b3d410();                                       // 0x00b3d410
void* FUN_0067de90();                                       // 0x0067de90
void  SP_cTelemetry_Reset(void*);                           // 0x007ebb60
void  eastl_rbtree_DoNukeSubtree(unsigned int);             // 0x009a9600
void* operator_new(unsigned int, void*, int, int, int, int);// 0x00f473a0
void* FUN_00e471e0();                                       // 0x00e471e0
void  FUN_00e46600(unsigned int, unsigned int, int, int);   // 0x00e46600
void  FUN_00e48dc0();                                       // 0x00e48dc0
void  FUN_00e37b40(void*, int, int);                        // 0x00e37b40
void  FUN_00e46020(int);                                    // 0x00e46020
void  FUN_00e37840(unsigned int, ...);                      // 0x00e37840
void  SlotMessage_Destruct(void*);                          // 0x00421cf0

#define MEM(T, o) (*(T*)((char*)this + (o)))

struct cUIManager
{
    int   FUN_00e3b5d0();   // @0x00e3b5d0 helper (defined in the binary; declaration only here)
    void  FUN_00e3b9e0(int dt);
    void  FUN_00e3be20(unsigned int p2, float a, float b, float c, float d, float e,
                       float f, float g, float h, float i, char p8);
    void  FUN_00e3c000();
    float FUN_00e3c100(float x);
    char  FUN_00e3c1a0(unsigned int* p2, float* p3, unsigned int* p4, float* p5,
                       unsigned int p6, unsigned int p7, char p8, float p9);
    char  FUN_00e38020(Vector2* a, Vector2* b, Vector2* c, Vector2* d, int flag);  // 0x00e38020 (__thiscall Timeline::ClipTracks)
};

// @ 0x00e3b9e0
void cUIManager::FUN_00e3b9e0(int dt)
{
    MEM(int, 0x288) -= dt;
    int iVar5 = MEM(int, 0x288);

    float scratch;
    switch (MEM(int, 0x284))
    {
    case 1:
    {
        int iVar5b = *(int*)(MEM(unsigned int, 0x188) - 4);
        if (iVar5b != 0 && *(int*)(iVar5b + 0xf0) != 0)
        {
            if (MEM(char, 0x27c) != 0)
                return;

            U3 col;
            switch (SP_GetCurrentGameMode())
            {
            case 0x1654c00: col.x = g_15a5984[0]; col.y = g_15a5984[1]; col.z = g_15a5984[2]; break;
            case 0x1654c01: col.x = g_15a5984[3]; col.y = g_15a5984[4]; col.z = g_15a5984[5]; break;
            case 0x1654c02: col.x = g_15a5984[6]; col.y = g_15a5984[7]; col.z = g_15a5984[8]; break;
            case 0x1654c04: col.x = g_15a5984[9]; col.y = g_15a5984[10]; col.z = g_15a5984[11]; break;
            default: goto label_1654c03;
            }
            V3 v3;
            v3.x = -1.0f; v3.y = -1.0f; v3.z = 0.0f;
            ((cSPHintMgr*)FUN_0067caf0())->FUN_0067aaf0(col, &PTR_PTR_015a59b4, 0, v3, 0, 0);
            MEM(char, 0x27c) = 1;
        }
    label_1654c03:
        if (MEM(char, 0x27c) == 0)
        {
            MEM(int, 0x284) = 2;
            return;
        }
        break;
    }
    case 2:
        if (MEM(unsigned int, 0x5c) != 0)
            ((void(__thiscall*)(void*, int, int))(*(unsigned int**)(char*)MEM(void*, 0x5c))[0x7c / 4])((void*)MEM(unsigned int, 0x5c), 2, 1);
        {
            float v = MEM(float, 0x28c) - (MEM(float, 0x98) + 1.0f);
            scratch = 0.0f;
            float* picked = &scratch;
            if (v > 0.0f) picked = &v;
            MEM(float, 0x28c) = *picked;
        }
        if (MEM(unsigned int, 0x3c) != 0)
        {
            void* o = (void*)MEM(unsigned int, 0x3c);
            float* pf = (float*)((void*(__thiscall*)(void*))(*(unsigned int**)(char*)o)[0x38 / 4])(o);
            float v = MEM(float, 0x28c) - (pf[2] - pf[0]) * DAT_016acde0;
            scratch = 0.0f;
            float* picked = &scratch;
            if (v > 0.0f) picked = &v;
            MEM(float, 0x270) = *picked;
            MEM(float, 0x290) = *picked;
        }
        MEM(unsigned int, 0x288) = DAT_016acd90;
        MEM(int, 0x284) = 3;
        return;
    case 3:
        if (iVar5 < 1)
        {
            MEM(unsigned int, 0x288) = DAT_016acda0;
            MEM(int, 0x284) = 4;
            return;
        }
        break;
    case 4:
        MEM(float, 0x270) = ((float)(DAT_016acda0 - iVar5) / (float)DAT_016acda0) *
                            (MEM(float, 0x28c) - MEM(float, 0x290)) + MEM(float, 0x290);
        if (iVar5 < 1)
        {
            if (MEM(unsigned int, 0x5c) != 0)
                ((void(__thiscall*)(void*, int, int))(*(unsigned int**)(char*)MEM(void*, 0x5c))[0x7c / 4])((void*)MEM(unsigned int, 0x5c), 2, 0);
            MEM(unsigned int, 0x288) = DAT_016acdb0;
            MEM(int, 0x284) = 5;
            return;
        }
        break;
    case 5:
        if (0 < iVar5)
            return;
        {
            int i = *(int*)(MEM(unsigned int, 0x188) - 4);
            if (i != 0 && *(int*)(i + 0xf0) != 0)
            {
                void* r = FUN_00e3a730(*(unsigned int*)(i + 0xe4), 0);
                if (r != 0)
                    FUN_00677360(1);
                MEM(unsigned int, 0x288) = DAT_016acdc0;
                MEM(int, 0x284) = 6;
                return;
            }
        }
        goto label_00e3bddf;
    case 6:
        if (0 < iVar5)
            return;
        {
            int i = *(int*)(MEM(unsigned int, 0x188) - 4);
            unsigned int id = (i != 0) ? *(unsigned int*)(i + 0xe4) : 0xa426730bu;
            int idx = FUN_00e36f50(id);
            if (*(int*)(MEM(unsigned int, 0x198) + idx * 4) != 0)
                FUN_00677360(0);
            if (i != 0 && *(unsigned int*)(i + 0xe4) == 0xbeb528cbu)
            {
                void* r = FUN_00e3a730(0x2db6dad3u, 1);
                if (r != 0)
                    FUN_00677360(1);
                MEM(unsigned int, 0x288) = DAT_016acdd0;
                MEM(int, 0x284) = 7;
                return;
            }
        }
        goto label_00e3bddf;
    case 7:
        if (0 < iVar5)
            return;
        if (*(int*)(MEM(unsigned int, 0x198) + 0x10) != 0)
            FUN_00677360(0);
    label_00e3bddf:
        MEM(int, 0x284) = 8;
        break;
    default:
        break;
    }
}

// @ 0x00e3be20
void cUIManager::FUN_00e3be20(unsigned int p2, float a, float b, float c, float d, float e,
                              float f, float g, float h, float i, char p8)
{
    if ((g_16acc84 & 1) == 0) g_16acc84 |= 1;
    if ((g_16acc84 & 2) == 0) g_16acc84 |= 2;
    if ((g_16acc84 & 4) == 0) g_16acc84 |= 4;
    if ((g_16acc84 & 8) == 0) g_16acc84 |= 8;

    void* o = (void*)MEM(unsigned int, 0x54);
    unsigned int vt = *(unsigned int*)o;
    void* (__thiscall* f1)(void*, float, float) =
        (void*(__thiscall*)(void*, float, float))(*(unsigned int**)(char*)o)[0xc4 / 4];

    float* r1 = (float*)f1(o, a, b);
    g_16acc7c = r1[0]; g_16acc80 = r1[1];
    float* r2 = (float*)f1(o, c, d);
    g_16acc74 = r2[0]; g_16acc78 = r2[1];
    float* r3 = (float*)f1(o, e, f);
    g_16acc6c = r3[0]; g_16acc70 = r3[1];
    float* r4 = (float*)f1(o, g, h);
    g_16acc64 = r4[0]; g_16acc68 = r4[1];

    FUN_00e37840(p2, g_16acc74, g_16acc78, g_16acc7c, g_16acc80, g_16acc6c, g_16acc70,
                 g_16acc64, g_16acc68);
    (void)i; (void)p8; (void)vt;
}

// @ 0x00e3c000
void cUIManager::FUN_00e3c000()
{
    int iVar1 = *(int*)(MEM(unsigned int, 0x188) - 4);
    if (iVar1 != 0)
    {
        int iVar3 = FUN_00e36f50(*(unsigned int*)(iVar1 + 0xe4));
        if (iVar3 != 4)
        {
            unsigned int local_4;
            if (iVar3 == 3)
                local_4 = (unsigned int)FUN_00e3b5d0();
            else
                local_4 = DAT_01481d84[iVar3];

            int* piVar4 = (int*)operator_new(0x10c, &DAT_013f6b3c, 0, 0, 0, 0);
            if (piVar4 != 0)
                piVar4 = (int*)FUN_00e471e0();

            int* piVar2 = (int*)MEM(unsigned int, 0x1c8);
            if (piVar4 != piVar2)
            {
                if (piVar4 != 0)
                    ((void(__thiscall*)(void*))(*(unsigned int**)(char*)piVar4)[0])(piVar4);
                MEM(unsigned int, 0x1c8) = (unsigned int)piVar4;
                if (piVar2 != 0)
                    ((void(__thiscall*)(void*))piVar2[1])(piVar2);
            }
            FUN_00e46600(MEM(unsigned int, 0x60), local_4, 1, 0);
            FUN_00e48dc0();
            FUN_00e37b40((void*)MEM(unsigned int, 0x1c8), 0, 1);
            if (*(int*)(iVar1 + 0xf0) != 0)
                FUN_00e46020(0);
        }
    }
}

// @ 0x00e3c100
float cUIManager::FUN_00e3c100(float x)
{
    float local_4 = x;
    int iVar1 = FUN_00e3b5d0();
    if (iVar1 == (int)0xa7a9e952)
    {
        if (0.33333334f < x)
            return x - 1.3333334f;
        local_4 = x + 0.6666667f;
    }
    else if (iVar1 == 0x2500e82c)
    {
        if (x < -0.33333334f)
            return x + 1.3333334f;
        return x - 0.6666667f;
    }
    return local_4;
}

// @ 0x00e3c1a0
char cUIManager::FUN_00e3c1a0(unsigned int* p2, float* p3, unsigned int* p4, float* p5,
                              unsigned int p6, unsigned int p7, char p8, float p9)
{
    Vector2 p2c, p3c, p4c, p5c;
    p2c.x = ((float*)p2)[0]; p2c.y = ((float*)p2)[1];
    p3c.x = p3[0];           p3c.y = p3[1];
    p4c.x = ((float*)p4)[0]; p4c.y = ((float*)p4)[1];
    p5c.x = p5[0];           p5c.y = p5[1];

    int iVar8 = 0x1e;
    float local_54 = (float)MEM(int, 0x280) / (float)DAT_016acf2c;
    int local_90 = 0x1e;
    char cVar4 = 0;

    if (p8 != 0)
    {
        cVar4 = FUN_00e38020(&p2c, &p3c, &p4c, &p5c, p7);
        if (cVar4 != 0)
        {
            local_90 = 0xf;
            iVar8 = 0xf;
        }
    }
    float local_a8 = p3c.x, local_a4 = p3c.y;
    int local_8c = 1;

    if (iVar8 != 0)
    {
        float local_60 = (float)iVar8;
        do
        {
            Vector2 obuf;
            float* pf = FUN_00e3a000(&obuf, &p2c, &p3c, &p4c, &p5c,
                                     (float)((double)local_8c / (double)local_60));
            float fVar1 = pf[0];
            float fVar2 = pf[1];
            if (MEM(unsigned int, 0x58) != 0 && MEM(unsigned int, 0x5c) != 0)
            {
                float fVar10;
                if (fVar1 == local_a8)
                    fVar10 = 0.0f;
                else
                    fVar10 = (MEM(float, 0x88) - local_a8) / (fVar1 - local_a8);
                float local_7c = (fVar1 - local_a8) * fVar10 + local_a8;
                float local_50 = (fVar2 - local_a4) * fVar10 + local_a4;

                void* o = (void*)MEM(unsigned int, 0x58);
                void* (__thiscall* vc4)(void*, float, float) =
                    (void*(__thiscall*)(void*, float, float))(*(unsigned int**)(char*)o)[0xc4 / 4];
                unsigned int tmp[2];
                vc4(o, local_7c, local_50);
                vc4(o, fVar1, fVar2);

                MEM(unsigned int, 0x24c) = tmp[0];
                if (local_a8 <= local_7c && local_7c <= fVar1)
                {
                    void* o2 = (void*)MEM(unsigned int, 0x5c);
                    unsigned int vtf = *(unsigned int*)o2;
                    float* puV = (float*)((void*(__thiscall*)(void*))(*(unsigned int**)(char*)o2)[0x38 / 4])(o2);
                    ((void(__thiscall*)(void*, float, unsigned int))(*(unsigned int**)(char*)vtf)[0x70 / 4])(o2, puV[0], tmp[1]);
                    MEM(float, 0x88) = local_7c;
                    MEM(float, 0x8c) = local_50;
                    MEM(char, 0x249) = 1;
                    iVar8 = local_90;
                }
            }

            float fVar10b = DAT_016acecc * p9;
            if (fVar1 != local_a8)
            {
                double ang = DAT_015a5890 - atan(fabs((fVar2 - local_a4) / (fVar1 - local_a8)));
                fVar10b = fVar10b / (float)sin(ang);
            }
            float fStack_80 = local_a4 + fVar10b;
            float fStack_74 = fVar2 - fVar10b;
            float fStack_6c = fVar2 + fVar10b;

            Vector2 t1, t2, t3, t4;
            float* r;
            r = FUN_00e3a570(&t1, local_a8, local_a4 - fVar10b, &p3c, DAT_016acf0c, &p4c, DAT_016acf0c, -1.0f);
            float fStack_48 = r[0], fStack_44 = r[1];
            r = FUN_00e3a570(&t2, local_a8, fStack_80, &p3c, DAT_016acf0c, &p4c, DAT_016acf0c, 1.0f);
            float uStack_84 = r[0], fStack_80b = r[1];
            r = FUN_00e3a570(&t3, fVar1, fStack_74, &p3c, DAT_016acf0c, &p4c, DAT_016acf0c, -1.0f);
            float uStack_78 = r[0], fStack_74b = r[1];
            r = FUN_00e3a570(&t4, fVar1, fStack_6c, &p3c, DAT_016acf0c, &p4c, DAT_016acf0c, 1.0f);
            float uStack_70 = r[0], fStack_6cb = r[1];
            float fStack_4c = fVar10b / DAT_016acecc;

            void* wm = SP_WindowManager();
            wm = (void*)((void*(__thiscall*)(void*))(*(unsigned int**)(char*)wm)[4 / 4])(wm);
            float* pf2 = (float*)((void*(__thiscall*)(void*))(*(unsigned int**)(char*)wm)[0x38 / 4])(wm);
            if (fStack_48 < (pf2[2] - pf2[0]) * local_54)
            {
                FUN_00e3be20(p6, fStack_48, fStack_44, uStack_84, fStack_80b, uStack_78,
                             fStack_74b, uStack_70, fStack_6cb, fStack_4c, p8);
            }
            local_8c = local_8c + 1;
            local_a8 = fVar1;
            local_a4 = fVar2;
        } while (local_8c <= iVar8);
    }
    return cVar4;
}

// @ 0x00e3c6f0
void FUN_00e3c6f0(char param_1, unsigned int param_2)
{
    void* iVar1 = FUN_00b3d410();
    if (iVar1 != 0)
    {
        unsigned char local_40_data[0x40];
        (void)local_40_data;
        *(unsigned int*)(local_40_data + 0x00) = 0;   // local_10
        *(unsigned int*)(local_40_data + 0x04) = 0;   // local_3c[0] xchg
        *(unsigned int*)(local_40_data + 0x08) = DAT_013eb844;
        *(unsigned int*)(local_40_data + 0x0c) = (param_1 != 0) ? 1u : 0u;
        *(unsigned int*)(local_40_data + 0x10) = 0;
        *(unsigned int*)(local_40_data + 0x14) = param_2;

        void* server = SP_MessageServer();
        // vcall slot 0x14: PostMessage(0x6256b62, &local, iVar1)
        struct { unsigned int vt; unsigned int data[0x40 / 4]; } msg;
        msg.vt = (unsigned int)(local_40_data + 4);
        ((void(__thiscall*)(void*, unsigned int, void*, void*))(*(unsigned int**)(char*)server)[0x14 / 4])
            (server, 0x06256b62u, &msg, iVar1);
        SlotMessage_Destruct(local_40_data);
    }
}

// @ 0x00e3c760
void FUN_00e3c760(void)
{
    void* p0 = FUN_0067de90();
    if (p0 != 0)
    {
        void* t = ((void*(__stdcall*)(int))FUN_0067de90)(0xc);
        ((void(__thiscall*)(void*))SP_cTelemetry_Reset)(t);
    }
    void* q = FUN_00b3d410();
    if (q != 0)
    {
        char* p = (char*)FUN_00b3d410();
        char* esi = p + 0x250;
        unsigned int v = *(unsigned int*)(p + 0x25c);
        ((void(__thiscall*)(void*, unsigned int))eastl_rbtree_DoNukeSubtree)(esi, v);
        *(int*)(esi + 8) = (int)(esi + 4);
        *(int*)(esi + 4) = (int)(esi + 4);
        *(int*)(esi + 0xc) = 0;
        *(char*)(esi + 0x10) = 0;
        *(int*)(esi + 0x14) = 0;
        *(int*)(p + 0x298) = 0;
    }
}
