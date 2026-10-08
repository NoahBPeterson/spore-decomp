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
    PAD_VIRT(7); PAD_VIRT(8); PAD_VIRT(9); PAD_VIRT(10); PAD_VIRT(11); PAD_VIRT(12); PAD_VIRT(13);
    PAD_VIRT(14); PAD_VIRT(15); PAD_VIRT(16); PAD_VIRT(17); PAD_VIRT(18); PAD_VIRT(19); PAD_VIRT(20);
    PAD_VIRT(21); PAD_VIRT(22); PAD_VIRT(23); PAD_VIRT(24); PAD_VIRT(25); PAD_VIRT(26); PAD_VIRT(27);
    PAD_VIRT(28); PAD_VIRT(29); PAD_VIRT(30); PAD_VIRT(31); PAD_VIRT(32); PAD_VIRT(33); PAD_VIRT(34);
    PAD_VIRT(35); PAD_VIRT(36); PAD_VIRT(37); PAD_VIRT(38); PAD_VIRT(39); PAD_VIRT(40); PAD_VIRT(41);
    PAD_VIRT(42); PAD_VIRT(43); PAD_VIRT(44); PAD_VIRT(45);
    virtual cTerritoryObject* Cast(u32 typeId);                 // +0xb8
    void StopEffect(u32 id, bool bImmediate);                   // 0x00c8ad30
    IEffect* GetEffect(u32 id);                                 // 0x00c888e0
    IEffect* CreateEffect(u32 key, int flags, u32 id);          // 0x00c8b060
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
