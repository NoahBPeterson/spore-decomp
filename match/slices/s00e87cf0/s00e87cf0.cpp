// Slice s00e87cf0: SP::cCityTerritoryView::UpdateSelection (0x00e87db0, 2113 bytes, __thiscall, virtual slot 0x74).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (inline fsin/fcos; no EH frame, no security cookie: /GS-).
//
// The retail layout differs from the 2008 PDB: +0x0c object view, +0x34 placement state (1/2/3), +0x38 the
// territory centre (Vector3), +0x44 the smoothed ring radius. Every frame it re-reads the centre and the
// state from the object, eases the radius toward the object's radius (10 percent per call), makes sure the
// two ring effects (ids 0x243a1dc / 0x243a1dd) exist (creating the first one when missing: game mode
// 0x1654c05 picks one of two effects by placement state, plus a second one when the player-inventory
// flag is set), then builds two closed rings of (n+1) points around the centre. n is the tuning's ring
// sample count (3..500, else 500). Ring A is the circle of the current radius, ring B a circle of
// radius 100 tilted by the quaternion that takes +Z to the centre direction; both are projected onto the
// planet and pushed outward by the tuning's ring height offset. Finally both effects get their points.
typedef unsigned int u32;
typedef unsigned char u8;

extern "C" double __cdecl cos(double);
extern "C" double __cdecl sin(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(cos, sin, sqrt)

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

#define PAD_VIRT(n) virtual void _v##n()

// A visual effect handle (reference counted): AddRef, Release, Start, ..., SetPoints at +0x44.
struct IEffect {
    virtual void AddRef();                                      // +0x00
    virtual void Release();                                     // +0x04
    virtual void Start(int flags);                              // +0x08
    PAD_VIRT(3); PAD_VIRT(4); PAD_VIRT(5); PAD_VIRT(6); PAD_VIRT(7); PAD_VIRT(8); PAD_VIRT(9);
    PAD_VIRT(10); PAD_VIRT(11); PAD_VIRT(12); PAD_VIRT(13); PAD_VIRT(14); PAD_VIRT(15); PAD_VIRT(16);
    virtual void SetPoints(int kind, const float* data, int count);   // +0x44
};

// Out-of-line AutoRefCount<IEffect>-style handle (operator= is not inlined at its use).
struct EffectRef {
    IEffect* mp;
    EffectRef& operator=(IEffect* p);                           // 0x00b5f950
};

// The object's position/radius interface (embedded at +0x34 of the object).
struct IObjectBounds {
    PAD_VIRT(0); PAD_VIRT(1); PAD_VIRT(2); PAD_VIRT(3); PAD_VIRT(4); PAD_VIRT(5); PAD_VIRT(6);
    PAD_VIRT(7); PAD_VIRT(8); PAD_VIRT(9); PAD_VIRT(10);
    virtual const Vector3* GetPosition();                       // +0x2c
    PAD_VIRT(12); PAD_VIRT(13); PAD_VIRT(14); PAD_VIRT(15); PAD_VIRT(16); PAD_VIRT(17); PAD_VIRT(18);
    PAD_VIRT(19); PAD_VIRT(20); PAD_VIRT(21); PAD_VIRT(22); PAD_VIRT(23); PAD_VIRT(24); PAD_VIRT(25);
    PAD_VIRT(26); PAD_VIRT(27);
    virtual float GetRadius();                                  // +0x70
};

// The object found by Cast(0x2450023).
struct cTerritoryObject {
    PAD_VIRT(0); PAD_VIRT(1); PAD_VIRT(2); PAD_VIRT(3); PAD_VIRT(4); PAD_VIRT(5); PAD_VIRT(6);
    PAD_VIRT(7); PAD_VIRT(8); PAD_VIRT(9); PAD_VIRT(10); PAD_VIRT(11); PAD_VIRT(12); PAD_VIRT(13);
    PAD_VIRT(14); PAD_VIRT(15); PAD_VIRT(16); PAD_VIRT(17); PAD_VIRT(18); PAD_VIRT(19); PAD_VIRT(20);
    PAD_VIRT(21);
    virtual bool IsAlternate();                                 // +0x58
    u32 pad04[(0x34 - 4) / 4];
    IObjectBounds mBounds;                                      // +0x34
    u32 pad38[(0xa6 - 0x38) / 4];
    char pad_a4[2];
    bool mbHasAlternate;                                        // +0xa6
    char pad_a7[(0x110 - 0xa7)];
    bool mbHasInventoryEffect;                                  // +0x110
};

struct cSpatialObjectView {
    // vtable slot 46 (+0xb8)
    PAD_VIRT(0); PAD_VIRT(1); PAD_VIRT(2); PAD_VIRT(3); PAD_VIRT(4); PAD_VIRT(5); PAD_VIRT(6);
    PAD_VIRT(7); PAD_VIRT(8); PAD_VIRT(9); PAD_VIRT(10);
    virtual void* GetVisible();                                 // +0x2c
    PAD_VIRT(12); PAD_VIRT(13);
    PAD_VIRT(14); PAD_VIRT(15); PAD_VIRT(16); PAD_VIRT(17); PAD_VIRT(18); PAD_VIRT(19); PAD_VIRT(20);
    PAD_VIRT(21); PAD_VIRT(22); PAD_VIRT(23); PAD_VIRT(24); PAD_VIRT(25); PAD_VIRT(26); PAD_VIRT(27);
    PAD_VIRT(28); PAD_VIRT(29); PAD_VIRT(30); PAD_VIRT(31); PAD_VIRT(32); PAD_VIRT(33); PAD_VIRT(34);
    PAD_VIRT(35); PAD_VIRT(36); PAD_VIRT(37); PAD_VIRT(38); PAD_VIRT(39); PAD_VIRT(40); PAD_VIRT(41);
    PAD_VIRT(42); PAD_VIRT(43); PAD_VIRT(44); PAD_VIRT(45);
    virtual cTerritoryObject* Cast(u32 typeId);                 // +0xb8
    cSpatialObjectView();                                       // 0x00e92af0 (not defined here)
    void Construct();                                           // out-of-line base constructor, 0x00e92af0
    ~cSpatialObjectView();                                      // 0x00e92660 (not defined here)
    void Init(void* owner);                                     // 0x00e92910
    void HandleSimulationUpdate(void* a, void* b);              // 0x00e92ca0
    void StopEffect(u32 id, bool bImmediate);                   // 0x00c8ad30
    IEffect* GetEffect(u32 id);                                 // 0x00c888e0
    bool HasEffect(u32 id);                                     // 0x00c88910 (PDB: GetEffect)
    IEffect* CreateEffect(u32 key, int flags, u32 id);          // 0x00c8b060
    bool CheckEffectMode(u32 a, u32 b, int c, int d);           // 0x00c8b220
    void SetEffectFloat(u32 id, float v);                       // 0x00c88a00
    void SetEffectFloat2(u32 id, float v);                      // 0x00c8a020
    void SetIsVisible(bool b);                                  // 0x00e889f0
    bool IsVisible();                                           // 0x00e88a10
};

struct cPlanetModel {
    void ProjectToSurface(Vector3* dst, const Vector3* src);    // 0x00b81630
};
struct cSPSpaceColonyTuning {
    float GetRingHeightOffset();                                // 0x010298b0
    int GetRingSamplePointCount();                              // 0x01029870
};
struct cPlayerInventory {
    void Refresh();                                             // 0x00ff3f00 (result unused)
};
struct cSPSimulatorSpaceGame {
    cPlayerInventory* GetPlayerInventory();                     // 0x00a1ad60
};

u32 __cdecl GetCurrentGameMode();                                              // 0x00b5b800
cSPSimulatorSpaceGame* __cdecl SpaceGameGet();                                 // 0x01002bd0
cSPSpaceColonyTuning* __cdecl GetSpaceColonyTuning();                          // 0x01029790
cPlanetModel* __cdecl PlanetModel();                                           // 0x00b3d350
void __cdecl QuaternionFromDirections(Quaternion* out, const Vector3* from, const Vector3* to);   // 0x00698180
extern float g_ringAngleRange;                                                 // 0x016c4bc8 (2 pi)
extern const float kZero;                                                      // 0x01485378

class cCityTerritoryView {
public:
    u32 pad00[3];
    cSpatialObjectView* mpObject;       // +0x0c
    u32 pad10[(0x34 - 0x10) / 4];
    int mPlacementState;                // +0x34
    Vector3 mCenter;                    // +0x38
    float mRadius;                      // +0x44
    u32 pad48[3];

    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    virtual void vslot4();
    virtual void vslot5();
    virtual void vslot6();
    virtual void vslot7();
    virtual void vslot8();
    virtual void vslot9();
    virtual void vslot10();
    virtual void vslot11();
    virtual void vslot12();
    virtual void vslot13();
    virtual void vslot14();
    virtual void vslot15();
    virtual void vslot16();
    virtual void vslot17();
    virtual void vslot18();
    virtual void vslot19();
    virtual void vslot20();
    virtual void vslot21();
    virtual void vslot22();
    virtual void vslot23();
    virtual void vslot24();
    virtual void vslot25();
    virtual void vslot26();
    virtual void vslot27();
    virtual void vslot28();
    virtual void vslot29();
    virtual void UpdateSelection();     // +0x74
};

// @ 0x00e87db0
void cCityTerritoryView::UpdateSelection()
{
    cTerritoryObject* obj = mpObject ? mpObject->Cast(0x2450023) : 0;

    mCenter = *obj->mBounds.GetPosition();

    int state = 1;
    if (obj->mbHasAlternate)
        state = obj->IsAlternate() ? 2 : 3;

    if (state != mPlacementState || obj->mBounds.GetRadius() != mRadius) {
        mpObject->StopEffect(0x243a1dc, true);
        mpObject->StopEffect(0x243a1dd, true);
        const float oldRadius = mRadius;
        mPlacementState = state;
        mRadius = (obj->mBounds.GetRadius() - oldRadius) * 0.1f + oldRadius;
    }

    IEffect* ring = mpObject->GetEffect(0x243a1dc);
    if (ring)
        ring->AddRef();
    EffectRef second;
    second.mp = mpObject->GetEffect(0x243a1dd);
    if (second.mp)
        second.mp->AddRef();

    if (ring == 0) {
        if (GetCurrentGameMode() == 0x1654c05) {
            u32 effectKey;
            if (mPlacementState == 2) {
                effectKey = 0x849a5ac3;
            } else {
                effectKey = 0x43fa3907;
                if (mPlacementState == 1)
                    effectKey = 0x849a5ac3;
            }
            IEffect* created = mpObject->CreateEffect(effectKey, 0, 0x243a1dc);
            if (created) {
                created->AddRef();
                ring = created;
            }
            SpaceGameGet()->GetPlayerInventory()->Refresh();
            if (obj->mbHasInventoryEffect) {
                second = mpObject->CreateEffect(effectKey, 0, 0x243a1dd);
                second.mp->Start(0);
            }
        } else {
            IEffect* created = mpObject->CreateEffect(0x5f688fa9, 0, 0x243a1dc);
            if (created) {
                created->AddRef();
                ring = created;
            }
        }
        ring->Start(0);
    }

    const float heightOffset = GetSpaceColonyTuning()->GetRingHeightOffset();
    int count = GetSpaceColonyTuning()->GetRingSamplePointCount();
    if (count < 3 || count > 500)
        count = 500;

    const float radius = mRadius;
    Vector3 dir;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 1.0f;
    const int numFloats = count * 3 + 3;
    Quaternion q;
    QuaternionFromDirections(&q, &dir, &mCenter);
    cPlanetModel* planet = PlanetModel();
    const float step = g_ringAngleRange / (float)count;

    float innerRing[1503];
    float outerRing[1503];
    Vector3 inner, outer;

    if (count > 0) {
        const float scale = 100.0f / radius;
        const float zeroScaled = scale * kZero;
        for (int i = 0; i < count; i++) {
            const float xx = q.x * q.x;
            const float yx = q.y * q.x;
            const float zz = q.z * q.z;
            const float zx = q.z * q.x;
            const float zy = q.z * q.y;
            const float yy = q.y * q.y;
            const float wx = q.w * q.x;
            const float wz = q.w * q.z;
            const float wy = q.w * q.y;
            const double angle = (double)i * (double)step;
            const double cd = cos(angle) * (double)radius;
            const float c = (float)cd;
            const double sd = -sin(angle) * (double)radius;
            const float s = (float)sd;
            const float cs = (float)(cd * (double)scale);
            const float ss = (float)((double)scale * sd);

            Vector3 a;
            a.y = mCenter.y + (((1.0f - (zz + xx) * 2.0f) * s + ((wz + yx) * c) * 2.0f) + (zy - wx) * 0.0f);
            a.x = mCenter.x + (((1.0f - (zz + yy) * 2.0f) * c + ((yx - wz) * s) * 2.0f) + (wy + zx) * 0.0f);
            a.z = mCenter.z + ((((wx + zy) * s + (zx - wy) * c) * 2.0f) + (1.0f - (yy + xx) * 2.0f) * 0.0f);

            const float by = (((wz + yx) * cs + (zy - wx) * zeroScaled) * 2.0f + (1.0f - (zz + xx) * 2.0f) * ss);
            Vector3 b;
            b.x = mCenter.x + (((yx - wz) * ss + (wy + zx) * zeroScaled) * 2.0f + (1.0f - (zz + yy) * 2.0f) * cs);
            b.y = mCenter.y + by;
            b.z = mCenter.z + ((((zx - wy) * cs + (wx + zy) * ss) * 2.0f) + (1.0f - (yy + xx) * 2.0f) * zeroScaled);

            planet->ProjectToSurface(&inner, &a);
            planet->ProjectToSurface(&outer, &b);

            const float inv = (float)(1.0 / sqrt((double)inner.x * inner.x + ((double)inner.y * inner.y + (double)inner.z * inner.z)));
            const float ox = (inner.x * inv) * heightOffset;
            const float oy = (inner.y * inv) * heightOffset;
            const float oz = (inner.z * inv) * heightOffset;
            outer.x = ox + outer.x;
            inner.x = ox + inner.x;
            inner.y = oy + inner.y;
            inner.z = oz + inner.z;
            outer.y = outer.y + oy;
            outer.z = outer.z + oz;

            innerRing[i * 3] = inner.x;
            innerRing[i * 3 + 1] = inner.y;
            innerRing[i * 3 + 2] = inner.z;
            outerRing[i * 3] = outer.x;
            outerRing[i * 3 + 1] = outer.y;
            outerRing[i * 3 + 2] = outer.z;
        }
    }

    innerRing[count * 3] = innerRing[0];
    innerRing[count * 3 + 1] = innerRing[1];
    innerRing[count * 3 + 2] = innerRing[2];
    outerRing[count * 3] = outerRing[0];
    outerRing[count * 3 + 1] = outerRing[1];
    outerRing[count * 3 + 2] = outerRing[2];

    ring->SetPoints(0xd, innerRing, numFloats);
    if (second.mp) {
        second.mp->SetPoints(0xd, outerRing, numFloats);
        second.mp->Release();
    }
    ring->Release();
}

// ---------------------------------------------------------------------------------------------
// The rest of the city view family (0x00e87cf0 .. 0x00e88ba0).  These are the small per-view
// constructors, the __stdcall registration factories, the walls view init/update pair and the
// feedback view's construct/destruct pair.  The retail factory epilogue is `ret 4`, so they are
// declared __stdcall; every factory allocates through the named operator new at 0x00f473a0.
// ---------------------------------------------------------------------------------------------

// Placement new, inlined away: lets a factory construct an object in the block it just allocated
// without MSVC looking for a two-argument operator new.
inline void* operator new(unsigned int, void* p) { return p; }

void* __cdecl ViewAlloc(unsigned int size, const char* name, int a, int b, int c, int d);     // 0x00f473a0
void __cdecl FreeViewBuffer(void* p, int flags);                                             // 0x00572020

// Slot-3 virtual lookup used by the views to find the game object they are attached to.
struct IObjectCast {
    PAD_VIRT(0); PAD_VIRT(1); PAD_VIRT(2);
    virtual void* Cast(u32 typeId);                     // +0x0c
};

// Reference counted effect/city handle: AddRef at +0x00, Release at +0x04, detach at +0x0c.
struct IRefCounted {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
    PAD_VIRT(2);
    virtual void Detach(int force);                     // +0x0c
};

// The view vtable slots the factories drive after construction.
struct IViewVtbl {
    PAD_VIRT(0); PAD_VIRT(1); PAD_VIRT(2); PAD_VIRT(3);
    virtual void SetExpanded(bool b);                   // +0x10
    PAD_VIRT(5); PAD_VIRT(6); PAD_VIRT(7); PAD_VIRT(8);
    virtual void Init(void* owner);                     // +0x24
    PAD_VIRT(10);
    virtual void* GetVisible();                         // +0x2c
};

// The drawable returned by slot 0x2c: +0x04 is its state/visibility word.
struct IRenderable {
    PAD_VIRT(0);
    u32 mFlags;                                         // +0x04
    u32 pad08[0x11];                                    // +0x08
    float mPos4c;                                       // +0x4c
    float mPos50;                                       // +0x50
    float mPos54;                                       // +0x54
};

// One-bit view of IRenderable::mFlags (bit 0), so the reader stays a byte load.
struct IRenderableBits {
    PAD_VIRT(0);
    u8 mVisible : 1;                                    // +0x04 bit 0
    u8 mRest : 7;
};

// Gonzago's world object: the effect spawn call sits at vtable +0x70.
struct IGonzagoWorld {
    PAD_VIRT(0); PAD_VIRT(1); PAD_VIRT(2); PAD_VIRT(3); PAD_VIRT(4); PAD_VIRT(5); PAD_VIRT(6);
    PAD_VIRT(7); PAD_VIRT(8); PAD_VIRT(9); PAD_VIRT(10); PAD_VIRT(11); PAD_VIRT(12); PAD_VIRT(13);
    PAD_VIRT(14); PAD_VIRT(15); PAD_VIRT(16); PAD_VIRT(17); PAD_VIRT(18); PAD_VIRT(19); PAD_VIRT(20);
    PAD_VIRT(21); PAD_VIRT(22); PAD_VIRT(23); PAD_VIRT(24); PAD_VIRT(25); PAD_VIRT(26); PAD_VIRT(27);
    virtual void SpawnEffect(void* obj, u32 effectId, int a, float b, int c);   // +0x70
};
IGonzagoWorld* __cdecl GonzagoModelWorld();                                  // 0x00b3d520
extern float g_cityEffectScale;                                              // 0x013ef574

struct cCivilization {
    u32 pad00[0xc4 / 4];                                // +0x000
    Vector3 mPos;                                       // +0x0c4
};

// The drawable/style block reached through cCityInfo::+0x120 (its flag word is at +0x50).
struct cCityVisual {
    PAD_VIRT(0); PAD_VIRT(1); PAD_VIRT(2); PAD_VIRT(3); PAD_VIRT(4); PAD_VIRT(5); PAD_VIRT(6);
    PAD_VIRT(7); PAD_VIRT(8); PAD_VIRT(9); PAD_VIRT(10); PAD_VIRT(11); PAD_VIRT(12); PAD_VIRT(13);
    PAD_VIRT(14); PAD_VIRT(15); PAD_VIRT(16); PAD_VIRT(17); PAD_VIRT(18); PAD_VIRT(19); PAD_VIRT(20);
    PAD_VIRT(21);
    virtual bool IsFlagged();                           // +0x58
    u32 pad04[(0x50 - 4) / 4];                          // +0x04
    u32 mFlags;                                         // +0x50
};

// The object the city exposes at +0x264.
struct cCityInfo {
    u32 pad00[0x120 / 4];                               // +0x000
    cCityVisual mVisual;                                // +0x120
    cCivilization* GetCivilization();                   // 0x00bd9bf0
};

struct cCity : IRefCounted {
    u32 pad04;                                          // +0x004
    u8 pad08[0x108 - 0x08];                             // +0x008
    u8 mbFlag108;                                       // +0x108
    u8 pad109[0x25c - 0x109];                           // +0x109
    float mField25c;                                    // +0x25c
    u32 pad260;                                         // +0x260
    cCityInfo* mpInfo;                                  // +0x264
    Vector3* GetPosition(Vector3* out);                 // 0x00bec830
};

struct cSPUIMeter {
    void Shutdown(int force);                           // 0x00e06940
};

// The feedback view is a plain object whose +0 line is a data vtable word.
class cCityFeedbackView {
public:
    void** mpVtbl;                                      // +0x00
    u32 m04;                                            // +0x04
    u32 m08;                                            // +0x08
    IRefCounted* mp0c;                                  // +0x0c
    cSPUIMeter* mp10;                                   // +0x10
    cSPUIMeter* mp14;                                   // +0x14
    cSPUIMeter* mp18;                                   // +0x18

    cCityFeedbackView();                                // 0x00e88ac0
    ~cCityFeedbackView();                               // 0x00e88ae0
};
extern void* cCityFeedbackView_vtbl[];                  // 0x014862c4
extern void* cGameDataView_vtbl[];                      // 0x01455648

// Destructor-only class at 0x00e88a30 (its vtable word is 0x014608ec).
class cCityEffectView : public cSpatialObjectView {
public:
    u32 pad04[16];                                      // +0x04
    void* mp44;                                         // +0x44
    IRefCounted* mp48;                                  // +0x48
    IRefCounted* mp4c;                                  // +0x4c

    ~cCityEffectView();                                 // 0x00e88a30
};

class cCitySoundLoopView : public cSpatialObjectView {
public:
    u32 pad04[12];                                      // +0x04
    u32 mSoundHandle;                                   // +0x34
    u32 pad38;                                          // +0x38

    cCitySoundLoopView();                               // factory-inlined (no standalone symbol)
};

class cCityWallsView : public cSpatialObjectView {
public:
    u32 pad04[2];                                       // +0x04
    cSpatialObjectView* mpObject;                       // +0x0c
    u32 pad10[2];                                       // +0x10
    Vector3 mLastPos;                                   // +0x18
    u32 pad24[4];                                       // +0x24
    cCity* mpCity;                                      // +0x34
    bool mbFlag38;                                      // +0x38
    bool mbFlag39;                                      // +0x39
    bool mbFlag3a;                                      // +0x3a
    u8 pad3b;                                           // +0x3b

    cCityWallsView();                                   // 0x00e88680
    void Init(void* owner);                             // 0x00e88720
    void HandleSimulationUpdate(void* a, void* b);      // 0x00e88820
};

extern void* cCityTerritoryView_vtbl[];                 // 0x01486208

// Retail layout of the territory view, mirrored for the new entries: the vtable word sits at +0x00,
// the object view at +0x0c and the smoothed radius at +0x44.  (The committed UpdateSelection above
// was compiled against the older declaration, which reserves one extra word at the front.)
class cCityTerritoryViewRetail {
public:
    void** mpVtbl;                                      // +0x00
    u32 pad04[2];                                       // +0x04
    cSpatialObjectView* mpObject;                       // +0x0c
    u32 pad10[(0x34 - 0x10) / 4];                       // +0x10
    int mPlacementState;                                // +0x34
    Vector3 mCenter;                                    // +0x38
    float mRadius;                                      // +0x44
    u32 pad48[3];                                       // +0x48

    cCityTerritoryViewRetail();                         // 0x00e87d30
    void StopEffects4(u32 id);                          // 0x00e87cf0
};

// @ 0x00e87cf0
void cCityTerritoryViewRetail::StopEffects4(u32 id)
{
    for (int i = 0; i < 4; ++i, ++id) {
        if (mpObject->HasEffect(id))
            mpObject->StopEffect(id, false);
    }
}

// @ 0x00e87d30
cCityTerritoryViewRetail::cCityTerritoryViewRetail()
{
    ((cSpatialObjectView*)this)->Construct();
    mpVtbl = cCityTerritoryView_vtbl;
    mRadius = 0.0f;
}

// @ 0x00e87d50
cCityTerritoryViewRetail* __stdcall MakeCityTerritoryView(void* owner)
{
    void* mem = ViewAlloc(0x48, "Simulator/cCityTerritoryView", 0, 0, 0, 0);
    cCityTerritoryViewRetail* p = mem ? new (mem) cCityTerritoryViewRetail() : 0;
    ((IViewVtbl*)p)->Init(owner);
    return p;
}

// Inlined into the factory at 0x00e88620; there is no standalone sound-loop constructor.
cCitySoundLoopView::cCitySoundLoopView()
{
    mSoundHandle = 0;
}

// @ 0x00e88620
cCitySoundLoopView* __stdcall MakeCitySoundLoopView(void* owner)
{
    void* mem = ViewAlloc(0x38, "Simulator/cCitySoundLoopView", 0, 0, 0, 0);
    cCitySoundLoopView* p = mem ? new (mem) cCitySoundLoopView() : 0;
    ((IViewVtbl*)p)->Init(owner);
    return p;
}

// @ 0x00e88680
cCityWallsView::cCityWallsView()
{
    mpCity = 0;
    mbFlag38 = false;
    mbFlag39 = false;
    mbFlag3a = false;
}

// @ 0x00e88720
void cCityWallsView::Init(void* owner)
{
    cSpatialObjectView::Init(owner);
    cCity* p = owner ? (cCity*)((IObjectCast*)owner)->Cast(0xed7fc07) : 0;
    cCity* old = mpCity;
    if (p != old) {
        if (p)
            p->AddRef();
        mpCity = p;
        if (old)
            old->Release();
    }
    ((IViewVtbl*)this)->SetExpanded(mpCity->mbFlag108 == 0);
}

// @ 0x00e88790
cCityWallsView* __stdcall MakeCityWallsView(void* owner)
{
    void* mem = ViewAlloc(0x3c, "Simulator/cCityWallsView", 0, 0, 0, 0);
    cCityWallsView* p = mem ? new (mem) cCityWallsView() : 0;
    ((IViewVtbl*)p)->Init(owner);
    Vector3 pos;
    p->mLastPos = *p->mpCity->GetPosition(&pos);
    void* r = ((IViewVtbl*)p)->GetVisible();
    if (GetCurrentGameMode() != 0x1654c10)
        ((IRenderable*)r)->mFlags |= 0x20;
    return p;
}

// @ 0x00e88820
void cCityWallsView::HandleSimulationUpdate(void* a, void* b)
{
    cSpatialObjectView::HandleSimulationUpdate(a, b);
    IRenderable* r = (IRenderable*)((IViewVtbl*)this)->GetVisible();
    if (r) {
        Vector3 v;
        if (GetCurrentGameMode() == 0x1654c05) {
            cCivilization* civ = mpCity->mpInfo->GetCivilization();
            v = civ->mPos;
        } else {
            Vector3 pos;
            Vector3* q = mpCity->GetPosition(&pos);
            v = *q;
        }
        if (v.x != mLastPos.x || v.y != mLastPos.y || v.z != mLastPos.z) {
            mLastPos = v;
            IRenderable* r2 = (IRenderable*)((IViewVtbl*)this)->GetVisible();
            if (r2) {
                r2->mPos4c = v.x;
                r2->mPos50 = v.y;
                r2->mPos54 = v.z;
                cCityVisual* vis = &mpCity->mpInfo->mVisual;
                if (vis->IsFlagged())
                    r2->mFlags &= ~0x800u;
                else
                    r2->mFlags |= 0x800;
            }
        }
        u32 bit = (r->mFlags >> 0xe) & 1;
        if (bit && !mbFlag3a)
            GonzagoModelWorld()->SpawnEffect(r, 0x40969046, 0, 0.0f, 0);
        mbFlag3a = bit != 0;
    }

    bool flagged = (mpCity->mpInfo->mVisual.mFlags & 0x800) == 0x800;
    if (mpObject->CheckEffectMode(0x7d2bf7a3, 0x30e8811, flagged, 0)) {
        mpObject->SetEffectFloat(0x30e8811, g_cityEffectScale);
        mpObject->SetEffectFloat2(0x30e8811, mpCity->mField25c);
    }
    cCityVisual* vis = &mpCity->mpInfo->mVisual;
    vis->mFlags &= ~0x800u;
}

// @ 0x00e889f0
void cSpatialObjectView::SetIsVisible(bool b)
{
    IRenderable* p = (IRenderable*)GetVisible();
    if (!p)
        return;
    if (b) {
        p->mFlags |= 1;
        return;
    }
    p->mFlags &= ~1u;
}

// @ 0x00e88a10
bool cSpatialObjectView::IsVisible()
{
    IRenderableBits* p = (IRenderableBits*)GetVisible();
    if (p)
        return p->mVisible;
    return false;
}

// @ 0x00e88a30
cCityEffectView::~cCityEffectView()
{
    if (mp44)
        FreeViewBuffer(mp44, 0);
    if (mp48) {
        mp48->Detach(0);
        IRefCounted* p = mp48;
        if (p) {
            mp48 = 0;
            p->Release();
        }
    }
    if (mp4c) {
        mp4c->Detach(0);
        IRefCounted* p = mp4c;
        if (p) {
            mp4c = 0;
            p->Release();
        }
    }
    if (mp4c)
        mp4c->Release();
    if (mp48)
        mp48->Release();
}

// @ 0x00e88ac0
cCityFeedbackView::cCityFeedbackView()
{
    m08 = 0;
    m04 = 0;
    mpVtbl = cCityFeedbackView_vtbl;
    mp0c = 0;
    mp10 = 0;
    mp14 = 0;
    mp18 = 0;
}

// @ 0x00e88ae0
cCityFeedbackView::~cCityFeedbackView()
{
    mpVtbl = cCityFeedbackView_vtbl;
    if (mp0c) {
        IRefCounted* p = mp0c;
        mp0c = 0;
        p->Release();
    }
    if (mp10) {
        mp10->Shutdown(1);
        cSPUIMeter* p = mp10;
        if (p) {
            mp10 = 0;
            ((IRefCounted*)p)->Release();
        }
    }
    if (mp14) {
        mp14->Shutdown(1);
        cSPUIMeter* p = mp14;
        if (p) {
            mp14 = 0;
            ((IRefCounted*)p)->Release();
        }
    }
    if (mp18) {
        mp18->Shutdown(1);
        cSPUIMeter* p = mp18;
        if (p) {
            mp18 = 0;
            ((IRefCounted*)p)->Release();
        }
    }
    if (mp18)
        ((IRefCounted*)mp18)->Release();
    if (mp14)
        ((IRefCounted*)mp14)->Release();
    if (mp10)
        ((IRefCounted*)mp10)->Release();
    if (mp0c)
        mp0c->Release();
    mpVtbl = cGameDataView_vtbl;
}

// @ 0x00e88ba0
cCityFeedbackView* __stdcall MakeCityFeedbackView(void* owner)
{
    IRefCounted* src;
    if (owner == 0 || (src = (IRefCounted*)((IObjectCast*)owner)->Cast(0xee9b2232)) == 0)
        return 0;
    void* mem = ViewAlloc(0x1c, "Simulator/cCityFeedbackView", 0, 0, 0, 0);
    cCityFeedbackView* p = mem ? new (mem) cCityFeedbackView() : 0;
    IRefCounted* old = p->mp0c;
    if (src != old) {
        src->AddRef();
        p->mp0c = src;
        if (old)
            old->Release();
    }
    return p;
}
