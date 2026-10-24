// s00feb120 -- SP::cSPMissionManager / SP::cEmpireLayer and helpers.

#include <math.h>

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef signed int         i32;
typedef unsigned __int64   u64;
typedef unsigned int       uint;

#define MOPS(p) ((COps*)(p))

static inline void** vtbl(const void* p) { return *(void***)p; }

// ---------------------------------------------------------------------------
// callees that are plain (non-ecx) functions in the original binary
// ---------------------------------------------------------------------------
void* FUN_01046fc0();                                  // 0x01046fc0
void* FUN_01021300();                                  // 0x01021300
void* FUN_00ffbe50();                                  // 0x00ffbe50
void* MaterialManager();                               // 0x0067dd70
void* __stdcall FUN_01002bd0(u32 key);                 // 0x01002bd0
void* __stdcall FUN_00b3d3e0(u32 key, int unk);        // 0x00b3d3e0
void* __stdcall FUN_00b3d3f0(void* avatar);            // 0x00b3d3f0
void* __stdcall FUN_00b3d2a0(void* arg);               // 0x00b3d2a0
void* __stdcall FUN_01021230(void* box, void* vec);    // 0x01021230
i32   __cdecl   atexit(void (*fn)(void));              // 0x011e07ef
void  __cdecl   FUN_0093aa70(void* stream, u32* v, int n, int m); // 0x0093aa70
void  __cdecl   FUN_0093a9a0(void* stream, void* v, int n);       // 0x0093a9a0
i32   __cdecl   FUN_006dde90(int n, void** out, void* a, void* b); // 0x006dde90
void  __cdecl   FUN_006ddee0();                        // 0x006ddee0
void  __cdecl   FUN_006ddef0(void* mesh);              // 0x006ddef0
void  __cdecl   FUN_006dde30(int a, int b, void* mat); // 0x006dde30
u32*  __cdecl   FUN_00555a20(u32* begin, u32* end, u32* value, u8 flag); // 0x00555a20
void* __cdecl   memcpy(void* d, const void* s, unsigned int n);    // 0x011e0744
u32   FUN_01021090();                                  // 0x01021090
void  __stdcall FUN_00c47b10(u32 arg);                 // 0x00c47b10

// ---------------------------------------------------------------------------
// callees invoked with ecx == an object pointer
// ---------------------------------------------------------------------------
struct COps
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
    i32  FUN_00dd5d80();                   // 0x00dd5d80
    void FUN_00dd6d10();                   // 0x00dd6d10
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

// ---------------------------------------------------------------------------
// one entry of cSPMissionManager's mission-requisite vector (stride 0x38)
// ---------------------------------------------------------------------------
struct cMissionRequisite
{
    u32  pad00;                 // +0x00
    i32  mMinWeaponryLevel;     // +0x04
    u32* mSpeciesIDsBegin;      // +0x08
    u32* mSpeciesIDsEnd;        // +0x0c
    u32  pad10[10];             // +0x10 .. +0x37
};

// ---------------------------------------------------------------------------
// SP::cSPMissionManager (retail field offsets taken from the disassembly)
// ---------------------------------------------------------------------------
class cSPMissionManager
{
public:
    u8   pad00[0x14];                              // +0x00
    bool mDebugDraw;                               // +0x14
    u8   pad15[0x34 - 0x15];                       // +0x15
    cMissionRequisite* mNPCMissionReqBegin;        // +0x34
    cMissionRequisite* mNPCMissionReqEnd;          // +0x38
    u8   pad3c[0x48 - 0x3c];                       // +0x3c
    cMissionRequisite* mColonyMissionReqBegin;     // +0x48
    cMissionRequisite* mColonyMissionReqEnd;       // +0x4c
    u8   pad50[0x80 - 0x50];                       // +0x50
    u32* mTutorialSpeciesIDs;                      // +0x80
    u8   pad84[0xa8 - 0x84];                       // +0x84
    void** mSlots;                                 // +0xa8
    u8   padAc[0xbc - 0xac];                       // +0xac
    u32  mMissionTimer;                            // +0xbc
    void* mTrackedMission;                         // +0xc0
    void* mMostRecentMission;                      // +0xc4
    u8   mNPCMissionList[0xc];                     // +0xc8
    u8   mColonyMissionList[0xc];                  // +0xd4
    u8   padE0[0x04];                              // +0xe0
    u32  mNPCMissionTimeLimit;                     // +0xe4
    u32  mColonyMissionTimeLimit;                  // +0xe8

    void FUN_00feba50();
    void RemoveNewMissionAvailableEventLog();
    u8   Write(void* stream);
    u32  FUN_00febc70();
    u8   IsNPCMissionAvailable(void* empire, i32 index);
    u8   FUN_00febd30(i32 index);
    u32  FUN_00febdc0(u32 index);
    void FUN_00febde0(u32 index, u32 value);
    u8   FUN_00febe00(void* key);
    u8   FUN_00febe50(void* key, u32* out);
    u32  FUN_00febe90();
    void FUN_00febeb0(void* mission);
    void FUN_00febf20(void* mission);
    i32  FUN_00febf80(void* key);
    void FUN_00fec430(i32 delta);
    void FUN_00fec4e0();
};

// ---------------------------------------------------------------------------
// SP::cEmpireLayer
// ---------------------------------------------------------------------------
class cEmpireLayer
{
public:
    u8    pad0[0x04];                  // +0x00
    void* mpViewer;                    // +0x04

    void DrawEmpire(void* empire, void* mesh);
    void DrawLayer(void* arg1, u32 layer, u32* viewer, void* mesh);
};

// serialiser used by cSPMissionManager::Write, 0xa14 bytes
class cVarListSerializer
{
public:
    u32 pad[0x285];

    void FUN_00692f90(void* a, void* b, u32 c);   // 0x00692f90
    u8   FUN_00692900(void* stream);              // 0x00692900
};

// ===========================================================================
// 0x00feb120
// ===========================================================================
struct QuadVert
{
    float x, y, z;        // +0x00
    u32   color;          // +0x0c
    float uv0[2];         // +0x10
    float uv1[2];         // +0x18
    float uv2[2];         // +0x20
};

// @ 0x00feb120
void FUN_00feb120(void* mesh, void* civA, void* civB, float* dir, float t, u8 flags)
{
    float* pa = MOPS(civA)->FUN_005c65e0();
    float* pb = MOPS(civB)->FUN_005c65e0();

    float dx = pb[0] - pa[0];
    float dy = pb[1] - pa[1];
    float dz = pb[2] - pa[2];
    float length = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));

    u8 flagA = 0;
    if (MOPS(FUN_01046fc0())->FUN_01044bf0(civA) != 0)
    {
        if (flags == 0 && MOPS(civA)->FUN_00bb9c00() == 0 &&
            *(u8*)FUN_01046fc0() == 0)
            flagA = 0;
        else
            flagA = 0xff;
    }

    u8 flagB = 0;
    if (MOPS(FUN_01046fc0())->FUN_01044bf0(civB) != 0)
    {
        if (flags == 0 && MOPS(civB)->FUN_00bb9c00() == 0 &&
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

// ===========================================================================
// 0x00feba10
// ===========================================================================
// @ 0x00feba10
void cSPMissionManager::RemoveNewMissionAvailableEventLog()
{
    void* log = FUN_00b3d3e0(0xe737105a, 0);
    i32 id = MOPS(log)->FUN_00dd5d80();
    if (id != 0)
    {
        void* log2 = FUN_00b3d3e0(id, 0);
        MOPS(log2)->FUN_00dd6d10();
    }
}

// ===========================================================================
// 0x00feba50
// ===========================================================================
// @ 0x00feba50
void cSPMissionManager::FUN_00feba50()
{
    mDebugDraw = (mDebugDraw == 0);
}

// ===========================================================================
// 0x00febb90
// ===========================================================================
// @ 0x00febb90
u8 cSPMissionManager::Write(void* stream)
{
    void* a = (*(void* (__thiscall**)(void*))((char*)vtbl(stream) + 0x20))(stream);
    void* b = (*(void* (__thiscall**)(void*))((char*)vtbl(a) + 0x18))(a);
    u32 key = 0x2aa56c7;
    FUN_0093aa70(b, &key, 1, 0);
    cVarListSerializer ser;
    ser.FUN_00692f90((void*)((char*)this - 8), (void*)0x15b4b90, 0x1a80d26);
    return ser.FUN_00692900(stream);
}

// ===========================================================================
// 0x00febc70
// ===========================================================================
// @ 0x00febc70
u32 cSPMissionManager::FUN_00febc70()
{
    u32 r = (u32)mMostRecentMission;
    if (r == 0)
        r = (u32)mTrackedMission;
    return r;
}

// ===========================================================================
// 0x00febc90
// ===========================================================================
// @ 0x00febc90
u8 cSPMissionManager::IsNPCMissionAvailable(void* empire, i32 index)
{
    i32 count = (i32)(mNPCMissionReqEnd - mNPCMissionReqBegin);
    if (index >= count)
        return 0;

    cMissionRequisite* req = mNPCMissionReqBegin + index;
    i32 n = (i32)(req->mSpeciesIDsEnd - req->mSpeciesIDsBegin);
    for (i32 i = 0; i < n; i++)
    {
        u32 id = req->mSpeciesIDsBegin[i];
        void* noun = FUN_01002bd0(id);
        void* a = MOPS(noun)->FUN_00bfc5f0();
        u8 ok = MOPS(a)->FUN_00fe4180();
        if (!ok)
            return 0;
    }

    if (empire != 0)
    {
        if (empire != FUN_01021300())
        {
            i32 lvl = MOPS(empire)->FUN_00c317a0();
            if (lvl < req->mMinWeaponryLevel)
                return 0;
        }
    }
    return 1;
}

// ===========================================================================
// 0x00febd30
// ===========================================================================
// @ 0x00febd30
u8 cSPMissionManager::FUN_00febd30(i32 index)
{
    i32 count = (i32)(mColonyMissionReqEnd - mColonyMissionReqBegin);
    if (index >= count)
        return 0;

    cMissionRequisite* req = mColonyMissionReqBegin + index;
    i32 n = (i32)(req->mSpeciesIDsEnd - req->mSpeciesIDsBegin);
    for (i32 i = 0; i < n; i++)
    {
        u32 id = req->mSpeciesIDsBegin[i];
        void* noun = FUN_01002bd0(id);
        void* a = MOPS(noun)->FUN_00bfc5f0();
        u8 ok = MOPS(a)->FUN_00fe4180();
        if (!ok)
            return 0;
    }
    return 1;
}

// ===========================================================================
// 0x00febdc0
// ===========================================================================
// @ 0x00febdc0
u32 cSPMissionManager::FUN_00febdc0(u32 index)
{
    if (index < 2)
        return mTutorialSpeciesIDs[index];
    return 0;
}

// ===========================================================================
// 0x00febde0
// ===========================================================================
// @ 0x00febde0
void cSPMissionManager::FUN_00febde0(u32 index, u32 value)
{
    if (index < 2)
        mTutorialSpeciesIDs[index] = value;
}

// ===========================================================================
// 0x00febe00
// ===========================================================================
// @ 0x00febe00
u8 cSPMissionManager::FUN_00febe00(void* key)
{
    u32 i = 0;
    void** slot = mSlots;
    do
    {
        if (*slot == key)
        {
            FUN_00c47b10(0);
            void* p = mSlots[i];
            if (p != 0)
            {
                mSlots[i] = 0;
                (*(void (__thiscall**)(void*))((char*)vtbl(p) + 4))(p);
            }
            return 1;
        }
        i++;
        slot++;
    } while (i < 3);
    return 0;
}

// ===========================================================================
// 0x00febe50
// ===========================================================================
// @ 0x00febe50
u8 cSPMissionManager::FUN_00febe50(void* key, u32* out)
{
    u32 i = 0;
    void** slot = mSlots;
    do
    {
        if (*slot == key)
        {
            if (out != 0)
                *out = ((u32*)0x16dac54)[i];
            return 1;
        }
        i++;
        slot++;
    } while (i < 3);
    return 0;
}

// ===========================================================================
// 0x00febe90
// ===========================================================================
// @ 0x00febe90
u32 cSPMissionManager::FUN_00febe90()
{
    void** slot = mSlots;
    u32 n = 0;
    if (slot[0] != 0)
        n = 1;
    if (slot[1] != 0)
        n = n + 1;
    if (slot[2] != 0)
        n = n + 1;
    return n;
}

// ===========================================================================
// 0x00febeb0
// ===========================================================================
// @ 0x00febeb0
void cSPMissionManager::FUN_00febeb0(void* mission)
{
    void* old = mTrackedMission;
    if (old != mission)
    {
        if (mission != old)
        {
            if (mission != 0)
                (*(void (__thiscall**)(void*))vtbl(mission))(mission);
            mTrackedMission = mission;
            if (old != 0)
                (*(void (__thiscall**)(void*))((char*)vtbl(old) + 4))(old);
        }
        if (old != 0)
            MOPS(old)->FUN_00c47d80();
        if (mTrackedMission != 0)
            MOPS(mTrackedMission)->FUN_00c47d80();
        mMissionTimer = 0;
    }
}

// ===========================================================================
// 0x00febf20
// ===========================================================================
// @ 0x00febf20
void cSPMissionManager::FUN_00febf20(void* mission)
{
    void* old = mMostRecentMission;
    if (old != mission)
    {
        if (mission != old)
        {
            if (mission != 0)
                (*(void (__thiscall**)(void*))vtbl(mission))(mission);
            mMostRecentMission = mission;
            if (old != 0)
                (*(void (__thiscall**)(void*))((char*)vtbl(old) + 4))(old);
        }
        if (old != 0)
            MOPS(old)->FUN_00c47d80();
        if (mMostRecentMission != 0)
            MOPS(mMostRecentMission)->FUN_00c47d80();
    }
}

// ===========================================================================
// 0x00febf80
// ===========================================================================
// @ 0x00febf80
i32 cSPMissionManager::FUN_00febf80(void* key)
{
    u32 i = 0;
    void** slot = mSlots;
    do
    {
        if (*slot == key)
            return (i32)((u32*)0x16dac54)[i];
        i++;
        slot++;
    } while (i < 3);
    return -1;
}

// ===========================================================================
// 0x00febfd0
// ===========================================================================
// @ 0x00febfd0
u8 FUN_00febfd0(void* self, u32* list)
{
    for (u32* p = (u32*)*list; p != list; p = (u32*)*p)
    {
        if (p + 2 != 0)
            MOPS(self)->FUN_00695b40(p + 2, (void*)0x15b49b0, (void*)0x14948dc);
    }
    return 1;
}

// ===========================================================================
// 0x00fec010
// ===========================================================================
// @ 0x00fec010
i32 FUN_00fec010(int* v)
{
    double sum = 0.0;
    float* p = (float*)v[0];
    float* end = (float*)v[1];
    if (p != end)
    {
        do
        {
            sum += *p;
            p++;
        } while (p != end);

        if (0.0 < sum)
        {
            double r = MOPS((void*)0x1601760)->FUN_009360d0() * sum;
            if (r < sum)
            {
                double acc = 0.0;
                i32 i = 0;
                for (float* q = (float*)v[0]; q != (float*)v[1]; q++)
                {
                    acc += *q;
                    if (r < acc)
                        return i;
                    i++;
                }
            }
            return (((i32)v[1] - (i32)v[0]) >> 2) - 1;
        }
    }
    return ((i32)v[1] - (i32)v[0]) >> 2;
}

// ===========================================================================
// 0x00fec3c0
// ===========================================================================
// @ 0x00fec3c0
void* FUN_00fec3c0(void* obj, u8* value)
{
    u32 one = 1;
    void* a = (*(void* (__thiscall**)(void*))((char*)vtbl(obj) + 0x20))(obj);
    void* b = (*(void* (__thiscall**)(void*))((char*)vtbl(a) + 0x18))(a);
    FUN_0093aa70(b, &one, 1, 0);

    u8 flag = (u8)(*value & 1);
    void* c = (*(void* (__thiscall**)(void*))((char*)vtbl(obj) + 0x20))(obj);
    void* d = (*(void* (__thiscall**)(void*))((char*)vtbl(c) + 0x18))(c);
    bool bv = flag != 0;
    FUN_0093a9a0(d, &bv, 1);
    return obj;
}

// ===========================================================================
// 0x00fec430
// ===========================================================================
// @ 0x00fec430
void cSPMissionManager::FUN_00fec430(i32 delta)
{
    if (mMostRecentMission != 0)
    {
        void* p = mTrackedMission;
        if (p != 0)
        {
            if (p != 0)
            {
                mTrackedMission = 0;
                (*(void (__thiscall**)(void*))((char*)vtbl(p) + 4))(p);
                MOPS(p)->FUN_00c47d80();
            }
            if (mTrackedMission != 0)
                MOPS(mTrackedMission)->FUN_00c47d80();
            mMissionTimer = 0;
        }
    }

    void* q = mTrackedMission;
    if (q != 0)
    {
        mMissionTimer = mMissionTimer + (u32)delta;
        if (mMissionTimer >= 0x2710)
        {
            if (q != 0)
            {
                mTrackedMission = 0;
                (*(void (__thiscall**)(void*))((char*)vtbl(q) + 4))(q);
                MOPS(q)->FUN_00c47d80();
            }
            if (mTrackedMission != 0)
                MOPS(mTrackedMission)->FUN_00c47d80();
            mMissionTimer = 0;
        }
    }
}

// ===========================================================================
// 0x00fec4e0
// ===========================================================================
// @ 0x00fec4e0
void cSPMissionManager::FUN_00fec4e0()
{
    u8* head = (u8*)&mNPCMissionList;
    u8* n = *(u8**)head;
    while (n != (u8*)&mNPCMissionList)
    {
        if ((u8*)n + 8 != 0)
        {
            void* timer = (u8*)n + 0x10;
            if (MOPS(timer)->FUN_00feba90())
            {
                u64 elapsed = MOPS(timer)->FUN_00bc3190();
                if (elapsed > (u64)mNPCMissionTimeLimit)
                    MOPS(timer)->FUN_00bc3110();
            }
        }
        n = *(u8**)n;
    }

    u8* n2 = *(u8**)&mColonyMissionList;
    while (n2 != (u8*)&mColonyMissionList)
    {
        if ((u8*)n2 + 8 != 0)
        {
            void* timer = (u8*)n2 + 0x10;
            if (MOPS(timer)->FUN_00feba90())
            {
                u64 elapsed = MOPS(timer)->FUN_00bc3190();
                if (elapsed > (u64)mColonyMissionTimeLimit)
                    MOPS(timer)->FUN_00bc3110();
            }
        }
        n2 = *(u8**)n2;
    }
}

// ===========================================================================
// 0x00feb510  SP::cEmpireLayer::DrawEmpire
// ===========================================================================
// @ 0x00feb510
void cEmpireLayer::DrawEmpire(void* empire, void* mesh)
{
    void** stars = (void**)MOPS(empire)->FUN_00c308d0();
    void** other = (void**)MOPS(empire)->FUN_00bef6c0();
    i32 count = ((char*)stars[1] - (char*)stars[0]) >> 2;
    bool drew = false;

    if (MOPS(empire)->FUN_00c31c50() != 0)
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
        MOPS(mpViewer)->FUN_007c3d30(posA, posB, 0, 0);

    double len2 = (double)posB[2] * posB[2] +
                  ((double)posB[1] * posB[1] + (double)posB[0] * posB[0]);
    float inv = (float)(1.0 / sqrt(len2 + 1e-08));
    dir[0] = inv * posB[0];
    dir[1] = inv * posB[1];
    dir[2] = inv * posB[2];

    void* playerEmpire = FUN_01021300();
    u8 colorEnabled = MOPS(playerEmpire)->FUN_00c31bc0();

    void* mat = (*(void* (__thiscall**)(u32, void*))((char*)vtbl(MaterialManager()) + 0x28))(0x71f30f82, empire);

    for (i32 i = 0; i < count; i++)
    {
        i32 a = ((i32*)stars[0])[i];
        i32 b = ((i32*)other[0])[i];
        if (a == 0 || b == 0 || a == b)
            continue;

        if (MOPS((void*)a)->FUN_00bb9c00() == 0 &&
            MOPS((void*)b)->FUN_00bb9c00() == 0 &&
            *(u8*)FUN_01046fc0() == 0 &&
            colorEnabled == 0)
            continue;

        if (!drew)
        {
            float color[3];
            MOPS(empire)->FUN_00c32cd0(color);
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

// ===========================================================================
// 0x00feb770  SP::cEmpireLayer::DrawLayer
// ===========================================================================
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

// @ 0x00feb770
void cEmpireLayer::DrawLayer(void* arg1, u32 layer, u32* viewer, void* mesh)
{
    if (layer != 0x17)
        return;

    MOPS(mpViewer)->FUN_007c50b0((void*)*viewer, 0, 0);
    if (!MOPS(mpViewer)->FUN_007c4fd0())
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
    box.e = MOPS(FUN_00ffbe50())->FUN_00ffbfd0();

    MOPS((void*)0x16dabfc)->FUN_00e25bd0((void*)*(u32*)0x16dac00,
                                         (void*)*(u32*)0x16dabfc);

    void* rec = FUN_01021230(&box, (void*)0x16dabfc);
    void* r2 = MOPS(rec)->FUN_00c8b360();
    void* sm = FUN_00b3d2a0(r2);
    MOPS(sm)->FUN_00bb1080();

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
        u32 avatar = MOPS(entry)->FUN_00b1fdb0();
        u8 flag = *(u8*)0x16dabf8;

        u32* pos = FUN_00555a20(*(u32**)0x16dabe4, *(u32**)0x16dabe8, &avatar, flag);
        if (pos == *(u32**)0x16dabe8)
        {
            if (pos == *(u32**)0x16dabec)
            {
                MOPS((void*)0x16dabe4)->FUN_005481d0(pos, &avatar);
            }
            else
            {
                *(u32**)0x16dabe8 = pos + 1;
                *pos = avatar;
            }
        }
        else if (avatar < *pos)
        {
            MOPS((void*)0x16dabe4)->FUN_005481d0(pos, &avatar);
        }
    }

    i32 n = ((i32)*(u32*)0x16dabe8 - (i32)*(u32*)0x16dabe4) >> 2;
    for (i32 i = 0; i < n; i++)
    {
        u32 id = (*(u32**)0x16dabe4)[i];
        void* star = FUN_00b3d2a0((void*)id);
        void* emp = (void*)MOPS(star)->FUN_00ba9370();

        FUN_01021090();

        bool draw = false;
        if (MOPS(FUN_01046fc0())->FUN_010449e0(1) != 0)
            draw = true;
        else if (MOPS(FUN_01046fc0())->FUN_010449e0(id) != 0 &&
                 FUN_01021300() == emp)
            draw = true;

        if (draw)
        {
            if (MOPS(FUN_00b3d3f0((void*)id))->FUN_00e18c70() == 0)
                DrawEmpire(emp, mesh);
        }
    }

    MOPS(mpViewer)->FUN_007c3c10();
}
