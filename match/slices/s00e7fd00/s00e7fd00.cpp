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

// Three ints, copied as a unit by the cell message path (00e809a0) and the intro-key
// resource (the same 12 bytes are a ResourceKey in sLoadLevel).
struct Int3 {
    int x, y, z;
    Int3() {}
    Int3(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
};

// cvtss2si with the current MXCSR rounding mode, as the original's inlined ROUND helper.
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

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
    ResourceKey mIntroKey;                    // +0x10 (also the Int3 written by 00e809a0)
    int mLevel;                               // +0x1c
    uint32 field_20;                          // +0x20
    uint32 field_24;                          // +0x24
    uint32 field_28;                          // +0x28
    int field_2c;                             // +0x2c
    int field_30;                             // +0x30
    unsigned char pad34[0x74 - 0x34];
    int field_74;                             // +0x74 (accumulated millisecond clock)
    unsigned char pad78[0xe2 - 0x78];
    bool field_e2;                            // +0xe2
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
    int field_515c;                           // +0x515c (paused / no time step)
    int field_5160;                           // +0x5160 (updated frame counter)
    uint32 pad5164[(0x5190 - 0x5164) / 4];
    cSerializableData* mpSerializableData;    // +0x5190
    uint32 pad5194[(0x51d4 - 0x5194) / 4];
    int field_51d4;                           // +0x51d4
    bool field_51d8;                          // +0x51d8
    bool field_51d9;                          // +0x51d9 (reload level after the step)
    unsigned char pad51da[0x51e0 - 0x51da];
    int field_51e0;                           // +0x51e0 (update state: 0 normal, 1 win, 2 quit)
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

class cSPUILayout { public:
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

// ---------------------------------------------------------------- cell update / message handlers (00e806b0, 00e809a0)
struct cTriggerTarget {                       // vtable-bearing object embedded at cTriggerMgr+0x04
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void SetTime(int timeMs, int dtMs);   // +0x38
};
struct cTriggerMgr {
    uint32 field_0;                           // +0x00
    cTriggerTarget mTarget;                   // +0x04
};

struct cResource {                            // resource object returned by the cursor provider
    uint32 field_0;                           // +0x00
    uint32 field_4;                           // +0x04
    uint32 field_8;                           // +0x08
    int* mpBegin;                             // +0x0c (IntVector data)
    int* mpEnd;                               // +0x10
    int* mpCapacity;                          // +0x14
    void resize(unsigned count);              // 0x007eb820
};

struct cResourceProvider {                    // DAT_015fd910
    cResource* Find(int group, int index);    // 0x00ba5410
    cResource* Create(int group, int index);  // 0x007ec160
};

struct cIntroState {                          // object at 0x016b3cb8
    void Load(void* data);                    // 0x006ffe00
};

cTriggerMgr* GetTriggerMgr();                                                  // 0x00b3d4d0
cTriggerMgr* FUN_00b3d3f0();                                                   // 0x00b3d3f0
void FUN_00e84bf0();                                                           // 0x00e84bf0
void FUN_00e82de0(int timeMs, int dtMs);                                       // 0x00e82de0
bool FUN_00e82c70();                                                           // 0x00e82c70
void* FUN_0067de20();                                                          // 0x0067de20 (SP::CheatManager)
void* FUN_0067dd20();                                                          // 0x0067dd20
void FUN_00e5b790(float t);                                                    // 0x00e5b790
void FUN_00e7f3a0(float t);                                                    // 0x00e7f3a0 (SP::sUpdateGame)
void FUN_00e73f60();                                                           // 0x00e73f60 (SP::sUpdateGfx)
void FUN_00e53b00(float t);                                                    // 0x00e53b00
void FUN_00e600a0(float t, char mode);                                         // 0x00e600a0 (CellCamera_Update)
void FUN_00e6c9f0(float t);                                                    // 0x00e6c9f0 (SP::sUpdateUI)
bool FUN_00e7f550();                                                           // 0x00e7f550
void FUN_00e82c80(int msg, int* out0, char* outByte, int* outInt, Int3* outVec); // 0x00e82c80
int  FUN_00e394f0(int id, Int3* a, Int3* b, Int3* c, Int3* d);                 // 0x00e394f0
void FUN_00e624b0(Int3 key);                                                   // 0x00e624b0 (12 bytes by value)
void FUN_00e4fbb0();                                                           // 0x00e4fbb0 (vector pointer in EAX)
int  __fastcall FUN_00e51430(int level);                                       // 0x00e51430 (level in ECX)
void* FUN_0067de90();                                                          // 0x0067de90
void* FUN_0067dcc0();                                                          // 0x0067dcc0 (SP::MessageServer)

// Trigger targets receive the millisecond clock through their virtual slot at +0x38.
static inline void TriggerSetTime(cTriggerMgr* mgr, int timeMs, int dtMs)
{
    mgr->mTarget.SetTime(timeMs, dtMs);
}

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

// @ 0x00e806b0
void sUpdate(float dt, float time)
{
    FUN_00e84bf0();
    int state = gspCellGame->field_51e0;

    if (state != 0) {
        if (dt == 0.0f)
            return;
        switch (state) {
        case 1:
            if (FUN_00e82c70()) {
                void* obj = FUN_0067dd20();
                ((void (__thiscall*)(void*))(*(void***)obj)[0x40 / 4])(obj);
            }
            break;
        case 2:
            if (FUN_00e82c70()) {
                void* obj = FUN_0067de20();
                ((void (__thiscall*)(void*, const char*))(*(void***)obj)[0x20 / 4])(obj, "quit");
            }
            break;
        }
        return;
    }

    if (gspCellGame->field_515c == 0 && dt != 0.0f) {
        gspCellGame->field_5160++;
        FUN_00e82de0(RoundToInt(time * 1000.0f), RoundToInt(dt * 1000.0f));

        cTriggerMgr* mgr = GetTriggerMgr();
        TriggerSetTime(mgr, RoundToInt(time * 1000.0f), RoundToInt(dt * 1000.0f));
        mgr = FUN_00b3d3f0();
        TriggerSetTime(mgr, RoundToInt(time * 1000.0f), RoundToInt(dt * 1000.0f));

        int* pClock = &gspCellGame->mpSerializableData->field_74;
        *pClock += RoundToInt(dt * 1000.0f);
        FUN_00e5b790(dt);
        FUN_00e7f3a0(dt);
        if (gspCellGame->field_51d8) {
            cSerializableData* ser = gspCellGame->mpSerializableData;
            bool bHatch = gspCellGame->field_51d9;
            sLoadLevel(ser->mLevel, ser->field_20, ser->field_24, ser->field_28,
                       gspCellGame->mbEditor, gspCellGame->field_4110, false);
            if (bHatch)
                FUN_00e7f550();
            FUN_00e7f3a0(dt);
        }
        FUN_00e73f60();
        FUN_00e53b00(dt);
        FUN_00e600a0(dt, 0);
        FUN_00e6c9f0(dt);
        return;
    }

    cTriggerMgr* mgr = GetTriggerMgr();
    TriggerSetTime(mgr, RoundToInt(time * 1000.0f), 0);
    mgr = FUN_00b3d3f0();
    TriggerSetTime(mgr, RoundToInt(time * 1000.0f), 0);
    ((cIntroState*)0x016b3cb8)->Load((void*)0x016b4378);
    FUN_00e600a0(time, 1);
    FUN_00e6c9f0(time);
}

}   // namespace SP

// @ 0x00e809a0
bool FUN_00e809a0(int param_1, void* msg)
{
    (void)param_1;
    char outByte;
    int out0;
    int outInt;
    Int3 v(0, 0, 0);
    FUN_00e82c80((int)msg, &out0, &outByte, &outInt, &v);
    if (out0 != 0x1100000)
        return true;

    if (outByte == 0) {
        gspCellGame->mpSerializableData->field_2c =
            FUN_00e51430(gspCellGame->mpSerializableData->mLevel) - outInt;
        gspCellGame->mpSerializableData->field_e2 = false;
        Int3 a(0, 0, 0);
        Int3 b(0, 0, 0);
        Int3 c(0, 0, 0);
        FUN_00e394f0(0xdbd1b537, &v, &c, &b, &a);

        cResource* res = ((cResourceProvider*)FUN_0067de90())->Find(7, 7);
        if (!res) {
            res = ((cResourceProvider*)FUN_0067de90())->Create(7, 0);
            if (!res)
                goto skip;
            res->resize(0xc);
            res->mpBegin[4] = 7;
        }
        res->mpBegin[1] = v.y;
        res->mpBegin[2] = v.x;
        res->mpBegin[3] = v.z;
    }

skip:
    FUN_00e624b0(v);
    // normalize() reads its vector pointer from EAX (register-convention helper).
    __asm {
        mov eax, dword ptr [gspCellGame]
        mov eax, dword ptr [eax + 0x5190]
        add eax, 0x34
    }
    FUN_00e4fbb0();
    {
        cSerializableData* ser = gspCellGame->mpSerializableData;
        ser->mIntroKey.instanceID = (uint32)v.x;
        ser->mIntroKey.typeID = (uint32)v.y;
        ser->mIntroKey.groupID = (uint32)v.z;
    }
    gspCellGame->mpSerializableData->field_30 =
        FUN_00e51430(gspCellGame->mpSerializableData->mLevel);
    SP::sLoadLevel(gspCellGame->mpSerializableData->mLevel,
                   gspCellGame->mpSerializableData->field_20,
                   gspCellGame->mpSerializableData->field_24,
                   gspCellGame->mpSerializableData->field_28,
                   gspCellGame->mbEditor, gspCellGame->field_4110, false);
    {
        void* server = FUN_0067dcc0();
        ((void (__thiscall*)(void*, int, int, int))(*(void***)server)[0x14 / 4])(
            server, 0x6579712, 0x26b05664, 0);
    }
    return true;
}
