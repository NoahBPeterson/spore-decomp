// Slice s00db4f60 -- SP::TRIBE_TAKE_OUT_TOOL_Tick (0x00db5300, 2089 bytes), the tribe-mode behavior-tree
// tick of a citizen creature that takes its tool out (PDB candidate name, caller-scored).
//
// State block (behavior_memory_block, layout from the asm; names are Claude-coined):
//   state 0: play the take-out animation. While the tool is not ready the creature plays the animation, and once
//            the play timer has run out and the locomotive object reports ready (vf+0x48) the tool is taken out.
//            Then the animation weight (creature->mpAnim+0x80) is eased towards mBlend, which becomes 1.0
//            when other creatures are crowding the creature (GetPropertyT<float>(0xfd4fd8dc) otherwise).
//            After the finish timer ran out the creature is released: tool effect cleared, state = 1.
//   state 1: end of the tool use: finishes the tribe timer, walks the creature back next to the tribe's
//            center on the planet surface and tells the tribe-mode UI. state = 2.
//   state 2: fade the animation weight to 1 and finish with the tool-effect animation.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (same module as the other SP::*_Tick behaviors).
#include "types.h"
#include <math.h>

namespace nSPBehaviorTree { struct behavior_memory_block { uint32_t Data[32]; }; }
using nSPBehaviorTree::behavior_memory_block;

namespace SP {

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vec3 operator-(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vec3 operator+(const Vec3& a, const Vec3& b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
struct Quat { float x, y, z, w; };

// Clamp to [lo, hi]: the original uses the SSE maxss/minss helper.
__forceinline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

#define PV(n) virtual void pv##n();

struct cSpatialObject;
struct cSPCreatureCitizen;

// Spatial/locomotive sub-object of a creature (at +0xc0), own vtable.
struct Loco {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
    virtual const Vec3* GetPosition();                            // +0x2c
    PV(0c) PV(0d)
    virtual void SetPosition(const Vec3* p);                      // +0x38
    PV(0f) PV(10)
    virtual void SetPositionAndOrientation(const Vec3* p, const Quat* q);   // +0x44
    virtual bool IsOnGround();                                    // +0x48 (name guessed)
    PV(13) PV(14) PV(15)
    virtual bool IsControlled();                                  // +0x58 (name guessed)
    PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    virtual float GetFootprintRadius();                           // +0x74
};

// Object embedded at creature+0x34.
struct SubObj34 { int FUN_00cee330(); };                          // 0xcee330

// Object embedded at creature+0x5a8 (animation speed / weight holder).
struct Obj5a8 {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual float GetFloat();                                     // +0x58
    void FUN_00f924e0(float f);                                   // 0xf924e0 thiscall(float)
    void FUN_00bfc460(int a);                                     // 0xbfc460 thiscall(int)
};

// Pointer at creature+0xb54.
struct AnimState { char pad[0x80]; float mWeight; };               // +0x80

struct Community {                                                // object returned by the tribe's vf+0xac
    char pad00[0x34];
    struct Anchor {
        PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a)
        virtual const Vec3* GetPosition();                        // +0x2c
    } mAnchor;                                                    // +0x34
    const Vec3* FUN_00c8ef20(Vec3* tmp);                          // 0xc8ef20
};

struct cTribe {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a)
    virtual Community* GetCommunity();                            // +0xac
    char pad04[0x2c8 - 0x4];
    float mTimer;                                                 // +0x2c8
    char pad2cc[0x556 - 0x2cc];
    bool  mbFlag556;                                              // +0x556
    unsigned GetAdultPopulation();                                // 0xc8f370
    void FUN_00c95cc0(cSPCreatureCitizen* c);                     // 0xc95cc0
};

struct UIController {                                             // object returned by cTribeModeStrategy vf+0x6c
    void FUN_00cca000(cSPCreatureCitizen* c, float pct);          // 0xcca000
    void FUN_00cc9e20(cSPCreatureCitizen* c);                     // 0xcc9e20
};

struct cTribeModeStrategy {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a)
    virtual UIController* GetUIController();                      // +0x6c
    static cTribeModeStrategy* Instance();                        // 0xcd40b0
};

struct SpatialObjVector {                                         // eastl::fixed_vector<AutoRefCount<cSpatialObject>, 8>
    cSpatialObject** mpBegin;
    cSpatialObject** mpEnd;
    cSpatialObject** mpCapacity;
    uint32_t pad0c[2];
    uint32_t mnFlags;                                             // +0x14
    cSpatialObject* mBuffer[8];                                   // +0x18
    SpatialObjVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 8), mnFlags(0) {}
    ~SpatialObjVector();                                          // 0xad92d0
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

struct cSpatialQuery {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11)
    virtual bool QueryRadius(const Vec3* pos, float radius, SpatialObjVector* out, int a, int b, int c);   // +0x48
};

struct cPlanetModel {
    void DirectionToSurfacePosition(Vec3* out, const Vec3* in);                          // 0xb815a0
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos, const Vec3* dir);          // 0xb7f250
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos);                           // 0xb7f190
};

struct GlobalObj {                                                // FUN_00b3d2b0() result
    void* FUN_00ac79d0();                                         // 0xac79d0
    void FUN_00ac7de0(int a, void* b);                            // 0xac7de0
};

struct PropertyList;

struct cSPCreatureCitizen {
    PV(00) PV(01) PV(02) PV(03) PV(04) PV(05) PV(06) PV(07) PV(08) PV(09) PV(0a) PV(0b) PV(0c) PV(0d) PV(0e)
    PV(0f) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(1a) PV(1b) PV(1c) PV(1d)
    PV(1e) PV(1f) PV(20) PV(21) PV(22) PV(23)
    virtual void vf90();                                          // +0x90
    PV(25) PV(26) PV(27) PV(28) PV(29) PV(2a) PV(2b) PV(2c) PV(2d) PV(2e) PV(2f) PV(30) PV(31)
    virtual void vfc8(int a);                                     // +0xc8
    char pad_cc[0x34 - 0x4];
    SubObj34 mObj34;                                              // +0x34
    char pad_35[0xc0 - 0x35];
    Loco mLoco;                                                   // +0xc0
    char pad_c4[0x5a8 - 0xc4];
    Obj5a8 mObj5a8;                                               // +0x5a8
    char pad_5ac[0xb50 - 0x5a8 - sizeof(Obj5a8)];
    int       mField50;                                           // +0xb50
    AnimState* mpAnim;                                            // +0xb54
    char pad_b58[6];
    bool      mbFlagB5e;                                          // +0xb5e

    cTribe* GetTribe();                                           // 0xc22f50
    int  GetCurrentToolEffect();                                  // 0xc22a70
    bool WaitForAnimEventOrEnd(uint32_t ev, void* p, int a, int b, int c);   // 0xc14ef0
    void SetCurrentToolEffect(int effect, int a);                 // 0xc24f40
    bool AnimationFinished(uint32_t id);                          // 0xc123f0
    void InterruptAnimation(uint32_t id, int a, int b);           // 0xc12310
    void FUN_00c14750(int a);                                     // 0xc14750
    bool FUN_00c0e0c0(uint32_t id);                               // 0xc0e0c0
};
#undef PV

cSpatialQuery* FUN_00b3d240();                                    // 0xb3d240
GlobalObj*     FUN_00b3d2b0();                                    // 0xb3d2b0
cPlanetModel*  PlanetModel();                                     // 0xb3d350
void*          GetCurrentGameMode();                              // 0xb5b800
cSPCreatureCitizen* FUN_00ae66f0(cSpatialObject* o);              // 0xae66f0 (cdecl)
Vec3* normalized_safe(Vec3* out, const Vec3* in);                 // 0x449c20 (cdecl)
float GetPropertyT_float(PropertyList* list, uint32_t id, float def);   // 0x4e1c70 SP::GetPropertyT<float> (cdecl)
extern PropertyList* g_DebugProps;                                // 0x1581288

struct TAKE_OUT_TOOL_memory_block {
    int   mState;          // +0x00
    float mPlayTimer;      // +0x04
    float mFinishTimer;    // +0x08
    float mCrowdTimer;     // +0x0c
    float mBlend;          // +0x10
    float mDuration;       // +0x14
    bool  mbReady;         // +0x18
    bool  mbAnimStarted;   // +0x19
};

static const uint32_t kAnimTakeOut = 0x2c39200;

// =====================================================================
// @ 0x00db5300  SP::TRIBE_TAKE_OUT_TOOL_Tick
// =====================================================================
bool TRIBE_TAKE_OUT_TOOL_Tick(void* pSelf, double, uint32_t flags, uint32_t, behavior_memory_block* pMemory,
                              behavior_memory_block*, float dt)
{
    cSPCreatureCitizen* creature = (cSPCreatureCitizen*)pSelf;
    TAKE_OUT_TOOL_memory_block* mem = (TAKE_OUT_TOOL_memory_block*)pMemory;
    cTribe* tribe = creature->GetTribe();
    Loco* loco = &creature->mLoco;

    if (loco->IsControlled()) {
        cTribeModeStrategy* strat = cTribeModeStrategy::Instance();
        if (strat && strat->GetUIController()) {
            float pct = ((mem->mDuration - tribe->mTimer) / mem->mDuration) * 100.0f;
            pct = Clamp(pct, 0.0f, 100.0f);
            strat->GetUIController()->FUN_00cca000(creature, pct);
        }
    }
    tribe->mTimer = tribe->mTimer - dt;

    switch (mem->mState) {
    case 0:
        if (mem->mbReady) {
            if (creature->mpAnim) {
                mem->mFinishTimer = mem->mFinishTimer - dt;
                if (mem->mFinishTimer <= 0.0f) {
                    creature->SetCurrentToolEffect(0, -1);
                    loco->SetPosition(creature->GetTribe()->GetCommunity()->mAnchor.GetPosition());
                    mem->mState = 1;
                    return true;
                }
                float p = pow((double)0.1f, (double)dt);
                AnimState* anim = creature->mpAnim;
                anim->mWeight = (1.0f - p) * 0.01f + p * anim->mWeight;
            }
            return true;
        }
        if (!creature->mbFlagB5e)
            return false;
        {
            uint32_t animId = 0x2481db4;
            if ((flags & 1) && tribe->GetAdultPopulation() < 2)
                animId = 0x5f0eaa9;
            if (!(mem->mbAnimStarted && creature->FUN_00c0e0c0(animId))) {
                mem->mbAnimStarted = true;
                creature->InterruptAnimation(animId, -1, 0);
                SubObj34* o = &creature->mObj34;
                if (o->FUN_00cee330()) {
                    FUN_00b3d2b0()->FUN_00ac7de0(o->FUN_00cee330(), FUN_00b3d2b0()->FUN_00ac79d0());
                }
            }
        }
        mem->mPlayTimer = mem->mPlayTimer - dt;
        if (mem->mPlayTimer <= 0.0f) {
            if (!loco->IsOnGround()) {
                creature->SetCurrentToolEffect(0, -1);
                const Vec3* c = creature->GetTribe()->GetCommunity()->mAnchor.GetPosition();
                Vec3 p = *c;
                Quat q;
                loco->SetPositionAndOrientation(&p, PlanetModel()->BuildSurfaceOrientation(&q, &p));
                mem->mState = 1;
                return true;
            }
            mem->mbReady = true;
        }
        if (GetCurrentGameMode() == (void*)0x1654c02 && loco->IsOnGround() && (flags & 0x1000) && creature->mpAnim) {
            mem->mCrowdTimer = mem->mCrowdTimer - dt;
            if (creature->mField50) {
                mem->mBlend = 1.0f;
            } else if (mem->mCrowdTimer < 0.0f) {
                mem->mCrowdTimer = 1.0f;
                mem->mBlend = 1.0f;
                const Vec3* pos = loco->GetPosition();
                float radius = loco->GetFootprintRadius();
                SpatialObjVector v;
                if (FUN_00b3d240()->QueryRadius(pos, radius + radius, &v, 0, 0, 0)) {
                    unsigned n = v.size();
                    for (unsigned i = 0; i < n; ++i) {
                        cSPCreatureCitizen* other = FUN_00ae66f0(v.mpBegin[i]);
                        if (other && other != creature && !other->mbFlagB5e) {
                            const Vec3* op = other->mLoco.GetPosition();
                            Vec3 d = *op - *pos;
                            float r2 = other->mLoco.GetFootprintRadius() + radius;
                            if (r2 * r2 > d.z * d.z + d.y * d.y + d.x * d.x) {
                                mem->mBlend = GetPropertyT_float(g_DebugProps, 0xfd4fd8dc, 0.4f);
                                break;
                            }
                        }
                    }
                }
            }
            float p = pow((double)0.1f, (double)dt);
            AnimState* anim = creature->mpAnim;
            anim->mWeight = (1.0f - p) * mem->mBlend + p * anim->mWeight;
        }
        return true;
    case 1:
        if (tribe->mbFlag556) {
            creature->vfc8(0);
            return true;
        }
        if (tribe->mTimer <= 0.0f) {
            tribe->mTimer = 0.0f;
            Obj5a8* o = &creature->mObj5a8;
            o->FUN_00f924e0(o->GetFloat());
            o->FUN_00bfc460(0);
            creature->vf90();
            creature->FUN_00c14750(1);
            tribe->FUN_00c95cc0(creature);
            Community* comm = tribe->GetCommunity();
            const Vec3* home = comm->mAnchor.GetPosition();
            Vec3 tmp;
            const Vec3* from = comm->FUN_00c8ef20(&tmp);
            Vec3 diff = *from - *home;
            Vec3 dir;
            normalized_safe(&dir, &diff);
            float r = loco->GetFootprintRadius();
            Vec3 off(dir.x * r, dir.y * r, dir.z * r);
            Vec3 tmp2;
            const Vec3* base = comm->FUN_00c8ef20(&tmp2);
            Vec3 target = *base + off;
            Vec3 surf;
            PlanetModel()->DirectionToSurfacePosition(&surf, &target);
            Quat orient;
            PlanetModel()->BuildSurfaceOrientation(&orient, &surf, &dir);
            loco->SetPositionAndOrientation(&surf, &orient);
            creature->mpAnim->mWeight = 0.0f;
            creature->InterruptAnimation(kAnimTakeOut, -1, 0);
            if (loco->IsControlled()) {
                cTribeModeStrategy* strat = cTribeModeStrategy::Instance();
                if (strat) {
                    if (strat->GetUIController()) {
                        strat->GetUIController()->FUN_00cc9e20(creature);
                    }
                }
            }
            mem->mState = 2;
        }
        return true;
    case 2:
        if (creature->GetCurrentToolEffect() != 0x11) {
            int ev = -1;
            if (creature->WaitForAnimEventOrEnd(0x7d7502fc, &ev, kAnimTakeOut, 0, 1))
                creature->SetCurrentToolEffect(0x11, -1);
        }
        {
            float w = pow((double)0.1f, (double)(dt * 0.33333334f));
            AnimState* anim = creature->mpAnim;
            float nw = w * anim->mWeight + (1.0f - w);
            anim->mWeight = nw;
            return !(0.95f < nw && creature->AnimationFinished(kAnimTakeOut));
        }
    }
    return false;
}

} // namespace SP
