// s00e83910 -- SP editor helpers: terrain-sphere unlock/save plumbing, verb-icon
//               geometry, quaternion placement, resource lookups and the editor
//               launch message.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-

#include <math.h>
#include <intrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef signed int     i32;
typedef unsigned __int64 u64;
typedef float          f32;

#pragma warning(disable: 4100)

#define MOPS(p) ((COps*)(p))
#define VT(p)   (*(void***)(p))

static inline void Release(void* p)
{
    if (p) { void** vt = *(void***)p; ((void (__thiscall*)(void*))vt[1])(p); }
}

// ---------------------------------------------------------------------------
// callees that are plain (non-ecx) functions in the original binary
// ---------------------------------------------------------------------------
void* __cdecl FUN_0067de40();                                     // 0x0067de40
void* __cdecl FUN_0067de60();                                     // 0x0067de60
void* __cdecl FUN_0067dcd0();                                     // 0x0067dcd0
void* __cdecl FUN_00675250();                                     // 0x00675250
u8    __cdecl FUN_006ab760(void* a, const u16* b);                // 0x006ab760
i32*  __cdecl FUN_0041ea00();                                     // 0x0041ea00
void* __cdecl FUN_00b3d300();                                     // 0x00b3d300
u64   __cdecl FUN_00593980(u32 a, i32 b);                         // 0x00593980
void* __cdecl FUN_00f473a0(u32 size, const char* file, u32 a, u32 b, u32 c, u32 d); // 0x00f473a0
void  __cdecl FUN_00f47380(void* p);                              // 0x00f47380
void  __cdecl FUN_004ba150(void* out);                            // 0x004ba150
u8    __cdecl FUN_006ad010(char* name);                           // 0x006ad010
void* __cdecl FUN_008de1a0();                                     // 0x008de1a0
void* __cdecl FUN_006b1f90(u32 area, u32 b, void* c);             // 0x006b1f90
void  __cdecl FUN_006b4b60(void* a, void* b);                     // 0x006b4b60
void* __cdecl FUN_00401090();                                     // 0x00401090
void* __cdecl FUN_009289f0(void* pool, u32 a, u32 b, u32 c, u32 d, u32 e); // 0x009289f0
void* __cdecl FUN_008ddb00(void* a, void* b, void* c, void* d, u32 e, void* f); // 0x008ddb00
u8    __cdecl FUN_008ddb90(void* a, void* b, void* c, void* d, u32 e); // 0x008ddb90
void  __cdecl FUN_009276c0(void* pool, void* p);                  // 0x009276c0
i32   __cdecl FUN_00e82770(void* p);                              // 0x00e82770
void  __cdecl FUN_004bafc0(void* a, void* b);                     // 0x004bafc0
void  __cdecl FUN_0059c190(f32* mat, f32* q);                     // 0x0059c190
void  __cdecl FUN_005a9200(void* launch);                         // 0x005a9200
void* __cdecl FUN_011e0744(void* d, const void* s, u32 n);        // 0x011e0744
void* __cdecl FUN_0067dcc0();                                     // 0x0067dcc0

extern u16 gEmptyString16[];                       // 0x01667bac
extern u16 gString16_b[];                          // 0x01667bae
extern f32 gHalf;                                  // 0x01471064
extern f32 gOne;                                   // 0x01485720
extern f32 gVerbScale;                             // 0x01486114
extern f32 gQScale;                                // 0x01470f1c
extern u32 gSignMask[4];                           // 0x013eb8b0
extern u32 gEditorVecA;                            // 0x016b4504
extern u32 gEditorVecB;                            // 0x016b4508
extern u32 gEditorVecC;                            // 0x016b450c
extern u32 gEditorMat[9];                          // 0x016b4554
extern void* gMemPool;                             // 0x016c8b44
extern u32 gVerbTable[];                           // 0x014860ac
extern u32 gVerbBaseA;                             // 0x0150d6d8
extern u32 gVerbBaseB;                             // 0x0150d6dc

// ---------------------------------------------------------------------------
// callees invoked with ecx == an object pointer
// ---------------------------------------------------------------------------
struct COps
{
    void* FUN_00f67d90();                              // 0x00f67d90
    void  FUN_006751a0(u32 a, void** out);             // 0x006751a0
    void  FUN_00c7a1f0(u32 player);                    // 0x00c7a1f0
    void  FUN_00598540(u32 key);                       // 0x00598540
    void  FUN_00598db0(i32 a, i32 b, i32 c, i32 d, i32 e,
                       i32 f, i32 g, f32 h, i32 i);    // 0x00598db0
    void  FUN_00596d70(i32 a, i32 b);                  // 0x00596d70
    u8    FUN_00595110(void* a, i32 b);                // 0x00595110
    void  FUN_00596da0(i32 a, i32 b, i32 c);           // 0x00596da0
    void  FUN_005942e0();                              // 0x005942e0
    void* FUN_00414e10();                              // 0x00414e10
    void  FUN_004df310(void* key);                     // 0x004df310
    void  FUN_00423650(const u16* first, const u16* last);// 0x00423650
    void  FUN_00475ab0(u32 n);                         // 0x00475ab0
    void  FUN_00550cf0(u16** wstr);                    // 0x00550cf0
    void* FUN_005508c0(u32 id, u32 a, u32 b);          // 0x005508c0
    void  FUN_00551240(void* a, const u16* name, const u16* summary,
                       u32 b, void* c, u32 d, u32 e);  // 0x00551240
    void* FUN_005a9080();                              // 0x005a9080
    void  FUN_005a9080_b();                            // 0x005a9080
};

// ---------------------------------------------------------------------------
// 0x00e83910
// ---------------------------------------------------------------------------
struct cTerrainSphere
{
    u8    pad0[0x10e8];        // +0x0000
    void* mpCollectables;      // +0x10e8
    u32   mKeyA;               // +0x10ec
    u8    pad10f0[0x0c];       // +0x10f0
    u32   mKeyB;               // +0x10fc
};

struct cResKey
{
    u32 v0;                    // +0x00
    u32 v1;                    // +0x04
    u32 v2;                    // +0x08
    u32 pad;                   // +0x0c
};

// @ 0x00e83910
void FUN_00e83910(u32 arg1, u32 arg2, u32 arg3)
{
    cTerrainSphere* ed = (cTerrainSphere*)MOPS(FUN_00b3d300())->FUN_00f67d90();
    ed->mKeyA = arg2;
    ed->mKeyB = arg3;

    cResKey local_40;
    local_40.v0 = 0;
    local_40.v1 = 0;
    local_40.v2 = 0;

    void* idgen = FUN_0067de60();
    ((void (__thiscall*)(void*, void*, u32, u32, u32, u32, u32))VT(idgen)[0x04 / 4])(
        idgen, &local_40, 0x2b978c46, 0x62, 0, 0x62, 0);

    void* guard = 0;
    void* mgr = FUN_0067dcd0();
    if (guard) Release(guard);

    void* obj = 0;
    u8 ok = ((u8 (__thiscall*)(void*, u32, void**, u32, u32, u32, u32))VT(mgr)[0x0c / 4])(
                mgr, arg1, &obj, 0, 0, 0, 0);
    if (ok)
    {
        MOPS(ed)->FUN_00c7a1f0(*(u32*)&obj);
        if (ed->mpCollectables)
        {
            MOPS(ed->mpCollectables)->FUN_00598540(0x465c50ba);
            u32* p = gVerbTable;
            do
            {
                u64 a = FUN_00593980(gVerbBaseA, p[-1]);
                u64 b = FUN_00593980(gVerbBaseB, p[0]);
                MOPS(ed->mpCollectables)->FUN_00598db0(
                    (i32)b, (i32)(b >> 32), 0, 0, 0, 0, 0, 0.0f, 0);
                MOPS(ed->mpCollectables)->FUN_00596d70((i32)b, (i32)(b >> 32));
                if (guard && MOPS(ed->mpCollectables)->FUN_00595110((void*)a, (i32)(a >> 32)))
                    MOPS(ed->mpCollectables)->FUN_00596da0((i32)b, (i32)(b >> 32), 0);
                p += 2;
            } while ((u32)p < 0x148610c);
            MOPS(ed->mpCollectables)->FUN_005942e0();
        }
        void* blk = 0;
        FUN_004ba150(&blk);
        *((u32*)blk + 2) = local_40.v0;
        *((u32*)blk + 3) = local_40.v1;
        *((u32*)blk + 4) = local_40.v2;
        FUN_006ad010((char*)blk);
        cResKey key2;
        key2.v0 = local_40.v0;
        key2.v1 = local_40.v1;
        key2.v2 = 0x1a99b06b;
        void* dbg = FUN_008de1a0();
        ((void (__thiscall*)(void*, void*, u32))VT(dbg)[0x6c / 4])(dbg, blk, 1);
        void* sa = FUN_006b1f90(0x11ac199, 0, &key2);
        FUN_006b4b60(blk, sa);
        void* spm = FUN_00401090();
        MOPS(spm)->FUN_004df310(&local_40);
        Release(blk);
    }

    cResKey keyA;
    keyA.v0 = *(u32*)&local_40.v0;
    keyA.v1 = 0x2f7d0004;
    keyA.v2 = local_40.v2;
    void* resmgr = FUN_0067dcd0();
    void* res = ((void* (__thiscall*)(void*, void*))VT(resmgr)[0x58 / 4])(resmgr, &keyA);
    void* sa2 = FUN_006b1f90(0x11ac199, 0, 0);
    u8 flag = 0;

    if (res && sa2)
    {
        u8 c1 = ((u8 (__thiscall*)(void*, void*, u32, u32, u32, u32, void*))VT(res)[0x34 / 4])(
                    res, &keyA, 0, 1, 6, 0, &keyA.v2);
        if (c1 && keyA.v2 != 0xffffffff)
        {
            void* p = FUN_009289f0(gMemPool, keyA.v2, 0, 0, 0, 0);
            void* r2 = FUN_008ddb00(res, &keyA, p, (void*)keyA.v2, 1, 0);
            if (r2 == (void*)keyA.v2)
                flag = FUN_008ddb90(sa2, &keyA, p, r2, 1);
            if (p) FUN_009276c0(gMemPool, p);
            if (flag)
            {
                keyA.v1 = (keyA.v1 & 0xffffff01) | 1;
                u8 c2 = ((u8 (__thiscall*)(void*, void*, u32, u32, u32, u32, void*))VT(res)[0x34 / 4])(
                            res, &keyA, 0, 1, 6, 0, &keyA.v2);
                if (c2 && keyA.v2 != 0xffffffff)
                {
                    void* q = FUN_009289f0(gMemPool, keyA.v2, 0, 0, 0, 0);
                    void* r3 = FUN_008ddb00(res, &keyA, q, (void*)keyA.v2, 1, 0);
                    if (r3 == (void*)keyA.v2)
                        flag = FUN_008ddb90(sa2, &keyA, q, r3, 1);
                    if (q) FUN_009276c0(gMemPool, q);
                }
            }
        }
    }

    cResKey keyB;
    keyB.v0 = ((u32*)&keyA.v0)[0];
    keyB.v1 = 0x30bdee3;
    keyB.v2 = ((u32*)&keyA.v0)[2];
    void* guard2 = 0;
    if (flag)
    {
        void* mgr2 = FUN_0067dcd0();
        if (guard2) Release(guard2);
        void* obj2 = 0;
        if (((u8 (__thiscall*)(void*, void*, void**, u32, u32, u32, u32))VT(mgr2)[0x0c / 4])(
                mgr2, &keyB, &obj2, 0, 0, 0, 0))
        {
            void* meta = obj2
                ? ((void* (__thiscall*)(void*, u32))VT(obj2)[0x0c / 4])(obj2, 0x30bdee3)
                : 0;
            void* aobj = FUN_00f473a0(0xd8, "Pollinator", 0, 0, 0, 0);
            if (aobj)
            {
                void* md = MOPS(aobj)->FUN_005a9080();
                if (md) Release(md);
            }
            u16* ws0 = gEmptyString16;
            u16* ws1 = gEmptyString16;
            u16* ws2 = gString16_b;
            MOPS(meta)->FUN_00550cf0(&ws0);
            void* mid = MOPS(meta)->FUN_005508c0((u32)ws0, (u32)meta, 0);
            void* nm = MOPS(meta)->FUN_00414e10();
            MOPS(meta)->FUN_00551240(&keyB, (const u16*)nm, (const u16*)mid,
                                     (u32)ws0, &keyB, 0, 0);
            void* mgr3 = FUN_0067dcd0();
            ((void (__thiscall*)(void*, void*, u32, void*, u32, u32))VT(mgr3)[0x20 / 4])(
                mgr3, meta, 0, sa2, 0, 0);
            if (((u32)ws2 - (u32)ws0 & 0xfffffffe) > 2 && ws0)
                FUN_00f47380(ws0);
            Release(meta);
        }
        Release(guard2);
    }
}

// ---------------------------------------------------------------------------
// 0x00e83e30
// ---------------------------------------------------------------------------
// @ 0x00e83e30
void FUN_00e83e30(i32* param_1, u8* param_2, u32* param_3)
{
    if (param_3[1] == 0x476a98c7)
    {
        *param_1 = 1;
        param_2[0] = 1;
        *(u32*)(param_2 + 4) = 0xb;
        *(u32*)(param_2 + 8) = gEditorVecA;
        *(u32*)(param_2 + 0xc) = gEditorVecB;
        *(u32*)(param_2 + 0x10) = gEditorVecC;
        for (int i = 0; i < 9; i++)
            ((u32*)(param_2 + 0x14))[i] = gEditorMat[i];
        *(f32*)(param_2 + 0x38) = gOne;
        *(u32*)(param_2 + 0x3c) = gEditorVecA;
        *(u32*)(param_2 + 0x40) = gEditorVecB;
        *(u32*)(param_2 + 0x44) = gEditorVecC;
        return;
    }

    void* local_2c = 0;
    FUN_004bafc0(param_3, &local_2c);
    i32 cnt = (*(i32*)((u8*)local_2c + 0x9c) - *(i32*)((u8*)local_2c + 0x98)) / 0x8c;
    i32 n = cnt > 0x40 ? 0x40 : cnt;
    *param_1 = 0;
    for (i32 i = 0; i < n; i++)
    {
        u8* p = (u8*)(*(i32*)((u8*)local_2c + 0x98) + i * 0x8c);
        i32 r = FUN_00e82770(p);
        i32 idx = *param_1;
        *param_1 = idx + 1;
        u8* rec = param_2 + idx * 0x48;
        *(i32*)(rec + 4) = r;
        rec[0] = (*(u16*)(p + 6) == 0xffff) ? 1 : 0;

        f32 s = *(f32*)(p + 0x2c);
        f32 m14 = s * (*(f32*)(p + 0x14) * gVerbScale);
        f32 m18 = s * (*(f32*)(p + 0x18) * gVerbScale);
        f32 m1c = s * (*(f32*)(p + 0x1c) * gVerbScale);
        f32 m20 = s * (*(f32*)(p + 0x20) * gVerbScale);
        f32 m24 = s * (*(f32*)(p + 0x24) * gVerbScale);
        f32 m28 = s * (*(f32*)(p + 0x28) * gVerbScale);

        f32 t14 = (m28 + m1c) * gHalf;
        f32 t18 = (m20 - m14) * gHalf;
        f32 t1c = (m20 + m14) * gHalf;
        f32 t20 = (m24 + m18) * gHalf;
        f32 t24 = (m28 - m1c) * gHalf;

        *(f32*)(rec + 8) = *(f32*)(p + 0x54) * gVerbScale +
            (*(f32*)(p + 0x48) * t14 + *(f32*)(p + 0x3c) * t20 + *(f32*)(p + 0x30) * t1c);
        *(f32*)(rec + 0xc) = *(f32*)(p + 0x58) * gVerbScale +
            (*(f32*)(p + 0x4c) * t14 + *(f32*)(p + 0x40) * t20 + *(f32*)(p + 0x34) * t1c);
        *(u32*)(rec + 0x10) = 0;

        f32 a1 = fabsf(t24);
        f32 a2 = fabsf(t18);
        f32 mx = a1 > a2 ? a1 : a2;
        *(f32*)(rec + 0x38) = mx;
        f32 sc = (r == 2 && *param_3 == 0xd9007204) ? gHalf : gOne;
        *(f32*)(rec + 0x38) = mx * sc;

        for (int k = 0; k < 9; k++)
            ((u32*)(rec + 0x14))[k] = ((u32*)(p + 0x30))[k];
        *(u32*)(rec + 0x3c) = *(u32*)(p + 0x60);
        *(u32*)(rec + 0x40) = *(u32*)(p + 0x64);
        *(u32*)(rec + 0x44) = *(u32*)(p + 0x68);
    }
    if (local_2c) Release(local_2c);
}

// ---------------------------------------------------------------------------
// 0x00e84150
// ---------------------------------------------------------------------------
// @ 0x00e84150
void FUN_00e84150(u8* param_1, i32 param_2, u16* param_3)
{
    i32* P = *(i32**)(param_1 + 0x17c);
    i32* V = (i32*)*P;
    i32 count = (*(i32*)((u8*)V + 0x388) - *(i32*)((u8*)V + 0x384)) / 0x468;
    i32 i20 = *(i32*)((u8*)P + 0x2e4);
    i32* pi23 = (i32*)(*(i32*)((u8*)V + 0x384) + 0x21c);
    i32 idx = 0;
    while (idx < count)
    {
        if (*pi23 == param_2)
        {
            u8* pP = (u8*)P;
            u8* p20 = (u8*)i20;
            f32 a = *(f32*)(pP + 0x3c);
            f32 b = *(f32*)(pP + 0x40);
            f32 c = *(f32*)(pP + 0x44);
            f32 d = *(f32*)(pP + 0x48);
            f32 e = *(f32*)(p20 + 0x10);
            f32 f = *(f32*)(p20 + 0x14);
            f32 g = *(f32*)(p20 + 0x18);
            f32 h = *(f32*)(p20 + 0x1c);
            f32 k = *(f32*)(p20 + 0x20);
            f32 l = *(f32*)(p20 + 0x24);
            f32 m = *(f32*)(p20 + 0x28);

            f32 q[4];
            q[0] = ((a * m + h * d) - b * l) + c * k;
            q[1] = ((l * a + b * m) + k * d) - c * h;
            q[2] = ((l * d - k * a) + c * m) + b * h;
            q[3] = ((m * d - a * h) - k * b) - c * l;

            f32 mat[9];
            FUN_0059c190(mat, q);

            *param_3 |= 6;
            *(f32*)((u8*)param_3 + 4) =
                *(f32*)(pP + 0x18) +
                ((((a * c + b * d) * g + (-(b * b) - (c * c)) * e) +
                  (a * b - c * d) * f) * gQScale + e);
            *(u16*)((u8*)param_3 + 2) += 2;
            *(f32*)((u8*)param_3 + 8) =
                *(f32*)(pP + 0x1c) +
                ((((b * c - a * d) * g + (-(a * a) - (c * c)) * f) +
                  (a * b + c * d) * e) * gQScale + f);
            *(f32*)((u8*)param_3 + 0xc) = 0.0f;
            for (int i = 0; i < 9; i++)
                ((u32*)((u8*)param_3 + 0x14))[i] = ((u32*)mat)[i];
            return;
        }
        idx++;
        i20 += 0x2bc;
        pi23 = (i32*)((u8*)pi23 + 0x468);
    }

    for (int i = 0; i < 9; i++)
        ((u32*)((u8*)param_3 + 0x14))[i] = gEditorMat[i];
    *(f32*)((u8*)param_3 + 0x10) = gOne;
    *(u32*)((u8*)param_3 + 4) = gEditorVecA;
    *(u32*)((u8*)param_3 + 8) = gEditorVecB;
    *(u32*)((u8*)param_3 + 0xc) = gEditorVecC;
    *(u16*)((u8*)param_3 + 0) = 0;
    *(u16*)((u8*)param_3 + 2) = 0;
}

// ---------------------------------------------------------------------------
// 0x00e84470
// ---------------------------------------------------------------------------
// @ 0x00e84470
void FUN_00e84470()
{
    void* mgr = FUN_0067de40();
    FUN_006ab760(((void* (__thiscall*)(void*))VT(mgr)[0x14 / 4])(mgr), (const u16*)L"fr-fr");
}

// ---------------------------------------------------------------------------
// 0x00e84490
// ---------------------------------------------------------------------------
// @ 0x00e84490
i32 FUN_00e84490(u32 param_1, u32 param_2)
{
    void* local_8 = 0;
    void* local_4;

    MOPS(FUN_00675250())->FUN_006751a0(param_1, &local_8);

    if (local_8 != 0)
    {
        i32 result =
            (((u8 (__thiscall*)(void*, u32, void**))VT(local_8)[0x24 / 4])(local_8, param_2, &local_4) &&
             *(u16*)((u8*)local_4 + 0x12) == 10)
                ? *FUN_0041ea00()
                : (i32)(size_t)local_4;
        Release(local_8);
        return result;
    }
    return (i32)(size_t)local_4;
}

// ---------------------------------------------------------------------------
// 0x00e84510
// ---------------------------------------------------------------------------
// @ 0x00e84510
u32 FUN_00e84510(u32* param_1)
{
    if (param_1[0] != 0)
    {
        u32 key[3];
        key[0] = param_1[0];
        key[1] = 0x30bdee3;
        key[2] = param_1[2];

        void* obj = 0;
        void* mgr = FUN_0067dcd0();
        if (obj) Release(obj);
        u8 ok = ((u8 (__thiscall*)(void*, u32*, void**, u32, u32, u32, u32))VT(mgr)[0x0c / 4])(
                    mgr, key, &obj, 0, 0, 0, 0);
        if (ok)
        {
            void* meta = obj
                ? ((void* (__thiscall*)(void*, u32))VT(obj)[0x0c / 4])(obj, 0x30bdee3)
                : 0;
            const u16* nm = (const u16*)MOPS(meta)->FUN_00414e10();
            const u16* e = nm;
            while (*e)
                ++e;
            MOPS(obj)->FUN_00423650(nm, e);
            Release(obj);
            return 1;
        }
        Release(obj);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00e84600
// ---------------------------------------------------------------------------
struct cEditorLaunch
{
    void* mpVtbl;      // +0x00
    u8    pad04[0x0c];
    u32   mField0c;    // +0x0c
    u32   mField10;    // +0x10
    u32   mField14;    // +0x14
    u32   mField18;    // +0x18
    u8    pad1c[0x20 - 0x1c];
    u8    mField20;    // +0x20
    u8    pad21[0x34 - 0x21];
    u8    mField34;    // +0x34
    u8    mField36;    // +0x36
    u8    mField37;    // +0x37
    u8    mField38;    // +0x38
    u8    mField39;    // +0x39
    u8    pad3a[0x3c - 0x3a];
    u8    mField3c;    // +0x3c
    u8    mField3d;    // +0x3d
    u8    pad3e[0x60 - 0x3e];
    f32   mField60;    // +0x60
    u8    mField64;    // +0x64
};

struct cRegMessage
{
    void* mpVtbl;      // +0x00
    u32   mField04;    // +0x04
    u32   mField08;    // +0x08
    u32   mField0c;    // +0x0c
    u32   mField10;    // +0x10
    u32   mField14;    // +0x14
    u32   mField18;    // +0x18
    u8    pad1c[0x30 - 0x1c];
    u32   mField30;    // +0x30
    u8    pad34[0x38 - 0x34];
    u32   mField38;    // +0x38
};

// @ 0x00e84600
void FUN_00e84600(u8 a1, i32 a2, u8 a3, u32* a4, f32 a5, u8 a6, void* a7,
                  u32 a8, u32 a9)
{
    u32 payload;
    if (a1 != 0)
    {
        cEditorLaunch* d = (cEditorLaunch*)FUN_00f473a0(0x9c, "App", 0, 0, 0, 0);
        if (d)
        {
            MOPS(d)->FUN_005a9080();
            Release(d);
        }
        if (a3 != 0)
            d->mField20 = 1;
        d->mField0c = a2;
        d->mField10 = a4[0];
        d->mField14 = a4[1];
        d->mField18 = a4[2];
        *(u32*)((u8*)d + 0x90) = 0x1100000;
        d->mField60 = a5;
        FUN_005a9200(d);
        ((void (__thiscall*)(void*))VT(d)[0x08 / 4])(d);
        payload = 1000;
    }
    else if (a6 == 0)
    {
        cEditorLaunch* d = (cEditorLaunch*)FUN_00f473a0(0x9c, "App", 0, 0, 0, 0);
        if (d)
        {
            MOPS(d)->FUN_005a9080();
            Release(d);
        }
        if (a3 != 0)
            d->mField20 = 1;
        d->mField0c = a2;
        d->mField10 = a4[0];
        d->mField14 = a4[1];
        d->mField18 = a4[2];
        *(u32*)((u8*)d + 0x90) = 0x1100000;
        void* old = *(void**)((u8*)d + 0x94);
        if (a7 != old)
        {
            if (a7) ((void (__thiscall*)(void*))VT(a7)[0])(a7);
            *(void**)((u8*)d + 0x94) = a7;
            if (old) Release(old);
        }
        d->mField34 = 0;
        d->mField36 = 0;
        d->mField38 = 0;
        d->mField37 = 0;
        d->mField39 = 0;
        d->mField3c = 1;
        d->mField3d = 0;
        d->mField64 = 0;
        d->mField60 = a5;
        FUN_005a9200(d);
        ((void (__thiscall*)(void*))VT(d)[0x08 / 4])(d);
        payload = a9;
    }
    else
    {
        payload = a1;
    }

    void* ms = FUN_0067dcc0();
    cRegMessage* rm = (cRegMessage*)FUN_00f473a0(0x40, "App", 0, 0, 0, 0);
    if (rm)
    {
        rm->mField30 = 0;
        rm->mpVtbl = (void*)0x13eb90c;
        _InterlockedExchange((volatile long*)&rm->mField04, 0);
        rm->mpVtbl = (void*)0x13eb844;
        rm->mField38 = 0;
    }
    rm->mField30 = 0x90a03fdf;
    rm->mField08 = payload;
    rm->mField10 = 0;
    rm->mField18 = 1;
    ((void (__thiscall*)(void*, u32, void*, u32, u32))VT(ms)[0x18 / 4])(
        ms, rm->mField30, rm, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x00e847f0
// ---------------------------------------------------------------------------
struct cString8
{
    u8*  mpBegin;      // +0x00
    u8*  mpEnd;        // +0x04
    u8*  mpCap;        // +0x08
    u8   pad0c[4];     // +0x0c
    u32  mKey0;        // +0x10
    u32  mKey1;        // +0x14

    void FUN_00475ab0(u32 n);                       // 0x00475ab0
    cString8* FUN_00e847f0(u32* src, u32* key);
};

// @ 0x00e847f0
cString8* cString8::FUN_00e847f0(u32* src, u32* key)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCap = 0;

    u8* begin = (u8*)src[0];
    u8* end = (u8*)src[1];
    u32 count = (u32)(end - begin);

    FUN_00475ab0(count + 1);

    u8* dst = mpBegin;
    FUN_011e0744(dst, begin, count);

    u8* p = dst + (end - begin);
    mpEnd = p;
    *p = 0;

    mKey0 = key[0];
    mKey1 = key[1];
    return this;
}
