// Slice s00e8ffa0: SP::cMineralView::HandleSimulationUpdate (0x00E8FFA0, 2168 bytes,
// __thiscall, ret 8).  Per-step update of a spice-geyser (commodity node) view: pick and tint
// the geyser icon effects, refresh the three loyalty meters, drive the mine-state effects
// (construct / capture / convert), and the ambient "hot spot" effect.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- (MSVC 2008 SP1).
//
// Virtual calls on objects whose class is not recovered use VCn(ret, obj, byteoffset, ...).

#include <float.h>
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;

#define VS(o, off)              (*(void**)(*(char**)(o) + (off)))
#define VC0(R, o, off)          ((R (__thiscall*)(void*))VS(o, off))((void*)(o))
#define VC1(R, o, off, T1, a1)  ((R (__thiscall*)(void*, T1))VS(o, off))((void*)(o), (a1))
#define VC5(R, o, off, T1, a1, T2, a2, T3, a3, T4, a4, T5, a5) \
    ((R (__thiscall*)(void*, T1, T2, T3, T4, T5))VS(o, off))((void*)(o), (a1), (a2), (a3), (a4), (a5))

struct Vec3 { float x, y, z; };

// Transform message sent to swarm effects (size 0x38).
struct XformMsg {
    u16   flags;      // +0x00  |2 = rotation, |4 = position
    u16   count;      // +0x02
    float pos[3];     // +0x04
    float scale;      // +0x10
    float rot[9];     // +0x14
    XformMsg();                           // 0x00434040
};

// The simulation object behind the view (view->mpObject, a cCommodityNode).  Effect helpers.
struct cSpatialObject {
    bool  GetEffect(int id);                          // 0x00c88910
    void* FindEffect(int id);                         // 0x00c888e0
    void  SetEffectParam(int id, float f);            // 0x00c88a00
    void  SetEffectPos(int id, void* p);              // 0x00c88a30
    void  KillEffect(int id, int flag);               // 0x00c8ad30
    void  CreateEffect(int effId, int p3, int id);    // 0x00c8b130
    void  CreateEffectB(int effId, int p3, int id);   // 0x00c8b1b0
    void  sub_a020(int id, float f);                  // 0x00c8a020
};

struct cPlanetModel {
    char  pad[0x64];
    u8*   mpTable;                                    // +0x64 per-cell flag table
    bool  sub_b7e3e0(const Vec3* pos);                // 0x00b7e3e0 (thiscall, ret 4)
    int   GetContinent(const Vec3* pos);              // 0x00b88590 (thiscall, ret 4): cell index
    void* BuildSurfaceOrientation(void* out, const Vec3* pos);   // 0x00b7f190 (ret 8)
};

// The commodity node's per-step record (view-side render state).
struct cFxRecord {
    u32   pad0;
    u32   mFlags;       // +0x04
    char  pad1[0x4c - 8];
    float mColor[3];    // +0x4c
};

struct cCommodityNode {
    cFxRecord* GetFxRecord();     // 0x009600f0: returns field at +0x1dc
    float      GetResourceFraction();   // 0x00bfdea0: fld [ecx+0x1d0]; fdiv [ecx+0x1d4]
    bool       sub_bfe0c0();      // 0x00bfe0c0
};

struct cGameNounManager {
    char* GetObject(int id);                          // 0x00b25f40 (thiscall, ret 4)
};

struct cGonzagoWorld {};

struct cSPUIMeter_e8ff {};   // vtbl slot 0 = AddRef, slot 1 = Release

int                GetCurrentGameMode();               // 0x00b5b800
cPlanetModel*      PlanetModel();                      // 0x00b3d350
cGameNounManager*  NounManager();                      // 0x00b3d300
void*              GetUniverseGlobal();                // 0x00b3d460
void*              GonzagoModelWorld();                // 0x00b3d520
char*              GetActivePlanet();                  // 0x01021260
u32                SPIDFromName(const char* name);     // 0x00571cf0
float*             Matrix3FromQuaternion(float* out, void* q);   // 0x0059c190
bool               Vector3_NotEqual(const Vec3* a, const Vec3* b);   // 0x0041dd30
extern const u32   kGeyserEffectIds[];                 // 0x014868b0

namespace SP {

class cMineralView {
public:
    void** mVTable;                                   // +0x00
    char   pad0[8];
    cSpatialObject* mpObject;                         // +0x0c
    char   pad1[0x18 - 0x10];
    Vec3   mColor;                                    // +0x18
    char   pad2[0x34 - 0x24];
    int    mEffectMode;                               // +0x34
    u8     mShieldFxOn;                               // +0x38
    char   mLastFlag;                               // +0x39
    u8     mHotSpotFxOn;                              // +0x3a
    char   pad3;
    cSPUIMeter_e8ff* mpConstructionMeter;             // +0x3c
    cSPUIMeter_e8ff* mpCulturalMeter;                 // +0x40
    cSPUIMeter_e8ff* mpMilitaryMeter;                 // +0x44

    void HandleSimulationUpdate(int a, int b);        // 0x00e8ffa0
    void HandleSimulationUpdateBase(int a, int b);    // 0x00e92ca0 (cSpatialObjectView)
    cSPUIMeter_e8ff* UpdateLoyaltyBar(cSPUIMeter_e8ff* p, char bShow, unsigned hdr);   // 0x00e8f120
};

}  // namespace SP

#define FU8(p, off)   (*(u8*)((char*)(p) + (off)))
#define FI32(p, off)  (*(int*)((char*)(p) + (off)))
#define FU32(p, off)  (*(u32*)((char*)(p) + (off)))
#define FF32(p, off)  (*(float*)((char*)(p) + (off)))

static inline void AssignMeter(cSPUIMeter_e8ff*& dst, cSPUIMeter_e8ff* src)
{
    cSPUIMeter_e8ff* old = dst;
    if (src != old) {
        if (src) VC0(void, src, 0);
        dst = src;
        if (old) VC0(void, old, 4);
    }
}

static __forceinline void MakeColor(Vec3* out)
{
    GetUniverseGlobal();
    u32 c = *(u32*)(GetActivePlanet() + 0x1c4);
    out->x = (float)(int)(u8)(c >> 16) * 0.003921569f;
    out->y = (float)(int)(u8)(c >> 8) * 0.003921569f;
    out->z = (float)(int)(u8)c * 0.003921569f;
}

// @ 0x00E8FFA0
void SP::cMineralView::HandleSimulationUpdate(int a, int b)
{
    HandleSimulationUpdateBase(a, b);
    int mode = GetCurrentGameMode();
    if (mode != 0x1654c04 && mode != 0x1654c05) {
        if (!PlanetModel()->sub_b7e3e0((const Vec3*)VC0(void*, mpObject, 0x2c)) &&
            !mpObject->GetEffect(0x4652727)) {
            mpObject->CreateEffect(0x16dd36c1, 0, 0x4652727);
            mpObject->SetEffectParam(0x4652727, 2048.0f);
            Vec3 col;
            MakeColor(&col);
            mpObject->SetEffectPos(0x4652727, &col);
        }
        return;
    }

    if (!mpObject) return;
    cCommodityNode* node = (cCommodityNode*)VC1(void*, mpObject, 0xb8, u32, 0x403df5f);
    if (!node) return;

    cFxRecord* rec = node->GetFxRecord();
    if (rec) {
        node->GetResourceFraction();
        char flag = node->sub_bfe0c0();
        if ((flag == 0 && mEffectMode != 5) || mLastFlag != flag) {
            mEffectMode = 5;
            if (mpObject->GetEffect(0x4652727)) {
                mpObject->KillEffect(0x4652727, 1);
                mpObject->KillEffect(0x4652728, 1);
            }
            int cell = PlanetModel()->GetContinent((const Vec3*)VC0(void*, (char*)node + 0x34, 0x2c));
            if (flag != 0) {
                const char* name;
                if (PlanetModel()->mpTable[cell] == 0) {
                    mpObject->CreateEffect(0xa8de65b4, 0, 0x4652727);
                    name = "object_resource_geyser_ocean_capped_icon";
                } else {
                    mpObject->CreateEffect(0x66dbfed1, 0, 0x4652727);
                    name = "object_resource_geyser_capped_icon";
                }
                mpObject->CreateEffect(SPIDFromName(name), 0, 0x4652728);
                mpObject->SetEffectParam(0x4652727, 2048.0f);
                mpObject->SetEffectParam(0x4652728, 2048.0f);
            } else {
                u32 id;
                if (PlanetModel()->mpTable[cell] == 0) {
                    id = 0x98e0bd04;
                } else {
                    int five = 5;
                    const int& idx = (mEffectMode < 5) ? mEffectMode : five;
                    id = kGeyserEffectIds[idx];
                }
                mpObject->CreateEffect(id, 0, 0x4652727);
                mpObject->SetEffectParam(0x4652727, 2048.0f);
            }
        }
        mLastFlag = flag;

        void* effA = mpObject->FindEffect(0x4652727);
        void* effB = mpObject->FindEffect(0x4652728);
        if (effA) {
            Vec3 pos;
            pos.x = FF32(rec, 0xc);
            pos.y = FF32(rec, 0x10);
            pos.z = FF32(rec, 0x14);
            XformMsg msg;
            float q[4];
            float tmp[9];
            float* m = Matrix3FromQuaternion(tmp, PlanetModel()->BuildSurfaceOrientation(q, &pos));
            for (int i = 0; i < 9; ++i) msg.rot[i] = m[i];
            msg.pos[0] = pos.x;
            msg.pos[1] = pos.y;
            msg.pos[2] = pos.z;
            msg.flags |= 2;
            msg.flags |= 4;
            msg.count++;
            msg.count++;
            VC1(void, effA, 0x18, void*, &msg);
            Vec3 col;
            MakeColor(&col);
            mpObject->SetEffectPos(0x4652727, &col);
            if (effB) {
                col.x = 1.0f;
                col.y = 1.0f;
                col.z = 1.0f;
                int nid = VC0(int, node, 0x4c);
                if (nid != -1) {
                    char* n = NounManager()->GetObject(nid);
                    if (n) {
                        col.x = FF32(n, 0xc4);
                        col.y = FF32(n, 0xc8);
                        col.z = FF32(n, 0xcc);
                    }
                }
                VC1(void, effB, 0x18, void*, &msg);
                mpObject->SetEffectPos(0x4652728, &col);
            }
        }
        if (VC0(u8, (char*)node + 0x34, 0x24)) {
            rec->mFlags |= 8;
            FU8(rec, 0x5c) = 2;
        } else {
            rec->mFlags &= 0xfffffff7;
        }
    }

    char bShow = (FI32(node, 0x214) != -1 && 100.0f > FF32(node, 0x224)) ? 1 : 0;
    AssignMeter(mpConstructionMeter, UpdateLoyaltyBar(mpConstructionMeter, bShow, 3));
    AssignMeter(mpCulturalMeter, UpdateLoyaltyBar(mpCulturalMeter, FI32(node, 0x21c) != -1, 1));
    AssignMeter(mpMilitaryMeter, UpdateLoyaltyBar(mpMilitaryMeter, FI32(node, 0x218) != -1, 0));

    int nounId = VC0(int, node, 0x4c);
    cFxRecord* R = (cFxRecord*)VC0(void*, this, 0x2c);
    int mineState = FI32(node, 0x1ec);
    if (R && mineState) {
        char* n = NounManager()->GetObject(nounId);
        if (FF32(node, 0x224) >= 100.0f)
            n = NounManager()->GetObject(FI32(node, 0x218));
        Vec3 tmpc;
        const Vec3* src;
        if (nounId == -1 || !n) {
            tmpc.x = 0.5f;
            tmpc.y = 0.5f;
            tmpc.z = 0.5f;
            src = &tmpc;
        } else {
            src = (const Vec3*)(n + 0xc4);
        }
        Vec3 c;
        c.x = src->x;
        c.y = src->y;
        c.z = src->z;
        if (Vector3_NotEqual(&c, &mColor)) {
            mColor.x = c.x;
            mColor.y = c.y;
            mColor.z = c.z;
            R->mColor[0] = c.x;
            R->mColor[1] = c.y;
            R->mColor[2] = c.z;
            if (VC0(u8, (char*)node + 0x34, 0x58))
                R->mFlags &= 0xfffff7ff;
            else
                R->mFlags |= 0x800;
        }
        switch (mineState) {
        case 1:
            R->mFlags &= 0xfffffffe;
            if (FU8(node, 0x1e9)) {
                mShieldFxOn = 0;
                FU8(node, 0x1e9) = 0;
            }
            if (FU8(node, 0x1e8)) {
                mpObject->FindEffect(0x547efc1);
                if (!mShieldFxOn) {
                    int cell = PlanetModel()->GetContinent((const Vec3*)VC0(void*, mpObject, 0x2c));
                    u32 id = (PlanetModel()->mpTable[cell] == 0) ? 0x70df71a8 : 0x40966708;
                    mpObject->CreateEffectB(id, 0, 0x547efc1);
                    mpObject->SetEffectParam(0x547efc1, FLT_MAX);
                    mpObject->SetEffectPos(0x547efc1, &mColor);
                    mShieldFxOn = 1;
                }
            }
            break;
        case 2:
            if (mpObject->FindEffect(0x547efc1))
                mpObject->KillEffect(0x547efc1, 1);
            R->mFlags |= 5;
            FU8(node, 0x1e6) = 1;
            break;
        case 3:
            if (((R->mFlags >> 14) & 1) && mHotSpotFxOn) {
                void* w = GonzagoModelWorld();
                VC5(void, w, 0x70, void*, R, u32, 0x6fb760ff, int, 1, float, 0.0f, int, 0);
                mHotSpotFxOn = 0;
            }
            break;
        case 4:
            if (((R->mFlags >> 14) & 1) && !mHotSpotFxOn) {
                void* w = GonzagoModelWorld();
                VC5(void, w, 0x70, void*, R, u32, 0x6fb760ff, int, 0, float, 0.0f, int, 0);
                mHotSpotFxOn = 1;
            }
            break;
        case 6:
            mShieldFxOn = 0;
            R->mFlags &= 0xfffffffe;
            break;
        }
    }

    if (FU32(node, 0x84) & 0x800) {
        if (!mpObject->GetEffect(0x30e8811)) {
            int id = VC0(int, node, 0x4c);
            u32 effId = (id != -1 ? 0xd37b39cdu : 0u) + 0x829de64au;
            mpObject->CreateEffect(effId, 0, 0x30e8811);
            mpObject->SetEffectParam(0x30e8811, 512.0f);
            mpObject->sub_a020(0x30e8811, 16.0f);
        }
        FU32(node, 0x84) &= 0xfffff7ff;
        return;
    }
    if (mpObject->GetEffect(0x30e8811))
        mpObject->KillEffect(0x30e8811, 1);
}
