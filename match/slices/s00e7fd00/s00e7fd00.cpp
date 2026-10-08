// Slice s00e7fd00 -- SP::sLoadLevel (cell stage): tears down the previous cell level (cells, ui windows,
// effects, gfx objects, callbacks), then sets up camera / extents / scale for the new level and re-targets
// the avatar cell and the level-intro ui image.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (cell TU; no /EHsc)
//
// Static register-convention helpers of the original TU (their implicit register argument is modeled as an
// ordinary first argument here, see nonmatching.txt): 0x00e7e130 (cell in EDI), 0x00e66010 (cell handle in
// EAX), 0x00e50810 (position in ESI), 0x00e78b80 / 0x00e78b20 (position ECX, group EDX, avatar EDI).
#include "types.h"
typedef uint32_t uint32;

// ---------------------------------------------------------------- math / resources
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
};

struct ResourceKey {
    uint32 instanceID;   // +0x0
    uint32 typeID;       // +0x4
    uint32 groupID;      // +0x8
    ResourceKey() {}
};

struct cBoundingBox { Vector3 lower; Vector3 upper; };

struct cIVisualEffect {                       // EA::Swarm::cIVisualEffect
    virtual int AddRef();                     // +0x00
    virtual int Release();                    // +0x04
    virtual bool Start(int flags);            // +0x08
    virtual bool Stop(int flags);             // +0x0c
};

// Effects world / sound world interfaces: only slot 13 (+0x34) is used here.
struct IGfxSystem {
    virtual int s0(); virtual int s1(); virtual int s2(); virtual int s3();
    virtual int s4(); virtual int s5(); virtual int s6(); virtual int s7();
    virtual int s8(); virtual int s9(); virtual int s10(); virtual int s11();
    virtual int s12();
    virtual void Reset();                     // +0x34
};

// ---------------------------------------------------------------- cell scale table (0x01483c30)
struct cCellScaleInfo {                       // Simulator::Cell::cCellScaleInfo (0x1c bytes)
    int scale;                                // +0x00
    int requiredFood;                         // +0x04
    int field_8;
    float field_C;
    float field_10;
    uint32 field_14;
    float field_18;
};

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

// ---------------------------------------------------------------- pools / game objects
struct cObjectPool {                          // cSPObjectPoolT<T, N>
    void* GetSafe(int index);                 // 0x00b721d0 (null when the handle is stale)
    void* Get(int index);                     // 0x00b72210
    void Free(int index);                     // 0x00b72260
    void Clear();                             // 0x00b72110
    int Begin();                              // 0x00e31100
    void* Next(int* pIterator);               // 0x00b72230
};

struct cCell {                                // pool element at cCellGame+0x1c (retail offsets)
    int mIndex;                               // +0x000 (pool handle)
    uint32 pad004[(0x108 - 0x04) / 4];
    uint32 field_108;                         // +0x108
    uint32 pad10c[(0x248 - 0x10c) / 4];
    int field_248;                            // +0x248
    uint32 pad24c[(0x35c - 0x24c) / 4];
    uint32 field_35c;                         // +0x35c
    uint32 field_360;                         // +0x360
    int field_364;                            // +0x364
    uint32 pad368;
    int field_36c;                            // +0x36c
    int field_370;                            // +0x370
};

struct cEffectHolder {                        // pool element at cCellGame+0x38
    uint32 pad[0x300 / 4];
    cIVisualEffect* mpEffect;                 // +0x300
};

struct cCbVector {                            // eastl::vector<pair<bool(*)(...), void*>> (8-byte elements)
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void erase(char* first, char* last);      // 0x00d018d0
};

struct cSerializableData {
    uint32 pad[0x10 / 4];
    ResourceKey mIntroKey;                    // +0x10
    int mLevel;                               // +0x1c  (overlaps mIntroKey.groupID? no: key is 0xc bytes, +0x1c follows)
};

struct cCellGame {
    uint32 pad0000[0x1c / 4];
    cObjectPool mCells;                       // +0x001c
    uint32 pad0020[(0x38 - 0x20) / 4];
    cObjectPool mEffectPool;                  // +0x0038
    uint32 pad003c[(0x54 - 0x3c) / 4];
    cObjectPool mUpdatePool;                  // +0x0054
    uint32 pad0058[(0x8c - 0x58) / 4];
    cObjectPool mLinkPool;                    // +0x008c
    uint32 pad0090[(0xa8 - 0x90) / 4];
    cObjectPool mMiscPool;                    // +0x00a8
    uint32 pad00ac[(0x40fc - 0xac) / 4];
    int midPlayerCell;                        // +0x40fc
    int field_4100;                           // +0x4100
    void* mpFluidParticles;                   // +0x4104
    uint32 pad4108;
    bool mbEditor;                            // +0x410c
    uint32 field_4110;                        // +0x4110
    uint32 field_4114;                        // +0x4114
    uint32 field_4118;                        // +0x4118
    int mAvatarCellIndex;                     // +0x411c
    uint32 pad4120[2];
    cCbVector mCallbacks;                     // +0x4128
    uint32 pad4134[(0x514c - 0x4134) / 4];
    float mfExtentHalf;                       // +0x514c
    float mfExtentHalf2;                      // +0x5150
    uint32 pad5154;
    int field_5158;                           // +0x5158
    uint32 pad515c[(0x5190 - 0x515c) / 4];
    cSerializableData* mpSerializableData;    // +0x5190
    uint32 pad5194[(0x51d4 - 0x5194) / 4];
    int field_51d4;                           // +0x51d4
    bool field_51d8;                          // +0x51d8
};

struct cGfxObjVec {                           // vector of 0x74-byte gfx objects
    struct Obj { uint32 pad[0x70 / 4]; cIVisualEffect* mpEffect; };
    Obj* mpBegin;
    Obj* mpEnd;
    Obj* mpCapacity;
    void erase(Obj* first, Obj* last);        // 0x00e65180
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cCellGfx {
    uint32 pad0000[0x4c / 4];
    float field_4c;                           // +0x4c
    uint32 pad0050[(0x161ac - 0x50) / 4];
    IGfxSystem* mpSystemA;                    // +0x161ac
    uint32 pad161b0[(0x161bc - 0x161b0) / 4];
    IGfxSystem* mpSystemB;                    // +0x161bc
    uint32 pad161c0[2];
    IGfxSystem* mpSystemC;                    // +0x161c8
    uint32 pad161cc[4];
    cGfxObjVec mObjects;                      // +0x161dc
    uint32 pad161e8[(0x16258 - 0x161e8) / 4];
    int field_16258;                          // +0x16258
};

struct cSPUILayout {
    void SetVisibility(bool v);               // 0x00810590
    void* FindWindowByID(uint32 id, bool recursive);   // 0x008105b0
};

struct cCellUI {
    uint32 pad0000[0x48 / 4];
    Vector3 mV48;                             // +0x48
    Vector3 mV54;                             // +0x54
    Vector3 mV60;                             // +0x60
    Vector3 mV6c;                             // +0x6c
    Vector3 mV78;                             // +0x78
    float field_84;                           // +0x84
    uint32 pad0088[2];
    cSPUILayout* mpLayout;                    // +0x90
    uint32 pad0094[2];
    cObjectPool mWindows;                     // +0x9c
    uint32 pad00a0[(0xb8 - 0xa0) / 4];
    int field_b8;                             // +0xb8
    float field_bc;                           // +0xbc
    uint32 pad00c0[(0xe0 - 0xc0) / 4];
    int field_e0;                             // +0xe0
    uint32 pad00e4[(0xf4 - 0xe4) / 4];
    float field_f4;                           // +0xf4
    float field_f8;                           // +0xf8
    uint32 pad00fc[(0x908 - 0xfc) / 4];
    float field_908;                          // +0x908
};

struct cLevelInfo {                           // returned by 0x00e4ce40
    uint32 pad0;
    uint32 field_4;                           // +0x04
    uint32 pad8[(0x18 - 0x08) / 4];
    uint32 field_18;                          // +0x18
    uint32 pad1c[(0xb8 - 0x1c) / 4];
    float field_b8;                           // +0xb8
    float field_bc;                           // +0xbc
};

struct cHandleRef {                           // 4-byte handle holder (ctor 0x00743b50, dtor 0x00e82130)
    int mp;
    cHandleRef();                             // 0x00743b50
    ~cHandleRef();                            // 0x00e82130 (drops the refcount at +0xc)
};

extern cCellGame* gspCellGame;                // 0x016b3c04
extern cCellGfx* gspCellGfx;                  // 0x016b3c08
extern cCellUI* gspCellUI;                    // 0x016b3c0c
extern Vector3 gCellPosition;                 // 0x015a7d3c
extern cBoundingBox gCellGameExtents;         // 0x016b3c88
extern cSPUILayout* gUILayouts[64];           // 0x016b4178
extern char gUILayoutUsed[64];                // 0x016b4278

// ---------------------------------------------------------------- callees
void SetGlobalAudioParameter(uint32 id, float value);                          // 0x00e82690
void UpdateCellState(cCell* c, float t, int a, int b);                         // 0x00e7e130 (cell in EDI)
void FUN_00e86980(uint32 a, uint32 b);                                         // 0x00e86980
void FUN_00bbb210(void* fluid, int handle);                                    // 0x00bbb210 (via thunk 0x00bbbde0)
void ReleaseCellModel(int handle, int flag);                                   // 0x00e66010 (handle in EAX)
void ClearFluidParticles(void* fluid);                                         // 0x00bbb0e0
void FUN_00e86b60();                                                           // 0x00e86b60
cLevelInfo* GetLevelInfo(cHandleRef* out);                                     // 0x00e4ce40
uint32 GetCellUint(int index);                                                 // 0x00e4cce0
void SetCameraPosition(Vector3* pos, float extent);                            // 0x00e750c0
void UpdateExtents(Vector3* pos);                                              // 0x00e50810 (position in ESI)
void __stdcall InitVisibleCells(int scale, cCbVector* callbacks, int flag);    // 0x00e7d370
void __fastcall FUN_00e78b80(Vector3* pos, int group, float f, int avatar);    // 0x00e78b80 (avatar in EDI)
void FUN_00e78b20(Vector3* pos, int group, float f, int avatar);               // 0x00e78b20 (pos ECX, group EDX)
void FUN_00e5f360();                                                           // 0x00e5f360
void SetWindowImage(void* window, const ResourceKey* key, uint32 color);       // 0x00807bb0
uint32 GetCellKey(uint32 value, cHandleRef* tmp);                              // 0x00e4cc40 (-> 0x00e823a0)
void FUN_00e78c00(cCell* cell, uint32 key);                                    // 0x00e78c00
void sHatchFromIce_Start();                                                    // 0x00e6ecb0
void FUN_00e6eb60();                                                           // 0x00e6eb60

// Re-derive the playfield extents around the camera position (the retail code inlines this body here and
// calls the out-of-line copy at 0x00e50810 once before).
__forceinline void SetExtents(const Vector3& pos)
{
    cBoundingBox box;
    box.lower = Vector3(-10.0f, -7.5f, 0.0f);
    box.upper = Vector3(10.0f, 7.5f, 0.0f);
    gCellGameExtents = box;
    gCellGameExtents.upper = gCellGameExtents.upper + pos;
    gCellGameExtents.lower = gCellGameExtents.lower + pos;
}

namespace SP {

// @ 0x00e7fd00
void sLoadLevel(int level, int param2, int param3, int param4, bool bGameMode, uint32 param6, bool bHatch)
{
    SetGlobalAudioParameter(0x1e08f6a, 0.0f);
    SetGlobalAudioParameter(0x8a4d210e, 0.0f);
    gspCellGame->field_51d8 = false;
    gspCellGame->mAvatarCellIndex = 0;
    gspCellGame->field_51d4 = 0;

    // 1. tick every update-pool object once with a zero time step, then drop them
    int it = gspCellGame->mUpdatePool.Begin();
    while (cCell* c = (cCell*)gspCellGame->mUpdatePool.Next(&it))
        UpdateCellState(c, 0.0f, 0, 1);
    gspCellGame->mUpdatePool.Clear();

    // 2. release every cell
    it = gspCellGame->mCells.Begin();
    while (int* slot = (int*)gspCellGame->mCells.Next(&it)) {
        int handle = *slot;
        if (gspCellGame->mCells.GetSafe(handle)) {
            if (handle == gspCellGame->mAvatarCellIndex)
                gspCellGame->mAvatarCellIndex = 0;
            cCell* cell = (cCell*)gspCellGame->mCells.Get(handle);
            FUN_00e86980(cell->field_35c, cell->field_360);
            if (cell->field_364 != -1)
                FUN_00bbb210(gspCellGame->mpFluidParticles, cell->field_364);
            if (cell->field_248 != 0)
                ReleaseCellModel(handle, 1);
            int link = cell->field_370;
            if (link != 0) {
                void* linkObj = gspCellGame->mLinkPool.GetSafe(link);
                if (linkObj) {
                    cCell* peer = (cCell*)gspCellGame->mCells.GetSafe(((int*)linkObj)[3]);
                    if (peer) {
                        peer->field_370 = 0;
                        peer->field_36c = 0;
                    }
                    gspCellGame->mLinkPool.Free(link);
                }
            }
            gspCellGame->mCells.Free(handle);
        }
    }
    ClearFluidParticles(gspCellGame->mpFluidParticles);
    FUN_00e86b60();

    // 3. hide and free every ui window of the level
    it = gspCellUI->mWindows.Begin();
    while (uint32* win = (uint32*)gspCellUI->mWindows.Next(&it)) {
        cSPUILayout* layout = (cSPUILayout*)win[0x34 / 4];
        layout->SetVisibility(false);
        for (int i = 0; i < 64; i++) {
            if (gUILayouts[i] == layout) {
                gUILayoutUsed[i] = 0;
                break;
            }
        }
        gspCellUI->mWindows.Free((int)win[0]);
    }

    // 4. stop and release the effect of every effect-pool entry
    it = gspCellGame->mEffectPool.Begin();
    while (cEffectHolder* e = (cEffectHolder*)gspCellGame->mEffectPool.Next(&it)) {
        if (e->mpEffect) {
            e->mpEffect->Stop(1);
            if (e->mpEffect) {
                cIVisualEffect* fx = e->mpEffect;
                e->mpEffect = 0;
                fx->Release();
            }
        }
    }
    gspCellGame->mEffectPool.Clear();
    gspCellGame->mLinkPool.Clear();
    gspCellGame->mCallbacks.erase(gspCellGame->mCallbacks.mpBegin, gspCellGame->mCallbacks.mpEnd);
    gspCellGame->mMiscPool.Clear();

    // 5. gfx: stop and release the effect of every gfx object, then clear the vector
    for (int i = 0; i < gspCellGfx->mObjects.size(); i++) {
        cGfxObjVec::Obj* o = gspCellGfx->mObjects.mpBegin + i;
        o->mpEffect->Stop(1);
        if (o->mpEffect) {
            cIVisualEffect* fx = o->mpEffect;
            o->mpEffect = 0;
            fx->Release();
        }
    }
    gspCellGfx->mObjects.erase(gspCellGfx->mObjects.mpBegin, gspCellGfx->mObjects.mpEnd);
    gspCellGfx->field_16258 = 0;
    gspCellGfx->mpSystemB->Reset();
    gspCellGfx->mpSystemA->Reset();
    gspCellGfx->mpSystemC->Reset();

    // 6. level / game-mode bookkeeping
    cHandleRef infoRef;
    cLevelInfo* info = GetLevelInfo(&infoRef);
    gspCellGame->mbEditor = bGameMode;
    gspCellGame->field_4110 = param6;
    if (bGameMode) {
        gspCellGame->field_4114 = GetCellUint(5);
        gspCellGame->field_4118 = GetCellUint(6);
    } else {
        gspCellGame->field_4114 = info->field_4;
        gspCellGame->field_4118 = info->field_18;
    }

    // 7. ui camera reset
    gspCellUI->field_bc = 1.0f;
    gspCellUI->mV78 = Vector3(0.0f, 0.0f, 20.0f);
    gspCellUI->mV6c = gspCellUI->mV78;
    gspCellUI->field_84 = 0.0f;
    gspCellUI->field_908 = 1.0f;
    gspCellUI->field_f8 = 0.0f;
    gspCellUI->field_e0 = 0;
    gspCellUI->field_f4 = 3.5f;
    gspCellUI->mV48 = gCellPosition;
    gspCellUI->mV54 = gCellPosition;
    gspCellUI->mV60 = gCellPosition;
    gspCellUI->field_b8 = 0;

    // 8. scale of the level
    gspCellGame->mfExtentHalf = GetCellScaleInfo(level)->field_10 * 0.5f;
    gspCellGame->mfExtentHalf2 = gspCellGame->mfExtentHalf;
    gspCellGame->mpSerializableData->mLevel = level;
    ((uint32*)gspCellGame->mpSerializableData)[0x20 / 4] = param2;
    ((uint32*)gspCellGame->mpSerializableData)[0x24 / 4] = param3;
    ((uint32*)gspCellGame->mpSerializableData)[0x28 / 4] = param4;
    gspCellGfx->field_4c = 1.0f / (gspCellGame->mfExtentHalf * 2.0f);
    SetCameraPosition(&gCellPosition, gspCellGame->mfExtentHalf * 2.0f);
    UpdateExtents(&gCellPosition);
    InitVisibleCells(GetCellScaleInfo(level)->scale, &gspCellGame->mCallbacks, 1);
    SetExtents(gCellPosition);
    FUN_00e78b80(&gCellPosition, gspCellGame->midPlayerCell, info->field_b8, gspCellGame->mAvatarCellIndex);
    FUN_00e78b80(&gCellPosition, gspCellGame->field_4100, info->field_b8, gspCellGame->mAvatarCellIndex);
    FUN_00e78b20(&gCellPosition, gspCellGame->midPlayerCell, info->field_bc, gspCellGame->mAvatarCellIndex);
    gspCellGame->field_5158 = 0;
    FUN_00e5f360();

    // 9. intro image + avatar
    ResourceKey key;
    key = gspCellGame->mpSerializableData->mIntroKey;
    key.typeID = 0x2f7d0004;
    SetWindowImage(gspCellUI->mpLayout->FindWindowByID(0x3d99151, true), &key, 0xffffffff);
    cCell* avatar = (cCell*)gspCellGame->mCells.Get(gspCellGame->mAvatarCellIndex);
    cHandleRef keyRef;
    FUN_00e78c00(avatar, GetCellKey(avatar->field_108, &keyRef));
    if (!gspCellGame->mbEditor && bHatch)
        sHatchFromIce_Start();
    else
        FUN_00e6eb60();
}

}   // namespace SP
