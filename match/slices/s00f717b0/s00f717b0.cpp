// Slice s00f717b0: SP::cTerrainEffectMaps registration (0x00f717b0). Creates every
// "Terrain/EffectMap/*" effect-map object and registers it with the Swarm effects manager
// (IEffectsManager::RegisterMap, vtable slot 0x88). The map classes live in an anonymous
// namespace in the original; class names/layouts come from the 2008 PDB.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <math.h>

void* operator new(unsigned int size, const char* pName, int flags, int debugFlags, int file, int line);  // 0x00f473a0

namespace {

struct cTerrainMapSet;
struct cTerrainStateMgr;
struct cViewer;

// EA::Swarm::cIMap: 12 virtual slots (IEffectMap). AddRef/Release are implemented by cMapBase.
struct cIMap {
    virtual int AddRef();
    virtual int Release();
    virtual void Start();
    virtual void Finish();
    virtual int ModificationCount();
    virtual void GetBounds();
    virtual bool PointInMap();
    virtual bool InWorldSpace();
    virtual float Height();
    virtual void Normal();
    virtual void Velocity();
    virtual void ColorAlpha();
};

// EA::RefCountTemplate<int>
struct RefCountTemplate {
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate();
    int mRefCount;
};

struct cMapBase : cIMap, RefCountTemplate {
    virtual int AddRef();
    virtual int Release();
};

struct cTerrainMapSet {
    int pad;
    int mRefCount;  // +4
};

struct cTerrainEffectMapBase : cMapBase {
    cTerrainEffectMapBase() : mMapSet(0) {}
    explicit cTerrainEffectMapBase(cTerrainMapSet* set) : mMapSet(set) {
        if (set) ++set->mRefCount;  // AutoRefCount copy: direct refcount increment
    }
    virtual int ModificationCount();
    virtual float Height();
    cTerrainMapSet* mMapSet;  // +0xc
};

struct cTerrainEffectMapHeight : cTerrainEffectMapBase {
    explicit cTerrainEffectMapHeight(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapGradient : cTerrainEffectMapBase {
    explicit cTerrainEffectMapGradient(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapNormal : cTerrainEffectMapBase {
    explicit cTerrainEffectMapNormal(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapFirstDeriv : cTerrainEffectMapBase {
    cTerrainEffectMapFirstDeriv(cTerrainMapSet* s, cTerrainStateMgr* m) : cTerrainEffectMapBase(s), mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};
struct cTerrainEffectMapAbove : cTerrainEffectMapBase {
    explicit cTerrainEffectMapAbove(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapAboveBinary : cTerrainEffectMapBase {
    explicit cTerrainEffectMapAboveBinary(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapBeach : cTerrainEffectMapBase {
    explicit cTerrainEffectMapBeach(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapBeachBinary : cTerrainEffectMapBase {
    explicit cTerrainEffectMapBeachBinary(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapCliff : cTerrainEffectMapBase {
    explicit cTerrainEffectMapCliff(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapCiffBinary : cTerrainEffectMapBase {
    explicit cTerrainEffectMapCiffBinary(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapSeaBed : cTerrainEffectMapBase {
    explicit cTerrainEffectMapSeaBed(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapSeaBedBinary : cTerrainEffectMapBase {
    explicit cTerrainEffectMapSeaBedBinary(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapLiveDead : cTerrainEffectMapBase {
    cTerrainEffectMapLiveDead(cTerrainMapSet* s, cTerrainStateMgr* m) : cTerrainEffectMapBase(s), mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};
struct cTerrainEffectMapGrass : cTerrainEffectMapBase {
    cTerrainEffectMapGrass(cTerrainMapSet* s, cTerrainStateMgr* m) : cTerrainEffectMapBase(s), mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};
struct cTerrainEffectMapFlora : cTerrainEffectMapBase {
    cTerrainEffectMapFlora(cTerrainMapSet* s, cTerrainStateMgr* m) : cTerrainEffectMapBase(s), mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};
struct cTerrainEffectMapLiveFlora : cTerrainEffectMapBase {
    cTerrainEffectMapLiveFlora(cTerrainMapSet* s, cTerrainStateMgr* m) : cTerrainEffectMapBase(s), mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};
struct cTerrainEffectMapDeadFlora : cTerrainEffectMapBase {
    cTerrainEffectMapDeadFlora(cTerrainMapSet* s, cTerrainStateMgr* m) : cTerrainEffectMapBase(s), mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};
struct cTerrainEffectMapDeadFloraColor : cTerrainEffectMapBase {
    explicit cTerrainEffectMapDeadFloraColor(cTerrainStateMgr* m) : mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};
struct cTerrainEffectMapSpecular : cTerrainEffectMapBase {
    cTerrainEffectMapSpecular(cTerrainStateMgr* m, cViewer* v) : mStateMgr(m), mViewer(v) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
    cViewer* mViewer;  // +0x14
};
struct cTerrainEffectMapColor : cTerrainEffectMapBase {
    explicit cTerrainEffectMapColor(cTerrainMapSet* s) : cTerrainEffectMapBase(s) {}
    virtual float Height();
};
struct cTerrainEffectMapWaterColor : cTerrainEffectMapBase {
    explicit cTerrainEffectMapWaterColor(cTerrainStateMgr* m) : mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};
struct cTerrainEffectMapDeadColor : cTerrainEffectMapBase {
    explicit cTerrainEffectMapDeadColor(cTerrainStateMgr* m) : mStateMgr(m) {}
    virtual float Height();
    cTerrainStateMgr* mStateMgr;  // +0x10
};

}  // namespace

// EA::Swarm::cIEffectsManager (vtable slots up to RegisterMap)
struct IEffectsManager {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a(); virtual void s0b();
    virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
    virtual void s18(); virtual void s19(); virtual void s1a(); virtual void s1b();
    virtual void s1c(); virtual void s1d(); virtual void s1e(); virtual void s1f();
    virtual void s20(); virtual void s21();
    virtual void RegisterMap(unsigned int mapInstance, unsigned int mapGroup, cIMap* pMap);  // 0x88
};

IEffectsManager* EffectsManager();  // SP::EffectsManager 0x0067ddd0

// 0x00f717b0 (cdecl): called from the terrain-state setup with (map set, state manager, viewer)
void RegisterTerrainEffectMaps(cTerrainMapSet* set, cTerrainStateMgr* mgr, cViewer* viewer) {
    IEffectsManager* em = EffectsManager();
    em->RegisterMap(0xf86c06, 0, new("Terrain/EffectMap/Height", 0, 0, 0, 0) cTerrainEffectMapHeight(set));
    em->RegisterMap(0x276b1e8, 0, new("Terrain/EffectMap/Gradient", 0, 0, 0, 0) cTerrainEffectMapGradient(set));
    em->RegisterMap(0xf86c19, 0, new("Terrain/EffectMap/Normal", 0, 0, 0, 0) cTerrainEffectMapNormal(set));
    em->RegisterMap(0xf86c22, 0, new("Terrain/EffectMap/FirstDeriv", 0, 0, 0, 0) cTerrainEffectMapFirstDeriv(set, mgr));
    em->RegisterMap(0x1acdb9c, 0, new("Terrain/EffectMap/Above", 0, 0, 0, 0) cTerrainEffectMapAbove(set));
    em->RegisterMap(0x1c8a626, 0, new("Terrain/EffectMap/AboveBinary", 0, 0, 0, 0) cTerrainEffectMapAboveBinary(set));
    em->RegisterMap(0x1acdb92, 0, new("Terrain/EffectMap/Beach", 0, 0, 0, 0) cTerrainEffectMapBeach(set));
    em->RegisterMap(0x1c8a61e, 0, new("Terrain/EffectMap/BeachBinary", 0, 0, 0, 0) cTerrainEffectMapBeachBinary(set));
    em->RegisterMap(0x1acdb88, 0, new("Terrain/EffectMap/Cliff", 0, 0, 0, 0) cTerrainEffectMapCliff(set));
    em->RegisterMap(0x1c8a610, 0, new("Terrain/EffectMap/CiffBinary", 0, 0, 0, 0) cTerrainEffectMapCiffBinary(set));
    em->RegisterMap(0x1acdba5, 0, new("Terrain/EffectMap/SeaBed", 0, 0, 0, 0) cTerrainEffectMapSeaBed(set));
    em->RegisterMap(0x1c8a62f, 0, new("Terrain/EffectMap/SeaBedBinary", 0, 0, 0, 0) cTerrainEffectMapSeaBedBinary(set));
    em->RegisterMap(0x2c9c762, 0, new("Terrain/EffectMap/LiveDead", 0, 0, 0, 0) cTerrainEffectMapLiveDead(set, mgr));
    em->RegisterMap(0x2c9c763, 0, new("Terrain/EffectMap/Grass", 0, 0, 0, 0) cTerrainEffectMapGrass(set, mgr));
    em->RegisterMap(0x2c9c764, 0, new("Terrain/EffectMap/Flora", 0, 0, 0, 0) cTerrainEffectMapFlora(set, mgr));
    em->RegisterMap(0x2c9c765, 0, new("Terrain/EffectMap/LiveFlora", 0, 0, 0, 0) cTerrainEffectMapLiveFlora(set, mgr));
    em->RegisterMap(0x2c9c766, 0, new("Terrain/EffectMap/DeadFlora", 0, 0, 0, 0) cTerrainEffectMapDeadFlora(set, mgr));
    em->RegisterMap(0x2c9c767, 0, new("Terrain/EffectMap/DeadFloraColor", 0, 0, 0, 0) cTerrainEffectMapDeadFloraColor(mgr));
    em->RegisterMap(0x2f7dcd2, 0, new("Terrain/EffectMap/Specular", 0, 0, 0, 0) cTerrainEffectMapSpecular(mgr, viewer));
    em->RegisterMap(0x16f280b, 0, new("Terrain/EffectMap/Color", 0, 0, 0, 0) cTerrainEffectMapColor(set));
    em->RegisterMap(0x2e831a1, 0, new("Terrain/EffectMap/WaterColor", 0, 0, 0, 0) cTerrainEffectMapWaterColor(mgr));
    em->RegisterMap(0x2e831af, 0, new("Terrain/EffectMap/DeadColor", 0, 0, 0, 0) cTerrainEffectMapDeadColor(mgr));
}

// --------------------------------------------------------------------------------------------------------
// 0x00f71f30 / 0x00f71f90 : helpers used by the terrain effect-map objects above.
// --------------------------------------------------------------------------------------------------------

// Probe object whose vtable slot +0x10 casts against the terrain and writes a 3-float hit point.
// Slots +0x00..+0x0c are other queries; only slot 4 is called here.
class cTerrainProbe {
public:
    virtual bool query0();
    virtual bool query1();
    virtual bool query2();
    virtual bool query3();
    virtual bool castPoint(const float* pos, float* hit, int a, int b, int c, int d);  // +0x10
    float distance(const float* pos, int a, int b);                                      // 0x00f71f30
};

// @ 0x00f71f30
float cTerrainProbe::distance(const float* pos, int a, int b)
{
    float hit[3];
    if (castPoint(pos, hit, 0, 0, a, b)) {
        float dx = pos[0] - hit[0];
        float dy = pos[1] - hit[1];
        float dz = pos[2] - hit[2];
        return sqrtf(dx * dx + dy * dy + dz * dz);
    }
    return 0.0f;
}

// cSPTransformOps::Assign(const void*): copies a transform blob into this object (0x00537dc0).
struct cSPTransformOps {
    char pad00[0x38];
    float mHeight;                      // +0x38
    cSPTransformOps* Assign(const void* src);
};

// Height source: two float pointers bounding the per-cell height samples.
struct cTerrainHeightSource {
    char pad00[0x40];
    const float* mBegin;                // +0x40
    const float* mEnd;                  // +0x44
};

// @ 0x00f71f90
void __stdcall SetTransformHeight(cTerrainHeightSource* src, const void* unused, const void* blob,
                                  cSPTransformOps* xf)
{
    xf->Assign(blob);
    xf->mHeight = 0;
    const float* p = src->mBegin;
    if (p != src->mEnd)
        xf->mHeight = *p;
}

// Terrain cast probes that share the 0x00f71f30 distance query. Both are thiscall with 6 stack
// arguments (ret 0x18); declared here for the slice bookkeeping, not reproduced byte-exactly.
// 0x00f71fc0 : cell blob at arg5 (+0 flag word, +0x02/+0x04/+0x06 offsets, +0x08 scale,
//              +0x14..+0x34 3x3 basis, +0x1c extra), radius in arg1, in/out position arg3,
//              out normal arg4.
// 0x00f72290 : capsule blob at arg5 (+0 flags, +0x04/+0x08/+0x10 offsets, +0x10 scale,
//              +0x14..+0x34 3x3 basis, +0x38 radius), direction arg1, out position arg2,
//              out normal arg3, user data arg4.
class cTerrainCastProbe {
public:
    int sweepSphere(float radius, int flags, float* pos, float* normal,
                    const unsigned char* cell, int user);
    int sweepCapsule(const float* dir, float* pos, float* normal, void* user,
                     const unsigned char* shape, int flags);
};
