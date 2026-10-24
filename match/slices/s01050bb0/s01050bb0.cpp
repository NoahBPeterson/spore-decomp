// Slice s01050bb0: the SP::cSPToolManager tool-use entry points - PlayerUseToolStart,
// PlayerUseToolUpdate and GetRandomDiscoverableTool.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

struct Vec3 { float x, y, z; };
struct Key3 { uint32_t a, b, c; };

#define VFN(obj, off) (*(void**)((char*)(*(void**)obj) + (off)))

// ---------------------------------------------------------------------------------------------
// free / cdecl helpers
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl FUN_01021300(void);                 // 0x01021300  cSPLivingUniverse::GetPlayerEmpire
extern "C" void* __cdecl FUN_00ffbe50(void);                 // 0x00ffbe50  GetUFOSimulator
extern "C" void* __cdecl FUN_00b3d390(void);                 // 0x00b3d390  palette/property manager getter
extern "C" void* __cdecl FUN_01021080(void);                 // 0x01021080  cSPLivingUniverse::GetUniverseContext
extern "C" void* __cdecl FUN_01021260(void);                 // 0x01021260  GetActivePlanet
extern "C" void* __cdecl FUN_00b3d300(void);                 // 0x00b3d300  NounManager
extern "C" void* __cdecl FUN_0067de30(void);                 // 0x0067de30  PropertyManager
extern "C" void* __cdecl FUN_01002bd0(void);                 // 0x01002bd0  SpaceGameGet
extern "C" int   __cdecl FUN_004eb930(const void* a, const void* b);                 // 0x004eb930
extern "C" int   __cdecl FUN_0102aec0(void* pTool, float* pA, float* pB);            // 0x0102aec0  IsNearbyObject
extern "C" int   __cdecl FUN_010527f0(void* pTool, uint32_t id, int flag);           // 0x010527f0  SetErrorEvent
extern "C" void  __cdecl FUN_0104e060(void* pOut, float, float, float, float);       // 0x0104e060  ComputeToolEffectPosition
extern "C" void  __cdecl FUN_01051320(uint32_t n);                                   // 0x01051320
extern "C" void  __cdecl FUN_006a12a0(uint32_t a, uint32_t b, void* out);            // 0x006a12a0  GetPropertyAsKeyInstance
extern "C" void  __cdecl FUN_004e19a0(void* vec, void* v);                           // 0x004e19a0  SpVector::push_back

// global RandomLinearCongruential instance shared by the EA random helpers
extern uint8_t g_RandomLCG;                                  // 0x01601760

// ---------------------------------------------------------------------------------------------
// thiscall callees, declared as members of a host class so `this` travels in ecx
// ---------------------------------------------------------------------------------------------
class tHost {
public:
    void*    __thiscall FUN_00a1ad60();                            // 0x00a1ad60  cSPSimulatorSpaceGame::GetPlayerInventory
    uint32_t __thiscall FUN_00c30cb0();                            // 0x00c30cb0  [ecx+0xd0]
    uint32_t __thiscall FUN_00ffc2d0();                            // 0x00ffc2d0  [ecx+0xd8]
    void*    __thiscall FUN_0104f850(uint32_t key);                // 0x0104f850
    uint32_t __thiscall FUN_0104bff0();                            // 0x0104bff0  tool flag query
    uint32_t __thiscall FUN_01050020();                            // 0x01050020  cSPSpaceToolData::GetUseCost
    int      __thiscall FUN_0104cb70();                            // 0x0104cb70  cSPSpaceToolData::IsInContext
    uint8_t  __thiscall FUN_00feba90();                            // 0x00feba90  cSPTimer::IsRunning
    bool     __thiscall FUN_00c37170();                            // 0x00c37170  empire bool query
    void     __thiscall FUN_0083f660();                            // 0x0083f660  byte[ecx+0x28] = 1
    void     __thiscall FUN_00ffc0a0();                            // 0x00ffc0a0  ++dword[ecx+0x24]
    void*    __thiscall FUN_00f67d90();                            // 0x00f67d90  cTerrainEditor::GetCurrentTerrainSphere
    void*    __thiscall FUN_008414c0();                            // 0x008414c0  [ecx+0x154]
    void     __thiscall FUN_00c7e2f0(uint8_t b);                   // 0x00c7e2f0
    void     __thiscall FUN_00c75640();                            // 0x00c75640  cSPTimer::Stop(ecx+0x1258)
    void*    __thiscall FUN_01050070(void* pTool, void* pSub, Vec3* pPos, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x01050070 UseToolStart
    uint32_t __thiscall FUN_010504a0(void* pTool, Vec3* pPos, int flag, uint32_t d);   // 0x010504a0 UseToolUpdate
    void     __thiscall FUN_0104fa90(void* pTool);                 // 0x0104fa90 UseToolStop
    void*    __thiscall FUN_01051c30();                            // 0x01051c30  RandDoubleUniform thunk
    double   __thiscall FUN_009360d0();                            // 0x009360d0  RandomDoubleUniform
    uint32_t __thiscall FUN_00a68fb0(uint32_t n);                  // 0x00a68fb0  RandomUint32Uniform
};

// ---------------------------------------------------------------------------------------------
// data globals (tool / property keys)
// ---------------------------------------------------------------------------------------------
extern Key3 DAT_016e1440;                                     // 0x016e1440  kTool_planetbusterbomb
extern Key3 DAT_016e1734;                                     // 0x016e1734  kTool_portal
extern Key3 DAT_016e138c;                                     // 0x016e138c  kTool_placecolony
extern Key3 DAT_016e1554;                                     // 0x016e1554  kTool_CreatureEdit
extern Key3 DAT_016e15c0;                                     // 0x016e15c0  kTool_zoo
extern Key3 DAT_016e12d8;                                     // 0x016e12d8  kDefaultResult

// ---------------------------------------------------------------------------------------------
// cSPSpaceToolData - the tool the player is using
// ---------------------------------------------------------------------------------------------
class cSPToolData {
public:
    uint8_t  mPad000[0x80];    // +0x000
    uint8_t  m080;             // +0x080  mnPriority / auto-handler flag
    uint8_t  mPad081[0x97];    // +0x081
    void*    m118;             // +0x118  charge visual effect object
    uint8_t  mPad11c[0x2c];    // +0x11c
    float    m148;             // +0x148  mDamageMultiplier
    uint8_t  mPad14c[0x28];    // +0x14c
    uint32_t m174;             // +0x174  mStrategyClassID
    uint32_t m178;             // +0x178  mToolType
    uint32_t m17c;             // +0x17c  mWeaponSubtype
    uint8_t  mPad180[0x24];    // +0x180
    uint32_t m1a4;             // +0x1a4  mEnergyCost
    float    m1a8;             // +0x1a8  mDamageArea
    uint8_t  mPad1ac[0x20];    // +0x1ac
    float    m1cc;             // +0x1cc  mDamageRadius
    uint8_t  mPad1d0[0x84];    // +0x1d0
    uint32_t m254;             // +0x254  tool flags
};

// the player inventory / space-game object returned by GetPlayerInventory
struct cSpaceGame {
    uint8_t  mPad000[0x18];    // +0x000
    uint8_t  m18;              // +0x018
    uint8_t  mPad019[7];       // +0x019
    uint8_t  m20;              // +0x020
    uint8_t  mPad021[3];       // +0x021
    uint32_t m24;              // +0x024
    uint8_t  mPad028[0x0c];    // +0x028
    uint8_t  mSub34[0x0c];     // +0x034  subobject (vtable)
    uint8_t  mPad040[0x7b4];   // +0x040
    float    m7f4;             // +0x7f4
};

// opaque cursor/property accessor used by the random-tool query
union cAccessor {
    struct { uint32_t m00, m04, m08, m0c; uint16_t m10; int16_t m12; };
    void* mpFirst;
};

// ---------------------------------------------------------------------------------------------
class cSPToolManager {
public:
    uint32_t __thiscall PlayerUseToolStart(cSPToolData* pTool, float* pPos, uint32_t p3);
    uint8_t  __thiscall PlayerUseToolUpdate(cSPToolData* pTool, float* pPos, uint32_t p3);
    Key3*    __thiscall GetRandomDiscoverableTool(Key3* pOut);
};

// =============================================================================================
// 0x01050bb0
// =============================================================================================
// @ 0x01050bb0
uint32_t __thiscall cSPToolManager::PlayerUseToolStart(cSPToolData* pTool, float* pPos, uint32_t p3)
{
    void* pEmpire = FUN_01021300();
    if (pEmpire == 0) return 0;
    cSpaceGame* pInv = (cSpaceGame*)((tHost*)FUN_00ffbe50())->FUN_00a1ad60();

    uint32_t toolType = pTool->m178;
    void* pr;
    if (toolType == 0) {
        pr = ((tHost*)FUN_00b3d390())->FUN_0104f850(0xb0da49d9u);
    } else {
        pr = ((tHost*)FUN_00b3d390())->FUN_0104f850(toolType);
        if (pr == 0) pr = ((tHost*)FUN_00b3d390())->FUN_0104f850(0xb0da49d9u);
    }

    uint32_t cost = ((uint32_t(__thiscall*)(void*, uint32_t))VFN(pr, 0x44))(pr, pTool->m1a4);
    uint32_t have = ((tHost*)pEmpire)->FUN_00c30cb0();
    if (have < cost) goto FAIL;
    if (pInv->m7f4 < pTool->m1a8) goto FAIL;

    Vec3 pos;
    pos.x = pPos[0];
    pos.y = pPos[1];
    pos.z = pPos[2];

  {
    uint32_t u9, u12, u14;
    void* pObj;
    if ((pTool->m174 >> 0x10) & 1) {
        pObj = (void*)((tHost*)FUN_00ffbe50())->FUN_00ffc2d0();
    } else {
        pObj = (void*)((tHost*)FUN_00ffbe50())->FUN_00c30cb0();
    }

    if (pObj == 0) {
        u14 = 0; u12 = 0; u9 = 0xffffffff;
    } else {
        if (FUN_01021080() == 0) {
            void* v = ((void*(__thiscall*)(void*))VFN(pObj, 8))(pObj);
            float* pf = (float*)((void*(__thiscall*)(void*, Vec3*))VFN(v, 0x6c))(v, &pos);
            float x = (pf[0] + pf[3]) * 0.5f;
            float y = (pf[4] + pf[1]) * 0.5f;
            float z = (pf[5] + pf[2]) * 0.5f;
            pos.x = x; pos.y = y; pos.z = z;
        } else {
            void* v = ((void*(__thiscall*)(void*))VFN(pObj, 8))(pObj);
            float* pf = (float*)((void*(__thiscall*)(void*))VFN(v, 0x2c))(v);
            pos.x = pf[0]; pos.y = pf[1]; pos.z = pf[2];
        }

        if ((pTool->m174 >> 2) & 1) {
            void* r = ((void*(__thiscall*)(void*, uint32_t))VFN(pObj, 8))(pObj, p3);
            u14 = ((uint32_t(__thiscall*)(void*, uint32_t))VFN(pObj, 0x24))(pObj, 0);
            u12 = 0;
            u9  = (uint32_t)r;
        } else {
            u14 = 0; u12 = 0; u9 = 0xffffffff;
        }
    }

    ((tHost*)this)->FUN_01050070(pTool, pInv->mSub34, &pos, u9, u12, u14, p3);
  }

    {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (k->a == DAT_016e1440.a && k->b == DAT_016e1440.b && k->c == DAT_016e1440.c) goto L_ed0;
        k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (k->a == DAT_016e1734.a && k->b == DAT_016e1734.b && k->c == DAT_016e1734.c) goto L_ed0;
        if (FUN_004eb930(((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool), &DAT_016e15c0)) goto L_ed0;
        if (FUN_004eb930(((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool), &DAT_016e138c)) goto L_ed0;
        if (FUN_004eb930(((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool), &DAT_016e1554)) goto L_ed0;
        goto L_ed9;
      L_ed0:
        ((cSpaceGame*)FUN_00ffbe50())->m18 = 1;
      L_ed9:
        ;
    }

    {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (k->a == DAT_016e1734.a && k->b == DAT_016e1734.b && k->c == DAT_016e1734.c) {
            ((cSpaceGame*)FUN_00ffbe50())->m20 = 1;
        }
    }

    {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (!(k->a == DAT_016e1440.a && k->b == DAT_016e1440.b && k->c == DAT_016e1440.c)) {
            k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
            if (!(k->a == DAT_016e1554.a && k->b == DAT_016e1554.b && k->c == DAT_016e1554.c)) {
                if (!FUN_004eb930(((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool), &DAT_016e1734))
                    goto L_f84;
            }
        }
        ((tHost*)FUN_00ffbe50())->FUN_00ffc0a0();
    }

  L_f84:
    {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (k->a == DAT_016e1440.a && k->b == DAT_016e1440.b && k->c == DAT_016e1440.c) {
            ((tHost*)FUN_00ffbe50())->FUN_0083f660();
        }
    }

    if (pTool->m17c == 0xe810d505u) {
        void* pTerrain = ((tHost*)FUN_00b3d300())->FUN_00f67d90();
        ((tHost*)pTerrain)->FUN_00c75640();
    }

    if (pTool->m17c == 0x293e3f3du) {
        Key3* k = ((Key3*(__thiscall*)(void*))VFN(pTool, 0x18))(pTool);
        if (!(k->a == DAT_016e138c.a && k->b == DAT_016e138c.b && k->c == DAT_016e138c.c)) {
            void* pPlanet = FUN_01021260();
            if (pPlanet != 0) {
                void* p154 = ((tHost*)pPlanet)->FUN_008414c0();
                if (p154 != 0) ((tHost*)p154)->FUN_00c7e2f0(1);
            }
        }
    }

    return 1;

  FAIL:
    have = ((tHost*)pEmpire)->FUN_00c30cb0();
    cost = ((tHost*)pTool)->FUN_01050020();
    if (have < cost) FUN_010527f0(pTool, 0x1999ea5fu, 1);
    if (pTool->m1a8 > pInv->m7f4) FUN_010527f0(pTool, 0xf04aa52au, 1);
    return 0;
}

// =============================================================================================
// 0x01051090
// =============================================================================================
// @ 0x01051090
uint8_t __thiscall cSPToolManager::PlayerUseToolUpdate(cSPToolData* pTool, float* pPos, uint32_t p3)
{
    uint8_t result = 0;

    if (pTool == 0) return result;

    if (pTool->m080 == 0 && ((tHost*)((char*)pTool + 0xc8))->FUN_00feba90() == 0)
        return result;

    void* pEmpire = FUN_01021300();
    if (pEmpire == 0) return result;

    if (((tHost*)pTool)->FUN_0104cb70() != 0) {
        uint32_t have = ((tHost*)pEmpire)->FUN_00c30cb0();
        uint32_t cost = ((tHost*)pTool)->FUN_01050020();
        if (cost <= have) {
            cSpaceGame* pInv = (cSpaceGame*)((tHost*)FUN_00ffbe50())->FUN_00a1ad60();
            if (pTool->m1a8 <= pInv->m7f4) {
                cSpaceGame* pInv2 = (cSpaceGame*)((tHost*)FUN_00ffbe50())->FUN_00a1ad60();
                if (((tHost*)pInv2)->FUN_00c37170() != 0) {
                    Vec3 pos;
                    pos.x = pPos[0]; pos.y = pPos[1]; pos.z = pPos[2];

                    void* pObj;
                    if ((pTool->m174 & 0x10000) == 0) {
                        pObj = (void*)((tHost*)FUN_00ffbe50())->FUN_00c30cb0();
                    } else {
                        pObj = (void*)((tHost*)FUN_00ffbe50())->FUN_00ffc2d0();
                    }

                    if (pObj != 0) {
                        void* v = ((void*(__thiscall*)(void*))VFN(pObj, 8))(pObj);
                        float* pf = (float*)((void*(__thiscall*)(void*, Vec3*))VFN(v, 0x6c))(v, &pos);
                        pos.z = (pf[0] + pf[3]) * 0.5f;
                        pos.x = (pf[4] + pf[1]) * 0.5f;
                        pos.y = (pf[5] + pf[2]) * 0.5f;
                        result = (uint8_t)((tHost*)this)->FUN_010504a0(pTool, &pos, 0xffffffff, p3);
                        return result;
                    }

                    if (pTool->m118 != 0) {
                        void* pEff = pTool->m118;
                        pTool->m118 = 0;
                        ((void(__thiscall*)(void*))VFN(pEff, 0xc0))(pEff);
                    }

                    cSpaceGame* pInv2 = (cSpaceGame*)((tHost*)FUN_00ffbe50())->FUN_00a1ad60();
                    float* q = (float*)((void*(__thiscall*)(void*))VFN(pInv2->mSub34, 0x2c))(pInv2->mSub34);
                    if (FUN_0102aec0(pTool, q, (float*)&pos) == 0) {
                        result = (uint8_t)((tHost*)this)->FUN_010504a0(pTool, &pos, 0xffffffff, p3);
                        return result;
                    }

                    if (((tHost*)pTool)->FUN_0104bff0() != 0) {
                        float* pf2 = (float*)((void*(__thiscall*)(void*))VFN(pInv2->mSub34, 0x2c))(pInv2->mSub34);
                        FUN_0104e060(&pos, pf2[0], pf2[1], pf2[2], pTool->m1cc * pTool->m148);
                        result = (uint8_t)((tHost*)this)->FUN_010504a0(pTool, &pos, 0xffffffff, p3);
                        return result;
                    }
                }
            }
        }
    }

    ((tHost*)this)->FUN_0104fa90(pTool);
    return result;
}

// =============================================================================================
// 0x010513a0
// =============================================================================================
// @ 0x010513a0
Key3* __thiscall cSPToolManager::GetRandomDiscoverableTool(Key3* pOut)
{
    uint8_t qbuf[0x20];

    void* pPM = FUN_0067de30();

    ((void(__thiscall*)(void*, uint32_t, uint32_t, void*))VFN(pPM, 0x2c))(pPM, 0x59252ee9u, 0x30608f0bu, qbuf);

    cAccessor* pAcc = (cAccessor*)((void*(__thiscall*)(void*, uint32_t))VFN(pPM, 0x28))(pPM, 0x2e06eceu);

    int count;
    if ((pAcc->m10 & 0x30) == 0) {
        if (pAcc->m12 == 0) goto DEFAULT;
        count = 1;
    } else {
        count = (int)pAcc->m08;
        if (count < 1) goto DEFAULT;
    }

    if ((pAcc->m10 & 0x30) == 0)
        pAcc = (pAcc->m12 != 0) ? pAcc : 0;
    else
        pAcc = (cAccessor*)pAcc->mpFirst;

    {
        void* vecCand = 0;
        uint32_t vecN = 0;
        FUN_01051320(4);

        Key3* pIt = (Key3*)pAcc;
        int n = count;
        if (n > 0) {
            do {
                void* pm2 = FUN_0067de30();
                uint8_t q2[0x20];
                ((void(__thiscall*)(void*, uint32_t, uint32_t, void*))VFN(pm2, 0x2c))(pm2, pIt->a, 0x30608f0bu, q2);

                void* sg = FUN_01002bd0();
                void* inv = ((tHost*)sg)->FUN_00a1ad60();
                uint32_t l2[2];
                l2[0] = 0; l2[1] = 0;
                uint8_t okB = ((uint8_t(__thiscall*)(void*, void*))VFN(inv, 0x74))(inv, l2);
                if (okB == 0) {
                    FUN_006a12a0(0, 0x370040au, l2);
                    Key3 d;
                    d.a = pIt->a; d.b = 0; d.c = 0;
                    FUN_004e19a0(&vecCand, &vecN);
                    (void)d;
                }
                pIt++;
                n--;
            } while (n != 0);
            (void)vecCand;
        }
    }

    {
        float w[4];
        w[0] = 0.0f; w[1] = 0.0f; w[2] = 0.0f; w[3] = 0.0f;

        float total = 0.0f;
        int i;
        for (i = 0; i < 4; i++) {
            total += w[i];
        }

        double r = ((tHost*)&g_RandomLCG)->FUN_009360d0() * (double)total;
        float target = (float)r;
        if (target < 0.0f) target = 0.0f;

        float acc = 0.0f;
        for (i = 0; i < 4; i++) {
            acc += w[i];
            if (w[i] > 0.0f && target <= acc) {
                uint32_t pick = ((tHost*)&g_RandomLCG)->FUN_00a68fb0(1);
                (void)pick;
                Key3 v;
                v.a = DAT_016e12d8.a; v.b = DAT_016e12d8.b; v.c = DAT_016e12d8.c;
                pOut->a = v.a; pOut->b = v.b; pOut->c = v.c;
                return pOut;
            }
        }
    }

  DEFAULT:
    pOut->a = DAT_016e12d8.a;
    pOut->b = DAT_016e12d8.b;
    pOut->c = DAT_016e12d8.c;
    return pOut;
}