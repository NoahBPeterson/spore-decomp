// Slice s00e73f60 -- SP::sUpdateGfx (cell stage): per-frame update of the cell game's
// graphics: audio parameters driven by the avatar cell, then one pass over every cell gfx
// object (propulsion, electric, charging, poison and other part effects).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU; no /EHsc: locals with dtors get no EH frame)
#include "types.h"
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#pragma intrinsic(sqrt)
extern "C" double __cdecl sqrt(double);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

// ---------------------------------------------------------------- math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator*(float f) const { return Vector3(x * f, y * f, z * f); }
};

// x87/SSE helpers from the original headers: clamp with maxss/minss on memory operands.
inline float Clamp(float value, float lo, float hi)
{
    __asm {
        movss xmm0, value
        maxss xmm0, lo
        minss xmm0, hi
        movss value, xmm0
    }
    return value;
}

inline float Saturate(float value, float hi)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, value
        minss xmm0, hi
        movss value, xmm0
    }
    return value;
}

// ---------------------------------------------------------------- resources / effects
struct ResourceKey {
    uint32 instanceID;   // +0x0
    uint32 typeID;       // +0x4
    uint32 groupID;      // +0x8
};

struct cIVisualEffect {                       // EA::Swarm::cIVisualEffect
    virtual int AddRef();                     // +0x00
    virtual int Release();                    // +0x04
    virtual bool Start(int flags);            // +0x08
    virtual bool Stop(int flags);             // +0x0c
    virtual void v10();
    virtual void v14();
    virtual void SetTransform(const void* transform);   // +0x18
};

struct cIEffectsWorld {                       // EA::Swarm::cIEffectsWorld
    virtual int AddRef();                     // +0x00
    virtual int Release();                    // +0x04
    virtual bool CreateVisualEffect(uint64 instanceID, cIVisualEffect** ppEffect);   // +0x08
};

// EA::COM::AutoRefCount<cIVisualEffect>
struct VisualEffectPtr {
    cIVisualEffect* mpObject;
    VisualEffectPtr() : mpObject(0) {}
    ~VisualEffectPtr() { if (mpObject) mpObject->Release(); }
    cIVisualEffect** AsPointer() { return &mpObject; }
    cIVisualEffect* operator->() const { return mpObject; }
    operator cIVisualEffect*() const { return mpObject; }
};

// ---------------------------------------------------------------- messaging
struct MessageData {
    float mFloat;
    uint32 mPad;
};

struct IMessageRC {
    virtual int AddRef();
    virtual int Release();
};

struct MessageRC : IMessageRC {               // vtable 0x013eb90c
    volatile long mRefCount;                  // +0x4
    MessageRC() { _InterlockedExchange(&mRefCount, 0); }
};

struct MessageBasic5 {                        // non-polymorphic base, laid out after MessageRC
    MessageData mData[5];                     // +0x08
    uint32 mId;                               // +0x30
    uint32 mPad34;
    MessageBasic5() : mId(0) {}
};

struct MessageBasicRC5 : MessageBasic5, MessageRC {   // vtable 0x013eb844
    uint32 mRCFlags;                          // +0x38
    uint32 mPad3c;
    MessageBasicRC5() : mRCFlags(0) {}
    ~MessageBasicRC5();                       // 0x00421cf0 (SlotMessage::Destruct)
    virtual int AddRef();
    virtual int Release();
};

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void MessageSend(uint32 messageID, void* pMessage, void* pListener);   // +0x14
};
namespace EA { namespace Messaging { IMessageServer* GetServer(); } }   // 0x00883860

struct cUIState { uint32 pad[0x2c / 4]; int mMode; };   // +0x2c
cUIState* GetUIState();                                  // 0x00b3d4d0

// ---------------------------------------------------------------- cell game
struct cCellScaleInfo {                       // Simulator::Cell::cCellScaleInfo (0x1c bytes)
    int scale;                                // +0x00
    int requiredFood;                         // +0x04
    int field_8;
    float field_C;
    float field_10;
    uint32 field_14;
    float field_18;
};

// 0x01483c30: one entry per food level, then the editor entry (level 1000) at 0x01483e60.
static const cCellScaleInfo kCellScaleInfos[21] = {
    { 1,    0,  0, 1.0f,     1.0f,     0x1d2ec0a4, 0.0f  },
    { 1,   50,  5, 1.73f,    1.0f,     0x1d2ec0a4, 0.0f  },
    { 2,  100, 10, 3.0f,     3.0f,     0x1d2ec0a4, 0.0f  },
    { 2,  150, 13, 5.2f,     3.0f,     0x1d2ec0a4, 0.0f  },
    { 3,  200, 16, 10.0f,    10.0f,    0x1d2ec0a5, 0.25f },
    { 3,  250, 19, 17.3f,    10.0f,    0x1d2ec0a5, 0.25f },
    { 4,  300, 22, 30.0f,    30.0f,    0x1d2ec0a5, 0.25f },
    { 4,  350, 25, 52.0f,    30.0f,    0x1d2ec0a5, 0.25f },
    { 5,  400, 28, 100.0f,   100.0f,   0x1d2ec0a6, 0.5f  },
    { 5,  450, 31, 173.0f,   100.0f,   0x1d2ec0a6, 0.5f  },
    { 6,  500, 34, 300.0f,   300.0f,   0x1d2ec0a6, 0.5f  },
    { 6,  550, 37, 520.0f,   300.0f,   0x1d2ec0a6, 0.5f  },
    { 7,  600, 40, 1000.0f,  1000.0f,  0x1d2ec0a7, 0.75f },
    { 7,  650, 43, 1730.0f,  1000.0f,  0x1d2ec0a7, 0.75f },
    { 8,  700, 46, 3000.0f,  3000.0f,  0x1d2ec0a7, 0.75f },
    { 8,  750, 49, 5200.0f,  3000.0f,  0x1d2ec0a7, 0.75f },
    { 9,  800, 52, 10000.0f, 10000.0f, 0x1d2ec0a0, 1.0f  },
    { 9,  850, 55, 17300.0f, 10000.0f, 0x1d2ec0a0, 1.0f  },
    { 10, 900, 58, 30000.0f, 30000.0f, 0x1d2ec0a0, 1.0f  },
    { 10, 950, 61, 52000.0f, 30000.0f, 0x1d2ec0a0, 1.0f  },
    { 10, 1000, 65, 52000.0f, 30000.0f, 0x1d2ec0a0, 1.0f },
};

inline const cCellScaleInfo* GetCellScaleInfo(int level)
{
    if (level == 1000)
        return &kCellScaleInfos[20];
    int i = 0;
    while (level >= kCellScaleInfos[i].requiredFood)
        i++;
    return &kCellScaleInfos[i - 1];
}

struct cSPTransform {                         // 0x38 bytes
    uint16 mFlags;                            // +0x00
    uint16 mModificationCount;                // +0x02
    Vector3 mTranslation;                     // +0x04
    float mScale;                             // +0x10
    float mRotation[9];                       // +0x14
};

struct cCell {                                // SP::cSPCell / Simulator::Cell::cCellObjectData
    int mIndex;                               // +0x000 (pool handle)
    uint32 pad004[(0x48 - 0x04) / 4];
    cSPTransform mTransform;                  // +0x048
    float mRelativeElevation;                 // +0x080
    uint32 pad084[3];
    Vector3 mVelocity;                        // +0x090
    uint32 pad09c;
    float mOpacity;                           // +0x0a0
    uint32 pad0a4[7];
    cSPTransform mVisualTransform;            // +0x0c0
    uint32 pad0f8;
    ResourceKey mModelKey;                    // +0x0fc
    uint32 pad108[(0x160 - 0x108) / 4];
    float field_160;                          // +0x160
    uint32 pad164[4];
    int field_174;                            // +0x174
};

// Byte-level accessors for the cell's scattered members (offsets from the retail binary).
#define CELL_FIELD(T, c, off) (*(T*)((char*)(c) + (off)))

struct cObjectPool {                          // cSPObjectPoolT<T, N>
    void* GetSafe(int index);                 // 0x00b721d0 (null when the handle is stale)
    void* Get(int index);                     // 0x00b72210
    int Begin();                              // 0x00e31100
    void* Next(int* pIterator);               // 0x00b72230
};

struct cCellSerializableData { uint32 pad[0x1c / 4]; int mLevel; };   // +0x1c

struct cCellGame {
    uint32 pad0000[0x1c / 4];
    cObjectPool mCells;                       // +0x001c
    uint32 pad0020[(0x40fc - 0x20) / 4];
    int midPlayerCell;                        // +0x40fc (cell group that renders in the main world)
    uint32 pad4100[2];
    void* mpFluidParticles;                   // +0x4108
    uint32 pad410c[4];
    int mAvatarCellIndex;                     // +0x411c
    bool field_4120;                          // +0x4120
    uint32 pad4124[(0x5158 - 0x4124) / 4];
    int field_5158;                           // +0x5158
    uint32 pad515c[(0x5190 - 0x515c) / 4];
    cCellSerializableData* mpSerializableData;   // +0x5190
    uint32 pad5194[(0x51b0 - 0x5194) / 4];
    int field_51b0;                           // +0x51b0
    int field_51b4;                           // +0x51b4
};

struct cCellGfxObject {                       // one entry of cCellGfx's pool at +0x168
    uint32 pad00[3];
    int mCellIndex;                           // +0x0c
    uint32 pad10[(0x60 - 0x10) / 4];
    cIVisualEffect* mpElectricEffect;         // +0x60
    cIVisualEffect* mpChargingEffect;         // +0x64
    uint32 pad68[4];
    cIVisualEffect* mpPoisonEffect;           // +0x78
    uint32 pad7c[4];
    cIVisualEffect* mpEffect8c;               // +0x8c
    cIVisualEffect* mpEffect90;               // +0x90
    cIVisualEffect* mpEffect94;               // +0x94
    cIVisualEffect* mpPlayerEffect;           // +0x98
    cIVisualEffect* mpEffect9c;               // +0x9c
    cIVisualEffect* mpJetEffect;              // +0xa0
    cIVisualEffect* mpCiliaEffect;            // +0xa4
    cIVisualEffect* mpFlagellaEffect;         // +0xa8

    void Update(const cSPTransform* transform, float opacity, float elevation, float lod,
                const cSPTransform* visualTransform, int anim, int field24c, int scaleDelta,
                int group);                   // 0x00e62b80
};

struct cPartEffectTable {                     // pool entry at cCellGfx+0x168, data at +0x24
    uint32 pad[0x24 / 4];
    struct cEffectSet* mpEffects;             // +0x24
};

struct cEffectEntry { uint32 key; uint32 pad; int value; };
struct cEffectSet {
    uint32 pad[0x8c / 4];
    cEffectEntry mEntries[16];                // +0x8c
    uint32 mCount;                            // +0x14c
};

struct cCellGfx {
    uint32 pad00000[0x40 / 4];
    char field_40[0x128];                     // +0x40
    cObjectPool mGfxObjects;                  // +0x168
    uint32 pad0016c[(0x161bc - 0x16c) / 4];
    cIEffectsWorld* mpBackgroundEffectsWorld; // +0x161bc
    uint32 pad161c0[2];
    cIEffectsWorld* mpMainEffectsWorld;       // +0x161c8
    uint32 pad161cc[4];
    char field_161dc[0x14];                   // +0x161dc
    int mCurrentSample;                       // +0x161f0
    float mSpeedParamSampling[4];             // +0x161f4
    uint32 pad16204;
    int mAudioHandle;                         // +0x16208
};

struct cSPFluidParticles {
    char pad[0x1bd60];
    char field_1bd60[0x1c210 - 0x1bd60];      // +0x1bd60
    char field_1c210[4];                      // +0x1c210
};

struct cCellUI { uint32 pad[0x48 / 4]; Vector3 mCursorPosition; };   // +0x48

struct cBoundingBox { Vector3 lower; Vector3 upper; };

extern cCellGame* gspCellGame;                // 0x016b3c04
extern cCellGfx* gspCellGfx;                  // 0x016b3c08
extern cCellUI* gspCellUI;                    // 0x016b3c0c
extern cBoundingBox sVisibleBackgroundBBox;   // 0x016b3c88

// ---------------------------------------------------------------- callees
void FUN_00e64e10();                                                   // 0x00e64e10
void LoadEffectMap();                                                  // 0x00e63560
void FUN_00e55080();                                                   // 0x00e55080
void SetAudioParameter(int handle, uint32 id, float value);           // 0x00e826b0
void SetGlobalAudioParameter(uint32 id, float value);                 // 0x00e82690
float FUN_00e5bfa0();                                                  // 0x00e5bfa0
float FUN_00e5be80();                                                  // 0x00e5be80
namespace SP {
float FluidParticlesSampleVelMagnitude(void* fluid, const Vector3& pos);   // 0x00e4e590
void UpdateCollectableVisibility(cCellGfxObject* gfx, int scale);     // 0x00e4f860
int GetScaleDifferenceWithPlayer(cCell* cell);                         // 0x00e57340
bool CreateEffectSafe(cIEffectsWorld* world, uint32 id, int flags, cIVisualEffect** ppEffect);   // 0x00628450
void sUpdateElectricRibbonEffect(cIEffectsWorld* world, cIVisualEffect** ppEffect, cCell* cell, int a, int b);  // 0x00e6b9b0
void sUpdateChargingEffect(cIEffectsWorld* world, cIVisualEffect** ppEffect, const ResourceKey* key,
                           cEffectSet* effects, const cSPTransform* transform, bool b, float f);  // 0x00e6bc10
void sUpdatePoisonReleaseEffect(cIEffectsWorld* world, cIVisualEffect** ppEffect, cCell* cell,
                                const ResourceKey* key, const cSPTransform* visualTransform, int level,
                                bool b, bool nearScale, bool isAvatar);  // 0x00e6bf30
}
float GetCellLod(cCell* cell);                                         // 0x00e6d6d0
void StartPartEffect(cIVisualEffect* effect, cEffectSet* effects, int a);   // 0x00e833f0
void UpdatePropulsionEffect(cIEffectsWorld* world, cIVisualEffect** ppEffect, const cSPTransform* visualTransform,
                            const cSPTransform* transform, float scale, float strength, uint32 id,
                            const char* name);        // 0x00e639d0
bool CellWantsPlayerEffect(cCell* cell);                               // 0x00e6b500
struct cCellResource { uint32 pad[0x1218 / 4]; int field_1218; uint32 pad121c[(0x128c - 0x121c) / 4]; int field_128c; };
cCellResource* GetCellResource(ResourceKey key);                       // 0x00e679e0
void FUN_00e63bf0(cCell* cell, cIEffectsWorld* world, cIVisualEffect** ppEffect, const cSPTransform* t, bool b);   // 0x00e63bf0
void CompactEffects(cCell* cell, cCellGfxObject* gfx);                // 0x00e51990
void FUN_00e61050(cIEffectsWorld* world, cIVisualEffect** ppEffect, const cSPTransform* t, cEffectSet* effects,
                  int a, bool b);                                       // 0x00e61050
void FUN_00e67510(cIEffectsWorld* world, cIVisualEffect** ppEffect, const cSPTransform* visualTransform,
                  const cSPTransform* t, cEffectSet* effects, int slot, bool b);   // 0x00e67510
void FUN_00e660e0(cCell* cell, cCellGfxObject* gfx);                  // 0x00e660e0
void FUN_00e6c330();                                                   // 0x00e6c330
void FUN_00e63ac0(void* p);                                            // 0x00e63ac0
void FUN_00e831a0(void* p, void* a, void* b);                          // 0x00e831a0

// 0x00e50620: remove the entry with `key` from the set, returning its value (static, register args).
static bool RemoveEffectEntry(cEffectSet* set, uint32 key, int* pValue)
{
    for (uint32 i = 0; i < set->mCount; i++) {
        if (set->mEntries[i].key == key) {
            if (pValue)
                *pValue = set->mEntries[i].value;
            set->mCount--;
            set->mEntries[i] = set->mEntries[set->mCount];
            return true;
        }
    }
    return false;
}

#define CELL_I(c, off)  CELL_FIELD(int, c, off)
#define CELL_F(c, off)  CELL_FIELD(float, c, off)
#define CELL_B(c, off)  CELL_FIELD(bool, c, off)

inline cObjectPool& Cells() { return gspCellGame->mCells; }
inline cObjectPool& GfxObjects() { return gspCellGfx->mGfxObjects; }
inline cCell* GetCellSafe(int id) { return (cCell*)Cells().GetSafe(id); }
inline cCell* GetCell(int id) { return (cCell*)Cells().Get(id); }
inline cCellGfxObject* NextGfx(int* it) { return (cCellGfxObject*)GfxObjects().Next(it); }
inline void* GetGfxEntry(int id) { return GfxObjects().Get(id); }
inline cEffectSet* GetPartEffects(cCell* cell)
{
    if (!CELL_I(cell, 0x248))
        return 0;
    if (!cell->mModelKey.instanceID)
        return 0;
    return ((cPartEffectTable*)GetGfxEntry(CELL_I(cell, 0x248)))->mpEffects;
}

inline cIEffectsWorld* GetEffectsWorld(cCell* cell)
{
    cIEffectsWorld*& world = CELL_I(cell, 0x35c) == gspCellGame->midPlayerCell
                                 ? gspCellGfx->mpMainEffectsWorld : gspCellGfx->mpBackgroundEffectsWorld;
    return world;
}

inline bool IsCursorMode() { int mode = GetUIState()->mMode; return mode == 1 || mode == 2; }

namespace SP {

// @ 0x00e73f60
void sUpdateGfx()
{
    FUN_00e64e10();
    LoadEffectMap();
    FUN_00e55080();

    cCell* avatar = GetCellSafe(gspCellGame->mAvatarCellIndex);
    float avgSpeed = 0.0f;
    float fluidSpeed;
    float health;
    float zoomed;
    if (avatar) {
        float speed = Saturate((float)sqrt(avatar->mVelocity.x * avatar->mVelocity.x +
                                           avatar->mVelocity.y * avatar->mVelocity.y +
                                           avatar->mVelocity.z * avatar->mVelocity.z) * 0.125f, 1.0f);
        gspCellGfx->mSpeedParamSampling[gspCellGfx->mCurrentSample++] = speed;
        gspCellGfx->mCurrentSample %= 4;
        float sum = 0.0f;
        for (int i = 0; i < 4; i++)
            sum += gspCellGfx->mSpeedParamSampling[i];
        avgSpeed = sum * 0.25f;
        SetAudioParameter(gspCellGfx->mAudioHandle, 0xf03e3ddf, Clamp((avatar->mTransform.mScale - 0.5f) * 0.6666667f, 0.0f, 1.0f));

        IMessageServer* server = EA::Messaging::GetServer();
        if (server) {
            Vector3 pos;
            if (IsCursorMode())
                pos = gspCellUI->mCursorPosition;
            else
                pos = avatar->mTransform.mTranslation;
            MessageBasicRC5 msg;
            msg.mData[0].mFloat = pos.x;
            msg.mData[1].mFloat = pos.y;
            msg.mData[2].mFloat = pos.z;
            server->MessageSend(0x052d9bab, &msg, 0);
        }

        int anim = CELL_I(avatar, 0x18c);
        if (anim == 7 || anim == 8 || anim == 9 || anim == 10)
            SetGlobalAudioParameter(0xf83dae6e, 0.0f);
        else
            SetGlobalAudioParameter(0xf83dae6e, FUN_00e5bfa0() + 1.0f);
        fluidSpeed = SP::FluidParticlesSampleVelMagnitude(gspCellGame->mpFluidParticles,
                                                          avatar->mTransform.mTranslation);
        health = (float)CELL_I(avatar, 0x244) * 0.16666667f;
        zoomed = gspCellGame->field_4120 ? 1.0f : 0.0f;
    } else {
        fluidSpeed = SP::FluidParticlesSampleVelMagnitude(gspCellGame->mpFluidParticles,
            (sVisibleBackgroundBBox.upper + sVisibleBackgroundBBox.lower) * 0.5f);
        health = 0.0f;
        zoomed = 0.0f;
        if (gspCellGame->field_5158 == 4)
            SetGlobalAudioParameter(0xf83dae6e, 0.0f);
        else
            SetGlobalAudioParameter(0xf83dae6e,
                Saturate((float)gspCellGame->mpSerializableData->mLevel * 0.001f, 1.0f) + 1.0f);
    }

    SetGlobalAudioParameter(0x07632190, Saturate(fluidSpeed * 0.1f, 1.0f));
    SetGlobalAudioParameter(0xb0b3caf6, health);
    SetGlobalAudioParameter(0xa807ac16, zoomed);
    SetGlobalAudioParameter(0xe6a63e05, avgSpeed);
    if (gspCellGame->field_51b4 == 3)
        SetGlobalAudioParameter(0x4cd9e37f, FUN_00e5be80());
    else
        SetGlobalAudioParameter(0x4cd9e37f, 0.0f);

    int it = gspCellGfx->mGfxObjects.Begin();
    for (cCellGfxObject* gfx = NextGfx(&it); gfx;
         gfx = NextGfx(&it)) {
        cCell* cell = GetCell(gfx->mCellIndex);

        int level = gspCellGame->mpSerializableData->mLevel;
        int playerScale = GetCellScaleInfo(level)->scale;
        int cellScale = CELL_I(cell, 0x358);
        if (cellScale == -1)
            cellScale = GetCellScaleInfo(level)->scale;
        gfx->Update(&cell->mTransform, cell->mOpacity, cell->mRelativeElevation, GetCellLod(cell),
                    &cell->mVisualTransform, CELL_I(cell, 0x18c), CELL_I(cell, 0x24c),
                    cellScale - playerScale + 2, CELL_I(cell, 0x35c));

        int scale = CELL_I(cell, 0x358);
        if (scale == -1)
            scale = GetCellScaleInfo(gspCellGame->mpSerializableData->mLevel)->scale;
        SP::UpdateCollectableVisibility(gfx, scale);

        cEffectSet* effects = GetPartEffects(cell);
        if (effects) {
            int effectID;
            if (RemoveEffectEntry(GetPartEffects(cell), 0x4ff54f49, &effectID)) {
                cIEffectsWorld* world = GetEffectsWorld(cell);
                VisualEffectPtr effect;
                world->CreateVisualEffect(effectID, effect.AsPointer());
                if (effect) {
                    effect->Start(0);
                    StartPartEffect(effect, GetPartEffects(cell), CELL_I(cell, 0x174));
                }
            }
        }

        cIEffectsWorld* world = GetEffectsWorld(cell);
        const ResourceKey* key = &cell->mModelKey;
        if (cell->mModelKey.instanceID) {
            float strength = 1.0f;
            if (SP::GetScaleDifferenceWithPlayer(cell) <= 1)
                strength = 0.25f;
            UpdatePropulsionEffect(world, &gfx->mpJetEffect, &cell->mVisualTransform, &cell->mTransform,
                                   strength, CELL_F(cell, 0x198), 0x2c34420c, "cell_propulsionJet");
            UpdatePropulsionEffect(world, &gfx->mpCiliaEffect, &cell->mVisualTransform, &cell->mTransform,
                                   strength, CELL_F(cell, 0x19c), 0xa6d4590b, "cell_propulsionCilia");
            UpdatePropulsionEffect(world, &gfx->mpFlagellaEffect, &cell->mVisualTransform, &cell->mTransform,
                                   strength, CELL_F(cell, 0x194), 0x44894cd7, "cell_propulsionFlagella");
        }

        if (CELL_I(cell, 0x35c) == gspCellGame->midPlayerCell) {
            if (CellWantsPlayerEffect(cell)) {
                if (!gfx->mpPlayerEffect) {
                    SP::CreateEffectSafe(world, 0xb71008db, 0, &gfx->mpPlayerEffect);
                    gfx->mpPlayerEffect->Start(0);
                }
                gfx->mpPlayerEffect->SetTransform(&cell->mTransform);
            } else if (gfx->mpPlayerEffect) {
                gfx->mpPlayerEffect->Stop(0);
                gfx->mpPlayerEffect->Release();
                gfx->mpPlayerEffect = 0;
            }
        }

        SP::sUpdateElectricRibbonEffect(world, &gfx->mpElectricEffect, cell, CELL_I(cell, 0x190),
                                        CELL_I(cell, 0x174));
        SP::sUpdateChargingEffect(world, &gfx->mpChargingEffect, key, effects, &cell->mTransform,
                                  CELL_B(cell, 0x18a), cell->field_160);

        int poisonLevel;
        if (key->instanceID == 0)
            poisonLevel = 0;
        else {
            cCellResource* res = GetCellResource(*key);
            if (gspCellGame->mAvatarCellIndex != cell->mIndex)
                poisonLevel = 1;
            else if (res->field_1218 <= 2)
                poisonLevel = 1;
            else
                poisonLevel = res->field_1218 > 4 ? 3 : 2;
        }
        SP::sUpdatePoisonReleaseEffect(world, &gfx->mpPoisonEffect, cell, key, &cell->mVisualTransform,
                                       poisonLevel, CELL_B(cell, 0x1ac),
                                       SP::GetScaleDifferenceWithPlayer(cell) <= 1,
                                       cell->mIndex == gspCellGame->mAvatarCellIndex);
        FUN_00e63bf0(cell, world, &gfx->mpEffect9c, &cell->mTransform, CELL_B(cell, 0x18b));
        CompactEffects(cell, gfx);

        bool isTarget = cell->mIndex == gspCellGame->field_51b0;
        FUN_00e61050(world, &gfx->mpEffect8c, &cell->mTransform, effects,
                     key->instanceID == 0 ? -1 : GetCellResource(*key)->field_128c, isTarget);
        FUN_00e67510(world, &gfx->mpEffect90, &cell->mVisualTransform, &cell->mTransform, effects, 6,
                     CELL_B(cell, 0x390));
        FUN_00e67510(world, &gfx->mpEffect94, &cell->mVisualTransform, &cell->mTransform, effects, 7,
                     CELL_B(cell, 0x391));
        FUN_00e660e0(cell, gfx);
    }

    FUN_00e6c330();
    FUN_00e63ac0(gspCellGfx->field_161dc);
    FUN_00e831a0(gspCellGfx->field_40, ((cSPFluidParticles*)gspCellGame->mpFluidParticles)->field_1c210,
                 ((cSPFluidParticles*)gspCellGame->mpFluidParticles)->field_1bd60);
}

}  // namespace SP
